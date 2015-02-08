#ifndef Message_h
#define Message_h

#include "Arduino.h"

class Message
{
  public:
    Message();
    Message(unsigned char startbyte,unsigned char mLength,unsigned char type, char *data,unsigned char endbyte);
    
    //Data Methods
    String DataToString();
    int DataToInt();
    float DataToFloat();
    double DataToDouble();
    
    
    unsigned char *StartByte;
    unsigned char *Length;
    unsigned char *Type;
    char *Data;
    unsigned char *EndByte;
  private:

};


#endif
