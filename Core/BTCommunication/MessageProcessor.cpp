#include "Arduino.h"
#include "MessageProcessor.h"


MessageProcessor::MessageProcessor(UdpService *udpService)
{
  //Service to get Messages from Remote
   this->udpService = udpService; 
}


Message MessageProcessor::ReceiveMessage()
{
  //Message
  //0 = startByte
  //1 = Type
  //2 = Length
  //3 = Data[]
  //4 = endbyte
  
  
  char *emptyDataArray = new char[1];
  emptyDataArray[0] = 0;
  Message errorMessage(0,0,0,emptyDataArray,0,0);
   char *receivedBytes = new char[25];
   
   this->udpService->GetBytes();
   
   if(udpService->packetBuffer[0] != startByte)
   {
      //Startbyte is not what we expected
     return errorMessage; 
   }
   int dataLength = my_atoi((const char *)udpService->packetBuffer[2]);
   
   if(udpService->packetBuffer[2] == 0x01)
   {
       Serial.println("Datalength is 1");
   }
   
   Serial.print("Datalenght:");
   Serial.println(dataLength);
   //as we now know how long the dataArray should be
   //we can easily find out if the Endbyte is right
   
   if(udpService->packetBuffer[udpService->packetBuffer[2] + 3] != endByte)
   {
     //Endbyte is not what we expected,
     //that means the Message must be broken
     Serial.println("Endbyte is broken");
     return errorMessage;
   }
   
   char *dataBytes = new char[dataLength];  
   
  //Store the DataBytes, which always begin at index 3
  for(int i=3;i < udpService->packetBuffer[2];i++)
  {
    dataBytes[i -3] = udpService->packetBuffer[i];
  }
  Serial.println("Returning Message");
  return Message(startByte,udpService->packetBuffer[1],udpService->packetBuffer[2],dataBytes,endByte,1);
}

int MessageProcessor::my_atoi(const char *s)
{
 int sign=1;
 if(*s == '-')
        sign = -1;
 s++;
 int num=0;
 while(*s)
  {
    num=((*s)-'0')+num*10;
    s++;   
  }
 return num*sign;
}

