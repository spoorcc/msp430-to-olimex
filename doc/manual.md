# Info

* [Datasheet](http://www.ti.com/lit/ds/symlink/msp430g2553.pdf)
* [Famiy user guide](http://www.ti.com/lit/ug/slau144j/slau144j.pdf)

## Dependencies

* mspgcc
* mspdebug
* Qt5
* Qt5SerialPort

## Usage

### Creating MSP elf

    cd msp_bin
    make

now an Elf file is created which can be transferred to the device

Open up the debugger:

    mspdebug rf2500

Optionally erase the device, program it and run the program.

    (mspdebug) erase
    (mspdebug) prog main.elf
    (mspdebug) run

### Building SerialSender

Send serial data from Qt to launchpad
Needs Qt5!!

### Simple debugging with gdb on msp430
First compile your file to an Elf file be sure to add -g flag to CFLAGS to let gdb see all symbls

    make

Then connect the device in mspdebug

    mspdebug rf2500

and erase the device in mspdebug

    (mspdebug) erase

Then let mspdebug accept commands sent by gdb

    (mspdebug) gdb

Start up gdb in a different terminal window and load the program to gdb (assuming main.elf is your compiled program)

    msp430-gdb "target remote localhost:2000" main.elf

When the above command did not work select target with

    (gdb) target remote localhost:2000

Then command mspdebug to load the Elf file  from gdb by sending load command

    (gdb) load main.elf

Set a breakpoint at the begin
   
    (gdb) br main
    (gdb) br main.c:32  //Breakpoint at line 32

Let the program continue (3 equivalent options)

    (gdb) continue
    (gdb) <press enter> 
    (gdb) c

When breakpoint is reached you can see values

    (gdb) info var          //print the defined global variables
    (gdb) info locals       //print the defined local variables
    (gdb) print teller      // prints value of teller
    (gdb) display teller    // displays value after every breakpoint

Delete a breakpoint

    (gdb) delete 1   // delete breakpoint 1

Let the program continue

    (gdb) continue

Gdb reference:
http://www.cs.berkeley.edu/~mavam/teaching/cs161-sp11/gdb-refcard.pdf
