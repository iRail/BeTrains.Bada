/**
 * Name        : tabtest
 * Version     : 
 * Vendor      : 
 * Description : 
 */


#include "tabtest.h"
#include "Controller.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

tabtest::tabtest()
{

}

tabtest::~tabtest()
{

}

Application*
tabtest::CreateInstance(void)
{
	return new tabtest();
}


bool
tabtest::OnAppInitializing(AppRegistry& appRegistry)
{
	Controller* controller = Controller::GetInstance();

	return true;
}

bool
tabtest::OnAppTerminating(AppRegistry& appRegistry, bool forcedTermination)
{
	// TODO:
	// Deallocate resources allocated by this application for termination.
	// The application's permanent data and context can be saved via appRegistry.
	return true;
}

void
tabtest::OnForeground(void)
{
	// TODO:
	// Start or resume drawing when the application is moved to the foreground.
}

void
tabtest::OnBackground(void)
{
	// TODO:
	// Stop drawing when the application is moved to the background.
}

void
tabtest::OnLowMemory(void)
{
	// TODO:
	// Free unused resources or close the application.
}

void
tabtest::OnBatteryLevelChanged(BatteryLevel batteryLevel)
{
	// TODO:
	// Handle any changes in battery level here.
	// Stop using multimedia features(camera, mp3 etc.) if the battery level is CRITICAL.
}

void
tabtest::OnScreenOn (void)
{
	// TODO:
	// Get the released resources or resume the operations that were paused or stopped in OnScreenOff().
}

void
tabtest::OnScreenOff (void)
{
	// TODO:
	//  Unless there is a strong reason to do otherwise, release resources (such as 3D, media, and sensors) to allow the device to enter the sleep mode to save the battery.
	// Invoking a lengthy asynchronous method within this listener method can be risky, because it is not guaranteed to invoke a callback before the device enters the sleep mode.
	// Similarly, do not perform lengthy operations in this listener method. Any operation must be a quick one.
}
