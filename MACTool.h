/**
 * @file MACTool.h
 * @copyright 2017
 * @author Bernd Wachter <bernd-github@wachter.fi>
 * @date 2017
 */

#ifndef _MACTOOL_H
#define _MACTOOL_H

#include <EEPROM.h>

#ifndef MACTOOL_USE_PERSISTENT_CONFIGURATION
#define MACTOOL_USE_PERSISTENT_CONFIGURATION 1
#endif

#if MACTOOL_USE_PERSISTENT_CONFIGURATION > 0
#include <PersistentConfiguration.h>
#endif

#ifndef MACTOOL_MAC_PREFIX
#define MACTOOL_MAC_PREFIX "06:DE:AD:00:00:00"
#endif

#ifndef MACTOOL_INIT_RAND
#define MACTOOL_INIT_RAND 1
#endif

#ifndef MACTOOL_SEED_PIN
#define MACTOOL_SEED_PIN 3
#endif


/*
 * Check if the configuration data contains a valid MAC address. If not,
 * generate one and mark the configuration data as changed.
 */
#if MACTOOL_USE_PERSISTENT_CONFIGURATION > 0
void init_MAC();
#endif

/*
 * Validate if each octet is within the allowed range, as well if there
 * are exactly 6 octets. If those tests fail return false to trigger
 * generation of a new MAC.
 */
bool validate_MAC(char *mac_string);

/*
 * Generate a new MAC by putting randomly generated numbers matching
 * ASCII table entries for 0-9 and A-F into the free spaces of the
 * MAC prefix
 */
void generate_MAC(char *mac_string);

/*
 * Convert the string representation of the MAC into a byte array
 * suitable for the Ethernet library
 */
void MAC_to_byte(char *mac_string, byte *mac_byte);

#endif
