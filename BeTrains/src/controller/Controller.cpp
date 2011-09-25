/*
 * Controller.cpp
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#include "controller/Controller.h"
#include "view/HeaderForm.h"
#include "model/Connection.h"
#include "model/Trip.h"

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
	routePlannerResults = null;
	liveBoardResults = null;
	liveBoardResults = null;
	waitingPopup = null;

	prevForm = null;
	currentForm = null;

	routeRequestManager=null;
	liveBoardRequestManager=null;

	//set start screen
	switchToFormRoutePlanner();

	/*
	 * test getting Locale lang. setting
	 */
	//Osp::Locations::Services::ServicePreferences preferences;
	//Osp::Locales::LanguageCode language = preferences.GetLanguage();
	//AppLog("Language is: %S",language)


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
	currentForm->RequestRedraw(true);
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
	formLiveBoard->RequestRedraw();
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
	formRoutePlanner->RequestRedraw();
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

	liveBoardResults->RequestRedraw();
}

void Controller::switchToRoutePlannerResults() {
	hidePopup();
	if(formRoutePlanner != null)
		formRoutePlanner->hideWaitingPopup();
	if (currentForm == null || currentForm != (Form*) routePlannerResults) {
		prevForm = currentForm;
		if(routePlannerResults ==null){
			routePlannerResults = new RoutePlannerResults();
			routePlannerResults->Initialize();
		}
		routePlannerResults->RequestRedraw(true);
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
	if(routeRequestManager != null)
		delete routeRequestManager;
	routeRequestManager = new RouteRequestManager();
	AppLog("set request");
	routeRequestManager->setRequest(AppData::GetInstance()->getCurrentRequest(),addToResults);
}

//if add to results is false==default then the results get cleared before adding the new onces from the last request
void Controller::retrieveLiveBoardResults(bool addToResults){
	if(liveBoardRequestManager != null)
		delete liveBoardRequestManager;
	liveBoardRequestManager = new LiveBoardRequestManager();
	liveBoardRequestManager->setRequest(AppData::GetInstance()->getCurrentLiveBoardRequest(),addToResults);
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
		Osp::Social::Calendarbook* calendarbook = new Calendarbook();
		calendarbook->Construct(null);
		CalEvent event;
		DateTime startTime, endTime;
		event.SetCategory(EVENT_CATEGORY_APPOINTMENT);
		Connection* first;
		Connection* last;
		trip->getConnections()->GetAt(0,first);
		trip->getConnections()->GetAt(trip->getConnections()->GetCount()-1,last);
		ConnectionNode* firstNode=first->getStartConnectionNode();
		ConnectionNode* lastNode=last->getEndConnectionNode();
		r = event.SetSubject(firstNode->getStation()->getName() + "-" + lastNode->getStation()->getName());
		DateTime start= firstNode->getDateTime();
		DateTime end  = lastNode->getDateTime();
		r = event.SetStartAndEndTime(start, end);
		String desc="testje";
		event.SetDescription(desc);
		calendarbook->AddEvent(event);

		AppLog("Controller::save to calendar");
	}
}

void Controller::newRequest(){
	AppData::GetInstance()->newRequest();
}

void Controller::newLiveboardRequest(){
	AppData::GetInstance()->newLiveboardRequest();
}

void Controller::getMoreResults(){
	showPopup();
	Request* request = AppData::GetInstance()->getCurrentRequest();
	Trip* lastTrip;
	request->getTrips()->GetAt(request->getTrips()->GetCount()-1,lastTrip);
	Connection* firstConn;
	lastTrip->getConnections()->GetAt(0,firstConn);
	DateTime lastTripTime = firstConn->getStartConnectionNode()->getDateTime();
	request->setDateTime(lastTripTime);
	request->setIsDepart(true); //could be problems if on arrival, then the request is somewhat wrong
	retrieveRoutePlannerResults(true);
}

void Controller::showPopup(){
	int width = currentForm->GetClientAreaBounds().width;
	int height = currentForm->GetClientAreaBounds().height;
	//AppLog("width %S, height %S",Integer::ToString(width).GetPointer(),Integer::ToString(height).GetPointer());
	if(waitingPopup==null){
		AppLog("Controller::first construct popup");
		waitingPopup = new WaitingPopup();
		waitingPopup->Construct(width,height);
	}
	AppLog("show popup");
	waitingPopup->showPopup(width,height);
	currentForm->Draw();
	currentForm->Show();
}
void Controller::hidePopup(){
	AppLog("hide popup");
	if(waitingPopup != null)
		waitingPopup->hidePopup();
	currentForm->Draw();
	currentForm->Show();
}
