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
#ifndef SPIFLASHHELPER_H
#define SPIFLASHHELPER_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <spi_flash.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SPI_FLASH_SEC_SIZE_LOG2 12

#define SPI_FLASH_MIN_WRITE_SIZE (sizeof(uint32_t))

static inline uint32_t ICACHE_FLASH_ATTR getFlashAddress(uint32_t sector);

static inline uint16_t ICACHE_FLASH_ATTR getFlashSector(uint32_t address);

static inline uint32_t ICACHE_FLASH_ATTR getFlashSectorOffset(uint32_t address);

static inline uint32_t ICACHE_FLASH_ATTR getFlashAddress(uint32_t sector)
{
  return ((uint32_t) sector) << SPI_FLASH_SEC_SIZE_LOG2;
}

static inline uint16_t ICACHE_FLASH_ATTR getFlashSector(uint32_t address)
{
  return ((uint16_t)((address >> SPI_FLASH_SEC_SIZE_LOG2)));
}

static inline uint32_t ICACHE_FLASH_ATTR getFlashSectorOffset(uint32_t address)
{
  return address & (SPI_FLASH_SEC_SIZE - 1);
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
