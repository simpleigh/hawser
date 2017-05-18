#include "hawser/hawser.h"
#include "hawser/info.h"

#include "../hawser_internal.h"


/**
 * AWS names for each service.
 */
static const char *AWS_SERVICES[AWS_SERVICE_COUNT] = {
	"ec2",
	"lambda",
	"sns",
	"sqs",
	"s3"
};


HAWSERresult
aws_service(AWS_SERVICE service, const char **dest)
{
	REQUIRE_RANGE(service, AWS_SERVICE_MIN, AWS_SERVICE_MAX);
	REQUIRE_NOT_NULL(dest);

	*dest = AWS_SERVICES[service];

	return HAWSER_OK;
}
