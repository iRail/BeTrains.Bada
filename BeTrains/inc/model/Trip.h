/*
 * Trip.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef TRIP_H_
#define TRIP_H_

#include <FBase.h>
#include "Model/Connection.h"

using namespace Osp::Base;

class Trip {
public:
	Trip();
	virtual ~Trip();

	//setters
	void setDuration(Osp::Base::TimeSpan duration);

	//getters
	Osp::Base::Collection::ArrayListT<Connection*>* getConnections();
	Osp::Base::TimeSpan getDuration();

private:
	Osp::Base::Collection::ArrayListT<Connection*> _connections; //ownership
	Osp::Base::TimeSpan _duration;
};

#endif /* TRIP_H_ */
