#include "Player.h"
#include "SimpleMoveControll.h"

Player* Player::createWithTiledMap( CCTMXTiledMap* map )
{
    Player* mPlayer = new Player();

    if(mPlayer && mPlayer->initWithTiledMap(map)) {
        //mPlayer->autorelease();
    }
    else {
        CC_SAFE_DELETE(mPlayer);
    }

    return mPlayer;
}

bool Player::initWithTiledMap( CCTMXTiledMap* map )
{
    /* ���ض��������ж��� */
    CCTMXObjectGroup* objGroup = map->objectGroupNamed("objects");

    /* ����meta�� */
    meta = map->layerNamed("meta");
    meta->setVisible(false);

    /* �����ϰ���� */
    barrier = map->layerNamed("barrier");

    /* �������������� */
    CCDictionary* playerPointDic = objGroup->objectNamed("PlayerPoint");
    float playerX = playerPointDic->valueForKey("x")->floatValue();
    float playerY = playerPointDic->valueForKey("y")->floatValue();

    /* -------------- ������� --------------- */
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCSprite* playerSprite = CCSprite::create("sprite/player1.png");
    playerSprite->setPosition(ccp(playerX, playerY));

    /* ������ӵ���ͼ */
    map->addChild(playerSprite, 20);

    /* �󶨾������ */
    setSprite(playerSprite);

    /* �����ͼ������ */ 
    this->map = map;

    return true;
}

void Player::run()
{
    CCArray* framesList = CCArray::create();

    framesList->addObject(CCSpriteFrame::create("sprite/player1.png", CCRectMake(0, 0, 77, 134)));
    framesList->addObject(CCSpriteFrame::create("sprite/player2.png", CCRectMake(0, 0, 66, 129)));
    framesList->addObject(CCSpriteFrame::create("sprite/player3.png", CCRectMake(0, 0, 99, 132)));
    framesList->addObject(CCSpriteFrame::create("sprite/player4.png", CCRectMake(0, 0, 111, 135)));
    framesList->addObject(CCSpriteFrame::create("sprite/player5.png", CCRectMake(0, 0, 94, 132)));
    framesList->addObject(CCSpriteFrame::create("sprite/player6.png", CCRectMake(0, 0, 64, 128)));
    framesList->addObject(CCSpriteFrame::create("sprite/player7.png", CCRectMake(0, 0, 96, 133)));
    framesList->addObject(CCSpriteFrame::create("sprite/player8.png", CCRectMake(0, 0, 103, 138)));
    
    CCAnimation* animation = CCAnimation::createWithSpriteFrames(framesList, 0.2f);
    animation->setLoops(-1);

    mSprite->runAction(CCAnimate::create(animation));
}

void Player::setSimplePosition( int x, int y )
{
    if(x >= map->getMapSize().width * map->getTileSize().width) {
        return;
    }
    /* -----------------�ж��Ƿ񲻿�ͨ��---------------- */
    /* ��õ�ǰ�����ڵ�ͼ�еĸ���λ�� */
    CCPoint tiledPos = tileCoordForPosition(ccp(x, y));

    /* ��ȡ��ͼ���ӵ�Ψһ��ʶ */
    int tiledGid = meta->tileGIDAt(tiledPos);

    /* ��Ϊ0���������������� */
    if(tiledGid != 0) {
        /* 
            ��ȡ�õ�ͼ���ӵ��������ԣ�Ŀǰ����ֻ��һ��Collidable����,
            ����������meta��ģ���ͬʱҲ������������ͼ�ģ������ڻ�ȡ���ӵ���������ʱ��
            ͨ������Ψһ��ʶ�ڵ�ͼ��ȡ�á�
        */
        CCDictionary* propertiesDict = map->propertiesForGID(tiledGid);

        if(propertiesDict != NULL) {
            const CCString* prop = CCString::create("");

            /* ȡ�ø��ӵ�Collidable����ֵ, �ж�Collidable�����Ƿ�Ϊtrue,�ǵĻ�����������ƶ� */
            prop = propertiesDict->valueForKey("Collidable");
            if(prop->length() > 0 && prop->m_sString.compare("true") == 0) {
                if(x > 0) {
                    x -= 1;
                }
                else {
                    x += 1;
                }

                if(y > 0) {
                    y -= 1;
                }
                else {
                    y += 1;
                }
            }

            /* ȡ�ø��ӵ�star����ֵ���ж��Ƿ�Ϊtrue���ǵĻ����ø����ϵ�������ʧ */
            prop = propertiesDict->valueForKey("star");
            if(prop->length() > 0 && prop->m_sString.compare("true") == 0) {
                /* ���ϰ���������ǰ���ӵ����� */
                barrier->removeTileAt(tiledPos);
            }
        }
    }

    Entity::setSimplePosition(x, y);

    /* ������Ϊ�����ƶ���ͼ */
    setViewPointByPlayer();
}

void Player::setViewPointByPlayer()
{
    if(mSprite == NULL) {
        return;
    }
    CCLayer* parent = (CCLayer* )mSprite->getParent();

    /* ��ͼ�������� */
    CCSize mapTiledNum = map->getMapSize();

    /* ��ͼ�������Ӵ�С */
    CCSize tiledSize = map->getTileSize();

    /* ��ͼ��С */
    CCSize mapSize = CCSize::CCSize(
        mapTiledNum.width * tiledSize.width, 
        mapTiledNum.height * tiledSize.height);

    /* ��Ļ��С */
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    /* ��������� */
    CCPoint spritePos = mSprite->getPosition();

    /* �����������С����Ļ��һ�룬��ȡ��Ļ�е����꣬����ȡ��������� */
    float x = max(spritePos.x, visibleSize.width / 2);
    float y = max(spritePos.y, visibleSize.height / 2);

    /* ���x��y������������Ͻǵļ���ֵ����ȡ����ֵ�����꣨����ֵ��ֵ���õ�ͼ������Ļ��ɳ��ֺڱߵļ������꣩ */
    x = min(x, mapSize.width - visibleSize.width / 2);
    y = min(y, mapSize.height - visibleSize.height / 2);

    CCPoint destPos = CCPoint::CCPoint(x, y);
    CCPoint centerPos = CCPoint::CCPoint(visibleSize.width / 2, visibleSize.height / 2);
    
    /* ������Ļ�е����Ҫ�ƶ���Ŀ�ĵ�֮��ľ��� */
    CCPoint viewPos = ccpSub(centerPos, destPos);

    parent->setPosition(viewPos);
}