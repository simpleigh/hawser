#ifndef __CONFIG_H
#define __CONFIG_H

#include "buffer.h"

typedef struct Config {
	const char *szRegion;
	char szAccessKeyId[21];
	char szSecretAccessKey[41];
	BUFFER *bufToken;
	int unsigned fUseMetadata;
	int unsigned fDebug;
	char szInstanceId[11];
} Config;

extern Config config;

void config_set_region(const char *szInput);
void config_set_access_key_id(const char *szInput);
void config_set_secret_access_key(const char *szInput);
void config_set_token(const char *szInput);
void config_set_use_metadata(const char *szInput);
void config_set_debug(const char *szInput);
void config_set_instance_id(const char *szInput);

void config_load(int argc, char **argv);
void config_load_file(const char *szFilename);
void config_load_user_file(void);
void config_load_environment(void);
void config_load_arguments(int argc, char **argv);
void config_load_iam(void);
void config_load_region(void);

#endif /* __CONFIG_H */
