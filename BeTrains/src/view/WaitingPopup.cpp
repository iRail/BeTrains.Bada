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
	popup(null)
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
		height = screenHeight/3;
	}else{
		//landscape
		width = 0.9*screenWidth;
		height = screenHeight/1.5;
	}
	//I18N
	String loading,cancel;
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"WP_LOADING", loading);
	appRes->GetString(L"WP_CANCEL", cancel);
	popup = new Popup();
	Dimension dim(width, height);
	popup->Construct(true, dim);

	popup->SetTitleText(loading);
	// Creates a button to close the Popup.
	button = new Button();
	button->Construct(Rectangle(0.15*width, 0.2*height, 0.70*width, 0.35*height), cancel);
	button->SetActionId(CANCEL_ACTION);
	button->AddActionEventListener(*this);
	popup->AddControl(*button);

}
void WaitingPopup::showPopup(int screenWidth, int screenHeight){
	AppLog("show popup");
	if(popup != null){
		button->RemoveActionEventListener(*this);
		popup->RemoveAllControls();
		delete popup;
	}

	Construct(screenWidth,screenHeight);
	/*
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

	Dimension dim(width, height);
	popup->Construct(true, dim);
	popup->SetTitleText(L"Loading...");
	// Creates a button to close the Popup.
	button = new Button();
	button->Construct(Rectangle(0.15*width, 0, 0.70*width, 0.5*height), L"Cancel");
	button->SetActionId(CANCEL_ACTION);
	button->AddActionEventListener(*this);
	popup->AddControl(*button);


	/*
	popup->SetSize(width,height);
	button->SetBounds(0.15*width, 0, 0.70*width, 0.5*height);
	*/
	popup->SetShowState(true);
	popup->Show();
}

void WaitingPopup::hidePopup(){
	if(popup != null)
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
