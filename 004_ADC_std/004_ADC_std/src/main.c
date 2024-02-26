
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value; // return edilen adc deðerini tutacak deðiþken, 12 bitlik okuma yapýldýðý için uint16_t seçildi.

float adc_voltage;

void GPIO_Config() // GPIO konfigürasyon ayarlarý
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;

	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void ADC_Config() // ADC konfigürasyon ayarlarý
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent; // Tek adc okumasý yaptýðýmýz için independent seçtik.
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4; // ADC'nin çalýþabilmesi için (36 MHz) seçilen hýz ona uygun bir deðere bölünmelidir. Yani 36 MHZ'den küçük olmalýdýr. 84/4 olmalý

	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;

	ADC_Init(ADC1, &ADC_InitStruct);

	ADC_Cmd(ADC1, ENABLE); // Çevresel birimleri aktif etmek için kullanýlan fonksiyondur.
}

uint16_t Read_ADC()
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);

	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // ADC okumasý bitene kadar (EOC bayraðý kalkana kadar) beklemeyi saðlar.

	return ADC_GetConversionValue(ADC1); // Okunan ADC deðerini return eder.

}

int main(void)
{

	GPIO_Config();
	ADC_Config();

  while (1)
  {
	  adc_value = Read_ADC();
	  adc_voltage = (0.000805) * adc_value;

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
