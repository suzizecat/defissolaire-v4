/*
 * Box.h
 *
 *  Created on: 24 oct. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_BOX_H_
#define MODULES_GUI_INCLUDE_BOX_H_

namespace sool {
namespace gui {

struct Box
{
public:
	enum class Cadrant
	{
		/* V
		 *H1|2|3
		 * -+-+-
		 * 2|#|
		 * -+-+-
		 * 3| |
		 */


		H1 = 1 << 0,
		H2 = 1 << 1,
		H3 = 1 << 2,
		V1 = 1 << 3,
		V2 = 1 << 4,
		V3 = 1 << 5,
		Hmsk = H1 | H2 | H3,
		Vmsk = V1 | V2 | V3
	};

	Cadrant get_cadrant(const int aX, const int aY) const;
	Box(const int x, const int y,const int w = 1,const int h = 1);
	Box(const Box& o);
	Box(const int coord[4]);
	Box();

	int x;
	int y;
	int w;
	int h;

	inline int bit_position(int aX, int aY) const
	{
			return aY * w + aX;
	};

	inline int x2() const {return x + w;};
	inline int y2() const {return y + h;};

	bool contains(const int aX, const int aY) const;
	bool contains(const Box& aBox) const;

	bool intersect(const Box& aBox) const;

	inline Box& absolutize(const Box& ref) {x += ref.x ; y += ref.y; return *this;};
	inline Box& relativize(const Box& ref) {x -= ref.x ; y -= ref.y; return *this;};
	Box& normalize();

	Box& crop_to(const Box& other);


};

inline const Box::Cadrant operator|(const Box::Cadrant a,const Box::Cadrant b) {return static_cast<Box::Cadrant>(static_cast<int>(a) | static_cast<int>(b));};
inline const Box::Cadrant operator&(const Box::Cadrant a,const Box::Cadrant b) {return static_cast<Box::Cadrant>(static_cast<int>(a) & static_cast<int>(b));};
inline Box::Cadrant& operator|=(Box::Cadrant& a,const Box::Cadrant& b){a = a | b; return a;};
inline bool operator!=(Box::Cadrant& a, Box::Cadrant& b) {return static_cast<int>(a) != static_cast<int>(b);};



} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_BOX_H_ */
