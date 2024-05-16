/*
 * NButton.cpp
 *
 *  Created on: 9 nov. 2020
 *      Author: julien
 */

#include <NButton.h>

namespace sool {
namespace gui {

NButton::NButton(const Box& aBox, const TextFormat_t* idle_style, View* parent, Canvas* aCanvas) :
		NWidget(aBox, idle_style, parent, aCanvas),
		_on_press_handler(nullptr),
		_on_release_handler(nullptr),
		_text(nullptr)
{
}

void NButton::_pre_draw_handler(Box *redraw_area)
{
	Canvas* drw = get_canvas();
	Box abs_box = get_absolute_box();
	const TextFormat_t* style = _styles[(int)_state];
	drw->fill_area(abs_box, style->color_bg);

	drw->wait_ready();
	if(_text != nullptr)
		drw->write_at(abs_box.x + 5, abs_box.y +  (abs_box.h/2) - (style->font->height/2), *style, _text);
}

void NButton::_post_draw_handler(Box *redraw_area)
{
	// Nothing
}


void NButton::press()
{
	if(_state != State::Pressed)
	{
		if(_on_press_handler != nullptr)
			_on_press_handler();
		_state = State::Pressed;
		invalidate();
	}
}

void NButton::release()
{
	if(_state != State::Idle)
	{
		if(_on_release_handler != nullptr)
			_on_release_handler();
		_state = State::Idle;
		invalidate();
	}
}

} /* namespace gui */
} /* namespace sool */
