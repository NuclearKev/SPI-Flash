# SPI-Flash on ZYBO

## Overview
This project will contain 2 major parts; a ZYBO project and a C# project. 
The ZYBO project will use the Digilent ZYBO and a PMOD with a SPI Flash 
device on it. It will contain a custom made library that will allow you to 
do different tasks with the flash device. Also, it will contain code to enable
you to communicate to a PC through Ethernet. The C# application will allow you
to communicate with the ZYBO. It will enable you to control what functions
the board: read from the flash, write to the flash, etc.

## PMOD SF
The PMOD SF is the first revision of Digilent's Serial Flash PMOD series. It
contains a Micron M25P16 16Mbit Serial Flash device. This device uses the SPI
protocol for communication.