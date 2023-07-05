#!/bin/bash

USER=${1:-"ubuntu"}
HOST=${2:-118.229.43.254}

TARGET_PATH="/path/to/target/directory"

rsync -avz -e "ssh -p $SERVER_PORT" $LOCAL_PATH $SERVER_USER@$SERVER_IP:$REMOTE_PATH
