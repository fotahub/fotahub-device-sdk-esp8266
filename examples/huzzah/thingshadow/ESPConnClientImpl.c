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
#include "ESPConnClientImpl.h"

#include <mem.h>
#include <spi_flash.h>
#include "SocketHelper.h"

enum ESPConnCallbackType {
  CONNECT,
  SENT,
  RECEIVED,
  DISCONNECTED,
  ERROR
};
typedef enum ESPConnCallbackType ESPConnCallbackType_t;

struct ESPConnReverseData {
  bool secure;
  void *pUserData;
  os_timer_t *pAsyncSimulationTimer;
  ESPConnCallbackType_t callbackType;
  IClientSocketHandler__idata_t **clientSocketHandlers;
};
typedef struct ESPConnReverseData ESPConnReverseData_t;

static void ICACHE_FLASH_ATTR asyncCallbackTimerHandler(void *arg);

static void ICACHE_FLASH_ATTR setAsyncCallbackTimer(void *arg, ESPConnCallbackType_t type);

static void ICACHE_FLASH_ATTR connectCallback(void *arg);

static void ICACHE_FLASH_ATTR sentCallback(void *arg);

static void ICACHE_FLASH_ATTR receiveCallback(void *arg, char *pData, uint16_t len);

static void ICACHE_FLASH_ATTR disconnectCallback(void *arg);

static void ICACHE_FLASH_ATTR errorCallback(void *arg, sint8 err);

static void ICACHE_FLASH_ATTR asyncCallbackTimerHandler(void *arg)
{
  struct espconn *pConn = ((struct espconn *)((arg)));
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  IClientSocketHandler__idata_t **clienSocketHandler = ((IClientSocketHandler__idata_t **)(pReverseData->clientSocketHandlers));
  
  switch (pReverseData->callbackType)
  {
    case CONNECT:
    {
      for ( uint8_t ___ic = 0 ; ___ic < MAX_SOCKET_HANDLER_COUNT; ___ic++ )
      {
        if (clienSocketHandler[___ic] != NULL) 
        {
          (*clienSocketHandler[___ic]->connected)(pConn, clienSocketHandler[___ic]->__instance);
        }
      }
      break;
    }
    case SENT:
    {
      for ( uint8_t ___ic = 0 ; ___ic < MAX_SOCKET_HANDLER_COUNT; ___ic++ )
      {
        if (clienSocketHandler[___ic] != NULL) 
        {
          (*clienSocketHandler[___ic]->datagramSent)(pConn, clienSocketHandler[___ic]->__instance);
        }
      }
      break;
    }
    case DISCONNECTED:
    {
      for ( uint8_t ___ic = 0 ; ___ic < MAX_SOCKET_HANDLER_COUNT; ___ic++ )
      {
        if (clienSocketHandler[___ic] != NULL) 
        {
          (*clienSocketHandler[___ic]->disconnected)(pConn, clienSocketHandler[___ic]->__instance);
        }
      }
      disposeESPConn(pConn);
      break;
    }
    default: {
    }
  }
}

static void ICACHE_FLASH_ATTR setAsyncCallbackTimer(void *arg, ESPConnCallbackType_t type)
{
  struct espconn *pConn = ((struct espconn *)((arg)));
  
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData != NULL) 
  {
    pReverseData->callbackType = type;
    os_timer_disarm(pReverseData->pAsyncSimulationTimer);
    os_timer_setfn(pReverseData->pAsyncSimulationTimer, &asyncCallbackTimerHandler, arg);
    os_timer_arm(pReverseData->pAsyncSimulationTimer, 10, false);
  }
}

static void ICACHE_FLASH_ATTR connectCallback(void *arg)
{
  if (arg == NULL) 
  {
    return;
  }
  setAsyncCallbackTimer(arg, CONNECT);
}

static void ICACHE_FLASH_ATTR sentCallback(void *arg)
{
  if (arg == NULL) 
  {
    return;
  }
  setAsyncCallbackTimer(arg, SENT);
}

static void ICACHE_FLASH_ATTR receiveCallback(void *arg, char *pData, uint16_t len)
{
  if (arg == NULL) 
  {
    return;
  }
  struct espconn *pConn = ((struct espconn *)((arg)));
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData != NULL) 
  {
    Datagram_t datagram;
    initDatagram(&datagram, pData, len);
    IClientSocketHandler__idata_t **clientSocketHandler = ((IClientSocketHandler__idata_t **)(pReverseData->clientSocketHandlers));
    for ( uint8_t ___ic = 0 ; ___ic < MAX_SOCKET_HANDLER_COUNT; ___ic++ )
    {
      if (clientSocketHandler[___ic] != NULL) 
      {
        (*clientSocketHandler[___ic]->datagramReceived)(pConn, &datagram, clientSocketHandler[___ic]->__instance);
      }
    }
  }
}

static void ICACHE_FLASH_ATTR disconnectCallback(void *arg)
{
  if (arg == NULL) 
  {
    return;
  }
  setAsyncCallbackTimer(arg, DISCONNECTED);
}

static void ICACHE_FLASH_ATTR errorCallback(void *arg, sint8 err)
{
  if (arg == NULL) 
  {
    return;
  }
  struct espconn *pConn = ((struct espconn *)((arg)));
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData != NULL) 
  {
    IClientSocketHandler__idata_t **clientSocketHandler = ((IClientSocketHandler__idata_t **)(pReverseData->clientSocketHandlers));
    for ( uint8_t ___ic = 0 ; ___ic < MAX_SOCKET_HANDLER_COUNT; ___ic++ )
    {
      if (clientSocketHandler[___ic] != NULL) 
      {
        (*clientSocketHandler[___ic]->connectionError)(pConn, espConnToSocketError(err), clientSocketHandler[___ic]->__instance);
      }
    }
  }
  
  disposeESPConn(pConn);
}

const void* ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_connect(SocketConnectionParameters_t *pConnParams, void *pUserData, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  if (pConnParams == NULL) 
  {
    return NULL;
  }
  
  struct espconn *pConn = createESPConn(ESPCONN_TCP, ((uint32_t) 0u), pConnParams->port, sizeof(ESPConnReverseData_t));
  if (pConn == NULL) 
  {
    return NULL;
  }
  
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  pReverseData->secure = pConnParams->pSecureConnectionParams != NULL;
  pReverseData->pUserData = pUserData;
  pReverseData->pAsyncSimulationTimer = &___cid->asyncSimulationTimer__field;
  if (___cid->clientSocketHandlers__ops != NULL) 
  {
    pReverseData->clientSocketHandlers = ___cid->clientSocketHandlers__ops;
  }
  
  int8_t status = espconn_regist_connectcb(pConn, &connectCallback);
  if (status != 0) 
  {
    os_printf("espconn callack registration failed, error code (errorCode: %d)\n", status);
    disposeESPConn(pConn);
    return NULL;
  }
  status = espconn_regist_disconcb(pConn, &disconnectCallback);
  if (status != 0) 
  {
    os_printf("espconn callack registration failed, error code (errorCode: %d)\n", status);
    disposeESPConn(pConn);
    return NULL;
  }
  /* 
   * must bind with error callback, the api has name reconcb but in SDK it is responsable to handle errors.
   */
  status = espconn_regist_reconcb(pConn, &errorCallback);
  if (status != 0) 
  {
    os_printf("espconn callack registration failed, error code (errorCode: %d)\n", status);
    disposeESPConn(pConn);
    return NULL;
  }
  
  status = espconn_regist_sentcb(pConn, &sentCallback);
  if (status != 0) 
  {
    os_printf("espconn callack registration failed, error code (errorCode: %d)\n", status);
    disposeESPConn(pConn);
    return NULL;
  }
  
  status = espconn_regist_recvcb(pConn, &receiveCallback);
  if (status != 0) 
  {
    os_printf("espconn callack registration failed, error code (errorCode: %d)\n", status);
    disposeESPConn(pConn);
    return NULL;
  }
  
  if (pConnParams->pSecureConnectionParams != NULL) 
  {
    if (pConnParams->pSecureConnectionParams->authenticateServer) 
    {
      if (!espconn_secure_ca_enable(ESPCONN_CLIENT, pConnParams->pSecureConnectionParams->rootCACertsAddress)) 
      {
        disposeESPConn(pConn);
        return NULL;
      }
    }
    else
    {
      espconn_secure_ca_disable(ESPCONN_CLIENT);
    }
    if (pConnParams->pSecureConnectionParams->clientCertAddress != 0) 
    {
      if (!espconn_secure_cert_req_enable(ESPCONN_CLIENT, pConnParams->pSecureConnectionParams->clientCertAddress)) 
      {
        disposeESPConn(pConn);
        return NULL;
      }
    }
    else
    {
      if (!espconn_secure_cert_req_disable(ESPCONN_CLIENT)) 
      {
        disposeESPConn(pConn);
        return NULL;
      }
    }
    if (!espconn_secure_set_buffer_size(ESPCONN_CLIENT, ___cid->sessionBufferSize__field)) 
    {
      os_printf("espconn_secure_set_size() failed\n");
      disposeESPConn(pConn);
      return NULL;
    }
    if (!espconn_secure_set_max_fragment_length(ESPCONN_CLIENT, pConnParams->pSecureConnectionParams->maxFragmentLength)) 
    {
      os_printf("espconn_secure_set_max_fragment_length() failed\n");
      disposeESPConn(pConn);
      return NULL;
    }
    if (!espconn_secure_set_max_data_rate(ESPCONN_CLIENT, pConnParams->pSecureConnectionParams->maxDataRate)) 
    {
      os_printf("espconn_secure_set_max_data_rate() failed\n");
      disposeESPConn(pConn);
      return NULL;
    }
  }
  if (pConnParams->pAddr->type == ENDPOINT_ADDRESS_TYPE_HOST_NAME) 
  {
    if (___cid->dnsClient__ops != NULL) 
    {
      if (!(*___cid->dnsClient__ops->resolveHostName)(((HostNameEndpointAddress_t *)(pConnParams->pAddr))->hostName, pConn, ___cid->dnsClient__ops->__instance)) 
      {
        os_printf("Unable to resolve host name:%s\n", ((HostNameEndpointAddress_t *)(pConnParams->pAddr))->hostName);
        disposeESPConn(pConn);
        return NULL;
      }
      return pConn;
    }
    os_printf("DNS Client must be connected to solve hostName\n");
    return NULL;
  }
  else if (pConnParams->pAddr->type == ENDPOINT_ADDRESS_TYPE_IPV4_ADDRESS) {
    
    ESPConnClientImpl_internalConnect(pConn, NULL, ((IPv4EndpointAddress_t *)(pConnParams->pAddr))->ipAddress, ___cid);
    return pConn;
  }
  return NULL;
}

bool ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_isConnected(const void* hSession, void *___id)
{
  if (hSession == NULL) 
  {
    os_printf("Session handle must not be null\n");
    return false;
  }
  struct espconn *pConn = ((struct espconn *) hSession);
  if (pConn->type == ESPCONN_TCP) 
  {
    return pConn->state != ESPCONN_NONE && pConn->state != ESPCONN_WAIT && pConn->state != ESPCONN_CLOSE;
  }
  else if (pConn->type == ESPCONN_UDP) {
    /* 
     * Sockets using connnectionless UDP protocol are implicitly always "connected"
     */
    return true;
  }
  return false;
}

void *ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_getUserData(const void* hSession, void *___id)
{
  if (hSession == NULL) 
  {
    os_printf("Session handle must not be null\n");
    return NULL;
  }
  
  struct espconn *pConn = ((struct espconn *) hSession);
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData != NULL) 
  {
    return pReverseData->pUserData;
  }
  return NULL;
}

void ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_sendDatagram(const void* hSession, Datagram_t *pDatagram, SocketFrameOptions_t *pOptions, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  if (hSession == NULL) 
  {
    os_printf("Session handle must not be null\n");
    (*___cid->datagramPool__ops->deleteDatagram)(pDatagram, ___cid->datagramPool__ops->__instance);
    return;
  }
  struct espconn *pConn = ((struct espconn *) hSession);
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData->secure) 
  {
    int8_t status = espconn_secure_send(pConn, pDatagram->pVisiblePayload, ((uint16_t)(pDatagram->visiblePayloadLength)));
    if (status != 0) 
    {
      for ( uint8_t ___pc = 0 ; ___pc < MAX_SOCKET_HANDLER_COUNT; ___pc++ )
      {
        if (___cid->clientSocketHandlers__ops[___pc] != NULL && ___cid->clientSocketHandlers__ops[___pc]->__instance != NULL) 
        {
          (*___cid->clientSocketHandlers__ops[___pc]->connectionError)(pConn, espConnToSocketError(status), ___cid->clientSocketHandlers__ops[___pc]->__instance);
        }
      }
      disposeESPConn(pConn);
    }
    
  }
  else
  {
    int8_t status = espconn_send(pConn, pDatagram->pVisiblePayload, ((uint16_t)(pDatagram->visiblePayloadLength)));
    if (status != 0) 
    {
      for ( uint8_t ___pc = 0 ; ___pc < MAX_SOCKET_HANDLER_COUNT; ___pc++ )
      {
        if (___cid->clientSocketHandlers__ops[___pc] != NULL && ___cid->clientSocketHandlers__ops[___pc]->__instance != NULL) 
        {
          (*___cid->clientSocketHandlers__ops[___pc]->connectionError)(pConn, espConnToSocketError(status), ___cid->clientSocketHandlers__ops[___pc]->__instance);
        }
      }
      disposeESPConn(pConn);
    }
  }
  
  /* 
   * TODO Store send datagram in ESPConnReverseData and perform subsequent step in runnable invoked from sent callback rather than right here
   * TODO Raise appropriate (overrun) error in case that there already is another send datagram present in ESPConnReverseDatannection
   */
  (*___cid->datagramPool__ops->deleteDatagram)(pDatagram, ___cid->datagramPool__ops->__instance);
}

void ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_disconnect(const void* hSession, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  if (hSession == NULL) 
  {
    os_printf("Session handle must not be null\n");
    return;
  }
  struct espconn *pConn = ((struct espconn *) hSession);
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData->secure) 
  {
    int8_t status = espconn_secure_disconnect(pConn);
    if (status != 0) 
    {
      for ( uint8_t ___pc = 0 ; ___pc < MAX_SOCKET_HANDLER_COUNT; ___pc++ )
      {
        if (___cid->clientSocketHandlers__ops[___pc] != NULL && ___cid->clientSocketHandlers__ops[___pc]->__instance != NULL) 
        {
          (*___cid->clientSocketHandlers__ops[___pc]->connectionError)(pConn, espConnToSocketError(status), ___cid->clientSocketHandlers__ops[___pc]->__instance);
        }
      }
      disposeESPConn(pConn);
    }
  }
  else
  {
    int8_t status = espconn_disconnect(pConn);
    if (status != 0) 
    {
      for ( uint8_t ___pc = 0 ; ___pc < MAX_SOCKET_HANDLER_COUNT; ___pc++ )
      {
        if (___cid->clientSocketHandlers__ops[___pc] != NULL && ___cid->clientSocketHandlers__ops[___pc]->__instance != NULL) 
        {
          (*___cid->clientSocketHandlers__ops[___pc]->connectionError)(pConn, espConnToSocketError(status), ___cid->clientSocketHandlers__ops[___pc]->__instance);
        }
      }
      disposeESPConn(pConn);
    }
  }
}

void ICACHE_FLASH_ATTR ESPConnClientImpl_internalConnect(const void* hSession, char const *hostName, uint32_t ipAddress, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  struct espconn *pConn = ((struct espconn *) hSession);
  setESPConnRemoteIP(pConn, ipAddress);
  ESPConnReverseData_t *pReverseData = ((ESPConnReverseData_t *)(pConn->reverse));
  if (pReverseData->secure) 
  {
    sint8 status = espconn_secure_connect(pConn, hostName);
    if (status != 0) 
    {
      for ( uint8_t ___pc = 0 ; ___pc < MAX_SOCKET_HANDLER_COUNT; ___pc++ )
      {
        if (___cid->clientSocketHandlers__ops[___pc] != NULL && ___cid->clientSocketHandlers__ops[___pc]->__instance != NULL) 
        {
          (*___cid->clientSocketHandlers__ops[___pc]->connectionError)(pConn, espConnToSocketError(status), ___cid->clientSocketHandlers__ops[___pc]->__instance);
        }
      }
      disposeESPConn(pConn);
      return;
    }
  }
  else
  {
    int8_t status = espconn_connect(pConn);
    if (status != 0) 
    {
      for ( uint8_t ___pc = 0 ; ___pc < MAX_SOCKET_HANDLER_COUNT; ___pc++ )
      {
        if (___cid->clientSocketHandlers__ops[___pc] != NULL && ___cid->clientSocketHandlers__ops[___pc]->__instance != NULL) 
        {
          (*___cid->clientSocketHandlers__ops[___pc]->connectionError)(pConn, espConnToSocketError(status), ___cid->clientSocketHandlers__ops[___pc]->__instance);
        }
      }
      disposeESPConn(pConn);
      return;
    }
  }
}

void ICACHE_FLASH_ATTR ESPConnClientImpl_dnsLookupHandler_hostNameResolved(char const *hostName, uint32_t ipAddress, void *pUserData, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  struct espconn *pConn = ((struct espconn *) pUserData);
  if (ipAddress == 0u) 
  {
    /* 
     * TODO Implement helper function extracting host name from request datagram and log host name
     */
    /* 
     * Reuse existing error callback to delegate error to handlers.
     */
    errorCallback(pConn, ((int8_t)(SOCKET_ERROR_NO_ROUTE_TO_HOST)));
    return;
  }
  ESPConnClientImpl_internalConnect(pConn, hostName, ipAddress, ___cid);
}

Datagram_t *ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_newDatagram(const void* hSession, size_t payloadLength, DatagramType_t type, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  return (*___cid->datagramPool__ops->newDatagram)(payloadLength, ___cid->datagramPool__ops->__instance);
}

Datagram_t *ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_resizeDatagram(const void* hSession, Datagram_t *pDatagram, size_t newSize, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  return (*___cid->datagramPool__ops->resizeDatagram)(pDatagram, newSize, ___cid->datagramPool__ops->__instance);
}

void ICACHE_FLASH_ATTR ESPConnClientImpl_clientSocket_deleteDatagram(const void* hSession, Datagram_t *pDatagram, void *___id)
{
  ESPConnClientImpl__cdata_t *___cid = ((ESPConnClientImpl__cdata_t *) ___id);
  (*___cid->datagramPool__ops->deleteDatagram)(pDatagram, ___cid->datagramPool__ops->__instance);
}
