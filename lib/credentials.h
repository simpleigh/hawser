#ifndef __CREDENTIALS_H
#define __CREDENTIALS_H

const char * credentials_get_access_key_id();
const char * credentials_get_secret_access_key();
void credentials_set_access_key_id(char *src);
void credentials_set_secret_access_key(char *src);

void credentials_load_environment();
void credentials_load_arguments(int argc, char **argv);

#endif /* __CREDENTIALS_H */
