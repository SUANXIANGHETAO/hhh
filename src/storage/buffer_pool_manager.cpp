/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "buffer_pool_manager.h"

/**
 * @description: 从free_list或replacer中得到可淘汰帧页的 *frame_id
 * @return {bool} true: 可替换帧查找成功 , false: 可替换帧查找失败
 * @param {frame_id_t*} frame_id 帧页id指针,返回成功找到的可替换帧id
 */
bool BufferPoolManager::find_victim_page(frame_id_t* frame_id) {
    // Todo:
    // 1 使用BufferPoolManager::free_list_判断缓冲池是否已满需要淘汰页面
    
    // 1.1 未满获得frame
    // 1.2 已满使用lru_replacer中的方法选择淘汰页面
    if (!free_list_.empty()) {
        *frame_id = free_list_.front();
        free_list_.pop_front();
        return true;
    }
    else {
        return replacer_->victim(frame_id);
    }
}

/**
 * @description: 更新页面数据, 如果为脏页则需写入磁盘，再更新为新页面，更新page元数据(data, is_dirty, page_id)和page table
 * @param {Page*} page 写回页指针
 * @param {PageId} new_page_id 新的page_id
 * @param {frame_id_t} new_frame_id 新的帧frame_id
 */
void BufferPoolManager::update_page(Page *page, PageId new_page_id, frame_id_t new_frame_id) {
    //判断是否为脏页
    if (page->is_dirty_) {
        page->is_dirty_ = false;
        disk_manager_->write_page(page->get_page_id().fd, page->get_page_id().page_no, page->get_data(), PAGE_SIZE);
    }
    //更新页表内容
    page_table_.erase(page->get_page_id());
    page_table_.insert(std::make_pair(new_page_id, new_frame_id));
   
    //更新page元数据
    page->reset_memory();
    page->id_= new_page_id;
    
    

    
}

/**
 * @description: 从buffer pool获取需要的页。
 *              如果页表中存在page_id（说明该page在缓冲池中），并且pin_count++。
 *              如果页表不存在page_id（说明该page在磁盘中），则找缓冲池victim page，将其替换为磁盘中读取的page，pin_count置1。
 * @return {Page*} 若获得了需要的页则将其返回，否则返回nullptr
 * @param {PageId} page_id 需要获取的页的PageId
 */
Page* BufferPoolManager::fetch_page(PageId page_id) {
    // Todo:
     //  1.     从page_table_中搜寻目标页
     //  1.1    若目标页有被page_table_记录，则将其所在frame固定(pin)，并返回目标页。
     //  1.2    否则，尝试调用find_victim_page获得一个可用的frame，若失败则返回nullptr
     //  2.     若获得的可用frame存储的为dirty page，则须调用updata_page将page写回到磁盘
     //  3.     调用disk_manager_的read_page读取目标页到frame
     //  4.     固定目标页，更新pin_count_
     //  5.     返回目标页
     
     //并发锁
    std::unique_lock<std::mutex> lock(latch_);
    //根据PageId 找到在页表中的记录
    std::unordered_map<PageId, frame_id_t, PageIdHash>::iterator it = page_table_.find(page_id);
    //若目标页有被page_table_记录，则将其所在frame固定(pin)，并返回目标页。
    if (it != page_table_.end()) {
        frame_id_t fid = it->second;
        replacer_->pin(fid);
        pages_[fid].pin_count_++;
        return &pages_[fid];
    }
    //否则，尝试调用find_victim_page获得一个可用的frame，若失败则返回nullptr
    else {
        frame_id_t frame_id = -1;
        //  2.     若获得的可用frame存储的为dirty page，则须调用updata_page将page写回到磁盘
        if (!find_victim_page(&frame_id)) {
            return nullptr;
        }
     //  3.     调用disk_manager_的read_page读取目标页到frame
     //  4.     固定目标页，更新pin_count_
     //  5.     返回目标页
        Page* P = &pages_[frame_id];
        update_page(P, page_id, frame_id);
        disk_manager_->read_page(page_id.fd, page_id.page_no, P->data_, PAGE_SIZE);
        replacer_->pin(frame_id);
        P->pin_count_ = 1;
        return P;
    }

}

/**
 * @description: 取消固定pin_count>0的在缓冲池中的page
 * @return {bool} 如果目标页的pin_count<=0则返回false，否则返回true
 * @param {PageId} page_id 目标page的page_id
 * @param {bool} is_dirty 若目标page应该被标记为dirty则为true，否则为false
 */
bool BufferPoolManager::unpin_page(PageId page_id, bool is_dirty) {
    // Todo:
        // 0. lock latch
        // 1. try to search page_id page P in page_table_
        // 1.1 P在页表中不存在 return false
        // 1.2 P在页表中存在 如何解除一次固定(pin_count)
        // 2. 页面是否需要置脏

        //并发锁
    std::unique_lock<std::mutex> lock(latch_);
    //根据PageId 找到在页表中的记录
    std::unordered_map<PageId, frame_id_t, PageIdHash>::iterator it = page_table_.find(page_id);
    // 1.1 P在页表中不存在 return false
    if (it == page_table_.end()) {
        return false;
    }

    // 1.2 P在页表中存在 解除一次固定(pin_count)
    else {
        frame_id_t fid = it->second;
        Page* P = &pages_[fid];
        if (P->pin_count_ == 0) {
            return false;
        }
        P->pin_count_--;
        if (P->pin_count_ == 0) {
            replacer_->unpin(fid);
        }
        // 2. 页面是否需要置脏
        if (is_dirty) {
            P->is_dirty_ = true;
        }
        return true;
    }
}

/**
 * @description: 将目标页写回磁盘，不考虑当前页面是否正在被使用
 * @return {bool} 成功则返回true，否则返回false(只有page_table_中没有目标页时)
 * @param {PageId} page_id 目标页的page_id，不能为INVALID_PAGE_ID
 */
bool BufferPoolManager::flush_page(PageId page_id) {    
    // Todo:
    // 0. lock latch
    // 1. 页表查找
    // 2. 存在时如何写回磁盘
    // 3. 写回后页面的脏位
    // Make sure you call DiskManager::WritePage!

    //并发锁
    std::unique_lock<std::mutex> lock(latch_);
    //根据PageId 找到在页表中的记录
    std::unordered_map<PageId, frame_id_t, PageIdHash>::iterator it = page_table_.find(page_id);
    //页表不存在此PageId记录
    if (it == page_table_.end()) {
        return false;
    }
    //存在时候 将数据写回磁盘 并且脏位变回false
    else {
        frame_id_t fid = it->second;
        Page* P = &pages_[fid];
        disk_manager_->write_page(P->get_page_id().fd, P->get_page_id().page_no, P->get_data(), PAGE_SIZE);
        P->is_dirty_ = false;
        return true;
    }
    
}

/**
 * @description: 创建一个新的page，即从磁盘中移动一个新建的空page到缓冲池某个位置。
 * @return {Page*} 返回新创建的page，若创建失败则返回nullptr
 * @param {PageId*} page_id 当成功创建一个新的page时存储其page_id
 */
Page* BufferPoolManager::new_page(PageId* page_id) {
    frame_id_t frame_id = -1 ;//初始化 缓冲区未成功分配内存时候 frame号为-1
    std::unique_lock<std::mutex> lock(latch_);//并发锁
    //未找到可淘汰页面 创建失败则返回nullptr
    if (!find_victim_page(&frame_id)) {
        return nullptr;
    }
    // 新建并初始化一个PageId* 指针 成功创建一个新的page存储其page_id
    *page_id = { page_id->fd, disk_manager_->allocate_page(page_id->fd) };
    
    Page* page = &pages_[frame_id];
    update_page(page, *page_id, frame_id);
    replacer_->pin(frame_id);
    page->pin_count_ = 1;
    return page;
}

/**
 * @description: 从buffer_pool删除目标页
 * @return {bool} 如果目标页不存在于buffer_pool或者成功被删除则返回true，若其存在于buffer_pool但无法删除则返回false
 * @param {PageId} page_id 目标页
 */
bool BufferPoolManager::delete_page(PageId page_id) {
    
    // Todo:
        // 0.   lock latch
        // 1.   Make sure you call DiskManager::DeallocatePage!
        // 2.   Search the page table for the requested page (P).
        // 2.1  If P does not exist, return true.
        // 2.2  If P exists, but has a non-zero pin-count, return false. Someone is using the page.
        // 3.   Otherwise, P can be deleted. Remove P from the page table, reset its metadata and return it to the free
        // list.
    
    //0.并发锁
    std::unique_lock<std::mutex> lock(latch_);
    //如果不存在此页 直接返回true
    auto it = page_table_.find(page_id);
    if (it == page_table_.end()) {
        return true;
    }
    //存在此页时 判断此页的固定数 如果大于0 则不能删除 返回false
    frame_id_t frame_id = it->second;
    Page* page = &pages_[frame_id];
    if (page->pin_count_ > 0) {
        return false;
    }
    //否则 删除此页 并且更新相关数据结构内容 返回true
    disk_manager_->deallocate_page(page_id.page_no);
    page_id.page_no = INVALID_PAGE_ID;
    page_table_.erase(it);
    page->reset_memory();
    free_list_.push_back(frame_id);
    return true;
}

/**
 * @description: 将buffer_pool中的所有页写回到磁盘
 * @param {int} fd 文件句柄
 */
void BufferPoolManager::flush_all_pages(int fd) {
    
    std::unique_lock<std::mutex> lock(latch_);//并发锁
    //循环遍历 缓冲区对应的pages集合 依次将页面数据写回磁盘 更新脏位为false
    for (size_t i = 0; i < pool_size_; i++) {
        Page* page = &pages_[i];
        if (page->get_page_id().page_no != INVALID_PAGE_ID&&page->is_dirty_) {
            disk_manager_->write_page(page->get_page_id().fd, page->get_page_id().page_no, page->get_data(), PAGE_SIZE);
            page->is_dirty_ = false;
        }

    }
    
    
}