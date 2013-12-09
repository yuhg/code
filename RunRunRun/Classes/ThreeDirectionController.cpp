#include "ThreeDirectionController.h"

bool ThreeDirectionController::init()
{
    this->iXSpeed = 0;
    this->iYSpeed = 0;

    /* �����������¼� */
    this->setTouchEnabled(true);

    this->scheduleUpdate();
    return true;
}

void ThreeDirectionController::update( float dt )
{
    if(mControllerListener == NULL) {
        return;
    }

    CCPoint curPos = mControllerListener->getCurPosition();
    curPos.x += iXSpeed;
    curPos.y += iYSpeed;

    mControllerListener->setSimplePosition(curPos.x + iXSpeed, curPos.y + iYSpeed);
}

void ThreeDirectionController::setiXSpeed( int iSpeed )
{
    this->iXSpeed = iSpeed;
}

void ThreeDirectionController::setiYSpeed( int iSpeed )
{
    this->iYSpeed = iSpeed;
}

bool ThreeDirectionController::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
    return true;
}

void ThreeDirectionController::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    /* ��ȡ��������� */
    CCPoint touchLocation = pTouch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

    /* �����ƶ�������� */
    CCPoint pos = mControllerListener->getCurPosition();

    /* �ж��������ƶ����������ƶ� */
    int iSpeed = 0;
    if(touchLocation.y > pos.y) {
        iSpeed = 1;
    }
    else {
        iSpeed = -1;
    }

    setiYSpeed(iSpeed);
}

void ThreeDirectionController::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
    /* ֹͣY���귽����ƶ� */
    setiYSpeed(0);
}

void ThreeDirectionController::registerWithTouchDispatcher()
{
    /* ע�ᴥ���¼� */
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}