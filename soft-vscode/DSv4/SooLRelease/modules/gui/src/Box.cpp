/*
 * Box.cpp
 *
 *  Created on: 24 oct. 2020
 *      Author: julien
 */

#include <Box.h>

namespace sool {
namespace gui {

Box::Box(const int x,const int y,const int w,const int h) : x(x), y(y), w(w), h(h)
{}


Box::Box(const Box& o) : x(o.x), y(o.y), w(o.w), h(o.h)
{}

Box::Box(const int coord[4]) : x(coord[0]), y(coord[1]), w(coord[2]), h(coord[3])
{}

Box::Box() : x(0), y(0), w(0), h(0) {}
bool Box::contains(int aX, int aY) const
{
	return aX >= x && aX <= x + w && aY >= y && aY <= y + h;
}

bool Box::contains(const Box& aBox) const
{
	return contains(aBox.x,aBox.y) && contains(aBox.x2(), aBox.y2());
}


Box::Cadrant Box::get_cadrant(const int aX,const int aY) const
{
	/* V
	 *H1|2|3
	 * -+-+-
	 * 2|#|
	 * -+-+-
	 * 3| |
	 */

	Box::Cadrant r;

	if(aX < x)
		r = Cadrant::H1;
	else if(aX > x2())
		r = Cadrant::H3;
	else
		r = Cadrant::H2;

	if(aY < y)
		r |=  Cadrant::V1;
	else if(aY > y2())
		r |= Cadrant::V3;
	else
		r |= Cadrant::V2;

	return r;
}

bool Box::intersect(const Box & b) const
{
	Cadrant p1 = get_cadrant(b.x, b.y);
	Cadrant p2 = get_cadrant(b.x2(),b.y2());

	const bool hrule = (p1 & Cadrant::Hmsk) != (p2 & Cadrant::Hmsk) || (p1 & Cadrant::H2) == Cadrant::H2;
	const bool vrule = (p1 & Cadrant::Vmsk) != (p2 & Cadrant::Vmsk) || (p1 & Cadrant::V2) == Cadrant::V2;
	return  hrule && vrule;
}

Box& Box::crop_to(const Box &other)
{
	Box r = Box(other).normalize();
	normalize();

	int lx1 = (r.x > x) ? r.x : x;
	int ly1 = (r.y > y) ? r.y : y;
	int lx2 = (r.x2() < x2()) ? r.x2() : x2();
	int ly2 = (r.y2() < y2()) ? r.y2() : y2();

	x = lx1;
	y =	ly1;
	w =	lx2 - lx1;
	h =	ly2 - ly1;
	return *this;

}


Box& Box::normalize()
{
	if(w < 0)
	{
		x -= w;
		w *=-1;
	}

	if(h < 0)
	{
		y -= h;
		h *=-1;
	}

	return *this;

}

} /* namespace gui */
} /* namespace sool */
