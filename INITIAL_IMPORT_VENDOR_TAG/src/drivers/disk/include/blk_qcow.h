/* 
 * <blk-qcow.h>
 *	
 * qemu block device read/write functions
 *   
 * Copyright (C) 2005 Joseph Jezak
 *
 * Based on the QEMU Block driver for the QCOW format
 * 
 * Copyright (c) 2004 Fabrice Bellard
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef _H_BLK_QCOW
#define _H_BLK_QCOW 

#include <zlib.h>
#include "platform.h"
#include "byteorder.h"
#include "blk_shared.h"
#include "ablk_sh.h"
#include "ablk.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/uio.h>
#include "aes.h"
#include <math.h>

/**************************************************************/
/* QEMU COW block driver with compression and encryption support */

#define QCOW_MAGIC (('Q' << 24) | ('F' << 16) | ('I' << 8) | 0xfb)
#define QCOW_VERSION 1

#define QCOW_CRYPT_NONE 0
#define QCOW_CRYPT_AES  1

#define QCOW_OFLAG_COMPRESSED (1LL << 63)

typedef struct QCowHeader {
    u32 magic;
    u32 version;
    u64 backing_file_offset;
    u32 backing_file_size;
    u32 mtime;
    u64 size; /* in bytes */
    u8 cluster_bits;
    u8 l2_bits;
    u32 crypt_method;
    u64 l1_table_offset;
} QCowHeader;

#define L2_CACHE_SIZE 16

typedef struct BDRVQcowState {
    int fd;
    int cluster_bits;
    int cluster_size;
    int cluster_sectors;
    int l2_bits;
    int l2_size;
    int l1_size;
    u64 cluster_offset_mask;
    u64 l1_table_offset;
    u64 *l1_table;
    u64 *l2_cache;
    u64 l2_cache_offsets[L2_CACHE_SIZE];
    u32 l2_cache_counts[L2_CACHE_SIZE];
    u8 *cluster_cache;
    u8 *cluster_data;
    u64 cluster_cache_offset;
    u32 crypt_method; /* current crypt method, 0 if no key yet */
    u32 crypt_method_header;
    AES_KEY aes_encrypt_key;
    AES_KEY aes_decrypt_key;

    /* Current block for seeking */
    long seek_block;
} BDRVQcowState;

/* Function declarations */
int qcow_open(bdev_desc_t *bdev);
int qcow_read(ablk_device_t *ad, u64 sector_num, u8 *buf, int nb_sectors);
int qcow_write(ablk_device_t *ad, u64 sector_num, const u8 *buf, int nb_sectors);
void qcow_close(bdev_desc_t *bdev);
void qcow_set_seek(ablk_device_t *ad, long block);

#endif
