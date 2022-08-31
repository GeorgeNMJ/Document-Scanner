#!/bin/bash


cmake -S . -B out/build/
cmake --build out/build/ && ./out/build/main
