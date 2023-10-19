#!/bin/bash
clang++ -std=c++14 -stdlib=libc++ -o main main.cc -lgtest -lgtest_main -pthread
