
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t count = 0;

void RCC_Config()
{
	RCC->CR |= 0x00010000;  //HSEON ENABLE
	while(!(RCC->CR & 0x00020000));  //HSEON Ready Flag Wait
	RCC->CR |= 0x00080000;  // CSS ENABLE
	RCC->CR |= 0x01000000; // PLL ON
	RCC->PLLCFGR |= 0x00400000;  // PLL e HSE se�tik
	RCC->PLLCFGR |= 0x00000004;  // PLL M = 4
	RCC->PLLCFGR |= 0x0005A000;  // PLL N = 168
	RCC->PLLCFGR |= 0x00000000;  // PLL P = 2
	RCC->CFGR |= 0x00000000;  //AHB Prescaler = 1
	RCC->CFGR |= 0x00080000;  //APB2 Prescaler = 2
	RCC->CFGR |= 0x00001400;  //APB1 Prescaler = 4
	RCC->CIR |= 0x00080000;  //HSERDY Flag clear
	RCC->CIR |= 0x00800000;  //CSS Flag clear
}

void Timer_Config()
{
	RCC->APB1ENR |= 1 << 0; // TIM2 Clock ENABLE
	TIM2->CR1 |= 0 << 4; // Counter mode is UPCOUNTER
	TIM2->CR1 |= 0 << 5; // Center aligned (edge-aligned) mode
	TIM2->CR1 |= 0 << 8; // Clock division is 1
	TIM2->SMCR |= 0 <<0; // Internal Clock Source
	TIM2->EGR |= 1 << 0; // Timer Update Generation
	TIM2->PSC = 41999; // Prescaler de�eri
	TIM2->ARR = 3999; // Period de�eri, timer'�n sayaca�� de�er
	TIM2->CR1 |= 1 << 0; // TIM2 Counter ENABLE
}

int main(void)
{
	RCC_Config();
	Timer_Config();

  while (1)
  {
	  count = TIM2->CNT;
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}