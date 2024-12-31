#!/bin/bash

battery_progress=
cat >/home/ink/.config/hypr/alerting.conf <<FILE
general {
  col.active_border=$(./precompiled_values.sh $(acpi -b | grep -oP '\d+(?=%)'))
}
FILE
