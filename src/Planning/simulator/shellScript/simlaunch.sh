#!/bin/sh
terminator -e " roslaunch final_autonomous_driving manual_driving.launch " &
sleep 3
terminator -e " roslaunch final_simulator simulation.launch "
