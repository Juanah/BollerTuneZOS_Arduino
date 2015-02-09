#include "Arduino.h"
#include "MessageProcessor.h"


MessageProcessor::MessageProcessor(UdpService *udpService)
{
  //Service to get Messages from Remote
    char *emptyDataArray = new char[1];
    emptyDataArray[0] = 0;
    
   this->udpService = udpService; 
   erMessage = new Message();
   erMessage->isLegal = 0;
   rMessage = new Message();
}


Message * MessageProcessor::ReceiveMessage()
{
  //Message
  //0 = startByte
  //1 = Type
  //2 = Length
  //3 = Data[]
  //4 = endbyte
   
   this->udpService->GetBytes();
    
   if(udpService->packetBuffer[0] != startByte)
   {
      //Startbyte is not what we expected
     return erMessage; 
   }
   //as we now know how long the dataArray should be
   //we can easily find out if the Endbyte is right
   
   if(udpService->packetBuffer[udpService->packetBuffer[2] + 3] != endByte)
   {
     //Endbyte is not what we expected,
     //that means the Message must be broken
     
     return erMessage;
   }
   _length = (int)((unsigned char)udpService->packetBuffer[2]);
   
   char *dataBytes; 
   char testBuffer[_length];
   Serial.println("SetArray");
  //Store the DataBytes, which always begin at index 3
  for(int i=0;i < _length;i++)
  {
    testBuffer[i] = udpService->packetBuffer[(i +3)];
  }  
  
  dataBytes = testBuffer;
  Serial.println("Returned");
  rMessage->isLegal = 1;
  rMessage->Length = udpService->packetBuffer[2];
  rMessage->Type = udpService->packetBuffer[1];
  rMessage->Data = dataBytes;
  return rMessage;
}


