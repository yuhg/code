#include "TollgateScene.h"
#include "Player.h"
#include "SimpleMoveControll.h"
#include "ThreeDirectionController.h"

CCScene* TollgateScene::scene()
{
    CCScene* mScene = CCScene::create();

    TollgateScene* mLayer = TollgateScene::create();

    mScene->addChild(mLayer);

    return mScene;
}

bool TollgateScene::init()
{
    /* 加载地图 */
    CCTMXTiledMap* map = CCTMXTiledMap::create("map/level01.tmx");
    this->addChild(map); 

    /* 创建玩家 */
    Player* mPlayer = Player::createWithTiledMap(map);

    /* 让玩家跑起来 */
    mPlayer->run();

    /* ------------ 创建玩家移动控制器 -------------- */
    ThreeDirectionController* mSMoveControll = ThreeDirectionController::create();
    mSMoveControll->setiXSpeed(1);
    mSMoveControll->setiYSpeed(0);

    /* 控制器要添加到场景中才能获得update事件 */
    this->addChild(mSMoveControll);

    mPlayer->setController(mSMoveControll);
    return true;
}