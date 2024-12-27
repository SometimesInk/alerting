#!/bin/bash

battery_progress=$(acpi -b | grep -oP '\d+(?=%)')

color_at_moment=$(./precompiled_values.sh battery_progress)
