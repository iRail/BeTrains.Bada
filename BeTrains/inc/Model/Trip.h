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
	TimeSpan *duration; //owernership
	ArrayListT<Connection*> connections; //ownership over all connection 's
public:
	//if duration is not defined like this an error arises
	Trip() :
		duration(new TimeSpan(0, 0, 0))
	{
		connections.Construct();
	}
	virtual ~Trip();
	TimeSpan *getDuration() const;
	void setDuration(int seconds);
	ArrayListT<Connection*> * getConnections();
	bool operator==(const Trip &c2) const;
	Trip & operator=(const Trip &c2);
	bool operator!=(const Trip &c2) const;
};

#endif /* TRIP_H_ */
