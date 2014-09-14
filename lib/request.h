#ifndef __REQUEST_H
#define __REQUEST_H

typedef struct request REQUEST;

REQUEST *request_create(const char *hostname, const char *path);

void request_destroy(REQUEST *request);

#endif /* __REQUEST_H */
