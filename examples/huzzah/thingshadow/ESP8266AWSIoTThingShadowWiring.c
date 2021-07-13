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
#include "ESP8266AWSIoTThingShadowWiring.h"

#include "FotaHub.h"
#include "DemoFOTAUpdateWorkflow.h"
#include <string.h>

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowIOHandlerInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__wire(void);

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack___shadow__wire(void);

/* 
 * comp instance data
 */
MultiPartitionAWSIoTThingShadowIOHandlerImpl__cdata_t awsIoTThingShadowInstances_thingShadowIOHandlerInst__instance = { 0 };

IJSONDocumentIOHandler__idata_t awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops = { 0 };

/* 
 * comp instance data
 */
AWSIoTThingShadowGateImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance = { 0 };

IConnectionMonitorHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_connectionMonitorHandler__ops = { 0 };

IAWSIoTThingShadowHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops = { 0 };

IFOTAUpdateStatusHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_fotaUpdateStatusHandler__ops = { 0 };

IRunnable__idata_t awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_runnable__ops = { 0 };

/* 
 * comp instance data
 */
AWSIoTMQTTThingShadowImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance = { 0 };

IAWSIoTThingShadow__idata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops = { 0 };

IMQTTClientHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops = { 0 };

ITimerHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_timeoutHandler__ops = { 0 };

/* 
 * comp instance data
 */
MQTTClientImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance = { 0 };

IMQTTClient__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops = { 0 };

IClientSocketHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops = { 0 };

ITimerHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimerHandler__ops = { 0 };

ITimerHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimeoutHandler__ops = { 0 };

/* 
 * comp instance data
 */
ESPConnClientImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance = { 0 };

IDNSLookupHandler__idata_t awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_dnsLookupHandler__ops = { 0 };

IClientSocket__idata_t awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops = { 0 };

/* 
 * comp instance data
 */
DNSClientImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__instance = { 0 };

IDNSClient__idata_t awsIoTThingShadowInstances_thingShadowStack_dnsClientInst_dnsClient__ops = { 0 };

/* 
 * comp instance data
 */
DynamicDatagramPoolImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__instance = { 0 };

IDatagramPool__idata_t awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops = { 0 };

/* 
 * comp instance data
 */
JSONProcessorImpl__cdata_t awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__instance = { 0 };

IJSONParser__idata_t awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonParser__ops = { 0 };

IJSONSerializer__idata_t awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops = { 0 };

/* 
 * comp instance data
 */
ESP8266AWSIoTThingShadowStack__cdata_t awsIoTThingShadowInstances_thingShadowStack___shadow__instance = { 0 };

void ICACHE_FLASH_ATTR awsIoTThingShadow_run(void)
{
  AWSIoTThingShadowGateImpl_runnable_run(&awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance);
}

void ICACHE_FLASH_ATTR fotahub_onConnectionStatusChanged(ConnectionStatus_t status)
{
  fotaUpdateWorkflow_onConnectionStatusChanged(status);
  AWSIoTThingShadowGateImpl_connectionMonitorHandler_statusChanged(status, &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance);
}

void ICACHE_FLASH_ATTR fotahub_onFirmwareUpdateStatusChanged(FOTAUpdateStatus_t status)
{
  fotaUpdateWorkflow_onFirmwareUpdateStatusChanged(status);
  AWSIoTThingShadowGateImpl_fotaUpdateStatusHandler_updateStatus(status, &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance);
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowIOHandlerInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowIOHandlerInst
   */
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops.writeOutput = &MultiPartitionAWSIoTThingShadowIOHandlerImpl_jsonDocumentIOHandler_writeOutput;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops.readInput = &MultiPartitionAWSIoTThingShadowIOHandlerImpl_jsonDocumentIOHandler_readInput;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowIOHandlerInst__instance;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_thingShadowGateInst
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.awsIoTThingShadowSession__field = NULL;
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.updateAvailable__field = false;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_connectionMonitorHandler__ops.statusChanged = &AWSIoTThingShadowGateImpl_connectionMonitorHandler_statusChanged;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops.connected = &AWSIoTThingShadowGateImpl_thingShadowHandler_connected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops.status = &AWSIoTThingShadowGateImpl_thingShadowHandler_status;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops.delta = &AWSIoTThingShadowGateImpl_thingShadowHandler_delta;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops.disconnected = &AWSIoTThingShadowGateImpl_thingShadowHandler_disconnected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops.connectionError = &AWSIoTThingShadowGateImpl_thingShadowHandler_connectionError;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_fotaUpdateStatusHandler__ops.updateStatus = &AWSIoTThingShadowGateImpl_fotaUpdateStatusHandler_updateStatus;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_runnable__ops.run = &AWSIoTThingShadowGateImpl_runnable_run;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_connectionMonitorHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_fotaUpdateStatusHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_runnable__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance;
  /* 
   * connected req sr port
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.firmwareUpdateVersionInfo__port = &awsIoTThingShadowInstances_thingShadowIOHandlerInst__instance.firmwareUpdateVersionInfo__srdata;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.jsonDocumentIOHandler__ops = &awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.thingShadow__ops = &awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.jsonParser__ops = &awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonParser__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance.jsonSerializer__ops = &awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_awsIoTMQTTThingShadowInst
   */
  memset(awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance.baseComponentData.awsIoTRequests__field, 0, sizeof(awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance.baseComponentData.awsIoTRequests__field));
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.connect = &AWSIoTMQTTThingShadowImpl_thingShadow_connect;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.getUserData = &AbstractAWSIoTMQTTThingShadowImpl_thingShadow_getUserData;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.isConnected = &AbstractAWSIoTMQTTThingShadowImpl_thingShadow_isConnected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.update = &AbstractAWSIoTMQTTThingShadowImpl_thingShadow_update;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.get = &AbstractAWSIoTMQTTThingShadowImpl_thingShadow_get;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.disconnect = &AbstractAWSIoTMQTTThingShadowImpl_thingShadow_disconnect;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.connected = &AbstractAWSIoTMQTTThingShadowImpl_mqttClientHandler_connected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.subscribed = &AbstractAWSIoTMQTTThingShadowImpl_mqttClientHandler_subscribed;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.published = &AbstractAWSIoTMQTTThingShadowImpl_mqttClientHandler_published;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.publishMessageReceived = &AbstractAWSIoTMQTTThingShadowImpl_mqttClientHandler_publishMessageReceived;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.disconnected = &AbstractAWSIoTMQTTThingShadowImpl_mqttClientHandler_disconnected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.connectionError = &AbstractAWSIoTMQTTThingShadowImpl_mqttClientHandler_connectionError;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_timeoutHandler__ops.expired = &AbstractAWSIoTMQTTThingShadowImpl_timeoutHandler_expired;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_thingShadow__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_timeoutHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance.baseComponentData.mqttClient__ops = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance.baseComponentData.awsIoTThingShadowHandlers__ops[0] = &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst_thingShadowHandler__ops;
  
  /* 
   * implements
   */
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance.baseComponentData.thingShadow_connect__abstract = &AWSIoTMQTTThingShadowImpl_thingShadow_connect;
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_mqttClientInst
   */
  memset(awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance.mqttSessions__field, 0, sizeof(awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance.mqttSessions__field));
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.connect = &MQTTClientImpl_mqttClient_connect;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.isConnected = &MQTTClientImpl_mqttClient_isConnected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.getUserData = &MQTTClientImpl_mqttClient_getUserData;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.newDatagram = &MQTTClientImpl_mqttClient_newDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.newPublishMessage = &MQTTClientImpl_mqttClient_newPublishMessage;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.subscribe = &MQTTClientImpl_mqttClient_subscribe;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.sendPublishMessage = &MQTTClientImpl_mqttClient_sendPublishMessage;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.deleteDatagram = &MQTTClientImpl_mqttClient_deleteDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.disconnect = &MQTTClientImpl_mqttClient_disconnect;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops.connected = &MQTTClientImpl_clientSocketHandler_connected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops.datagramSent = &MQTTClientImpl_clientSocketHandler_datagramSent;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops.datagramReceived = &MQTTClientImpl_clientSocketHandler_datagramReceived;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops.disconnected = &MQTTClientImpl_clientSocketHandler_disconnected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops.connectionError = &MQTTClientImpl_clientSocketHandler_connectionError;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimerHandler__ops.expired = &MQTTClientImpl_keepAliveTimerHandler_expired;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimeoutHandler__ops.expired = &MQTTClientImpl_keepAliveTimeoutHandler_expired;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_mqttClient__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimerHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_keepAliveTimeoutHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance.socket__ops = &awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance.mqttClientHandler__ops = &awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst_mqttClientHandler__ops;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_espConnClientInst
   */
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_dnsLookupHandler__ops.hostNameResolved = &ESPConnClientImpl_dnsLookupHandler_hostNameResolved;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.connect = &ESPConnClientImpl_clientSocket_connect;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.isConnected = &ESPConnClientImpl_clientSocket_isConnected;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.getUserData = &ESPConnClientImpl_clientSocket_getUserData;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.newDatagram = &ESPConnClientImpl_clientSocket_newDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.resizeDatagram = &ESPConnClientImpl_clientSocket_resizeDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.sendDatagram = &ESPConnClientImpl_clientSocket_sendDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.deleteDatagram = &ESPConnClientImpl_clientSocket_deleteDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.disconnect = &ESPConnClientImpl_clientSocket_disconnect;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_dnsLookupHandler__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_clientSocket__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance.dnsClient__ops = &awsIoTThingShadowInstances_thingShadowStack_dnsClientInst_dnsClient__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance.datagramPool__ops = &awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance.clientSocketHandlers__ops[0] = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst_clientSocketHandler__ops;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_dnsClientInst
   */
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_dnsClientInst_dnsClient__ops.resolveHostName = &DNSClientImpl_dnsClient_resolveHostName;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_dnsClientInst_dnsClient__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__instance;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__instance.dnsLookupHandler__ops = &awsIoTThingShadowInstances_thingShadowStack_espConnClientInst_dnsLookupHandler__ops;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_datagramPoolInst
   */
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops.newDatagram = &DynamicDatagramPoolImpl_datagramPool_newDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops.resizeDatagram = &DynamicDatagramPoolImpl_datagramPool_resizeDatagram;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops.delete = &DynamicDatagramPoolImpl_datagramPool_delete;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst_datagramPool__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__instance;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack_jsonProcessorInst
   */
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonParser__ops.parse = &JSONProcessorImpl_jsonParser_parse;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonParser__ops.resetFlags = &JSONProcessorImpl_jsonParser_resetFlags;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.serialize = &JSONProcessorImpl_jsonSerializer_serialize;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.beginDocument = &JSONProcessorImpl_jsonSerializer_beginDocument;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.beginObject = &JSONProcessorImpl_jsonSerializer_beginObject;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.addValue = &JSONProcessorImpl_jsonSerializer_addValue;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.endObject = &JSONProcessorImpl_jsonSerializer_endObject;
  /* 
   * prov port
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.endDocument = &JSONProcessorImpl_jsonSerializer_endDocument;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonParser__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__instance;
  /* 
   * prov port owning instance
   */
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst_jsonSerializer__ops.__instance = &awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__instance;
  
}

static inline void ICACHE_FLASH_ATTR awsIoTThingShadowInstances_thingShadowStack___shadow__wire(void)
{
  /* 
   * INSTANCE: thingShadowStack___shadow
   */
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.thingShadowGateInst__field = &awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__instance;
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.awsIoTMQTTThingShadowInst__field = &awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__instance;
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.mqttClientInst__field = &awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__instance;
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.espConnClientInst__field = &awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__instance;
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.dnsClientInst__field = &awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__instance;
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.datagramPoolInst__field = &awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__instance;
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.jsonProcessorInst__field = &awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__instance;
  /* 
   * connected req sr port
   */
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.firmwareUpdateVersionInfo__port = &awsIoTThingShadowInstances_thingShadowIOHandlerInst__instance.firmwareUpdateVersionInfo__srdata;
  /* 
   * required port ops
   */
  awsIoTThingShadowInstances_thingShadowStack___shadow__instance.jSONDocumentIOHandler__ops = &awsIoTThingShadowInstances_thingShadowIOHandlerInst_jsonDocumentIOHandler__ops;
  
}

void ICACHE_FLASH_ATTR awsIoTThingShadowInstances__init(void)
{
  awsIoTThingShadowInstances_thingShadowIOHandlerInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_thingShadowGateInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_awsIoTMQTTThingShadowInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_mqttClientInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_espConnClientInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_dnsClientInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_datagramPoolInst__wire();
  awsIoTThingShadowInstances_thingShadowStack_jsonProcessorInst__wire();
  awsIoTThingShadowInstances_thingShadowStack___shadow__wire();
  
  void *___componentInstance = NULL;
  ___componentInstance = &awsIoTThingShadowInstances_thingShadowIOHandlerInst__instance;
  MultiPartitionAWSIoTThingShadowIOHandlerImpl_init(___componentInstance);
  ___componentInstance = &awsIoTThingShadowInstances_thingShadowStack___shadow__instance;
  ESP8266AWSIoTThingShadowStack___setup(___componentInstance);
}
