/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once
#include "execution_defs.h"
#include "execution_manager.h"
#include "executor_abstract.h"
#include "index/ix.h"
#include "system/sm.h"

class ProjectionExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> prev_;        // 投影节点的儿子节点
    std::vector<ColMeta> cols_;                     // 需要投影的字段
    size_t len_;                                    // 字段总长度
    std::vector<size_t> sel_idxs_;                  //索引
    
    // 记录当前元组的数据
    std::vector<Value> curr_tuple_;
   public:
    ProjectionExecutor(std::unique_ptr<AbstractExecutor> prev, const std::vector<TabCol> &sel_cols) {
         prev_ = std::move(prev);//权限转移

    
    size_t curr_offset = 0;
       std::fstream outfile;
    auto &prev_cols = prev_->cols();

    for (auto &sel_col : sel_cols) {

        auto pos = get_col(prev_cols, sel_col);

        sel_idxs_.push_back(pos - prev_cols.begin());

        auto col = *pos;
        col.offset = curr_offset;
        curr_offset += col.len;
        cols_.push_back(col);
        
    }
    len_ = curr_offset;
    }
    std::string getType() override { return "Projection"; }

    size_t tupleLen() const override { return len_; }

    const std::vector<ColMeta> &cols() const override { return cols_; }
    
    void beginTuple() override {
         prev_->beginTuple();
    }

    void nextTuple() override {
        prev_->nextTuple();
    }
    bool is_end() const override { return prev_->is_end(); }

    std::unique_ptr<RmRecord> Next() override {
            assert(!is_end());
    auto prev_rec = prev_->Next();
    
    if (prev_rec == nullptr) {
        return nullptr; // 如果上一个执行器返回空指针，表示已经到达末尾，直接返回空指针
    }

    auto &prev_cols = prev_->cols();
    auto &proj_cols = cols_;
    auto proj_rec = std::make_unique<RmRecord>(len_);

    for (size_t proj_idx = 0; proj_idx < proj_cols.size(); proj_idx++) {
        size_t prev_idx = sel_idxs_[proj_idx];
        auto &prev_col = prev_cols[prev_idx];
        auto &proj_col = proj_cols[proj_idx];

        // 利用memcpy将数据从上一个记录复制到投影记录中
        memcpy(proj_rec->data + proj_col.offset, prev_rec->data + prev_col.offset, proj_col.len);
    }

    return proj_rec;
    }


    Rid &rid() override { return _abstract_rid; }
};