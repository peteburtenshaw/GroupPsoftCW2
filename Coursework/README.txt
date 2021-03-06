Environment Sensor Recorder. For SOFT 253 Coursework.  
Group P
---Dev Notes---
                                     /~\
                                    |oo )      We're doomed!
                                    _\=/_
                    ___        #   /  _  \   #
                   /() \        \\//|/.\|\\//
                 _|_____|_       \/  \_/  \/
                | | === | |         |\ /|
                |_|  O  |_|         \_ _/
                 ||  O  ||          | | |
                 ||__*__||          | | |
                |~ \___/ ~|         []|[]
                /=\ /=\ /=\         | | |
________________[_]_[_]_[_]________/_]_[_\_________________________

TO DO: 

Queue - 
    //class - methods and variables, .h and .cpp- ask peter if you need help
    //implement in main
    ?use with messages
    //look into delete n - when performed, isFull should become false
Commands-
    Add each method for each command
    Change input to readchar, printchar, repeat
	
ROSS -
	IF STATEMENTS
		make them again lol
			maybe make a method to use a bit like this:
			void compare(char[] user input,char[] string to compare){code in here}
			nesting them would be preferable, i.e. this one:
			if (equal to "read")
				if(equal to "all")
			
			
CRAIG -
	LOGGING
		after the computer does something, add a string to a mail queue with a message that you want to print
		that mail queue goes to thread 4 and prints it there
		all printing should be done via this thread so think about when logging is turned on/off
		i've got the serial interface class in place, use that perhaps, maybe make it a string (but strings don't work)


NOTES:
In order to accept text input, you need to change the putty setting under Terminal> Line discipline options->Local echo-> Force on

# Getting started with Blinky on mbed OS

This guide reviews the steps required to get Blinky working on an mbed OS platform.

Please install [mbed CLI](https://github.com/ARMmbed/mbed-cli#installing-mbed-cli).

## Import the example application

From the command-line, import the example:

```
mbed import mbed-os-example-blinky
cd mbed-os-example-blinky
```

### Now compile

Invoke `mbed compile`, and specify the name of your platform and your favorite toolchain (`GCC_ARM`, `ARM`, `IAR`). For example, for the ARM Compiler 5:

```
mbed compile -m K64F -t ARM
```

Your PC may take a few minutes to compile your code. At the end, you see the following result:

```
[snip]
+----------------------------+-------+-------+------+
| Module                     | .text | .data | .bss |
+----------------------------+-------+-------+------+
| Misc                       | 13939 |    24 | 1372 |
| core/hal                   | 16993 |    96 |  296 |
| core/rtos                  |  7384 |    92 | 4204 |
| features/FEATURE_IPV4      |    80 |     0 |  176 |
| frameworks/greentea-client |  1830 |    60 |   44 |
| frameworks/utest           |  2392 |   512 |  292 |
| Subtotals                  | 42618 |   784 | 6384 |
+----------------------------+-------+-------+------+
Allocated Heap: unknown
Allocated Stack: unknown
Total Static RAM memory (data + bss): 7168 bytes
Total RAM memory (data + bss + heap + stack): 7168 bytes
Total Flash memory (text + data + misc): 43402 bytes
Image: .\.build\K64F\ARM\mbed-os-example-blinky.bin
```

### Program your board

1. Connect your mbed device to the computer over USB.
1. Copy the binary file to the mbed device.
1. Press the reset button to start the program.

The LED on your platform turns on and off.

## Export the project to Keil MDK, and debug your application

From the command-line, run the following command:

```
mbed export -m K64F -i uvision
```

To debug the application:

1. Start uVision.
1. Import the uVision project generated earlier.
1. Compile your application, and generate an `.axf` file.
1. Make sure uVision is configured to debug over CMSIS-DAP (From the Project menu > Options for Target '...' > Debug tab > Use CMSIS-DAP Debugger).
1. Set breakpoints, and start a debug session.

![Image of uVision](img/uvision.png)

## Troubleshooting

1. Make sure `mbed-cli` is working correctly and its version is `>1.0.0`

 ```
 mbed --version
 ```

 If not, you can update it:

 ```
 pip install mbed-cli --upgrade
 ```

2. If using Keil MDK, make sure you have a license installed. [MDK-Lite](http://www.keil.com/arm/mdk.asp) has a 32 KB restriction on code size.

