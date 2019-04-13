#!/bin/bash
if [ ! -d obj ]; then
  mkdir obj
fi
cd obj
g++ ../src/*.cpp -c -g
cd ..
if [ ! -d bin ]; then
  mkdir bin
fi
g++ obj/*.o -o bin/soccer
