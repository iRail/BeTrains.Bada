/*
 * Connection.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <FBase.h>
#include "ConnectionNode.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

class Connection {
private:
	TimeSpan* timeBetween; //ownership
	String* vehicleName; //ownership
	String* vehicleType; //ownership
	ConnectionNode* startNode; //ownership
	ConnectionNode* endNode; //ownership
public:
	Connection()
		:timeBetween(null),startNode(null),endNode(null),vehicleName(null),vehicleType(null){
	}
	virtual ~Connection();

	void setTimeBetween(TimeSpan *timeBetween_);
	TimeSpan * getTimeBetween()const;
	void setVehicleName(String *name);
	String* getVehicleName()const;
	void setVehicleType(String *type);
	String* getVehicleType()const;
	void setStartNode(ConnectionNode * node);
	ConnectionNode * getStartNode()const;
	void setEndNode(ConnectionNode * node);
	ConnectionNode * getEndNode()const;

	bool operator==(const Connection &c2)const;
	Connection& operator=(const Connection &c2);
	bool operator!=(const Connection &c2)const;

};

#endif /* CONNECTION_H_ */
