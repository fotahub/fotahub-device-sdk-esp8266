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
#ifndef ESPCONNCLIENTIMPL_H
#define ESPCONNCLIENTIMPL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include <espconn.h>
#include "ESPConnHelper.h"
#include "DNS.h"
#include "Socket.h"
#include "DatagramPool.h"
#include "DatagramHelper.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_SOCKET_HANDLER_COUNT 1

struct ESPConnClientImpl__cdata {
  /* 
   * fields
   */
  uint16 sessionBufferSize__field;
  /* 
   * fields
   */
  os_timer_t asyncSimulationTimer__field;
  /* 
   * Req port ops
   */
  IClientSocketHandler__idata_t *clientSocketHandlers__ops[MAX_SOCKET_HANDLER_COUNT];
  /* 
   * Req port ops
   */
  IDNSClient__idata_t *dnsClient__ops;
  /* 
   * Req port ops
   */
  IDatagramPool__idata_t *datagramPool__ops;
};
typedef struct ESPConnClientImpl__cdata ESPConnClientImpl__cdata_t;

const void* ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_connect(SocketConnectionParameters_t *pConnParams, void *pUserData, void *___id);

bool ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_isConnected(const void* hSession, void *___id);

void *ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_getUserData(const void* hSession, void *___id);

void ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_sendDatagram(const void* hSession, Datagram_t *pDatagram, SocketFrameOptions_t *pOptions, void *___id);

void ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_disconnect(const void* hSession, void *___id);

void ICACHE_FLASH_ATTR ESPConnClientImpl_internalConnect(const void* hSession, char const *hostName, uint32_t ipAddress, void *___id);

void ICACHE_FLASH_ATTR ESPConnClientImpl_dnsLookupHandler_hostNameResolved(char const *hostName, uint32_t ipAddress, void *pUserData, void *___id);

Datagram_t *ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_newDatagram(const void* hSession, size_t payloadLength, DatagramType_t type, void *___id);

Datagram_t *ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_resizeDatagram(const void* hSession, Datagram_t *pDatagram, size_t newSize, void *___id);

void ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_deleteDatagram(const void* hSession, Datagram_t *pDatagram, void *___id);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
