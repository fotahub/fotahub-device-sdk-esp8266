#ifndef FOTAHUB_H
#define FOTAHUB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "FOTAUpdateDefinitions.h"
#include "ConnectionManagementDefinitions.h"

#ifdef __cplusplus
extern "C" {
#endif

enum NetworkAdapterStatus {
  NETWORK_ADAPTER_STATUS_DISCONNECTED,
  NETWORK_ADAPTER_STATUS_ERROR = 1,
  NETWORK_ADAPTER_STATUS_CONNECTED = 2
};
typedef enum NetworkAdapterStatus NetworkAdapterStatus_t;

void ICACHE_FLASH_ATTR fotahub_init(char const *productId, char const *productName, FOTAUpdateClientConfig_t const *pUpdateClientConfig, uint32_t rootCACertsAddress);

void ICACHE_FLASH_ATTR fotahub_run(void);

void ICACHE_FLASH_ATTR fotahub_notifyNetworkStatusChange(NetworkAdapterStatus_t status);

bool ICACHE_FLASH_ATTR fotahub_downloadFirmwareUpdate(FirmwareUpdateInfo_t *pUpdateInfo);

bool ICACHE_FLASH_ATTR fotahub_applyFirmwareUpdate(FirmwareUpdateInfo_t *pUpdateInfo);

bool ICACHE_FLASH_ATTR fotahub_confirmFirmwareUpdate(FirmwareUpdateInfo_t *pUpdateInfo);

bool ICACHE_FLASH_ATTR fotahub_rollBackFirmwareUpdate(FirmwareUpdateInfo_t *pUpdateInfo);

extern void ICACHE_FLASH_ATTR fotahub_onConnectionStatusChanged(ConnectionStatus_t status);

extern void ICACHE_FLASH_ATTR fotahub_onFirmwareUpdateStatusChanged(FOTAUpdateStatus_t status);

extern void ICACHE_FLASH_ATTR fotahub_onProvideFirmwareUpdateVerificationInfo(FirmwareUpdateInfo_t const *pUpdateInfo, FOTAUpdateVerificationAlgorithm_t *pVerificationAlgorithm, uint8_t const  **ppVerificationData);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
