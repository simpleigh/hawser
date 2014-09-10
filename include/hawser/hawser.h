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


#ifdef __cplusplus
}
#endif

#endif /* __HAWSER_H */
