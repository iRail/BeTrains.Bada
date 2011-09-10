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
	formLiveBoard=null;
	formRoutePlanner =null;
	prevForm = null;


	// Create a form
	FormLiveboard *pFormLiveboard = new FormLiveboard();
	currentForm = pFormLiveboard;
	pFormLiveboard->Initialize();

	// Add the form to the frame
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->AddControl(*currentForm);

	// Set the current form
	pFrame->SetCurrentForm(*currentForm);

	// Draw and Show the form
	currentForm->Draw();
	currentForm->Show();
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
void Controller::switchToFormLiveBoard(){
	if(currentForm != (Form*)formLiveBoard){
		prevForm = currentForm;
		formLiveBoard = new FormLiveboard();
		formLiveBoard->Initialize();
		currentForm = formLiveBoard;

		// Add the form to the frame
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		pFrame->AddControl(*currentForm);

		// Set the current form
		pFrame->SetCurrentForm(*currentForm);

		// Draw and Show the form
		currentForm->Draw();
		currentForm->Show();

	}
}

void Controller::switchToFormRoutePlanner(){
	if(currentForm != (Form*)formRoutePlanner){
			prevForm = currentForm;
			formRoutePlanner = new FormRouteplanner();
			formRoutePlanner->Initialize();
			currentForm = formRoutePlanner;

			// Add the form to the frame
			Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			pFrame->AddControl(*currentForm);

			// Set the current form
			pFrame->SetCurrentForm(*currentForm);

			// Draw and Show the form
			currentForm->Draw();
			currentForm->Show();
		}
}

void Controller::switchToResultsLiveBoard(){}
void Controller::switchToResultsRoutePlanner(){}
void Controller::selectStation(Osp::Base::String & station){} //TODO change to class Station

//actions
void Controller::returnSelectedStation(){}
