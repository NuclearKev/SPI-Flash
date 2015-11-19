/*

   This is also released under the GNU LGPLv3 and above. Enjoy.

*/

#include <stdint.h>
#include "spiflash.h"
#include <stdlib.h>

void enableWrite(XGpio *SSptr, XSpiPs *SPIptr){

  uint8_t SendBuffer[1] = {0x06}; //write enable command
  
  XGpio_DiscreteWrite(SSptr, 1, 0); //drop slave select
  XSpiPs_PolledTransfer(SPIptr, SendBuffer, NULL, 1);
  XGpio_DiscreteWrite(SSptr, 1, 1); //raise slave select

}


uint8_t readStatusRegister(XGpio *SSptr, XSpiPs *SPIptr){

  uint8_t SendBuffer[1] = {0x05}; //read Status Register command
  uint8_t ReceiveBuffer[2];
  
  XGpio_DiscreteWrite(SSptr, 1, 0);
  XSpiPs_PolledTransfer(SPIptr, SendBuffer, ReceiveBuffer, 2);
  XGpio_DiscreteWrite(SSptr, 1, 1);

  /* Always found in the second array element */
  return ReceiveBuffer[1];
}


/* The most significant byte of startAddress is always 0x00, so the MSB we use
   is the next most significant byte. For example, 0x00123456, 0x12 is our most
   significant byte. This is because we use a 12-bit address on the actual chip.

   Also, the address you send can be ANY address in that sector and it will
   still erase the entire sector. */
void eraseSector(XGpio *SSptr, XSpiPs *SPIptr, uint32_t startAddress){

  uint8_t SendBuffer[4];

  SendBuffer[0] = 0xD8; //erase sector command
  SendBuffer[1] = startAddress >> 16; //grabs most significant byte
  SendBuffer[2] = startAddress >> 8;  //grabs middle byte
  SendBuffer[3] = startAddress;       //grabs least significant byte
  
  XGpio_DiscreteWrite(SSptr, 1, 0);
  XSpiPs_PolledTransfer(SPIptr, SendBuffer, NULL, 4);
  XGpio_DiscreteWrite(SSptr, 1, 1);

}


/* Read the comments for the eraseSector function to understand the addressing
   scheme.
   We always want to send the command then 3 bytes of address, this is why we
   add a 4 to the size of the data array to get the correct size for SendBuffer
   and for the number of bytes sent. ***YOU MUST ERASE THE SECTOR BEFORE WRITING
   TO ANY ADDRESS*** */
void pageProgram(XGpio *SSptr, XSpiPs *SPIptr, uint32_t address, uint8_t data[], uint32_t size){

  uint32_t i, j = size + 4;
  uint8_t SendBuffer[j];


  SendBuffer[0] = 0x02; //page program command
  SendBuffer[1] = address >> 16;
  SendBuffer[2] = address >> 8;
  SendBuffer[3] = address;

  /* puts all data into the SendBuffer AFTER the command and address bytes */
  for(i = 0; i < size; i++){
    SendBuffer[i + 4] = data[i];
  }

  /* ships out all bytes; command, addresses, and data */
  XGpio_DiscreteWrite(SSptr, 1, 0);
  XSpiPs_PolledTransfer(SPIptr, SendBuffer, NULL, j);
  XGpio_DiscreteWrite(SSptr, 1, 1);

}

/* This functions reads "bytes" amount of bytes from the flash. In order to 
return an array correctly, I needed to use malloc function to allocate space 
for it. The last for loop is there because the first 4 bytes of data in the 
received array contain zeros always, we don't need them so I remove them. */
uint8_t *readData(XGpio *SSptr, XSpiPs *SPIptr, uint32_t startAddress, uint32_t bytes){

  uint32_t i, j = bytes + 4; //number of bytes sent AND received
  uint8_t SendBuffer[4];
  uint8_t tempReceiveBuffer[j];
  uint8_t *ReceiveBuffer = (uint8_t*)malloc(sizeof(uint8_t)*bytes); //allocates space for the array

  SendBuffer[0] = 0x03; //read bytes command
  SendBuffer[1] = startAddress >> 16; //grabs most significant byte
  SendBuffer[2] = startAddress >> 8;  //grabs middle byte
  SendBuffer[3] = startAddress;       //grabs least significant byte
  
  XGpio_DiscreteWrite(SSptr, 1, 0);
  XSpiPs_PolledTransfer(SPIptr, SendBuffer, tempReceiveBuffer, j);
  XGpio_DiscreteWrite(SSptr, 1, 1);

  /* The top 4 elements in tempReceiveBuffer are always zeros, thus, I remove them */
  for(i = 4; i < j; i++){
    ReceiveBuffer[i - 4] = tempReceiveBuffer[i];
  }

  return ReceiveBuffer;
}
