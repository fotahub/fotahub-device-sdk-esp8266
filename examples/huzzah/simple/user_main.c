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
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "user_config.h"
#include "WiFiStationDrv.h"
#include "UARTDrv.h"
#include "UserLoopDrv.h"
#include "BlinkDrv.h"
#include "MultiPartitionDemoFirmwareUpdateInfoSerialReader.h"
#include "DemoFOTAUpdateWorkflow.h"
#include "DemoProductInfo.h"
#include "FotaHub.h"
#include <user_interface.h>
#include "user_loop.h"
#include "user_pre_init_default.h"

void ICACHE_FLASH_ATTR user_init(void)
{
  one_uart_init(UART_UNIT, UART_BAUDRATE);
  
  os_printf("\n--------------------------------------------------------------------------\n");
  os_printf("Running %s %s firmware from partition %d\n", ((char *)(DEMO_PRODUCT_NAME)), ((char *)(DEMO_PRODUCT_FIRMWARE_VERSION)), system_upgrade_userbin_check() + 1);
  os_printf("--------------------------------------------------------------------------\n\n");
  
  userLoop_init();
  blink_init(USER_LOOP_INTERVAL, BLINK_PERIOD);
  
  firmwareUpdateInfoReader_init();
  fotaUpdateWorkflow_init();
  fotahub_init(((char *)(DEMO_PRODUCT_ID)), ((char *)(DEMO_PRODUCT_NAME)), &ESP8266_FOTA_UPDATE_CLIENT_CONFIG, 0xF8u);
  
  wifiStation_connect(((char *)(WIFI_STATION_SSID)), ((char *)(WIFI_STATION_PASSWORD)));
}

void ICACHE_FLASH_ATTR user_loop(void)
{
  firmwareUpdateInfoReader_run();
  fotahub_run();
  blink_run();
}
