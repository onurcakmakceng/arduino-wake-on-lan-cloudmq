#include <SPI.h>
#include <Ethernet.h>


//#TODO: These variables can be 'const', consider
//--FIELDS--------------------------------------------
// The media access control (ethernet hardware) address for the shield:
byte mac[] = { 0x00, 0x00, 0x0B, 0xAA, 0xBB, 0xCC }; 

// The broadcast IP of our network
byte broadCastIp[] = { 255, 255, 255, 255 };

// Mac address of the machine we want to WOL
byte remote_MAC_ADD[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//UDP WOL port
int wolPort = 9;
//----------------------------------------------------


//--INITIALIZE----------------------------------------
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  Serial.println("Arduino is initializing. Please wait...");

  // Initialize the ethernet device
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }

  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");

  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}
//----------------------------------------------------


//--WORKER-THREAD-------------------------------------
void loop() {
  if (Serial.read() == 'w') {
     
    Serial.println("I'm in");
    
    byte magicPacket[102];
    
    //#TODO: String operations can be implemented later
    int i, j, k;
    
    // Magic message? or Offset?
    for (i = 0; i < 6; i++) {
      magicPacket[i] = 0xFF;
    }

    // Target MAC Address
    for (j = 0; j < 16; j++) {
      for (k = 0; k < 6; k++, i++) {
        magicPacket[i] = remote_MAC_ADD[k];
      }
    }

    EthernetUDP Udp;

    Udp.begin(wolPort);
    Udp.beginPacket(broadCastIp, wolPort);
    Udp.write(magicPacket, sizeof magicPacket);
    Udp.endPacket();
  }
}
//----------------------------------------------------
