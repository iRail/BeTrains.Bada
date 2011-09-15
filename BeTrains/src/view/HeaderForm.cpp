/*
 * HeaderForm.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#include "view/HeaderForm.h"
#include "controller/Controller.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

HeaderForm::HeaderForm(void) {
}

HeaderForm::~HeaderForm(void) {
}

bool HeaderForm::Initialize(bool leftbutton,bool rightbutton) {
	this->RemoveAllControls();
	int settings = FORM_STYLE_NORMAL | FORM_STYLE_INDICATOR | FORM_STYLE_HEADER;
	if(leftbutton) settings = settings | FORM_STYLE_SOFTKEY_0;
	if(rightbutton) settings = settings | FORM_STYLE_SOFTKEY_1;
	Form::Construct(settings);
	return true;
}

result HeaderForm::OnInitializing(int index) {
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

	// routePlanner header
	HeaderItem routePlannerHeaderItem;
	routePlannerHeaderItem.Construct(HEADER_ID_ROUTE_PLANNER);
	routePlannerHeaderItem.SetText("Route Planner");
	routePlannerHeaderItem.SetActionId(this->HEADER_ID_ROUTE_PLANNER);

	/*
	 * create HeaderItems
	 */
	headerObj->AddItem(routePlannerHeaderItem);
	headerObj->AddItem(liveBoardHeaderItem);

	// derive correct index
	if(index == HEADER_ID_LIVEBOARD){
		index = 1;
	}else if( HEADER_ID_ROUTE_PLANNER){
		index = 0;
	}else{
		index = 0;
	}
	headerObj->SetItemSelected(index);
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