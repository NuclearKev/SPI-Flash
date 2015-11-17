/* This library can be used to communicate to a Micron 16-bit serial flash device.
This library uses some pre-written functions written by Xilinx.

This library is released under the GNU LGPLv3 or higher. Enjoy. */

#ifndef _SPIFLASH_H_
#define _SPIFLASH_H_

#include "xgpio.h"
#include "xspips.h"

void enableWrite(XGpio *SSptr, XSpiPs *SPIptr);
uint8_t readStatusRegister(XGpio *SSptr, XSpiPs *SPIptr);
void eraseSector(XGpio *SSptr, XSpiPs *SPIptr, uint32_t startAddress);
void pageProgram(XGpio *SSptr, XSpiPs *SPIptr, uint32_t address, uint8_t data[], uint32_t size);
uint8_t *readData(XGpio *SSptr, XSpiPs *SPIptr, uint32_t startAddress, uint32_t bytes);

#endif //spiflash_h
