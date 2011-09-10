/*
 * ConnectionNode.cpp
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/ConnectionNode.h"

using namespace Osp::Base;

ConnectionNode::ConnectionNode():
	_delay(TimeSpan(0))
{
}

ConnectionNode::~ConnectionNode() {
}

void ConnectionNode::setDateTime(DateTime dateTime){
	_dateTime = dateTime;
}
void ConnectionNode::setDelay(TimeSpan delay){
	_delay = delay;
}
void ConnectionNode::setPlatform(String platform){
	_platform = platform;
}
void ConnectionNode::setStation(Station* station){
	_station = station;
}

DateTime ConnectionNode::getDateTime() const{
	return _dateTime;
}
TimeSpan ConnectionNode::getDelay() const{
	return _delay;
}
String ConnectionNode::getPlatform() const{
	return _platform;
}
Station* ConnectionNode::getStation() const{
	return _station;
}
