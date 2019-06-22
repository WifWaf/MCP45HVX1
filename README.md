# MCP45HVX1

![Version](https://img.shields.io/badge/Version-v1.0.0-green.svg)

***Please Note: currently there is no support for non-ST versions (more than one tap). However this will be added in the future, so feel free to watch this repository***

 Library for MCP45HVX1 digital potentiometers using the Arduino platform. Supports most devices.

### Features
---
* Wiper Read/Write commands
* Wiper incrimental/decremntal commands
* TCON control by function name
  * Shutdown / Startup
  * Disconect/Connect Terminal A or Terminal B
  * Disconect/Connect Wiper
* TCON Read/Write Register (Write uses typedef struct - see header) 

### Pending changes
---
* General Call Commands
* Support for dual tap versions

### Commands
---
See header file for list of function names.

### Usage
---
The library will be found in the IDE/IO library manager. Alternatively, simply clone this library to your working library folder and include "MCP45HVX1.h" in your main sketch.

If you are having difficulties, please raise an issue.

### A Bit About this IC
---
See extras for the official datasheet

### Authors
---
Myself, you can find my contact details below.

### License
---
This project is licensed under Apache 2.0 - see the LICENSE.md file for details

### Acknowledgments
----
 None

### Feedback
---
Feel free to improve on the project and propose appropriate changes and even coding advice as I'm still new to this world.

Please contact me at jdwifwaf@gmail.com
