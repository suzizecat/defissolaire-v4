/**
 * Copyright (c) 2018-2020 FAUCHER Julien & FRANCE Loic
 * This file is part of SooL core Library.
 *
 *  SooL core Library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 *
 *  SooL core Library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with SooL core Library. If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef SOOL_IRQ_H
#define SOOL_IRQ_H

#include "../../sool_chip_setup.h"
#include "system_stm32.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
#if defined(STM32L5      )
	Reset_IRQn = -15,
	SecureFault_IRQn = -9,
	RTC_S_IRQn = 3,
	TAMP_IRQn = 4,
	TAMP_S_IRQn = 5,
	FLASH_IRQn = 6,
	FLASH_S_IRQn = 7,
	GTZC_IRQn = 8,
	RCC_IRQn = 9,
	RCC_S_IRQn = 10,
	EXTI0_IRQn = 11,
	EXTI1_IRQn = 12,
	EXTI2_IRQn = 13,
	EXTI3_IRQn = 14,
	EXTI4_IRQn = 15,
	EXTI5_IRQn = 16,
	EXTI6_IRQn = 17,
	EXTI7_IRQn = 18,
	EXTI8_IRQn = 19,
	EXTI9_IRQn = 20,
	EXTI10_IRQn = 21,
	EXTI11_IRQn = 22,
	EXTI12_IRQn = 23,
	EXTI13_IRQn = 24,
	EXTI14_IRQn = 25,
	EXTI15_IRQn = 26,
	DMAMUX1_IRQn = 27,
	DMAMUX1_S_IRQn = 28,
	DMA1_Channel1_IRQn = 29,
	DMA1_Channel2_IRQn = 30,
	DMA1_Channel3_IRQn = 31,
	DMA1_Channel4_IRQn = 32,
	DMA1_Channel5_IRQn = 33,
	DMA1_Channel6_IRQn = 34,
	DMA1_Channel7_IRQn = 35,
	DMA1_Channel8_IRQn = 36,
	ADC1_2_IRQn = 37,
	DAC_IRQn = 38,
	FDCAN1_IT0_IRQn = 39,
	FDCAN1_IT1_IRQn = 40,
	TIM1_BRK_IRQn = 41,
	TIM1_UP_IRQn = 42,
	TIM1_TRG_COM_IRQn = 43,
	TIM1_CC_IRQn = 44,
	TIM2_IRQn = 45,
	TIM3_IRQn = 46,
	TIM4_IRQn = 47,
	TIM5_IRQn = 48,
	TIM6_IRQn = 49,
	TIM7_IRQn = 50,
	TIM8_BRK_IRQn = 51,
	TIM8_UP_IRQn = 52,
	TIM8_TRG_COM_IRQn = 53,
	TIM8_CC_IRQn = 54,
	I2C1_EV_IRQn = 55,
	I2C1_ER_IRQn = 56,
	I2C2_EV_IRQn = 57,
	I2C2_ER_IRQn = 58,
	SPI1_IRQn = 59,
	SPI2_IRQn = 60,
	USART1_IRQn = 61,
	USART2_IRQn = 62,
	USART3_IRQn = 63,
	UART4_IRQn = 64,
	UART5_IRQn = 65,
	LPUART1_IRQn = 66,
	LPTIM1_IRQn = 67,
	LPTIM2_IRQn = 68,
	TIM15_IRQn = 69,
	TIM16_IRQn = 70,
	TIM17_IRQn = 71,
	COMP_IRQn = 72,
	USB_FS_IRQn = 73,
	CRS_IRQn = 74,
	FMC_IRQn = 75,
	OCTOSPI1_IRQn = 76,
	SDMMC1_IRQn = 78,
	DMA2_Channel1_IRQn = 80,
	DMA2_Channel2_IRQn = 81,
	DMA2_Channel3_IRQn = 82,
	DMA2_Channel4_IRQn = 83,
	DMA2_Channel5_IRQn = 84,
	DMA2_Channel6_IRQn = 85,
	DMA2_Channel7_IRQn = 86,
	DMA2_Channel8_IRQn = 87,
	I2C3_EV_IRQn = 88,
	I2C3_ER_IRQn = 89,
	SAI1_IRQn = 90,
	TSC_IRQn = 92,
	RNG_IRQn = 94,
	FPU_IRQn = 95,
	HASH_IRQn = 96,
	LPTIM3_IRQn = 98,
	SPI3_IRQn = 99,
	I2C4_EV_IRQn = 100,
	I2C4_ER_IRQn = 101,
	DFSDM1_FLT0_IRQn = 102,
	DFSDM1_FLT1_IRQn = 103,
	DFSDM1_FLT2_IRQn = 104,
	DFSDM1_FLT3_IRQn = 105,
	UCPD1_IRQn = 106,
	ICACHE_IRQn = 107,
#endif
	NonMaskableInt_IRQn = -14,
	PendSV_IRQn = -2,
	SysTick_IRQn = -1,
	WWDG_IRQn = 0,
#if defined(STM32F0      ) || defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32G0      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L0      ) || \
    defined(STM32L4      ) || defined(STM32L5      ) || defined(STM32WB      )
	HardFault_IRQn = -13,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || \
    defined(STM32L4      ) || defined(STM32L5      ) || defined(STM32WB      )
	MemoryManagement_IRQn = -12,
	BusFault_IRQn = -11,
	UsageFault_IRQn = -10,
	DebugMonitor_IRQn = -4,
#endif
#if defined(STM32F0      ) || defined(STM32G0      ) || defined(STM32L0      ) || defined(STM32L1      )
	SVC_IRQn = -5,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L4      ) || \
    defined(STM32L5      ) || defined(STM32WB      )
	SVCall_IRQn = -5,
#endif
#if defined(STM32H723xx  ) || defined(STM32H730xx  ) || defined(STM32H742xx  ) || defined(STM32H743xx  ) || \
    defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H750xx  ) || defined(STM32H753xx  ) || \
    defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	PVD_AVD_IRQn = 1,
	ADC3_IRQn = 127,
	BDMA_Channel0_IRQn = 129,
	BDMA_Channel1_IRQn = 130,
	BDMA_Channel2_IRQn = 131,
	BDMA_Channel3_IRQn = 132,
	BDMA_Channel4_IRQn = 133,
	BDMA_Channel5_IRQn = 134,
	BDMA_Channel6_IRQn = 135,
	BDMA_Channel7_IRQn = 136,
	LPTIM4_IRQn = 140,
	LPTIM5_IRQn = 141,
	SAI4_IRQn = 146,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32L1      ) || \
    defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F334x8  ) || \
    defined(STM32F373xC  ) || defined(STM32G031xx  ) || defined(STM32G041xx  ) || defined(STM32G071xx  ) || \
    defined(STM32G081xx  ) || defined(STM32L011xx  ) || defined(STM32L051xx  ) || defined(STM32L052xx  ) || \
    defined(STM32L053xx  ) || defined(STM32L062xx  ) || defined(STM32L063xx  ) || defined(STM32L082xx  )
	PVD_IRQn = 1,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32L4      ) || defined(STM32L5      ) || \
    defined(STM32WB      ) || defined(STM32H7A3xxQ ) || defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	PVD_PVM_IRQn = 1,
#endif
#if defined(STM32F042x6  ) || defined(STM32F071xB  )
	PVD_VDDIO2_IRQn = 1,
	CEC_CAN_IRQn = 30,
#endif
#if defined(STM32F0      ) || defined(STM32L0      ) || defined(STM32L5      )
	RTC_IRQn = 2,
#endif
#if defined(STM32G0      )
	RTC_TAMP_IRQn = 2,
#endif
#if defined(STM32G4      ) || defined(STM32GB      )
	RTC_TAMP_LSECSS_IRQn = 2,
	FDCAN1_IT0_IRQn = 21,
	FDCAN1_IT1_IRQn = 22,
	LPTIM1_IRQn = 49,
	UCPD1_IRQn = 63,
	CRS_IRQn = 75,
	SAI1_IRQn = 76,
	RNG_IRQn = 90,
	LPUART1_IRQn = 91,
	I2C3_EV_IRQn = 92,
	I2C3_ER_IRQn = 93,
	DMAMUX_OVR_IRQn = 94,
	DMA2_Channel6_IRQn = 97,
	CORDIC_IRQn = 100,
	FMAC_IRQn = 101,
#endif
#if defined(STM32H7A3xxQ ) || defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	RTC_TAMP_STAMP_CSS_LSE_IRQn = 2,
	DFSDM2_IRQn = 42,
	DFSDM1_FLT4_IRQn = 64,
	DFSDM1_FLT5_IRQn = 65,
	DFSDM1_FLT6_IRQn = 66,
	DFSDM1_FLT7_IRQn = 67,
	DAC2_IRQn = 127,
	BDMA2_Channel0_IRQn = 129,
	BDMA2_Channel1_IRQn = 130,
	BDMA2_Channel2_IRQn = 131,
	BDMA2_Channel3_IRQn = 132,
	BDMA2_Channel4_IRQn = 133,
	BDMA2_Channel5_IRQn = 134,
	BDMA2_Channel6_IRQn = 135,
	BDMA2_Channel7_IRQn = 136,
	UART9_IRQn = 140,
	USART10_IRQn = 141,
	GFXMMU_IRQn = 153,
	BDMA1_IRQn = 154,
#endif
#if defined(STM32L1      )
	TAMPER_STAMP_IRQn = 2,
	DAC_IRQn = 21,
	TIM9_IRQn = 25,
	TIM10_IRQn = 26,
	TIM11_IRQn = 27,
	USB_FS_WKUP_IRQn = 42,
	TIM6_IRQn = 43,
	TIM7_IRQn = 44,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || \
    defined(STM32L4      ) || defined(STM32H723xx  ) || defined(STM32H730xx  ) || defined(STM32H742xx  ) || \
    defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H750xx  ) || \
    defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	TAMP_STAMP_IRQn = 2,
#endif
#if defined(STM32WB      )
	TAMP_STAMP_LSECSS_IRQn = 2,
	C2SEV_PWR_C2H_IRQn = 21,
	PKA_IRQn = 29,
	I2C1_EV_IRQn = 30,
	I2C1_ER_IRQn = 31,
	SPI1_IRQn = 34,
	USART1_IRQn = 36,
	TSC_IRQn = 39,
	PWR_SOTF_BLEACT_802ACT_RFPHASE_IRQn = 43,
	IPCC_C1_RX_IRQn = 44,
	IPCC_C1_TX_IRQn = 45,
	HSEM_IRQn = 46,
	LPTIM1_IRQn = 47,
	LPTIM2_IRQn = 48,
	AES2_IRQn = 52,
	RNG_IRQn = 53,
	FPU_IRQn = 54,
	DMAMUX1_OVR_IRQn = 62,
#endif
#if defined(STM32F0      ) || defined(STM32G0      ) || defined(STM32L0      )
	FLASH_IRQn = 3,
	EXTI0_1_IRQn = 5,
	EXTI2_3_IRQn = 6,
	EXTI4_15_IRQn = 7,
	DMA1_Channel1_IRQn = 9,
	DMA1_Channel2_3_IRQn = 10,
	I2C1_IRQn = 23,
	SPI1_IRQn = 25,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || \
    defined(STM32L4      ) || defined(STM32WB      )
	RTC_WKUP_IRQn = 3,
	FLASH_IRQn = 4,
	RCC_IRQn = 5,
	EXTI0_IRQn = 6,
	EXTI1_IRQn = 7,
	EXTI3_IRQn = 9,
	EXTI4_IRQn = 10,
	EXTI9_5_IRQn = 23,
	EXTI15_10_IRQn = 40,
	RTC_Alarm_IRQn = 41,
#endif
#if defined(STM32F042x6  ) || defined(STM32F071xB  ) || defined(STM32L052xx  ) || defined(STM32L053xx  ) || \
    defined(STM32L062xx  ) || defined(STM32L063xx  ) || defined(STM32L082xx  )
	RCC_CRS_IRQn = 4,
	TSC_IRQn = 8,
#endif
#if defined(STM32G0      ) || defined(STM32F030xC  ) || defined(STM32F038xx  ) || defined(STM32L010x8  ) || \
    defined(STM32L011xx  ) || defined(STM32L051xx  )
	RCC_IRQn = 4,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32L4      ) || \
    defined(STM32WB      )
	EXTI2_IRQn = 8,
#endif
#if defined(STM32F3      )
	EXTI2_TSC_IRQn = 8,
	CAN_RX1_IRQn = 21,
	CAN_SCE_IRQn = 22,
#endif
#if defined(STM32G071xx  ) || defined(STM32G081xx  )
	UCPD1_2_IRQn = 8,
	TIM6_DAC_LPTIM1_IRQn = 17,
	TIM7_LPTIM2_IRQn = 18,
	USART3_4_LPUART1_IRQn = 29,
	CEC_IRQn = 30,
#endif
#if defined(STM32G030xx  ) || defined(STM32G031xx  ) || defined(STM32G041xx  )
	DMA1_Ch4_5_DMAMUX1_OVR_IRQn = 11,
#endif
#if defined(STM32G070xx  ) || defined(STM32G071xx  ) || defined(STM32G081xx  )
	DMA1_Ch4_7_DMAMUX1_OVR_IRQn = 11,
#endif
#if defined(STM32F3      ) || defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32L1      ) || \
    defined(STM32L4      ) || defined(STM32WB      )
	DMA1_Channel1_IRQn = 11,
	DMA1_Channel2_IRQn = 12,
	DMA1_Channel3_IRQn = 13,
	DMA1_Channel4_IRQn = 14,
	DMA1_Channel5_IRQn = 15,
	DMA1_Channel6_IRQn = 16,
#endif
#if defined(STM32F071xB  ) || defined(STM32L010x8  ) || defined(STM32L051xx  ) || defined(STM32L052xx  ) || \
    defined(STM32L053xx  ) || defined(STM32L062xx  ) || defined(STM32L063xx  ) || defined(STM32L082xx  )
	DMA1_Channel4_5_6_7_IRQn = 11,
#endif
#if defined(STM32F030xC  ) || defined(STM32F038xx  ) || defined(STM32F042x6  ) || defined(STM32L011xx  )
	DMA1_Channel4_5_IRQn = 11,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32H7      )
	DMA1_Stream0_IRQn = 11,
	DMA1_Stream1_IRQn = 12,
	DMA1_Stream2_IRQn = 13,
	DMA1_Stream3_IRQn = 14,
	DMA1_Stream4_IRQn = 15,
	DMA1_Stream5_IRQn = 16,
	DMA1_Stream6_IRQn = 17,
	ADC_IRQn = 18,
	DMA1_Stream7_IRQn = 47,
	DMA2_Stream0_IRQn = 56,
	DMA2_Stream1_IRQn = 57,
	DMA2_Stream2_IRQn = 58,
	DMA2_Stream3_IRQn = 59,
	DMA2_Stream4_IRQn = 60,
	DMA2_Stream5_IRQn = 68,
	DMA2_Stream6_IRQn = 69,
	DMA2_Stream7_IRQn = 70,
#endif
#if defined(STM32F071xB  ) || defined(STM32G071xx  ) || defined(STM32G081xx  ) || defined(STM32L011xx  ) || \
    defined(STM32L051xx  ) || defined(STM32L052xx  ) || defined(STM32L053xx  ) || defined(STM32L062xx  ) || \
    defined(STM32L063xx  ) || defined(STM32L082xx  )
	ADC1_COMP_IRQn = 12,
#endif
#if defined(STM32F030xC  ) || defined(STM32F038xx  ) || defined(STM32F042x6  ) || defined(STM32G030xx  ) || \
    defined(STM32G031xx  ) || defined(STM32G041xx  ) || defined(STM32G070xx  ) || defined(STM32L010x8  )
	ADC1_IRQn = 12,
#endif
#if defined(STM32L0      )
	LPTIM1_IRQn = 13,
	TIM21_IRQn = 20,
#endif
#if defined(STM32F0      ) || defined(STM32G0      )
	TIM1_BRK_UP_TRG_COM_IRQn = 13,
	TIM1_CC_IRQn = 14,
	TIM14_IRQn = 19,
	TIM16_IRQn = 21,
	TIM17_IRQn = 22,
#endif
#if defined(STM32L082xx  )
	USART4_5_IRQn = 14,
	I2C3_IRQn = 21,
#endif
#if defined(STM32L0      ) || defined(STM32F038xx  ) || defined(STM32F042x6  ) || defined(STM32F071xB  ) || \
    defined(STM32G031xx  ) || defined(STM32G041xx  ) || defined(STM32G071xx  ) || defined(STM32G081xx  )
	TIM2_IRQn = 15,
#endif
#if defined(STM32F0      ) || defined(STM32G0      ) || defined(STM32L082xx  )
	TIM3_IRQn = 16,
#endif
#if defined(STM32F3      ) || defined(STM32L1      ) || defined(STM32L4      ) || defined(STM32WB      ) || \
    defined(STM32G471xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  )
	DMA1_Channel7_IRQn = 17,
#endif
#if defined(STM32G031xx  ) || defined(STM32G041xx  )
	LPTIM1_IRQn = 17,
	LPTIM2_IRQn = 18,
#endif
#if defined(STM32F071xB  ) || defined(STM32L052xx  ) || defined(STM32L053xx  ) || defined(STM32L062xx  ) || \
    defined(STM32L063xx  ) || defined(STM32L082xx  )
	TIM6_DAC_IRQn = 17,
#endif
#if defined(STM32F030xC  ) || defined(STM32G070xx  ) || defined(STM32L051xx  )
	TIM6_IRQn = 17,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32F302xE  ) || defined(STM32F303x8  ) || \
    defined(STM32F328xx  ) || defined(STM32F334x8  ) || defined(STM32F358xx  ) || defined(STM32L412xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  )
	ADC1_2_IRQn = 18,
#endif
#if defined(STM32L1      ) || defined(STM32WB      ) || defined(STM32F302x8  ) || defined(STM32F373xC  ) || \
    defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  ) || defined(STM32L4R5xx  ) || \
    defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	ADC1_IRQn = 18,
#endif
#if defined(STM32F030xC  ) || defined(STM32F071xB  ) || defined(STM32G070xx  ) || defined(STM32L082xx  )
	TIM7_IRQn = 18,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32F407xx  ) || defined(STM32F412Zx  ) || \
    defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || \
    defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || \
    defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  ) || defined(STM32L475xx  ) || \
    defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || \
    defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	CAN1_TX_IRQn = 19,
	CAN1_RX0_IRQn = 20,
	CAN1_RX1_IRQn = 21,
	CAN1_SCE_IRQn = 22,
#endif
#if defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  ) || defined(STM32F358xx  ) || \
    defined(STM32F373xC  )
	CAN_TX_IRQn = 19,
	CAN_RX0_IRQn = 20,
#endif
#if defined(STM32H7      )
	FDCAN1_IT0_IRQn = 19,
	FDCAN2_IT0_IRQn = 20,
	FDCAN1_IT1_IRQn = 21,
	FDCAN2_IT1_IRQn = 22,
	FDCAN_CAL_IRQn = 63,
	DMAMUX1_OVR_IRQn = 102,
	DFSDM1_FLT0_IRQn = 110,
	DFSDM1_FLT1_IRQn = 111,
	DFSDM1_FLT2_IRQn = 112,
	DFSDM1_FLT3_IRQn = 113,
	SWPMI1_IRQn = 115,
	TIM15_IRQn = 116,
	TIM16_IRQn = 117,
	TIM17_IRQn = 118,
	MDIOS_WKUP_IRQn = 119,
	MDIOS_IRQn = 120,
	MDMA_IRQn = 122,
	SDMMC2_IRQn = 124,
	HSEM1_IRQn = 125,
	DMAMUX2_OVR_IRQn = 128,
	COMP_IRQn = 137,
	LPTIM2_IRQn = 138,
	LPTIM3_IRQn = 139,
	LPUART1_IRQn = 142,
	CRS_IRQn = 144,
	ECC_IRQn = 145,
	WAKEUP_PIN_IRQn = 149,
#endif
#if defined(STM32F302x8  ) || defined(STM32F302xE  )
	USB_HP_CAN_TX_IRQn = 19,
	USB_LP_CAN_RX0_IRQn = 20,
	USBWakeUp_RMP_IRQn = 76,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32L1      ) || defined(STM32WB35xx  ) || \
    defined(STM32WB55xx  )
	USB_HP_IRQn = 19,
	USB_LP_IRQn = 20,
#endif
#if defined(STM32F030xC  ) || defined(STM32F071xB  ) || defined(STM32G070xx  ) || defined(STM32G071xx  ) || \
    defined(STM32G081xx  )
	TIM15_IRQn = 20,
#endif
#if defined(STM32L1      ) || defined(STM32WB35xx  ) || defined(STM32WB55xx  )
	COMP_IRQn = 22,
#endif
#if defined(STM32L051xx  ) || defined(STM32L052xx  ) || defined(STM32L053xx  ) || defined(STM32L062xx  ) || \
    defined(STM32L063xx  ) || defined(STM32L082xx  )
	TIM22_IRQn = 22,
#endif
#if defined(STM32G0      ) || defined(STM32F030xC  ) || defined(STM32F071xB  ) || defined(STM32L051xx  ) || \
    defined(STM32L052xx  ) || defined(STM32L053xx  ) || defined(STM32L062xx  ) || defined(STM32L063xx  ) || \
    defined(STM32L082xx  )
	I2C2_IRQn = 24,
#endif
#if defined(STM32L100xB  )
	LCD_IRQn = 24,
#endif
#if defined(STM32F373xC  )
	TIM15_IRQn = 24,
	TIM16_IRQn = 25,
	TIM17_IRQn = 26,
	TIM18_DAC2_IRQn = 27,
	CEC_IRQn = 42,
	TIM12_IRQn = 43,
	TIM13_IRQn = 44,
	TIM14_IRQn = 45,
	SDADC1_IRQn = 61,
	SDADC2_IRQn = 62,
	SDADC3_IRQn = 63,
	USBWakeUp_IRQn = 76,
	TIM19_IRQn = 78,
#endif
#if defined(STM32H7      ) || defined(STM32WB      )
	TIM1_BRK_IRQn = 24,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32L4      ) || defined(STM32F302x8  ) || \
    defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  ) || \
    defined(STM32F358xx  )
	TIM1_BRK_TIM15_IRQn = 24,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      )
	TIM1_BRK_TIM9_IRQn = 24,
	TIM1_TRG_COM_TIM11_IRQn = 26,
#endif
#if defined(STM32H7      ) || defined(STM32F410Tx  )
	TIM1_UP_IRQn = 25,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || \
    defined(STM32F411xE  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  )
	TIM1_UP_TIM10_IRQn = 25,
	OTG_FS_WKUP_IRQn = 42,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32L4      ) || defined(STM32WB      ) || \
    defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || \
    defined(STM32F334x8  ) || defined(STM32F358xx  )
	TIM1_UP_TIM16_IRQn = 25,
#endif
#if defined(STM32G0      ) || defined(STM32F030xC  ) || defined(STM32F042x6  ) || defined(STM32F071xB  ) || \
    defined(STM32L051xx  ) || defined(STM32L052xx  ) || defined(STM32L053xx  ) || defined(STM32L062xx  ) || \
    defined(STM32L063xx  ) || defined(STM32L082xx  )
	SPI2_IRQn = 26,
#endif
#if defined(STM32H7      ) || defined(STM32L412xx  ) || defined(STM32L431xx  ) || defined(STM32L443xx  ) || \
    defined(STM32L462xx  )
	TIM1_TRG_COM_IRQn = 26,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32WB      ) || defined(STM32F302x8  ) || \
    defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  ) || \
    defined(STM32F358xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM1_TRG_COM_TIM17_IRQn = 26,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L4      ) || defined(STM32WB      ) || \
    defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || \
    defined(STM32F334x8  ) || defined(STM32F358xx  )
	TIM1_CC_IRQn = 27,
#endif
#if defined(STM32F0      ) || defined(STM32G0      ) || defined(STM32L051xx  ) || defined(STM32L052xx  ) || \
    defined(STM32L053xx  ) || defined(STM32L062xx  ) || defined(STM32L063xx  ) || defined(STM32L082xx  )
	USART1_IRQn = 27,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32L4      ) || \
    defined(STM32WB      ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || defined(STM32F411xE  ) || \
    defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  )
	TIM2_IRQn = 28,
#endif
#if defined(STM32G0      ) || defined(STM32L0      ) || defined(STM32F030xC  ) || defined(STM32F042x6  ) || \
    defined(STM32F071xB  )
	USART2_IRQn = 28,
#endif
#if defined(STM32L062xx  ) || defined(STM32L063xx  ) || defined(STM32L082xx  )
	AES_RNG_LPUART1_IRQn = 29,
#endif
#if defined(STM32G031xx  ) || defined(STM32G041xx  ) || defined(STM32L010x8  ) || defined(STM32L011xx  ) || \
    defined(STM32L051xx  )
	LPUART1_IRQn = 29,
#endif
#if defined(STM32L052xx  ) || defined(STM32L053xx  )
	RNG_LPUART1_IRQn = 29,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32F302xE  ) || defined(STM32F303x8  ) || \
    defined(STM32F328xx  ) || defined(STM32F334x8  ) || defined(STM32F358xx  ) || defined(STM32F373xC  ) || \
    defined(STM32F401xE  ) || defined(STM32F407xx  ) || defined(STM32F411xE  ) || defined(STM32F412Zx  ) || \
    defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || \
    defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || \
    defined(STM32L462xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM3_IRQn = 29,
#endif
#if defined(STM32F071xB  ) || defined(STM32G070xx  )
	USART3_4_IRQn = 29,
#endif
#if defined(STM32F030xC  )
	USART3_6_IRQn = 29,
#endif
#if defined(STM32L053xx  ) || defined(STM32L063xx  )
	LCD_IRQn = 30,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32F302xE  ) || defined(STM32F358xx  ) || \
    defined(STM32F373xC  ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || defined(STM32F411xE  ) || \
    defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM4_IRQn = 30,
#endif
#if defined(STM32G041xx  ) || defined(STM32G081xx  )
	AES_RNG_IRQn = 31,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || \
    defined(STM32L4      )
	I2C1_EV_IRQn = 31,
	I2C1_ER_IRQn = 32,
	USART1_IRQn = 37,
	USART2_IRQn = 38,
#endif
#if defined(STM32F042x6  ) || defined(STM32L052xx  ) || defined(STM32L053xx  ) || defined(STM32L062xx  ) || \
    defined(STM32L063xx  ) || defined(STM32L082xx  )
	USB_IRQn = 31,
#endif
#if defined(STM32WB35xx  ) || defined(STM32WB55xx  )
	I2C3_EV_IRQn = 32,
	I2C3_ER_IRQn = 33,
	SPI2_IRQn = 35,
	LPUART1_IRQn = 37,
	CRS_IRQn = 42,
	QUADSPI_IRQn = 50,
	AES1_IRQn = 51,
	DMA2_Channel1_IRQn = 55,
	DMA2_Channel2_IRQn = 56,
	DMA2_Channel3_IRQn = 57,
	DMA2_Channel4_IRQn = 58,
	DMA2_Channel5_IRQn = 59,
	DMA2_Channel6_IRQn = 60,
	DMA2_Channel7_IRQn = 61,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32L4      ) || \
    defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F358xx  ) || defined(STM32F373xC  )
	I2C2_EV_IRQn = 33,
	I2C2_ER_IRQn = 34,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32L4      ) || \
    defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  ) || \
    defined(STM32F358xx  ) || defined(STM32F373xC  )
	SPI1_IRQn = 35,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32L4      ) || defined(STM32F302x8  ) || \
    defined(STM32F302xE  ) || defined(STM32F358xx  ) || defined(STM32F373xC  ) || defined(STM32F401xE  ) || \
    defined(STM32F407xx  ) || defined(STM32F411xE  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || \
    defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  )
	SPI2_IRQn = 36,
#endif
#if defined(STM32WB55xx  )
	SAI1_IRQn = 38,
	LCD_IRQn = 49,
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || defined(STM32L4      ) || \
    defined(STM32F407xx  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  )
	USART3_IRQn = 39,
#endif
#if defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || \
    defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	DFSDM1_FLT3_IRQn = 42,
	DFSDM1_FLT2_IRQn = 63,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32F302x8  ) || defined(STM32F302xE  )
	USBWakeUp_IRQn = 42,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32F358xx  ) || defined(STM32L475xx  ) || \
    defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || \
    defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	TIM8_BRK_IRQn = 43,
	TIM8_UP_IRQn = 44,
	TIM8_TRG_COM_IRQn = 45,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F407xx  ) || \
    defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  )
	TIM8_BRK_TIM12_IRQn = 43,
	TIM8_UP_TIM13_IRQn = 44,
	TIM8_TRG_COM_TIM14_IRQn = 45,
#endif
#if defined(STM32L151xE  )
	TIM5_IRQn = 46,
	SPI3_IRQn = 47,
	UART4_IRQn = 48,
	UART5_IRQn = 49,
	DMA2_Channel1_IRQn = 50,
	DMA2_Channel2_IRQn = 51,
	DMA2_Channel3_IRQn = 52,
	DMA2_Channel4_IRQn = 53,
	DMA2_Channel5_IRQn = 54,
	COMP_ACQ_IRQn = 56,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32H7      ) || defined(STM32F358xx  ) || defined(STM32F407xx  ) || defined(STM32F412Zx  ) || \
    defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || \
    defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || \
    defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM8_CC_IRQn = 46,
#endif
#if defined(STM32F358xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  )
	ADC3_IRQn = 47,
#endif
#if defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  )
	SDMMC2_IRQn = 47,
	DCMI_PSSI_IRQn = 85,
#endif
#if defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F302xE  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || \
    defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	FMC_IRQn = 48,
#endif
#if defined(STM32F2      ) || defined(STM32F407xx  ) || defined(STM32F417xx  )
	FSMC_IRQn = 48,
#endif
#if defined(STM32F2      ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || defined(STM32F411xE  ) || \
    defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  )
	SDIO_IRQn = 49,
#endif
#if defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32L431xx  ) || defined(STM32L443xx  ) || \
    defined(STM32L462xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	SDMMC1_IRQn = 49,
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32H7      ) || \
    defined(STM32F373xC  ) || defined(STM32G471xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || \
    defined(STM32G484xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM5_IRQn = 50,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32H7      ) || defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F358xx  ) || \
    defined(STM32F373xC  ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || defined(STM32F411xE  ) || \
    defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || \
    defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	SPI3_IRQn = 51,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32H7      ) || \
    defined(STM32F302xE  ) || defined(STM32F358xx  ) || defined(STM32F407xx  ) || defined(STM32F417xx  ) || \
    defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || defined(STM32L462xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || \
    defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	UART4_IRQn = 52,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F302xE  ) || \
    defined(STM32F358xx  ) || defined(STM32F407xx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  ) || defined(STM32G471xx  ) || defined(STM32G473xx  ) || \
    defined(STM32G474xx  ) || defined(STM32G484xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || \
    defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || \
    defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	UART5_IRQn = 53,
#endif
#if defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  ) || defined(STM32F373xC  )
	TIM6_DAC1_IRQn = 54,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32H7      ) || defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F358xx  ) || \
    defined(STM32F407xx  ) || defined(STM32F410Tx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  ) || defined(STM32L431xx  ) || defined(STM32L443xx  ) || \
    defined(STM32L462xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM6_DAC_IRQn = 54,
#endif
#if defined(STM32F412Zx  ) || defined(STM32L412xx  )
	TIM6_IRQn = 54,
#endif
#if defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  )
	TIM7_DAC2_IRQn = 55,
#endif
#if defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  )
	TIM7_DAC_IRQn = 55,
	ADC5_IRQn = 62,
	TIM20_BRK_IRQn = 77,
	TIM20_UP_IRQn = 78,
	TIM20_TRG_COM_IRQn = 79,
	TIM20_CC_IRQn = 80,
	FDCAN3_IT0_IRQn = 88,
	FDCAN3_IT1_IRQn = 89,
	QUADSPI_IRQn = 95,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32GB      ) || defined(STM32H7      ) || \
    defined(STM32F358xx  ) || defined(STM32F373xC  ) || defined(STM32F407xx  ) || defined(STM32F412Zx  ) || \
    defined(STM32F417xx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || \
    defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || \
    defined(STM32G431xx  ) || defined(STM32G441xx  ) || defined(STM32G471xx  ) || defined(STM32L431xx  ) || \
    defined(STM32L443xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	TIM7_IRQn = 55,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32L4      ) || defined(STM32F302xE  ) || \
    defined(STM32F358xx  ) || defined(STM32F373xC  )
	DMA2_Channel1_IRQn = 56,
	DMA2_Channel2_IRQn = 57,
	DMA2_Channel3_IRQn = 58,
	DMA2_Channel4_IRQn = 59,
	DMA2_Channel5_IRQn = 60,
#endif
#if defined(STM32F358xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  )
	ADC4_IRQn = 61,
	COMP4_5_6_IRQn = 65,
	COMP7_IRQn = 66,
#endif
#if defined(STM32F412Zx  ) || defined(STM32F423xx  ) || defined(STM32L462xx  ) || defined(STM32L475xx  ) || \
    defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || \
    defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	DFSDM1_FLT0_IRQn = 61,
	DFSDM1_FLT1_IRQn = 62,
#endif
#if defined(STM32F7      ) || defined(STM32F207xx  ) || defined(STM32F407xx  ) || defined(STM32F417xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F479xx  ) || defined(STM32H723xx  ) || defined(STM32H730xx  ) || defined(STM32H742xx  ) || \
    defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H750xx  ) || \
    defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	ETH_IRQn = 61,
	ETH_WKUP_IRQn = 62,
#endif
#if defined(STM32F2      ) || defined(STM32F407xx  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || \
    defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || defined(STM32F746xx  ) || \
    defined(STM32F750xx  ) || defined(STM32F765xx  ) || defined(STM32F769xx  ) || defined(STM32F777xx  )
	CAN2_TX_IRQn = 63,
	CAN2_RX0_IRQn = 64,
	CAN2_RX1_IRQn = 65,
	CAN2_SCE_IRQn = 66,
#endif
#if defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	CM7_SEV_IRQn = 64,
	CM4_SEV_IRQn = 65,
	HSEM2_IRQn = 126,
	HOLD_CORE_IRQn = 148,
#endif
#if defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32F358xx  )
	COMP1_2_3_IRQn = 64,
#endif
#if defined(STM32F302xE  )
	COMP1_2_IRQn = 64,
#endif
#if defined(STM32F302x8  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || defined(STM32F334x8  )
	COMP2_IRQn = 64,
#endif
#if defined(STM32L4      ) || defined(STM32F373xC  )
	COMP_IRQn = 64,
#endif
#if defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || \
    defined(STM32F334x8  )
	COMP4_6_IRQn = 65,
#endif
#if defined(STM32GB      ) || defined(STM32G431xx  ) || defined(STM32G441xx  ) || defined(STM32G471xx  )
	COMP4_IRQn = 65,
#endif
#if defined(STM32L4      )
	LPTIM1_IRQn = 65,
	LPTIM2_IRQn = 66,
	DMA2_Channel6_IRQn = 68,
	DMA2_Channel7_IRQn = 69,
	LPUART1_IRQn = 70,
	TSC_IRQn = 77,
#endif
#if defined(STM32F334x8  ) || defined(STM32G474xx  ) || defined(STM32G484xx  )
	HRTIM1_Master_IRQn = 67,
	HRTIM1_TIMA_IRQn = 68,
	HRTIM1_TIMB_IRQn = 69,
	HRTIM1_TIMC_IRQn = 70,
	HRTIM1_TIMD_IRQn = 71,
	HRTIM1_TIME_IRQn = 72,
	HRTIM1_FLT_IRQn = 73,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || \
    defined(STM32F411xE  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  ) || \
    defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || \
    defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	OTG_FS_IRQn = 67,
#endif
#if defined(STM32L412xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  )
	USB_IRQn = 67,
#endif
#if defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || \
    defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	OCTOSPI1_IRQn = 71,
	OCTOSPI2_IRQn = 76,
	I2C4_EV_IRQn = 84,
	DMAMUX1_OVR_IRQn = 94,
#endif
#if defined(STM32L412xx  ) || defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  ) || \
    defined(STM32L475xx  ) || defined(STM32L476xx  )
	QUADSPI_IRQn = 71,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F401xE  ) || \
    defined(STM32F407xx  ) || defined(STM32F411xE  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || \
    defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  )
	USART6_IRQn = 71,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32L4      ) || \
    defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F401xE  ) || defined(STM32F407xx  ) || \
    defined(STM32F411xE  ) || defined(STM32F412Zx  ) || defined(STM32F417xx  ) || defined(STM32F423xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  )
	I2C3_EV_IRQn = 72,
	I2C3_ER_IRQn = 73,
#endif
#if defined(STM32F423xx  )
	CAN3_TX_IRQn = 74,
	CAN3_RX0_IRQn = 75,
	CAN3_RX1_IRQn = 76,
	CAN3_SCE_IRQn = 77,
	UART9_IRQn = 88,
	UART10_IRQn = 89,
	DFSDM2_FLT0_IRQn = 98,
	DFSDM2_FLT1_IRQn = 99,
	DFSDM2_FLT2_IRQn = 100,
	DFSDM2_FLT3_IRQn = 101,
#endif
#if defined(STM32G474xx  ) || defined(STM32G484xx  )
	HRTIM1_TIMF_IRQn = 74,
#endif
#if defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F407xx  ) || \
    defined(STM32F417xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  )
	OTG_HS_EP1_OUT_IRQn = 74,
	OTG_HS_EP1_IN_IRQn = 75,
	OTG_HS_WKUP_IRQn = 76,
	OTG_HS_IRQn = 77,
#endif
#if defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  ) || defined(STM32L475xx  ) || \
    defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || \
    defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	SAI1_IRQn = 74,
#endif
#if defined(STM32F302x8  ) || defined(STM32F302xE  ) || defined(STM32F373xC  )
	USB_HP_IRQn = 74,
	USB_LP_IRQn = 75,
#endif
#if defined(STM32L475xx  ) || defined(STM32L476xx  ) || defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || \
    defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	SAI2_IRQn = 75,
#endif
#if defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L475xx  ) || defined(STM32L476xx  )
	SWPMI1_IRQn = 76,
#endif
#if defined(STM32F207xx  ) || defined(STM32F407xx  ) || defined(STM32F417xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32F746xx  ) || defined(STM32F750xx  ) || defined(STM32F765xx  ) || \
    defined(STM32F769xx  ) || defined(STM32F777xx  ) || defined(STM32H742xx  ) || defined(STM32H743xx  ) || \
    defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H750xx  ) || defined(STM32H753xx  ) || \
    defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	DCMI_IRQn = 78,
#endif
#if defined(STM32H723xx  ) || defined(STM32H730xx  ) || defined(STM32H7A3xxQ ) || defined(STM32H7B0xxQ ) || \
    defined(STM32H7B3xx  )
	DCMI_PSSI_IRQn = 78,
	OCTOSPI1_IRQn = 92,
	DTS_IRQn = 147,
	OCTOSPI2_IRQn = 150,
#endif
#if defined(STM32L4R9xx  ) || defined(STM32L4S9xx  )
	DSI_IRQn = 78,
#endif
#if defined(STM32L443xx  ) || defined(STM32L476xx  )
	LCD_IRQn = 78,
#endif
#if defined(STM32F423xx  ) || defined(STM32F730xx  ) || defined(STM32F733xx  ) || defined(STM32L443xx  ) || \
    defined(STM32L462xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	AES_IRQn = 79,
#endif
#if defined(STM32F215xx  ) || defined(STM32F417xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F479xx  ) || defined(STM32F750xx  ) || defined(STM32F777xx  ) || defined(STM32H730xx  ) || \
    defined(STM32H750xx  ) || defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || \
    defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	CRYP_IRQn = 79,
#endif
#if defined(STM32F2      ) || defined(STM32F417xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || \
    defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F479xx  ) || defined(STM32F750xx  ) || \
    defined(STM32F777xx  ) || defined(STM32H730xx  ) || defined(STM32H750xx  ) || defined(STM32H753xx  ) || \
    defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	HASH_RNG_IRQn = 80,
#endif
#if defined(STM32L4      ) || defined(STM32F407xx  ) || defined(STM32F410Tx  ) || defined(STM32F412Zx  ) || \
    defined(STM32F423xx  ) || defined(STM32F722xx  ) || defined(STM32F730xx  ) || defined(STM32F733xx  ) || \
    defined(STM32F746xx  ) || defined(STM32F765xx  ) || defined(STM32F769xx  ) || defined(STM32H723xx  ) || \
    defined(STM32H742xx  ) || defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || \
    defined(STM32H7A3xxQ )
	RNG_IRQn = 80,
#endif
#if defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L4      )
	FPU_IRQn = 81,
#endif
#if defined(STM32L412xx  ) || defined(STM32L431xx  ) || defined(STM32L443xx  ) || defined(STM32L462xx  ) || \
    defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  )
	CRS_IRQn = 82,
#endif
#if defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || \
    defined(STM32L4S9xx  )
	HASH_CRS_IRQn = 82,
#endif
#if defined(STM32G471xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  )
	I2C4_EV_IRQn = 82,
	FDCAN2_IT0_IRQn = 86,
	FDCAN2_IT1_IRQn = 87,
	DMA1_Channel8_IRQn = 96,
	DMA2_Channel7_IRQn = 98,
	DMA2_Channel8_IRQn = 99,
#endif
#if defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F479xx  )
	UART7_IRQn = 82,
	UART8_IRQn = 83,
#endif
#if defined(STM32G471xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || defined(STM32G484xx  ) || \
    defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || \
    defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	I2C4_ER_IRQn = 83,
#endif
#if defined(STM32L462xx  )
	I2C4_EV_IRQn = 83,
	I2C4_ER_IRQn = 84,
#endif
#if defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F302xE  ) || defined(STM32F401xE  ) || \
    defined(STM32F411xE  ) || defined(STM32F412Zx  ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32G471xx  ) || defined(STM32G473xx  ) || defined(STM32G474xx  ) || \
    defined(STM32G484xx  )
	SPI4_IRQn = 84,
#endif
#if defined(STM32G441xx  ) || defined(STM32G484xx  )
	AES_IRQn = 85,
#endif
#if defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S5xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	DCMI_IRQn = 85,
#endif
#if defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F411xE  ) || defined(STM32F412Zx  ) || \
    defined(STM32F423xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F479xx  )
	SPI5_IRQn = 85,
#endif
#if defined(STM32L4Q5xx  )
	PKA_IRQn = 86,
#endif
#if defined(STM32H7      ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F479xx  ) || defined(STM32F746xx  ) || defined(STM32F750xx  ) || \
    defined(STM32F765xx  ) || defined(STM32F769xx  ) || defined(STM32F777xx  )
	SPI6_IRQn = 86,
#endif
#if defined(STM32F7      ) || defined(STM32H7      ) || defined(STM32F423xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  )
	SAI1_IRQn = 87,
#endif
#if defined(STM32F429xx  ) || defined(STM32F439xx  ) || defined(STM32F479xx  ) || defined(STM32F746xx  ) || \
    defined(STM32F750xx  ) || defined(STM32F769xx  ) || defined(STM32F777xx  ) || defined(STM32H723xx  ) || \
    defined(STM32H730xx  ) || defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || \
    defined(STM32H750xx  ) || defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || \
    defined(STM32H7A3xxQ ) || defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	LTDC_IRQn = 88,
	LTDC_ER_IRQn = 89,
#endif
#if defined(STM32H7      ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F479xx  ) || defined(STM32F746xx  ) || defined(STM32F750xx  ) || \
    defined(STM32F765xx  ) || defined(STM32F769xx  ) || defined(STM32F777xx  ) || defined(STM32L4P5xx  ) || \
    defined(STM32L4Q5xx  ) || defined(STM32L4R5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S5xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	DMA2D_IRQn = 90,
#endif
#if defined(STM32L4P5xx  ) || defined(STM32L4Q5xx  ) || defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || \
    defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	LTDC_IRQn = 91,
	LTDC_ER_IRQn = 92,
#endif
#if defined(STM32F479xx  )
	QUADSPI_IRQn = 91,
	DSI_IRQn = 92,
#endif
#if defined(STM32F7      ) || defined(STM32L5      ) || defined(STM32F446xx  ) || defined(STM32H742xx  ) || \
    defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H750xx  ) || \
    defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || defined(STM32H7A3xxQ ) || \
    defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	SAI2_IRQn = 91,
#endif
#if defined(STM32F7      ) || defined(STM32F412Zx  ) || defined(STM32F423xx  ) || defined(STM32F446xx  ) || \
    defined(STM32H742xx  ) || defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || \
    defined(STM32H750xx  ) || defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	QUADSPI_IRQn = 92,
#endif
#if defined(STM32L562xx  )
	AES_IRQn = 93,
	PKA_IRQn = 97,
	OTFDEC1_IRQn = 108,
#endif
#if defined(STM32F446xx  )
	CEC_IRQn = 93,
	SPDIF_RX_IRQn = 94,
#endif
#if defined(STM32L4R7xx  ) || defined(STM32L4R9xx  ) || defined(STM32L4S7xx  ) || defined(STM32L4S9xx  )
	GFXMMU_IRQn = 93,
#endif
#if defined(STM32F7      ) || defined(STM32H7      )
	LPTIM1_IRQn = 93,
#endif
#if defined(STM32H7      ) || defined(STM32F746xx  ) || defined(STM32F750xx  ) || defined(STM32F765xx  ) || \
    defined(STM32F769xx  ) || defined(STM32F777xx  )
	CEC_IRQn = 94,
	I2C4_EV_IRQn = 95,
	I2C4_ER_IRQn = 96,
	SPDIF_RX_IRQn = 97,
#endif
#if defined(STM32F410Tx  ) || defined(STM32F412Zx  ) || defined(STM32F423xx  ) || defined(STM32F446xx  )
	FMPI2C1_EV_IRQn = 95,
	FMPI2C1_ER_IRQn = 96,
#endif
#if defined(STM32F410Tx  ) || defined(STM32F423xx  )
	LPTIM1_IRQn = 97,
#endif
#if defined(STM32F769xx  )
	DSI_IRQn = 98,
#endif
#if defined(STM32H742xx  ) || defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || \
    defined(STM32H750xx  ) || defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	OTG_FS_EP1_OUT_IRQn = 98,
	OTG_FS_EP1_IN_IRQn = 99,
	OTG_FS_WKUP_IRQn = 100,
	OTG_FS_IRQn = 101,
	HRTIM1_Master_IRQn = 103,
	HRTIM1_TIMA_IRQn = 104,
	HRTIM1_TIMB_IRQn = 105,
	HRTIM1_TIMC_IRQn = 106,
	HRTIM1_TIMD_IRQn = 107,
	HRTIM1_TIME_IRQn = 108,
	HRTIM1_FLT_IRQn = 109,
	SAI3_IRQn = 114,
#endif
#if defined(STM32F765xx  ) || defined(STM32F769xx  ) || defined(STM32F777xx  )
	DFSDM1_FLT0_IRQn = 99,
	DFSDM1_FLT1_IRQn = 100,
	DFSDM1_FLT2_IRQn = 101,
	DFSDM1_FLT3_IRQn = 102,
	CAN3_TX_IRQn = 104,
	CAN3_RX0_IRQn = 105,
	CAN3_RX1_IRQn = 106,
	CAN3_SCE_IRQn = 107,
	MDIOS_IRQn = 109,
#endif
#if defined(STM32F722xx  ) || defined(STM32F730xx  ) || defined(STM32F733xx  ) || defined(STM32F765xx  ) || \
    defined(STM32F769xx  ) || defined(STM32F777xx  )
	SDMMC2_IRQn = 103,
#endif
#if defined(STM32F769xx  ) || defined(STM32F777xx  )
	JPEG_IRQn = 108,
#endif
#if defined(STM32H743xx  ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H750xx  ) || \
    defined(STM32H753xx  ) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || defined(STM32H7A3xxQ ) || \
    defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	JPEG_IRQn = 121,
#endif
#if defined(STM32H747xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	DSI_IRQn = 123,
#endif
#if defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || \
    defined(STM32H7A3xxQ ) || defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	WWDG_RST_IRQn = 143,
#endif
#if defined(STM32H730xx  ) || defined(STM32H7B0xxQ ) || defined(STM32H7B3xx  )
	OTFDEC1_IRQn = 151,
	OTFDEC2_IRQn = 152,
#endif
#if defined(STM32H723xx  ) || defined(STM32H730xx  )
	FMAC_IRQn = 153,
	CORDIC_IRQn = 154,
	UART9_IRQn = 155,
	USART10_IRQn = 156,
	I2C5_EV_IRQn = 157,
	I2C5_ER_IRQn = 158,
	FDCAN3_IT0_IRQn = 159,
	FDCAN3_IT1_IRQn = 160,
	TIM23_IRQn = 161,
	TIM24_IRQn = 162,
#endif
} IRQn_Type;

#ifdef __cplusplus
}
#endif

#endif //__SOOL_IRQN_H