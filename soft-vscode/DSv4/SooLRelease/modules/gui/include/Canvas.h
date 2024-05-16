/*
 * Canva.h
 *
 *  Created on: 26 sept. 2020
 *      Author: julien
 */

#ifndef MODULES_GUI_INCLUDE_CANVAS_H_
#define MODULES_GUI_INCLUDE_CANVAS_H_

#include <DMA2D.h>
#include "../include/Font.h"
#include "Box.h"
namespace sool {
namespace gui {

class Canvas
{
	volatile uint32_t* _buffer;
	Box _box;

	bool _ready;
	int _lock;
	bool _updated;
protected:
	void _write_c(int x,const int y,const char c, const Font_t& font,const uint32_t fg_color,const uint32_t bg_color);

public:
	Canvas(volatile uint32_t* buffer,const unsigned int size_x,const unsigned int size_y);
	Canvas(volatile uint32_t* buffer,const Box& aBox);

	//int bit_position(int x, int y) const;
	void setup_dma2d_target(int x, int y, int width, int height) const;
	void setup_dma2d_target(const Box& box) const;

	void fill_area(int x, int y, int width, int height,const  uint32_t color);
	void fill_area(const Box& aBox, const uint32_t color);
	void fill_area(const uint32_t color);

	void display_buffer(const volatile uint32_t* const buffer , const Box& box);

	void write_at(int x, int y, const Font_t& font, uint32_t fg, uint32_t bg,const char* text);
	void write_at(const int x,const int y,const Font_t& font,const char* text);
	void write_at(int x,const int y,const TextFormat_t& tf,const char *text);


	inline bool is_ready() const {return _ready && sool::core::DMA2D->is_ready();};
	inline bool is_available() const {return !_lock && is_ready();};
	void wait_ready() const;
	void wait_available() const;

	inline bool is_updated() const {return _updated;};
	inline void clear_updated() {_updated = false;};

	inline void lock() {_lock ++;};
	inline void unlock()
	{
		if(_lock > 0)
			_lock --;
		else
			_lock = 0;
	}

	inline void set_buffer(volatile uint32_t* buffer_addr) {_buffer = buffer_addr;};
	inline volatile uint32_t* get_buffer() const {return _buffer;};
	inline Box get_box() const {return Box(_box);};

};

} /* namespace gui */
} /* namespace sool */

#endif /* MODULES_GUI_INCLUDE_CANVAS_H_ */
