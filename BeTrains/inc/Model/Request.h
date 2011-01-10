/*
 * Request.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */
#ifndef REQUEST_H_
#define REQUEST_H_

#include <FBase.h>
#include "Station.h"
#include "Trip.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

class Request {
private:
	DateTime* dateTime; //dateTime ownership
	bool departure;
	Station* fromStation; //fromStation: no ownership
	Station* toStation; //toStation: no ownership
	ArrayListT<Trip*> results; //ownership over all connection 's
public:
	Request(Station *fromStation_, Station *toStation_) :
		fromStation(fromStation_), toStation(toStation_),dateTime(null)
	{
		results.Construct();
	}
	virtual ~Request();
	void switchStation();
	void toggleDepartArrival();

	//getters and setters
	void setDateTime(DateTime* dateTime_);
	DateTime *getDateTime()const;
	void setFromStation(Station *station);
	Station *getFromStation()const;
	void setToStation(Station *station);
	Station *getToStation()const;
	bool isDeparture()const{ return departure; }
	ArrayListT<Trip*> * getResults();

	bool operator==(const Request &c2) const;
	Request & operator=(const Request &c2);
	bool operator!=(const Request &c2) const;
};

#endif /* REQUEST_H_ */
