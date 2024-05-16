/*
 * TextArea.h
 *
 *  Created on: 10 nov. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_TEXT_H_
#define MODULES_GUI_INCLUDE_TEXT_H_

#include <Area.h>

namespace sool {
namespace gui {

class Text: public Area
{
protected:
	char* _text;
	virtual void _pre_draw_handler(Box* redraw_area);

public:
	Text(const Box& aBox,const TextFormat_t* style, char* text, View* parent = nullptr, Canvas* aCanvas = nullptr);

	void refresh_box();

};

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_TEXT_H_ */
