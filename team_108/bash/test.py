import os

os.system("roslaunch wpb_home_tutorials hector_mapping.launch")

os.system("roslaunch wpb_home_bringup minimal.launch")

os.system("rosrun team_108 map_go")
