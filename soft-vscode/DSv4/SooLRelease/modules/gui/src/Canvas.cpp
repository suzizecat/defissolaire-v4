/*
 * Canva.cpp
 *
 *  Created on: 26 sept. 2020
 *      Author: julien
 */

#include <Canvas.h>

namespace sool {
namespace gui {

Canvas::Canvas(volatile uint32_t* buffer,const unsigned int size_x,const unsigned int size_y) : _buffer(buffer), _box(0,0,size_x,size_y), _ready(true)
 {}

Canvas::Canvas(volatile uint32_t* buffer,const Box& aBox) : _buffer(buffer), _box(aBox), _ready(true)
{}


void Canvas::setup_dma2d_target(int x, int y, int width, int height) const
{
	using namespace sool::core;
	while(! DMA2D->is_ready())
		asm("nop");
	if(x + width > _box.w || y + height > _box.h)
		return;

	DMA2D->OPFCCR.CM = 0; //ARGB8888;
	DMA2D->OMAR = (uint32_t)&(_buffer[_box.bit_position(x,y)]);
	DMA2D->OOR.LO = _box.w - width;
	DMA2D->NLR.PL = width;
	DMA2D->NLR.NL = height;
}

void Canvas::setup_dma2d_target(const Box& box) const
{
	setup_dma2d_target(box.x, box.y, box.w, box.h);
}

void Canvas::display_buffer(const volatile uint32_t* const buffer, const Box& box)
{
	using namespace sool::core;
	DMA2D->set_mode(DMA2D::Mode::Transfer);
	setup_dma2d_target(box);

	DMA2D->FGOR.LO = 0;
	DMA2D->FGMAR = (uint32_t)buffer;
	DMA2D->IFCR.CTCIF = 1;
	DMA2D->CR.START = 1;
	 _updated = true;

}

void Canvas::fill_area(int x, int y, int width, int height, uint32_t color)
{
	using namespace sool::core;
	setup_dma2d_target(x, y, width, height);
	DMA2D->OCOLR = color;
	DMA2D->set_mode(DMA2D::Mode::ColorFill);
	DMA2D->IFCR.CTCIF = 1;
	DMA2D->CR.START = 1;
	_updated = true;
}

void Canvas::fill_area(const Box& aBox, const uint32_t color)
{
	fill_area(aBox.x, aBox.y, aBox.w, aBox.h, color);
}
void Canvas::fill_area(const uint32_t color)
{
	fill_area(_box.x,_box.y,_box.w,_box.h,color);
}


void Canvas::_write_c(const int x, const int y,const char c, const Font_t& font,const uint32_t color_fg,const uint32_t color_bg)
{
	int pix_position;
	int char_position = font.char_start(c);
	for(int i = 0; i < font.height; i ++)
	{
		pix_position = _box.bit_position(x, y+i);
		for(int j = 0; j < font.width; j++)
		{
			if(font.table[char_position + (j/8)] & (1 << (7-j%8)))
				_buffer[pix_position] = color_fg;
			else if(color_bg != 0)
				_buffer[pix_position] = color_bg;
			pix_position ++;
		}
		char_position += font.line_byte_size();
	}
	_updated = true;

}


void Canvas::write_at(int x, int y, const Font_t &font,	uint32_t fg, uint32_t bg,const char *text)
{
	wait_ready();
	lock();
	_ready = false;
	char c = 0;
	int text_index = 0;

	int init_x = x;
	while((c = text[text_index++]) != 0)
	{

		if(c != '\n')
		{
			_write_c(x,y,c,font,fg,bg);
			x += font.width;
		}
		else
		{
			x = init_x;
			y += font.height;
		}
	}

	_ready = true;
	unlock();
}

void Canvas::write_at(int x,const int y,const Font_t& font,const char *text)
{
	write_at(x, y, font, 0xFF000000, 0, text);
}

void Canvas::write_at(int x,const int y,const TextFormat_t& tf,const char *text)
{
	write_at(x, y, *(tf.font), tf.color_fg, tf.color_bg, text);
}

void Canvas::wait_ready() const
{
	while(! is_ready())
		asm("nop");
	/*Todo Add support for OS::wait()*/
}

void Canvas::wait_available() const
{
	while(! is_available())
		asm("nop");
	/*Todo Add support for OS::wait()*/
}

} /* namespace gui */
} /* namespace sool */

