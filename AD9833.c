/**********************************************************
                       ��������
���ܣ�stm32f103rct6����AD9833ģ��
�ӿڣ��������Žӿ������AD9833.h
ʱ�䣺2023/06/08
�汾��2.1
���ߣ���������
������������ֻ��ѧϰʹ�ã�����ؾ���

������������뵽�Ա��꣬�������ӽ߳�Ϊ������ ^_^
https://kvdz.taobao.com/ 
���ǲ����300Khz���������Ϊ��дֵ�����������Ҳ����400Khz
**********************************************************/
#include "AD9833.h"		
#include "gpio.h"

//ʱ������Ϊ25 MHzʱ�� ����ʵ��0.1 Hz�ķֱ��ʣ���ʱ������Ϊ1 MHzʱ�������ʵ��0.004 Hz�ķֱ��ʡ�
//�����ο�ʱ���޸Ĵ˴����ɡ�
#define FCLK 25000000	//���òο�ʱ��25MHz����Ĭ�ϰ��ؾ���Ƶ��25Mhz��

#define RealFreDat    268435456.0/FCLK//�ܵĹ�ʽΪ Fout=��Fclk/2��28�η���*28λ�Ĵ�����ֵ

/************************************************************
** �������� ��void AD983_GPIO_Init(void)  
** �������� ����ʼ������AD9833��Ҫ�õ���IO��
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
*				****����Ҫ�ĺ���
**************************************************************/

void AD983_GPIO_Init(void) 
{

	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();	 //ʹ��PA�˿�ʱ��

	GPIO_InitStruct.Pin = GPIO_PIN_3| GPIO_PIN_4| GPIO_PIN_5;

	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
} 

/**********************************************************************************************
** �������� ��unsigned char AD9833_SPI_Write(unsigned char* data,unsigned char bytesNumber)
** �������� ��ʹ��ģ��SPI��AD9833д����
** ��ڲ��� ��* data:д�����ݻ�����,��һ���ֽ��ǼĴ�����ַ���ڶ����ֽڿ�ʼҪд������ݡ�
						bytesNumber: Ҫд����ֽ���
** ���ڲ��� ����
** ����˵�� ����
* *			����Ҫ�ĺ���
************************************************************************************************/
unsigned char AD9833_SPI_Write(unsigned char* data,unsigned char bytesNumber)
{
  unsigned char i,j; 
	unsigned char writeData[5]	= {0,0, 0, 0, 0};
	
 //   AD9833_SCLK=1; 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
 //   AD9833_FSYNC=0 ; 
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, 0);

	for(i = 0;i < bytesNumber;i ++)
	{
		writeData[i] = data[i + 1];
	}
	
	for(i=0 ;i<bytesNumber ;i++) 
	{
    for(j=0 ;j<8 ;j++)      
		{ 
        if(writeData[i] & 0x80) 
          AD9833_SDATA_1; 
        else 
          AD9833_SDATA_0; 

        AD9833_SCLK_0; 
        writeData[i] <<= 1; 
        AD9833_SCLK_1; 
    } 
	}
    AD9833_SDATA_1; 
    AD9833_FSYNC_1; 
		
		return i;
}

/************************************************************
** �������� ��void AD9833_Init(void)  
** �������� ����ʼ������AD9833��Ҫ�õ���IO�ڼ��Ĵ���
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
**ʹ���ȵ����������
**************************************************************/
void AD9833_Init(void)
{
    AD983_GPIO_Init();
    AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
}

/*****************************************************************************************
** �������� ��void AD9833_Reset(void)  
** �������� ������AD9833�ĸ�λλ
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
*******************************************************************************************/
void AD9833_Reset(void)
{
	AD9833_SetRegisterValue(AD9833_REG_CMD | AD9833_RESET);
	HAL_Delay(10);
}

/*****************************************************************************************
** �������� ��void AD9833_ClearReset(void)  
** �������� �����AD9833�ĸ�λλ��
** ��ڲ��� ����
** ���ڲ��� ����
** ����˵�� ����
*******************************************************************************************/
void AD9833_ClearReset(void)
{
	AD9833_SetRegisterValue(AD9833_REG_CMD);
}

/*****************************************************************************************
** �������� ��void AD9833_SetRegisterValue(unsigned short regValue)
** �������� ����ֵд��Ĵ���
** ��ڲ��� ��regValue��Ҫд��Ĵ�����ֵ��
** ���ڲ��� ����
** ����˵�� ����
**           ����Ҫ�ĺ���
*******************************************************************************************/
void AD9833_SetRegisterValue(unsigned short regValue)
{
	unsigned char data[5] = {0x03, 0x00, 0x00};	
	
	data[1] = (unsigned char)((regValue & 0xFF00) >> 8);
	data[2] = (unsigned char)((regValue & 0x00FF) >> 0);
	AD9833_SPI_Write(data,2);
}

/*****************************************************************************************
** �������� ��void AD9833_SetFrequencyQuick(float fout,unsigned short type)
** �������� ��д��Ƶ�ʼĴ���
** ��ڲ��� ��val��Ҫд���Ƶ��ֵ��
**						type���������ͣ�AD9833_OUT_SINUS���Ҳ���AD9833_OUT_TRIANGLE���ǲ���AD9833_OUT_MSB����
** ���ڲ��� ����
** ����˵�� ��ʱ������Ϊ25 MHzʱ�� ����ʵ��0.1 Hz�ķֱ��ʣ���ʱ������Ϊ1 MHzʱ�������ʵ��0.004 Hz�ķֱ��ʡ�
* *******������������������Ҫ����
*******************************************************************************************/
void AD9833_SetFrequencyQuick(float fout,unsigned short type)
{
	AD9833_SetFrequency(AD9833_REG_FREQ0, fout,type);
}

/*****************************************************************************************
** �������� ��void AD9833_SetFrequency(unsigned short reg, float fout,unsigned short type)
** �������� ��д��Ƶ�ʼĴ���
** ��ڲ��� ��reg��Ҫд���Ƶ�ʼĴ�����
**						val��Ҫд���ֵ��
**						type���������ͣ�AD9833_OUT_SINUS���Ҳ���AD9833_OUT_TRIANGLE���ǲ���AD9833_OUT_MSB����
** ���ڲ��� ����
** ����˵�� ����
* *					����Ҫ�ĺ���
* +
*******************************************************************************************/
void AD9833_SetFrequency(unsigned short reg, float fout,unsigned short type)
{
	unsigned short freqHi = reg;
	unsigned short freqLo = reg;
	unsigned long val=RealFreDat*fout;
	freqHi |= (val & 0xFFFC000) >> 14 ;
	freqLo |= (val & 0x3FFF);
	AD9833_SetRegisterValue(AD9833_B28|type);
	AD9833_SetRegisterValue(freqLo);
	AD9833_SetRegisterValue(freqHi);
}

/*****************************************************************************************
** �������� ��void AD9833_SetPhase(unsigned short reg, unsigned short val)
** �������� ��д����λ�Ĵ�����
** ��ڲ��� ��reg��Ҫд�����λ�Ĵ�����
**						val��Ҫд���ֵ��
** ���ڲ��� ����
** ����˵�� ����
*******************************************************************************************/
void AD9833_SetPhase(unsigned short reg, unsigned short val)
{
	unsigned short phase = reg;
	phase |= val;
	AD9833_SetRegisterValue(phase);
}

/*****************************************************************************************
** �������� ��void AD9833_Setup(unsigned short freq, unsigned short phase,unsigned short type)
** �������� ��д����λ�Ĵ�����
** ��ڲ��� ��freq��ʹ�õ�Ƶ�ʼĴ�����
							phase��ʹ�õ���λ�Ĵ�����
							type��Ҫ����Ĳ������͡�
** ���ڲ��� ����
** ����˵�� ����
*******************************************************************************************/
void AD9833_Setup(unsigned short freq, unsigned short phase,unsigned short type)
{
	unsigned short val = 0;
	
	val = freq | phase | type;
	AD9833_SetRegisterValue(val);
}

/*****************************************************************************************
** �������� ��void AD9833_SetWave(unsigned short type)
** �������� ������Ҫ����Ĳ������͡�
** ��ڲ��� ��type��Ҫ����Ĳ������͡�
** ���ڲ��� ����
** ����˵�� ����
*******************************************************************************************/
void AD9833_SetWave(unsigned short type)
{
	AD9833_SetRegisterValue(type);
}








