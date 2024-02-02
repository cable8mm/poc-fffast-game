//
//  TableItem.cpp
//  fffast
//
//  Created by cable8mm on 13. 4. 4..
//
//

#include "TableItem.h"

TableItem::TableItem(CCSprite *table, CCSprite *tableCloth, CCSprite *tableObject, CCSprite *highlight,
                     CCPoint position) {
    this->status = FULL_SETTING;
    this->isSelected = false;

    this->_table = table;
    this->_tableCloth = tableCloth;
    this->_tableObject = tableObject;
    this->_highlight = highlight;

    this->_table->setPosition(position);
    this->_tableCloth->setPosition(position);
    this->_tableObject->setPosition(position);
    this->_highlight->setPosition(position);
}

void TableItem::show() {
    this->_table->setVisible(true);
    this->_tableCloth->setVisible(true);
    this->_tableObject->setVisible(true);
}

CCSprite *TableItem::tableCloth() {
    return this->_tableCloth;
}

void TableItem::highlight(bool on) {
    this->_highlight->setVisible(on);
}
