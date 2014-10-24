#!/bin/bash

cd debug-build
G_SLICE=always-malloc G_DEBUG=gc-friendly valgrind --tool=memcheck --leak-check=full --suppressions=../suppressions.txt  --gen-suppressions=no ./facturation
cd ..
