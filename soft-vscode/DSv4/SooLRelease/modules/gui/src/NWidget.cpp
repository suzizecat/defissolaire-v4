/*
 * NWidget.cpp
 *
 *  Created on: 9 nov. 2020
 *      Author: julien
 */

#include <NWidget.h>

namespace sool {
namespace gui {

NWidget::NWidget(const Box& aBox,const TextFormat_t* default_style, View* parent, Canvas* aCanvas ) :
		View(aBox, parent, aCanvas) , _state(State::Idle)
{
	for(int i = 0; i < (int)State::LAST; i++)
	{
		set_style((State)i, default_style);
	}
}

} /* namespace gui */
} /* namespace sool */
