#ifndef _BETRAINS_H_
#define _BETRAINS_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FNet.h>

#include "View/MainForm.h"
#include "View/StationSelectForm.h"
#include "View/PlannerForm.h"
#include "View/IView.h"
#include "Controller/Controller.h"
#include "View/TripListForm.h"
#include "Model/Station.h"


using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::System;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

class PlannerForm;

class BeTrains :
	public Osp::App::Application,
	public Osp::System::IScreenEventListener,
	public IView,
	public Osp::Net::Http::IHttpTransactionEventListener
{
private:
	//FRAME
	Frame* frame;
	//FORMS
	MainForm *mainForm;
	StationSelectForm *stationSelectForm;
	PlannerForm *plannerForm;
	TripListForm *tripListForm;

	//DATA
	Controller controller;
	ArrayListT<Request *> previousRequests; //ownership
	Request * currentRequest; //ownership
	ArrayListT<Trip *> * testTripList; //ownership
public:
	BeTrains();
	~BeTrains();
	static Osp::App::Application* CreateInstance(void);
	void setForm(Form *form);
	Controller* const getController(); //const pointer, controller state can be changed
	void update();

	Osp::Base::Collection::ArrayListT<Station*> * getStationList();

	//actions
	void showMainMenu();
	void showMap();
	void showRoutePlanner();
	void showRoutePlannerStationSelector(bool isFromStation); //adress from the pointer to fill station in
	void showRoutePlannerResults();
	void showTripList();
	void cancelCurrentRequest();
	void routePlannerSelectStation(bool isFromStation,Station* selectedStation);

	bool OnAppInitializing(Osp::App::AppRegistry& appRegistry);
	bool OnAppTerminating(Osp::App::AppRegistry& appRegistry, bool forcedTermination = false);
	void OnForeground(void){}
	void OnBackground(void){}
	void OnLowMemory(void){}
	void OnBatteryLevelChanged(Osp::System::BatteryLevel batteryLevel){}
	void OnScreenOn (void){}
	void OnScreenOff (void){}

	void getFromInternet(const String* const from,const String* const to);

	void OnTransactionReadyToRead(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	void OnTransactionAborted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, result r);
	void OnTransactionReadyToWrite(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	void OnTransactionHeaderCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs);
	void OnTransactionCompleted(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction);
	void OnTransactionCertVerificationRequiredN(Osp::Net::Http::HttpSession& httpSession, Osp::Net::Http::HttpTransaction& httpTransaction, Osp::Base::String* pCert);

};

#endif
