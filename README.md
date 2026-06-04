# discourse-objects
Arduino code for DisCourse object playback.

The code executes the following:
- Initialize VS1053 chip for playback
- A 5 second delay for setup
- Checks for an SD card
- Lights the neopixel
- Plays the track on loop with a 5 second delay between the end of the track and when it restarts.

# Hardware Notes
If you're using an Adafruit Feather (RP2040), the connection to your machine may not register the first time you plug in the USB. To fix, I used the instructions from the Adafruit blog for [configuring the board for CircuitPython](https://learn.adafruit.com/adafruit-feather-rp2040-pico/circuitpython).

> To enter the bootloader, hold down the BOOT/BOOTSEL button (highlighted in red above), and while continuing to hold it (don't let go!), press and release the reset button (highlighted in red or blue above). Continue to hold the BOOT/BOOTSEL button until the RPI-RP2 drive appears!
> 
> If the drive does not appear, release all the buttons, and then repeat the process above.
> 
> You can also start with your board unplugged from USB, press and hold the BOOTSEL button (highlighted in red above), continue to hold it while plugging it into USB, and wait for the drive to appear before releasing the button.
> 
> A lot of people end up using charge-only USB cables and it is very frustrating! Make sure you have a USB cable you know is good for data sync.
>
> You will see a new disk drive appear called RPI-RP2.
> Drag the adafruit_circuitpython_etc.uf2 file to RPI-RP2.

After this, the Arduino IDE will show the Port that the board is plugged into (unless you're accidentally using a charging cable). Select it and the right board, then upload the arduino code.

I don't know why this works but it seems to shake something loose and get my computer to see the board without actually requiring me to code in CircuitPython.

# micro SD Config Notes
To work out of the box, the micro SD card should have a single mp3 file named 'track001.mp3'
