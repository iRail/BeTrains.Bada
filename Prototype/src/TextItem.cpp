/*
 * TextItem.cpp
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

#include "TextItem.h"
#include <FBase.h>
#include <FUi.h>

using namespace Osp::Ui::Controls;

result
TextItem::DrawElement  (
        const Canvas& canvas,
        const Rectangle& rect,
        CustomListItemStatus itemStatus)
{
    Canvas *canvasPtr = const_cast<Canvas*>(&canvas);
    canvasPtr->SetFont(*(font));

    Dimension textDim;
    font->GetTextExtent(content, content.GetLength(), textDim);

    int xOffset = 0;
    if (alignment != LEFT)
    {
        xOffset = rect.width - textDim.width;
        if (alignment == CENTER)
        {
            // Middle position.
            xOffset = xOffset / 2;
        }
    }

    int yOffset = (rect.height - textDim.height) / 2;
    return canvasPtr->DrawText(Point(rect.x + xOffset,rect.y + yOffset),
            content);
}
