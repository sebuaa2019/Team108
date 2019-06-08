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

    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "master_location";
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "1";
    arAct.push_back(newAct);

    newAct.nAct = ACT_SPEAK;
    newAct.strTarget = "开始抓取饮料";
    newAct.nDuration = 5;
    arAct.push_back(newAct);
}

void CInnovationScript::Queue_take_pic_detect()
{
    
}