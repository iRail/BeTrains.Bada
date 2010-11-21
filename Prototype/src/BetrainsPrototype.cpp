/**
 * Name        : BetrainsPrototype2
 * Version     : 
 * Vendor      : BartB
 * Description : 
 */

#include "BetrainsPrototype.h"
#include "MainOptionList.h"
#include "TrainsResultsForm.h"
#include "PlannerSearchForm.h"
#include "IRailConnection.h"
#include "Connection.h";


#include "FXml.h"
using namespace Osp::Base::Utility;
using namespace Osp::Xml;

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Net;

BetrainsPrototype::BetrainsPrototype()
{
}

BetrainsPrototype::~BetrainsPrototype()
{
}

Application*
BetrainsPrototype::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new BetrainsPrototype();
}

void BetrainsPrototype::showMenu(void){
	Connection b;
	b.setDuration(10000);
	String to = L"vanneke";
	String fr = L"naarreke";
	b.setFromStation(to);
	b.setToStation(fr);
	b.setToTime(L"2010-11-17T05:00Z");

	MainOptionList *pMainOptionList = new MainOptionList();
	pMainOptionList->Initialize();
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	Form *form = pFrame->GetCurrentForm();
	pFrame->AddControl(*pMainOptionList);
	pFrame->SetCurrentForm(*pMainOptionList);
	pMainOptionList->Draw();
	pMainOptionList->Show();
	if(form != null){
		pFrame->RemoveControl(*form);
	}
}

void BetrainsPrototype::showRoutePlanner(void){
	PlannerSearchForm *pPlannerSearchForm = new PlannerSearchForm();
	pPlannerSearchForm->Initialize();
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	Form *form = pFrame->GetCurrentForm();
	pFrame->AddControl(*pPlannerSearchForm);
	pFrame->SetCurrentForm(*pPlannerSearchForm);
	pPlannerSearchForm->Draw();
	pPlannerSearchForm->Show();
	if(form != null){
		pFrame->RemoveControl(*form);
	}
}

void BetrainsPrototype::showChat(void){
	showMenu();
}

void BetrainsPrototype::showMap(void){

}

void BetrainsPrototype::showTraffic(void){}

void BetrainsPrototype::showPlannerResults(Osp::Base::String from,Osp::Base::String to){
	IRailConnection* conn = new IRailConnection();
	TrainsResultsForm *pTrainsResultsForm = new TrainsResultsForm();
	pTrainsResultsForm->Initialize();
	conn->getTrip(from,to,pTrainsResultsForm);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	Form *form = pFrame->GetCurrentForm();
	pFrame->AddControl(*pTrainsResultsForm);
	pFrame->SetCurrentForm(*pTrainsResultsForm);
	pTrainsResultsForm->Draw();
	pTrainsResultsForm->Show();
	if(form != null){
		pFrame->RemoveControl(*form);
	}
}

bool
BetrainsPrototype::OnAppInitializing(AppRegistry& appRegistry)
{
	showMenu();
	return true;
}

bool
BetrainsPrototype::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
BetrainsPrototype::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
BetrainsPrototype::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
BetrainsPrototype::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
BetrainsPrototype::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
BetrainsPrototype::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
BetrainsPrototype::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
