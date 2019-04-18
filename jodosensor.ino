#include <Adafruit_NeoPixel.h>
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
int cds = A1;
int led = A0;

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  strip.begin();
  strip.show(); 
  
  int cdsValue = analogRead(cds);

  Serial.print("cds =  ");
  Serial.println(cdsValue);

  if(cdsValue > 200){
    colorWipe(strip.Color(0, 0, 0), 50);
  }
  else{
    colorWipe(strip.Color(255, 255, 255), 50);
  }
  delay(500);
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<16;i++){      
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

//네오픽셀 out - d6
//조도센서 out - a1
