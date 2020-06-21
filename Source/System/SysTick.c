#include "SysTick.h"


static __IO uint64_t TimingDelay=0;



void SysTick_Init(void)
{
  if(SysTick_Config(SystemCoreClock / 1000)) //1000000:us 1000:ms
  { 
		/* Capture error */
		NVIC_SystemReset();
	}	   
}								    

void TimingDelay_Crement(void)
{
	if(TimingDelay < 0x100000000)
	{
		TimingDelay++;
	}
	else
	{
		TimingDelay =0;
	}
}

uint64_t millis(void)
{
	return TimingDelay;
}

void delay_ms(__IO u32 nTime)
{	 		  	  
const uint64_t fac_ms= millis();
uint32_t timeDelay_ms;
uint32_t timeDelay_now;

	do
	{
		timeDelay_now = millis();
		timeDelay_ms = timeDelay_now - fac_ms;
	}
  while(timeDelay_ms < nTime);					   
} 


