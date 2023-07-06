//
//  TableItem.h
//  fffast
//
//  Created by cable8mm on 13. 4. 4..
//
//

#ifndef __fffast__TableItem__
#define __fffast__TableItem__

enum TABLE_ITEM_STATUS {
    FULL_SETTING,
    NO_TABLE_CLOTH,
    BROKEN_TABLE_OBJECT
};

#include "cocos2d.h"
using namespace cocos2d;

class TableItem : public cocos2d::CCObject
{
public:
    TableItem(CCSprite *sprite);
    TableItem(CCSprite *table, CCSprite *tableCloth, CCSprite *object, CCSprite *highlight, CCPoint position);
    void setPosition(CCPoint position);
    void show();

    CCSprite* tableCloth();
    void highlight(bool on);

    unsigned int status;
    bool isSelected;
    
protected:
    CCSprite* _tableCloth;      // 식탁보
    CCSprite* _tableObject;          // 식탁위 물건
    CCSprite* _table;           // 식탁
    CCSprite* _highlight;           // 식탁보 하일라이트
    CCPoint _position;          // 좌표
    CCPoint _resetPosition;     // 원래 스프라이트(리셋 대비용)
    
};

#endif /* defined(__fffast__TableItem__) */
