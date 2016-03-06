//**************************************************************//
//  Name    : 7 Segment Count up                            
//  Author  : Rob Moncur
//  Date    : 5 March 2016
//  Modified: 5 March 2016                                
//  Version : 1.0                                             
//  Notes   : Code to drive 7 segment display for Moncur        //
//          : control panel. Counts up when swithc is engaged.                      
//****************************************************************

#include <Time.h>
#include <TimeLib.h>

int latchPin = 11; //Pin connected to ST_CP of 74HC595
int clockPin = 10; //Pin connected to SH_CP of 74HC595
int dataPin = 12;  //Pin connected to DS of 74HC595
int switchPin = 8;
int d1 = 2;        //Pin connected to digit 1
int d2 = 3;        //Pin connected to digit 2
int d3 = 4;        //Pin connected to digit 3
int d4 = 5;        //Pin connected to digit 4

unsigned long time = 0;

String digit1 = "0";
String digit2 = "0";
String digit3 = "0";
String digit4 = "0";

void setup() {
  //set pins to output so you can control the shift register
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitOn(d1);
  digitOn(d2);
  digitOn(d3);
  digitOn(d4);

  //reading from pin 13. It is the switch
  pinMode(switchPin, INPUT_PULLUP);

  //pinMode(8,OUTPUT);
  //pinMode(9,OUTPUT);
  //digitalWrite(8,LOW);
  //digitalWrite(9,HIGH);

  Serial.begin(9600); 

}

void loop() {

  //http://playground.arduino.cc/code/time
  int m = minute(now());
  int s = second(now());
  if( s > 9 ){
    digit3 = String(s)[0];
    digit4 = String(s)[1];
  } else {
    digit3 = "0";
    digit4 = String(s);
  }

  if( m > 9 ){
    digit1 = String(m)[0];
    digit2 = String(m)[1];
  } else {
    digit1 = "0";
    digit2 = String(m);
  }

  int switchState = digitalRead(switchPin);
  if(switchState == HIGH){

    int mydelay = 3;

    //Turning each digit on and off so fast it looks like they are static
    digitOn(d1);
    digitOff(d2);
    digitOff(d3);
    digitOff(d4);
    displayNumber(digit1);
    delay(mydelay);
  
    digitOff(d1);
    digitOn(d2);
    digitOff(d3);
    digitOff(d4);
    displayNumber(digit2);
    delay(mydelay);
  
    digitOff(d1);
    digitOff(d2);
    digitOn(d3);
    digitOff(d4);
    displayNumber(digit3);
    delay(mydelay);
  
    digitOff(d1);
    digitOff(d2);
    digitOff(d3);
    digitOn(d4);
    displayNumber(digit4);
    delay(mydelay);
    
  } else {
    digitOff(d1);
    digitOff(d2);
    digitOff(d3);
    digitOff(d4);
    setTime(0); 
  }
  

}

void digitOn(int d){
  pinMode(d, OUTPUT);
  digitalWrite(d,LOW);
}

void digitOff(int d){
  pinMode(d, INPUT);
}

void displayNumber(String digit){

  int code = 0;
  if     (digit == "0"){code = 126;}
  else if(digit == "1"){code = 12;}
  else if(digit == "2"){code = 182;}
  else if(digit == "3"){code = 158;}
  else if(digit == "4"){code = 204;}
  else if(digit == "5"){code = 218;}
  else if(digit == "6"){code = 250;}
  else if(digit == "7"){code = 14;}
  else if(digit == "8"){code = 254;}
  else if(digit == "9"){code = 222;}
  else if(digit == "l"){code = 112;}
  else if(digit == "a"){code = 238;}

   digitalWrite(latchPin, LOW);// take the latchPin low so the LEDs don't change while you're sending in bits:
   shiftOut(dataPin, clockPin, MSBFIRST, code); // shift out the bits: 
   digitalWrite(latchPin, HIGH); //take the latch pin high so the LEDs will light up:

}

