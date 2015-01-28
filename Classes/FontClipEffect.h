//
//  FontClipEffect.h
//  ClippingNodeDemo
//
//  Created by fangyu on 1/28/15.
//
//

#ifndef __ClippingNodeDemo__FontClipEffect__
#define __ClippingNodeDemo__FontClipEffect__

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class FontClipEffect
: public cocos2d::Layer
{
public:
    
public:
    virtual bool init();
    static cocos2d::Scene* createScene();
    void menuCloseCallback(Ref* sender);
    CREATE_FUNC(FontClipEffect);
    
    Size visibleSize;
    Size winSize;
    Vec2 origin;

};
#endif /* defined(__ClippingNodeDemo__FontClipEffect__) */
