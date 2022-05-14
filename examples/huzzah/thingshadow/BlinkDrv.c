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
#include "BlinkDrv.h"

#include <eagle_soc.h>
#include <gpio.h>

static uint16_t currentTick;

static uint16_t expirationTick;

void ICACHE_FLASH_ATTR blink_init(uint16_t runPeriod, uint16_t blinkPeriod)
{
  PIN_FUNC_SELECT(BLINK_PIN_NAME, BLINK_FUNC_GPIO);
  
  currentTick = 0;
  expirationTick = (blinkPeriod >> 1) / runPeriod;
}

void ICACHE_FLASH_ATTR blink_run(void)
{
  if (currentTick == expirationTick) 
  {
    uint32_t state = GPIO_INPUT_GET(BLINK_PIN);
    (state ^= (0x01u));
    GPIO_OUTPUT_SET(BLINK_PIN, state);
    
    currentTick = 0;
  }
  else
  {
    currentTick++;
  }
}
