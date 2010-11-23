/**
 * Name        : BeTrains
 * Version     : 
 * Vendor      : iRail Betrains
 * Description : 
 * Author	   : Bart Bruynooghe
 */


#include "BeTrains.h"
#include "Model/Connection.h"
#include "Model/Trip.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

BeTrains::BeTrains()
{
}

BeTrains::~BeTrains()
{
}

Application*
BeTrains::CreateInstance(void)
{
	// Create the instance through the constructor.
	return new BeTrains();
}

bool
BeTrains::OnAppInitializing(AppRegistry& appRegistry)
{
	Connection *c = new Connection();
	if(c == null){
		AppLog("2:null");
	}
	Trip *p = new Trip();
	p->getConnections()->Add(c);
	delete p;
	if(c == null){
		AppLog("2:null");
	}
	AppLog("OKaytjes");
	// Uncomment the following statement to listen to the screen on/off events.
	//PowerManager::SetScreenEventListener(*this);

	// Create a form
	//Form1 *pForm1 = new Form1();
	//pForm1->Initialize();

	// Add the form to the frame
	//Frame *pFrame = GetAppFrame()->GetFrame();
	//pFrame->AddControl(*pForm1);
	//pFrame->SetCurrentForm(*pForm1);
	//pForm1->Draw();
	//pForm1->Show();

	return true;
}

bool
BeTrains::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	return true;
}

void
BeTrains::OnForeground(void)
{
}

void
BeTrains::OnBackground(void)
{
}

void
BeTrains::OnLowMemory(void)
{
}

void
BeTrains::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{

}

void
BeTrains::OnScreenOn (void)
{
}

void
BeTrains::OnScreenOff (void)
{
}
