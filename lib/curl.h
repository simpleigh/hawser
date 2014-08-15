#ifndef __CURL_H
#define __CURL_H

#include "buffer.h"

void curl_get(BUFFER *buffer, const char *szUrl);

void curl_cleanup(void);

#endif /* __CURL_H */
