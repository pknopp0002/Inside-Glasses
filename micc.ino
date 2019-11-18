//#include "MegunoLink.h"
#include <SoftwareSerial.h>


SoftwareSerial BT(3,4);
int nt, ct, c=0;

int LED = 3;

const int MIC = 1; //the microphone amplifier output is connected to pin A0
int adc;
int dB, PdB; //the variable that will hold the value read from the microphone each time
//TimePlot MyPlot;

const int MIC2 = 0; //the microphone amplifier output is connected to pin A0
int adc2;
int dB2, PdB2; //the variable that will hold the value read from the microphone each time



void setup() 
{
  Serial.begin(9600); //sets the baud rate at 9600 so we can check the values the microphone is obtaining on the Serial Monitor
  pinMode(LED, OUTPUT);
  BT.begin(9600);
}

void loop()
{
  ct = micros();
  if(ct>=nt){
  nt=ct+100000; 
  
  PdB = dB; //Store the previous of dB here
  adc = analogRead(MIC); //Read the ADC value from amplifer  
  dB = (adc+83.2073) / 11.003; //Convert ADC value to dB using Regression values

 // MyPlot.SendData("dBValue", dB);

  PdB2 = dB2; //Store the previous of dB here
  adc2= analogRead(MIC2); //Read the ADC value from amplifer 
  dB2 = (adc2+83.2073) / 11.003; //Convert ADC value to dB using Regression values

  int dB_total = (dB + dB2)/2;

  if (PdB!=dB_total)
  {
  BT.print(dB);
  BT.print(" ");
  BT.print(dB2);
  BT.print("\n");
  }

  if (dB_total >= 72)
  {
    digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);
    digitalWrite(LED, LOW);
  }
  }
}
