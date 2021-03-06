#include "lidar_hardware_serial.h"



//static USART_CallbackFunction_t USART_Function;
static volatile uint16_t _rx_buffer_head;
static volatile uint16_t _rx_buffer_tail;
static uint8_t _rx_buffer[SERIAL_RX_BUFFER_SIZE];


/**
  * @brief  Serial port object constructor
  * @param  Serial peripheral address
  * @retval none
  */
//void HardwareSerial(void)
//{
//	USART_Function = 0;
//	_rx_buffer_head =	0;
//	_rx_buffer_tail = 0;
//}



void lidar_serial_begin(void)
{
  USART_InitTypeDef LidarSerial_Init;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(LIDAR_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);
 
  GPIO_InitStructure.GPIO_Pin = LIDAR_TX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LIDAR_GPIO_PORT, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = LIDAR_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LIDAR_GPIO_PORT, &GPIO_InitStructure);   


  /* USARTx configuration ----------------------------------------------------*/
  /* Enable USART clock */
	LIDAR_SERIAL_CLK_INIT(LIDAR_SERIAL_CLK, ENABLE);
	
	LidarSerial_Init.USART_BaudRate = BAURATE;
	LidarSerial_Init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	LidarSerial_Init.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	LidarSerial_Init.USART_Parity = USART_Parity_No;
	LidarSerial_Init.USART_StopBits = USART_StopBits_1;
	LidarSerial_Init.USART_WordLength = USART_WordLength_8b;
	USART_Init(LIDAR_SERIAL, &LidarSerial_Init);
	USART_Cmd(LIDAR_SERIAL, ENABLE);
	
    /* Enable the Tx buffer empty interrupt */
	USART_ITConfig(LIDAR_SERIAL, USART_IT_RXNE, ENABLE);
	USART_ClearITPendingBit(LIDAR_SERIAL, USART_IT_RXNE);;

  /* NVIC configuration */
  /* Configure the Priority Group to 1 bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = LIDAR_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = USART_PreemptionPriority_Default;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = USART_SubPriority_Default;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable USART */
  USART_Cmd(LIDAR_SERIAL, ENABLE);   
}

void lidar_serial_end(void)
{
  USART_Cmd(LIDAR_SERIAL, DISABLE);
}

//void lidar_serial_attachInterrupt(USART_CallbackFunction_t Function)
//{
//   USART_Function = Function;
//}


unsigned int lidar_serial_available(void)
{
  return ((unsigned int)(SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % SERIAL_RX_BUFFER_SIZE;
}

int lidar_serial_read(void)
{
	
  unsigned char c;
    // if the head isn't ahead of the tail, we don't have any characters
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
         c = _rx_buffer[_rx_buffer_tail];
        _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % SERIAL_RX_BUFFER_SIZE;
        return c;
    }
}


int lidar_serial_peek(void)
{
    if (_rx_buffer_head == _rx_buffer_tail)
    {
        return -1;
    }
    else
    {
        return _rx_buffer[_rx_buffer_tail];
    }
}

void lidar_serial_flush(void)
{
    _rx_buffer_head = _rx_buffer_tail;
}

size_t lidar_serial_write(uint8_t n)
{
		while (!USART_GetFlagStatus(LIDAR_SERIAL, USART_FLAG_TC)){};
		// Wait until transmit data register is empty
	  USART_SendData(LIDAR_SERIAL, n);
    return n;
}

void lidar_serial_write_string(char *s)
{
	while (*s)
	{
		lidar_serial_write(*s++);
	}
}

void lidar_serial_write_buff(uint8_t *s,uint16_t lenght)
{
	uint16_t i;
	for(i=0; i < lenght; i++)
	{
		lidar_serial_write(s[i]);
	}
}

void LIDAR_IRQHANDLER(void)
{
	uint8_t c;
	uint32_t i;
	
 	if(USART_GetITStatus(LIDAR_SERIAL, USART_IT_RXNE ) != RESET)
	{
			c = USART_ReceiveData(LIDAR_SERIAL);
			i = (uint32_t)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;
			if (i != _rx_buffer_tail)
			{
					_rx_buffer[_rx_buffer_head] = c;
					_rx_buffer_head = i;
			}

//			if(USART_Function)
//					USART_Function();

			USART_ClearITPendingBit(LIDAR_SERIAL, USART_IT_RXNE);
			USART_ClearFlag(LIDAR_SERIAL,USART_IT_RXNE);
	}
}
