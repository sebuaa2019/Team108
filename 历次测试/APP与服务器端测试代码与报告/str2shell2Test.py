import socket
import threading
import os
import time
import subprocess

def str2shell2(str):
    global p_move, p_map , p_grab, p_navi
    if str == 'map_start':
        os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_bringup minimal.launch; exec bash\"'")
        time.sleep(2)
        os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_tutorials hector_mapping.launch; exec bash\"'")

    if str == 'map_finish':
        p_temp = subprocess.Popen('rosrun map_server map_saver -f map',shell=True)
        p_temp.wait()
        p_temp = subprocess.Popen('cp ~/map.pgm ~/catkin_ws/src/team_108/maps/', shell=True)
        p_temp.wait()
        p_temp = subprocess.Popen('cp ~/map.yaml ~/catkin_ws/src/team_108/maps/', shell=True)
        p_temp.wait()
        p_temp = subprocess.Popen('cp ~/map.pgm ~/catkin_ws/src/wpb_home/wpb_home_tutorials/maps/', shell=True)
        p_temp.wait()
        p_temp = subprocess.Popen('cp ~/map.yaml ~/catkin_ws/src/wpb_home/wpb_home_tutorials/maps/', shell=True)
        p_temp.wait()
        p_temp = subprocess.Popen('rm ~/waypoints.xml', shell=True)
        p_temp.wait()
        p_temp = subprocess.Popen('rosnode kill rviz', shell=True)
        p_temp.wait()

    if str == 'move_forward':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 go_forward',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 go_forward',shell=True)

    if str == 'move_backward':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 go_backward',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 go_backward',shell=True)

    if str == 'move_left':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 go_left',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 go_left',shell=True)

    if str == 'move_right':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 go_right',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 go_right',shell=True)

    if str == 'rotateleft':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 turn_left',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 turn_left',shell=True)

    if str == 'rotateright':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 turn_right',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 turn_right',shell=True)

    if str == 'stop':
        if p_move is None:
            p_move = subprocess.Popen('rosrun team_108 go_stop',shell=True)
        else:
            if p_move.poll() is None:
                p_move.kill()
            p_move = subprocess.Popen('rosrun team_108 go_stop',shell=True)

    if 'grab' in str:
        p_temp = subprocess.Popen('rosnode kill rviz', shell=True)
        p_temp.wait()
        os.system("gnome-terminal -e 'bash -c \"roslaunch team_108 script_add1.launch\"'")

    if 'navigation' in str:
        p_temp = subprocess.Popen('rosnode kill rviz', shell=True)
        p_temp.wait()
        os.system("gnome-terminal -e 'bash -c \"roslaunch team_108 script_add2.launch\"'")

    if 'follow' in str:
        p_temp = subprocess.Popen('rosnode kill rviz', shell=True)
        p_temp.wait()
        os.system("gnome-terminal -e 'bash -c \"roslaunch wpb_home_apps shopping.launch\"'")







p_move = None
p_map = None
p_grab = None
p_navi = None
while(true):
    str = input('请输入测试的命令')
    if str == 'quit' :
        break; 
    str2shell2(str)
