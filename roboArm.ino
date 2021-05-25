//Codes to test a degree of freedom of a 3D printed robotic arm

// Stepper Motor X
  const int stepPinx = 2; //X.STEP
  const int dirPinx = 5; // X.DIR

// Stepper Motor Y
  const int stepPiny = 3; //X.STEP
  const int dirPiny = 6; // X.DIR
  
// joystick
int vrx = A0; 
int vry = A1; 
int vrx_data = 0; 
int vry_data = 0; 

int x = 0;
int y = 0;
 
int SMSpeed = 500; // Stepper Motor Speed 
 void setup() {
 // Sets the two pins as Outputs
 Serial.begin(9600); 
 pinMode(stepPinx,OUTPUT); 
 pinMode(dirPinx,OUTPUT);
 pinMode(stepPiny,OUTPUT); 
 pinMode(dirPiny,OUTPUT);
 pinMode(vrx , INPUT); 
 pinMode(vry, INPUT); 
 }

 
 void loop() 
 {
  
joystick(); 

 }

 void joystick()
{
vrx_data = analogRead(vrx);
Serial.print("Vrx:"); 
Serial.println(vrx_data); 

vry_data = analogRead(vry);
Serial.print("Vry:"); 
Serial.println(vry_data); 

// to stop the stepper motor
if ( (vrx_data > 490)  &&   (vrx_data < 510)   )
{

;
  
}


if ( vrx_data > 700  )
{

digitalWrite(dirPinx,HIGH);
//digitalWrite(dirPiny,HIGH); //appended 28.2.21 16:16
x = x + 1; 
 digitalWrite(stepPinx,HIGH);  
 //digitalWrite(stepPiny,HIGH); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed); 
 digitalWrite(stepPinx,LOW);
 //digitalWrite(stepPiny,LOW); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed); 
  
}




if ( vrx_data < 300   )
{
digitalWrite(dirPinx,LOW);
//digitalWrite(dirPiny,LOW); //appended 28.2.21 16:16
x = x - 1; 

 digitalWrite(stepPinx,HIGH); 
 //digitalWrite(stepPiny,HIGH); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed); 
 digitalWrite(stepPinx,LOW); 
 //digitalWrite(stepPiny,LOW); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed);  
}

//do y axis
// to stop the stepper motor
if ( (vry_data > 490)  &&   (vry_data < 510)   )
{

;
  
}


if ( vry_data > 700  )
{

digitalWrite(dirPiny,HIGH);
digitalWrite(dirPinx,HIGH); //appended 28.2.21 16:16
y = y + 1; 

 digitalWrite(stepPiny,HIGH); 
 digitalWrite(dirPinx,HIGH); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed); 
 digitalWrite(stepPiny,LOW); 
 digitalWrite(dirPinx,LOW); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed); 
  
}


//do y axis

if ( vry_data < 300   )
{
digitalWrite(dirPiny,LOW);
digitalWrite(dirPinx,LOW); //appended 28.2.21 16:16
y = y - 1; 

 digitalWrite(stepPiny,HIGH); 
 digitalWrite(dirPinx,HIGH); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed); 
 digitalWrite(stepPiny,LOW); 
 digitalWrite(dirPinx,LOW); //appended 28.2.21 16:16
 delayMicroseconds(SMSpeed);  
}





}
