/*
 * b-lcd40-dsi1.cpp
 *
 *  Created on: 11 sept. 2020
 *      Author: julien
 */

#include "../include/B_LCD40_DSI1.h"
using namespace sool::core;

// Commands
const uint8_t _enter_cmd2_mode[]   = {0xFF,0x80,0x09,0x01};
const uint8_t _enable_orise_cmd[]  = {0xFF,0x80,0x09};
const uint8_t lcdRegData3[]  = {0xE1,0x00,0x09,0x0F,0x0E,0x07,0x10,0x0B,0x0A,0x04,0x07,0x0B,0x08,0x0F,0x10,0x0A,0x01};
const uint8_t lcdRegData4[]  = {0xE2,0x00,0x09,0x0F,0x0E,0x07,0x10,0x0B,0x0A,0x04,0x07,0x0B,0x08,0x0F,0x10,0x0A,0x01};
const uint8_t _setup_gvdd[]  = {0xD8,0x79,0x79};
//const uint8_t _setup_gvdd[]  = {0xD8,0x8F,0x8F};
const uint8_t _setup_panel_type[]  = {0xB3,0x00,0x01};
const uint8_t lcdRegData7[]  = {0xCE,0x85,0x01,0x00,0x84,0x01,0x00};
const uint8_t lcdRegData8[]  = {0xCE,0x18,0x04,0x03,0x39,0x00,0x00,0x00,0x18,0x03,0x03,0x3A,0x00,0x00,0x00};
const uint8_t lcdRegData9[]  = {0xCE,0x18,0x02,0x03,0x3B,0x00,0x00,0x00,0x18,0x01,0x03,0x3C,0x00,0x00,0x00};
const uint8_t lcdRegData10[] = {0xCF,0x01,0x01,0x20,0x20,0x00,0x00,0x01,0x02,0x00,0x00};
const uint8_t lcdRegData11[] = {0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData12[] = {0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData13[] = {0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData14[] = {0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData15[] = {0xCB,0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData16[] = {0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x04,0x04,0x04,0x04,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData17[] = {0xCB,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData18[] = {0xCB,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
const uint8_t lcdRegData19[] = {0xCC,0x00,0x26,0x09,0x0B,0x01,0x25,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData20[] = {0xCC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x0A,0x0C,0x02};
const uint8_t lcdRegData21[] = {0xCC,0x25,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData22[] = {0xCC,0x00,0x25,0x0C,0x0A,0x02,0x26,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData23[] = {0xCC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x0B,0x09,0x01};
const uint8_t lcdRegData24[] = {0xCC,0x26,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
const uint8_t lcdRegData25[] = {0xFF,0xFF,0xFF,0xFF};



namespace sool { namespace bsp {



void OTM8009::enable_extended_cmd()
{
	using namespace sool::core;
	nop();
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,4,_enter_cmd2_mode);
	set_shift(0x80);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,4,_enable_orise_cmd);
}

void OTM8009::set_shift(uint8_t val)
{
	using namespace sool::core;
	if(_shift != val)
	{
		DSI->write_short(_vchannel, DSI::ShortWriteType::DCS_OneParam, 0x00, val);
		_shift = val;
	}
}

void OTM8009::setup_voltages()
{
	//Output level during porch and non-display = GND
	_send_short_cmd2(0xC480, 0x30);
	//Delay
	for(int i =0; i < 50000; i++)
		asm("nop");
	//Undocumented
	_send_short_cmd2(0xC48A, 0x40);
	for(int i =0; i < 50000; i++)
		asm("nop");

	_send_short_cmd2(0xC5B1, 0xA9);
	_send_short_cmd2(0xC591, 0x34);
	_send_short_cmd2(0xC0B4, 0x50);
	_send_short_cmd2(0xD900, 0x4E);
	_send_short_cmd2(0xC181, 0x66);

	//Videomode internal
	_send_short_cmd2(0xC1A1, 0x08);
	_send_short_cmd2(0xC592, 0x01);
	_send_short_cmd2(0xC595, 0x34);

	/* GVDD/NGVDD settings */
	set_shift(0x00);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,4,_setup_gvdd);

	_send_short_cmd2(0xC594, 0x33);
	_send_short_cmd2(0xC0A3, 0x1B);
	_send_short_cmd2(0xC582, 0x83);

	/* Source driver precharge */
	_send_short_cmd2(0xC481, 0x83);
	_send_short_cmd2(0xC1A1, 0x0E);
	set_shift(0xA6);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,3,_setup_panel_type);

	/*GOAVST*/
	set_shift(0x80);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,7,lcdRegData7);
	set_shift(0xA0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,15,lcdRegData8);
	set_shift(0xB0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,15,lcdRegData9);
	set_shift(0xC0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,11,lcdRegData10);

	_send_short_cmd2(0xCFD0, 0x00);

	set_shift(0x80);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,12,lcdRegData11);
	set_shift(0x90);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData12);
	set_shift(0xA0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData13);
	set_shift(0xB0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,11,lcdRegData14);
	set_shift(0xC0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData15);
	set_shift(0xD0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData16);
	set_shift(0xE0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,11,lcdRegData17);
	set_shift(0xF0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,11,lcdRegData18);
	set_shift(0x80);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,11,lcdRegData19);
	set_shift(0x90);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData20);
	set_shift(0xA0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData21);
	set_shift(0xB0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,11,lcdRegData22);
	set_shift(0xC0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData23);
	set_shift(0xD0);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,16,lcdRegData24);

	// Pump1 min and max
	_send_short_cmd2(0xC581, 0x66);
	_send_short_cmd2(0xF5B6, 0x06);

	_send_short_cmd2(0xC6B1, 0x06);


}

void OTM8009::_send_short(uint8_t reg, uint8_t value)
{
	DSI->write_short(_vchannel, DSI::ShortWriteType::DCS_OneParam, reg, value);
}

void OTM8009::_send_short_cmd2(uint16_t reg, uint8_t value)
{
	set_shift(reg & 0xFF);
	DSI->write_short(_vchannel, DSI::ShortWriteType::DCS_OneParam, (reg >> 8) & 0xFF, value);
}

void OTM8009::disable_extended_cmd()
{
	set_shift(0x00);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,4,lcdRegData25);
	nop();
}

void OTM8009::nop() {
	using namespace sool::core;
	DSI->write_short(_vchannel, DSI::ShortWriteType::DCS_NoParam, 0x00, 0x00);
}

void OTM8009::dcs_init(MCUColorMode mcu_cm, RGBColorMode rgb_cm)
{

	//Gamma correction
	_send_short(0x00,0x00);
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,17,lcdRegData3);
	nop();

	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,17,lcdRegData4);
	nop();

	//Sleep out
	_send_short(0x11,0x00);
	for(int i =0; i < 500000; i++)
		asm("nop");


	set_color_mode(mcu_cm, rgb_cm);


}

void OTM8009::tearing_effect_on(TEMode mode)
{
	_send_short(0x35,(uint8_t)mode);
}

void OTM8009::tearing_effect_off()
{
	_send_short(0x34,0);
}

void OTM8009::set_color_mode(MCUColorMode mcu_cm, RGBColorMode rgb_cm)
{
	unsigned int colmode = static_cast<uint32_t>(mcu_cm) | static_cast<uint32_t>(rgb_cm);
	_send_short(0x3A,colmode);
}

void OTM8009::set_orientation(Orientation val)
{
	if((val == Orientation::Landscape) != _is_orientation_landscape)
	{
		_send_short(0x36, static_cast<uint32_t>(val));
		_is_orientation_landscape = (val == Orientation::Landscape);
	}
}

void OTM8009::set_resolution(Resolution res)
{
	uint8_t payload[5] = {0,0,0,0,0};
	unsigned int resolution = static_cast<unsigned int>(res);
	if(_is_orientation_landscape)
		payload[0] = 0x2A; //CASET, horizontal resolution
	else
		payload[0] = 0x2B; //PASET, vertival resolution

	payload[4] = resolution & 0xFF;
	payload[3] = (resolution >> 8) & 0xFF;
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,5,payload);

	if(! _is_orientation_landscape)
		payload[0] = 0x2A; //CASET, horizontal resolution
	else
		payload[0] = 0x2B; //PASET, vertival resolution

	// 480px
	payload[4] = 0xDF;
	payload[3] = 0x01;
	DSI->write_long(_vchannel, DSI::LongWriteType::DCS,5,payload);
}

void OTM8009::set_brightness(uint8_t brval)
{
	_send_short(0x51,brval);
}

void OTM8009::enable_backlight()
{
	_send_short(0x53,0x2C);
}

void OTM8009::set_cabm(ContentAdaptativeBrigthnessMode mode, uint8_t minimum)
{
	_send_short(0x55,static_cast<uint32_t>(mode));
	_send_short(0x57,minimum);
}

void OTM8009::display_on()
{
	_send_short(0x29,0x00);
	nop();
	_send_short(0x2C,0x00);
}

void OTM8009::display_off()
{
	_send_short(0x28,0x00);
	/*nop();
	_send_short(0x2C,0x00);*/
}

OTM8009::OTM8009(int vchannel) : _vchannel(vchannel), _shift(0), _is_orientation_landscape(false)
{

}

void OTM8009::init()
{
	enable_extended_cmd();
	setup_voltages();
	nop();
	//disable_extended_cmd();
}

B_LCD40_DSI1::B_LCD40_DSI1(core::LTDC::PixelFormat pfl1,core::LTDC::PixelFormat pfl2) : _disp_ctrl(0),
		_l1_pixel_format(pfl1),
		_l2_pixel_format(pfl2)
{

}

void B_LCD40_DSI1::init_dsi()
{
	using namespace core;
	//LCD_Reset
	GPIOJ->enable_clock();

	PJ15 = GPIO::Mode::Output | GPIO::PuPd::PullUp | GPIO::OutType::PushPull | GPIO::Speed::High;
	//Activate XRES (active low)
	PJ15.write(false);
	//Wait for at least 20ms, here way more.
	for(int i=0; i<500000; i++)
		asm("nop");
	PJ15.write(true);

	//Wait for at least 10ms before sending commands.
	for(int i=0; i<250000; i++)
			asm("nop");

	//Enable screen related clock
	//RCC->APB2ENR.LTDCEN = 1;

	//DMA2D->enable_clock();

	//RCC->APB2ENR.DSI = 1;
	DSI->enable_clock();
	//RCC->APB2ENR |= 1 << 27;

	//DSI PLL setup

	DSI->WRPCR.REGEN = 1;
	while(! DSI->WISR.RRS)
		asm("nop");

	DSI->WRPCR.NDIV = 100;
	DSI->WRPCR.IDF = 5; // Div by 5
	DSI->WRPCR.ODF = 0;

	//Lane clock : 62.5 MHz
	DSI->WRPCR.PLLEN = 1;
	while(! DSI->WISR.PLLLS)
			asm("nop");

	DSI->PCTLR.DEN = 1;
	DSI->PCTLR.CKE = 1;

	//Automatic clock control
	DSI->CLCR.ACR = 0;
	DSI->CLCR.DPCC = 1;

	DSI->CCR.TXECKDIV = 4;
	DSI->WPCR1.UIX4 = 8; // WPCR0 in RM
	DSI->PCONFR.NL = 1; // Two data lanes

	DSI->IER0 = 0;
	DSI->IER1 = 0;

	DSI->MCR.CMDM = 0;
	DSI->WCFGR.DSIM = 0;

	DSI->LCVCIDR.VCID = 0;
	DSI->LPCR.DEP = 0; // Active high
	DSI->LPCR.VSP = 0; // Active high
	DSI->LPCR.HSP = 0; // Active high
	DSI->LCOLCR.COLC = 0b0101; //24bpp
	DSI->WCFGR.COLMUX = 0b101; //24bpp



}

void B_LCD40_DSI1::setup_video_mode()
{
	//Mode vidéo

	DSI->VMCR.VMT = 2; //BURST MODE
	DSI->VPCR.VPSIZE = _HACT; //Nb de pixels dans un paquet
	DSI->VCCCR.NUMC = 0; // Line transmitted in one packet.
	DSI->VNPCR.NPSIZE = 0xFFF; //Unused as we are in burst mode

	//Configuration des timings
	DSI->VHSACR.HSA = 4;
	DSI->VHBPCR.HBP = 77;
	DSI->VLCR.HLINE = 1982;
	DSI->VVSACR.VSA = 1;
	DSI->VVBPCR.VBP = 15;
	DSI->VVFPCR.VFP = 16;
	DSI->VVACR.VA   = 480;

	DSI->VMCR.LPCE = 1;
	DSI->LPMCR.LPSIZE = 16;
	DSI->LPMCR.VLPSIZE = 0;

	DSI->VMCR.LPHBPE = 1;
	DSI->VMCR.LPHFPE = 1;
	DSI->VMCR.LPVAE  = 1;
	DSI->VMCR.LPVFPE = 1;
	DSI->VMCR.LPVBPE = 1;
	DSI->VMCR.LPVSAE = 1;
	DSI->VMCR.FBTAAE = 0;

}
void B_LCD40_DSI1::setup_adapted_command_mode()
{
	//Adapted command mode setup
	//*
	DSI->MCR.CMDM = 1;
	DSI->WCFGR.DSIM = 1;
	//*/
	DSI->LCCR.CMDSIZE = 800;

	//Tearing effect, through DSI Link
	DSI->WCFGR.AR = 0;
	DSI->WCFGR.TESRC = 0;

	DSI->CMCR.TEARE = 1;

	//DSI->PCR.BTAE = 1;

	//DSI->WCR.LTDCEN = 1;
}

void B_LCD40_DSI1::setup_dsi_acm_timings()
{
	DSI->CLTCR.HS2LP_TIME = 35;
	DSI->CLTCR.LP2HS_TIME = 35;

	DSI->DLTCR.MRD_TIME = 10;
	DSI->DLTCR.HS2LP_TIME= 35;
	DSI->DLTCR.LP2HS_TIME = 35;

	DSI->PCONFR.SW_TIME = 4+26; //60ns + 52UI

}


void B_LCD40_DSI1::setup_pattern_generator()
{
	using namespace sool::core;
	//Pattern generator
	DSI->VMCR.PGO = 0; //Horizontal bars
	DSI->VMCR.PGM = 0;
	DSI->VMCR.PGE = 1;
}

void B_LCD40_DSI1::enable_dsi()
{
	using namespace sool::core;
	DSI->WCR.DSIEN = 1;
	DSI->CR.EN = 1;

}

void B_LCD40_DSI1::disable_dsi()
{
	using namespace sool::core;

	DSI->CR.EN = 0;
	DSI->WCR.DSIEN = 0;

}

void B_LCD40_DSI1::enable_screen()
{
	_disp_ctrl.init();
	_disp_ctrl.dcs_init(OTM8009::MCUColorMode::bpp24, OTM8009::RGBColorMode::bpp24);
	_disp_ctrl.set_orientation(OTM8009::Orientation::Landscape);
	_disp_ctrl.set_resolution(OTM8009::Resolution::R480x800);
	_disp_ctrl.set_brightness(0xC2);
	_disp_ctrl.set_cabm(OTM8009::ContentAdaptativeBrigthnessMode::StillPicture,0x80);
	_disp_ctrl.enable_backlight();
	_disp_ctrl.display_on();

}

void OTM8009::refresh()
{
	//_send_short(0x23,0x00);
	nop();
}

void B_LCD40_DSI1::refresh()
{
	DSI->WCR.LTDCEN = 1;
}

void B_LCD40_DSI1::send_display_off()
{
	_disp_ctrl.display_off();
}

void B_LCD40_DSI1::send_display_on()
{
	_disp_ctrl.display_on();
}

void B_LCD40_DSI1::setup_ltdc()
{
	using namespace sool::core;
	LTDC->enable_clock();

	//Configure Pixel Clock

	//Configuration des timings image
	LTDC->SSCR.HSW = 1; //_CONVERT_TO_HFREQ(_HSA - 1);
	LTDC->SSCR.VSH = 0;//_VSA - 1;

	LTDC->BPCR.AHBP= 35;//_CONVERT_TO_HFREQ(_HSA + _HBP -1);
	LTDC->BPCR.AVBP= 15;//_VSA + _VBP -1;

	LTDC->AWCR.AAV = 836;//_CONVERT_TO_HFREQ(_HSA + _HBP + _HACT -1);
	LTDC->AWCR.AAH = 495;//_VSA + _VBP + _VACT -1;

	LTDC->TWCR.TOTALW = 869;//_CONVERT_TO_HFREQ(_HSA + _HBP + _HACT + _HFP -1);
	LTDC->TWCR.TOTALH = 511;//_VSA + _VBP + _VACT + _VFP -1;



	//Synchronous signals and clock polarity setup
	LTDC->GCR.HSPOL = 1; //Active high
	LTDC->GCR.VSPOL = 1; //Active high
	LTDC->GCR.DEPOL = 0; //Active low as per app note requirement.
	LTDC->GCR.PCPOL = 0; //Active high (supposed)

	//Setup background color
	LTDC->BCCR.BC = 0xF0F0F0; //RGB

	//setup interrupts
	//Prepare line value for VSYNC
	LTDC->LIPCR.LIPOS = 	LTDC->AWCR.AAH - 10;
	//Setup layers

	//Enable layers and clut


}

void B_LCD40_DSI1::setup_ltdc_cmdmode()
{

		using namespace sool::core;
		LTDC->enable_clock();

		//Configure Pixel Clock

		LTDC->SSCR.HSW = 1;
		LTDC->SSCR.VSH = 1;

		LTDC->BPCR.AHBP= 2;
		LTDC->BPCR.AVBP= 2;

		LTDC->AWCR.AAV = 802;
		LTDC->AWCR.AAH = 482;

		LTDC->TWCR.TOTALW = 803;
		LTDC->TWCR.TOTALH =483;



		//Synchronous signals and clock polarity setup
		LTDC->GCR.HSPOL = 1; //Active high
		LTDC->GCR.VSPOL = 1; //Active high
		LTDC->GCR.DEPOL = 0; //Active low as per app note requirement.
		LTDC->GCR.PCPOL = 0; //Active high (supposed)

		//Setup background color
		LTDC->BCCR.BC = 0xF0F0F0; //RGB

		//setup interrupts
		//Prepare line value for VSYNC
		LTDC->LIPCR.LIPOS = 	LTDC->AWCR.AAH - 10;
		//Setup layers

		//Enable layers and clut


}

void B_LCD40_DSI1::enable_ltdc()
{
	LTDC->enable();
}

}
}

