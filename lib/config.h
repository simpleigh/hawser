#ifndef __CONFIG_H
#define __CONFIG_H

const char * config_get_access_key_id();
const char * config_get_secret_access_key();
unsigned int config_get_debug();

void config_set_access_key_id(const char *src);
void config_set_secret_access_key(const char *src);
void config_set_debug(const char *src);

void config_load(int argc, char **argv);
void config_load_iam();
void config_load_file(const char *filename);
void config_load_user_file();
void config_load_environment();
void config_load_arguments(int argc, char **argv);

#endif /* __CONFIG_H */
