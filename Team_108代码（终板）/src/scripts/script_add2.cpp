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
    newAct.strTarget = "master";
    arAct.push_back(newAct);


	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "请设置导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_ADD_WAYPOINT;
	newAct.strTarget = "user_set_1";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "导航点已设置";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_ADD_WAYPOINT;
	newAct.strTarget = "user_set_2";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "导航点已设置";
	newAct.nDuration = 5;
	arAct.push_back(newAct);


	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "返回";
	newAct.nDuration = 10;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "master";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "已到达起点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);
/*
	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);
*/
	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "user_set_1";
	arAct.push_back(newAct);	

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "到达位置一";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "user_set_2";
	arAct.push_back(newAct);	

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "到达位置二";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "master";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "已到达起点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);
/*
	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_ADD_WAYPOINT;
	newAct.strTarget = "user_set_2";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_ADD_WAYPOINT;
	newAct.strTarget = "user_set_3";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "返回";
	newAct.nDuration = 10;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "master";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "已返回原点请指示";
	newAct.nDuration = 8;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "user_set_1";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "到达航点一";
	newAct.nDuration = 5;
	arAct.push_back(newAct);


	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "user_set_2";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "到达航点二";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "导航点";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "user_set_3";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "到达航点三";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_LISTEN;
	newAct.strTarget = "返回";
	newAct.nDuration = 5;
	arAct.push_back(newAct);

	newAct.nAct = ACT_GOTO;
	newAct.strTarget = "master";
	arAct.push_back(newAct);

	newAct.nAct = ACT_SPEAK;
	newAct.strTarget = "已返回原点导航结束";
	newAct.nDuration = 8;
	arAct.push_back(newAct);
*/
}
