/*
 * Request.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Request.h"

Request::~Request() {
	delete dateTime;
	Trip* trip;
	for(int i=0;i<results.GetCount();i++){
		results.GetAt(i,trip);
		delete trip;
	}
}

void Request::switchStation() {
	Station *h = fromStation;
	fromStation = toStation;
	toStation = h;
}
void Request::toggleDepartArrival() {
	departure = !departure;
}

void Request::setDateTime(DateTime* dateTime_) {
	if(dateTime == null) dateTime = new DateTime();
	dateTime = dateTime_;
}

DateTime *Request::getDateTime() const {
	return dateTime;
}

void Request::setFromStation(Station *station) {
	fromStation = station;
}

Station *Request::getFromStation() const {
	return fromStation;
}

void Request::setToStation(Station *station) {
	toStation = station;
}

Station * Request::getToStation() const {
	return toStation;
}

ArrayListT<Trip*> * Request::getResults(){
	return &results;
}

bool Request::operator==(const Request &c2) const {
	return fromStation == c2.getFromStation()
			&& toStation == c2.getToStation();
	//TODO question is it neccessary times and dates need to be equald apon
}

Request & Request::operator=(const Request &c2) {
	fromStation = c2.getFromStation();
	toStation = c2.getToStation();
	departure = c2.isDeparture();
	dateTime = new DateTime(*(c2.getDateTime()));
	//TODO results copy constructor
	return *this;
}

bool Request::operator!=(const Request &c2) const {
	return !((*this) == c2);
}
