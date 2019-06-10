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

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "user_set_2";
    arAct.push_back(newAct);
/*
    newAct.nAct = ACT_MOVE;
    newAct.fLinear_x = 0;
    newAct.fLinear_y = 0;
    newAct.fAngular_z = 0;
    arAct.push_back(newAct);

    newAct.nAct = ACT_GOTO;
    newAct.strTarget = "master_location";
    arAct.push_back(newAct);
*/
/*    
    newAct.nAct = ACT_ADD_WAYPOINT;
    newAct.strTarget = "user_set_2";
    arAct.push_back(newAct);
*/

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