#!/bin/bash
rosrun map_server map_server -f map
cp ~/map.pgm ~/catkin_ws/src/team_108/maps/
cp ~/map.yaml ~/catkin_ws/src/team_108/maps/
