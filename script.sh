#!/bin/bash

hyprctl notify -1 10000 "rgb(ff1ea3)" "Hello everyone!"

cat >/home/ink/.config/hypr/alerting.conf <<FILE
general {
  col.active_border=$(eval /home/ink/Documents/GitHub/alerting/precompiler/precompiled_values.sh "$1")
}
FILE
