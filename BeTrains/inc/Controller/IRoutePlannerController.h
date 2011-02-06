/*
 * IRoutePlannerController.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef IROUTEPLANNERCONTROLLER_H_
#define IROUTEPLANNERCONTROLLER_H_

#include "Model/Request.h"

class IRoutePlannerController{
public:
	virtual void getTrainInfo(Request * const req)=0;
	virtual void nextTrains()=0;
	virtual void previousTrains()=0;
};

#endif /* IROUTEPLANNERCONTROLLER_H_ */
