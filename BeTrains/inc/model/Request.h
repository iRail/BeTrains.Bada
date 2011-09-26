/*
 * Request.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef REQUEST_H_
#define REQUEST_H_

#include <FBase.h>
#include "Model/Station.h"
#include "Model/Trip.h"


class Request {
public:
	Request();
	virtual ~Request();

	//setters
	void setFromStation(Station* station);
	void setToStation(Station* station);
	void setDateTime(Osp::Base::DateTime dateTime);
	void setIsDepart(bool isDepart);

	//getters
	// get station may not be const, because we want to change the value from outside
	Station*& getFromStation();
	Station*& getToStation();
	Osp::Base::DateTime* getDateTime() const;
	bool isDepart() const;
	Osp::Base::Collection::ArrayListT<Trip*>* getTrips();
	Osp::Base::Collection::ArrayListT<Osp::Base::String>* getErrors();

	//methods
	void switchStations();
	void clearTrips(); 	//removes all trips
	void clearTime(); 	//removes time *set to now
	void clear(); 		//removes all settings
	bool validate();	//returns false if not correct

private:
	Station* 									_from;
	Station* 									_to;
	Osp::Base::DateTime* 						_pDateTime; //ownership
	bool 										_isDepart;
	Osp::Base::Collection::ArrayListT<Trip*> 	_trips; //ownership
	Osp::Base::Collection::ArrayListT<String>	_errors;
};

#endif /* REQUEST_H_ */
