#include "hawser/hawser.h"
#include "hawser/info.h"

#include "../hawser_internal.h"


/**
 * AWS names for each service.
 */
static const char *AWS_SERVICE_NAMESPACES[AWS_SERVICE_COUNT] = {
	"ec2",
	"lambda",
	"sns",
	"sqs",
	"sts",
	"s3"
};


HAWSERresult
aws_service_namespace(AWS_SERVICE service, const char **dest)
{
	REQUIRE_RANGE(service, AWS_SERVICE_MIN, AWS_SERVICE_MAX);
	REQUIRE_NOT_NULL(dest);

	*dest = AWS_SERVICE_NAMESPACES[service];

	return HAWSER_OK;
}
