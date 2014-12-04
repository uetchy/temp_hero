#!/bin/sh

./configure --with-readline=`brew --prefix readline` && make && ./src/main
