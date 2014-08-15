#ifndef __BUFFER_H
#define __BUFFER_H

#include <stddef.h>

typedef struct BUFFER BUFFER;

BUFFER *buffer_create(void);

BUFFER *buffer_from(const char *szString);
BUFFER *buffer_nfrom(const char *szString, size_t cbString);

size_t buffer_len(const BUFFER *buffer);
char * buffer_data(const BUFFER *buffer);

size_t buffer_append(BUFFER *buffer, const char *szString);
size_t buffer_nappend(BUFFER *buffer, const char *szString, size_t cbString);
size_t buffer_append_line(BUFFER *buffer, const char *szString);

void buffer_clear(BUFFER *buffer);
void buffer_destroy(BUFFER *buffer);

#endif /* __BUFFER_H */
