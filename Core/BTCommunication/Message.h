#ifndef Message_h
#define Message_h

#include "Arduino.h"

class Message
{
  public:
    Message();
    Message( char startbyte,char mLength,char type, char *data,char endbyte,char legal);
    
    
    //Data Methods
    String DataToString();
    int DataToInt();
    float DataToFloat();
    double DataToDouble();
    
    
    char StartByte;
    char Length;
    char Type;
    char *Data;
    char EndByte;
    
    char isLegal;
    
  private:

};


#endif
