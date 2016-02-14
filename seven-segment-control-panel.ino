//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 23 Mar 2010                                 
//  Version : 2.0                                             
//  Notes   : Code for using a 74HC595 Shift Register           //
//          : to count from 0 to 255                           
//****************************************************************

#include <Time.h>
#include <TimeLib.h>

int latchPin = 11; //Pin connected to ST_CP of 74HC595
int clockPin = 10; //Pin connected to SH_CP of 74HC595
int dataPin = 12;  //Pin connected to DS of 74HC595
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

  //displayNumber(2);
  //digitalWrite(latchPin, LOW);// take the latchPin low so the LEDs don't change while you're sending in bits:
  //shiftOut(dataPin, clockPin, MSBFIRST, 2); // shift out the bits: 
  //digitalWrite(latchPin, HIGH); //take the latch pin high so the LEDs will light up:
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

  int mydelay = 3;

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

  /*  
  for (int numberToDisplay = 0; numberToDisplay < 10; numberToDisplay++) {
    displayNumber(numberToDisplay);
    delay(1000);

    if( numberToDisplay % 2 == 0 ){
      pinMode(2, OUTPUT);
      digitalWrite(2,LOW);
    } else {
      pinMode(2, INPUT);      
    }
  }
  */

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
  if(digit == "0"){code = 126;}
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
/*
  switch(digit){
    case "0": code = 126; break;
    case "1": code = 12; break;
    case "2": code = 182; break;
    case "3": code = 158; break;
    case "4": code = 204; break;
    case "5": code = 218; break;
    case "6": code = 250; break;
    case "7": code = 14; break;
    case "8": code = 254; break;
    case "9": code = 222; break;
    case "L": code = 112; break;
    case "A": code = 238; break;
  }
*/
   digitalWrite(latchPin, LOW);// take the latchPin low so the LEDs don't change while you're sending in bits:
   shiftOut(dataPin, clockPin, MSBFIRST, code); // shift out the bits: 
   digitalWrite(latchPin, HIGH); //take the latch pin high so the LEDs will light up:

}

