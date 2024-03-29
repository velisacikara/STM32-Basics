#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/*
 * Bu �al��mada GPIO, Timer ve Interrrupt bir arada kullan�lm��t�r.
 * Timer her ta�t��� durumda interrupta girecek ve ledler toggle olacakt�r.
 * Count de�i�keni ile timer'�n de�erleri STM Studio �zerinden takip edilebilir.
 * */

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

int count; // Timer de�erini tutacak de�i�ken

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;

	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

void Timer_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 1999;
	TIM_InitStruct.TIM_Prescaler = 41999;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIM_InitStruct);

	TIM_Cmd(TIM2, ENABLE);
}

void NVIC_Config()
{
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); // Timer ile interrupt'� birbirine ba�lamak i�in kullan�l�r.

	NVIC_Init(&NVIC_InitStruct);
}

void TIM2_IRQHandler() // Interrupt fonksiyonu
{
	GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // flag temizleme
}

int main(void)
{
	GPIO_Config();
	Timer_Config();
	NVIC_Config();

  while (1)
  {
	  count = TIM_GetCounter(TIM2);
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
