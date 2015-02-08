#ifndef UDPClient_h
#define UDPClient_h

#include "Arduino.h"

class UDPClient
{
  public:
    UDPClient(char *ipAddress,unsigned int port);
    unsigned int GetPort();
    char * GetIpAddress();
  private:
    unsigned int *port;
    char *ipAddress;
    
};


#endif
