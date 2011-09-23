/*
 * WaitingPopup.cpp
 *
 *  Created on: 19-sep.-2011
 *      Author: B123
 */

#include "WaitingPopup.h"
#include "controller/Controller.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;

WaitingPopup::WaitingPopup(String title,int width,int height) {
	//Popup::Construct(true, Dimension(width,height));
	cancelButton = new Button();
	cancelButton->Construct(Rectangle(width*0.15,height/3,width*0.6,height/4),L"Cancel");
	cancelButton->SetActionId(CANCEL_BUTTON_ID);
	cancelButton->AddActionEventListener(*this);
	AddControl(*cancelButton);
	SetTitleText(title);
}

WaitingPopup::~WaitingPopup() {
}

void WaitingPopup::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	if(actionId == CANCEL_BUTTON_ID){
		AppLogDebug("popup cancel button pressed");
		Controller::GetInstance()->cancelRequest();
	}
}
