/*
 * View.h
 *
 *  Created on: 8 nov. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_VIEW_H_
#define MODULES_GUI_INCLUDE_VIEW_H_

#include "Box.h"
#include "Canvas.h"
namespace sool {
namespace gui {


/*
 * A view is the logical representation of graphical items hierarchy.
 * It also can hold a canvas.
 * If it doesn't have a canvas, the relative canvas is the parent's one.
 *
 * In any cases, the view is able to provide an "absolute box" which is a box matching its own box,
 * but with regards to the master's position in the canvas
 */
class View {

protected:

	View* _parent;
	View* _child;
	View* _sister;

	Canvas* _cnv;
	Box _box;

	bool _visible;

	View* _last_child() const;

	View(const Box& aBox,View* parent = nullptr,Canvas* aCnv = nullptr);


	virtual void _pre_draw_handler(Box* redraw_area) = 0;
	virtual void _post_draw_handler(Box* redraw_area) = 0;

public:

	void add_child(View* aView);
	Box get_absolute_box() const;

	Canvas* get_canvas() const;

	void draw(const Box& redraw_area);
	void invalidate(const Box& invalid_area);
	void invalidate();

	void show();
	void hide();

	void move_to(int x, int y);
	bool is_visible();
};

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_VIEW_H_ */
