#ifndef _USART_H
#define _USART_H

#include <stdio.h>
#include "stm32f10x.h"

/**
 * @brief  connected to USART2
 */ 
#define USARTx                   		 USART1
#define USART_CLKx                   RCC_APB2Periph_USART1

#define USART_TX_PIN                 GPIO_Pin_9
#define USART_RX_PIN                 GPIO_Pin_10
#define USART_GPIO_PORT           	 GPIOA
#define USART_GPIO_CLK            	 RCC_APB2Periph_GPIOA

#define USART_TX_SOURCE              GPIO_PinSource2


#define USARTx_IRQn                  USART1_IRQn


void USART_Configuration(void);
void USART_NVIC_Config(void);

#endif /*_USART_H*/
