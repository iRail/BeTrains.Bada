/*
 * IRoutePlannerController.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef IROUTEPLANNERCONTROLLER_H_
#define IROUTEPLANNERCONTROLLER_H_

class IRoutePlannerController {
public:
	IRoutePlannerController();
	virtual ~IRoutePlannerController();
	virtual void getTrainInfo()=0;
	virtual void nextTrains()=0;
	virtual void previousTrains()=0;
	virtual void switchStations()=0;
	virtual void switchDepartArrival()=0;
};

#endif /* IROUTEPLANNERCONTROLLER_H_ */
