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
		duration(null)
	{
		connections.Construct(3); //I assume most traintrips don't have more than 3trains: naturaly this don't mean it can't be more
	}
	virtual ~Trip();
	TimeSpan *getDuration() const;
	void setDuration(TimeSpan *duration_);
	ArrayListT<Connection*> * getConnections();
	bool operator==(const Trip &c2) const;
	Trip & operator=(const Trip &c2);
	bool operator!=(const Trip &c2) const;
};

#endif /* TRIP_H_ */
