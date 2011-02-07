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
	mainForm = null;
	stationselectform = null;
	plannerForm = null;
	tripListForm = null;
	requests.Construct(10);
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
	getController()->addView(this);
	//showMainMenu();

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
	ArrayListT<Trip *> * testTripList = controller.createTripList(&buffer);
	showTripList(testTripList);
	return true;
}

Controller* const BeTrains::getController(){
	return &controller;
}

void BeTrains::setForm(Form *form){
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	pFrame->AddControl(*form);
	pFrame->SetCurrentForm(*form);
	form->Draw();
	form->Show();
}

void BeTrains::showMainMenu(){
	mainForm = new MainForm();
	mainForm->Initialize();
	setForm(mainForm);
}

void BeTrains::showMap(){
}

void BeTrains::showRoutePlanner(){
	plannerForm = new PlannerForm();
	plannerForm->Initialize();
	setForm(plannerForm);
}

void BeTrains::showTripList(ArrayListT<Trip *> * trips){
	tripListForm = new TripListForm(trips);
	tripListForm->Initialize();
	setForm(tripListForm);
}

void BeTrains::update(){
	//AppLog("Update method invocation");
}

void BeTrains::showRoutePlannerStationSelector(Station *selectedStation,ArrayListT<Station *> * stations){
	stationselectform = new StationSelectForm(stations,selectedStation);
	stationselectform->Initialize();
	setForm(stationselectform);
	stationselectform->setKeyboard();
}

void BeTrains::showRoutePlannerResults(){
	//TODO : implement
}

bool
BeTrains::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}
