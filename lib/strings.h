#ifndef __STRINGS_H
#define __STRINGS_H

#include <stddef.h>

/**
 * Calculate the length of a string line.
 *
 * Counts the length of the first line of a string by counting up to the first
 * NULL or newline.
 *
 * CAUTION:
 *  - szString MUST contain a NULL or newline.
 *
 * @param char *szString String to measure.
 *
 * @return size_t Length of first line.
 */
size_t strlinelen(const char *szString);

#endif /* __STRINGS_H */
