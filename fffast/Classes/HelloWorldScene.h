#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d;
using namespace CocosDenshion;

enum TABLE_ACTION_RESULT {
    SUCCESS_GET_CLOTH,
    FAIL_GETTING_CLOTH,
    SHAKE_OBJECT
};

class HelloWorld : public CCLayer
{
public:
    HelloWorld();
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuPauseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
    virtual void ccTouchesBegan(CCSet* touches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
    virtual void ccTouchCancelled(CCSet* touches, CCEvent* event);

	virtual void update(float dt);
    virtual void removeSprite(CCObject* pObj);
    CCSprite getTouchSprite(CCPoint pt);

	virtual void setScore(int score);
    void reset();
    
    long millisecondNow();
    
protected:
    int         _score;
    CCLabelTTF* _lbScore;
    
    int         _tableCount;
    CCArray*    _tableSprites;
    
    bool        _isPause;
    CCSprite*   _selectedTableSprite;
    clock_t     _selectingTime;
    CCPoint     _selectedPoint;
    CCTexture2D*    _objectOverTableCloth;
    CCArray*     _shakeObjectOverTableClothSpriteFrames;
    CCSprite*   _objectOverTableClothSprite;
    CCArray*    _objectOverTableClothSprites;
    CCTexture2D*    _tableClothTexture;
    CCArray*    _tableClothSprites;
    int         _selectedIndex;
    
    int         _status;    // READY
    
    CCArray*    _classSpriteFrames;
    
    int _spriteTableCoordinations[16][4];
    CCArray*    _tableCoordinations;
    
    CCArray*    tableItems;
    bool        atFirst;
};

#endif // __HELLOWORLD_SCENE_H__
