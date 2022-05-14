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
#include "user_pre_init_default.h"

#include <user_interface.h>

static void ICACHE_FLASH_ATTR initPartitionTable(enum flash_size_map flashSizeMap);

static void ICACHE_FLASH_ATTR adjustPartitionTableDataForFlashSize_512(void);

static partition_item_t partitionTable[] = 
{
  { SYSTEM_PARTITION_BOOTLOADER, 0x0u, 0x1000u }, 
  { SYSTEM_PARTITION_OTA_1, 0x1000u, SYSTEM_PARTITION_OTA_SIZE }, 
  { SYSTEM_PARTITION_OTA_2, 0x101000u, SYSTEM_PARTITION_OTA_SIZE }, 
  { SYSTEM_PARTITION_RF_CAL, 0x3fb000u, 0x1000u }, 
  { SYSTEM_PARTITION_PHY_DATA, 0x3fc000u, 0x1000u }, 
  { SYSTEM_PARTITION_SYSTEM_PARAMETER, 0x3fd000u, 0x3000u }
};

static void ICACHE_FLASH_ATTR initPartitionTable(enum flash_size_map flashSizeMap)
{
  /* 
   * TODO: add dynamic OTA size support
   */
  switch (flashSizeMap)
  {
    case FLASH_SIZE_16M_MAP_1024_1024:
    {
      partitionTable[3].addr = 0x1fb000u;
      partitionTable[4].addr = 0x1fc000u;
      partitionTable[5].addr = 0x1fd000u;
      break;
    }
    case FLASH_SIZE_32M_MAP_512_512:
    {
      adjustPartitionTableDataForFlashSize_512();
      break;
    }
    case FLASH_SIZE_16M_MAP_512_512:
    {
      adjustPartitionTableDataForFlashSize_512();
      partitionTable[3].addr = 0x1fb000u;
      partitionTable[4].addr = 0x1fc000u;
      partitionTable[5].addr = 0x1fd000u;
      break;
    }
    case FLASH_SIZE_8M_MAP_512_512:
    {
      adjustPartitionTableDataForFlashSize_512();
      partitionTable[3].addr = 0xfb000u;
      partitionTable[4].addr = 0xfc000u;
      partitionTable[5].addr = 0xfd000u;
      break;
    }
    default: {
      /* 
       * Do nothing, use 32m-c1 (1024KB + 1024KB) settings
       */
    }
  }
}

static void ICACHE_FLASH_ATTR adjustPartitionTableDataForFlashSize_512(void)
{
  partitionTable[1].size = 0x7A000u;
  partitionTable[2].addr = 0x81000u;
  partitionTable[2].size = 0x7A000u;
  
}

void ICACHE_FLASH_ATTR user_pre_init(void)
{
  enum flash_size_map flashSizeMap = system_get_flash_size_map();
  if (flashSizeMap < 2) 
  {
    os_printf("The flash map is not supported\n");
    while (true)
    {
    }
  }
  
  initPartitionTable(flashSizeMap);
  
  if (!system_partition_table_regist(partitionTable, sizeof(partitionTable) / sizeof(partitionTable[0]), flashSizeMap)) 
  {
    os_printf("system_partition_table_regist fail\n");
    while (true)
    {
    }
  }
}

uint32_t user_iram_memory_is_enabled(void)
{
  return 1;
}
