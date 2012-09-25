#!/bin/sh
(LD_PRELOAD="./nightwatchman.so" ./unprotected_heap.bin)
