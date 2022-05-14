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
#include "UserLoopDrv.h"

#include <osapi.h>
#include "user_loop.h"

static void ICACHE_FLASH_ATTR osTimerCallback(void *pArg);

static os_timer_t hTimer;

void ICACHE_FLASH_ATTR userLoop_init(void)
{
  os_timer_disarm(&hTimer);
  os_timer_setfn(&hTimer, &osTimerCallback, NULL);
  os_timer_arm(&hTimer, USER_LOOP_INTERVAL, true);
}

static void ICACHE_FLASH_ATTR osTimerCallback(void *pArg)
{
  user_loop();
}
