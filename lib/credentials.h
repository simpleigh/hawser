#ifndef __CREDENTIALS_H
#define __CREDENTIALS_H

const char * credentials_get_access_key_id();
const char * credentials_get_secret_access_key();
void credentials_set_access_key_id(const char *src);
void credentials_set_secret_access_key(const char *src);

void credentials_load(int argc, char **argv);
void credentials_load_iam();
void credentials_load_file(const char *filename);
void credentials_load_user_file();
void credentials_load_environment();
void credentials_load_arguments(int argc, char **argv);

#endif /* __CREDENTIALS_H */
