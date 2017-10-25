/**
 * @file MACTool.h
 * @copyright 2017
 * @author Bernd Wachter <bernd-github@wachter.fi>
 * @date 2017
 */

#ifndef _MACTOOL_H
#define _MACTOOL_H

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
