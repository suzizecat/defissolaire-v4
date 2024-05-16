/*
 * View.cpp
 *
 *  Created on: 8 nov. 2020
 *      Author: julien
 */

#include <View.h>

namespace sool {
namespace gui {

View::View(const Box& aBox,View* parent,Canvas* aCnv) : _cnv(aCnv), _box(aBox), _visible(true)
{
	if(parent != nullptr)
		parent->add_child(this);
}

void View::add_child(View *aView)
{
	View* lc = _last_child();

	if(lc == nullptr)
		_child = aView;
	else
		lc->_sister = aView;
	aView->_parent = this;
}

View* View::_last_child() const
{
	if(_child == nullptr)
		return nullptr;
	View* r = _child;
	while(r->_sister != nullptr)
		r = r->_sister;

	return r;
}

Box View::get_absolute_box() const
{
	Box ret(_box);

	if(_cnv != nullptr || _parent == nullptr)
		return ret;

	View* p = _parent;
	do
	{
		ret.absolutize(p->_box);
	}while(p->_cnv == nullptr && (p = p->_parent) !=  nullptr);

	return ret;
}

void View::draw(const Box& redraw_area)
{
	if(! is_visible())
		return;

	Box area(redraw_area);
	//area.relativize(_box);
	_cnv->lock();
	_pre_draw_handler(&area);

	if(_child != nullptr)
	{
		View* c = _child;
		do
		{
			if(area.intersect(c->_box))
				c->draw(Box(area).crop_to(c->_box).relativize(c->_box));
			c = c->_sister;
		}while(c != nullptr);
	}

	_post_draw_handler(&area);
	_cnv->unlock();

}
/*
void View::draw(const Box& redraw_area)
{
	if(! is_visible())
		return;

	Box area(redraw_area);
	//area.relativize(_box);
	_cnv->lock();
	_pre_draw_handler(&area);

	if(_child != nullptr)
	{
		View* c = _child;
		do
		{
			if(area.intersect(c->_box))
				c->draw(Box(area).crop_to(c->_box).relativize(c->_box));
			c = c->_sister;
		}while(c != nullptr);
	}

	_post_draw_handler(&area);
	_cnv->unlock();

}*/


Canvas* View::get_canvas() const
{
	const View* curr = this;
	do
	{
	if(curr->_cnv != nullptr)
		return curr->_cnv;

	curr = curr->_parent;
	}while(curr != nullptr);

	return nullptr;
}

void View::invalidate(const Box& invalid_area)
{
	View* master = this;
	Box context(invalid_area);


	while(! master->_box.contains(context) && master->_parent != nullptr)
	{
		master = master->_parent;
		context.absolutize(master->_box);
	}

	//The draw area must be relative to the View which will draw it.
	master->draw(context.relativize(master->_box));
}

void View::invalidate()
{
	invalidate(_box);
}


void View::show()
{
	_visible = true;
	invalidate(_box);
}
void View::hide()
{
	_visible = false;
	if(_parent != nullptr)
		_parent->invalidate();
}

void View::move_to(int x, int y)
{
	Box save(_box);
	_box.x = x;
	_box.y = y;
	if(! get_canvas()->get_box().contains(get_absolute_box()))
		_box = save;
	else
	{
		int x1 = save.x < _box.x ? save.x : _box.x;
		int x2 = save.x2() > _box.x2() ? save.x2() : _box.x2();
		int y1 = save.y < _box.y ? save.y : _box.y;
		int y2 = save.y2() > _box.y2() ? save.y2() : _box.y2();

		invalidate(Box(x1,y1,x2-x1,y2-y1));


	}
}

bool View::is_visible()
{
	View* v = this;
	while(v != nullptr)
	{
		if(! v->_visible)
			return false;
		v = v->_parent;
	}
	return true;
}

} /* namespace gui */
} /* namespace sool */
