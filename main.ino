
/* SoftwareSerial */
#include<SoftwareSerial.h>

/* 미세먼지 측정을 위한 설정 */
int data[100];
int check;
int count = 1 ;

/* 데이터 초기 값 설정 */
int sent = 1;

/**/
float PM1_0 = 0;
float PM2_5 = 0;
float PM10 = 0;

SoftwareSerial pms7003(4, 5);


void setup() {
  Serial.begin(115200);
  delay(10);

  pms7003.begin(9600);


}

void loop() {
  if (pms7003. available()) {
    data[count] = pms7003.read();
    count = count + 1 ;
  }

  if (count == 64) {
    pms7003.end();
    for (int i = 1; i < 33; i ++) {

      check = 0;

      PM1_0 = data[i + 10] * 256 + data[i + 11];
      PM2_5 = data[i + 12] * 256 + data[i + 13];
      PM10 = data[i + 14] * 256 + data[i + 15];

      for (int h = i; h < i + 30; h++) {
        check = check + data[h];
      }
      if (data[i] == 66 & data[i + 1] == 77 & (data[i + 30] * 16 * 16 + data[i + 31]) == check) {
        pms7003.begin(9600);

        Serial.println(String(sent) + " " + "DATA");
        Serial.println("------------------------------");
        Serial.println("| Dust density(ug/m3) : ");
        Serial.print("| PM1.0 : ");
        Serial.println(PM1_0);
        Serial.print("| PM2.5 : ");
        Serial.println(PM2_5);
        Serial.print("| PM10 : ");
        Serial.println(PM10);
        Serial.println("------------------------------");

        /***************************************************
           Sending Data to Thinkspeak Channel
         **************************************************/
        if (client.connect(TS_SERVER, 80))  {


          String postStr = "&device_id=" + device_id_str;
          postStr += "&pm1=" + String(PM1_0);
          postStr += "&pm25=";
          postStr += String(PM2_5);
          postStr += "&pm10=";
          postStr += String(PM10);
          postStr += "\r\n\r\n";

          Serial.println("parameters = " + postStr);

          client.print("POST /air/?requestby=arduino HTTP/1.1\n");
          client.print("Host: " + TS_SERVER_STR + "\n");
          client.print("Connection: close\n");
          client.print("Content-Type: application/x-www-form-urlencoded\n");
          client.print("Content-Length: ");
          client.print(postStr.length());
          client.print("\n\n");
          client.print(postStr);
        }
        sent++;
        client.stop();
        count = 1;

        //delay(3000);
        delay(1000 * 20);   // 1분에 한번 실행
      }

    }
  }
}
