import os

# 启动建图模块

os.system("sh ~/catkin_ws/src/team_108/bash/mapping.sh")
# 让机器人移动进行建图
str = "0"
while (str != "1"):
    str = input("输入1让机器人前进进行建图")
    if str == "1":
        os.system('sh ~/catkin_ws/src/team_108/bash/mapping_go.sh')
    else:
        str = input("输入1让机器人前进进行建图")
# 保存地图
str = "0"
while (str != "1"):
    str = input("输入1让机器人保存地图")
    if str == "1":
        os.system('sh ~/catkin_ws/src/team_108/bash/save_map.sh')
    else:
        str = input("输入1让机器人前进进行建图")
# 到达桌子添加导航点
str = "0"
while (str != "1"):
    str = input("输入1添加导航点，输入2向前移动，输入3右转")
    if str == "1":
        os.system('sh ~/catkin_ws/src/team_108/bash/save_map.sh')
    else:
        if (str == "2"):
            os.system('sh ~/catkin_ws/src/team_108/bash/go_forward.sh')
        else:
            os.system('sh ~/catkin_ws/src/team_108/bash/turn_right.sh')
