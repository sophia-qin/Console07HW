// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            28

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      5

const byte Rset_pin=49; // This is the common AMIB push button pin
const int AIM[]={128,128,128}; // 50% power white light
const int MISS[]={128,0,0}; // 50% power red light
const int HIT[]={0,0,128}; // 50% power blue light

int color_state=0;
int project_state=0;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 2000; // delay for half a second

void setup() {

pixels.begin(); // This initializes the NeoPixel library.
Serial.begin(9600);
pinMode(Rset_pin, INPUT_PULLUP);
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
if(digitalRead(Rset_pin)==LOW)
{
  if(color_state==0)
  {color_state=1;}
  else if(color_state==1)
  {color_state=2;}
  else if(color_state==2)
  {color_state=3;}
  else if(color_state==3)
  {color_state=0;}
  project_state=0;
  delay(1000);
  Serial.println("state Change");
  Serial.println(color_state);
}

if(color_state==1 && project_state==0)
 { for(int i=0;i<NUMPIXELS;i++)
  {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,255,255));
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    project_state=1; 

  }
 }
  if(color_state==2 && project_state==0)
 { for(int i=0;i<NUMPIXELS;i++)
  {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    project_state=1; 

  }
 }
 if(color_state==3 && project_state==0)
 { for(int i=0;i<NUMPIXELS;i++)
  {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,255));
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    project_state=1; 

  }
 }
  if(color_state==0 && project_state==0)
 { for(int i=0;i<NUMPIXELS;i++)
  {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).
    project_state=1; 

  }
 }
}
