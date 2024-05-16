/*
 * NButton.h
 *
 *  Created on: 9 nov. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_NBUTTON_H_
#define MODULES_GUI_INCLUDE_NBUTTON_H_

#include "NWidget.h"

namespace sool {
namespace gui {

class NButton : public NWidget
{
protected:
	void (* _on_press_handler)();
	void (* _on_release_handler)();


	const char* _text;

	virtual void _pre_draw_handler(Box* redraw_area);
	virtual void _post_draw_handler(Box* redraw_area);

public:

	NButton(const Box& aBox,const TextFormat_t* idle_style, View* parent = nullptr, Canvas* aCanvas = nullptr);

	void press();
	void release();
	inline void set_press_handler(void(*aHandler)())   {_on_press_handler = aHandler;};
	inline void set_release_handler(void(*aHandler)()) {_on_release_handler = aHandler;};
	inline void set_text(const char* aLabel) {_text = aLabel;};

};

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_NBUTTON_H_ */
