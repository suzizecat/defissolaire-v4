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
#ifndef SOOL_CMSIS_H
#define SOOL_CMSIS_H

#include "../../sool_chip_setup.h"
#ifdef __cplusplus
extern "C" {
#endif
#if defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	#define DUAL_CORE            
#endif
#if defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7) || \
    defined(STM32H7A3xxQ ) || defined(STM32H7B0xxQ )
	#define SMPS                 
#endif
#if defined(STM32G0      ) || defined(STM32L0      )
	#define __CM0PLUS_REV        0x0000
#endif
#if defined(STM32F0      )
	#define __CM0_REV            0x0000
#endif
#if defined(STM32L5      )
	#define __CM33_REV           0x0000
	#define __DSP_PRESENT        0x0001
	#define __NVIC_PRIO_BITS     0x0003
	#define __SAUREGION_PRESENT  0x0001
#endif
#if defined(STM32F2      ) || defined(STM32L1      )
	#define __CM3_REV            0x0200
#endif
#if defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32G4      ) || defined(STM32GB      ) || \
    defined(STM32L4      ) || defined(STM32WB      ) || defined(STM32H745xx_CORE_CM7) || defined(STM32H747xx_CORE_CM7) || \
    defined(STM32H755xx_CORE_CM7) || defined(STM32H757xx_CORE_CM7)
	#define __CM4_REV            0x0001
#endif
#if defined(STM32F746xx  ) || defined(STM32F750xx  )
	#define __CM7_REV            0x0001
#endif
#if defined(STM32H7      ) || defined(STM32F722xx  ) || defined(STM32F730xx  ) || defined(STM32F733xx  ) || \
    defined(STM32F765xx  ) || defined(STM32F769xx  ) || defined(STM32F777xx  )
	#define __CM7_REV            0x0100
#endif
#if defined(STM32F7      ) || defined(STM32H7      )
	#define __DCACHE_PRESENT     0x0001
	#define __ICACHE_PRESENT     0x0001
#endif
#if defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G4      ) || \
    defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L4      ) || defined(STM32L5      ) || \
    defined(STM32WB      )
	#define __FPU_PRESENT        0x0001
#endif
#if defined(STM32F0      ) || defined(STM32F302x8  ) || defined(STM32F303x8  ) || defined(STM32F328xx  ) || \
    defined(STM32F334x8  ) || defined(STM32L010x8  ) || defined(STM32L011xx  )
	#define __MPU_PRESENT        0x0000
#endif
#if defined(STM32F2      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G0      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || \
    defined(STM32L4      ) || defined(STM32L5      ) || defined(STM32WB      ) || defined(STM32F302xE  ) || \
    defined(STM32F358xx  ) || defined(STM32F373xC  ) || defined(STM32L051xx  ) || defined(STM32L052xx  ) || \
    defined(STM32L053xx  ) || defined(STM32L062xx  ) || defined(STM32L063xx  ) || defined(STM32L082xx  )
	#define __MPU_PRESENT        0x0001
#endif
#if defined(STM32F0      ) || defined(STM32G0      ) || defined(STM32L0      )
	#define __NVIC_PRIO_BITS     0x0002
#endif
#if defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L1      ) || \
    defined(STM32L4      ) || defined(STM32WB      )
	#define __NVIC_PRIO_BITS     0x0004
#endif
#if defined(STM32G0      ) || defined(STM32L0      ) || defined(STM32L5      ) || defined(STM32WB      )
	#define __VTOR_PRESENT       0x0001
#endif
	#define __Vendor_SysTickConfig 0x0000

#ifdef __cplusplus
}
#endif
#include "system_stm32.h"
#endif //__SOOL_CMSIS_H