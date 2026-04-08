#!/bin/bash

curl -X POST "http://localhost:3333/api/exhibitions/new" \
  -H 'Content-Type:application/json' \
  -d '{ "Title": "Test", "Description": "Test", "Image": "fem.jpg", "Color": "blue", "IsOpen": false }';
