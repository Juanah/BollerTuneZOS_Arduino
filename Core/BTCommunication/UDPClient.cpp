
#include "Arduino.h"
#include "UDPClient.h"

UDPClient::UDPClient(char *ipAddress,unsigned int port)
{
   this->ipAddress = ipAddress;
   this->port = new unsigned int(port);
}


unsigned int UDPClient::GetPort()
{
   return *this->port; 
}
char * UDPClient::GetIpAddress()
{
    
    return this->ipAddress;
}
