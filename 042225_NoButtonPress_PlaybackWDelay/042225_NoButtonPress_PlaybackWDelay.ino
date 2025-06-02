#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// Feather RP2040 Setup
#define VS1053_RESET  -1        // VS1053 reset pin (not used!)

#if defined(ARDUINO_ADAFRUIT_FEATHER_RP2040)
  #define VS1053_CS     8       // VS1053 chip select pin (output)
  #define VS1053_DCS    10      // VS1053 Data/command select pin (output)
  #define CARDCS        7       // Card chip select pin
  #define VS1053_DREQ   9       // VS1053 Data request, ideally an Interrupt pin
#endif

int trackNum = 1;               // Initialize track number for playback

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ, CARDCS);

// Neopixel setup
#define PIN 16      // Pin for NeoPixel data
#define NUMPIXELS 1 // Number of NeoPixels in the strip (adjust as needed)

Adafruit_NeoPixel pixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool isPlaying = false;

void setup() {
  Serial.begin(115200);
  delay(1);

  pixel.begin(); // Initialize the NeoPixel library

  // Music Player test
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }

  Serial.println(F("VS1053 found"));

  // Check for SD Card
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println("SD OK!");

  // List files
  printDirectory(SD.open("/"), 0);

  // Set volume for left, right channels. lower numbers = louder
  musicPlayer.setVolume(30,30);

  //Set up interrupt to signal when a file's played through
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT); //DREQ

}

void loop() {
 //detect if playing
 if (musicPlayer.stopped()) {
  pixel.clear();
  pixel.show();
  delay(3000);
  pixel.setPixelColor(0, pixel.Color(20, 5, 50));
  pixel.show();
  playBack();
 } 
}

/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {

     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

/// Playback
void playBack() {
  Serial.println(trackNum);
    // Play a file in the background, REQUIRES interrupts!

  String trackFile = "/track00" + String(trackNum) + ".mp3";
  Serial.println(("Playing " + trackFile));
  musicPlayer.startPlayingFile(trackFile.c_str());
}