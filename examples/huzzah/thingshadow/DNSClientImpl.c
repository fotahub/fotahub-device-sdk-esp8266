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
#include "DNSClientImpl.h"

#include <espconn.h>
#include <ip_addr.h>
#include <mem.h>

struct DNSLookupData {
  void *pUserData;
  IDNSLookupHandler__idata_t *dnsLookupHandler;
};
typedef struct DNSLookupData DNSLookupData_t;

static void ICACHE_FLASH_ATTR dnsFoundCallback(char const *hostName, ip_addr_t *ipaddr, void *arg);

static void ICACHE_FLASH_ATTR dnsFoundCallback(char const *hostName, ip_addr_t *ipaddr, void *arg)
{
  if (arg == NULL) 
  {
    return;
  }
  
  DNSLookupData_t *pLookupData = ((DNSLookupData_t *) arg);
  if (pLookupData->dnsLookupHandler != NULL) 
  {
    /* 
     * TODO Return IPADDR_NONE in case that ipaddr is NULL
     */
    uint32_t ipAddress = (ipaddr != NULL) ? (ipaddr->addr) : (IPADDR_ANY);
    (*pLookupData->dnsLookupHandler->hostNameResolved)(hostName, ipAddress, pLookupData->pUserData, pLookupData->dnsLookupHandler->__instance);
  }
  
  os_free(pLookupData);
}

bool ICACHE_FLASH_ATTR DNSClientImpl_dnsClient_resolveHostName(char const *hostName, void *pUserData, void *___id)
{
  DNSClientImpl__cdata_t *___cid = ((DNSClientImpl__cdata_t *) ___id);
  /* 
   * Handle cases where host name contains a stringified IP address
   */
  uint32_t parsedIPAddress = ipaddr_addr(hostName);
  if (parsedIPAddress != IPADDR_NONE) 
  {
    (*___cid->dnsLookupHandler__ops->hostNameResolved)(hostName, parsedIPAddress, pUserData, ___cid->dnsLookupHandler__ops->__instance);
    return true;
  }
  
  /* 
   * Engage actual host name resolution procedure
   * espconn is bigger than DNSLookupData, it's not safe to cast DNSLookupData to espconn
   */
  DNSLookupData_t *pLookupData = ((DNSLookupData_t *)(os_malloc(sizeof(struct espconn))));
  if (pLookupData == NULL) 
  {
    return false;
  }
  pLookupData->pUserData = pUserData;
  pLookupData->dnsLookupHandler = ___cid->dnsLookupHandler__ops;
  
  ip_addr_t resolvedIPAddress;
  err_t status = espconn_gethostbyname(((struct espconn *)(pLookupData)), hostName, &resolvedIPAddress, &dnsFoundCallback);
  if (status == ESPCONN_OK) 
  {
    (*___cid->dnsLookupHandler__ops->hostNameResolved)(hostName, resolvedIPAddress.addr, pUserData, ___cid->dnsLookupHandler__ops->__instance);
    os_free(pLookupData);
    return true;
  }
  else if (status == ESPCONN_INPROGRESS) {
    return true;
  }
  else if (status == ESPCONN_ARG) {
    os_printf("Invalid host name (hostName: %s)\n", hostName);
    os_free(pLookupData);
    return false;
  }
  else
  {
    os_printf("espconn_gethostbyname() failed, error code (errorCode: %d)\n", status);
    os_free(pLookupData);
    return false;
  }
}
