/*
 * Controller.h
 *
 *  Created on: 10 sep. 2011
 *  Author: Jan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FSocial.h>

#include "view/HeaderForm.h"
#include "view/FormLiveboard.h"
#include "view/FormRouteplanner.h"
#include "view/SelectStationForm.h"
#include "view/RoutePlannerResults.h"
#include "view/LiveBoardResults.h"

#include "controller/RouteRequestManager.h"
#include "controller/LiveBoardRequestManager.h"

using namespace Osp::Ui::Controls;

class Controller {


private:
	Controller();
	/*
	 * Forms
	 */
	FormLiveboard* 			formLiveBoard;
	FormRouteplanner*  		formRoutePlanner;
	SelectStationForm* 		selectStationForm;
	RoutePlannerResults*	routePlannerResults;
	LiveBoardResults*		liveBoardResults;

	Form* 					prevForm;
	Form* 					currentForm;

	/*
	 * content managers
	 * downloading from irail
	 */
	RouteRequestManager*		routeRequestManager;
	LiveBoardRequestManager*	liveBoardRequestManager;

	void 					SetCurrentForm(Form*);

public:
	virtual 				~Controller();
	static 					Controller* instance;
	static 					Controller* GetInstance();

	//switch forms
	void 					switchToFormLiveBoard();
	void 					switchToFormRoutePlanner();
	void 					switchToLiveBoardResults();
	void 					switchToRoutePlannerResults();
	void 					selectStation(Station* &station); //Station* station
	void					setPreviousForm(); //GO BACK

	//actions

	void					retrieveRoutePlannerResults(bool addToResults=false);
	void					retrieveLiveBoardResults(bool addToResults=false);
	void 					clearRoutePlanner();
	void 					clearLiveboard();
	void 					setRoutePlannerTime(DateTime time);
	void 					setLiveboardTime(DateTime time);
	void					cancelRequest();
	void 					switchRequestStations();
	void 					setIsDeparture(bool isDeparture);
	void					saveToCalendar(int index); //saves from index from current results to calendar

	void					newRequest();
	void					newLiveboardRequest();
	void 					getMoreResults();

};

#endif /* CONTROLLER_H_ */
