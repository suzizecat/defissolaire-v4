/*
 * Font.h
 *
 *  Created on: 28 sept. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_FONT_H_
#define MODULES_GUI_INCLUDE_FONT_H_

#include <cstdint>
namespace sool {
namespace gui {

typedef struct Font_t
{
public:
	const int height;
	const int width;
	const uint8_t* table;

	inline int line_byte_size() const
	{
		return (width / 8) + ((width > 8 && width % 8 != 0) ? 1 : 0);
	};

	inline int char_start(const char c) const
	{
		return (c - ' ') * line_byte_size() * height;
	};


} Font_t;

typedef struct TextFormat_t
{
public:
	const Font_t* font;
	uint32_t color_fg;
	uint32_t color_bg;
} TextFormat_t;

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_FONT_H_ */
