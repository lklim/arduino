/* 
Admendment 2.0 Date 14.1.14
   1) Modify loop to become interrrupt on A0
*/   


#include <Goertzel.h>

//Arduino project to detect the phone number press by the tone sound of the dial

int sensorPin = A0;
int led = 13;

// ideally an integer of SAMPLING_FREQUENCY/N to center the bins around your content so if you're
// looking for 700hz, frequencies below and above it equally contribute. Read up on Kevin's article 
// for more info.
// Nyquist says the highest frequency we can target is SAMPLING_FREQUENCY/2 
//const float TARGET_FREQUENCY = 852; 

const int freq[8] = { 697, 770, 852, 941, 1209, 1336, 1477, 1633} ;
byte  freqCount[8] = { 0, 0, 0, 0, 0, 0, 0, 0};
char pressKey[4][4] = { { '1', '2', '3', 'A' },
                        { '4', '5', '6', 'B' },
                        { '7', '8', '9', 'C' },
                        { '*', '0', '#', 'D' }};
boolean sounded = false;
                        
// if you're trying to detect several different drum hits all within low frequency like
// ~100-200hz you'll need a small bin size like 25 or 50 to distinguish them.
// If however you're just trying to find ANY bass hit you might want something
// basically equal to frequency youre looking for like ~100
 
// If Im detecting a frequency much higher with no care about nearby tones, like 2000hz
// Ill set to a round divisor like 200 So 1900 to 2100 could trigger, but not less or more
// Max is 200 as we have limited ram in the Arduino, and sampling longer would make us less 
// responsive anyway
const int N = 199; 	

// This is what will trigger the led. Its INCREDIBLY squishy based on volume of your source, 
// frequency, etc. You'll just need to get in your environment and look at the serial console
// to start. Then pick something that triggers pleasantly to your eye.
const float THRESHOLD = 4000; //4060; //4000;	

// Again, the highest frequency we can target is SAMPLING_FREQUENCY/2. So Since Arduino is 
// relatively slow in terms of audio, we sample literally as fast as we can
// This is generally around ~8900hz for a 16mhz Arduino and 4400hz for an 8mhz Arduino.
// User nicola points out these rates are for stock arduino firmware and that on a board 
// by board basis you can juice the adc rates. For Arduino Uno you could move that rate up to 
// 22khz by adding somthing like this to your setup:
//  _SFR_BYTE(ADCSRA) |=  _BV(ADPS2); // Set ADPS2
//  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS1); // Clear ADPS1
//  _SFR_BYTE(ADCSRA) &= ~_BV(ADPS0); // Clear ADPS0
const float SAMPLING_FREQUENCY = 8880 ; //8900; 

long interval = 0;
boolean keypressed = false;

Goertzel goertzel = Goertzel(852, N, SAMPLING_FREQUENCY);

// version 2 addition 14.1.15
void pciSetup(byte pin) 
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group 
}

// version 2 end addition 14.1.15

ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
 digitalWrite(13,digitalRead(A0));
 sounded = true;
 }  

void setup(){
    // version 2 addition 14.1.15
  //digitalWrite(A0,HIGH);
  pciSetup(A0);
  // version 2 end addition 14.1.15
  
  goertzel.calibrate(sensorPin);
  pinMode(led, OUTPUT);     
  Serial.begin(9600); 
  Serial.println("Waiting for target Frequency");
  Serial.println("__________________________________________________");
 

}



void loop()
{
  
if(sounded){
  sounded = false;  
  int i;
  goertzel.sample(sensorPin); //Will take n samples
  
  for(i=0; i<8; i++) {
   goertzel.goertzel2(freq[i], N, SAMPLING_FREQUENCY);  
   float magnitude = goertzel.detect();  //check them for target_freq
  
   if(magnitude>THRESHOLD){ //if you're getting false hits or no hits adjust this
     digitalWrite(led, HIGH); //if found, enable led 
     ++freqCount[i];
     Serial.print(freq[i]);
     Serial.println(", "); 
     if( interval == 0) interval = millis();
     keypressed = true;
      }
   else {
     // digitalWrite(led, LOW); //if not found, or lost, disable led
     // Serial.print("L.");
       }
   }
   
  if(keypressed)  //ensure interval between key pressese at least x seconds apart 
    //if(millis() - interval > 2000 ){
      {
        delay(2000);
      Serial.print("Key tone detected: "); 
      Serial.print(pressKey[getIndexOfMaximumValue(freqCount,0,4)][getIndexOfMaximumValue(freqCount,4,8)-4]);
      //byte a , b;
     // a = getIndexOfMaximumValue(freqCount,0,4);
     // b = getIndexOfMaximumValue(freqCount,4,8) - 4;
     
     /*
      byte a = 0;
       byte b = 0;
      {
      
       byte maxIndex = 0;
       byte max = freqCount[maxIndex];
       for ( i=0; i<4; i++){
       if (max<freqCount[i]){
          max = freqCount[i];
          a = i;
             }
        }  
      }
      
       {
      
       byte maxIndex = 4;
       byte max = freqCount[maxIndex];
       for (i=4; i<8; i++){
       if (max<freqCount[i]){
          max = freqCount[i];
          b = i - 4;
             }
        }  
      }
     
      
      Serial.print(a);
      Serial.print(",");
      Serial.println(b);
      Serial.print("Key tone detected: ");
      Serial.println(pressKey[a][b]);  */
    
      keypressed = false;
      interval = 0;
      Serial.println(); 
      for(i=0; i<8; ++i)
       freqCount[i] = 0;
    }
  // Serial.println(magnitude);
  }
}

byte getIndexOfMaximumValue(byte* array, byte startp, byte sizep){
  byte maxIndex = startp;
  byte max = array[maxIndex];
  for (byte i=startp; i<sizep; i++){
    if (max<=array[i]){
      max = array[i];
      maxIndex = i;
    }
  }
  return maxIndex;
}
