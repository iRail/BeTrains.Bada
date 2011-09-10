/*
 * HeaderForm.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#include "HeaderForm.h"
#include "Controller.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

HeaderForm::HeaderForm(void) {
}

HeaderForm::~HeaderForm(void) {
}

bool HeaderForm::Initialize(bool leftbutton,bool rightbutton) {
	int settings = FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR | FORM_STYLE_HEADER;
	if(leftbutton) settings = settings | FORM_STYLE_SOFTKEY_0;
	if(rightbutton) settings = settings | FORM_STYLE_SOFTKEY_1;
	Form::Construct(settings);
	return true;
}

result HeaderForm::OnInitializing(void) {
	result r = E_SUCCESS;

	/*
	 * set OrientationListener
	 */
	this->SetOrientation(ORIENTATION_AUTOMATIC);
	this->AddOrientationEventListener(*this);
	// set header
	Header* headerObj = this->GetHeader();
	headerObj->SetStyle(HEADER_STYLE_SEGMENTED);


	// Liveboard header
	HeaderItem liveBoardHeaderItem;
	liveBoardHeaderItem.Construct(HEADER_ID_LIVEBOARD);
	liveBoardHeaderItem.SetText("liveboard");
	liveBoardHeaderItem.SetActionId(this->HEADER_ID_LIVEBOARD);

	// Stations header
	HeaderItem stationsHeaderItem;
	stationsHeaderItem.Construct(HEADER_ID_ROUTE_PLANNER);
	stationsHeaderItem.SetText("Route Planner");
	stationsHeaderItem.SetActionId(this->HEADER_ID_ROUTE_PLANNER);

	/*
	 * create HeaderItems
	 */

	headerObj->AddItem(liveBoardHeaderItem);
	headerObj->AddItem(stationsHeaderItem);

	/*
	 * add header action listener
	 */

	headerObj->AddActionEventListener(*this);
	return r;
}

result HeaderForm::OnTerminating(void) {
	result r = E_SUCCESS;

	return r;
}

void HeaderForm::OnActionPerformed(const Osp::Ui::Control& source, int actionId){
	if(actionId == this->HEADER_ID_ROUTE_PLANNER)
		Controller::GetInstance()->switchToFormRoutePlanner();
	if(actionId==this->HEADER_ID_LIVEBOARD)
			Controller::GetInstance()->switchToFormLiveBoard();
}

void HeaderForm::OnOrientationChanged(const Control& source, OrientationStatus orientationStatus){

}
