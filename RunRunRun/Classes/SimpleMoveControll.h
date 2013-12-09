#ifndef __SIMPLE_MOVE_CONTROLL_H__
#define __SIMPLE_MOVE_CONTROLL_H__

#include "cocos2d.h"
#include "Controller.h"

using namespace cocos2d;


class SimpleMoveControll : public Controller {
public:
    CREATE_FUNC(SimpleMoveControll);
    virtual bool init();
    virtual void update(float dt);

    /* �����ƶ��ٶ� */
    void setiSpeed(int iSpeed);

    
private:
    int iSpeed;
};

#endif