#ifndef MessageProcessor_h
#define MessageProcessor_h

#include "Arduino.h"
#include "UdpService.h"
#include "Message.h"

class MessageProcessor
{
  public:
    MessageProcessor(UdpService *udpService);
    
    //Receives a standart min. 5Byte Message
    Message ReceiveMessage();
    
  private:
  UdpService *udpService;
  char endByte = 0xDE;
  char startByte = 0x01;
  int my_atoi(const char *s);
};


#endif
