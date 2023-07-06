//
//  PauseMenuLayer.cpp
//  fffast
//
//  Created by cable8mm on 13. 4. 4..
//
//

#include "PauseMenuLayer.h"

PauseMenuLayer::PauseMenuLayer()
{
}

// on "init" you need to initialize your instance
bool PauseMenuLayer::init()
{
    
    //////////////////////////////
    // 1. super init first
    if( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) ) //RGBA
    {
        return false;
    }
    CCLog("PauseMenuLayer init()");
    
    // add bg
//    CCSprite* bgDimming  = CCSprite::create("bg_dimming.png");
//    bgDimming->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
//    this->addChild(bgDimming);
    
    // add pause button
    CCMenuItemFont *btnResume = CCMenuItemFont::create("RESUME",
                                                      this,
                                                        menu_selector(PauseMenuLayer::menuResumeCallback) );
    btnResume->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2 + 30) );
    btnResume->setFontSize(40);

    CCMenuItemFont *btnRestart = CCMenuItemFont::create("RESTART",
                                                       this,
                                                       menu_selector(PauseMenuLayer::menuRestartCallback) );
    btnRestart->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width / 2, CCDirector::sharedDirector()->getWinSize().height / 2 - 30   ) );
    btnRestart->setFontSize(40);

    // create menu, it's an autorelease object
    CCMenu* menu = CCMenu::create(btnResume, btnRestart, NULL);
    menu->setPosition( CCPointZero );
    this->addChild(menu, 9000);
    
    return true;
}

void PauseMenuLayer::menuResumeCallback(CCObject* pSender)
{
    CCLog("Pushed menuResumeCallback");
    this->removeFromParentAndCleanup(true);
}

void PauseMenuLayer::menuRestartCallback(CCObject* pSender)
{
    CCLog("Pushed menuRestartCallback");
    this->removeFromParentAndCleanup(true);
}
