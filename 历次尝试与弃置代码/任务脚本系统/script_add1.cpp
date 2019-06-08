#include "8_innovation_script.h"
CInnovationScript::CInnovationScript()
{
    
}

CInnovationScript::~CInnovationScript()
{

}

void CInnovationScript::Queue_goto_detect()
{
    stAct newAct;
/*
    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "1";
    arAct.push_back(newAct);

    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "master_location";
    arAct.push_back(newAct);
*/

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "master";
    arAct.push_back(newAct);
/*
    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "导航点";
    newAct.nDuration = 3;
    arAct.push_back(newAct);
/*
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "到";
    newAct.nDuration = 4;
    arAct.push_back(newAct);
*/
/*
    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "user_set_1";
    arAct.push_back(newAct);

    

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "导航点已添加";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

*/
    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "开始抓取";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GRAB;
    newAct.strTarget = "";
    newAct.nDuration = 5;
    arAct.push_back(newAct);
/*
    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "返回";
    newAct.nDuration = 3;
    arAct.push_back(newAct);
*/
/*
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "抓取完成";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

    
    newAct.nAct = ACT_LISTEN;
    newAct.strTarget = "返回";
    newAct.nDuration = 5;
    arAct.push_back(newAct);

*/
    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "master";
    arAct.push_back(newAct);
/*
    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "你他娘的真是个天才";
    newAct.nDuration = 4;
    arAct.push_back(newAct);
*/

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "已返回起点";
    newAct.nDuration = 4;
    arAct.push_back(newAct);

    newAct.nAct = ACT_PASS;
    arAct.push_back(newAct);


/*
    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "master_location";
    arAct.push_back(newAct);


    newAct.nAct = ACT_SHOW_IMAGE;
    newAct.strTarget = "~/image.jpg";
    arAct.push_back(newAct);


    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "1";
    arAct.push_back(newAct);


    newAct.nAct = ACT_SHOW_IMAGE;
    newAct.strTarget = "~/image.jpg";
    arAct.push_back(newAct);


    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "master_location";
    arAct.push_back(newAct);*/
}