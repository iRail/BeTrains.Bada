/*
 * IView.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef IVIEW_H_
#define IVIEW_H_

#include "Model/Station.h"

class IView {
public:
	virtual void update()=0;
	void showMainMenu();
	void showMap();
	void showRoutePlanner();
	void showRoutePlannerStationSelector(Station *selectedStation,Osp::Base::Collection::ArrayListT<Station *> * stations);
	void showRoutePlannerResults();
};

#endif /* IVIEW_H_ */
