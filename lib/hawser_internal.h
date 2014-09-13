#ifndef __HAWSER_INTERNAL_H
#define __HAWSER_INTERNAL_H

/**
 * Boolean value for use in logical expressions.
 */
#define BOOL int


/**
 * True value for use in logical expressions.
 */
#define TRUE 1


/**
 * False value for use in logical expressions.
 */
#define FALSE 0


/**
 * Common return value when strings are equal.
 */
#define COMPARE_EQUAL 0


/**
 * Returns HAWSER_NULL if a supplied pointer is NULL.
 */
#define REQUIRE_NOT_NULL(pointer) if (!pointer) return HAWSER_NULL


/**
 * Returns HAWSER_INVALID if a supplied value is out of range.
 */
#define REQUIRE_RANGE(value, min, max) \
	if ((value) < (min) || (value) > (max)) {\
		return HAWSER_INVALID;\
	}


#endif /* __HAWSER_INTERNAL_H */
