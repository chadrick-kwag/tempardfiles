#include <Adafruit_NeoPixel.h>

#include <Event.h>
#include <Timer.h>

#include <SoftwareSerial.h>



SoftwareSerial bt(10,11); // rx,tx

#define NLED 50

#define BUTTON1 2
#define BUTTON2 3

#define PIN 6

#define IMGARR_1_SIZE 12
#define IMGARR_2_SIZE 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NLED, PIN, NEO_GRB + NEO_KHZ800);

int image1_array[IMGARR_1_SIZE][4]={ {47,150,150,150} , {46,150,150,150} , {45,150,150,150} , {44,150,150,150} , {43,150,150,150}, {42,150,150,150} , {35,150,150,150} , {34,150,150,150} , {33,150,150,150} , {32,150,150,150} , {25,150,150,150} , {24,150,150,150} };

int image2_array[IMGARR_2_SIZE][4]{ {1,0,120,120} , {2,0,120,120} , {8,0,120,120} , {9,0,120,120} , {10,0,120,120} , {11,0,120,120} };

int fade_count=0;
int fade_ended=1;
int event1_id=0;


Timer t;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("serial start");
  bt.begin(9600);

  strip.begin();


  pinMode(BUTTON1,INPUT);
  pinMode(BUTTON2,INPUT);
  attachInterrupt(0,pin_ISR,FALLING);
  attachInterrupt(1,pin_ISR2,FALLING);

  

}
int first=0;

void loop() {
  // put your main code here, to run repeatedly:

  t.update();

}


/*
 * 
 * 
 */

void pin_ISR(){
  Serial.println("btn1");
  bt.write('1');
  if(event1_id!=0){
    Serial.println("already running");
    t.stop(event1_id);
    fade_count=0;
    
    
  }

  fade_ended=0;
  
  setimg3(image1_array,100);

  event1_id=t.every(150,fadecallback);
  
  
}


void pin_ISR2(){
  Serial.println("btn2");
  bt.write('2');

}


void setimg3(int fuck[IMGARR_1_SIZE][4], int factor){
  int i;
  for(i=0;i<IMGARR_1_SIZE;i++){
    strip.setPixelColor(fuck[i][0],fuck[i][1]*factor/100,fuck[i][2]*factor/100,fuck[i][3]*factor/100);
  }
  strip.show();
}


void setimg2(int fuck[IMGARR_2_SIZE][4], int factor){
  int i;
  for(i=0;i<IMGARR_1_SIZE;i++){
    strip.setPixelColor(fuck[i][0],fuck[i][1]*factor/100,fuck[i][2]*factor/100,fuck[i][3]*factor/100);
  }
  strip.show();
}



void fadecallback(){

  if(fade_ended){
    return;
  }


  if(fade_count<5){
    setimg3(image1_array,(4-fade_count++)*20);
    
  }
  if(fade_count>=5){
    fade_count=0;
    
    t.stop(event1_id);
    event1_id=0;
    fade_ended=1;
  }

  
}




