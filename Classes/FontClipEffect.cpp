//
//  FontClipEffect.cpp
//  ClippingNodeDemo
//
//  Created by fangyu on 1/28/15.
//
//

#include "FontClipEffect.h"

USING_NS_CC;
using namespace std;

Scene* FontClipEffect::createScene()
{
    Scene* scene = Scene::create();
    
    FontClipEffect* layer = FontClipEffect::create();
    scene->addChild(layer);
    return scene;
}


bool FontClipEffect::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    winSize = Director::getInstance()->getWinSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    
    Sprite* bg = Sprite::create("HelloWorld.png");
    bg->setPosition(visibleSize / 2);
    
    
    Sprite* gameTitle = Sprite::create("game_title.png");
    
    Size clipSize = gameTitle->getContentSize();
    
    Sprite* spark = Sprite::create("spark.png");
    spark->setPosition(-clipSize.width, 0);
    
    
    ClippingNode* clippingNode = ClippingNode::create();
    clippingNode->setAlphaThreshold(0);
    clippingNode->setContentSize(clipSize);
    clippingNode->setPosition(visibleSize / 2);
    this->addChild(clippingNode);
    
    
    clippingNode->setStencil(gameTitle);
    
    clippingNode->addChild(gameTitle, 1);
    clippingNode->addChild(spark,2);
    
    
    MoveTo* moveAction = MoveTo::create(2.0f, Vec2(clipSize.width, 0));
    MoveTo* moveBackAction = MoveTo::create(2.0f, Vec2(-clipSize.width, 0));
    Sequence* seq = Sequence::create(moveAction, moveBackAction, NULL);
    RepeatForever* repeatAction = RepeatForever::create(seq);
    spark->runAction(repeatAction);
    
    return true;
}