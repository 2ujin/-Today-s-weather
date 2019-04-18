#include "DHT.h" //DHT-22센서를 사용하기위하여 라이브러리를 불러옵니다.
#include <Adafruit_NeoPixel.h>
#define PIN            6
//#define NUMPIXELS      16

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, PIN, NEO_GRB + NEO_KHZ800);
DHT dht(8, DHT22); /*8번 PIN에서 데이터가 들어오고,센서는 DHT22 센서를 사용한다고 정의합니다.*/

void setup() {
  Serial.begin(9600); //PC모니터를 이용하기 위하여, 시리얼통신을 정의해줍니다.
  dht.begin(); //DHT22센서의 사용시작을 정의해줍니다.
  
//#if defined (__AVR_ATtiny85__)
//  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//#endif
//  // End of trinket special code
//  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 
  
  delay(2000);   //측정하는 시간사이에 2초간의 딜레이를 줘야 합니다.
  
  float h = dht.readHumidity();  //습도값을 읽어온후 h변수값에 값을 저장합니다. 
  float t = dht.readTemperature(); //온도값을 읽어온후 t변수값에 값을 저장합니다. 
  float hic = dht.computeHeatIndex(t, h, false); //DHT22는 열지수(체감온도)를 나타내줄수있는 함수가 포함되어있습니다.

  Serial.print("습도 : ");
  Serial.print(h); //습도가 출력 됩니다.
  Serial.print(" %\t");
  Serial.print("온도 : ");
  Serial.print(t); //온도가 출력됩니다.
  Serial.print(" *C ");
  Serial.print("체감온도 : ");
  Serial.print(hic); //열지수(체감온도)가 출력됩니다.
  Serial.println(" *C ");

  if(t>20){
  colorWipe(strip.Color(255, 0, 0), 50); //빨간색 출력
  }

}


void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<2;i++){      
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
 
