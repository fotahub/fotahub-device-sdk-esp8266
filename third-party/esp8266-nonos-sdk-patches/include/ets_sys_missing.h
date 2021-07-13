/*
 *  ets_sys_missing.h
 *
 *  Function prototypes, data types, etc. that are missing in Espressif SDK headers.
 *
 *  Created on: 26 mai 2016
 *      Author: steph
 */

#ifndef INCLUDE_ETS_SYS_MISSING_H_
#define INCLUDE_ETS_SYS_MISSING_H_

#include <stdarg.h>

void ets_wdt_enable(void);
void ets_wdt_disable(void);

void ets_putc(char c);

int ets_vprintf(const char *format, va_list arg);
int ets_vsprintf(char *str, const char *format, va_list arg);
int ets_vsnprintf(char *str, size_t n, const char *format, va_list arg);

int ets_str2macaddr(void *, void *);
void ets_update_cpu_frequency(int freqmhz);

bool ets_post(uint8_t prio, ETSSignal sig, uint32_t par);
bool ets_task(ETSTask task, uint8_t prio, ETSEvent *queue, uint8_t qlen);

#endif /* INCLUDE_ETS_SYS_MISSING_H_ */
