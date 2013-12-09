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

    /* 实现SimpleMoveListener接口的方法 */
    virtual void setSimplePosition(int x, int y);
    virtual CCPoint getCurPosition();
protected:
    CCSprite* mSprite;
    Controller* mController;
    CCTMXTiledMap* map;

    CCTMXLayer* meta;   /* 检测碰撞的地图层 */
    CCTMXLayer* barrier;/* 障碍物层 */

    /* 将像素坐标转换为地图格子坐标*/
    CCPoint tileCoordForPosition(CCPoint pos);
};

#endif