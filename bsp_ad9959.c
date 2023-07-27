/**
 ******************************************************************************
 * @file			:bsp_ad9959.c
 * @brief			:The board support package for AD9959.
 * @version			:0.1.1
 * @author			:July
 * @date			:2022.07.01
 * @updata			:2022.07.14
 ******************************************************************************
 * @pinset		:
 *
 *				F1RC:
 *							GPIOB_PIN_3 	---> P0
 *							GPIOB_PIN_4 	---> P1
 *							GPIOB_PIN_5		---> P2
 *							GPIOB_PIN_6		---> P3
 *							GPIOB_PIN_7		---> SD0
 *							GPIOC_PIN_10	---> SD1
 *							GPIOC_PIN_11	---> SD2
 *							GPIOC_PIN_9		---> SD3
 *							GPIOC_PIN_12	---> PDC/PWR
 *							GPIOA_PIN_15	---> UPDATA
 *							GPIOC_PIN_5		---> RST
 *							GPIOC_PIN_7		---> CS
 *							GPIOC_PIN_8		---> SCK
 *
 *				F4ZG:
 *							GPIOC_PIN_3 	---> P0
 *							GPIOA_PIN_1 	---> P1
 *							GPIOA_PIN_3	  ---> P2
 *							GPIOA_PIN_5		---> P3
 *							GPIOA_PIN_7		---> SD0
 *							GPIOC_PIN_5		---> SD1
 *							GPIOB_PIN_1		---> SD2
 *							GPIOB_PIN_2		---> SD3
 *							GPIOA_PIN_2		---> PDC/PWR
 *							GPIOA_PIN_6	---> UPDATA
 *							GPIOC_PIN_2	---> RST
 *							GPIOC_PIN_4	---> CS
 *							GPIOB_PIN_0		---> SCK
 *
 *******************************************************************************
 */

#include "bsp_ad9959.h"
#include "gpio.h"

#if AD9959_USART_DRIVE
uint8_t ad9959_mode[][10] = {"POINT", "SWEEP", "FSK2", "FSK4", "AM"};
uint32_t ad9959_param = 0;
#else

uint32_t FRE_Send = 0;

uint8_t AD9959_Mode = 0;		   // ɨƵ���ߵ�Ƶ
uint8_t AD9959_Wave_Show_Mode = 1; // ����ɨƵ--1  ������ɨƵ--0

/********************************ɨƵ/ɨ��*********************************/
/*
 * ͨ��
 * */
uint8_t AD9959_SweepWaveFlag = 0;	 // �Ƿ���ʾ����
uint32_t AD9959_SweepCount = 0;		 // extern����ʱ����--ms
uint32_t AD9959_SweepCountTimes = 0; // extern����ʱ����
uint32_t AD9959_SweepTime = 2;		 // ɨƵ���ʱ��--ms

/*
 * ɨƵ
 * */
uint32_t AD9959_SweepMaxFre = 1000000; // ���ɨƵƵ��--Hz
uint32_t AD9959_SweepMinFre = 1000;	   // ��СɨƵƵ��--Hz
uint32_t AD9959_SweepStepFre = 1000;   // ɨƵ����Ƶ��--Hz

/*
 * ɨ��  0~16383(��Ӧ�Ƕȣ�0��~360��)
 * */
uint32_t AD9959_SweepMaxPha = 16383; // ���ɨ����λ
uint32_t AD9959_SweepMinPha = 0;	 // ��Сɨ����λ
uint32_t AD9959_SweepStepPha = 450;	 // ɨ�ಽ����λ

/********************************��Ƶ*********************************/
uint32_t AD9959_FixedMaxFre = 300000; // ���̶����Ƶ��--Hz
uint32_t AD9959_FixedMinFre = 10000;  // ��С�̶����Ƶ��--Hz
uint32_t AD9959_FixedStepFre = 10000; // �����̶����Ƶ��--Hz
uint32_t AD9959_FixedAmpli = 1023;	  // ������Ƶ�ʷ���--Hz
uint32_t AD9959_FixedNowFre = 15000;  // ��ʱ���Ƶ��--Hz

uint32_t AD9959_NowSinFre[5] = {0};
uint32_t AD9959_NowSinAmp[5] = {0};
uint32_t AD9959_NowSinPhr[5] = {0};

int AD9959_FixedPhase_Differ = 0;	   // ��λ
int AD9959_FixedPhase_Differ_Last = 0; // ��λ
uint8_t AD9959_FixedAmpli_Differ = 0;  // ����
int AD9959_FixedAmpli_Eror = -40;	   // ��λ����У׼

uint8_t CSR_DATA0[1] = {0x10}; // �� CH0
uint8_t CSR_DATA1[1] = {0x20}; // �� CH1
uint8_t CSR_DATA2[1] = {0x40}; // �� CH2
uint8_t CSR_DATA3[1] = {0x80}; // �� CH3

uint8_t FR2_DATA[2] = {0x00, 0x00};		  // default Value = 0x0000
uint8_t CFR_DATA[3] = {0x00, 0x03, 0x02}; // default Value = 0x000302

uint8_t CPOW0_DATA[2] = {0x00, 0x00}; // default Value = 0x0000   @ = POW/2^14*360

uint8_t LSRR_DATA[2] = {0x00, 0x00}; // default Value = 0x----

uint8_t RDW_DATA[4] = {0x00, 0x00, 0x00, 0x00}; // default Value = 0x--------

uint8_t FDW_DATA[4] = {0x00, 0x00, 0x00, 0x00}; // default Value = 0x--------

uint32_t SinFre[5] = {40000, 40000, 40000, 40000};
uint32_t SinAmp[5] = {1023, 1023, 1023, 1023};
uint32_t SinPhr[5] = {0, 455, 4096 * 2 - 1, 4096 * 3 - 1};

#ifdef __BSP_STM32F1
void AD9959_Drv_Init(void)
{
	/* GPIO Ports Clock Enable */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	/*Configure GPIOA pin Output Level */
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);

	/*Configure GPIOB pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);

	/*Configure GPIOC pin Output Level */
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12, GPIO_PIN_RESET);

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 |
						  GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
#else
void AD9959_Drv_Init(void)
{
	/* GPIO Ports Clock Enable */
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOG, AD9959_SDIO3_Pin | AD9959_SDIO2_Pin | AD9959_Reset_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOC, AD9959_PS0_Pin | AD9959_SCLK_Pin | AD9959_SDIO1_Pin | AD9959_PS2_Pin | AD9959_UPDATE_Pin | AD9959_CS_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port, AD9959_SDIO0_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOD, AD9959_PS3_Pin | AD9959_PWR_Pin | AD9959_PS1_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pins : PGPin PGPin PGPin */
	GPIO_InitStruct.Pin = AD9959_SDIO3_Pin | AD9959_SDIO2_Pin | AD9959_Reset_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/*Configure GPIO pins : PCPin PCPin PCPin PCPin
							 PCPin PCPin */
	GPIO_InitStruct.Pin = AD9959_PS0_Pin | AD9959_SCLK_Pin | AD9959_SDIO1_Pin | AD9959_PS2_Pin | AD9959_UPDATE_Pin | AD9959_CS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = AD9959_SDIO0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(AD9959_SDIO0_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PDPin PDPin PDPin */
	GPIO_InitStruct.Pin = AD9959_PS3_Pin | AD9959_PWR_Pin | AD9959_PS1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}
#endif

// ��ʱ
void delay1(uint32_t length)
{
	length = length * 12;
	while (length--)
		;
}
// IO�ڳ�ʼ��
void Intserve(void)
{
	AD9959_PWR_RESET;
	AD9959_CS_SET;
	AD9959_SCLK_RESET;
	AD9959_UPDATE_RESET;
	AD9959_PS0_RESET;
	AD9959_PS1_RESET;
	AD9959_PS2_RESET;
	AD9959_PS3_RESET;
	AD9959_SDIO0_RESET;
	AD9959_SDIO1_RESET;
	AD9959_SDIO2_RESET;
	AD9959_SDIO3_RESET;
}
// AD9959��λ
void IntReset(void)
{
	AD9959_Reset_RESET;
	delay1(1); // 1
	AD9959_Reset_SET;
	delay1(30); // 30
	AD9959_Reset_RESET;
}
// AD9959��������
void IO_Update(void)
{
	AD9959_UPDATE_RESET;
	delay1(2); // 2
	AD9959_UPDATE_SET;
	delay1(4); // 4
	AD9959_UPDATE_RESET;
}
/*--------------------------------------------
�������ܣ�������ͨ��SPI��AD9959д����
RegisterAddress: �Ĵ�����ַ
NumberofRegisters: �����ֽ���
*RegisterData: ������ʼ��ַ
temp: �Ƿ����IO�Ĵ���
----------------------------------------------*/
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData, uint8_t temp)
{
	uint8_t ControlValue = 0;
	uint8_t ValueToWrite = 0;
	uint8_t RegisterIndex = 0;
	uint8_t i = 0;

	ControlValue = RegisterAddress;
	// д���ַ
	AD9959_SCLK_RESET;
	AD9959_CS_RESET;
	for (i = 0; i < 8; i++)
	{
		AD9959_SCLK_RESET;
		if (0x80 == (ControlValue & 0x80))
			AD9959_SDIO0_SET;
		else
			AD9959_SDIO0_RESET;
		AD9959_SCLK_SET;
		ControlValue <<= 1;
	}
	AD9959_SCLK_RESET;
	// д������
	for (RegisterIndex = 0; RegisterIndex < NumberofRegisters; RegisterIndex++)
	{
		ValueToWrite = RegisterData[RegisterIndex];
		for (i = 0; i < 8; i++)
		{
			AD9959_SCLK_RESET;
			if (0x80 == (ValueToWrite & 0x80))
				AD9959_SDIO0_SET;
			else
				AD9959_SDIO0_RESET;
			AD9959_SCLK_SET;
			ValueToWrite <<= 1;
		}
		AD9959_SCLK_RESET;
	}
	if (temp != 0)
		IO_Update();
	AD9959_CS_SET;
}
/*---------------------------------------
�������ܣ�����ͨ�����Ƶ��
Channel:  ���ͨ��
Freq:     ���Ƶ��
---------------------------------------*/
void AD9959_WriteFreq(uint8_t Channel, uint32_t Freq)
{
	uint8_t CFTW0_DATA[4] = {0x00, 0x00, 0x00, 0x00}; // �м����
	uint32_t Temp;
	Temp = (uint32_t)Freq * 8.589934592; // ������Ƶ�����ӷ�Ϊ�ĸ��ֽ�  8.589934592=(2^32)/500000000 ����500M=25M*20(��Ƶ���ɱ��)
	CFTW0_DATA[3] = (uint8_t)Temp;
	CFTW0_DATA[2] = (uint8_t)(Temp >> 8);
	CFTW0_DATA[1] = (uint8_t)(Temp >> 16);
	CFTW0_DATA[0] = (uint8_t)(Temp >> 24);
	if (Channel == 0)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA0, 1);	   // ���ƼĴ���д��CH0ͨ��
		WriteData_AD9959(CFTW0_ADD, 4, CFTW0_DATA, 1); // CTW0 address 0x04.���CH0�趨Ƶ��
	}
	else if (Channel == 1)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA1, 1);	   // ���ƼĴ���д��CH1ͨ��
		WriteData_AD9959(CFTW0_ADD, 4, CFTW0_DATA, 1); // CTW0 address 0x04.���CH1�趨Ƶ��
	}
	else if (Channel == 2)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA2, 1);	   // ���ƼĴ���д��CH2ͨ��
		WriteData_AD9959(CFTW0_ADD, 4, CFTW0_DATA, 1); // CTW0 address 0x04.���CH2�趨Ƶ��
	}
	else if (Channel == 3)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA3, 1);	   // ���ƼĴ���д��CH3ͨ��
		WriteData_AD9959(CFTW0_ADD, 4, CFTW0_DATA, 1); // CTW0 address 0x04.���CH3�趨Ƶ��
	}
}
/*---------------------------------------
�������ܣ�����ͨ���������
Channel:  ���ͨ��
Ampli:    �������
---------------------------------------*/
void AD9959_WriteAmpl(uint8_t Channel, uint16_t Ampli)
{
	uint16_t A_temp;						  //=0x23ff;
	uint8_t ACR_DATA[3] = {0x00, 0x00, 0x00}; // default Value = 0x--0000 Rest = 18.91/Iout
	A_temp = Ampli | 0x1000;
	ACR_DATA[2] = (uint8_t)A_temp;		  // ��λ����
	ACR_DATA[1] = (uint8_t)(A_temp >> 8); // ��λ����

	if (Channel == 0)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA0, 1);
		WriteData_AD9959(ACR_ADD, 3, ACR_DATA, 1);
	}

	else if (Channel == 1)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA1, 1);
		WriteData_AD9959(ACR_ADD, 3, ACR_DATA, 1);
	}

	else if (Channel == 2)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA2, 1);
		WriteData_AD9959(ACR_ADD, 3, ACR_DATA, 1);
	}

	else if (Channel == 3)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA3, 1);
		WriteData_AD9959(ACR_ADD, 3, ACR_DATA, 1);
	}
}
/*---------------------------------------
�������ܣ�����ͨ�������λ
Channel:  ���ͨ��
Phase:    �����λ,��Χ��0~16383(��Ӧ�Ƕȣ�0��~360��)
---------------------------------------*/
void AD9959_WritePhase(uint8_t Channel, uint16_t Phase)
{
	uint16_t P_temp = 0;
	P_temp = (uint16_t)Phase;
	CPOW0_DATA[1] = (uint8_t)P_temp;
	CPOW0_DATA[0] = (uint8_t)(P_temp >> 8);
	if (Channel == 0)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA0, 1);
		WriteData_AD9959(CPOW0_ADD, 2, CPOW0_DATA, 1);
	}

	else if (Channel == 1)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA1, 1);
		WriteData_AD9959(CPOW0_ADD, 2, CPOW0_DATA, 1);
	}

	else if (Channel == 2)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA2, 1);
		WriteData_AD9959(CPOW0_ADD, 2, CPOW0_DATA, 1);
	}

	else if (Channel == 3)
	{
		WriteData_AD9959(CSR_ADD, 1, CSR_DATA3, 1);
		WriteData_AD9959(CPOW0_ADD, 2, CPOW0_DATA, 1);
	}
}

// AD9959��ʼ��
void AD9959_Init(void)
{
	uint8_t FR1_DATA[3] = {0xD0, 0x00, 0x00}; // 20��Ƶ Charge pump control = 75uA FR1<23> -- VCO gain control =0ʱ system clock below 160 MHz;

	AD9959_Drv_Init();

	Intserve(); // IO�ڳ�ʼ��
	IntReset(); // AD9959��λ

	WriteData_AD9959(FR1_ADD, 3, FR1_DATA, 1); // д���ܼĴ���1
	WriteData_AD9959(FR2_ADD, 2, FR2_DATA, 1);

#if 0
  WriteData_AD9959(CFR_ADD,3,CFR_DATA,1);
  WriteData_AD9959(CPOW0_ADD,2,CPOW0_DATA,0);
  WriteData_AD9959(ACR_ADD,3,ACR_DATA,0);
  WriteData_AD9959(LSRR_ADD,2,LSRR_DATA,0);
  WriteData_AD9959(RDW_ADD,2,RDW_DATA,0);
  WriteData_AD9959(FDW_ADD,4,FDW_DATA,1);
#endif

	// д���ʼƵ��
	AD9959_WriteFreq(3, SinFre[3]);
	AD9959_WriteFreq(0, SinFre[0]);
	AD9959_WriteFreq(1, SinFre[1]);
	AD9959_WriteFreq(2, SinFre[2]);

	AD9959_WritePhase(3, SinPhr[3]);
	AD9959_WritePhase(0, SinPhr[0]);
	AD9959_WritePhase(1, SinPhr[1]);
	AD9959_WritePhase(2, SinPhr[2]);

	AD9959_WriteAmpl(3, SinAmp[3]);
	AD9959_WriteAmpl(0, SinAmp[0]);
	AD9959_WriteAmpl(1, SinAmp[1]);
	AD9959_WriteAmpl(2, SinAmp[2]);
}
#endif
