#ifndef __LIDAR_HARDWARESERIAL_H
#define __LIDAR_HARDWARESERIAL_H

#include "stm32f10x.h"
#include "stdio.h"

#define SERIAL_RX_BUFFER_SIZE 128
#define SERIAL_Config_Default SERIAL_8N1
#define USART_PreemptionPriority_Default 1
#define USART_SubPriority_Default 3

typedef uint16_t rx_buffer_index_t;
typedef void(*USART_CallbackFunction_t)(void);

typedef enum {
    SERIAL_8N1 = USART_WordLength_8b | USART_Parity_No | (USART_StopBits_1 >> 8),
    SERIAL_8N2 = USART_WordLength_8b | USART_Parity_No | (USART_StopBits_2 >> 8),
    SERIAL_8E1 = USART_WordLength_8b | USART_Parity_Even | (USART_StopBits_1 >> 8),
    SERIAL_8E2 = USART_WordLength_8b | USART_Parity_Even | (USART_StopBits_2 >> 8),
    SERIAL_8O1 = USART_WordLength_8b | USART_Parity_Odd | (USART_StopBits_1 >> 8),
    SERIAL_8O2 = USART_WordLength_8b | USART_Parity_Odd | (USART_StopBits_2 >> 8),
    SERIAL_8N0_5 = USART_WordLength_8b | USART_Parity_No | (USART_StopBits_0_5 >> 8),
    SERIAL_8N1_5 = USART_WordLength_8b | USART_Parity_No | (USART_StopBits_1_5 >> 8),
    SERIAL_8E0_5 = USART_WordLength_8b | USART_Parity_Even | (USART_StopBits_0_5 >> 8),
    SERIAL_8E1_5 = USART_WordLength_8b | USART_Parity_Even | (USART_StopBits_1_5 >> 8),
    SERIAL_8O0_5 = USART_WordLength_8b | USART_Parity_Odd | (USART_StopBits_0_5 >> 8),
    SERIAL_8O1_5 = USART_WordLength_8b | USART_Parity_Odd | (USART_StopBits_1_5 >> 8),

    SERIAL_9N1 = USART_WordLength_9b | USART_Parity_No | (USART_StopBits_1 >> 8),
    SERIAL_9N2 = USART_WordLength_9b | USART_Parity_No | (USART_StopBits_2 >> 8),
    SERIAL_9E1 = USART_WordLength_9b | USART_Parity_Even | (USART_StopBits_1 >> 8),
    SERIAL_9E2 = USART_WordLength_9b | USART_Parity_Even | (USART_StopBits_2 >> 8),
    SERIAL_9O1 = USART_WordLength_9b | USART_Parity_Odd | (USART_StopBits_1 >> 8),
    SERIAL_9O2 = USART_WordLength_9b | USART_Parity_Odd | (USART_StopBits_2 >> 8),
    SERIAL_9N0_5 = USART_WordLength_9b | USART_Parity_No | (USART_StopBits_0_5 >> 8),
    SERIAL_9N1_5 = USART_WordLength_9b | USART_Parity_No | (USART_StopBits_1_5 >> 8),
    SERIAL_9E0_5 = USART_WordLength_9b | USART_Parity_Even | (USART_StopBits_0_5 >> 8),
    SERIAL_9E1_5 = USART_WordLength_9b | USART_Parity_Even | (USART_StopBits_1_5 >> 8),
    SERIAL_9O0_5 = USART_WordLength_9b | USART_Parity_Odd | (USART_StopBits_0_5 >> 8),
    SERIAL_9O1_5 = USART_WordLength_9b | USART_Parity_Odd | (USART_StopBits_1_5 >> 8),
} SERIAL_Config;

#define BAURATE														115200
#define Get_USART_WordLength_x(SERIAL_x) 	((uint16_t)(SERIAL_x&0xF000))
#define Get_USART_Parity_x(SERIAL_x) 			((uint16_t)(SERIAL_x&0x0F00))
#define Get_USART_StopBits_x(SERIAL_x) 		((uint16_t)((SERIAL_x&0x00F0)<<8))


#define LIDAR_SERIAL                 USART1
#define LIDAR_SERIAL_CLK	           RCC_APB2Periph_USART1
#define LIDAR_SERIAL_CLK_INIT				 RCC_APB2PeriphClockCmd

#define LIDAR_TX_PIN                 GPIO_Pin_9
#define LIDAR_RX_PIN                 GPIO_Pin_10
#define	LIDAR_GPIO_PORT           	 GPIOA
#define LIDAR_GPIO_CLK            	 RCC_APB2Periph_GPIOA


#define LIDAR_IRQn                   USART1_IRQn
#define LIDAR_IRQHANDLER  				   USART1_IRQHandler



//void HardwareSerial(void);
void lidar_serial_begin(void);
void lidar_serial_end(void);
void lidar_serial_attachInterrupt(USART_CallbackFunction_t Function);
unsigned int lidar_serial_available(void);
int lidar_serial_read(void);
int lidar_serial_peek(void);
void lidar_serial_flush(void);
size_t lidar_serial_write(uint8_t n);
void lidar_serial_write_string(char *s);
void lidar_serial_write_buff(uint8_t *s,uint16_t lenght);

#endif
