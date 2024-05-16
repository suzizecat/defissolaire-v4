/*
 * NWidget.h
 *
 *  Created on: 9 nov. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_NWIDGET_H_
#define MODULES_GUI_INCLUDE_NWIDGET_H_

#include "View.h"
#include "Box.h"
#include "Canvas.h"
namespace sool {
namespace gui {

class NWidget : public View
{
public :
	enum class State : int
	{
		Idle = 0,
		Pressed,
		Disabled,
		LAST
	};
protected:

	State _state;
	const TextFormat_t* _styles[(int)State::LAST];


	NWidget(const Box& aBox, const TextFormat_t* default_style, View* parent = nullptr, Canvas* aCanvas = nullptr);
	virtual void _pre_draw_handler(Box* redraw_area) = 0;
	virtual void _post_draw_handler(Box* redraw_area) = 0;
public:

	inline void set_style(const State aState,const TextFormat_t* style)
	{
		_styles[(int)aState] = style;
	};
};

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_NWIDGET_H_ */
