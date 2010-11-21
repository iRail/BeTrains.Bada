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
	DateTime dateTime;
	bool departure;
	Station fromStation;
	Station toStation;
	//TODO arraylist results
	//ArrayList<Trip> results;
public:
	Request(Station const &fromStation_, Station const &toStation_) :
		fromStation(fromStation_), toStation(toStation_) {
		//TODO init construct empty results
	}
	virtual ~Request();
	void switchStation();
	void toggleDepartArrival();
	//TODO add trip method
	//void addTrip(Trip &trip);

	bool operator==(const Request &c2) const {
		return false;
		//TODO operator overloading implementation
	}

	Request & operator=(const Request &c2) {
		//TODO operator overloading implementation
		return *this;
	}

	bool operator!=(const Request &c2) const {
		return true;
		//TODO operator overloading implementation
	}
};

#endif /* REQUEST_H_ */
