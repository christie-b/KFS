#!/bin/bash

docker build -t kfs .
docker run -d --rm --name kfs kfs