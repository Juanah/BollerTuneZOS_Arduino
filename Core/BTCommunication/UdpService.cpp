#include "Arduino.h"
#include "UdpService.h"

UdpService::UdpService()
{
  
}


void UdpService::Init(UDPConnectionInfo *connectionInfo)
{
   byte ipTest[] = {connectionInfo->ipAddress[0],connectionInfo->ipAddress[1],connectionInfo->ipAddress[2],connectionInfo->ipAddress[3]};
   unsigned int port = connectionInfo->GetPort();
   Serial.print("Port:");
   Serial.println(port);

  if(ipTest[0] == 192)
  {
   Serial.println("Address looks right"); 
  }
  
  this->macAdress = new byte[6];
   char * mAddress = connectionInfo->GetMacAddress();
   
   this->macAdress[0] = mAddress[0];
   this->macAdress[1] = mAddress[1];
   this->macAdress[2] = mAddress[2];
   this->macAdress[3] = mAddress[3];
   this->macAdress[4] = mAddress[4];
   this->macAdress[5] = mAddress[5];
  
  Ethernet.begin(this->macAdress,ipTest);

  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print(".");
  }
  if(Udp.begin(port) == 0)
  {
   Serial.println("Failed to initialize UDPService"); 
  }else
  {
  Serial.println("Initialzed");

  }
}

String UdpService::GetStringData()
{
  int packetSize = Udp.parsePacket();
  
  if (packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    
    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);

    
    String returnString = String(packetBuffer);
    for(int i=0;i<UDP_TX_PACKET_MAX_SIZE;i++) packetBuffer[i] = 0;
    
    return returnString;
    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();
  }else
  {
     String noData = "Nodata";
    return noData; 
  }
}


void UdpService::GetBytes()
{
    int packetSize = Udp.parsePacket();
    for(int i=0;i<UDP_TX_PACKET_MAX_SIZE;i++) packetBuffer[i] = 0;
    
    if (packetSize)
  {
    
    // read the packet into packetBufffer
    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    Serial.print("Buffer:");
    Serial.println(sizeof(packetBuffer));
    // send a reply, to the IP address and port that sent us the packet we received
    //Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    //Udp.write(ReplyBuffer);
    //Udp.endPacket();
  }
  
}


int UdpService::SendString(String string,UDPClient *client)
{
  char  ReplyBuffer[] = "r255g0b0";
  int bufferLength = string.length();
  
  char replyBuffer[bufferLength];
  
  string.toCharArray(replyBuffer,bufferLength);
  
  Serial.print("Sizeofbuffer");
  Serial.println(sizeof(replyBuffer));
  Serial.println(client->GetPort());
  
  char * ip2 = client->GetIpAddress();
  
  byte testIP[] = {ip2[0],ip2[1],ip2[2],ip2[3]};
  
  int result =  Udp.beginPacket(testIP, client->GetPort());
    Udp.write(replyBuffer);
    Udp.endPacket();
    Serial.println(result);
    return result;
}
    
int UdpService::SendBytes(char *bytes,UDPClient *client)
{
   int result =  Udp.beginPacket(client->GetIpAddress(), client->GetPort());
    Udp.write(bytes);
    Udp.endPacket();
    return result;
}



