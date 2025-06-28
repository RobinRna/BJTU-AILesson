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
#include "errors.h" // For throwing exceptions

/**
 * @brief 初始化file_handle和rid
 * @param file_handle
 */
RmScan::RmScan(const RmFileHandle *file_handle) : file_handle_(file_handle) {
    // Todo:
    // 初始化file_handle和rid（指向第一个存放了记录的位置）
    
    // Corrected: Use const_cast to call non-const member function from a const object pointer
    if (const_cast<RmFileHandle*>(file_handle_)->get_file_hdr().num_pages <= 1) { // Only header page exists
        rid_ = {RM_NO_PAGE, -1};
    } else {
        rid_ = {1, -1}; // Start from first data page
        next();
    }
}

/**
 * @brief 找到文件中下一个存放了记录的位置
 */
void RmScan::next() {
    // Todo:
    // 找到文件中下一个存放了记录的非空闲位置，用rid_来指向这个位置
    
    // Corrected: Use const_cast to call non-const member function
    const auto& file_hdr = const_cast<RmFileHandle*>(file_handle_)->get_file_hdr();
    rid_.slot_no++; 

    while (rid_.page_no < file_hdr.num_pages) {
        RmPageHandle page_handle = file_handle_->fetch_page_handle(rid_.page_no);
        while (rid_.slot_no < file_hdr.num_records_per_page) {
            if (Bitmap::is_set(page_handle.bitmap, rid_.slot_no)) {
                file_handle_->buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), false);
                return;
            }
            rid_.slot_no++;
        }
        file_handle_->buffer_pool_manager_->unpin_page(page_handle.page->get_page_id(), false);
        rid_.page_no++;
        rid_.slot_no = 0;
    }
    
    rid_.page_no = RM_NO_PAGE;
}

/**
 * @brief ​ 判断是否到达文件末尾
 */
bool RmScan::is_end() const {
    // Todo: 修改返回值
    return rid_.page_no == RM_NO_PAGE;
}

/**
 * @brief RmScan内部存放的rid
 */
Rid RmScan::rid() const {
    if(is_end()) {
        // Corrected: Use a defined exception type
        throw InternalError("Record scan is end.");
    }
    return rid_;
}