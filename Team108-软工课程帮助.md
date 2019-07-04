软工Team108总结
=================
作为软工课程机器人项目第一届的学生，在实践的过程中算是走了不少弯路。所以经过讨论我们小组准备做一个课程相关的技术与管理方面的总结。如果这个项目下一届还开的话，希望能帮到大家（虽然感觉那个机器人情况已经十分让人担忧了）。写这篇文章的目的在于让大家减少在基础部分的时间消耗，直接进入创新部分。这样的话在减轻大家整体负担的同时，也能提升项目质量。特别说明的是我们选择的是吴老师，尚老师和姚老师的课程。使用的机器人为启智机器人。本文将主要从管理和技术两个大方面来谈。

# 管理层面
首先要说的是软工这门课程不光是看最后的结果，对整个过程的管理也是十分看重。在这个课程的过程中老师会教授很多的管理方面的知识，然后大部分时候你会听的云里雾里，不知道如何运用（对，说的就是我这个不够优秀的组长）。等到真正做项目的时候，在几次迭代审查的时候就会发现问题所在。在这里说一下我们组出现的问题，供大家参考和改正。

## 看板系统的建立
使用Github管理并不只是把代码传上去，然后更新代码这些工作。老师会要求建立详细的看板系统。其实所谓看板系统就是把Github中大家提出的issue按照不同的分类（即不同的功能分类）分开。

到Github的project项目中就可以新建看板项目。但是！这只是第一步啊，还要有每个代表每个问题是什么阶段的标签。这个标签我们是这样加的，在问题中有label一栏，在那里可以新建label然后起上不同阶段的名字。但是我觉得这不是一种很科学的添加标签的方法，因为这毕竟会侵占一个label的位置。所以还请大家做个参考好了。
## 文件版本管理
一定要做好文件版本管理啊，因为不知道什么时候全组代码会被莫名删掉（对就是会有这种情况发生），那时候如果没有一个最新版本的代码管理的话会很麻烦的。代码管理也没有什么特别优异的管理经验吧，就是按每个版本的先后顺序标记好保存起来就可以了。
# 技术层面
技术层面我感觉需要主要分为三方面来谈：ROS本身的配置；物体抓取方面的理解和安卓应用控制机器人。下面来分别介绍
## ROS配置部分
ROS文件系统中的最基本的概念：Package，是组织ROS代码的最基本单位，每一个Package都可以包括库文件，可执行文件，脚本及其它的一些文件。我们的代码也要放在一个package

catkin 编译构建系统的功能包 ——编译产生的可执行文件并未存放在功能包目录下，而是存放在一个单独的标准化目录层次结构中。对于使用 apt-get 安装的功能包，其所在根目录为/opt/ros/indigo。可执行文件存储在这个根目录下的 lib 子目录里。同样，在自动生成的头文件存储在 include 子目录下。当有需要时，ROS通过搜索 CMAKE_PREFIX_PATH 环境变量列出的目录，这个环境变量由 setup.bash 自动设置。

而catkin_make命令是由cmakeLists.list这个文件来指挥的。所以每当我们向机器人中加入一个功能，就要在这里进行注册。

```cmake
add_executable(turn_right
  src/turn_right.cpp
)
add_dependencies(turn_right ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(turn_right
  ${catkin_LIBRARIES}
)

///////////////////////////////////////////////////////////////
add_executable(script_add1
  src/script_exc.cpp
  src/action_manager/action_manager.cpp
  src/scripts/script_add1.cpp
)
add_dependencies(script_add1 ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
target_link_libraries(script_add1
  ${catkin_LIBRARIES}
)
```

 cmake文件基本的配置如上，我们要将我们向运行的可运行文件放在add_executable中，紧接着第一个参数是节点的名字，即我们在调用这个节点时写的名字。第二个参数是这个节点源文件所在的位置。后面add_dependencies中的参数是一些这个节点的依赖项。

在后面的例子中我们也展示了如何将多个源文件组合成为一个节点。这些节点之间是可以共用一些文件的。

### 节点管理器（The Master）

ROS 的一个基本目标是使机器人的很多节点**node**（可执行文件，几乎相对独立的小程序）能够同时运行。为此，这些节点必须能够彼此通信。ROS 中实现通信的关键部分就是ROS 节点管理器。要启动节点管理器，使用如下命令：roscore  。节点管理器应该在使用 ROS 的全部时间内持续运行。一个合理的工作流程是在一个终端启动roscore，然后打开其他终端运行其他程序。当结束时可以通过在 roscore 终端键入Ctrl-C 停止节点管理器。如果roscore 被终止，当前运行的其他节点将无法建立新的连接，即使 稍后重启 roscore 也无济于事。

roslaunch 是个启动文件，其目的是一次性启动多个节点。每一个启动文件都应该和一个特定的功能包关联起来。通常的命名方案是以.launch 作为启动文件的后缀。这是一个自适应工具，如果启动多节点时没有节点管理器运行，它会自动启动节点管理器；如果已经有一个节点 管理器在运行，则会使用已有的。rosrun 一次只能启动 一个节点，而 roslaunch 可以同时启动多个节点。一般launch文件会放在功能包的根目录中。

以后会专门讲一下roslaunch  <http://www.cnblogs.com/zjiaxing/p/5542614.html>

### 节点（Nodes）

一旦启动roscore后，便可以运行ROS程序了。 ROS程序的运行实例被称为节点（node） ,例如 rosrun turtlesim turtlesim_node  这个节点是可执行文件 turtlesim_node 的实例化，负责创建 turtlesim窗口和模拟海龟的运动。可以看出rosrun 命令有两个参数，其中第一个参数是功能包的名称，第二个参数是该软件包中的可执行文件的名称。还要注意的是通过节点管理器注册成为 ROS 节点发生在程序的内部，而不是通过 rosrun 命令。

启动roscore后运行rosnode list 可以看到出现节点/ rosout  。rosout 节点是一个特殊的节点，通过 roscore 自动启动。其作用有点类似于控制台程序中使用的标准输出（即 std：：cout）。

/rosout也是话题，所有的节点发布都向话题/rosout 发布消息，该话题由同名的 /rosout 节点订阅。这个话题的作用是用来生成各个节点的文本日志消息。在某些地方/rosout 既指节点又指话题。但 ROS 并不会这种重复的名字而混淆，因为 ROS 会根据上下文来推测我们讨论的是/rosout节点,还是/rosout话题。

举个例子来说明也许会更好,这个例子将在话题和消息里说明。

读者还要注意的是rosrun 命令中可执行文件的名称与节点名称并不一定相同。节点名称是在代码中命名的例如ros::init (argc, argv, "odom");而可执行文件名称是在CMakeLists.txt中命名的。但可以使用 rosrun 命令显式设置节点的名称，语法如下：rosrun package-name executable-name _ _name:=node-name 这种方法将使用 node-name 参数给出的名称覆盖节点的默认名。因为 ROS 中要求每个节点有不同的名称，因此该方法很重要尤其是移植程序中。

### 话题和消息

ROS节点之间进行通信所利用的最重要的机制就是消息传递。在ROS中，消息有组织地存放在话题里。消息传递的理念是：当一个节点想要分享信息时，它就会发布(publish)消息到对应的一个或者多个话题；当一个节点想要接收信息时，它就会订阅(subscribe)它所需要的一个或者多个话题。ROS节点管理器负责确保发布节点和订阅节点能找到对方；而且消息是直接地从发布节点传递到订阅节点，中间并不经过节点管理器转交。

查看节点构成的计算图：先介绍个工具rqt_graph，要查看节点之间的连接关系，恐怕将其表示为图形是最便于查看的。在ROS 系统中查看节点之间的发布-订阅关系的最简单方式就是在终端输入如下令：rqt_graph。r 代表ROS，qt 指的是用来实现这个可视化程序的Qt 图形界面（GUI）工具包。

## 物体抓取部分的理解

抓取部分的代码十分复杂，如果想要自己实现的话还是要费一些事情的，当然我也希望能有小组自己实现出来自己的抓取代码。但是如果想要做出最好的抓取效果就要对原本的抓取代码进行修改。下面就对原有的抓取代码进行解析。

抓取部分的代码主要分为几个部分，其中点云类型转换和在rviz中画出各种图形的部分读者自己看一看就可以了，在整个功能实现的过程中用处不大。主要来讲解抓取步骤的部分。
抓取步骤的进行是由一个命名为nStep的变量控制的，根据其不同的取值来确定下面该进行哪一步。例如

```
if(nStep == STEP_FIND_PLANE)  //(点云处理算法在上面)
    {
        mani_ctrl_msg.position[0] = 0;
        mani_ctrl_msg.position[1] = 0.16;
        mani_ctrl_pub.publish(mani_ctrl_msg);
        VelCmd(0,0,0);
        ctrl_msg.data = "pose_diff reset";
        ctrl_pub.publish(ctrl_msg);
        if(fabs(fPlaneHeight - fLastPlaneHeight) < 0.05)
        {
            nPlaneHeightCounter ++;
        }
        else
        {
            nPlaneHeightCounter = 0;
        }
        fLastPlaneHeight = fPlaneHeight;
        ROS_WARN("[FIND_PLANE] z= %.2f xm= %.2f y=(%.2f , %.2f) counter= %d" ,fPlaneHeight,boxPlane.xMin,boxPlane.yMin,boxPlane.yMax,nPlaneHeightCounter);
        if(nPlaneHeightCounter > 10)
        {
            nPlaneHeightCounter = 0;
            nTimeDelayCounter = 0;
            nStep = STEP_PLANE_DIST;
            fMoveTargetX = boxPlane.xMin - 0.7;
            fMoveTargetY = 0;
        }
        result_msg.data = "find plane";
        result_pub.publish(result_msg);
    }
```
标志着到达了寻找平面的步骤。

而具体的抓取参数则在这个部分控制。
```
if(nStep == STEP_FIND_OBJ)  //(点云处理算法在上面)
    {
        VelCmd(0,0,0);
        ctrl_msg.data = "pose_diff reset";
        ctrl_pub.publish(ctrl_msg);
        if(nObjDetectCounter > 3)
        {
            nObjDetectCounter = 0;
            // 目标物品的坐标
            fObjGrabX = boxLastObject.xMin;
            fObjGrabY = (boxLastObject.yMin+boxLastObject.yMax)/2;
            fObjGrabZ = boxLastObject.zMax;
            ROS_WARN("[OBJ_TO_GRAB] x = %.2f y= %.2f ,z= %.2f w= %.2f" ,fObjGrabX, fObjGrabY, fObjGrabZ,boxLastObject.yMin - boxLastObject.yMax);
            
```
分别控制物体抓取x，y，z方向的抓取。
注意这些部分一定要保证fabs小于的数值为小数，否则无法进入到下一个步骤。
```
 if(fabs(vx) < 0.01 && fabs(vy) < 0.01)
            {
                VelCmd(0,0,0);
                ctrl_msg.data = "pose_diff reset";
                ctrl_pub.publish(ctrl_msg);
                nStep = STEP_HAND_UP;
            }
```
## 安卓应用控制机器人
在这学期的软件工程课程中，我们实现了使用安卓手机无线控制机器人的功能，借此机会叙述一下用到的方法。

我们使用了socket来实现移动设备与机器人的无线通讯。机器人配备了一台机载电脑，搭载了linux系统，支持python、C++等多种编程语言。此外，机器人还搭载了一台无线路由器，可以当做无线网卡使用，具有连接无线网络的能力。我们将机载平台作为服务器端（Server），使用python编写相关代码；将安卓移动设备作为客户端（Client），使用Java编写相关代码。实际上，无论何种设备作为服务器或客户端都能够实现通讯的目的。

### 服务器端
服务器端运行在机器人的机载电脑上，使用Python编写相关代码。具体实现步骤如下：
1.import socket //导入socket库。

2.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) //创建一个socket（仅创建资源，还没有建立连接）；socket.AF_INET指使用IPv4协议，如果使用IPv6协议应该使用socket.AF_INET6；socket.SOCK_STREAM指使用面向流的TCP协议。

3.s.bind((ip, portnum)) //每一个TCP连接是由一对ip地址与端口号确定的，相信大家在计算机网络课程上也有所了解。使用bind绑定ip地址和端口号。需要注意的是，这里的ip是本机的ip地址，而且是我们需要用于通信的网卡的ip地址。比如一台电脑可能有无线网卡、有线网卡等多块网卡，有多个ip地址，这里一定要填需要用于通信的网卡地址。在windows下，可以在cmd中使用ipconfig -all命令查看所有网卡的ip地址；在linux下，可以在终端中使用ifconfig -a命令查看ip地址。在课程中，我们使用的是机载电脑无线网卡（无线路由器）的ip。端口号可以自由指定，但是不要使用小于1024的端口号，而且端口号小于65535，我们使用了9999作为端口号。

4.s.listen(1) //开始监听端口，参数代表可以连接的最大数量。据说linux系统中此参数无效，默认为最大值，有兴趣的同学可以深入研究一下。

5.sock, addr = s.accept() //接受客户端发起的连接请求，返回的sock, addr代表这个连接的socket以及客户端的ip地址。这里的sock需要在发送、接受数据时用到。至此，客户端与服务器端就建立了连接。

6.建立连接后，可以使用sock.recv(bufsize[,flag])来接收发来的数据并根据接受的数据做出一些操作，也可以使用sock.send(string[,flag])向客户端发送数据。具体的先后顺序由程序的需要确定。recv方法的参数为接受的数据的最大长度，flag字段一般不使用；send方法的参数为发送的字符串。需要注意的是，这两个方法均为阻塞式的，如果需要同时建立多条连接，那么需要在主线程中新建线程来执行这些操作。

7.sock.close() //传输完成后，使用close方法释放资源。
服务器端实现一个简单的socket通信的步骤介绍完毕，同时网上这方面的博客也非常之多，可以方便的查询到。

### 客户端
客户端运行在安卓移动设备上，使用Java语言编写。具体的实现步骤如下：
1.Socket socket = new Socket(); //新建一个socket，仅申请资源，还没有连接。

2.socket.connect( new InetSocketAddress( ip, port), timeout); //根据ip地址和端口号建立连接。需要注意的是，这里的ip地址和端口号都是服务器代码中指定的ip地址和端口号，比如我们使用了机器人机载平台无线网卡的ip地址和9999。timeout为一个整数，可以省略，表示经过timeout毫秒后，如果连接还没有建立，那么就报错。这个方法会抛出IOException，需要使用try catch包裹。

3.
```
BufferedReader reader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
```
//其中reader用于从socket中接收数据，writer用于通过socket发送数据。

4.writer.write(str); writer.flush(); //通过socket发送数据，flush用于清空缓冲区，将数据发送出去。

String response = reader.readLine()；//读取socket中的数据，这个方法在执行时会立刻对socket进行读取，也就是说可能在服务器端还没有发送数据时就进行了读取，导致读出空值。可以采用while循环和判断的方法，直到读出数据后再进行下一步操作。当采用while循环时，实际上就成为了阻塞式执行，所以需要根据具体情况，决定是否需要新建线程执行读取操作。

5.reader.close(); writer.close(); socket.close(); //传输信息完毕后，使用close方法释放相关的资源。

安卓客户端上使用socket通信的步骤大致如上所述。开启安卓手机的个人热点功能，将机载平台连接至安卓手机的热点网络，就能够实现二者的通信。其实只要位于同一局域网下，就能够进行socket通信。需要注意的是教学楼的BUAA-WIFI无线网可能设置了某种安全机制，导致同时连接至BUAA-WIFI时可能出现无法进行socket通信的问题。在实际的实现安卓APP的过程中还需要解决一些问题，同样也是非常重要的，也记录在此。

在编写安卓应用时，一个需要注意的关键点是UI线程与工作线程的分离。在使用socket通信时，很多操作都是阻塞式的，当UI进程被阻塞一段时间后，就会出现应用未响应而闪退。所以需要新建工作线程来处理socket通信的相关功能。这就涉及到工作线程与UI线程的信息传递问题。线程通信的方法有很多，我们使用了Handler来实现。子线程的结构可以总结为Looper.prepare();定义handler相关逻辑；Looper.loop()三部分。基本上可以理解为一个死循环，不断接收UI线程的信息，作出处理。但是Handler与Activity的生命周期不同步，因此非常容易出现内存泄漏的问题，在这里不推荐使用。由于开发时间较紧，我们还没有来得及作出改进，同学们可以使用runOnUiThread等更加方便、安全的方法。

socket连接的建立、信息的传递等过程可能出现各种各样的错误，而且我们还是通过无线传输的方式来进行通信，可靠性并不能说非常高，因此一定要编写完备的错误判断、处理机制。例如，让服务器端每收到一条消息后发送一条确认消息，当收到确认消息后，客户端才能够发送下一条消息。这就需要对APP上的按钮进行一些操作，比如发送消息后将按钮设定为无效，接收到消息后，按钮恢复有效，防止出现重复发送消息或者服务器接收的内容不可控的问题。同样，需要在发送失败后向用户做出提示。除了要实现功能之外，错误的避免、出错处理也是一个十分重要的部分，需要花费大量时间设计、测试。

---------------
这就是我们的课程总结了，希望对大家能有帮助。我们的所有代码与文档均保存在GitHub上，同学们可以参考。相信同学们有能力做出更加完善的产品，同学们加油！