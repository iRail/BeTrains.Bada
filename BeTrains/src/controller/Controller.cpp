/*
 * Controller.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#include "controller/Controller.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

Controller* Controller::instance = 0;

Controller::Controller() {
	//init vars
	formLiveBoard = null;
	formRoutePlanner = null;
	selectStationForm = null;
	liveBoardResults = null;

	prevForm = null;
	currentForm = null;

	routeRequestManager=null;
	liveBoardRequestManager=null;

	//set start screen
	switchToFormRoutePlanner();
}

Controller::~Controller() {

}

Controller*
Controller::GetInstance() {

	if (Controller::instance == 0) {
		Controller::instance = new Controller();
	}
	return Controller::instance;
}

//switch forms
void Controller::switchToFormLiveBoard() {
	if (currentForm == null || currentForm != (Form*) formLiveBoard) {
		prevForm = currentForm;
		if(formLiveBoard ==null){
			formLiveBoard = new FormLiveboard();
			formLiveBoard->Initialize();
		}
		currentForm = formLiveBoard;
		SetCurrentForm(currentForm);
	}
}

void Controller::SetCurrentForm(Form* currentForm) {
	// Add the form to the frame
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->AddControl(*currentForm);
	//when deleting prev form, you cant switch forms from in a method from the current form, when giving control back it shuts down the app
	//if (prevForm != null)
	//	pFrame->RemoveControl(*prevForm);
	pFrame->SetCurrentForm(*currentForm);

	// Draw and Show the form
	currentForm->Draw();
	currentForm->RequestRedraw();
	currentForm->Show();
}

void Controller::switchToFormRoutePlanner() {
	if (currentForm == null || currentForm != (Form*) formRoutePlanner) {
		prevForm = currentForm;
		if(formRoutePlanner ==null){
			formRoutePlanner = new FormRouteplanner();
			formRoutePlanner->Initialize();
		}
		currentForm = formRoutePlanner;
		SetCurrentForm(currentForm);
	}
}

void Controller::switchToLiveBoardResults() {
	if (currentForm == null || currentForm != (Form*) liveBoardResults) {
			prevForm = currentForm;
		if (liveBoardResults == null) {
			liveBoardResults = new LiveBoardResults();
			liveBoardResults->Initialize();
		}
		currentForm = liveBoardResults;
		SetCurrentForm(currentForm);
	}
}

void Controller::switchToRoutePlannerResults() {
	if (currentForm == null || currentForm != (Form*) routePlannerResults) {
		prevForm = currentForm;
		if(routePlannerResults ==null){
			routePlannerResults = new RoutePlannerResults();
			routePlannerResults->Initialize();
		}
		currentForm = routePlannerResults;
		SetCurrentForm(currentForm);
		routePlannerResults->RequestRedraw();
	}
}

void Controller::selectStation(Station* &station) { //Station* station
	if (currentForm == null || currentForm != (Form*) selectStationForm) {
		prevForm = currentForm;
		if(selectStationForm == null){
			selectStationForm = new SelectStationForm();
			selectStationForm->Initialize();
		}
		selectStationForm->setStation(station);
		currentForm = selectStationForm;
		SetCurrentForm(currentForm);
	}
}

void Controller::setPreviousForm(){
	if(prevForm != null){
		//I switch current & prevForm so in the SetCurrentForm method, controls from the current get removed
		Form* toggleForm=currentForm;
		currentForm = prevForm;
		prevForm = toggleForm;
		if(currentForm == static_cast<Form*>(formRoutePlanner)){
			formRoutePlanner->RequestRedraw();
		}
		if(currentForm == static_cast<Form*>(formLiveBoard)){
			formLiveBoard->RequestRedraw();
		}
		currentForm->RequestRedraw(true);
		//TODO howcome overloading functions is not working? example above
		SetCurrentForm(currentForm);
	}
}

void Controller::retrieveRoutePlannerResults(){
	if(routeRequestManager != null)
		delete routeRequestManager;
	routeRequestManager = new RouteRequestManager();
	routeRequestManager->setRequest(AppData::GetInstance()->getCurrentRequest());
}

void Controller::retrieveLiveBoardResults(){
	if(liveBoardRequestManager != null)
		delete liveBoardRequestManager;
	liveBoardRequestManager = new LiveBoardRequestManager();
	liveBoardRequestManager->setRequest(AppData::GetInstance()->getCurrentLiveBoardRequest());
}
