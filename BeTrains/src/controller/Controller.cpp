/*
 * Controller.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#include "controller/Controller.h"
#include "view/HeaderForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Social;

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


//switch forms
void Controller::switchToFormLiveBoard() {
	if (currentForm == null || currentForm != (Form*) formLiveBoard) {
		prevForm = currentForm;
		if(formLiveBoard ==null){
			formLiveBoard = new FormLiveboard();
			formLiveBoard->Initialize();
		}
		currentForm = formLiveBoard;
		Header* header = currentForm->GetHeader();
		header->SetItemSelected(HeaderForm::HEADER_ID_LIVEBOARD);
		header->SetItemSelected(HeaderForm::HEADER_ID_LIVEBOARD);
		SetCurrentForm(currentForm);
	}
}

void Controller::switchToFormRoutePlanner() {
	if (currentForm == null || currentForm != (Form*) formRoutePlanner) {
		prevForm = currentForm;
		if(formRoutePlanner ==null){
			formRoutePlanner = new FormRouteplanner();
			formRoutePlanner->Initialize();
		}
		currentForm = formRoutePlanner;
		Header* header = currentForm->GetHeader();
		header->SetItemSelected(HeaderForm::HEADER_ID_ROUTE_PLANNER);
		SetCurrentForm(currentForm);
	}
}

void Controller::switchToLiveBoardResults() {
	if(formLiveBoard != null)
		formLiveBoard->hideWaitingPopup();
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
	if(formRoutePlanner != null)
		formRoutePlanner->hideWaitingPopup();
	if (currentForm == null || currentForm != (Form*) routePlannerResults) {
		prevForm = currentForm;
		if(routePlannerResults ==null){
			routePlannerResults = new RoutePlannerResults();
			routePlannerResults->Initialize();
		}
		currentForm = routePlannerResults;
		SetCurrentForm(currentForm);
	}
	routePlannerResults->RequestRedraw();
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

void Controller::retrieveRoutePlannerResults(bool addToResults){
	AppLog("delete route request manager");
	if(routeRequestManager != null)
		delete routeRequestManager;
	AppLog("create new manager");
	routeRequestManager = new RouteRequestManager();
	AppLog("set request");
	routeRequestManager->setRequest(AppData::GetInstance()->getCurrentRequest(),addToResults);
}

//if add to results is false==default then the results get cleared before adding the new onces from the last request
void Controller::retrieveLiveBoardResults(){
	if(liveBoardRequestManager != null)
		delete liveBoardRequestManager;
	liveBoardRequestManager = new LiveBoardRequestManager();
	liveBoardRequestManager->setRequest(AppData::GetInstance()->getCurrentLiveBoardRequest());
}

void Controller::clearRoutePlanner(){
	// clear our request model
	AppData::GetInstance()->getCurrentRequest()->clear();

	// clear the views by requesting a redraw
	formRoutePlanner->RequestRedraw(true);
}

void Controller::clearLiveboard(){
	// clear our liveboard model
	AppData::GetInstance()->getCurrentLiveBoardRequest()->clear();

	// clear the views by requesting a redraw
	formLiveBoard->RequestRedraw(true);
}

void Controller::setRoutePlannerTime(DateTime time){
	AppData::GetInstance()->getCurrentRequest()->setDateTime(time);
	formRoutePlanner->RequestRedraw(true);
}

void Controller::setLiveboardTime(DateTime time){
	AppData::GetInstance()->getCurrentLiveBoardRequest()->setDateTime(time);
	formLiveBoard->RequestRedraw(true);
}

void Controller::cancelRequest(){
	if(routeRequestManager != null)
		routeRequestManager->cancelRequest();
	if(liveBoardRequestManager != null)
		liveBoardRequestManager->cancelRequest();
}

void Controller::switchRequestStations(){
	AppData::GetInstance()->getCurrentRequest()->switchStations();
	formRoutePlanner->RequestRedraw(true);
}

void Controller::setIsDeparture(bool isDeparture){
	AppData::GetInstance()->getCurrentRequest()->setIsDepart(isDeparture);
}

void Controller::saveToCalendar(int index){
	Trip* trip=null;
	result r = AppData::GetInstance()->getCurrentRequest()->getTrips()->GetAt(index,trip);
	if(r==E_SUCCESS && trip !=null){
		AppLog("1");
		Osp::Social::Calendarbook* calendarbook = new Calendarbook();
		AppLog("2");
		calendarbook->Construct(null);
		AppLog("3");
		CalEvent event;
		DateTime startTime, endTime;
		AppLog("4");
		event.SetCategory(EVENT_CATEGORY_APPOINTMENT);
		Connection* first;
		Connection* last;
		AppLog("5");
		trip->getConnections()->GetAt(0,first);
		AppLog("6");
		trip->getConnections()->GetAt(trip->getConnections()->GetCount()-1,last);
		ConnectionNode* firstNode=first->getStartConnectionNode();
		ConnectionNode* lastNode=last->getEndConnectionNode();
		AppLog("7");
		r = event.SetSubject(firstNode->getStation()->getName() + "-" + lastNode->getStation()->getName());
		DateTime start= firstNode->getDateTime();
		DateTime end  = lastNode->getDateTime();
		AppLog("8");
		r = event.SetStartAndEndTime(start, end);
		String desc="testje";
		AppLog("9");
		event.SetDescription(desc);
		calendarbook->AddEvent(event);

		AppLog("Controller::save to calendar");
	}

}
