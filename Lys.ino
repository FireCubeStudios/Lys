#include <FastLED.h>
#include <DmxSimple.h>

const int universeSize = 16;
uint8_t state = 0;

#define NUM_LEDS 300
#define DATA_PIN 12
CRGB leds[NUM_LEDS];

DEFINE_GRADIENT_PALETTE(greenorange_mode0){
  0,0,0,0,
  112,0,0,0,
  135,170,0,71,
  147,67,2,241,
  156,150,0,210,
  170,255,0,106,
  255,0,0,0
};

DEFINE_GRADIENT_PALETTE(greenorange_mode1){
  0,0,0,0,
  51,170,0,71,
  204,150,0,255,
  255,0,0,0
};

DEFINE_GRADIENT_PALETTE(greenblack_mode2){
  0,0,0,0,
  165,0,0,0,
  207,70,0,152,
  230,150,0,255,
  255,0,0,0
};

DEFINE_GRADIENT_PALETTE(greenblue_mode3){
  0,   0, 255, 0,   // Green
  51,  0, 255, 31,  // Lighter Green
  111,  0, 255, 71,  // Lighter Green
  204, 0, 0, 250,   // Blue
  255, 0, 0, 0      // Black
};

CRGBPalette16 myPalette0 = greenorange_mode0;
CRGBPalette16 myPalette1 = greenorange_mode1;
CRGBPalette16 myPalette2 = greenblack_mode2;
CRGBPalette16 myPalette3 = greenblue_mode3;

void setup() {
  DmxSimple.usePin(3);
  DmxSimple.maxChannel(500);
  randomSeed(analogRead(0));

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  FastLED.clear();

}

void loop() {
// put your main code here, to run repeatedly:

updateDMX();
updateLED();
  
}

void updateDMX(){
    switch (state) {

    case 0:
      lysMode0();
      break;

    case 1:
      lysMode1();
      break;

    case 2:
      lysMode2();
      break;
  
    case 3:
      lysMode3();
      break;

    case 4:
      lysMode4();
      break;

    case 5:
      lysMode5();
      break;
  }
}

void updateLED(){
    switch (state) {

    case 0:
      LEDMode0();
      break;

    case 1:
      LEDMode1();
      break;

    case 2:
      LEDMode2();
      break;
  
    case 3:
      LEDMode3();
      break;
      
    case 4:
      LEDMode4();
      break;

    case 5:
      LEDMode5();
      break;
  }
}

int lysMode0_state = 0;
int lysMode0_count_i = 0;
int lysMode0_count_r = 0;
unsigned long lastMillis0 = 0;
unsigned long lastMillis1 = 0;

void lysMode0() {
  switch (lysMode0_state) {
    case 0:
      resetDMXLights();
      lysMode0_state = 1;
      lysMode0_count_r = 50;
      break;

    case 1:
      if (millis() - lastMillis0 >= 10) {
        if (lysMode0_count_r < 255) {
          DMXWrite(lysMode0_count_r, 60, 0);
          lysMode0_count_r++;
        } else {
          lysMode0_count_i++;
          lysMode0_count_r = 50;
          if (lysMode0_count_i > 4)
            state = random(6);
        }
        lastMillis0 = millis();
      }
      break;
  }
}

int lysMode1_state = 0;
int lysMode1_count_i = 0;
int lysMode1_count_r = 0;
int lysMode1_count_b = 0;

unsigned long lastMillis7 = 0;  // Variable to store the last millis() value
int counter1 = 0;
int brightness1 = 20;

unsigned long lastMillis8 = 0;  // Variable to store the last millis() value
int counter2 = 0;
int brightness2 = 150;

void lysMode1() {
  switch (lysMode1_state) {
    case 0:
      resetDMXLights();
      lysMode1_state = 1;
      break;

    case 1:
      // Check if 200 milliseconds have passed
      if (millis() - lastMillis7 >= 200) {
        if (brightness1 < 50) {
          DMXWrite(30, brightness1, 0);
          brightness1++;
          counter1++;
        } else {
          lysMode1_state = 2;
          lastMillis7 = millis();  // Update the lastMillis7 value
        }
      }
      break;

    case 2:
      // Check if 7 milliseconds have passed
      if (millis() - lastMillis7 >= 7) {
        if (brightness2 > 29) {
          DMXWrite(60, brightness2, 0);
          brightness2--;
        } else {
          lysMode1_count_i++;
          if (lysMode1_count_i > 7) {
            state = random(6);
            lysMode1_state = 0;  // Reset state for the next time
          } else {
            lysMode1_state = 1;  // Go back to state 1
          }
        }
        lastMillis7 = millis();  // Update the lastMillis7 value
      }
      break;
  }
}

unsigned long lastMillis3 = 0;  // Variable to store the last millis() value
int lysMode2_state = 0;
int lysMode2_count_i = 0;
int maxRepeats2 = 5;  // Adjust this value based on how many times you want it to repeat

void lysMode2() {

static float i2 = 0;
  switch (lysMode2_state) {
    case 0:
      resetDMXLights();
      lysMode2_state = 1;
      break;

    case 1:
      float s2 = sin(i2);
      int r2 = int(s2 * 100);
      int g2 = int(s2 * 240);
      int b2 = int(s2 * 4);

      // Check if the specified time has passed
      if (millis() - lastMillis3 >= (1 - s2) * 5 + 3) {
        if (i2 < 3.14159) {
          DMXWrite(r2, g2, b2);
          i2 += 3.14159 / 510;
        } else {
          lysMode2_count_i++;
          if (lysMode2_count_i >= maxRepeats2) {
            state = random(6);
            lysMode2_state = 0;  // Reset state for next time
          } else {
            i2 = 0;  // Reset i2 for the next iteration
          }
        }
        lastMillis3 = millis();  // Update the lastMillis2 value
      }
      break;
  }
}

unsigned long lastMillis4 = 0;  // Variable to store the last millis() value
int lysMode3_state = 0;
int lysMode3_count_i = 0;
int maxRepeats3 = 5;  // Adjust this value based on how many times you want it to repeat

void lysMode3() {
  static float i2 = 0;
  switch (lysMode3_state) {
    case 0:
      resetDMXLights();
      lysMode3_state = 1;
      break;

    case 1:
      float s2 = sin(i2);
      int r2 = int(s2 * 4);
      int g2 = int(s2 * 240);
      int b2 = int(s2 * 30);

      // Check if the specified time has passed
      if (millis() - lastMillis4 >= (1 - s2) * 5 + 3) {
        if (i2 < 3.14159) {
          DMXWrite(r2, g2, b2);
          i2 += 3.14159 / 510;
        } else {
          lysMode3_count_i++;
          if (lysMode3_count_i >= maxRepeats3) {
            state = random(6);
            lysMode3_state = 0;  // Reset state for next time
          } else {
            i2 = 0;  // Reset i2 for the next iteration
          }
        }
        lastMillis4 = millis();  // Update the lastMillis value
      }
      break;
  }
}


int lysMode4_state = 0;
int lysMode4_count_i = 0;
int brightness4 = 20;
int gbrightness4 = brightness4 - 15;
unsigned long previousMillis4 = 0;
const long interval4 = 8;  // Adjust the interval as needed (milliseconds)
const int maxRepeats = 20;  // Adjust the maximum number of repeats

void lysMode4() {
  unsigned long currentMillis4 = millis();

  switch (lysMode4_state) {
    case 0:
      resetDMXLights();
      lysMode4_state = 1;
      break;

    case 1:
      if (currentMillis4 - previousMillis4 >= interval4) {
        if (brightness4 < 50) {
          DMXWrite(brightness4, gbrightness4, 0);
          brightness4++;
        } else {
          DMXWrite(20, 5, 0);  // Flash red light
          brightness4 = 20;
          lysMode4_count_i++;

          if (lysMode4_count_i > maxRepeats) {
            state = random(6);
            lysMode4_state = 0;  // Reset state for next time
            lysMode4_count_i = 0;  // Reset the repeat counter
          }
        }
        previousMillis4 = currentMillis4;
      }
      break;
  }
}

int lysMode5_state = 0;
int lysMode5_count_i = 0;
int brightness5 = 20;
int gbrightness5 = brightness5 - 15;
unsigned long previousMillis5 = 0;
const long interval5 = 8;  // Adjust the interval as needed (milliseconds)
const int maxRepeats5 = 20;  // Adjust the maximum number of repeats

void lysMode5() {
  unsigned long currentMillis5 = millis();

  switch (lysMode5_state) {
    case 0:
      resetDMXLights();
      lysMode5_state = 1;
      break;

    case 1:
      if (currentMillis5 - previousMillis5 >= interval5) {
        if (brightness5 < 50) {
          DMXWrite(0, brightness5, gbrightness5);
          brightness5++;
        } else {
          DMXWrite(0, 20, 5); 
          brightness5 = 20;
          lysMode5_count_i++;

          if (lysMode5_count_i > maxRepeats5) {
            state = random(6);
            lysMode5_state = 0;  // Reset state for next time
            lysMode5_count_i = 0;  // Reset the repeat counter
          }
        }
        previousMillis5 = currentMillis5;
      }
      break;
  }
}


void LEDMode0(){
  uint16_t sinBeat = beatsin16(2,0,NUM_LEDS - 1,0,0);
  uint16_t sinBeat1 = beatsin16(6,0,NUM_LEDS - 1,0,70);
  uint16_t sinBeat2 = beatsin16(9,10,NUM_LEDS - 1,0,0);
  uint16_t sinBeat3 = beatsin16(3,15,NUM_LEDS - 1,0,70);
  fill_palette(leds,NUM_LEDS,(sinBeat+sinBeat1)/2,1,myPalette0,255,LINEARBLEND);

  
  EVERY_N_MILLISECONDS(1){
    for(int i=0;i<4;i++){
      blur1d(leds, NUM_LEDS, 50);
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, 10);

  FastLED.show();
}

void LEDMode1(){
  uint16_t sinBeat = beatsin16(7,0,NUM_LEDS - 1,0,0);
  uint16_t sinBeat1 = beatsin16(3,0,NUM_LEDS - 1,0,0);
  uint8_t fade = beatsin8(86,0,NUM_LEDS - 1,0,0);
  fill_palette(leds,NUM_LEDS,(sinBeat+sinBeat1)/2,1,myPalette1,fade,LINEARBLEND);
  EVERY_N_MILLISECONDS(1){
    for(int i=0;i<4;i++){
      blur1d(leds, NUM_LEDS, 50);
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, 10);

  FastLED.show();
}

void LEDMode2(){
  uint16_t sinBeat = beatsin16(5,0,NUM_LEDS - 1,0,0);
  uint16_t sinBeat1 = beatsin16(6,0,NUM_LEDS - 1,0,0);
  fill_palette(leds,NUM_LEDS,(sinBeat+sinBeat1)/2,1,myPalette2,255,LINEARBLEND);
  fadeToBlackBy(leds, NUM_LEDS, 10);
  EVERY_N_MILLISECONDS(1){
    for(int i=0;i<4;i++){
      blur1d(leds, NUM_LEDS, 50);
    }
  }

  FastLED.show();
}

void LEDMode3(){
  uint16_t sinBeat = beatsin16(5,0,NUM_LEDS - 1,0,0);
  uint16_t sinBeat1 = beatsin16(6,0,NUM_LEDS - 1,0,0);
  fill_palette(leds,NUM_LEDS,(sinBeat+sinBeat1)/2,1,myPalette3,255,LINEARBLEND);
  fadeToBlackBy(leds, NUM_LEDS, 10);
  EVERY_N_MILLISECONDS(1){
    for(int i=0;i<4;i++){
      blur1d(leds, NUM_LEDS, 50);
    }
  }

  FastLED.show();
}

void LEDMode4(){
  uint16_t pos0 = map(beat8(25,0),0,255,0,NUM_LEDS-1);
  uint16_t pos1 = map(beat8(21,400),0,255,0,NUM_LEDS-1);
  uint16_t pos2 = map(beat8(18,800),0,255,0,NUM_LEDS-1);
  leds[pos0] = CRGB(210,0,0);
  leds[pos1] = CRGB(230,0,0);
  leds[pos2] = CRGB(255,0,0);

  EVERY_N_MILLISECONDS(1){
    for(int i=0;i<4;i++){
      blur1d(leds, NUM_LEDS, 50);
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, 10);

  FastLED.show();
}

void LEDMode5(){
  uint16_t pos0 = map(beat8(25,0),0,255,0,NUM_LEDS-1);
  uint16_t pos1 = map(beat8(21,400),0,255,0,NUM_LEDS-1);
  uint16_t pos2 = map(beat8(18,800),0,255,0,NUM_LEDS-1);
  leds[pos0] = CRGB(0, 0, 210);
  leds[pos1] = CRGB(0, 50, 230);
  leds[pos2] = CRGB(0, 90, 255);

  EVERY_N_MILLISECONDS(1){
    for(int i=0;i<4;i++){
      blur1d(leds, NUM_LEDS, 50);
    }
  }
  fadeToBlackBy(leds, NUM_LEDS, 10);

  FastLED.show();
}

void resetDMXLights(){
  DmxSimple.write(100, 0);
  DmxSimple.write(101, 0);
  DmxSimple.write(102, 0);
}

void DMXWrite(int r, int g, int b){
  DmxSimple.write(100, r);
  DmxSimple.write(101, g);
  DmxSimple.write(102, b);
}
