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

class UpdateExecutor : public AbstractExecutor {
   private:
    TabMeta tab_;
    std::vector<Condition> conds_;
    RmFileHandle *fh_;
    std::vector<Rid> rids_;
    std::string tab_name_;
    std::vector<SetClause> set_clauses_;
    SmManager *sm_manager_;
    //Transaction *UpdateExecutor::transaction();
   public:
    UpdateExecutor(SmManager *sm_manager, const std::string &tab_name, std::vector<SetClause> set_clauses,
                   std::vector<Condition> conds, std::vector<Rid> rids, Context *context) {
        sm_manager_ = sm_manager;
        tab_name_ = tab_name;
        set_clauses_ = set_clauses;
        tab_ = sm_manager_->db_.get_table(tab_name);
        fh_ = sm_manager_->fhs_.at(tab_name).get();
        conds_ = conds;
        rids_ = rids;
        context_ = context;
    }
    std::unique_ptr<RmRecord> Next() override {
        // Get all necessary index files
        std::vector<IxIndexHandle *> ihs(tab_.cols.size(), nullptr);
        for (auto &set_clause : set_clauses_) {
            auto lhs_col = tab_.get_col(set_clause.lhs.col_name);
            if (lhs_col->index) {
                size_t lhs_col_idx = lhs_col - tab_.cols.begin();
                // lab3 task3 Todo
                // 获取需要的索引句柄,填充vector ihs
                ihs[lhs_col_idx] = sm_manager_->ihs_.at(tab_name_ + "." + set_clause.lhs.col_name).get();
                // lab3 task3 Todo end
            }
        }
        // Update each rid from record file and index file
        for (auto &rid : rids_) {
            auto rec = fh_->get_record(rid, context_);
            // lab3 task3 Todo
            // Remove old entry from index
            //  for (size_t i = 0; i < tab_.cols.size(); i++) {
            //     if (ihs[i] != nullptr) {
            //         auto col = tab_.cols[i];
            //         std::string col_value(rec->data + col.offset, col.len);
            //         ihs[i]->delete_entry(col_value.c_str(),transaction); //transacion 要不要使用？
            //     }
            // }

            // lab3 task3 Todo end

            // record a update operation into the transaction
            RmRecord update_record{rec->size};
            memcpy(update_record.data, rec->data, rec->size);

            // lab3 task3 Todo
            // Update record in record file
             for (auto &set_clause : set_clauses_) {
                auto lhs_col = tab_.get_col(set_clause.lhs.col_name);
                std::string new_value(set_clause.rhs.str_val, lhs_col->len);
                memcpy(update_record.data + lhs_col->offset, new_value.data(), new_value.size());
            }
            fh_->update_record(rid, update_record.data, context_);

            // lab3 task3 Todo end

            // lab3 task3 Todo
            // Insert new entry into index
            
            // for (size_t i = 0; i < tab_.cols.size(); i++) {
            //     if (ihs[i] != nullptr) {
            //         auto col = tab_.cols[i];
            //         std::string col_value(update_record.data + col.offset, col.len);
            //         ihs[i]->insert_entry(col_value.c_str(), rid); //transaction
            //     }
            // }
    
            // lab3 task3 Todo end
        }
        return nullptr;
    }

    Rid &rid() override { return _abstract_rid; }
};