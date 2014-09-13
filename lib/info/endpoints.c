#include "hawser/hawser.h"
#include "hawser/info.h"

#include "../hawser_internal.h"

/**
 * AWS endpoints for each service and region.
 */
/*static const char *AWS_ENDPOINTS[AWS_SERVICE_COUNT][AWS_REGION_COUNT] = {
	{
		"ec2.us-east-1.amazonaws.com",
		"ec2.us-west-2.amazonaws.com",
		"ec2.us-west-1.amazonaws.com",
		"ec2.eu-west-1.amazonaws.com",
		"ec2.ap-southeast-1.amazonaws.com",
		"ec2.ap-southeast-2.amazonaws.com",
		"ec2.ap-northeast-1.amazonaws.com",
		"ec2.sa-east-1.amazonaws.com"
	},
	{
		"s3.amazonaws.com",
		"s3-us-west-2.amazonaws.com",
		"s3-us-west-1.amazonaws.com",
		"s3-eu-west-1.amazonaws.com",
		"s3-ap-southeast-1.amazonaws.com",
		"s3-ap-southeast-2.amazonaws.com",
		"s3-ap-northeast-1.amazonaws.com",
		"s3-sa-east-1.amazonaws.com"
	}
};*/


HAWSERresult
aws_endpoint(
	AWS_SERVICE service,
	AWS_REGION region,
	const char **dest
)
{
	return HAWSER_INVALID;
}
