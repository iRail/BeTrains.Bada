/*
 * ItemFactory.h
 *
 *  Created on: 27-okt-2010
 *      Author: B
 */

#ifndef ITEMFACTORY_H_
#define ITEMFACTORY_H_

#include <FBase.h>
#include <FUi.h>
#include "TextItem.h"
#include "Constants.h"

using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui::Controls;

class ItemFactory {
private:
    Font* pDefaultFont;
    CustomListItemFormat* pFormat;

public:
	ItemFactory(): pDefaultFont(new Font()), pFormat(NULL) {};
	virtual ~ItemFactory();
	CustomListItemFormat* createFormat(const int listWidth);
	void Initialise(int listWidth);
	CustomListItem* createItem(
			const String& stationNames, const String& times,
			const String& duration, int trains);
private:
	TextItem* createTextItem(const String& text, TextItem::Align alignment);
};

#endif /* ITEMFACTORY_H_ */
