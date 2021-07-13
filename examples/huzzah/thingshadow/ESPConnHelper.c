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
#include "ESPConnHelper.h"

#include <mem.h>
#include <stdio.h>

struct espconn *ICACHE_FLASH_ATTR createESPConn(enum espconn_type connectionType, uint32_t ipAddr, uint16_t port, size_t reverseDataSize)
{
  /* 
   * Allocate new connection descriptor
   */
  struct espconn *pConn = ((struct espconn *)((os_malloc(sizeof(struct espconn)))));
  if (pConn == NULL) 
  {
    os_printf("Out of memory\n");
    return NULL;
  }
  /* 
   * Perform basic initialization
   */
  pConn->type = connectionType;
  pConn->state = ESPCONN_NONE;
  /* 
   * Allocate and initialize protocol data
   */
  if (connectionType == ESPCONN_TCP) 
  {
    esp_tcp *pTCP = ((esp_tcp *)((os_malloc(sizeof(esp_tcp)))));
    if (pTCP == NULL) 
    {
      os_printf("Out of memory\n");
      disposeESPConn(pConn);
      return NULL;
    }
    pConn->proto.tcp = pTCP;
    
    pTCP->local_port = ((int32_t)((espconn_port())));
    os_memcpy(pTCP->remote_ip, &ipAddr, 4);
    pTCP->remote_port = port;
  }
  else if (connectionType == ESPCONN_UDP) {
    esp_udp *pUDP = ((esp_udp *)((os_malloc(sizeof(esp_udp)))));
    if (pUDP == NULL) 
    {
      os_printf("Out of memory\n");
      disposeESPConn(pConn);
      return NULL;
    }
    pConn->proto.udp = pUDP;
    
    pUDP->local_port = ((int32_t)((espconn_port())));
    os_memcpy(pUDP->remote_ip, &ipAddr, 4);
    pUDP->remote_port = port;
  }
  /* 
   * Allocate reverse data
   */
  void *pReverseData = ((void *)(os_malloc(reverseDataSize)));
  if (pReverseData == NULL) 
  {
    os_printf("Out of memory\n");
    disposeESPConn(pConn);
    return NULL;
  }
  pConn->reverse = pReverseData;
  
  return pConn;
}

void ICACHE_FLASH_ATTR setESPConnRemoteIP(struct espconn *espconn, uint32_t ipAddr)
{
  if (espconn->proto.tcp != NULL) 
  {
    os_memcpy(espconn->proto.tcp->remote_ip, &ipAddr, 4);
    return;
  }
  if (espconn->proto.udp != NULL) 
  {
    os_memcpy(espconn->proto.udp->remote_ip, &ipAddr, 4);
    return;
  }
}

void ICACHE_FLASH_ATTR disposeESPConn(struct espconn *pConn)
{
  if (pConn == NULL) 
  {
    return;
  }
  /* 
   * Delete protocol data
   */
  if (pConn->type == ESPCONN_TCP) 
  {
    if (pConn->proto.tcp != NULL) 
    {
      os_free(pConn->proto.tcp);
    }
  }
  else if (pConn->type == ESPCONN_UDP) {
    if (pConn->proto.udp != NULL) 
    {
      os_free(pConn->proto.udp);
    }
  }
  /* 
   * Free reverse data
   */
  if (pConn->reverse != NULL) 
  {
    os_free(pConn->reverse);
  }
  /* 
   * Delete connection
   */
  espconn_delete(pConn);
  /* 
   * Free connection descriptor
   */
  os_free(pConn);
}

SocketError_t ICACHE_FLASH_ATTR espConnToSocketError(int8_t errorCode)
{
  switch (((int16_t) errorCode))
  {
    case ESPCONN_MEM:
    {
      return SOCKET_ERROR_OUT_OF_MEMORY;
    }
    case ESPCONN_TIMEOUT:
    {
      return SOCKET_ERROR_CONNECTION_TIMED_OUT;
    }
    case ESPCONN_RTE:
    {
      return SOCKET_ERROR_NO_ROUTE_TO_HOST;
    }
    case ESPCONN_INPROGRESS:
    {
      return SOCKET_ERROR_OPERATION_NOW_IN_PROGRESS;
    }
    case ESPCONN_MAXNUM:
    {
      return SOCKET_ERROR_TOO_MANY_CONNECTIONS;
    }
    case ESPCONN_ABRT:
    {
      return SOCKET_ERROR_SOFTWARE_CAUSED_CONNECTION_ABORT;
    }
    case ESPCONN_RST:
    {
      return SOCKET_ERROR_CONNECTION_RESET_BY_PEER;
    }
    case ESPCONN_CLSD:
    {
      return SOCKET_ERROR_CONNECTION_CLOSED;
    }
    case ESPCONN_CONN:
    {
      return SOCKET_ERROR_TRANSPORT_ENDPOINT_UNAVAILABLE;
    }
    case ESPCONN_ARG:
    {
      return SOCKET_ERROR_INVALID_ARGUMENT;
    }
    case ESPCONN_IF:
    {
      return SOCKET_ERROR_NETWORK_INTERFACE;
    }
    case ESPCONN_ISCONN:
    {
      return SOCKET_ERROR_TRANSPORT_ENDPOINT_ALREADY_CONNECTED;
    }
    case ESPCONN_TIME:
    {
      return SOCKET_ERROR_TIME;
    }
    case ESPCONN_NODATA:
    {
      return SOCKET_ERROR_NODATA;
    }
    case ESPCONN_HANDSHAKE:
    {
      return SOCKET_ERROR_CONNECTION_HANDSHAKE;
    }
    case ESPCONN_RESP_TIMEOUT:
    {
      return SOCKET_ERROR_RESPONSE_TIMED_OUT;
    }
    case ESPCONN_SSL_INVALID_DATA:
    {
      return SOCKET_ERROR_SECURITY;
    }
    default: {
      os_printf("Internal espconn error: %d\n", errorCode);
      return SOCKET_ERROR_UNKNOWN;
    }
  }
}
