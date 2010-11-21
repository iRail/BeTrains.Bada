/*
 * TextItem.h
 * The code written in this file was intended to serve as an EXAMPLE. You are
 * free to modify and use code in this file, provided that credit is given
 * where due.However, the code is also provided without ANY WARRANTY, EXPRESSED
 * OR IMPLIED, INCLUDING ANY WARRANTIES OR CONDITIONS OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSES. Users of the code contained in this file
 * assume the risks and costs of, including but not limited to, any program
 * errors, data loss or interruption of operations.
 *
 * This was written for the Bada "Custom Lists" tutorial at:
 * http://kahdev.wordpress.com/2010/07/28/bada_creating_custom_list
 *
 *  Created on: 17/07/2010
 *      Author: Kah
 */
#ifndef TEXTITEM_H_
#define TEXTITEM_H_

#include <FBase.h>
#include <FUi.h>

using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui::Controls;

class TextItem : public ICustomListElement
{

public:
    enum Align {
        LEFT,
        CENTER,
        RIGHT
    };

private:
    const String content;
    const Font* font;
    const Align alignment;

public:
    TextItem(const String& content, Font* font, Align alignment=LEFT) :
        content(content), font(font), alignment(alignment) {};


    result DrawElement(
            const Canvas& canvas,
            const Rectangle& rect,
            CustomListItemStatus itemStatus
    );

    virtual ~TextItem() {};
};

#endif /* TEXTITEM_H_ */
