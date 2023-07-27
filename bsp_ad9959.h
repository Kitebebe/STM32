/**
 ******************************************************************************
 * @file			:bsp_ad9959.h
 * @brief			:The board support package for AD9959.
 * @version		    :0.1.1
 * @author		    :July
 * @date			:2022.07.01
 * @updata		    :2022.07.14
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

#ifndef __BSP_AD9959_H__
#define __BSP_AD9959_H__

#include "main.h"
/* ==================================== */
#define AD9959_USART_DRIVE 0
/* ==================================== */

#if AD9959_USART_DRIVE

#define USE_STDIO 1U

extern uint8_t ad9959_mode[][10];
extern uint32_t ad9959_param;

#if (USE_STDIO)
#define __AD9959_AT printf("AT\r\n")                                          /* ����ָ�� */
#define __AD9959_RST printf("AT+RESET\r\n")                                   /* ��λ */
#define __AD9959_GET_VERSION printf("AT+VERSION\r\n")                         /* �汾��ȡ */
#define __AD9959_SET_CHANNEL(n) printf("AT+CHANNEL+%d\r\n", ad9959_param = n) /* ͨ������		1/2/3/4 */
#define __AD9959_SET_REF(n) printf("AT+REF+%d\r\n", ad9959_param = n)         /* �ο�����Ƶ������		10-125	MHz */
#define __AD9959_SET_MULT(n) printf("AT+MULT+%d\r\n", ad9959_param = n)       /* ��Ƶ������	1-20 */
#define __AD9959_SET_MODE(n) printf("AT+MODE+%s\r\n", ad9959_mode[n])         /* ����ģʽ	POINT/SWEEP/FSK2/FSK4/AM */

#define __AD9959_SET_POINT_FRE(n) printf("AT+FRE+%d\r\n", ad9959_param = n) /* ��ƵƵ�����	1-200,000,000	Hz */
#define __AD9959_SET_POINT_AMP(n) printf("AT+AMP+%d\r\n", ad9959_param = n) /* ��Ƶ�������	1-1023 */
#define __AD9959_SET_POINT_PHA(n) printf("AT+PHA+%d\r\n", ad9959_param = n) /* ��Ƶ��λ���	0-16386����Ӧ0-360�㣩 */

#define __AD9959_SET_SWEEP_STARTFRE(n) printf("AT+STARTFRE+%d\r\n", ad9959_param = n) /* ɨƵ��ʼƵ��	1-200,000,000	Hz */
#define __AD9959_SET_SWEEP_ENDFRE(n) printf("AT+ENDFRE+%d\r\n", ad9959_param = n)     /* ɨƵ����Ƶ��	1-200,000,000	Hz */
#define __AD9959_SET_SWEEP_STARTAMP(n) printf("AT+STARTAMP+%d\r\n", ad9959_param = n) /* ɨƵ��ʼ����	1-1023 */
#define __AD9959_SET_SWEEP_ENDAMP(n) printf("AT+ENDAMP+%d\r\n", ad9959_param = n)     /* ɨƵ��������	1-1023 */
#define __AD9959_SET_SWEEP_TIME(n) printf("AT+TIME+%d\r\n", ad9959_param = n)         /* ɨƵ���ʱ��	0-9999	ms */
#define __AD9959_SET_SWEEP_STEP(n) printf("AT+STEP+%d\r\n", ad9959_param = n)         /* ɨƵ���Ƶ��	1-200,000,000	Hz */
#define __AD9959_SWEEP_ON printf("AT+SWEEP+ON\r\n", ad9959_param = n)                 /* ɨƵ��ʼ */
#define __AD9959_SWEEP_OFF printf("AT+SWEEP+OFF\r\n", ad9959_param = n)               /* ɨƵ���� */

#define __AD9959_SET_2FSK_FRE1(n) printf("AT+FRE1+%d\r\n", ad9959_param = n) /* 2FSKģʽƵ��1		1-200,000,000	Hz */
#define __AD9959_SET_2FSK_FRE2(n) printf("AT+FRE2+%d\r\n", ad9959_param = n) /* 2FSKģʽƵ��2		1-200,000,000	Hz */

#define __AD9959_SET_4FSK_FRE1(n) printf("AT+FRE1+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��1		1-200,000,000	Hz */
#define __AD9959_SET_4FSK_FRE2(n) printf("AT+FRE2+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��2		1-200,000,000	Hz */
#define __AD9959_SET_4FSK_FRE3(n) printf("AT+FRE3+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��3		1-200,000,000	Hz */
#define __AD9959_SET_4FSK_FRE4(n) printf("AT+FRE4+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��4		1-200,000,000	Hz */

#define __AD9959_SET_AM_FRE(n) printf("AT+FRE+%d\r\n", ad9959_param = n)   /* AMƵ��	1-200,000,000	Hz */
#define __AD9959_SET_AM_DEP(n) printf("AT+DEP+%d\r\n", ad9959_param = n)   /* AM�������	1-100 */
#define __AD9959_SET_AM_RATE(n) printf("AT+RATE+%d\r\n", ad9959_param = n) /* AM��������	20-600	Hz */
#define __AD9959_AM_ON printf("AT+AM+ON\r\n", ad9959_param = n)            /* ��ʼAM���� */
#define __AD9959_AM_OFF printf("AT+AM+OFF\r\n", ad9959_param = n)          /* ����AM���� */
#else
#define __AD9959_AT bsprif1("AT\n")                                          /* ����ָ�� */
#define __AD9959_RST bsprif1("AT+RESET\n")                                   /* ��λ */
#define __AD9959_GET_VERSION bsprif1("AT+VERSION\n")                         /* �汾��ȡ */
#define __AD9959_SET_CHANNEL(n) bsprif1("AT+CHANNEL+%d\n", ad9959_param = n) /* ͨ������		1/2/3/4 */
#define __AD9959_SET_REF(n) bsprif1("AT+REF+%d\n", ad9959_param = n)         /* �ο�����Ƶ������		10-125	MHz */
#define __AD9959_SET_MULT(n) bsprif1("AT+MULT+%d\n", ad9959_param = n)       /* ��Ƶ������	1-20 */
#define __AD9959_SET_MODE(n) bsprif1("AT+MODE+%s\n", ad9959_mode[n])         /* ����ģʽ	POINT/SWEEP/FSK2/FSK4/AM */

#define __AD9959_SET_POINT_FRE(n) bsprif1("AT+FRE+%d\n", ad9959_param = n) /* ��ƵƵ�����	1-200,000,000	Hz */
#define __AD9959_SET_POINT_AMP(n) bsprif1("AT+AMP+%d\n", ad9959_param = n) /* ��Ƶ�������	1-1023 */
#define __AD9959_SET_POINT_PHA(n) bsprif1("AT+PHA+%d\n", ad9959_param = n) /* ��Ƶ��λ���	0-16386����Ӧ0-360�㣩 */

#define __AD9959_SET_SWEEP_STARTFRE(n) bsprif1("AT+STARTFRE+%d\r\n", ad9959_param = n) /* ɨƵ��ʼƵ��	1-200,000,000	Hz */
#define __AD9959_SET_SWEEP_ENDFRE(n) bsprif1("AT+ENDFRE+%d\r\n", ad9959_param = n)     /* ɨƵ����Ƶ��	1-200,000,000	Hz */
#define __AD9959_SET_SWEEP_STARTAMP(n) bsprif1("AT+STARTAMP+%d\r\n", ad9959_param = n) /* ɨƵ��ʼ����	1-1023 */
#define __AD9959_SET_SWEEP_ENDAMP(n) bsprif1("AT+ENDAMP+%d\r\n", ad9959_param = n)     /* ɨƵ��������	1-1023 */
#define __AD9959_SET_SWEEP_TIME(n) bsprif1("AT+TIME+%d\r\n", ad9959_param = n)         /* ɨƵ���ʱ��	0-9999	ms */
#define __AD9959_SET_SWEEP_STEP(n) bsprif1("AT+STEP+%d\r\n", ad9959_param = n)         /* ɨƵ���Ƶ��	1-200,000,000	Hz */
#define __AD9959_SWEEP_ON bsprif1("AT+SWEEP+ON\r\n", ad9959_param = n)                 /* ɨƵ��ʼ */
#define __AD9959_SWEEP_OFF bsprif1("AT+SWEEP+OFF\r\n", ad9959_param = n)               /* ɨƵ���� */

#define __AD9959_SET_2FSK_FRE1(n) bsprif1("AT+FRE1+%d\r\n", ad9959_param = n) /* 2FSKģʽƵ��1		1-200,000,000	Hz */
#define __AD9959_SET_2FSK_FRE2(n) bsprif1("AT+FRE2+%d\r\n", ad9959_param = n) /* 2FSKģʽƵ��2		1-200,000,000	Hz */

#define __AD9959_SET_4FSK_FRE1(n) bsprif1("AT+FRE1+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��1		1-200,000,000	Hz */
#define __AD9959_SET_4FSK_FRE2(n) bsprif1("AT+FRE2+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��2		1-200,000,000	Hz */
#define __AD9959_SET_4FSK_FRE3(n) bsprif1("AT+FRE3+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��3		1-200,000,000	Hz */
#define __AD9959_SET_4FSK_FRE4(n) bsprif1("AT+FRE4+%d\r\n", ad9959_param = n) /* 4FSKģʽƵ��4		1-200,000,000	Hz */

#define __AD9959_SET_AM_FRE(n) bsprif1("AT+FRE+%d\r\n", ad9959_param = n)   /* AMƵ��	1-200,000,000	Hz */
#define __AD9959_SET_AM_DEP(n) bsprif1("AT+DEP+%d\r\n", ad9959_param = n)   /* AM�������	1-100 */
#define __AD9959_SET_AM_RATE(n) bsprif1("AT+RATE+%d\r\n", ad9959_param = n) /* AM��������	20-600	Hz */
#define __AD9959_AM_ON bsprif1("AT+AM+ON\r\n", ad9959_param = n)            /* ��ʼAM���� */
#define __AD9959_AM_OFF bsprif1("AT+AM+OFF\r\n", ad9959_param = n)          /* ����AM���� */
#endif
#else

#ifdef __BSP_STM32F1_ENABLED
// ���Ŷ���
#define AD9959_PS0_Pin GPIO_PIN_3
#define AD9959_PS0_GPIO_Port GPIOB

#define AD9959_PS1_Pin GPIO_PIN_4
#define AD9959_PS1_GPIO_Port GPIOB

#define AD9959_PS2_Pin GPIO_PIN_5
#define AD9959_PS2_GPIO_Port GPIOB

#define AD9959_PS3_Pin GPIO_PIN_6
#define AD9959_PS3_GPIO_Port GPIOB

#define AD9959_SDIO0_Pin GPIO_PIN_7
#define AD9959_SDIO0_GPIO_Port GPIOB

#define AD9959_SDIO1_Pin GPIO_PIN_10
#define AD9959_SDIO1_GPIO_Port GPIOC

#define AD9959_SDIO2_Pin GPIO_PIN_11
#define AD9959_SDIO2_GPIO_Port GPIOC

#define AD9959_PWR_Pin GPIO_PIN_12
#define AD9959_PWR_GPIO_Port GPIOC

#define AD9959_UPDATE_Pin GPIO_PIN_15
#define AD9959_UPDATE_GPIO_Port GPIOA

#define AD9959_Reset_Pin GPIO_PIN_5
#define AD9959_Reset_GPIO_Port GPIOC

#define AD9959_CS_Pin GPIO_PIN_7
#define AD9959_CS_GPIO_Port GPIOC

#define AD9959_SCLK_Pin GPIO_PIN_8
#define AD9959_SCLK_GPIO_Port GPIOC

#define AD9959_SDIO3_Pin GPIO_PIN_9
#define AD9959_SDIO3_GPIO_Port GPIOC
#else /* STM32F4 */
// ���Ŷ���
#define AD9959_PS0_Pin GPIO_PIN_3
#define AD9959_PS0_GPIO_Port GPIOC

#define AD9959_PS1_Pin GPIO_PIN_1
#define AD9959_PS1_GPIO_Port GPIOA

#define AD9959_PS2_Pin GPIO_PIN_3
#define AD9959_PS2_GPIO_Port GPIOA

#define AD9959_PS3_Pin GPIO_PIN_5
#define AD9959_PS3_GPIO_Port GPIOA

#define AD9959_SDIO0_Pin GPIO_PIN_7
#define AD9959_SDIO0_GPIO_Port GPIOA

#define AD9959_SDIO1_Pin GPIO_PIN_5
#define AD9959_SDIO1_GPIO_Port GPIOC

#define AD9959_SDIO2_Pin GPIO_PIN_1
#define AD9959_SDIO2_GPIO_Port GPIOB

#define AD9959_PWR_Pin GPIO_PIN_2
#define AD9959_PWR_GPIO_Port GPIOA

#define AD9959_UPDATE_Pin GPIO_PIN_6
#define AD9959_UPDATE_GPIO_Port GPIOA

#define AD9959_Reset_Pin GPIO_PIN_2
#define AD9959_Reset_GPIO_Port GPIOC

#define AD9959_CS_Pin GPIO_PIN_4
#define AD9959_CS_GPIO_Port GPIOC

#define AD9959_SCLK_Pin GPIO_PIN_0
#define AD9959_SCLK_GPIO_Port GPIOB

#define AD9959_SDIO3_Pin GPIO_PIN_2
#define AD9959_SDIO3_GPIO_Port GPIOB
#endif

/*SET*/
#define AD9959_PS0_SET HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port, AD9959_PS0_Pin, GPIO_PIN_SET)
#define AD9959_PS1_SET HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port, AD9959_PS1_Pin, GPIO_PIN_SET)
#define AD9959_PS2_SET HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port, AD9959_PS2_Pin, GPIO_PIN_SET)
#define AD9959_PS3_SET HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port, AD9959_PS3_Pin, GPIO_PIN_SET)
#define AD9959_SDIO0_SET HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port, AD9959_SDIO0_Pin, GPIO_PIN_SET)
#define AD9959_SDIO1_SET HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port, AD9959_SDIO1_Pin, GPIO_PIN_SET)
#define AD9959_SDIO2_SET HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port, AD9959_SDIO2_Pin, GPIO_PIN_SET)

#define AD9959_PWR_SET HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port, AD9959_PWR_Pin, GPIO_PIN_SET)
#define AD9959_Reset_SET HAL_GPIO_WritePin(AD9959_Reset_GPIO_Port, AD9959_Reset_Pin, GPIO_PIN_SET)
#define AD9959_UPDATE_SET HAL_GPIO_WritePin(AD9959_UPDATE_GPIO_Port, AD9959_UPDATE_Pin, GPIO_PIN_SET)
#define AD9959_CS_SET HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin, GPIO_PIN_SET)
#define AD9959_SCLK_SET HAL_GPIO_WritePin(AD9959_SCLK_GPIO_Port, AD9959_SCLK_Pin, GPIO_PIN_SET)
#define AD9959_SDIO3_SET HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port, AD9959_SDIO3_Pin, GPIO_PIN_SET)

/*RESET*/
#define AD9959_PS0_RESET HAL_GPIO_WritePin(AD9959_PS0_GPIO_Port, AD9959_PS0_Pin, GPIO_PIN_RESET)
#define AD9959_PS1_RESET HAL_GPIO_WritePin(AD9959_PS1_GPIO_Port, AD9959_PS1_Pin, GPIO_PIN_RESET)
#define AD9959_PS2_RESET HAL_GPIO_WritePin(AD9959_PS2_GPIO_Port, AD9959_PS2_Pin, GPIO_PIN_RESET)
#define AD9959_PS3_RESET HAL_GPIO_WritePin(AD9959_PS3_GPIO_Port, AD9959_PS3_Pin, GPIO_PIN_RESET)
#define AD9959_SDIO0_RESET HAL_GPIO_WritePin(AD9959_SDIO0_GPIO_Port, AD9959_SDIO0_Pin, GPIO_PIN_RESET)
#define AD9959_SDIO1_RESET HAL_GPIO_WritePin(AD9959_SDIO1_GPIO_Port, AD9959_SDIO1_Pin, GPIO_PIN_RESET)
#define AD9959_SDIO2_RESET HAL_GPIO_WritePin(AD9959_SDIO2_GPIO_Port, AD9959_SDIO2_Pin, GPIO_PIN_RESET)

#define AD9959_PWR_RESET HAL_GPIO_WritePin(AD9959_PWR_GPIO_Port, AD9959_PWR_Pin, GPIO_PIN_RESET)
#define AD9959_Reset_RESET HAL_GPIO_WritePin(AD9959_Reset_GPIO_Port, AD9959_Reset_Pin, GPIO_PIN_RESET)
#define AD9959_UPDATE_RESET HAL_GPIO_WritePin(AD9959_UPDATE_GPIO_Port, AD9959_UPDATE_Pin, GPIO_PIN_RESET)
#define AD9959_CS_RESET HAL_GPIO_WritePin(AD9959_CS_GPIO_Port, AD9959_CS_Pin, GPIO_PIN_RESET)
#define AD9959_SCLK_RESET HAL_GPIO_WritePin(AD9959_SCLK_GPIO_Port, AD9959_SCLK_Pin, GPIO_PIN_RESET)
#define AD9959_SDIO3_RESET HAL_GPIO_WritePin(AD9959_SDIO3_GPIO_Port, AD9959_SDIO3_Pin, GPIO_PIN_RESET)

#define AD9959_Mode_Sweep 1    // ģʽ--ɨƵ
#define AD9959_Mode_FixedFre 2 // ģʽ--��Ƶ
#define AD9959_Mode_FHSS 3     // ģʽ--��Ƶ

extern uint8_t AD9959_Mode;           // ɨƵ���ߵ�Ƶ
extern uint8_t AD9959_Wave_Show_Mode; // ����ɨƵ--1  ������ɨƵ--0

extern uint32_t AD9959_SweepMaxFre;     // ���ɨƵƵ��--Hz
extern uint32_t AD9959_SweepMinFre;     // ��СɨƵƵ��--Hz
extern uint32_t AD9959_SweepStepFre;    // ɨƵ����Ƶ��--Hz
extern uint32_t AD9959_SweepTime;       // ɨƵ���ʱ��--ms
extern uint8_t AD9959_SweepWaveFlag;    // �Ƿ���ʾ����
extern uint32_t AD9959_SweepCount;      // extern����ʱ����--ms
extern uint32_t AD9959_SweepCountTimes; // extern����ʱ����

extern uint32_t AD9959_SweepMaxPha;  // ���ɨ����λ
extern uint32_t AD9959_SweepMinPha;  // ��Сɨ����λ
extern uint32_t AD9959_SweepStepPha; // ɨ�ಽ����λ

extern uint32_t AD9959_FixedMaxFre;  // ���̶����Ƶ��--Hz
extern uint32_t AD9959_FixedMinFre;  // ��С�̶����Ƶ��--Hz
extern uint32_t AD9959_FixedStepFre; // �����̶����Ƶ��--Hz
extern uint32_t AD9959_FixedAmpli;   // ������Ƶ�ʷ���--Hz
extern uint32_t AD9959_FixedNowFre;  // ��ʱ���Ƶ��--Hz

extern uint32_t AD9959_NowSinFre[5];
extern uint32_t AD9959_NowSinAmp[5];
extern uint32_t AD9959_NowSinPhr[5];

// AD9959�Ĵ�����ַ����
#define CSR_ADD 0x00           // CSR ͨ��ѡ��Ĵ���
#define FR1_ADD 0x01           // FR1 ���ܼĴ���1
#define FR2_ADD 0x02           // FR2 ���ܼĴ���2
#define CFR_ADD 0x03           // CFR ͨ�����ܼĴ���
#define CFTW0_ADD 0x04         // CTW0 ͨ��Ƶ��ת���ּĴ���
#define CPOW0_ADD 0x05         // CPW0 ͨ����λת���ּĴ���
#define ACR_ADD 0x06           // ACR ���ȿ��ƼĴ���
#define LSRR_ADD 0x07          // LSR ͨ������ɨ��Ĵ���
#define RDW_ADD 0x08           // RDW ͨ����������ɨ��Ĵ���
#define FDW_ADD 0x09           // FDW ͨ����������ɨ��Ĵ���

// ��ʱ
void delay1(uint32_t length);
// IO�ڳ�ʼ��
void Intserve(void);
// AD9959��λ
void IntReset(void);
// AD9959��������
void IO_Update(void);
/*--------------------------------------------
�������ܣ�������ͨ��SPI��AD9959д����
RegisterAddress: �Ĵ�����ַ
NumberofRegisters: �����ֽ���
*RegisterData: ������ʼ��ַ
temp: �Ƿ����IO�Ĵ���
----------------------------------------------*/
void WriteData_AD9959(uint8_t RegisterAddress, uint8_t NumberofRegisters, uint8_t *RegisterData, uint8_t temp);
/*---------------------------------------
�������ܣ�����ͨ�����Ƶ��
Channel:  ���ͨ��
Freq:     ���Ƶ��
---------------------------------------*/
void AD9959_WriteFreq(uint8_t Channel, uint32_t Freq);
/*---------------------------------------
�������ܣ�����ͨ���������
Channel:  ���ͨ��
Ampli:    �������
---------------------------------------*/
void AD9959_WriteAmpl(uint8_t Channel, uint16_t Ampli);
/*---------------------------------------
�������ܣ�����ͨ�������λ
Channel:  ���ͨ��
Phase:    �����λ,��Χ��0~16383(��Ӧ�Ƕȣ�0��~360��)
---------------------------------------*/
void AD9959_WritePhase(uint8_t Channel, uint16_t Phase);
/*---------------------------------------
�������ܣ�AD9959��ʼ��
---------------------------------------*/
void AD9959_Init(void);

#endif
#endif
