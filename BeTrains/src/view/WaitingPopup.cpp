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
	cancelButton(null)
{
}

WaitingPopup::~WaitingPopup()
{
}

void WaitingPopup::Construct(int screenWidth, int screenHeight){
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
	*/
	//AppLog("width %S, height %S",Integer::ToString(width).GetPointer(),Integer::ToString(height).GetPointer());
	Popup::Construct(true,Dimension(390,200));
	AppLog("WaitingPopup::first construct popup");
	cancelButton = new Button();
	cancelButton->Construct(Rectangle(5,50,380,150),L"Cancel");
	//cancelButton->Construct(Rectangle(0,0,width,height*0.9),L"Cancel");
	cancelButton->SetActionId(CANCEL_BUTTON_ID);
	cancelButton->AddActionEventListener(*this);
	AddControl(*cancelButton);
}
void WaitingPopup::showPopup(int screenWidth, int screenHeight){
	if(screenWidth < screenHeight){
		//portrait
		SetSize(0.9*screenWidth,screenHeight/4);
		cancelButton->SetBounds(0,0,0.9*screenWidth,screenHeight/4);
	}else{
		//landscape
		SetSize(0.9*screenWidth,screenHeight/2);
		cancelButton->SetBounds(0,0,0.9*screenWidth,screenHeight/2.5);
	}
	RequestRedraw(true);
	SetShowState(true);

	//SetTitleText("Title");
}

void WaitingPopup::hidePopup(){
	SetShowState(false);
}

void WaitingPopup::OnActionPerformed(const Osp::Ui::Control &source, int actionId)
{
	if(actionId == CANCEL_BUTTON_ID){
		AppLogDebug("popup cancel button pressed");
		Controller::GetInstance()->cancelRequest();
	}
}
