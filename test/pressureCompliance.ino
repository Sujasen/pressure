
#include <Adafruit_SSD1306.h>
#include <ADAFRUIT_GFX.h>

#define MOSI        51   //SPI MOSI; D1 on LCD screen
#define CLK         52   //SPI CLK; D0 on LCD Screen
#define OLED_DC    33 //OLED_DC
#define OLED_CS    31 //OLED Chip Select 
#define OLED_RESET 35 //OLED Reset


#define TIME_LIMIT 5
#define TIME_HOLD  5
#define MIN_PRESSURE 0


Adafruit_SSD1306 display(MOSI, CLK, OLED_DC, OLED_RESET, OLED_CS);
int Sensor[6];
int clk = TIME_LIMIT;
int radii[6];

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.display();
  Serial.begin(9600);
}

void adjustSeat(){
  Serial.println("adjustSeat Begin");
  bool complete = false;
  int timer[6] = {0};
  int i;
  while(!complete){
    
    readSensor();
    draw_all_circs(radii);
    complete = true;
    for(i=0; i<6;i++){
       if(Sensor[i] <= 0){
          timer[i]++;
       }
       if(timer[i] <= TIME_HOLD)
          complete = false;
     }
     delay(50);
   }
   Serial.println("adjustSeat Done");
}

void draw_all_circs(int radii[]) {
    display.clearDisplay();
    delay(100);
    display.drawCircle(10, 13, radii[0], WHITE);
    display.drawCircle(50, 13, radii[1], WHITE);
    display.drawCircle(90, 13, radii[2], WHITE);
    display.drawCircle(10, 25, radii[3], WHITE);
    display.drawCircle(50, 25, radii[4], WHITE);
    display.drawCircle(90, 25, radii[5], WHITE);
    delay(100);
    display.display();
}

void readSensor(){
  Sensor[0] = analogRead(A0);
  Sensor[1] = analogRead(A1);
  Sensor[2] = analogRead(A2);
  Sensor[3] = analogRead(A3);
  Sensor[4] = analogRead(A4);
  Sensor[5] = analogRead(A5);


  radii[0] = convertReading(Sensor[0]);
  radii[1] = convertReading(Sensor[1]);
  radii[2] = convertReading(Sensor[2]);
  radii[3] = convertReading(Sensor[3]);
  radii[4] = convertReading(Sensor[4]);
  radii[5] = convertReading(Sensor[5]);
 
  
  Serial.print(" Clock: ");   Serial.print(clk); 
  Serial.print(" Sensor5: "); Serial.print(Sensor[5]);
  Serial.print(" Sensor4: "); Serial.print(Sensor[4]); Serial.println();
  
  }

  int convertReading(int i){
    int value;
    value = i/100;
    Serial.print(value);
    if (value>5)
      value = 5;
    return value;    
  }


void loop() {
  display.clearDisplay();
  display.print(clk);
  display.display();
  display.setCursor(0,0);
  delay(500);
  clk--;
  if(clk <= 0){
     adjustSeat();
     clk = TIME_LIMIT;
  }
   
}
