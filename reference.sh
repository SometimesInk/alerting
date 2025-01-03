#!/bin/bash

eval /home/ink/Documents/GitHub/alerting/script.sh "$(acpi -b | grep -oP '\d+(?=%)')"
