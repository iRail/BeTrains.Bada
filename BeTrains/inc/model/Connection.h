/*
 * Connection.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Model/Vehicle.h"
#include "Model/ConnectionNode.h"

class Connection {
public:
	Connection();
	virtual ~Connection();

	//setters
	void setVehicle(Vehicle* vehicle);
	void setStartNode(ConnectionNode* start);
	void setEndNode(ConnectionNode* end);

	//getters
	Vehicle* getVehicle() const;
	ConnectionNode* getStartConnectionNode() const;
	ConnectionNode* getEndConnectionNode() const;

private:
	Vehicle* 		_vehicle; 		//ownership
	ConnectionNode*	_startNode; 	//ownership
	ConnectionNode* _endNode; 		//ownership
};

#endif /* CONNECTION_H_ */
