#include "hawser/hawser.h"
#include "hawser/info.h"

#include "../hawser_internal.h"


/**
 * AWS endpoints for each service and region.
 */
static const char *AWS_ENDPOINTS[AWS_SERVICE_COUNT][AWS_REGION_COUNT] = {
	{  /* Amazon EC2 */
		"ec2.us-east-2.amazonaws.com",
		"ec2.us-east-1.amazonaws.com",
		"ec2.us-west-1.amazonaws.com",
		"ec2.us-west-2.amazonaws.com",
		"ec2.ca-central-1.amazonaws.com",
		"ec2.ap-south-1.amazonaws.com",
		"ec2.ap-northeast-2.amazonaws.com",
		"ec2.ap-southeast-1.amazonaws.com",
		"ec2.ap-southeast-2.amazonaws.com",
		"ec2.ap-northeast-1.amazonaws.com",
		"ec2.eu-central-1.amazonaws.com",
		"ec2.eu-west-1.amazonaws.com",
		"ec2.eu-west-2.amazonaws.com",
		"ec2.sa-east-1.amazonaws.com"
	},
	{  /* AWS Lambda */
		"lambda.us-east-2.amazonaws.com",
		"lambda.us-east-1.amazonaws.com",
		"lambda.us-west-1.amazonaws.com",
		"lambda.us-west-2.amazonaws.com",
		"",
		"lambda.ap-south-1.amazonaws.com",
		"lambda.ap-northeast-2.amazonaws.com",
		"lambda.ap-southeast-1.amazonaws.com",
		"lambda.ap-southeast-2.amazonaws.com",
		"lambda.ap-northeast-1.amazonaws.com",
		"lambda.eu-central-1.amazonaws.com",
		"lambda.eu-west-1.amazonaws.com",
		"lambda.eu-west-2.amazonaws.com",
		""
	},
	{  /* Amazon SNS */
		"sns.us-east-2.amazonaws.com",
		"sns.us-east-1.amazonaws.com",
		"sns.us-west-1.amazonaws.com",
		"sns.us-west-2.amazonaws.com",
		"sns.ca-central-1.amazonaws.com",
		"sns.ap-south-1.amazonaws.com",
		"sns.ap-northeast-2.amazonaws.com",
		"sns.ap-southeast-1.amazonaws.com",
		"sns.ap-southeast-2.amazonaws.com",
		"sns.ap-northeast-1.amazonaws.com",
		"sns.eu-central-1.amazonaws.com",
		"sns.eu-west-1.amazonaws.com",
		"sns.eu-west-2.amazonaws.com",
		"sns.sa-east-1.amazonaws.com"
	},
	{  /* Amazon SQS */
		"sqs.us-east-2.amazonaws.com",
		"sqs.us-east-1.amazonaws.com",
		"sqs.us-west-1.amazonaws.com",
		"sqs.us-west-2.amazonaws.com",
		"sqs.ca-central-1.amazonaws.com",
		"sqs.ap-south-1.amazonaws.com",
		"sqs.ap-northeast-2.amazonaws.com",
		"sqs.ap-southeast-1.amazonaws.com",
		"sqs.ap-southeast-2.amazonaws.com",
		"sqs.ap-northeast-1.amazonaws.com",
		"sqs.eu-central-1.amazonaws.com",
		"sqs.eu-west-1.amazonaws.com",
		"sqs.eu-west-2.amazonaws.com",
		"sqs.sa-east-1.amazonaws.com"
	},
	{  /* Amazon S3 */
		"s3.dualstack.us-east-2.amazonaws.com",
		"s3.dualstack.us-east-1.amazonaws.com",
		"s3.dualstack.us-west-1.amazonaws.com",
		"s3.dualstack.us-west-2.amazonaws.com",
		"s3.dualstack.ca-central-1.amazonaws.com",
		"s3.dualstack.ap-south-1.amazonaws.com",
		"s3.dualstack.ap-northeast-2.amazonaws.com",
		"s3.dualstack.ap-southeast-1.amazonaws.com",
		"s3.dualstack.ap-southeast-2.amazonaws.com",
		"s3.dualstack.ap-northeast-1.amazonaws.com",
		"s3.dualstack.eu-central-1.amazonaws.com",
		"s3.dualstack.eu-west-1.amazonaws.com",
		"s3.dualstack.eu-west-2.amazonaws.com",
		"s3.dualstack.sa-east-1.amazonaws.com"
	}
};


HAWSERresult
aws_endpoint(
	AWS_SERVICE service,
	AWS_REGION region,
	const char **dest
)
{
	REQUIRE_RANGE(service, AWS_SERVICE_MIN, AWS_SERVICE_MAX);
	REQUIRE_RANGE(region,  AWS_REGION_MIN,  AWS_REGION_MAX);
	REQUIRE_NOT_NULL(dest);

	if (*AWS_ENDPOINTS[service][region] == '\0') {
		/* Endpoint string has length 0 */
		return HAWSER_BAD_REGION;
	}

	*dest = AWS_ENDPOINTS[service][region];

	return HAWSER_OK;
}
