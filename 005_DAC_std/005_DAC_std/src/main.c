
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int i;

void Delay(uint32_t time)
{
	while(time--);
}

GPIO_InitTypeDef GPIO_InitStruct;
DAC_InitTypeDef DAC_InitStruct;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5; // DAC_Channel_2 kullan�ld��� i�in PA5'ten ��k�� al�n�r. Channel_1 olsayd� PA4'ten ��k�� aln�rd�.

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void DAC2_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_None;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable; // Buffer aktif edilerek g�r�lt� engellemeye �al���l�r.

	DAC_Init(DAC_Channel_2, &DAC_InitStruct);

	DAC_Cmd(DAC_Channel_2, ENABLE);
}

int main(void)
{
	GPIO_Config();
	DAC2_Config();

  while (1)
  {
	  for(; i < 255 ; i++) // 8 bitlik i�lem yapt���m�z i�in 255'e kadar say�yor.
	  {
		  DAC_SetChannel2Data(DAC_Align_8b_R, i);
		  Delay(168000);
	  }
	  i = 0;
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
