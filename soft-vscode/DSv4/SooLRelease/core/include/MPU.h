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


//Generated 2020-09-26T14:47:31.759923

#ifndef __SOOL_CORE_MPU_H
#define __SOOL_CORE_MPU_H
#include "lib_utils/peripheral_include.h"
//SOOL-MPU-INCLUDES

#if	defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G0      ) || \
    defined(STM32G4      ) || defined(STM32GB      ) || defined(STM32H7      ) || defined(STM32L0      ) || defined(STM32L1      ) || \
    defined(STM32L4      ) || defined(STM32WB      )
namespace sool {
	namespace core {
		class MPU /// memory protection unit
		{
		public:
			//SOOL-MPU-SUB-TYPES-BEGIN
			enum class RegionSize
			{
			Size64B = 4,
			Size128B,
			Size256B,
			Size512B,
			Size1KiB,
			Size2KiB,
			Size4KiB,
			Size8KiB,
			Size16KiB,
			Size32KiB,
			Size64KiB,
			Size128KiB,
			Size256KiB,
			Size512KiB,
			Size1MiB,
			Size2MiB,
			Size4MiB,
			Size8MiB,
			Size16MiB,
			Size32MiB,
			Size64MiB,
			Size128MiB,
			Size256MiB,
			Size512MiB,
			Size1GiB,
			Size2GiB,
			Size4GiB
			};
			
			enum class RegionType
			{
			StronglyOrdered = 0,
			Device_Shared = 0b10,
			Normal_NonShared_WriteThrough_NoWAlloc = 0b100,
			Normal_Shared_WriteThrough_NoWAlloc = 0b101,
			Normal_NonShared_WriteBack_NoWAlloc = 0b110,
			Normal_Shared_WriteBack_NoWAlloc = 0b111,
			Normal_NonShared_NoCache= 0b1000,
			Normal_Shared_NoCache = 0b1001,
			Normal_NonShared_WriteBack_WAlloc = 0b1110,
			Normal_Shared_WriteBack_WAlloc = 0b1111,
			Device_NonShared = 0b010000,
			};
			
			enum class AccessPermission
			{
			NoAccess = 0,
			PRW_UNoAccess,
			PRW_UR,
			FullAccess,
			PRO_UNoAccess = 0b101,
			ReadOnly
			};
			//SOOL-MPU-SUB-TYPES-END
			struct TYPER_t: public Reg32_t /// MPU type register
			{
				using Reg32_t::operator=;
				uint32_t SEPARATE         : 1; /// Separate flag
				uint32_t                  : 7;
				uint32_t DREGION          : 8; /// Number of MPU data regions
				uint32_t IREGION          : 8; /// Number of MPU instruction regions
				uint32_t                  : 8;
				//SOOL-MPU_TYPER-DECLARATIONS
			};
			struct CTRL_t: public Reg32_t /// MPU control register
			{
				using Reg32_t::operator=;
				uint32_t ENABLE           : 1; /// Enables the MPU
				uint32_t HFNMIENA         : 1; /// Enables the operation of MPU during hard fault
				uint32_t PRIVDEFENA       : 1; /// Enable priviliged software access to default memory map
				uint32_t                  : 29;
				//SOOL-MPU_CTRL-DECLARATIONS
			};
			struct RNR_t: public Reg32_t /// MPU region number register
			{
				using Reg32_t::operator=;
				uint32_t REGION           : 8; /// MPU region
				uint32_t                  : 24;
				//SOOL-MPU_RNR-DECLARATIONS
			};
			struct RBAR_t: public Reg32_t /// MPU region base address register
			{
				using Reg32_t::operator=;
				uint32_t REGION           : 4; /// MPU region field
				uint32_t VALID            : 1; /// MPU region number valid
				uint32_t ADDR             : 27; /// Region base address field
				//SOOL-MPU_RBAR-DECLARATIONS
			};
			struct RASR_t: public Reg32_t /// MPU region attribute and size register
			{
				using Reg32_t::operator=;
				uint32_t ENABLE           : 1; /// Region enable bit.
				uint32_t SIZE             : 5; /// Size of the MPU protection region
				uint32_t                  : 2;
				uint32_t SRD              : 8; /// Subregion disable bits
				uint32_t B                : 1; /// memory attribute
				uint32_t C                : 1; /// memory attribute
				uint32_t S                : 1; /// Shareable memory attribute
				uint32_t TEX              : 3; /// memory attribute
				uint32_t                  : 2;
				uint32_t AP               : 3; /// Access permission
				uint32_t                  : 1;
				uint32_t XN               : 1; /// Instruction access disable bit
				uint32_t                  : 3;
				//SOOL-MPU_RASR-DECLARATIONS
			};
			TYPER_t TYPER; /// MPU type register
			CTRL_t CTRL; /// MPU control register
			RNR_t RNR; /// MPU region number register
			RBAR_t RBAR; /// MPU region base address register
			RASR_t RASR; /// MPU region attribute and size register
			//SOOL-MPU-DECLARATIONS-BEGIN
			void enable(const bool enable = true) volatile;
			void enable_default_region(const bool enable = true) volatile;
			void enable_during_hardfault(const bool enable = true) volatile;
			void select_region(int region) volatile;
			void set_region_size(const RegionSize size) volatile;
			void set_region_execute(const bool n_XN) volatile;
			void set_access_type(const RegionType type) volatile;
			void set_access_permission(const AccessPermission perm) volatile;
			void set_subregion_mask(const uint8_t mask = 0b11111111) volatile;
			void set_region_enable(const bool enable) volatile;
			void set_region_base_address(const uintptr_t addr) volatile;
			inline int get_region() const;
			//SOOL-MPU-DECLARATIONS-END

			#if __SOOL_DEBUG_NOPHY
				MPU(uintptr_t addr) : myaddr(addr){};
				const uintptr_t myaddr;
				inline const uintptr_t get_addr() const volatile {return myaddr;};
			#else
				inline const uintptr_t get_addr() const volatile {return reinterpret_cast<uintptr_t>(this);};
			private:
				MPU() = delete;
			#endif
		};

#if	defined(STM32F2      ) || defined(STM32F3      ) || defined(STM32F4      ) || defined(STM32F7      ) || defined(STM32G0      ) || \
    defined(STM32H7      ) || defined(STM32L0      ) || defined(STM32L1      ) || defined(STM32L4      ) || defined(STM32WB      )
#define MPU_BASE_ADDR ((uint32_t)0xe000ed90U)
#define MPU_TMPL
#endif

#if	defined(STM32G4      ) || defined(STM32GB      )
#define MPU_BASE_ADDR ((uint32_t)0xe000e084U)
#define MPU_TMPL
#endif


//Instances for peripheral MPU
		#if __SOOL_DEBUG_NOPHY
			volatile class MPU * const MPU = new class MPU(MPU_BASE_ADDR);
		#else
			volatile class MPU * const MPU = reinterpret_cast<class MPU* const>(MPU_BASE_ADDR);
		#endif

		//SOOL-MPU-DEFINES-BEGIN
		#define SOOL_MPU_PRESENT
		//SOOL-MPU-DEFINES-END
		//SOOL-MPU-DEFINITIONS-BEGIN
		inline int MPU::get_region() const {return RNR.REGION;};
		//SOOL-MPU-DEFINITIONS-END

	};
};
#undef MPU_TMPL

#endif

#endif //__SOOL_CORE_MPU_H