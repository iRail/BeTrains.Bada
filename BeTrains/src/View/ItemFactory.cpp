/*
 * ItemFactory.cpp
 *
 *  Created on: 27-okt-2010
 *      Author: B
 */

#include "View/ItemFactory.h"


ItemFactory::~ItemFactory() {
	// TODO Auto-generated destructor stub
}

void ItemFactory::Initialise(const int listWidth)
{
    pFormat = createFormat(listWidth);
    pDefaultFont->Construct(Osp::Graphics::FONT_STYLE_PLAIN,20);
}

CustomListItemFormat* ItemFactory::createFormat(const int listWidth)
{
    CustomListItemFormat *format = new CustomListItemFormat();
    format->Construct();
    const int INDENT = 30;

    format->AddElement(Constants::LIST_STATIONS, Rectangle(0, 0, listWidth-INDENT, 25));
    format->AddElement(Constants::LIST_TRAINS, Rectangle(listWidth-INDENT, 0, INDENT-10, 25));
    format->AddElement(Constants::LIST_TIMES, Rectangle(0, 25, listWidth/2, 25));
    format->AddElement(Constants::LIST_DURATION, Rectangle(listWidth/2, 25, listWidth/2-10, 25));
    return format;
}

CustomListItem* ItemFactory::createItem(const String& stationNames, const String& times, const String& duration, int trains){
	CustomListItem* item = new CustomListItem();
	item->Construct(50); //TODO generic
	item->SetItemFormat(*pFormat);
	item->SetElement(Constants::LIST_STATIONS,
			*(createTextItem(stationNames, TextItem::LEFT )));
	item->SetElement(Constants::LIST_TRAINS,
			*(createTextItem(L"#" + Integer::ToString(trains),TextItem::RIGHT )));
	item->SetElement(Constants::LIST_TIMES,
			*(createTextItem( times, TextItem::LEFT)));
	item->SetElement(Constants::LIST_DURATION,
			*(createTextItem(duration, TextItem::RIGHT)));
	return item;
}

TextItem* ItemFactory::createTextItem(const String& text, const TextItem::Align alignment)
{
    return new TextItem(text, pDefaultFont,alignment);
}
