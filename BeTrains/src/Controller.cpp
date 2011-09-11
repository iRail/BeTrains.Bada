/*
 * Controller.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#include "Controller.h"

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
	prevForm = null;
	currentForm = null;
	formLiveBoard = new FormLiveboard();
	formRoutePlanner = new FormRouteplanner();
	selectStationForm = new SelectStationForm();
	switchToFormRoutePlanner();
	//selectStation();
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
		//formLiveBoard = new FormLiveboard();
		formLiveBoard->Initialize();
		currentForm = formLiveBoard;
		SetCurrentForm(currentForm);
	}
}

void Controller::SetCurrentForm(Form* currentForm) {
	// Add the form to the frame
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->AddControl(*currentForm);
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
		//formRoutePlanner = new FormRouteplanner();
		formRoutePlanner->Initialize();
		currentForm = formRoutePlanner;
		SetCurrentForm(currentForm);
	}
}

void Controller::switchToResultsLiveBoard() {
}
void Controller::switchToResultsRoutePlanner() {
}
void Controller::selectStation() { //Station* station
	if (currentForm == null || currentForm != (Form*) selectStationForm) {
		prevForm = currentForm;
		//selectStationForm = new SelectStationForm();
		selectStationForm->Initialize();
		currentForm = selectStationForm;
		SetCurrentForm(currentForm);
	}
}

void Controller::setPreviousForm(){
	/*
	if(prevForm != null){
		//I switch current & prevForm so in the SetCurrentForm method, controls from the current get removed
		Form* toggleForm=currentForm;
		currentForm = prevForm;
		prevForm = toggleForm;
		currentForm->Initialize();
		SetCurrentForm(currentForm);
	}
	*/
}

//actions
void Controller::returnSelectedStation() {
}
