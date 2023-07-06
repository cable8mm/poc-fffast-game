//
//  PauseMenuLayer.h
//  fffast
//
//  Created by cable8mm on 13. 4. 4..
//
//

#ifndef __fffast__PauseMenuLayer__
#define __fffast__PauseMenuLayer__

#include "cocos2d.h"
using namespace cocos2d;

class PauseMenuLayer : public cocos2d::CCLayerColor
{
public:
    PauseMenuLayer();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    void menuResumeCallback(CCObject* pSender);
    void menuRestartCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(PauseMenuLayer);
    
protected:

};

#endif /* defined(__fffast__PauseMenuLayer__) */
