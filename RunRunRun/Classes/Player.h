#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

class Player : public Entity {
public:
    bool initWithTiledMap(CCTMXTiledMap* map);

    static Player* createWithTiledMap(CCTMXTiledMap* map);

    /* 重写父类的函数 */
    virtual void setSimplePosition(int x, int y);

    /* 让玩家跑起来 */
    void run();

    /* 以主角为中心移动地图 */
    void setViewPointByPlayer();

private:
    
};

#endif