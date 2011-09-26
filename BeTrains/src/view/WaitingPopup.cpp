/*
 * WaitingPopup.cpp
 *
 *  Created on: 19-sep.-2011
 *      Author: B123
 */

#include "view/WaitingPopup.h"
#include "controller/Controller.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;

WaitingPopup::WaitingPopup():
	cancelButton(null),
	popup(null),
	msgbox(null)
{
}

WaitingPopup::~WaitingPopup()
{
}

void WaitingPopup::Construct(int screenWidth, int screenHeight){
	AppLog("WaitingPopup::Construct");
	int width, height;
	if(screenWidth < screenHeight){
		//portrait
		width = 0.9*screenWidth;
		height = screenHeight/4;
	}else{
		//landscape
		width = 0.9*screenWidth;
		height = screenHeight/2;
	}
	//AppLog("width %S, height %S",Integer::ToString(width).GetPointer(),Integer::ToString(height).GetPointer());
	//popup = new Popup();
	//popup->Construct(true,Dimension(390,200));
	//msgbox = new MessageBox();
	//msgbox->Construct("loading","",MSGBOX_STYLE_CANCEL);
	//Popup::Construct(true,Dimension(390,200));
	AppLog("WaitingPopup::first construct popup");
	//cancelButton = new Button();
	//cancelButton->Construct(Rectangle(5,50,380,150),L"Cancel");
	//cancelButton->Construct(Rectangle(0,0,width,height*0.9),L"Cancel");
	//cancelButton->SetActionId(CANCEL_BUTTON_ID);
	//cancelButton->AddActionEventListener(*this);
	//AddControl(*cancelButton);

	popup = new Popup();
	Dimension dim(width, height);
	popup->Construct(true, dim);
	popup->SetTitleText(L"Loading...");
	// Creates a button to close the Popup.
	button = new Button();
	button->Construct(Rectangle(0.15*width, 0, 0.70*width, 0.5*height), L"Cancel");
	button->SetActionId(CANCEL_ACTION);
	button->AddActionEventListener(*this);
	popup->AddControl(*button);

}
void WaitingPopup::showPopup(int screenWidth, int screenHeight){
	int width, height;
	if(screenWidth < screenHeight){
		//portrait
		width = 0.9*screenWidth;
		height = screenHeight/4;
	}else{
		//landscape
		width = 0.9*screenWidth;
		height = screenHeight/2;
	}
	popup->SetSize(width,height);
	button->SetBounds(0.15*width, 0, 0.70*width, 0.5*height);
	popup->SetShowState(true);
	popup->Show();
}

void WaitingPopup::hidePopup(){
	popup->SetShowState(false);
}

void WaitingPopup::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	if(actionId == CANCEL_ACTION){
		AppLogDebug("popup cancel button pressed");
		Controller::GetInstance()->cancelRequest();
		Controller::GetInstance()->hidePopup(); //this also redraws current form, so it gets removed again
	}
}
