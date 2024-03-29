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
#ifndef ESP8266AWSIOTTHINGSHADOWWIRING_H
#define ESP8266AWSIOTTHINGSHADOWWIRING_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include "MultiPartitionAWSIoTThingShadowDataPlane.h"
#include "ESP8266AWSIoTThingShadowStack.h"

#ifdef __cplusplus
extern "C" {
#endif

void ICACHE_FLASH_ATTR awsIoTThingShadow_run(void);

void ICACHE_FLASH_ATTR awsIoTThingShadowInstances__init(void);

/* 
 * comp instance data
 */
extern MultiPartitionAWSIoTThingShadowIOHandlerImpl__cdata_t awsIoTThingShadowInstances_thingShadowIOHandlerInst__instance;

extern IJSONDocumentIOHandler__idata_t awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops;

/* 
 * comp instance data
 */
extern AWSIoTThingShadowGateImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance;

extern IConnectionMonitorHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_connectionMonitorHandler__ops;

extern IIoTClientHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops;

extern IFOTAUpdateStatusHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_fotaUpdateStatusHandler__ops;

extern IRunnable__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_runnable__ops;

/* 
 * comp instance data
 */
extern AWSIoTMQTTThingShadowImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance;

extern IIoTClient__idata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops;

extern IMQTTClientHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops;

extern ITimerHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_timeoutHandler__ops;

/* 
 * comp instance data
 */
extern MQTTClientImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance;

extern IMQTTClient__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops;

extern IClientSocketHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops;

extern ITimerHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimerHandler__ops;

extern ITimerHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimeoutHandler__ops;

/* 
 * comp instance data
 */
extern ESPConnClientImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance;

extern IDNSLookupHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_dnsLookupHandler__ops;

extern IClientSocket__idata_t awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops;

/* 
 * comp instance data
 */
extern DNSClientImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__instance;

extern IDNSClient__idata_t awsIoTThingShadowInstances_thingShadowStack_dnsClientInst_dnsClient__ops;

/* 
 * comp instance data
 */
extern DynamicDatagramPoolImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__instance;

extern IDatagramPool__idata_t awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops;

/* 
 * comp instance data
 */
extern JSONProcessorImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__instance;

extern IJSONParser__idata_t awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonParser__ops;

extern IJSONSerializer__idata_t awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops;

/* 
 * comp instance data
 */
extern ESP8266AWSIoTThingShadowStack__cdata_t awsIoTThingShadowInstances_thingShadowStack___shadow__instance;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
