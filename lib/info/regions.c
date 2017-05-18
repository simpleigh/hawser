#include "hawser/hawser.h"
#include "hawser/info.h"

#include "../hawser_internal.h"


/**
 * AWS names for each region.
 */
static const char *AWS_REGIONS[AWS_REGION_COUNT] = {
	"us-east-2",
	"us-east-1",
	"us-west-1",
	"us-west-2",
	"ca-central-1",
	"ap-south-1",
	"ap-northeast-2",
	"ap-southeast-1",
	"ap-southeast-2",
	"ap-northeast-1",
	"eu-central-1",
	"eu-west-1",
	"eu-west-2",
	"sa-east-1"
};


HAWSERresult
aws_region(AWS_REGION region, const char **dest)
{
	REQUIRE_RANGE(region, AWS_REGION_MIN, AWS_REGION_MAX);
	REQUIRE_NOT_NULL(dest);

	*dest = AWS_REGIONS[region];

	return HAWSER_OK;
}
