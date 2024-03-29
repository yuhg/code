#include "SimpleMoveControll.h"

bool SimpleMoveControll::init()
{
    this->iSpeed = 0;

    /* 设置每一帧都要调用update函数 */
    this->scheduleUpdate();

    return true;
}

void SimpleMoveControll::update( float dt )
{
    if(mControllerListener == NULL) {
        return;
    }
    CCPoint pos = mControllerListener->getCurPosition();
    pos.x += iSpeed;
    mControllerListener->setSimplePosition(pos.x, pos.y);
}

void SimpleMoveControll::setiSpeed( int iSpeed )
{
    this->iSpeed = iSpeed;
}
