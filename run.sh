#!/usr/bin/env bash

set -e

bash build.sh > /dev/null 2>&1
node build/SIEVE.js
