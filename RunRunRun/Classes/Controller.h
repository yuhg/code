#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "cocos2d.h"
#include "ControllerListener.h"

using namespace cocos2d;

class Controller : public CCLayer {
public:
    /* ���ü������� */
    void setControllerListener(ControllerListener* mControllerListener);

protected:
    ControllerListener* mControllerListener;
};

#endif