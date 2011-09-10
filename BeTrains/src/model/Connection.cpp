/*
 * Connection.cpp
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/Connection.h"

Connection::Connection():
	_vehicle(null),
	_startNode(null),
	_endNode(null)
{
}

Connection::~Connection() {
	if(_vehicle)
		delete _vehicle;
	if(_startNode)
		delete _startNode;
	if(_endNode)
		delete _endNode;
}

//setters
void Connection::setVehicle(Vehicle* vehicle){
	if(_vehicle)
		delete _vehicle;
	_vehicle = vehicle;
}
void Connection::setStartNode(ConnectionNode* start){
	if(_startNode)
		delete _startNode;
	_startNode = start;
}
void Connection::setEndNode(ConnectionNode* end){
	if(_endNode)
		delete _endNode;
	_endNode = end;
}

//getters
Vehicle* Connection::getVehicle() const{
	return _vehicle;
}
ConnectionNode* Connection::getStartConnectionNode() const{
	return _startNode;
}
ConnectionNode* Connection::getEndConnectionNode() const{
	return _endNode;
}
