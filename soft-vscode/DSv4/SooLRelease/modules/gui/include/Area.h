/*
 * Area.h
 *
 *  Created on: 9 nov. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_AREA_H_
#define MODULES_GUI_INCLUDE_AREA_H_

#include <NWidget.h>

namespace sool {
namespace gui {

class Area: public NWidget
{

protected:
	virtual void _pre_draw_handler(Box* redraw_area);
	inline virtual void _post_draw_handler(Box* redraw_area){};
public:
	Area(const Box& aBox,const TextFormat_t* style, View* parent = nullptr, Canvas* aCanvas = nullptr);

};

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_AREA_H_ */
