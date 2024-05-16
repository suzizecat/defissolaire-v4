/*
 * Area.cpp
 *
 *  Created on: 9 nov. 2020
 *      Author: julien
 */

#include <Area.h>

namespace sool {
namespace gui {

Area::Area(const Box& aBox, const TextFormat_t* style, View* parent, Canvas* aCanvas) :
		NWidget(aBox, style, parent, aCanvas)
{
}

void Area::_pre_draw_handler(Box *redraw_area)
{
	Canvas* drw = get_canvas();
	Box abs = get_absolute_box();
	Box abs_redraw_area = Box(*redraw_area).absolutize(abs);

	const TextFormat_t* style = _styles[(int)_state];
	drw->fill_area(abs_redraw_area, style->color_bg);
	//*redraw_area = Box(_box).relativize(_box);
}

} /* namespace gui */
} /* namespace sool */
