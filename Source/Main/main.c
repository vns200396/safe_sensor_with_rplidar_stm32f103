#include "stm32f10x.h"
#include "scan_space.h"

int main(void)
{
	SystemInit();
	SysTick_Init();
	lidar_init();
	led_alert_init();
	while(1)
	{
		lidar_scanning();
	}
}

