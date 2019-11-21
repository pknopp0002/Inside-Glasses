//#include "MegunoLink.h"
#include <SoftwareSerial.h>


SoftwareSerial BT(8,4);
int nt, ct, c=0;

int LED = 3;
int ledstate = LOW;
int interval = 500000;

const int MIC = 1; //the microphone amplifier output is connected to pin A0
int adc;
int dB, PdB; //the variable that will hold the value read from the microphone each time
//TimePlot MyPlot;

const int MIC2 = 0; //the microphone amplifier output is connected to pin A0
int adc2;
int dB2, PdB2; //the variable that will hold the value read from the microphone each time

int dB_total;
int bluetooth;

void setup() 
{
  Serial.begin(9600); //sets the baud rate at 9600 so we can check the values the microphone is obtaining on the Serial Monitor
  pinMode(LED, OUTPUT);
  BT.begin(9600);
}

void loop()
{
  int sum = 0;
  int sum2 = 0;
  ct = micros();
  if ((ct - nt >= interval) && ledstate == HIGH){
    ledstate = LOW;
    digitalWrite(LED, ledstate);
    nt = ct;
  }
  
 
  
  PdB = dB; //Store the previous of dB here
  PdB2 = dB2; //Store the previous of dB here


  for(int i = 0; i< 5; i++){
  adc = analogRead(MIC); //Read the ADC value from amplifer  
  sum += (adc+83.2073) / 11.003; //Convert ADC value to dB using Regression values
  
 // MyPlot.SendData("dBValue", dB);

  
  adc2= analogRead(MIC2); //Read the ADC value from amplifer 
  sum2 += (adc2+83.2073) / 11.003; //Convert ADC value to dB using Regression values
  
  
  }
  dB = sum / 5;
  dB2 = sum2 / 5;
  

  dB_total = (dB + dB2)/2;
bluetooth = dB_total;

  if (PdB!=dB_total)
  {
  BT.print(dB);
  BT.print("\t");
  BT.print(dB2);
  BT.print("\t");
  BT.print(dB_total);
  BT.print("\n");
  
 
  
  }
  
  
  if (dB_total >= 65)
  {
    ledstate = HIGH;
    digitalWrite(LED, ledstate); 
    nt = micros();
    // turn the LED on (HIGH is the voltage level)
  }
  
  }
