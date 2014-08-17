#ifndef __CONFIG_H
#define __CONFIG_H

typedef struct Config {
	char szAccessKeyId[21];
	char szSecretAccessKey[41];
	int unsigned fIamRole;
	int unsigned fDebug;
} Config;

extern Config config;

void config_set_access_key_id(const char *szInput);
void config_set_secret_access_key(const char *szInput);
void config_set_iam_role(const char *szInput);
void config_set_debug(const char *szInput);

void config_load(int argc, char **argv);
void config_load_file(const char *szFilename);
void config_load_user_file();
void config_load_environment();
void config_load_arguments(int argc, char **argv);
void config_load_iam();

#endif /* __CONFIG_H */
