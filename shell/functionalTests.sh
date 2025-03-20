#!/bin/bash
./shell/clrRepo.sh
./shell/cmpRelease.sh
python3 ./tests/functional/Tester.py
