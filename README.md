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
* Read Sector/Page
* Erase Sector/Page
* Write Page

To demonstrate the functionality of this project, I will be sending some data
using Ethernet to the ZYBO and have it be stored on the flash. C# will generate
said data (either a sine wave or some random data). Once the data is written, I
will send the read command to the ZYBO and have it return the written data
back to C#. 

## PMOD SF
The PMOD SF is the first revision of Digilent's Serial Flash PMOD series. It
contains a Numonyx M25P16 16Mbit Serial Flash device. This device uses the SPI
protocol for communication.
