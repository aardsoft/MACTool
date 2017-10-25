/*
 * This example should have your Arduino request an address from DHCP with a
 * newly generated MAC on the first try, and re-using this MAC on any reset
 * or reflash, as long as the new code does not overwrite the EEPROM region
 * used for storing the MAC
 */

#include <SPI.h>
#include <Ethernet.h>
#include <MACTool.h>
#include <EEPROM.h>

char mac[18];

void setup(){
  // initialize random number generator from unused(!) analogue pin 3
  randomSeed(analogRead(3));

  // read the MAC as string from EEPROM
  EEPROM.get(0, mac);

  // check if the read MAC is valid...
  if (!validate_MAC(mac)){
    // .. and if not, generate one ..
    generate_MAC(mac);
    // .. and write it to the EEPROM
    EEPROM.put(0, mac);
  }

  // the byte representation of the MAC
  byte mac_b[8];

  // convert string representation to byte
  MAC_to_byte(mac, mac_b);

  // configure network via DHCP
  if (Ethernet.begin(mac_b) == 0)
    for(;;);
}

void loop(){
  delay(1000);
}
