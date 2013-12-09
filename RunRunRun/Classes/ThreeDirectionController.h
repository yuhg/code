#ifndef __THREE_DIRECTION_CONTROLLER_H__
#define __THREE_DIRECTION_CONTROLLER_H__

#include "Controller.h"
#include "cocos2d.h"

using namespace cocos2d;

class ThreeDirectionController : public Controller {
public:
    CREATE_FUNC(ThreeDirectionController);
    virtual bool init();
    virtual void update(float dt);

    /* �����¼� */
    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);

    /* ����X�����ƶ��ٶ� */
    void setiXSpeed(int iSpeed);

    /* ����Y�����ƶ��ٶ� */
    void setiYSpeed(int iSpeed);

private:
    int iXSpeed;
    int iYSpeed;
};

#endif