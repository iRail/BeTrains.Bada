/*
 * Controller.h
 *
 *  Created on: 10-dec-2010
 *  Author: Bart Bruynooghe
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


#include "View/IView.h"
#include "Model/Request.h"
#include "Model/Station.h"
#include "Controller/IRoutePlannerController.h"
#include "Controller/IRailAPI.h"

using namespace Osp::Base::Collection;

class Controller :
	public IRoutePlannerController,
	public IRailAPI
{
public:
	Controller();
	virtual ~Controller();
	void addView(IView *view);
	void getTrainInfo(Request * const req);
	void nextTrains();
	void previousTrains();
};

#endif /* CONTROLLER_H_ */
