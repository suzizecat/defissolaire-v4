#pragma once 
#ifndef _BSP_AS5047P_H
#define _BSP_AS5047P_H


#include <stdint.h>


namespace bsp::AS5047P
{

extern int current_motor;

union Frame_t
{
    uint16_t raw;
    struct
    {
        uint16_t PARITY :1; // Even parity bit, calculated on the 15LSB
        uint16_t READ   :1; // Set for read, 0 for write
        uint16_t ADDR   :14;
    } command ;

    struct
    {
        uint16_t PARITY :1; // Even parity bit, calculated on the 15LSB
        uint16_t ERR    :1; // Set if a frame error occured, always at 0 for write data
        uint16_t DATA   :14; 
    } data ;
    
    /* data */
};

extern const Frame_t NOP;


void set_current_motor(int mot);
uint16_t read_register(uint16_t address);
uint16_t write_register(uint16_t address, uint16_t data);
void set_parity(Frame_t& frame);

}
#endif