/*
 * ConnectionNode.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef CONNECTIONNODE_H_
#define CONNECTIONNODE_H_

#include <FBase.h>
#include "Station.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

class ConnectionNode {
private:
	int platform;
	TimeSpan delay;
	DateTime dateTime;
	Station station;
public:
	ConnectionNode() :
		delay(TimeSpan(0, 0, 0)) {
	}
	virtual ~ConnectionNode();

	void setStation(Station const &station);
	Station getStation() const;

	void setPlatform(int platform);
	int getPlatform();

	void setDelay(int seconds);
	TimeSpan getDelay();

	void setDateTime(int seconds);
	DateTime getDateTime();

	bool operator==(const ConnectionNode &c2) const {
		return false;
		//TODO operator overloading implementation
	}

	ConnectionNode & operator=(const ConnectionNode &c2) {
		//TODO operator overloading implementation
		return *this;
	}

	bool operator!=(const ConnectionNode &c2) const {
		return true;
		//TODO operator overloading implementation
	}
};

#endif /* CONNECTIONNODE_H_ */
