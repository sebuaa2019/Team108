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
    newAct.strTarget = "2";
    arAct.push_back(newAct);

}