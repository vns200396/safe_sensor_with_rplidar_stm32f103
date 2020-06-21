/*
 * RoboPeak RPLIDAR Driver for Arduino
 * RoboPeak.com
 * 
 * Copyright (c) 2014, RoboPeak 
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY 
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES 
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef __RPLIDAR_H
#define __RPLIDAR_H

#pragma once


#include "rptypes.h"
#include "rplidar_cmd.h"

#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

#include "lidar_hardware_serial.h"
#include "SysTick.h"
#include "system.h"



#define MOTOR_GPIO_CLK 							 RCC_APB2Periph_GPIOA
#define MOTOR_GPIO_Pin 							 GPIO_Pin_7
#define MOTOR_GPIO_PORT							 GPIOA
#define MOTOR_CTRL									 PAout(7)



#define RPLIDAR_DEFAULT_TIMEOUT 		 500


typedef struct
{
    float distance;
    float angle;
    uint8_t quality;
    bool  startBit;
}RPLidarMeasurement;



typedef enum
{
	NO_ALERT,
	WARRING,
	DANGER
}FunctionalAlert;


void rplidar_gpio_init(void);
void start_motor_rplidar(void);
void stop_motor_rplidar(void);
float rplidar_get_distance(void);
float rplidar_get_angle(void);
uint8_t rplidar_get_quality(void);
bool rplidar_get_startBit(void);
void rplidar_begin(void);
void rplidar_end(void);
bool rplidar_isOpen(void);
u_result rplidar_getHealth(rplidar_response_device_health_t * healthinfo, uint32_t timeout);
u_result rplidar_getDeviceInfo(rplidar_response_device_info_t * info, uint32_t timeout );
u_result rplidar_stop(void);
u_result rplidar_startScan(bool force, uint32_t timeout);
u_result rplidar_waitPoint(uint32_t timeout);
u_result rplidar_sendCommand(uint8_t cmd, const void * payload, size_t payloadsize);
u_result rplidar_waitResponseHeader(rplidar_ans_header_t * header, uint32_t timeout);
u_result detect_lidar(void);
#endif
