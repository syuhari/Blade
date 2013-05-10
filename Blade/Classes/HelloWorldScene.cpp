#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define MOTION_STREAK_TAG 1

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sprite = CCSprite::create("HelloWorld.png");
    sprite->setPosition(ccp(size.width/2, size.height/2));
    this->addChild(sprite);
    
    m_iCount = 0;
    srand( static_cast<unsigned int>( time(NULL) ) );
    
    return true;
}

void HelloWorld::onEnter() {
    CCNode::onEnter();
    this->setTouchEnabled(true);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
}

void HelloWorld::resetMotionStreak() {
    this->removeChildByTag(MOTION_STREAK_TAG, true);
    CCMotionStreak* streak = CCMotionStreak::create(0.5f, 1, 10, ccc3(255, 255, 0), "line.png");
    this->addChild(streak, 5, MOTION_STREAK_TAG);
}

void HelloWorld::addMotionStreakPoint(cocos2d::CCPoint point) {
    CCMotionStreak* streak = (CCMotionStreak*)this->getChildByTag(MOTION_STREAK_TAG);
    streak->setPosition(point);
    
    if (++m_iCount>100) {
        int r = rand()%256;
        int b = rand()%265;
        int g = rand()%256;
        streak->setColor(ccc3(r, b, g));
        m_iCount = 0;
    }
}

bool HelloWorld::ccTouchBegan(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pEvent) {
    this->resetMotionStreak();
    CCPoint point = this->convertTouchToNodeSpace(ptouch);
    this->addMotionStreakPoint(point);
    return true;
}

void HelloWorld::ccTouchMoved(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pEvent) {
    CCPoint point = this->convertTouchToNodeSpace(ptouch);
    this->addMotionStreakPoint(point);
}

void HelloWorld::ccTouchEnded(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pEvent) {
}

void HelloWorld::ccTouchCancelled(cocos2d::CCTouch *ptouch, cocos2d::CCEvent *pEvent) {
}

