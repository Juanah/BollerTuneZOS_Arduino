#include "Arduino.h"
#include "Message.h"


Message::Message( char startbyte,char mLength,char type, char *data,char endbyte,char legal)
{
   StartByte = startbyte; 
   Length = mLength; 
   Type = type; 
   this->Data = data; 
   EndByte = endbyte; 
   isLegal = legal;
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




