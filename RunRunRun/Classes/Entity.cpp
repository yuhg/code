#include "Entity.h"
#include "Controller.h"

void Entity::setSprite( CCSprite* mSprite )
{
    this->mSprite = mSprite;
}

void Entity::setController( Controller* controller )
{
    this->mController = controller;
    controller->setControllerListener(this);
}


void Entity::setSimplePosition( int x, int y )
{
    if(mSprite) {
        mSprite->setPosition(ccp(x, y));
    }
}

cocos2d::CCPoint Entity::getCurPosition()
{
    if(mSprite) {
        return mSprite->getPosition();
    }

    return CCPoint::CCPoint(0, 0);
}

CCPoint Entity::tileCoordForPosition( CCPoint pos )
{
    CCSize mapTiledNum = map->getMapSize();
    CCSize tiledSize = map->getTileSize();

    int x = pos.x / tiledSize.width;
    int y = pos.y / tiledSize.height;

    /* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
    y = mapTiledNum.height - y;

    return ccp(x, y);
}