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
#include "DemoFOTAUpdateSelfTest.h"

#include "FotaHub.h"
#include <stdlib.h>
#include <time.h>

static bool ICACHE_FLASH_ATTR runRandomSelfTest(uint8_t successRate);

void ICACHE_FLASH_ATTR fotaUpdateSelfTest_init(void)
{
  srand(((uint32_t)(time(NULL))));
}

static bool ICACHE_FLASH_ATTR runRandomSelfTest(uint8_t successRate)
{
  if (((uint8_t)((os_random() % 100))) >= (successRate)) 
  {
    os_printf("Firmware self test failed (reason: simulated pseudo-random failure)\n");
    return false;
  }
  return true;
}

void ICACHE_FLASH_ATTR validateFirmwareUpdateActivation(void)
{
  os_printf("Validating firmware update\n");
  /* 
   * Perform any sort of tests and checks to see if device behaves as expected after firmware over-the-air update
   */
  if (runRandomSelfTest(SIMULATED_ACTIVATION_SUCCESS_RATE)) 
  {
    os_printf("Firmware update successfully activated\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_ACTIVATION_SUCCEEDED);
  }
  else
  {
    os_printf("Firmware update activation failed\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_ACTIVATION_FAILED);
  }
}

void ICACHE_FLASH_ATTR validateFirmwareUpdateReversion(void)
{
  os_printf("Validating previous firmware\n");
  /* 
   * Perform any sort of tests and checks to see if device behaves as expected after reversion firmware update
   */
  if (runRandomSelfTest(SIMULATED_REVERSION_SUCCESS_RATE)) 
  {
    os_printf("Firmware update successfully reverted\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_REVERSION_SUCCEEDED);
  }
  else
  {
    os_printf("Firmware update reversion failed\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_REVERSION_FAILED);
  }
}
