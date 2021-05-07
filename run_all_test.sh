#!/bin/bash

for file in ` ls inputs `
do
  bin/qmsdd inputs/${file}
  echo
  # sleep 1
done
