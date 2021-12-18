#include <IRLibSendBase.h>    //We need the base code
#include <IRLib_HashRaw.h>    //Only use raw sender


const int analogInPinEnter = A1;  // Analog input pin that the receiver is attached to
const int analogInPinExit = A2;  // Analog input pin that the receiver is attached to

int sensorValueEnter = 0; // value read from the receiver
int sensorValueExit = 0; // value read from the receiver
int counter = 0; // value read from the receiver


IRsendRaw mySender;


#define RAW_DATA_LEN 260
uint16_t rawDataOn[RAW_DATA_LEN]={
  3250, 1642, 406, 406, 406, 406, 410, 1218, 
  410, 406, 406, 1222, 406, 406, 406, 406, 
  406, 406, 410, 1218, 406, 1222, 406, 406, 
  410, 402, 410, 406, 406, 1218, 410, 1222, 
  406, 402, 410, 402, 410, 406, 406, 402, 
  410, 406, 406, 406, 406, 406, 410, 406, 
  406, 402, 406, 406, 406, 406, 410, 402, 
  410, 406, 406, 1222, 406, 406, 410, 402, 
  410, 402, 406, 406, 410, 402, 410, 402, 
  410, 406, 406, 1222, 406, 406, 410, 402, 
  410, 402, 410, 402, 410, 1218, 406, 1218, 
  410, 1218, 410, 1214, 410, 1218, 410, 1214, 
  410, 1222, 406, 1222, 410, 402, 410, 402, 
  410, 1222, 406, 406, 410, 402, 410, 402, 
  410, 402, 406, 406, 410, 402, 410, 402, 
  410, 406, 406, 1218, 410, 1218, 410, 402, 
  410, 402, 410, 1222, 410, 402, 410, 402, 
  410, 402, 410, 402, 410, 1222, 406, 406, 
  410, 402, 410, 1218, 410, 402, 410, 402, 
  410, 402, 410, 406, 410, 402, 410, 402, 
  410, 402, 410, 1218, 410, 402, 410, 402, 
  410, 406, 406, 406, 410, 402, 410, 402, 
  410, 402, 410, 402, 410, 402, 410, 402, 
  410, 402, 410, 402, 410, 406, 406, 406, 
  410, 402, 406, 402, 410, 406, 406, 406, 
  410, 402, 410, 402, 410, 402, 410, 402, 
  410, 402, 410, 402, 410, 402, 410, 402, 
  410, 406, 406, 406, 410, 402, 410, 402, 
  410, 402, 406, 406, 410, 402, 410, 402, 
  410, 402, 410, 406, 406, 1222, 410, 402, 
  410, 402, 410, 1218, 410, 406, 406, 1218, 
  410, 1222, 406, 406, 406, 406, 410, 402, 
  410, 1310, 410, 1000};



#define RAW_DATA_LEN 116
uint16_t rawDataOff[RAW_DATA_LEN]={
  3254, 1638, 410, 402, 410, 406, 406, 1222, 
  410, 402, 410, 1218, 410, 406, 406, 406, 
  410, 402, 410, 1214, 410, 1222, 406, 406, 
  406, 406, 410, 402, 410, 1218, 410, 1218, 
  410, 402, 410, 402, 410, 402, 410, 402, 
  410, 402, 410, 402, 410, 406, 406, 406, 
  406, 402, 410, 402, 410, 402, 410, 406, 
  410, 402, 410, 1218, 410, 402, 410, 402, 
  410, 402, 410, 406, 406, 406, 406, 406, 
  406, 406, 410, 1218, 410, 402, 410, 402, 
  410, 402, 410, 406, 406, 1222, 410, 402, 
  410, 402, 410, 402, 410, 402, 410, 402, 
  410, 406, 406, 1222, 410, 402, 410, 1218, 
  410, 1214, 410, 1218, 410, 1214, 410, 1218, 
  410, 1310, 410, 1000};


  void setup() {
  //initialize serial communications at 9600 bps:
  Serial.begin(9600);
  }
  void loop() {
  // read the analog in value:
  sensorValueEnter = analogRead(analogInPinEnter);
  sensorValueExit = analogRead(analogInPinExit);
     

  if(sensorValueEnter < 403){ //checks if object is there or not
    counter+=1;
    if(counter == 1){ //checks if object is the first object in room 
      mySender.send(rawDataOn,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequenc (open AC)
  }}
 
  if(sensorValueExit < 203 ){ //checks if object is there or not
    if(counter == 0){ //checks if object is the last one in room
      mySender.send(rawDataOff,RAW_DATA_LEN,36);//Pass the buffer,length, optionally frequenc (shut down AC)
    }else{
      counter-=1;
    }}
    
  
  // print the results to the serial monitor to send it to generate CSV file usingPython:
  Serial.print(sensorValueEnter);
  Serial.print(",");
  Serial.print(sensorValueExit);
  Serial.print(",");
  if(counter != 0){
  Serial.println("1");//means AC On
  }else{
  Serial.println(counter);//means AC Off
  }
  delay(1000);
}
