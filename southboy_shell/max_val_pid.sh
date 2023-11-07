#!/bin/bash
pid_max=$(cat /proc/sys/kernel/pid_max)

echo "maximum process ID value: $pid_max"
