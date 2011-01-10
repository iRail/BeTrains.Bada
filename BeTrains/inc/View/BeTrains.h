#ifndef _BETRAINS_H_
#define _BETRAINS_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

#include "View/MainForm.h"
#include "View/Stationselectform.h"
#include "View/PlannerForm.h"
#include "View/IView.h"
#include "Controller/Controller.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

class PlannerForm;

class BeTrains :
	public Osp::App::Application,
	public Osp::System::IScreenEventListener,
	public IView
{
private:
		MainForm *mainForm;
		Stationselectform *stationselectform;
		PlannerForm *plannerForm;
		Controller controller;
public:
	BeTrains();
	~BeTrains();
	static Osp::App::Application* CreateInstance(void);
	void setForm(Form *form);
	void showMainMenu();
	void showRoutePlanner();
	void showRoutePlannerStationSelector();
	void showRoutePlannerResults();
	Controller* const getController(); //const pointer, controller state can be changed
	void update();

	bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
	bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);
	void OnForeground(void){}
	void OnBackground(void){}
	void OnLowMemory(void){}
	void OnBatteryLevelChanged(Osp::System::BatteryLevel batteryLevel){}
	void OnScreenOn (void){}
	void OnScreenOff (void){}
};

#endif
