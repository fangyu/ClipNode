#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();

    Sprite* bg = Sprite::create("HelloWorld.png");
    bg->setPosition(visibleSize / 2);
    this->addChild(bg);
    
    m_holesClipper = ClippingNode::create();
    m_holesClipper->setPosition(visibleSize / 2);
    this->addChild(m_holesClipper);
    
    m_holesClipper->setInverted(true);
    m_holesClipper->setAlphaThreshold(0.5f);
    m_holesClipper->runAction(RepeatForever::create(RotateBy::create(1, 45)));
    
    m_holesStencil = Node::create();
    m_holesClipper->setStencil(m_holesStencil);
    m_holesStencil->addChild(Sprite::create("ball.png"), -1);
    
    m_holes = Node::create();
    m_holesClipper->addChild(m_holes);
    
    Sprite* content = Sprite::create("blocks.png");
    m_holesClipper->addChild(content, -1, "content");
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onTouchesBegan(const std::vector<Touch*>& touches, Event* unused_event)
{
    Vec2 point = touches[0]->getLocation();
    point = m_holesClipper->convertToNodeSpace(point);
    
    Sprite* content = (Sprite*)m_holesClipper->getChildByName("content");
    Size contentSize = content->getContentSize();
    Rect rect = Rect(-contentSize.width / 2, -contentSize.height / 2, contentSize.width, contentSize.height);
    
    if (rect.containsPoint(point))
    {
        pokeHoleAtPoint(point);
    }
}

void HelloWorld::pokeHoleAtPoint(const Vec2& point)
{
    CCLOG("Add a Hole!!!");
    
    auto hole = Sprite::create("hole_effect.png");
    hole->setPosition(point);
    m_holes->addChild(hole);

    auto holeStencil = Sprite::create("hole_stencil.png");
    holeStencil->setPosition(point);
    m_holesStencil->addChild(holeStencil);

    m_holesClipper->runAction(Sequence::create(ScaleTo::create(0.05f, 1.05f), ScaleTo::create(0.05f, 1.0f), NULL));
}
