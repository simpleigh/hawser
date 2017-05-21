#ifndef __ID_H
#define __ID_H

#include <stdlib.h>

#include "hawser/hawser.h"

#include "../hawser_internal.h"


/**
 * Type of function that validates ID characters.
 * Is scanned across a string.
 *  - first iteration: previous is NUL
 *  - last iteration: current is NUL
 */
typedef BOOL (*ID_VALIDATOR)(char current, char previous);


/**
 * Copies an ID string, performing some basic checks.
 */
HAWSERresult id_checked_copy(
    char *id,
    const char *string,
    size_t min_strlen,
    size_t max_strlen,
    ID_VALIDATOR validator_fn
);


#endif /* __ID_H */
