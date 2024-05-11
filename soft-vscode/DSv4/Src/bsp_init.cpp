#include "bsp_init.h"
#include "sool_setup.h"

#include <system_stm32.h>

#include "RCC.h"
#include "PWR.h"
#include "FLASH.h"
#include "SPI.h"
#include "GPIO.h"
#include "USART.h"
#include "TIM.h"
#include <stdint.h>

using namespace sool::core;

int SPI_WAIT_DELAY = 0;

void bsp_setup_rcc()
{	
	PWR->CR1.VOS = 0b01; // Use core voltage range "1" (high performances, not low power)
	while(PWR->SR2.VOSF)
		asm("nop");

	// Setup 4WS of flash latency in prevision of 80MHz 
	FLASH->ACR.LATENCY = 4;
	/*
	By default, the MSI is used. 
	Setup the HSI (16MHz) with a /2 prediv on the PLL or the HSE without prediv.
	*/
	RCC->CR.HSION = 0b1;

	RCC->PLLCFGR.PLLM = 2-1; // Divides by two, - Used with HSI at 16MHz
	RCC->PLLCFGR.PLLN = 20-1; // Times 20, output shall be >64MHz (here 160MHz)
	RCC->PLLCFGR.PLLR = 0; // Divides by Two
	// Output shall be at 80MHz

	// Await that all subsequent oscillators are ready:
	while(! RCC->CR.HSIRDY)
		asm("nop");


	// PLL Source, shall be : 10 for HSI and 11 for HSE, 00 For ultra low power (no clock).
	RCC->PLLCFGR.PLLSRC = 0b10;
	RCC->PLLCFGR.PLLPEN = 1;

	// Actually start the PLL 
	RCC->CR.PLLON = 1;
	while(! RCC->CR.PLLRDY)
		asm("nop");

	// Select the PLL as the system clock source
	RCC->CFGR.SW = 0b11;
	while(RCC->CFGR.SWS != 0b11)
		asm("nop");

	// Disable the (now unused) MSI
	RCC->CR.MSION = 0;

	SystemCoreClockUpdate();
}


/**
 * @brief Setup the SPI1 peripheral to connect to the two encoders.
 * 
 * @details As we are restricted by the poor performances of the SPI IP, we will work
 * by manually setting the CSn pin and performing manual waits where required.
 * Therefore, no interrupts, no DMA, almost no automated management.
 * 
 */
void bsp_setup_spi()
{
	SPI1->enable_clock();
	GPIOB->enable_clock();
	GPIOC->enable_clock();

	SPI1->CR1.CPOL = 0;
	SPI1->CR1.CPHA = 1;
	SPI1->CR1.MSTR = 1;
	// Prescaler of 2**4 = 16, giving 5MHz with regards to 10MHz max.
	// May be reduced by increasing BR as very low ammount of data and 
	// Fairly bad connection quality for high-speed. 
	SPI1->CR1.BR   = 4-1; 
	SPI1->CR1.LSBFIRST = 0;
	
	// As SPI CSn hardware management is absolutely useless, use software CSn
	// to manually driver the appropriate CSn pin.
	SPI1->CR1.SSM = 1; 

	// Do *not* use the "bidirectional" mode where one wire is used as tri-state
	// for MISO and MOSI.
	SPI1->CR1.BIDIMODE = 0;

	SPI1->CR2.DS = 16-1; // 16 bits data 

	// The SPI is ready to be started, but SPIEN shall only be used alongside a transmission.
}

void bsp_setup_uart()
{
	USART2->enable_clock();

	// Default to 1 START bit, 8 data bits 
	USART2->CR1 = 0;
	
	USART2->CR1.PCE = 0; // No parity
	USART2->CR1.PS = 0;  // Even parity, 1 for Odd
	
	USART2->CR2.MSBFIRST = 0; 
	USART2->CR2.SWAP = 0; // If required (oups) swap RX and TX pins 
	USART2->CR2.STOP = 0; // 1 Stop bit 

	// Compute the baudrate from the system core clock
	// The input clock is actually PCLK (which is after SYSCLK)
	// But the divider is 1.
	USART2->BRR = (SystemCoreClock / 9600) -1;  

	//Enable
	USART2->CR1.RXNEIE = 1;

	USART2->CR1.TE = 1;
	USART2->CR1.RE = 1;
	USART2->CR1.UE = 1;

	NVIC_SetPriority(IRQn_Type::USART2_IRQn,1);
	NVIC_EnableIRQ(IRQn_Type::USART2_IRQn);
}

/**
 * @brief Setup the TIM1 for RADIO capture
 * 
 * @note TIM1 Will receive all radio signals in input capture mode.
 * As the signal is 1 to 2ms active at 20ms frequency, the resolution
 * will be 1MHz to capture a value between 1000 to 2000 for a 20'000 
 * period (shall be < 16 bits).
 * 
 * @note The update event will be used to trigger the DMA and send data
 * to a variable that may be used by the main program.
 * It will induce a period of latency between the command and its processing
 * which is not important as this is the RC command.
 * 
 */
void bsp_init_tim_radio()
{
	RCC->APB2ENR.TIM1EN = 1;
	RCC->APB2RSTR.TIM1RST = 1;
	WAIT;
	RCC->APB2RSTR.TIM1RST = 0;
	// It is required to have an input Capture Compare mode

	TIM1->CR1 = 0;
	TIM1->CR2.CCDS = 1; // Trigger DMA on update event, not on capture event.
	
	TIM1->PSC = 80-1; // Given a 80MHz input clock, provides one tick at 1MHz
	TIM1->ARR = 20'000 -1; // As 1ms is 1e3 points, set period to 20ms
	TIM1->RCR = 0 ; // All overflow will trigger an update event

	// No filter, no prescaling
	TIM1->CCMR1_Input.CC1S = 0b01; // Map TIM channel 1 on IC channel 1 as input
	TIM1->CCMR1_Input.CC2S = 0b01; // Map TIM channel 2 on IC channel 2 as input
	TIM1->CCMR2_Input.CC3S = 0b01; // Map TIM channel 3 on IC channel 3 as input
	TIM1->CCMR2_Input.CC4S = 0b01; // Map TIM channel 4 on IC channel 4 as input


	// As we want to capture on the falling edge, we set the polarity appropriately.
	// Might be needed to check in order to *start* the capture on rising edge.

	TIM1->CCER = 0x2222; // Use a direct value as SooL seems to have an issue on this register.

	// Actually enable the capture counter.
	TIM1->CCER.CC1E = 1;
	TIM1->CCER.CC2E = 1;
	TIM1->CCER.CC3E = 1;
	TIM1->CCER.CC4E = 1;

	// Finally enable the timer.
	TIM1->CR1.CEN = 1;
}

void bsp_spi_enable()
{
	// Update the wait delay with a ceil logic
	SPI_WAIT_DELAY = 1 + (SystemCoreClock / BSP_WAIT_FREQUENCY);
	SPI1->CR1.SPE = 1;
}

void bsp_spi_disable()
{
	SPI1->CR1.SPE = 0;
}

void bsp_spi_set_csn(int mot, bool value)
{
	if(mot == 1)
		PC14.write(value);
	else
		PC15.write(value);
}

void bsp_spi_delay()
{
	for(int i = 0; i <= SPI_WAIT_DELAY; i++)
		WAIT;
}


/**
 * @brief Perform an SPI transmission and return the received data
 * 
 * @param mot Motor to send the data to
 * @param data_tx Data to send
 * @return uint16_t Received data
 */
uint16_t bsp_spi_exchange(int mot, uint16_t data_tx)
{
	bsp_spi_set_csn(mot,false);
	bsp_spi_delay();

	SPI1->DR.DR = data_tx;

	while(SPI1->SR.BSY == 1)
		WAIT;

	uint16_t ret = SPI1->DR.DR;

	bsp_spi_delay();
	bsp_spi_set_csn(mot,true);
	bsp_spi_delay();
}


