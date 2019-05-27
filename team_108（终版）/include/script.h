#ifndef INNO_SCRIPT_H
#define INNO_SCRIPT_H
#include "action_manager.h"

class CInnovationScript : public CActionManager
{
public:
	CInnovationScript();
	~CInnovationScript();
    //void Queue();
    void Queue_goto_detect();
    void Queue_take_pic_detect();
};

#endif // INNO_SCRIPT_H