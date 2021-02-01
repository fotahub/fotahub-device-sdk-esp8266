/*
 *  Copyright (C) 2020-2021 FotaHub Inc. All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  This file is part of the FotaHub(R) Device SDK program (https://fotahub.com)
 */
#ifndef USER_PRE_INIT_DEFAULT_H
#define USER_PRE_INIT_DEFAULT_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SYSTEM_PARTITION_OTA_SIZE 0x8A000u

void ICACHE_FLASH_ATTR user_pre_init(void);

uint32_t user_iram_memory_is_enabled(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
