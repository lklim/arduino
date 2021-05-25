#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
//#define SD_ChipSelectPin 10  //using digital pin 4 on arduino nano 328
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>

int index = 0;

TMRpcm tmrpcm;   // create an object for use in this sketch
char mychar;

char *song[] = {"some.wav","rolling.wav","adagio.wav","young.wav","show.wav", "roger.wav", "trouble.wav","midd.wav","air.wav","bird.wav","stfire.wav","amanda.wav","kabar.wav","dance.wav","wild.wav","17.wav","ymca.wav","universe.wav"}; 

void setup(){
 
  tmrpcm.speakerPin = 11; //11 on Mega, 9 on Uno, Nano, etc
  //Complimentary Output or Dual Speakers:
  //pinMode(12,OUTPUT); //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45
  
  Serial.begin(9600);
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail"); 
    return;   // don't do anything more if not
  }
  else {
      Serial.println("Key in Song Code and press enter:");
      Serial.println("-----------------------------------------");
      Serial.println("Adele - Somebody Like You[0], Adele - Rolling in the Deep[1], Fun We are Young[3], Lenka - The show[4], Lenka - Trouble is a friend[6], The Middle East - Blood[7], Nelly Furtado - I'm Like A Bird[9]");
      Serial.println("Mamma&Papa - dancing in the Street[13], Goodies - wild thing[14], Ian Janis - Seventeen[15], Village People - YMCA[16], Across The Universe[17]");   
  }
  tmrpcm.play(song[index]); //the sound file "music" will play each time the arduino powers up, or is reset
}
 
void loop(){ 
  if(! tmrpcm.isPlaying() ){
     ++index;
     if(index > 17) {
       index = 0;
     }  
     tmrpcm.play(song[index]);
     delay(2000); //do not incre while waiting for player to start
  }
  if(Serial.available() > 0){  
    
    static char input[3];
    static uint8_t i;
    mychar = Serial.read();
 /*
    if(mychar == 'a'){ //send the letter a over the serial monitor to start playback
      tmrpcm.play("air.wav");
      index = 8;
    } 
    else if(mychar == 'b'){ //send the letter b over the serial monitor to start playback
      tmrpcm.play("bird.wav");
      index = 9;
    } else if(mychar == 'd'){ //send the letter d over the serial monitor to start playback
      tmrpcm.play("amanda.wav");
      index = 11;
    }  else if(mychar == 'k'){
      tmrpcm.play("kabar.wav");
      index = 12;
    } else if(mychar == 'm'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("midd.wav");
      index = 7;
    } else if(mychar == 'r'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("rolling.wav");
      index = 1;
    } else if(mychar == 'o'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("show.wav");
      index = 4;
     } else if(mychar == 'e'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("some.wav");
      index = 0;
     } else if(mychar == 't'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("trouble.wav");
      index = 6;
     } else if(mychar == 'u'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("universe.wav");
      index = 3;
     } else if(mychar == 'g'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("roger.wav");
      index = 5;
     } else if(mychar == 's'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("stfire.wav");
      index = 10;
     } else if(mychar == 'i'){ //send the letter m over the serial monitor to start playback
      tmrpcm.play("adagio.wav");
      index = 2;
     }
   */
  

  if (  mychar != '\r' && i < 2 ) // assuming "Carriage Return" is chosen in the Serial monitor as the line ending character
    input[i++] =  mychar;
    
  else
  {
    input[i] = '\0';
    i = 0;
      
     index = atoi( input );
     tmrpcm.play(song[index]);
  }
  
    /*if((int)(mychar - '0') >= 0){
    index = (int)(mychar - '0');
    tmrpcm.play(song[index]);
    }*/
    
   delay(1000);
  }
 
}
