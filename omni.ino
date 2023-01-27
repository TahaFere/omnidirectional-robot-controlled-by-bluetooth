#include <SoftwareSerial.h>
//#include <Servo.h>
#include "NewPing.h"
#define TRIGGER_PIN 7
#define ECHO_PIN 8
#define MAX_DISTANCE 200

SoftwareSerial mySerial(2, 4); // RX, TX
int veri;
int L1=11;
int L2=10;
int R1=3;
int R2=5;
int G1=9;
int G2=6;
long sure,uzaklik;
int buzzer=12;
void motor(int sol,int sag,int arka){
  if(sol>0){
    digitalWrite(L1,0);
    analogWrite(L2,sol);
  }
  else{
    digitalWrite(L2,0);
    analogWrite(L1,abs(sol));
      
  }
    if(sag>0){
    digitalWrite(R1,0);
    analogWrite(R2,sag);
  }
  else{
    digitalWrite(R2,0);
    analogWrite(R1,abs(sag));
      
  }
    if(arka>0){
    digitalWrite(G1,0);
    analogWrite(G2,arka);
  }
  else{
    digitalWrite(G2,0);
    analogWrite(G1,abs(arka));     
  }
  }
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//float duration, distance;
void setup() {
pinMode(ECHO_PIN,INPUT);
pinMode(TRIGGER_PIN,OUTPUT);
pinMode(L1,OUTPUT);
pinMode(L2,OUTPUT);
pinMode(R1,OUTPUT);
pinMode(R2,OUTPUT);
pinMode(G1,OUTPUT);
pinMode(G2,OUTPUT);
pinMode(buzzer,OUTPUT);
delay(2000);
Serial.begin(9600);
mySerial.begin(9600);
}
void engel_kont(){
  int distance = sonar.ping_cm();
  if(distance<3) distance=200;
  Serial.println(distance);
  
  if(distance<30) {motor(0,0,0); digitalWrite(buzzer,1);motor(50,-50,50);delay(200); motor(0,0,0); }
  else{
    digitalWrite(buzzer,0);
    
    }
  }
void ileri(){ motor(95,100,0);   }
void geri() { motor(-110,-100,0);}
void sag()  { motor(64,-80,-185);}
void sol()  { motor(-64,80,185); }
void dur()  { motor(0,0,0);      }
void loop() {
engel_kont();
if (mySerial.available()){

char gelen=mySerial.read();
//Serial.print(distance);

//delay(20);
if(gelen=='S'){motor(0,0,0);}
if(gelen=='F'){ileri();}
if(gelen=='B'){geri();}
if(gelen=='L'){sol();}
if(gelen=='R'){sag();}
if(gelen=='I'||gelen=='J'){motor(50,-50,50);}
if(gelen=='H'||gelen=='G'){motor(-50,50,-50);}
if(gelen=='v'){digitalWrite(buzzer,0);}
if(gelen=='V'){digitalWrite(buzzer,1);}
}
}
