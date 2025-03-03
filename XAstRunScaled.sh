#!/bin/bash
if [ $# = 0 ]; then
  system=$(hostname)
  if [ "$system" = "MobiusTorus" ]; then
    scale=4.5
  else
    if [ "$system" = "TinyTon" ]; then
      scale=1.75
    else
      scale=2
    fi
  fi
else
  scale=$1
fi
run_scaled --scale=$scale xterm -e "./XAstSetup;./XAsteroids"
