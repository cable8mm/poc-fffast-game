#include "HelloWorldScene.h"
#include "PauseMenuLayer.h"
#include "TableItem.h"

HelloWorld::HelloWorld()
: _isPause(false), _score(0)
{
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();
    
    // enable Touch
    layer->setTouchEnabled(true);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void HelloWorld::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	this->_selectingTime = clock();
    
    CCLog("TouchBegan Time %ld", millisecondNow());
    
    // TODO
    // if pause button tapped, _isPause set false
    
    if (this->_isPause) {
        return;
    }
    
    CCTouch *touch  = (CCTouch*)*touches->begin();
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    this->_selectedPoint.x    = pt.x;
    this->_selectedPoint.y    = pt.y;
    
    // if table_cloths touched
    for (unsigned int i=0; i < this->tableItems->count(); i++) {
        TableItem* tableItem    = (TableItem*)this->tableItems->objectAtIndex(i);
        if (tableItem->status == FULL_SETTING) {
            CCSprite* tableClothSprite    = (CCSprite*)tableItem->tableCloth();
            CCRect tableClothRect    = tableClothSprite->boundingBox();
            if (tableClothRect.containsPoint(pt)) {
                tableItem->isSelected   = true;
                return;
            }
        }
    }
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event) {
    
    
    
    // 테이블 터치 처리. 테이블 이외의 버튼 등의 처리 코드는 위에 위치해야 한다.
    TableItem* tableItem;
    TableItem* selectedTableItem;
    bool isSelectingTableItem   = false;
    
//    CCARRAY_FOREACH(this->tableItems,tableItem) {
//        if (tableItem->isSelected) {
//            selectedTableItem  = tableItem;
//            isSelectingTableItem    = true;
//            break;
//        }
//    }
    
    if (isSelectingTableItem == false) {
        return;
    }
    
    CCTouch *touch  = (CCTouch*)*touches->begin();
    CCPoint pt    = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    
    clock_t  unselectingTime = clock();
    float  diffSelected    = (float)(unselectingTime - this->_selectingTime);
    
    // distance
    float distance  = ccpDistance(pt,this->_selectedPoint);

    // shake and unsivible animation (this->_selectedTableSprite)
    CCArray* shakeObjectOverTableClothSpriteFrames    = new CCArray;
    
    int afterSweep; // 1 : success , 0 : failure, 2 : shake
    if (distance > 100. && diffSelected < 800000.) {    // success
        afterSweep  = 1;
        CCLog("SUCCESS");
        this->setScore(this->_score + 1);
        
        CCArray *removingTableCloth    = new CCArray;
        
        for (int i=0; i < 5; i++) {
            if (pt.x - this->_selectedPoint.x < 0) {
                removingTableCloth->addObject(CCSpriteFrame::createWithTexture(this->_tableClothTexture, CCRectMake(0, 200*i, 300, 200)));
                
            } else {
                removingTableCloth->addObject(CCSpriteFrame::createWithTexture(this->_tableClothTexture, CCRectMake(300, 200*i, 300, 200)));
                
            }
        }
        
        CCAnimation* animationTableCloth  = CCAnimation::createWithSpriteFrames(removingTableCloth, .1f);
        CCAnimate*  animateTableCloth = CCAnimate::create(animationTableCloth);
        
        CCSprite* selectedTableClothSprite  = (CCSprite*)this->_tableClothSprites->objectAtIndex(this->_selectedIndex);
        
        CCCallFuncO* actionDone  = CCCallFuncO::create(this, callfuncO_selector(HelloWorld::removeSprite), (CCSprite*)selectedTableClothSprite);
        
        selectedTableClothSprite->runAction(CCSequence::create(animateTableCloth, actionDone, NULL));
        
        this->_spriteTableCoordinations[this->_selectedIndex][3] = 0;
    } else if (distance < 100. || distance == 100.) {   // shake
        afterSweep  = 2;
        CCLog("AKABI");
    } else {                                            // failure
        afterSweep  = 3;
        CCLog("FAILURE");
        
    }
    
    for (int i=0; i < 4; i++) {
        if (afterSweep == 3) {   // 깨짐
            shakeObjectOverTableClothSpriteFrames->addObject(CCSpriteFrame::createWithTexture(this->_objectOverTableCloth, CCRectMake(200, 200*i, 200, 200)));
        } else {    // 흔들흔들
            shakeObjectOverTableClothSpriteFrames->addObject(CCSpriteFrame::createWithTexture(this->_objectOverTableCloth, CCRectMake(0, 200*i, 200, 200)));
        }
    }
    
    CCAnimation* animation  = CCAnimation::createWithSpriteFrames(shakeObjectOverTableClothSpriteFrames, .2f);
    CCAnimate*  animate = CCAnimate::create(animation);
    CCSprite* selectedObjectOverTableClothSprite  = (CCSprite*)this->_objectOverTableClothSprites->objectAtIndex(this->_selectedIndex);
    
    selectedObjectOverTableClothSprite->runAction(animate);
    this->_selectedTableSprite->setVisible(false);
    
    selectedTableItem->isSelected   = false;
}

void HelloWorld::removeSprite(CCObject* pObj) {
	CCSprite* sprite = (CCSprite*)pObj;
	sprite->removeFromParentAndCleanup(true);
}

void HelloWorld::ccTouchCancelled(CCSet* touches, CCEvent* event) {
    CCLog("Touch Cancel");
    this->_selectedTableSprite->setVisible(false);
}

void HelloWorld::reset() {  // 점수 초기화 및 테이블 리세팅
    // 점수 초기화
    this->setScore(0);
        
    float tableInformations[16][2] = {
        {100.,406.} ,{330.,443.} ,{560.,480.} ,{790.,517.}
        ,{230.,306.} ,{460.,343.} ,{690.,380.} ,{920.,417.}
        ,{360.,206.} ,{590.,243.} ,{820.,280.} ,{1050.,317.}
        ,{490.,106.} ,{720.,143.} ,{950.,180.} ,{1180.,217.}
    };

    unsigned int tableCount = sizeof((tableInformations))/sizeof((tableInformations[0]));
    
    CCSprite* highlightSprite = this->_selectedTableSprite  = CCSprite::create("table_select.png", CCRectMake(0, 0, 200, 200));
    this->_selectedTableSprite->setVisible(false);
    this->addChild(this->_selectedTableSprite, 8000);
    
    // 테이블 리세팅
    for (unsigned int i=0; i < tableCount; i++) {
        if (this->tableItems->count() > i) {
            this->tableItems->objectAtIndex(i)->release();
        }
        // generate tables
        CCSprite *tableSprite = CCSprite::create("table.png", CCRectMake(0, 0, 200, 200) );
        
        // generate table cloths
        CCSpriteFrame* stableTableCloth   = CCSpriteFrame::createWithTexture(this->_tableClothTexture
                                                                             , CCRectMake(0, 0, 300, 200));
        
        CCSprite *tableClothSprite = CCSprite::createWithSpriteFrame(stableTableCloth);
        
        //generate objects over table cloth
        CCSpriteFrame* stableObjectOverTableCloth   = CCSpriteFrame::createWithTexture(this->_objectOverTableCloth
                                                                                       , CCRectMake(0, 0, 200, 200));
        CCSprite* tableObject = CCSprite::createWithSpriteFrame(stableObjectOverTableCloth);
        
        // make table item instance
        TableItem* tableItem    = new TableItem(tableSprite, tableClothSprite, tableObject, highlightSprite, ccp(tableInformations[i][0],tableInformations[i][1]));
        this->tableItems->addObject(tableItem);
        this->addChild(tableSprite, 2);
        this->addChild(tableClothSprite, 3);
        this->addChild(tableObject, 4);
    }

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
#define TRANSFORM_SCALE  2.5
    
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // add pause button
    CCMenuItemImage *btnPause = CCMenuItemImage::create(
                                                        "button_up.png",
                                                        "button_down.png",
                                                        this,
                                                        menu_selector(HelloWorld::menuPauseCallback) );
    btnPause->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 54, CCDirector::sharedDirector()->getWinSize().height - 50) );
    
    // create menu, it's an autorelease object
    CCMenu* pause = CCMenu::create(btnPause, NULL);
    pause->setPosition( CCPointZero );
    this->addChild(pause, 9000);
    
    // add score png
    CCSprite* bgScore   = CCSprite::create("score.png", CCRectMake(0, 0, 590, 77) );
    bgScore->setPosition(ccp(300, CCDirector::sharedDirector()->getWinSize().height-40.));
    this->addChild(bgScore, 8000);
    
#ifndef NDEBUG
    // add cocos version
    CCLabelTTF*     cocosVersion = CCLabelTTF::create();
    cocosVersion->setColor(ccc3(0, 0, 0));
    cocosVersion->setFontSize(40.);
    cocosVersion->setString(cocos2dVersion());
    cocosVersion->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 250, 40.));
    this->addChild(cocosVersion, 8001);
#endif
    
    this->tableItems    = new CCArray;
    
    // add score
    _lbScore    = CCLabelTTF::create();
    _lbScore->setPosition(ccp(300, CCDirector::sharedDirector()->getWinSize().height-40.));
    _lbScore->setColor(ccc3(0, 0, 0));
    _lbScore->setFontSize(40.);
    this->addChild(_lbScore, 8001);
    this->setScore(0);
    
    /////////////////////////////
    // add table image
    
    this->_objectOverTableCloth = CCTextureCache::sharedTextureCache()->addImage("glass_ani.png");
    this->_objectOverTableClothSprites  = new CCArray;
    
    this->_tableClothTexture    = CCTextureCache::sharedTextureCache()->addImage("table_cloth_ani.png");
    
    this->reset();
    
    /////////////////////////////
    // 3. add your codes below...
    
    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pSprite = CCSprite::create("bg_level1.png");
    
    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    
    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    this->_status   = 0;    // READY
    this->schedule(schedule_selector(HelloWorld::update));
    return true;
}

void HelloWorld::setScore(int score) {
    this->_score    = score;
    char strScore[20];
    sprintf(strScore, "%d", score);
    this->_lbScore->setString(strScore);
}

void HelloWorld::update(float dt) {
    switch (this->_status) {
        case 0: // READY
            break;
        case 1: // PLAY GAME
            break;
        case 2: // PAUSE GAME
            break;
    }
}

void HelloWorld::menuPauseCallback(CCObject* pSender)
{
    CCLog("PauseCallback Pushed");
    this->pauseSchedulerAndActions();
    PauseMenuLayer* pauseMenuLayer  = PauseMenuLayer::create();
    pauseMenuLayer->setColor(ccc3(0, 0, 0));
    this->addChild(pauseMenuLayer, 100000);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

long HelloWorld::millisecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_sec / 1000);
}
