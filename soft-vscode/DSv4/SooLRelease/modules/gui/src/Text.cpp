/*
 * TextArea.cpp
 *
 *  Created on: 10 nov. 2020
 *      Author: julien
 */

#include <Text.h>

namespace sool {
namespace gui {

Text::Text(const Box &aBox, const TextFormat_t *style,
		char *text, View *parent, Canvas *aCanvas) : Area(aBox, style, parent, aCanvas), _text(text)
{
	refresh_box();
}



void Text::_pre_draw_handler(Box *redraw_area)
{
	Canvas* drw = get_canvas();
	Box abs_box = get_absolute_box();
	drw->write_at(abs_box.x, abs_box.y, *_styles[(int)_state], _text);
}

void Text::refresh_box()
{
	if (_text[0] == 0)
	{
		_box.w = 1;
		_box.h = 1;
	}

	const Font_t* font = _styles[(int)_state]->font;

	int xmax = 0;
	int ylen = font->height;
	int text_index = 0;
	int x = 0;
	char c;


	while((c = _text[text_index++]) != 0)
	{
		if(c != '\n')
		{
			x += font->width;
		}
		else
		{
			if(x > xmax)
				xmax = x;
			x = 0;
			ylen += font->height;
		}
	}

	if(x > xmax)
		xmax = x;

	_box.w = xmax;
	_box.h = ylen;

}

} /* namespace gui */
} /* namespace sool */
