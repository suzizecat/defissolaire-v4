#include "bsp_as5047p.h"
#include "bsp_init.h"

int bsp::AS5047P::current_motor = 0;
const bsp::AS5047P::Frame_t bsp::AS5047P::NOP = {0x4000};

void bsp::AS5047P::set_current_motor(int mot)
{
    current_motor = mot;
}

void bsp::AS5047P::set_parity(Frame_t & frame)
{
    bool parity = true;

    for(int i = 0; i<15; i++)
        parity = (frame.raw & (1 << i)) == 0 ? parity : !parity;

    frame.command.PARITY = parity ? 1 : 0;
}

uint16_t bsp::AS5047P::read_register(uint16_t address)
{
    Frame_t to_send = {0};
    to_send.command.ADDR = address;
    to_send.command.READ = 1;
    
    set_parity(to_send);

    bsp_spi_exchange(current_motor,to_send.raw);
    return bsp_spi_exchange(current_motor,NOP.raw);
}

uint16_t bsp::AS5047P::write_register(uint16_t address, uint16_t data)
{
    Frame_t to_send = {0};
    to_send.command.ADDR = address;
    to_send.command.READ = 0;
    
    bool parity = true;

    set_parity(to_send);

    bsp_spi_exchange(current_motor,to_send.raw);

    to_send.data.DATA = data;
    set_parity(to_send);
    return bsp_spi_exchange(current_motor,to_send.raw);
}
