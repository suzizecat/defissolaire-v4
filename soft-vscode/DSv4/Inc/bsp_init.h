#pragma once 
#ifndef _BSP_INIT_H
#define _BSP_INIT_H
#include <cstdint>
/**
 * @brief The frequency equivalent to the delay to use for the SPI
 * 
 * @details it is equivalent to 1/350ns and allows a proper division by CoreClock
 * without using floats.
 * 
 */
#define BSP_WAIT_FREQUENCY 2857142
#define WAIT asm("nop")

extern int SPI_WAIT_DELAY;

void bsp_setup_rcc();
void bsp_setup_spi();
void bsp_setup_uart();

uint16_t bsp_spi_exchange(int mot, uint16_t data_tx);

#endif // _BSP_INIT_H