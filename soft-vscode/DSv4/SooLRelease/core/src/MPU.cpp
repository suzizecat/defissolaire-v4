//
// Created by julien on 03/11/2020.
//

#include "../include/MPU.h"
#ifdef SOOL_MPU_PRESENT
namespace sool
{
	namespace core
	{
		void MPU::enable(const bool enable) volatile
		{
			CTRL.ENABLE = enable ? 1 : 0;
		}
		void MPU::enable_default_region(const bool enable) volatile
		{
			CTRL.PRIVDEFENA = enable ? 1 : 0;
		}

		void MPU::enable_during_hardfault(const bool enable) volatile
		{
			CTRL.HFNMIENA = enable ? 1 : 0;
		}

		void MPU::select_region(int region) volatile
		{
			if(region >= 0 && region < TYPER.DREGION)
				RNR = region;
		}
		void MPU::set_region_size(const RegionSize size) volatile
		{
			RASR.SIZE = static_cast<int>(size);
		}
		void MPU::set_region_execute(const bool n_XN) volatile
		{
			RASR.XN = n_XN ? 0:1;
		}
		void MPU::set_access_type(const RegionType type) volatile
		{
			RASR_t buffer;
			buffer = static_cast<uint32_t>(type) << 16;

			RASR.S = buffer.S;
			RASR.C = buffer.C;
			RASR.B = buffer.B;
			RASR.TEX = buffer.TEX;
		}

		void MPU::set_access_permission(const AccessPermission perm) volatile
		{
			RASR.AP = static_cast<uint32_t>(perm);
		}
		void MPU::set_subregion_mask(const uint8_t mask) volatile
		{
			RASR.SRD = mask;
		}

		void MPU::set_region_base_address(const uintptr_t addr) volatile
		{
			RBAR.ADDR = addr & ((~0) << (RASR.SIZE + 1));
		}
		void MPU::set_region_enable(const bool enable) volatile
		{
			RASR.ENABLE = enable ? 1 : 0;
		}
	};
};
#endif