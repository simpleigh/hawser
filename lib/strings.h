#ifndef __STRINGS_H
#define __STRINGS_H

#include <stddef.h>

/**
 * Append a string onto another.
 *
 * Copies bytes from szSource to szDestination while *szSource is not NULL.
 * Returns the final value of szDestination.
 *
 * Can be used to append strings as follows:
 *
 *     char *to = string; // Destination string.
 *     to = strappend(to, "str1");
 *     to = strappend(to, "str2");
 *     // string is now "str1str2"
 *
 * CAUTION:
 *  - Does not copy the terminating NULL byte.
 *  - szSource MUST be NULL-terminated.
 *
 * @param char *szDestination String to copy to.
 * @param char *szSource      String to copy from.
 *
 * @return char * End of copied string.
 */
char *strappend(char *szDestination, const char *szSource);


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
