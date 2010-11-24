/*
 * ConnectionNode.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/ConnectionNode.h"

ConnectionNode::~ConnectionNode() {
	if(delay) delete delay;
	if(dateTime) delete dateTime;
}

void ConnectionNode::setStation(Station *station){
	this->station = station;
}
Station * ConnectionNode::getStation() const{
	return station;
}

void ConnectionNode::setPlatform(int platform){
	this->platform = platform;
}
int ConnectionNode::getPlatform() const{
	return platform;
}

void ConnectionNode::setDelay(int seconds){
	if(delay != null) delete delay;
	delay = new TimeSpan(seconds*1000);
}

TimeSpan * ConnectionNode::getDelay() const{
	return delay;
}

void ConnectionNode::setDateTime(int seconds){
	if(dateTime == null) dateTime = new DateTime();
	//TODO Convert seconds to date
}

DateTime * ConnectionNode::getDateTime() const{
	return dateTime;
}

bool ConnectionNode::operator==(const ConnectionNode &c2) const {
	return platform == c2.getPlatform() &&
			*dateTime == *c2.getDateTime() &&
			*station == *c2.getStation();
}

ConnectionNode & ConnectionNode::operator=(const ConnectionNode &c2) {
	if(delay != null) delete delay;
	if(dateTime != null) delete dateTime;
	platform = c2.getPlatform();
	delay = new TimeSpan(*c2.getDelay());
	dateTime = new DateTime(*c2.getDateTime());
	station = c2.getStation();//shallow copy because there is a fixed list of stations
	return *this;
}

bool ConnectionNode::operator!=(const ConnectionNode &c2) const {
	return !((*this) == c2);
}
