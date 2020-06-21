#include "usart.h"



///* USER CODE BEGIN PFP */
///* Private function prototypes -----------------------------------------------*/
//struct __FILE
//{
//  int handle;
//  /* Whatever you require here. If the only file you are using is */
//  /* standard output using printf() for debugging, no file handling */
//  /* is required. */
//};


///*send text over SWV*/
//int fputc(int ch, FILE *f) {
//    ITM_SendChar(ch);//send method for SWV
//    return(ch);
//}

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

void USART_NVIC_Config(void);

/*******************************************************************************
* Function Name  : USART_Configuration
* Description    : Configure Open_USART 
* Input          : None
* Output         : None
* Return         : None
* Attention		 : None
*******************************************************************************/
void USART_Configuration(void)
{ 												
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure; 

  RCC_APB2PeriphClockCmd(USART_GPIO_CLK,ENABLE);



 /*
  *  Open_USART1_TX -> PA9 , Open_USART1_RX -PA10
  */

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);    
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);   
	
/*
   		 USARTx configured as follow:
         - BaudRate = 115200 baud  
		 - Word Length = 8 Bits
         - One Stop Bit
         - No parity
         - Hardware flow control disabled (RTS and CTS signals)
         - Receive and transmit    
 */
  RCC_APB2PeriphClockCmd(USART_CLKx,ENABLE);

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTx, &USART_InitStructure);
  /* Enable the Open_USART Transmit interrupt: this interrupt is generated when the 
     Open_USART transmit data register is empty */
  USART_ITConfig(USARTx,USART_IT_RXNE,ENABLE);

  USART_Cmd(USARTx, ENABLE);
  USART_NVIC_Config();

}

void USART_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/* Use no semihosting */
#if 0
#pragma import(__use_no_semihosting)
struct __FILE
{  
	int handle;
};
FILE __stdout;

_sys_exit(int x)
{
	x = x;
}
#endif

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
//  /* Place your implementation of fputc here */
//  /* e.g. write a character to the USART */
//  USART_SendData(USARTx, (uint8_t) ch);

//  /* Loop until the end of transmission */
//  while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
//  {}
    ITM_SendChar(ch);//send method for SWV
  return ch;
}
