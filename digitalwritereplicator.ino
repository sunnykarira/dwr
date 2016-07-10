
#include <Servo.h>                       //to be included for servomotor
#include<SoftwareSerial.h>   //to be included to send or recieve data
Servo left;                   //object for left motor

int incoming=0;              //to save incoming co-ordinate
int x=0;                    //to save x coordinate
int y=0;                      //to save y co-ordinate
 
Servo right;                 //right motor object
SoftwareSerial recieve(4,5);  //RX,TX        //to send or recieve data from bluetooth and app  4 th pin of arduino as RX , and 5th pin TX

 int uppos;
int pos = 0;    // variable to store the servo position 
int leftturn=0;  
 int i=0;  //incrementor
 Servo up;
void setup() 
{ 
  left.attach(8);  // left motor configure
  right.attach(9); // right motor configure
  up.attach(7);  //hold up motor configure
  recieve.begin(9600);  // begin  recieving from bluetooth
  Serial.begin(9600); // begin recieving from serial monitor
  
  
} 
 
void loop() 
{   
    if(Serial.available()>0){ 
      int switcher=Serial.parseInt();                      //serial.parseint() converts data available at serial monitor into integer
      if(switcher==1){
       int leftservoleftturn=Serial.parseInt();
       Serial.write(leftservoleftturn);                     //for calibration
       for(pos=leftservoleftturn;pos>=0;pos-=1){            //recieve input from serial monitor
        left.write(pos);                                     //and move left motor by left turn
        delay(20);
       }
         
      }
      
      if(switcher==2){
        int leftservorightturn=Serial.parseInt();
        Serial.write(leftservorightturn);
       for(pos=0;pos<=leftservorightturn;pos+=1){             //for calibration
        left.write(pos);                                       //move left motor by right turn
        delay(20);
       }
      }
      
      if(switcher==3){
        int rightservoleftturn=Serial.parseInt();           //for calibration
        Serial.write(rightservoleftturn);                   //move right motor by left turn
       for(pos=rightservoleftturn;pos>=0;pos-=1){
        right.write(pos);
        delay(20);
       }
      
      }
      if(switcher==4){
        int rightservorightturn=Serial.parseInt();         //for calibration
        Serial.write(rightservorightturn);                 //move right motor by right turn
       for(pos=0;pos<=rightservorightturn;pos+=1){
        right.write(pos);
        delay(20);
       }
      
      }
      
        
    }
 
  
  if(recieve.available()>0){                 //if data from app to bluetooth is available
    
    i++;                                    //incement
    incoming=recieve.read();                 //read data into incoming variable
    incoming=map(incoming,0,255,0,60);    // map it from 0-255 to 0-60 degrees
    if(i==1){                                      //if i=1 means x-cordinate is coming from app
      for(uppos=0;uppos<=30;uppos+=1){                 //move up motor by 30 degrees up
       up.write(30-uppos);
      }
      x=incoming;                             //save the x cordinate
      Serial.write(incoming);
      for(pos=0;pos<=x;pos+=1){
        leftturn=1;                              //move left and right motor x degrees with delay 30
      left.write(pos);
      right.write(pos);
      delay(30);
      }
    }
    if(i==2){                            //if i=2 means y cordinate is coming from app
        i=0;
      y=incoming;                       //save y coordinate
      Serial.write(incoming);
      for(pos=0;pos<=y;pos+=1){
      right.write(pos);                   //move right motor right
      left.write(y-pos);                   //move left motor left to traverse y coordinate on paper
      delay(30);
      }
      //iskey baad wapas band karenge
      
      
      for(uppos=0;uppos<=180;uppos+=1){
       up.write(uppos);
       delay(10);
      }
      
      for(uppos=180;uppos>=0;uppos-=1){
      up.write(uppos);
      delay(10);
      }      
      
    }
  
 
} 
else{
  if(leftturn==1){                 //this is the code to bring motors to the position where they started writing on paper
  for(pos=0;pos<=y;pos+=1){
   right.write(y-pos);
   left.write(pos);                      
   delay(30);
  }
  for(pos=0;pos<=x;pos+=1){
    left.write(x-pos);
    right.write(x-pos);
    delay(30);
  
  }
  leftturn=0;
  }
}
delay(200);
}

