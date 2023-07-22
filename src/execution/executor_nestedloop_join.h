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

class NestedLoopJoinExecutor : public AbstractExecutor {
   private:
    std::unique_ptr<AbstractExecutor> left_;    // 左儿子节点（需要join的表）
    std::unique_ptr<AbstractExecutor> right_;   // 右儿子节点（需要join的表）
    size_t len_;                                // join后获得的每条记录的长度
    std::vector<ColMeta> cols_;                 // join后获得的记录的字段

    std::vector<Condition> fed_conds_;          // join条件
    bool isend;
    std::map<TabCol, Value> prev_feed_dict_;
   public:
    NestedLoopJoinExecutor(std::unique_ptr<AbstractExecutor> left, std::unique_ptr<AbstractExecutor> right, 
                            std::vector<Condition> conds) {
        left_ = std::move(left);
        right_ = std::move(right);
        len_ = left_->tupleLen() + right_->tupleLen();
        cols_ = left_->cols();
        auto right_cols = right_->cols();
        for (auto &col : right_cols) {
            col.offset += left_->tupleLen();
        }

        cols_.insert(cols_.end(), right_cols.begin(), right_cols.end());
        isend = false;
        fed_conds_ = std::move(conds);

    }

      std::string getType() override { return "Join"; }

    size_t tupleLen() const override { return len_; }

    const std::vector<ColMeta> &cols() const override { return cols_; }

    void beginTuple() override {
        left_->beginTuple();
        if (left_->is_end()) {
            return;
        }
        feed_right();
        right_->beginTuple();
        while (right_->is_end()) {
            // 此处任务点取消,不用做
            // lab3 task2 Todo
            // 如果当前innerTable(右表或算子)扫描完了
            // 你需要移动到outerTable(左表)下一个记录,然后把右表移动到第一个记录的位置
            left_->nextTuple();
            if (left_->is_end()) {
                break;
            }
            feed_right();
            right_->beginTuple();
            // lab3 task2 Todo end
        }
    }

    void nextTuple() override {
        assert(!is_end());
        right_->nextTuple();
        while (right_->is_end()) {
            // lab3 task2 Todo
            // 如果右节点扫描完了
            // 你需要把左表移动到下一个记录并把右节点回退到第一个记录
            // lab3 task2 Todo end

            // Move to the next record in the left table and reset the right table to the first record
        left_->nextTuple();
        if (left_->is_end()) {
            break;
        }
        feed_right();
        right_->beginTuple();
    }
        }
    

    bool is_end() const override { return left_->is_end(); }

    std::unique_ptr<RmRecord> Next() override {
        assert(!is_end());
        auto record = std::make_unique<RmRecord>(len_);
        // lab3 task2 Todo
        // 你需要调用左右算子的Next()获取下一个记录进行拼接赋给返回的连接结果std::make_unique<RmRecord>record中
        // memecpy()可能对你有所帮助
        // lab3 task2 Todo End
        // Join the next record from the left and right tables and assign it to the result record
    auto left_record = left_->Next();
    auto right_record = right_->Next();
    memcpy(record->data, left_record->data, left_->tupleLen());
    memcpy(record->data + left_->tupleLen(), right_record->data, right_->tupleLen());
    return record;
    }

    // 递归更新条件谓词
    void feed(const std::map<TabCol, Value> &feed_dict) override {
        prev_feed_dict_ = feed_dict;
        left_->feed(feed_dict);
    }

    // 默认以right 作inner table
    void feed_right() {
        // 将左子算子的ColMeta数组和对应的下一个元组转换成<TabCol,Value>的map
        // 每一个表列和其对应的Value相对应
        auto left_dict = rec2dict(left_->cols(), left_->Next().get());
        auto feed_dict = prev_feed_dict_;
        // 将左子算子的<列,值>map中的KV对增加到prev_feed_dict_(feed_dict)中
        feed_dict.insert(left_dict.begin(), left_dict.end());
        // 右子算子调用feed,对当前的feed_dict
        // 重置右子算子的连接条件
        right_->feed(feed_dict);
    }

    Rid &rid() override { return _abstract_rid; }
    
};