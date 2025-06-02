# discourse-objects
Arduino code for DisCourse object playback.

The code executes the following:
- Initialize VS1053 chip for playback
- A 5 second delay for setup
- Checks for an SD card
- Lights the neopixel
- Plays the track on loop with a 5 second delay between the end of the track and when it restarts.
