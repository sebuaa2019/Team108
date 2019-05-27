rosrun map_server map_saver -f map
cp ~/map.pgm  /wpb_home_tutorials/maps/
cp ~/map.yaml /wpb_home_tutorials/maps/

roslaunch waterplus_map_tools add_waypoint.launch