/*
 * timer.h
 *
 *  Created on: 2020-12-17
 *      Author: Rick
 */

/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */
#include<KF8A200GQS.h>
#include "includes.h"
#ifndef _TIMER_H_
#define _TIMER_H_

typedef struct Timer {
	uint64_t timeout;
	uint64_t repeat;
    void (*timeout_cb)(void);
    struct Timer* next;
}Timer;

#ifdef __cplusplus
extern "C" {
#endif

void timer_init(struct Timer* handle, void(*timeout_cb)(), uint64_t timeout, uint64_t repeat);
int  timer_start(struct Timer* handle);
void timer_stop(struct Timer* handle);
void timer_ticks(void);
void timer_loop(void);

#ifdef __cplusplus
}
#endif

#endif
