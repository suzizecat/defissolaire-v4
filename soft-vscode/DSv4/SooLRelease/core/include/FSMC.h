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


//Generated 2020-09-26T14:47:32.079800

#ifndef __SOOL_CORE_FSMC_H
#define __SOOL_CORE_FSMC_H
#include "lib_utils/peripheral_include.h"
//SOOL-FSMC-INCLUDES-BEGIN
#include "RCC.h"
//SOOL-FSMC-INCLUDES-END

#if	defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32L1      ) || defined(STM32F405xx  ) || defined(STM32F412Cx  ) || \
    defined(STM32F413xx  ) || defined(STM32F417xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  )
#if	defined(STM32F2      ) || defined(STM32L1      ) || defined(STM32F405xx  ) || defined(STM32F412Cx  ) || defined(STM32F417xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32F750xx  ) || defined(STM32F756xx  ) || defined(STM32F765xx  ) || defined(STM32F767xx  ) || \
    defined(STM32F769xx  )
#define FSMC_BCRx_WRAPMOD WRAPMOD
#else
#define FSMC_BCRx_WRAPMOD
#endif

#if	defined(STM32F413xx  ) || defined(STM32F427xx  ) || defined(STM32F437xx  ) || defined(STM32F723xx  ) || defined(STM32F730xx  ) || \
    defined(STM32F732xx  )
#define FSMC_BCRx_CPSIZE CPSIZE
#else
#define FSMC_BCRx_CPSIZE
#endif

#if	defined(STM32F7      ) || defined(STM32F413xx  ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || \
    defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  )
#define FSMC_BCRx_CCLKEN CCLKEN
#else
#define FSMC_BCRx_CCLKEN
#endif

#if	defined(STM32F413xx  ) || defined(STM32F723xx  ) || defined(STM32F730xx  ) || defined(STM32F732xx  )
#define FSMC_BCRx_WFDIS WFDIS
#else
#define FSMC_BCRx_WFDIS
#endif

#if	defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32F405xx  ) || defined(STM32F412Cx  ) || defined(STM32F417xx  ) || \
    defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  )
#define FSMC_PCR
#define FSMC_SR
#define FSMC_PMEM
#define FSMC_PATT
#define FSMC_ECCR
#endif

#if	defined(STM32F7      ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  )
#define FSMC_SDCRx
#define FSMC_SDTRx
#define FSMC_SDCMR
#define FSMC_SDRTR
#define FSMC_SDSR
#define FSMC_MAP0_SDCR1 SDCRx_t SDCR1
#define FSMC_MAP0_SDTR1 SDTRx_t SDTR1
#define FSMC_MAP0_SDTR2 SDTRx_t SDTR2
#define FSMC_MAP0_SDCMR SDCMR_t SDCMR
#define FSMC_MAP0_SDRTR SDRTR_t SDRTR
#define FSMC_MAP0_SDSR SDSR_t SDSR
#else
#define FSMC_MAP0_SDCR1 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_SDTR1 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_SDTR2 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_SDCMR __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_SDRTR __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_SDSR __SOOL_PERIPH_PADDING_4
#endif

#if	defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || \
    defined(STM32F479xx  ) || defined(STM32F750xx  ) || defined(STM32F756xx  ) || defined(STM32F765xx  ) || defined(STM32F767xx  ) || \
    defined(STM32F769xx  )
#define FSMC_SDSR_RE RE
#else
#define FSMC_SDSR_RE
#endif

#if	defined(STM32F427xx  ) || defined(STM32F437xx  ) || defined(STM32F723xx  ) || defined(STM32F730xx  ) || defined(STM32F732xx  )
#define FSMC_SDCR2
#define FSMC_MAP1_SDCR2 SDCR2_t SDCR2
#else
#define FSMC_MAP1_SDCR2 __SOOL_PERIPH_PADDING_4
#endif

#if	defined(STM32F723xx  ) || defined(STM32F730xx  ) || defined(STM32F732xx  )
#define FSMC_SDCR2_RBURST RBURST
#else
#define FSMC_SDCR2_RBURST
#endif

#if	defined(STM32F2      ) || defined(STM32F405xx  ) || defined(STM32F412Cx  ) || defined(STM32F417xx  ) || defined(STM32F427xx  ) || \
    defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  )
#define FSMC_PIO4
#define FSMC_MAP1_PCR2 PCR_t PCR2
#define FSMC_MAP1_SR2 SR_t SR2
#define FSMC_MAP1_PMEM2 PMEM_t PMEM2
#define FSMC_MAP1_PATT2 PATT_t PATT2
#define FSMC_MAP1_ECCR2 ECCR_t ECCR2
#define FSMC_MAP1_PCR3 PCR_t PCR3
#define FSMC_MAP1_SR3 SR_t SR3
#define FSMC_MAP1_PMEM3 PMEM_t PMEM3
#define FSMC_MAP1_PATT3 PATT_t PATT3
#define FSMC_MAP1_ECCR3 ECCR_t ECCR3
#define FSMC_MAP1_PCR4 PCR_t PCR4
#define FSMC_MAP1_SR4 SR_t SR4
#define FSMC_MAP1_PMEM4 PMEM_t PMEM4
#define FSMC_MAP1_PATT4 PATT_t PATT4
#define FSMC_MAP1_PIO4 PIO4_t PIO4
#else
#define FSMC_MAP1_PCR2 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_SR2 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PMEM2 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PATT2 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_ECCR2 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PCR3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_SR3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PMEM3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PATT3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_ECCR3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PCR4 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_SR4 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PMEM4 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PATT4 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_PIO4 __SOOL_PERIPH_PADDING_4
#endif

#if	defined(STM32F7      ) || defined(STM32F479xx  )
#define FSMC_MAP0_PCR PCR_t PCR
#define FSMC_MAP0_SR SR_t SR
#define FSMC_MAP0_PMEM PMEM_t PMEM
#define FSMC_MAP0_PATT PATT_t PATT
#define FSMC_MAP0_ECCR ECCR_t ECCR
#else
#define FSMC_MAP0_PCR __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_SR __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_PMEM __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_PATT __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_ECCR __SOOL_PERIPH_PADDING_4
#endif

#if	defined(STM32F2      ) || defined(STM32F7      ) || defined(STM32L1      ) || defined(STM32F405xx  ) || defined(STM32F412Cx  ) || \
    defined(STM32F413xx  ) || defined(STM32F417xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  )
#define FSMC_MAP0_BWTR3 BxTRx_t BWTR3
#define FSMC_MAP0_BWTR4 BxTRx_t BWTR4
#else
#define FSMC_MAP0_BWTR3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP0_BWTR4 __SOOL_PERIPH_PADDING_4
#endif

#if	defined(STM32F429xx  ) || defined(STM32F439xx  ) || defined(STM32F446xx  ) || defined(STM32F479xx  ) || defined(STM32F750xx  ) || \
    defined(STM32F756xx  ) || defined(STM32F765xx  ) || defined(STM32F767xx  ) || defined(STM32F769xx  )
#define FSMC_MAP0_SDCR2 SDCRx_t SDCR2
#else
#define FSMC_MAP0_SDCR2 __SOOL_PERIPH_PADDING_4
#endif

#if	defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  )
#define FSMC_MAP1_BWTR3 BxTRx_t BWTR3
#define FSMC_MAP1_BWTR4 BxTRx_t BWTR4
#else
#define FSMC_MAP1_BWTR3 __SOOL_PERIPH_PADDING_4
#define FSMC_MAP1_BWTR4 __SOOL_PERIPH_PADDING_4
#endif

namespace sool {
	namespace core {
		class FSMC /// flexible memory controller
		{
		public:
			//SOOL-FSMC-SUB-TYPES-BEGIN
			//SOOL-FSMC-SUB-TYPES-END
			struct BCRx_t: public Reg32_t /// SRAM/NOR-Flash chip-select control register 1
			{
				using Reg32_t::operator=;
				uint32_t MBKEN            : 1; /// Memory bank enable bit
				uint32_t MUXEN            : 1; /// Memory bank enable bit
				uint32_t MTYP             : 2; /// Memory type
				uint32_t MWID             : 2; /// Memory data bus width
				uint32_t FACCEN           : 1; /// Flash access enable
				uint32_t                  : 1;
				uint32_t BURSTEN          : 1; /// Burst enable bit
				uint32_t WAITPOL          : 1; /// Wait signal polarity bit
				uint32_t FSMC_BCRx_WRAPMOD : 1;
				uint32_t WAITCFG          : 1; /// Wait timing configuration
				uint32_t WREN             : 1; /// Write enable bitWREN
				uint32_t WAITEN           : 1; /// Wait enable bit
				uint32_t EXTMOD           : 1; /// Extended mode enable
				uint32_t ASYNCWAIT        : 1; /// Wait signal during asynchronous transfers
				uint32_t FSMC_BCRx_CPSIZE : 3; /// CRAM page size
				uint32_t CBURSTRW         : 1; /// Write burst enable
				uint32_t FSMC_BCRx_CCLKEN : 1; /// Continuous Clock Enable
				uint32_t FSMC_BCRx_WFDIS  : 1; /// Write FIFO Disable
				uint32_t                  : 10;
				//SOOL-FSMC_BCRx-DECLARATIONS
			};
			struct BxTRx_t: public Reg32_t /// SRAM/NOR-Flash chip-select timing register 1
			{
				using Reg32_t::operator=;
				uint32_t ADDSET           : 4; /// Address setup phase duration
				uint32_t ADDHLD           : 4; /// Address-hold phase duration
				uint32_t DATAST           : 8; /// Data-phase duration
				uint32_t BUSTURN          : 4; /// Bus turnaround phase duration
				uint32_t CLKDIV           : 4; /// Clock divide ratio
				uint32_t DATLAT           : 4; /// Data latency
				uint32_t ACCMOD           : 2; /// Access mode
				uint32_t                  : 2;
				//SOOL-FSMC_BxTRx-DECLARATIONS
			};
			#ifdef FSMC_PCR
			struct PCR_t: public Reg32_t /// PC Card/NAND Flash control register
			{
				using Reg32_t::operator=;
				uint32_t                  : 1;
				uint32_t PWAITEN          : 1;
				uint32_t PBKEN            : 1;
				uint32_t PTYP             : 1;
				uint32_t PWID             : 2;
				uint32_t ECCEN            : 1;
				uint32_t                  : 2;
				uint32_t TCLR             : 4;
				uint32_t TAR              : 4;
				uint32_t ECCPS            : 3;
				uint32_t                  : 12;
				//SOOL-FSMC_PCR-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SR
			struct SR_t: public Reg32_t /// FIFO status and interrupt register
			{
				using Reg32_t::operator=;
				uint32_t IRS              : 1;
				uint32_t ILS              : 1;
				uint32_t IFS              : 1;
				uint32_t IREN             : 1;
				uint32_t ILEN             : 1;
				uint32_t IFEN             : 1;
				uint32_t FEMPT            : 1;
				uint32_t                  : 25;
				//SOOL-FSMC_SR-DECLARATIONS
			};
			#endif
			#ifdef FSMC_PMEM
			struct PMEM_t: public Reg32_t /// Common memory space timing register
			{
				using Reg32_t::operator=;
				uint32_t MEMSETx          : 8;
				uint32_t MEMWAITx         : 8;
				uint32_t MEMHOLDx         : 8;
				uint32_t MEMHIZx          : 8;
				//SOOL-FSMC_PMEM-DECLARATIONS
			};
			#endif
			#ifdef FSMC_PATT
			struct PATT_t: public Reg32_t /// Attribute memory space timing register
			{
				using Reg32_t::operator=;
				uint32_t ATTSETx          : 8; /// Attribute memory x setup time
				uint32_t ATTWAITx         : 8; /// Attribute memory x wait time
				uint32_t ATTHOLDx         : 8; /// Attribute memory x hold time
				uint32_t ATTHIZx          : 8; /// Attribute memory x databus HiZ time
				//SOOL-FSMC_PATT-DECLARATIONS
			};
			#endif
			#ifdef FSMC_ECCR
			struct ECCR_t: public Reg32_t /// ECC result register
			{
				using Reg32_t::operator=;
				uint32_t ECCx             : 32; /// ECC result
				//SOOL-FSMC_ECCR-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SDCRx
			struct SDCRx_t: public Reg32_t /// SDRAM Control Register 1
			{
				using Reg32_t::operator=;
				uint32_t NC               : 2; /// Number of column address bits
				uint32_t NR               : 2; /// Number of row address bits
				uint32_t MWID             : 2; /// Memory data bus width
				uint32_t NB               : 1; /// Number of internal banks
				uint32_t CAS              : 2; /// CAS latency
				uint32_t WP               : 1; /// Write protection
				uint32_t SDCLK            : 2; /// SDRAM clock configuration
				uint32_t RBURST           : 1; /// Burst read
				uint32_t RPIPE            : 2; /// Read pipe
				uint32_t                  : 17;
				//SOOL-FSMC_SDCRx-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SDTRx
			struct SDTRx_t: public Reg32_t /// SDRAM Timing register 1
			{
				using Reg32_t::operator=;
				uint32_t TMRD             : 4; /// Load Mode Register to Active
				uint32_t TXSR             : 4; /// Exit self-refresh delay
				uint32_t TRAS             : 4; /// Self refresh time
				uint32_t TRC              : 4; /// Row cycle delay
				uint32_t TWR              : 4; /// Recovery delay
				uint32_t TRP              : 4; /// Row precharge delay
				uint32_t TRCD             : 4; /// Row to column delay
				uint32_t                  : 4;
				//SOOL-FSMC_SDTRx-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SDCMR
			struct SDCMR_t: public Reg32_t /// SDRAM Command Mode register
			{
				using Reg32_t::operator=;
				uint32_t MODE             : 3; /// Command mode
				uint32_t CTB2             : 1; /// Command target bank 2
				uint32_t CTB1             : 1; /// Command target bank 1
				uint32_t NRFS             : 4; /// Number of Auto-refresh
				uint32_t MRD              : 13; /// Mode Register definition
				uint32_t                  : 10;
				//SOOL-FSMC_SDCMR-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SDRTR
			struct SDRTR_t: public Reg32_t /// SDRAM Refresh Timer register
			{
				using Reg32_t::operator=;
				uint32_t CRE              : 1; /// Clear Refresh error flag
				uint32_t COUNT            : 13; /// Refresh Timer Count
				uint32_t REIE             : 1; /// RES Interrupt Enable
				uint32_t                  : 17;
				//SOOL-FSMC_SDRTR-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SDSR
			struct SDSR_t: public Reg32_t /// SDRAM Status register
			{
				using Reg32_t::operator=;
				uint32_t FSMC_SDSR_RE     : 1; /// Refresh error flag
				uint32_t MODES1           : 2; /// Status Mode for Bank 1
				uint32_t MODES2           : 2; /// Status Mode for Bank 2
				uint32_t BUSY             : 1; /// Busy status
				uint32_t                  : 26;
				//SOOL-FSMC_SDSR-DECLARATIONS
			};
			#endif
			#ifdef FSMC_SDCR2
			struct SDCR2_t: public Reg32_t /// SDRAM Control Register 2
			{
				using Reg32_t::operator=;
				uint32_t NC               : 2; /// Number of column address bits
				uint32_t NR               : 2; /// Number of row address bits
				uint32_t MWID             : 2; /// Memory data bus width
				uint32_t NB               : 1; /// Number of internal banks
				uint32_t CAS              : 2; /// CAS latency
				uint32_t WP               : 1; /// Write protection
				uint32_t SDCLK            : 2; /// SDRAM clock configuration
				uint32_t FSMC_SDCR2_RBURST : 1; /// Burst read
				uint32_t                  : 19;
				//SOOL-FSMC_SDCR2-DECLARATIONS
			};
			#endif
			#ifdef FSMC_PIO4
			struct PIO4_t: public Reg32_t /// I/O space timing register 4
			{
				using Reg32_t::operator=;
				uint32_t IOSETx           : 8;
				uint32_t IOWAITx          : 8;
				uint32_t IOHOLDx          : 8;
				uint32_t IOHIZx           : 8;
				//SOOL-FSMC_PIO4-DECLARATIONS
			};
			#endif
			union
			{
				struct
				{
					BCRx_t BCR1; /// SRAM/NOR-Flash chip-select control register 1
					BxTRx_t BTR1; /// SRAM/NOR-Flash chip-select timing register 1
					__SOOL_PERIPH_PADDING_4;
					BxTRx_t BTR2; /// SRAM/NOR-Flash chip-select timing register 2
					__SOOL_PERIPH_PADDING_4;
					BxTRx_t BTR3; /// SRAM/NOR-Flash chip-select timing register 3
					__SOOL_PERIPH_PADDING_4;
					BxTRx_t BTR4; /// SRAM/NOR-Flash chip-select timing register 4
					__SOOL_PERIPH_PADDING_32;
					__SOOL_PERIPH_PADDING_64;
					FSMC_MAP0_PCR; /// PC Card/NAND Flash control register
					FSMC_MAP0_SR; /// FIFO status and interrupt register
					FSMC_MAP0_PMEM; /// Common memory space timing register
					FSMC_MAP0_PATT; /// Attribute memory space timing register
					__SOOL_PERIPH_PADDING_4;
					FSMC_MAP0_ECCR; /// ECC result register
					__SOOL_PERIPH_PADDING_4;
					__SOOL_PERIPH_PADDING_8;
					__SOOL_PERIPH_PADDING_32;
					__SOOL_PERIPH_PADDING_64;
					BxTRx_t BWTR1; /// SRAM/NOR-Flash write timing registers 1
					__SOOL_PERIPH_PADDING_4;
					BxTRx_t BWTR2; /// SRAM/NOR-Flash write timing registers 2
					__SOOL_PERIPH_PADDING_4;
					FSMC_MAP0_BWTR3; /// SRAM/NOR-Flash write timing registers 3
					__SOOL_PERIPH_PADDING_4;
					FSMC_MAP0_BWTR4; /// SRAM/NOR-Flash write timing registers 4
					__SOOL_PERIPH_PADDING_32;
					FSMC_MAP0_SDCR1; /// SDRAM Control Register 1
					FSMC_MAP0_SDCR2; /// SDRAM Control Register 2
					FSMC_MAP0_SDTR1; /// SDRAM Timing register 1
					FSMC_MAP0_SDTR2; /// SDRAM Timing register 2
					FSMC_MAP0_SDCMR; /// SDRAM Command Mode register
					FSMC_MAP0_SDRTR; /// SDRAM Refresh Timer register
					FSMC_MAP0_SDSR; /// SDRAM Status register
				};
				struct
				{
					__SOOL_PERIPH_PADDING_8;
					BCRx_t BCR2; /// SRAM/NOR-Flash chip-select control register 2
					__SOOL_PERIPH_PADDING_4;
					BCRx_t BCR3; /// SRAM/NOR-Flash chip-select control register 3
					__SOOL_PERIPH_PADDING_4;
					BCRx_t BCR4; /// SRAM/NOR-Flash chip-select control register 4
					__SOOL_PERIPH_PADDING_4;
					__SOOL_PERIPH_PADDING_64;
					FSMC_MAP1_PCR2; /// PC Card/NAND Flash control register 2
					FSMC_MAP1_SR2; /// FIFO status and interrupt register 2
					FSMC_MAP1_PMEM2; /// Common memory space timing register 2
					FSMC_MAP1_PATT2; /// Attribute memory space timing register 2
					__SOOL_PERIPH_PADDING_4;
					FSMC_MAP1_ECCR2; /// ECC result register 2
					__SOOL_PERIPH_PADDING_8;
					FSMC_MAP1_PCR3; /// PC Card/NAND Flash control register 3
					FSMC_MAP1_SR3; /// FIFO status and interrupt register 3
					FSMC_MAP1_PMEM3; /// Common memory space timing register 3
					FSMC_MAP1_PATT3; /// Attribute memory space timing register 3
					__SOOL_PERIPH_PADDING_4;
					FSMC_MAP1_ECCR3; /// ECC result register 3
					__SOOL_PERIPH_PADDING_8;
					FSMC_MAP1_PCR4; /// PC Card/NAND Flash control register 4
					FSMC_MAP1_SR4; /// FIFO status and interrupt register 4
					FSMC_MAP1_PMEM4; /// Common memory space timing register 4
					FSMC_MAP1_PATT4; /// Attribute memory space timing register 4
					FSMC_MAP1_PIO4; /// I/O space timing register 4
					__SOOL_PERIPH_PADDING_16;
					__SOOL_PERIPH_PADDING_64;
					FSMC_MAP1_BWTR3; /// SRAM/NOR-Flash write timing registers 3
					__SOOL_PERIPH_PADDING_4;
					FSMC_MAP1_BWTR4; /// SRAM/NOR-Flash write timing registers 4
					__SOOL_PERIPH_PADDING_4;
					__SOOL_PERIPH_PADDING_16;
					__SOOL_PERIPH_PADDING_32;
					FSMC_MAP1_SDCR2; /// SDRAM Control Register 2
					__SOOL_PERIPH_PADDING_4;
					__SOOL_PERIPH_PADDING_16;
				};
			};
			//SOOL-FSMC-DECLARATIONS-BEGIN
			constexpr volatile Reg32_t &get_clock_enable_reg(const uintptr_t addr) volatile;
			constexpr uint32_t get_clock_enable_bit(const uintptr_t addr) volatile;
			
			inline void enable_clock() volatile;
			//SOOL-FSMC-DECLARATIONS-END

			#if __SOOL_DEBUG_NOPHY
				FSMC(uintptr_t addr) : myaddr(addr){};
				const uintptr_t myaddr;
				inline const uintptr_t get_addr() const volatile {return myaddr;};
			#else
				inline const uintptr_t get_addr() const volatile {return reinterpret_cast<uintptr_t>(this);};
			private:
				FSMC() = delete;
			#endif
		};

#if	defined(STM32F7      ) || defined(STM32F427xx  ) || defined(STM32F429xx  ) || defined(STM32F437xx  ) || defined(STM32F439xx  ) || \
    defined(STM32F446xx  ) || defined(STM32F479xx  )
#define FMC_BASE_ADDR ((uint32_t)0xa0000000U)
#define FMC_TMPL
#endif

#if	defined(STM32F2      ) || defined(STM32L1      ) || defined(STM32F405xx  ) || defined(STM32F412Cx  ) || defined(STM32F417xx  )
#define FSMC_BASE_ADDR ((uint32_t)0xa0000000U)
#define FSMC_TMPL
#endif

#if	defined(STM32F413xx  )
#define FSMC_BASE_ADDR ((uint32_t)0x60000000U)
#define FSMC_TMPL
#endif


//Instances for peripheral FSMC

		#if defined(FMC_BASE_ADDR) 
			#if __SOOL_DEBUG_NOPHY
				volatile class FSMC * const FMC = new class FSMC(FMC_BASE_ADDR);
			#else
				volatile class FSMC * const FMC = reinterpret_cast<class FSMC* const>(FMC_BASE_ADDR);
			#endif
		#endif

		#if defined(FSMC_BASE_ADDR) 
			#if __SOOL_DEBUG_NOPHY
				volatile class FSMC * const FSMC = new class FSMC(FSMC_BASE_ADDR);
			#else
				volatile class FSMC * const FSMC = reinterpret_cast<class FSMC* const>(FSMC_BASE_ADDR);
			#endif
		#endif
		//SOOL-FSMC-DEFINES
		//SOOL-FSMC-DEFINITIONS-BEGIN
		
		
		
		        inline constexpr volatile Reg32_t& FSMC::get_clock_enable_reg(const uintptr_t addr) volatile
		        {
		            switch (addr)
		            {
		                //Output for FMCEN
		#ifdef FMC_BASE_ADDR
		                case FMC_BASE_ADDR :
			return RCC->AHB3ENR;
		#endif
		                //Output for FSMCEN
		#ifdef FSMC_BASE_ADDR
		                case FSMC_BASE_ADDR :
			#if defined(STM32F2      ) || defined(STM32F4      )
		return RCC->AHB3ENR;
			#elif defined(STM32L1      )
		return RCC->AHBENR;
			#endif
		#endif
		            }
		        }
		
		        inline constexpr uint32_t FSMC::get_clock_enable_bit(const uintptr_t addr) volatile
		        {
		            switch (addr)
		            {
		                //Output for FMCEN
		#ifdef FMC_BASE_ADDR
		                case FMC_BASE_ADDR :
		return 1 << 0;
		#endif
		                //Output for FSMCEN
		#ifdef FSMC_BASE_ADDR
		                case FSMC_BASE_ADDR :
			#if defined(STM32F2      ) || defined(STM32F4      )
		return 1 << 0;
			#elif defined(STM32L1      )
		return 1 << 30;
			#endif
		#endif
		            }
		        }
		
		       inline void FSMC::enable_clock() volatile
		        {
		            get_clock_enable_reg(get_addr()) |= get_clock_enable_bit(get_addr());
		        }
		
		//SOOL-FSMC-DEFINITIONS-END
	};
};
#undef FSMC_BCRx_WFDIS
#undef FSMC_MAP1_PMEM4
#undef FSMC_MAP1_BWTR4
#undef FSMC_MAP1_SDCR2
#undef FSMC_MAP1_SR3
#undef FSMC_MAP1_BWTR3
#undef FSMC_MAP0_SDRTR
#undef FSMC_MAP1_PCR3
#undef FSMC_MAP0_BWTR3
#undef FSMC_SDSR_RE
#undef FSMC_MAP1_ECCR2
#undef FSMC_MAP1_PMEM3
#undef FSMC_MAP1_ECCR3
#undef FSMC_MAP1_PIO4
#undef FSMC_MAP0_SDCR2
#undef FSMC_MAP0_SDCR1
#undef FSMC_TMPL
#undef FSMC_MAP1_PATT2
#undef FSMC_MAP1_PMEM2
#undef FSMC_MAP1_SR4
#undef FSMC_MAP0_SDCMR
#undef FSMC_MAP0_SDTR1
#undef FSMC_MAP0_PATT
#undef FSMC_BCRx_CCLKEN
#undef FSMC_MAP0_ECCR
#undef FMC_TMPL
#undef FSMC_MAP1_PCR2
#undef FSMC_SDCR2_RBURST
#undef FSMC_MAP0_SR
#undef FSMC_MAP0_PCR
#undef FSMC_MAP1_PCR4
#undef FSMC_BCRx_CPSIZE
#undef FSMC_MAP0_SDTR2
#undef FSMC_MAP1_SR2
#undef FSMC_MAP0_PMEM
#undef FSMC_MAP1_PATT3
#undef FSMC_BCRx_WRAPMOD
#undef FSMC_MAP1_PATT4
#undef FSMC_MAP0_SDSR
#undef FSMC_MAP0_BWTR4

#endif

#endif //__SOOL_CORE_FSMC_H