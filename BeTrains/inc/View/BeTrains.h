#ifndef _BETRAINS_H_
#define _BETRAINS_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

#include "View/MainForm.h"
#include "View/Stationselectform.h"
#include "View/IView.h"
#include "Controller/Controller.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
/**
 * [BeTrains] application must inherit from Application class
 * which provides basic features necessary to define an application.
 */
class BeTrains :
	public Osp::App::Application,
	public Osp::System::IScreenEventListener,
	public IView
{
private:
		MainForm *mainForm;
		Stationselectform *stationselectform;
		Controller controller;
public:
	/**
	 * [BeTrains] application must have a factory method that creates an instance of itself.
	 */
	BeTrains();
	~BeTrains();
	static Osp::App::Application* CreateInstance(void);
	void setForm(Form *form);
	void showMainMenu();
	void showRoutePlanner();
	void showRoutePlannerStationSelector();
	void showRoutePlannerResults();
	Controller* getController();
	void update();

	bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
	bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);
	void OnForeground(void);
	void OnBackground(void);
	void OnLowMemory(void);
	void OnBatteryLevelChanged(Osp::System::BatteryLevel batteryLevel);
	void OnScreenOn (void);
	void OnScreenOff (void);
};

#endif
