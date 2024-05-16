/*
 * b-lcd40-dsi1.h
 *
 *  Created on: 11 sept. 2020
 *      Author: julien
 */

#ifndef MODULES_BSP_INCLUDE_B_LCD40_DSI1_H_
#define MODULES_BSP_INCLUDE_B_LCD40_DSI1_H_

#include <LTDC.h>
#include <DSI.h>
#include <RCC.h>
#include <GPIO.h>

namespace sool {
namespace bsp {

	class OTM8009
	{
	private:




		const int _vchannel;
		unsigned int _shift;
		bool _is_orientation_landscape;

		void _send_short(uint8_t reg,uint8_t value);
		void _send_short_cmd2(uint16_t reg,uint8_t value);


	public:

		enum class MCUColorMode : uint32_t
		{
			bpp12 = 0x03,
			bpp16 = 0x05,
			bpp18 = 0x06,
			bpp24 = 0x07

		};

		enum class RGBColorMode : uint32_t
		{
			bpp12 = 0x30,
			bpp16 = 0x50,
			bpp18 = 0x60,
			bpp24 = 0x70,
			bpp24_3DT = 0xE0
		};

		enum class Orientation : uint32_t
		{
			Portrait = 0x00,
			Landscape= 0x60
		};

		enum class Resolution : uint32_t
		{
			R480x864 = 0x035F,
			R480x854 = 0x0355,
			R480x800 = 0x031F,
			R480x720 = 0x02CF,
			R480x640 = 0x027F,
			R480x480 = 0x01DF,
			R480x360 = 0x0167
		};

		enum class ContentAdaptativeBrigthnessMode : uint32_t
		{
			Off = 0,
			UserInterface = 1,
			StillPicture = 2,
			MovingImage = 3
		};

		enum class TEMode : uint8_t
		{
			VSync = 0,
			VSync_HBlink = 1
		};

		OTM8009(int vchannel);
		void enable_extended_cmd();
		void disable_extended_cmd();
		void set_shift(uint8_t val);
		void set_color_mode(MCUColorMode mcu_cm, RGBColorMode rgb_cm);
		void setup_voltages();
		void set_orientation(Orientation val);
		void set_resolution(Resolution res);
		void set_brightness(uint8_t brval);
		void set_cabm(ContentAdaptativeBrigthnessMode mode, uint8_t minimum);
		void enable_backlight();
		void dcs_init(MCUColorMode mcu_cm, RGBColorMode rgb_cm);
		void tearing_effect_on(TEMode mode = TEMode::VSync);
		void tearing_effect_off();
		void display_on();
		void display_off();

		void nop();
		void init();

		void refresh();

	};


	class B_LCD40_DSI1
	{
	private:
		//Timings


/*
		static constexpr unsigned int _VACT  = 480;
		static constexpr unsigned int _VSA	 = 1;
		static constexpr unsigned int _VBP	 = 15;
		static constexpr unsigned int _VFP	 = 16;

		static constexpr unsigned int _HACT  = 800;
		static constexpr unsigned int _HSA   = 2;
		static constexpr unsigned int _HBP   = 34;
		static constexpr unsigned int _HFP   = 34;
/*/
		static constexpr unsigned int _VACT  = 480;
		static constexpr unsigned int _VSA	 = 2;
		static constexpr unsigned int _VBP	 = 20;
		static constexpr unsigned int _VFP	 = 20;

		static constexpr unsigned int _HACT  = 800;
		static constexpr unsigned int _HSA   = 10;
		static constexpr unsigned int _HBP   = 15;
		static constexpr unsigned int _HFP   = 16;

		static constexpr unsigned int _H_FREQ_FACTOR   = 22786;
		static constexpr unsigned int _H_FREQ_DIV      = 10000;
//*/
		static constexpr unsigned int _CONVERT_TO_HFREQ(unsigned int v)
		{
			//Integer divide, multiplication first then divide.
			return (v * _H_FREQ_FACTOR) / _H_FREQ_DIV;
		};

		OTM8009 _disp_ctrl;
		core::LTDC::PixelFormat _l1_pixel_format;
		core::LTDC::PixelFormat _l2_pixel_format;
	public:
		B_LCD40_DSI1(core::LTDC::PixelFormat pfl1 = core::LTDC::PixelFormat::ARGB8888,
					 core::LTDC::PixelFormat pfl2 = core::LTDC::PixelFormat::ARGB8888);
		void init_dsi();
		void setup_video_mode();
		void setup_adapted_command_mode();
		void setup_pattern_generator();
		void setup_ltdc();
		void setup_ltdc_cmdmode();
		void enable_ltdc();
		void enable_dsi();
		void disable_dsi();
		void enable_screen();
		void send_display_off();
		void send_display_on();
		void setup_dsi_acm_timings();
		inline void allow_dsi_lp_commands(bool allow)
		{
			using namespace sool::core;
			if(allow)
				DSI->CMCR |= 0x7FF << 8;
			else
				DSI->CMCR &= ~(0x7FF << 8);
		}

		void refresh();

	};

}
}



#endif /* MODULES_BSP_INCLUDE_B_LCD40_DSI1_H_ */
