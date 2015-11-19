# SPI-Flash on ZYBO

## Overview
This project will contain 2 major parts; a ZYBO project and a C# project. 
The ZYBO project will use the Digilent ZYBO and a PMOD with a SPI Flash 
device on it. It will contain a custom made library that will allow you to 
do different tasks with the flash device. Also, it will contain code to enable
you to communicate to a PC through Ethernet. That being said, the C# application
will control what is done on the ZYBO. The functions that will be used include
the following:
* Read Status Register
* Read Data 
* Erase Sector/All
* Write Page

To demonstrate the functionality of this project, I will be sending some data
using Ethernet to the ZYBO and have it be stored on the flash. C# will generate
said data (either a sine wave or some random data). Once the data is written, I
will send the read command to the ZYBO and have it return the written data
back to C#. 

## PMOD SF
The PMOD SF is the first revision of Digilent's Serial Flash PMOD series. It
contains a Numonyx M25P16 16Mbit Serial Flash device. This device can store up
to ~16Mbits (2MBs) of data. It uses the SPI protocol and can operate at a max
SCLK rate of 75MHz. The master of this device can be configured with either
CPOL=0 & CPHA=0 or CPOL=1 & CPHA=1. The data is send in on the raising edge of
the clock and data is outputted on the falling edge. The information sent to the
device should follow this format: {command, addressByte1, addressByte2, AddressByte3,
data0, data1, ... , dataN}. Where "command" is the command to be ran, addressByte1,
2 and 3 are the start address in which you will be writing, reading, or erasing
(explained more later), and "data" is the data to be written. Note that some
commands don't use the addresses or data.

This device has 32 sectors, each containing 256 pages and each page being 256
bytes wide. Each sector contains 65,536 addresses for a total of 2,097,152
addresses; each address holds 1 byte of data.

Due to how the PMOD is set up, there is no HOLD# or W# pins to worry about.
However, on the actual chip W# is used for write protection and HOLD# is used
for holding a specific state.

### Commands
This section will have in-depth information on the different commands that will
be used. Keep in mind that there are other commands available but I don't use
them in this project.

#### Write Enable
This command's code is 0x06. It does not need any addresses, dummies, or data
bytes. This command sets the write enable latch (WEL) bit in the status register
The WEL bit must be set before execution of every PROGRAM, ERASE, and WRITE
command.

#### Read Status Register

#### Read Data Bytes

#### Page Program

#### Sector Erase

#### Bulk Erase
