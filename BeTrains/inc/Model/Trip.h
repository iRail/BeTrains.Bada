/*
 * Trip.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef TRIP_H_
#define TRIP_H_

#include <FBase.h>
#include "Connection.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

class Trip {
private:
	TimeSpan duration;
	//ArrayList<Connection> connections;
public:
	//if not duration is not defined like this an error arises
	Trip() :
		duration(TimeSpan(0, 0, 0))
	{
		//connections.Construct();
	}
	virtual ~Trip();
	TimeSpan getDuration();
	void setDuration(int seconds);
	//TODO add/get connection method
	void addConnection(Connection &conn);

	bool operator==(const Trip &c2) const {
		return false;
		//TODO operator overloading implementation
	}

	Trip & operator=(const Trip &c2) {
		//TODO operator overloading implementation
		return *this;
	}

	bool operator!=(const Trip &c2) const {
		return true;
		//TODO operator overloading implementation
	}

};

#endif /* TRIP_H_ */
