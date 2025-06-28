/* Copyright (c) 2023 Renmin University of China
RMDB is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
        http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "rm_scan.h"
#include "rm_file_handle.h"

/**
 * @brief 初始化file_handle和rid
 * @param file_handle
 */
RmScan::RmScan(const RmFileHandle *file_handle) : file_handle_(file_handle) {
    // 数据页从1开始，0是文件头页
    rid_ = {1, -1};
    next();
}

/**
 * @brief 找到文件中下一个存放了记录的位置
 */
void RmScan::next() {
    int current_page = rid_.page_no;
    int current_slot = rid_.slot_no;

    while(current_page < file_handle_->file_hdr_.num_pages) {
        // 在当前页内查找下一个有效的记录
        current_slot = Bitmap::next_bit(true, file_handle_->fetch_page_handle(current_page).bitmap,
                                          file_handle_->file_hdr_.num_records_per_page, current_slot);
        
        if (current_slot < file_handle_->file_hdr_.num_records_per_page) {
            // 找到了
            rid_ = {current_page, current_slot};
            return;
        }

        // 当前页扫描完毕，移动到下一页
        current_page++;
        current_slot = -1; // 从下一页的第一个槽位开始
    }

    // 如果循环结束仍未找到，说明已到达文件末尾
    rid_ = {RM_NO_PAGE, -1};
}

/**
 * @brief ​ 判断是否到达文件末尾
 */
bool RmScan::is_end() const {
    return rid_.page_no == RM_NO_PAGE;
}

/**
 * @brief RmScan内部存放的rid
 */
Rid RmScan::rid() const {
    return rid_;
}