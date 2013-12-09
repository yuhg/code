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
    /* ���ص�ͼ */
    CCTMXTiledMap* map = CCTMXTiledMap::create("map/level01.tmx");
    this->addChild(map); 

    /* ������� */
    Player* mPlayer = Player::createWithTiledMap(map);

    /* ����������� */
    mPlayer->run();

    /* ------------ ��������ƶ������� -------------- */
    ThreeDirectionController* mSMoveControll = ThreeDirectionController::create();
    mSMoveControll->setiXSpeed(1);
    mSMoveControll->setiYSpeed(0);

    /* ������Ҫ��ӵ������в��ܻ��update�¼� */
    this->addChild(mSMoveControll);

    mPlayer->setController(mSMoveControll);
    return true;
}