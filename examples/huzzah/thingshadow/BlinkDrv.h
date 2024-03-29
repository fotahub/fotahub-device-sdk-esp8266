/*
 *  Copyright (C) 2022 FotaHub Inc. All rights reserved.
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
#ifndef BLINKDRV_H
#define BLINKDRV_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BLINK_PIN 0

#define BLINK_PIN_NAME (PERIPHS_IO_MUX_GPIO0_U)

#define BLINK_FUNC_GPIO (FUNC_GPIO0)

void ICACHE_FLASH_ATTR blink_init(uint16_t runPeriod, uint16_t blinkPeriod);

void ICACHE_FLASH_ATTR blink_run(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
