/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "lru_replacer.h"
#include "mutex"
LRUReplacer::LRUReplacer(size_t num_pages) { max_size_ = num_pages; }

LRUReplacer::~LRUReplacer() = default;  

/**
 * @description: 使用LRU策略删除一个victim frame，并返回该frame的id
 * @param {frame_id_t*} frame_id 被移除的frame的id，如果没有frame被移除返回nullptr
 * @return {bool} 如果成功淘汰了一个页面则返回true，否则返回false
 */
bool LRUReplacer::victim(frame_id_t* frame_id) {
    // C++17 std::scoped_lock
    // 它能够避免死锁发生，其构造函数能够自动进行上锁操作，析构函数会对互斥量进行解锁操作，保证线程安全。
   // std::scoped_lock lock{latch_};  //  如果编译报错可以替换成其他lock
    
    std::unique_lock<std::mutex> lock(latch_);
    // Todo:
    //  利用lru_replacer中的LRUlist_,LRUHash_实现LRU策略
    //  选择合适的frame指定为淘汰页面,赋值给*frame_id
      if (LRUlist_.empty()) {
        // 没有可淘汰的页面
        frame_id = nullptr;
        return false;
    }

    // 选择链表尾部的页面作为淘汰页面
    frame_id_t victim_frame_id = LRUlist_.back();
    LRUlist_.pop_back();  // 从LRU list中移除
    LRUhash_.erase(victim_frame_id);  // 从LRU Hash中删除

    *frame_id = victim_frame_id;
    return true;
}

/**
 * @description: 固定指定的frame，即该页面无法被淘汰
 * @param {frame_id_t} 需要固定的frame的id
 */
void LRUReplacer::pin(frame_id_t frame_id) {
    //std::scoped_lock lock{latch_};
    //std::mutex mutex;
    std::unique_lock<std::mutex> lock(latch_);
    // Todo:
    // 固定指定id的frame
    // 在数据结构中移除该frame
     // 检查该frame是否存在于LRU Hash中
    auto it = LRUhash_.find(frame_id);
    if (it != LRUhash_.end()) {
        // 从LRU list和LRU Hash中删除该frame
        LRUlist_.erase(it->second);
        LRUhash_.erase(it);
    }
}

/**
 * @description: 取消固定一个frame，代表该页面可以被淘汰
 * @param {frame_id_t} frame_id 取消固定的frame的id
 */
void LRUReplacer::unpin(frame_id_t frame_id) {
    // Todo:
    //  支持并发锁
    //  选择一个frame取消固定
      std::unique_lock<std::mutex> lock(latch_);

    // 检查该 frame 是否存在于 LRU Hash 中
    auto it = LRUhash_.find(frame_id);
    if (it == LRUhash_.end()) {
        // 如果 frame 不在 LRU Hash 中，将其添加回 LRU list 和 LRU Hash 中
        LRUlist_.push_front(frame_id);
        LRUhash_[frame_id] = LRUlist_.begin();
    }
}

/**
 * @description: 获取当前replacer中可以被淘汰的页面数量
 */
size_t LRUReplacer::Size() { return LRUlist_.size(); }
