#include "Arduino.h"
#include "Message.h"


Message::Message(unsigned char startbyte,unsigned char mLength,unsigned char type, char *data,unsigned char endbyte)
{
   this->StartByte = new unsigned char(startbyte); 
   this->Length = new unsigned char(mLength); 
   this->Type = new unsigned char(type); 
   this->Data = data; 
   this->EndByte = new unsigned char(endbyte); 
}



String Message::DataToString()
{
   return String(this->Data); 
}
int Message::DataToInt()
{
    return atoi(this->Data);
}
float Message::DataToFloat()
{
 return atof(this->Data); 
  
}
double Message::DataToDouble()
{
   return strtod(this->Data,NULL);
}




