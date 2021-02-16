/**
 * @file MACTool.cpp
 * @copyright 2017
 * @author Bernd Wachter <bernd-github@wachter.fi>
 * @date 2017
 */

#include <stdlib.h>
#include <string.h>
#include <Arduino.h>

#include "MACTool.h"

/*
 * Prefix for generating MAC addresses. The last three octets
 * will be replaced with random numbers. MAC addresses are
 * permanent.
 */
char mac_prefix[18] = MACTOOL_MAC_PREFIX;

#if MACTOOL_USE_PERSISTENT_CONFIGURATION > 0
void init_MAC(){
#if MACTOOL_INIT_RAND > 0
  randomSeed(analogRead(MACTOOL_SEED_PIN));
#endif

  if (!validate_MAC(config.mac)){
    generate_MAC(config.mac);
    state.config_changed = true;
  }
}
#endif

bool validate_MAC(char *mac_string){
  char mac_address[18];
  char *t_ptr;

  strcpy(mac_address, mac_string);
  t_ptr = strtok(mac_address, ":");

  int i = 0;
  while (t_ptr != NULL){
    int octet = strtol(t_ptr, NULL, 16);
    if (octet < 0 || octet > 255)
      return false;

    t_ptr = strtok(NULL, ":");
    i++;
  }

  // loop should've covered exactly 6 octets
  if (i != 6)
    return false;

  return true;
}

void generate_MAC(char *mac_string){
  strcpy(mac_string, mac_prefix);
  // Generate pos. 9,10; 12,13; 15,16
  for (int i=0; i<9; i+=3){
    for (int j=0; j<2; j++){
      if (random(0,2))
        // ASCII-Table 0-9
        mac_string[9+j+i] = random(48,58);
      else
        // ASCII-Table A-F
        mac_string[9+j+i] = random(65,71);
    }
  }
}

void MAC_to_byte(char *mac_string, byte *mac_byte){
  char *t_ptr;
  char mac[18];
  strcpy(mac, mac_string);

  t_ptr = strtok(mac, ":");
  int i = 0;
  while (t_ptr != NULL){
    mac_byte[i] = strtol(t_ptr, NULL, 16);
    t_ptr = strtok(NULL, ":");
    i++;
  }
}
