#ifndef __HAWSER_H
#define __HAWSER_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Result ENUM.
 *
 * Many functions return this type in order to indicate success or failure.
 * New error conditions may be added in future versions.
 */
typedef enum {
	HAWSER_OK = 0,
	HAWSER_INVALID, /* Invalid input data.           */
	HAWSER_NULL,    /* NULL pointer passed as input. */
	HAWSER_MEMORY   /* Memory allocation issue.      */
} HAWSERresult;


/**
 * AWS regions.
 */
typedef enum {
	AWS_REGION_INVALID = -1,
	AWS_US_EAST_1      =  0,
	AWS_US_WEST_2,
	AWS_US_WEST_1,
	AWS_EU_WEST_1,
	AWS_AP_SOUTHEAST_1,
	AWS_AP_SOUTHEAST_2,
	AWS_AP_NORTHEAST_1,
	AWS_SA_EAST_1
} AWS_REGION;


/**
 * Minimum valid AWS region.
 */
#define AWS_REGION_MIN AWS_US_EAST_1


/**
 * Maximum valid AWS region.
 */
#define AWS_REGION_MAX AWS_SA_EAST_1


/**
 * Number of AWS regions.
 */
#define AWS_REGION_COUNT (AWS_REGION_MAX - AWS_REGION_MIN + 1)


/**
 * AWS credentials.
 */
typedef struct {
	char *accessKeyId;
	char *secretAccessKey;
	char *token;
} AWS_CREDENTIALS;


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_H */
