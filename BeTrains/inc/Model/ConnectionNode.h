/*
 * ConnectionNode.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef CONNECTIONNODE_H_
#define CONNECTIONNODE_H_

#include <FBase.h>
#include <FBaseDateTime.h>
#include "Station.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

class ConnectionNode {
private:
	String* platform; //ownership
	TimeSpan* delay; //ownership
	DateTime* dateTime; //ownership
	Station* station; //no ownership
public:
	ConnectionNode() :
		platform(null),delay(null),dateTime(null),station(null) {
	}
	virtual ~ConnectionNode();

	void setStation(Station *station);
	Station * getStation() const;

	void setPlatform(String* platform);
	String* getPlatform() const;

	void setDelay(TimeSpan* delay_);
	TimeSpan * getDelay()const;

	void setDateTime(DateTime * dateTime_);
	DateTime * getDateTime()const;

	bool operator==(const ConnectionNode &c2) const;

	ConnectionNode & operator=(const ConnectionNode &c2);

	bool operator!=(const ConnectionNode &c2) const;
};

#endif /* CONNECTIONNODE_H_ */
