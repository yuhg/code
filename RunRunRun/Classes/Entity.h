#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "Controller.h"
#include "ControllerListener.h"

using namespace cocos2d;

class Entity : public CCNode, public ControllerListener {
public:
    void setSprite(CCSprite* mSprite);
    void setController(Controller* controller);

    /* ʵ��SimpleMoveListener�ӿڵķ��� */
    virtual void setSimplePosition(int x, int y);
    virtual CCPoint getCurPosition();
protected:
    CCSprite* mSprite;
    Controller* mController;
    CCTMXTiledMap* map;

    CCTMXLayer* meta;   /* �����ײ�ĵ�ͼ�� */
    CCTMXLayer* barrier;/* �ϰ���� */

    /* ����������ת��Ϊ��ͼ��������*/
    CCPoint tileCoordForPosition(CCPoint pos);
};

#endif