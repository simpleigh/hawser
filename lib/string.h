#ifndef __STRING_H
#define __STRING_H

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

#endif /* __STRING_H */
