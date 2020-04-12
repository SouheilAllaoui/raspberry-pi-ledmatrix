#!/bin/bash

gcc -fPIC -shared -o pin_management.so pin_management.c -l bcm2835