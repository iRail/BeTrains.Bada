/**
 * Name        : BeTrains
 * Version     : 
 * Vendor      : iRail Betrains
 * Description : 
 * Author	   : Bart Bruynooghe
 */


#include "View/BeTrains.h"
#include "Model/Connection.h"
#include "Model/Trip.h"
#include "Controller/Controller.h"
#include "View/TripListForm.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

BeTrains::BeTrains()
{
	// initialize variables , a list of request is forseen with a default capacity of 5
	stationSelectForm = null;
	plannerForm = null;
	tripListForm = null;
	testTripList = null;
	currentRequest = null;
	previousRequests.Construct(10);

	//TODO demo files, can be removed later
	String fileName(L"/Home/test.xml");
	File *file = new File();
	FileAttributes sourcefilemeta;
	File::GetAttributes(fileName, sourcefilemeta);
	int filesize = sourcefilemeta.GetFileSize();
	ByteBuffer buffer;
	buffer.Construct(filesize);
	file->Construct(fileName, L"r");
	file->Read(buffer);
	delete file;
	buffer.SetPosition(0);
	testTripList = controller.createTripList(&buffer);
}

BeTrains::~BeTrains()
{
}

Application* BeTrains::CreateInstance(void)
{
	return new BeTrains();
}

bool BeTrains::OnAppInitializing(AppRegistry& appRegistry)
{
	frame = Application::GetInstance()->GetAppFrame()->GetFrame();
	//create all Forms
	mainForm = new MainForm();
	stationSelectForm = new StationSelectForm();
	plannerForm = new PlannerForm();
	tripListForm = new TripListForm;

	//initiate forms
	mainForm->Initialize();
	stationSelectForm->Initialize();
	plannerForm->Initialize();
	tripListForm->Initialize();

	//add forms to frame
	frame->AddControl(*mainForm);
	frame->AddControl(*stationSelectForm);
	frame->AddControl(*plannerForm);
	frame->AddControl(*tripListForm);

	//load mainform on front
	showMainMenu();
	return true;
}

void BeTrains::showMainMenu(){
	frame->SetCurrentForm(*mainForm);
	frame->RequestRedraw();
}

void BeTrains::showMap(){
	showTripList();
}

void BeTrains::showRoutePlanner(){
	plannerForm->update(currentRequest);
	frame->SetCurrentForm(*plannerForm);
	frame->RequestRedraw();
}

void BeTrains::showTripList(){
	tripListForm->update(currentRequest);
	frame->SetCurrentForm(*tripListForm);
	frame->RequestRedraw();
}

void BeTrains::cancelCurrentRequest(){
	if(currentRequest != null){
		delete currentRequest;
		currentRequest=null;
	}
	showMainMenu();
}

void BeTrains::routePlannerSelectStation(bool isFromStation,Station* selectedStation){
	if(currentRequest == null)
		currentRequest = new Request();
	if(isFromStation){
		currentRequest->setFromStation(selectedStation);
	}else{
		currentRequest->setToStation(selectedStation);
	}
	plannerForm->update(currentRequest);
	frame->SetCurrentForm(*plannerForm);
	frame->RequestRedraw();
}

void BeTrains::update(){
	//AppLog("Update method invocation");
}

void BeTrains::showRoutePlannerStationSelector(bool isFromStation){
	stationSelectForm->update(isFromStation);
	frame->SetCurrentForm(*stationSelectForm);
	frame->RequestRedraw();
	stationSelectForm->setKeyboard();
}

void BeTrains::showRoutePlannerResults(){
	//TODO : implement
}

bool
BeTrains::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}

ArrayListT<Station*> * BeTrains::getStationList(){
	return controller.getStations();
}

Controller* const BeTrains::getController(){
	return &controller;
}
