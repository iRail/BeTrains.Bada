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
	showMainMenu();
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

void BeTrains::showRoutePlanner(){
	plannerForm = new PlannerForm();
	plannerForm->Initialize();
	setForm(plannerForm);
}

void BeTrains::update(){
	AppLog("Update method invocation");
}

void BeTrains::showRoutePlannerStationSelector(){
	stationselectform = new Stationselectform();
	stationselectform->Initialize();
	setForm(stationselectform);
}

void BeTrains::showRoutePlannerResults(){
// TODO : implement

}

bool
BeTrains::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}
