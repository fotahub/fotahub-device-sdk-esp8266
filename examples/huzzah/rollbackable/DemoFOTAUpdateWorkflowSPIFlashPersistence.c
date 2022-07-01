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
#include "DemoFOTAUpdateWorkflowSPIFlashPersistence.h"

#include "SPIFlashHelper.h"
#include "DemoFOTAUpdateWorkflowPersistence.h"
#include <mem.h>

void ICACHE_FLASH_ATTR saveState(int16_t state)
{
  uint16_t sector = getFlashSector(DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS);
  if (spi_flash_erase_sector(sector) != SPI_FLASH_RESULT_OK) 
  {
    os_printf("Failed to erase NVS sector %d\r\n", DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS);
  }
  if (spi_flash_write(DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS, ((uint32_t *)(&state)), ((uint32_t)(sizeof(state)))) != SPI_FLASH_RESULT_OK) 
  {
    os_printf("Failed write statemachine state to NVS sector %d\r\n", DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS);
  }
}

int16_t ICACHE_FLASH_ATTR loadState(void)
{
  int16_t state = 0;
  if (spi_flash_read(DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS, ((uint32_t *)(&state)), ((uint32_t)(sizeof(state)))) != SPI_FLASH_RESULT_OK) 
  {
    return 0;
  }
  /* 
   * Return initial state when persisted state is read from an uninitialized or 
   * freshly erased NVS flash sector
   */
  if (state == -1) 
  {
    return 0;
  }
  return state;
}
