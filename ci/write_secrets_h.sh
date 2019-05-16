#!/bin/bash

SECRETS_H="${TRAVIS_BUILD_DIR}/secrets.h"
cp "${SECRETS_H}.example" "${SECRETS_H}"

sed -i -- "s/IMGUR_CLIENT_ID .*/IMGUR_CLIENT_ID \"${IMGUR_CLIENT_ID}\"/g" "${SECRETS_H}"
sed -i -- "s/IMGUR_CLIENT_SECRET .*/IMGUR_CLIENT_SECRET \"${IMGUR_CLIENT_SECRET}\"/g" "${SECRETS_H}"
sed -i -- "s/PASSWORD_RAW_KEY .*/PASSWORD_RAW_KEY \"${PASSWORD_RAW_KEY}\"/g" "${SECRETS_H}"
