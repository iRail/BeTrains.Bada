/*
 * Controller.h
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>

#include "HeaderForm.h"
#include "FormLiveboard.h"
#include "FormRouteplanner.h"
#include "SelectStationForm.h"

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

	Form* 					prevForm;
	Form* 					currentForm;

	void 					SetCurrentForm(Form*);


public:
	virtual 				~Controller();
	static 					Controller* instance;
	static 					Controller* GetInstance();

	//switch forms
	void 					switchToFormLiveBoard();
	void 					switchToFormRoutePlanner();
	void 					switchToResultsLiveBoard();
	void 					switchToResultsRoutePlanner();
	void 					selectStation(Station* &station); //Station* station
	void					setPreviousForm(); //GO BACK

	//actions
	void 					returnSelectedStation();

};

#endif /* CONTROLLER_H_ */
