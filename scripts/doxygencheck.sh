#!/bin/bash -e
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color
LIMIT=21000
WARNINGS=$( IMAGE_DIR=./images/doxygen  GIT_HASH=#notset SEM_VERSION="not set"  doxygen |&  grep "warning" | wc -l)

if [ "$1" == "1" ]; then
    IMAGE_DIR=./images/doxygen doxygen |&  grep "warning"
    exit 0
fi

echo -e "Doxygen warnings: ${GREEN}$WARNINGS${NC}"
if [ "$WARNINGS" -gt "$LIMIT" ]; then
    echo -e "Doxygen warnings exceed ${RED}$LIMIT${NC}, failing build."
    exit $WARNINGS
fi
