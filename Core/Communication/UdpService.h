#ifndef UdpService_h
#define UdpService_h

#include <SPI.h>         
#include <Ethernet.h>
#include <EthernetUdp.h>

#include "Arduino.h"
#include "UDPConnectionInfo.h"
#include "UDPClient.h"

class UdpService
{
  public:
    UdpService();
    void Init(UDPConnectionInfo *connectionInfo);
    
    //Receive Methods
    String GetStringData();
    char * GetBytes();
    
    //Send Methods
    int SendString(String string,UDPClient *client);
    
    int SendBytes(char *bytes,UDPClient *client);
    
  private:
    UDPConnectionInfo *connectionInfo;
    byte *macAdress;
    byte *ipaddress;
    EthernetUDP Udp;
    char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
};

#endif
