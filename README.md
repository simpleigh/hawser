# hawser

[![Build Status](https://travis-ci.org/simpleigh/hawser.svg?branch=master)](https://travis-ci.org/simpleigh/hawser)
![Licence](http://img.shields.io/badge/licence-GPLv3-red.svg)

NOTE: hawser is still incomplete and non-functional!

## What is it?

A simple tool to perform tiny sysadmin tasks using Amazon Web Services.

Will support:

* retrieving tags from EC2
* uploading files to S3 buckets
* downloading files from S3 buckets

### Why not use an existing tool or library?

* Most libraries are huge and try to support all AWS' services.
* Many libraries depend on a third-party installer, e.g. pip or composer.
* I don't want to clutter up production servers (security), or SCM (annoying).
* In order to keep my AWS account secure,
I want to know the minimal IAM permissions required for a particular job,
and use temporary access credentials where possible.

### Other tools

* [s3cmd](http://s3tools.org/usage) is a powerful tool for S3 and CloudFront.
    * Doesn't document required IAM permissions (as far as I can tell).
    * Doesn't appear to support temporary access credentials.
    * I still need something to access EC2 tags.

* [AWS CLI](http://aws.amazon.com/cli/) is Amazon's CLI tool.
    * Requires `pip` for installation.
    I don't run a Python stack so don't really need this,
    and it makes it harder to configure machines with tools like Chef or Puppet.

## Installation

### Requirements

Make sure you have the following tools:

* A C compiler

* The GNU build system:
    * `make`
    * `autoconf`
    * `automake`
    * `autoreconf`

* Required libraries (including headers):
    * [libcurl](http://curl.haxx.se/libcurl/) 
    * [OpenSSL](http://www.openssl.org/)

### Compiling

Run the following:

    ./autogen.sh
    ./configure
    make
