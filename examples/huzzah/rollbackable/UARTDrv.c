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
#include "UARTDrv.h"

#include "MultiPartitionDemoFirmwareUpdateInfoSerialReader.h"
#include <user_interface.h>
#include <ets_sys.h>

static void ICACHE_FLASH_ATTR uart_recvTask(os_event_t *pEvent);

static uint8_t uartUnit;

void ICACHE_FLASH_ATTR one_uart_init(uint8_t unit, UartBautRate baudrate)
{
  uartUnit = unit;
  system_os_task(&uart_recvTask, uart_recvTaskPrio, uart_recvTaskQueue, uart_recvTaskQueueLen);
  
  UartDev.baut_rate = baudrate;
  uart_config(unit);
  
  ETS_UART_INTR_ENABLE();
}

static void ICACHE_FLASH_ATTR uart_recvTask(os_event_t *pEvent)
{
  if (pEvent->sig == uart_recvTaskSignal) 
  {
    /* 
     * Determine lenght of available data in the UART unit's RX FIFO
     */
    uint32_t uartStatus = READ_PERI_REG(UART_STATUS(uartUnit));
    uint8_t rxFIFOLength = UART_RXFIFO_DATA_LEN(uartStatus);
    
    /* 
     * Signal received data to upstream receive handler
     */
    for ( int16_t __i = 0 ; __i < rxFIFOLength; __i++ )
    {
      uint32_t uartFifo = READ_PERI_REG(UART_FIFO(uartUnit));
      uint8_t rxChar = UART_RXFIFO_DATA(uartFifo);
      firmwareUpdateInfoReader_onCharacterReceived(rxChar);
    }
    
    /* 
     * Clear RX FIFO full and RX FIFO timeout interrupts that may have been arriving
     * while system_os_post-ed invocation of this runnable was underway but have been
     * handled by fully reading out RX FIFO right here
     */
    WRITE_PERI_REG(UART_INT_CLR(uartUnit), UART_RXFIFO_FULL_INT_CLR | UART_RXFIFO_TOUT_INT_CLR);
    
    /* 
     * Re-enable RX interrupt requests
     */
    uart_rx_intr_enable(uartUnit);
  }
}
