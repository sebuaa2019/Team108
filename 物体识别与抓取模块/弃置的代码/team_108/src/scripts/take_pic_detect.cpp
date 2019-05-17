#include "8_innovation_script.h"
CInnovationScript::CInnovationScript()
{
    
}

CInnovationScript::~CInnovationScript()
{

}

void CInnovationScript::Queue()
{
    stAct newAct;

    newAct.nAct = ACT_CAP_IMAGE;
    newAct.strTarget = "/home/robot/team_108/raw_image.jpg";
    arAct.push_back(newAct);

    newAct.nAct = ACT_SHOW_IMAGE;
    newAct.strTarget = "/home/robot/team_108/raw_image.jpg";
    arAct.push_back(newAct);
}