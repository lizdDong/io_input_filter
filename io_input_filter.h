/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-04     lizd       the first version
 */
#ifndef _IO_INPUT_FILTER_H_
#define _IO_INPUT_FILTER_H_

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"


void iif_init(void);
int iif_add_pin(rt_base_t pin);
int iif_read_pin(rt_base_t pin);

#endif /* PACKAGES_IO_INPUT_FILTER_H_ */
