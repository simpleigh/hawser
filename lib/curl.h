#ifndef __CURL_H
#define __CURL_H

#include "buffer.h"

unsigned int curl_get(BUFFER *bufDestination, const char *szUrl);

void curl_cleanup(void);

#endif /* __CURL_H */
