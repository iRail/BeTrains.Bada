/*
 * Request.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Request.h"

Request::Request(){
	fromStation=null;
	toStation=null;
	dateTime= null;
	results.Construct();
}

Request::~Request() {
	if(dateTime !=null) delete dateTime;
	//NO ownership over the 2 stations
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
	if(dateTime != null) delete dateTime;
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

String Request::parseDate(){
	//format ddmmyy with leading zero's
	if(dateTime != null){
		String parsed = L"";
		int day=dateTime->GetDay();
		int year=dateTime->GetYear();
		int month=dateTime->GetMonth();
		if(day<10) parsed = L"0";
		parsed += Integer::ToString(day);
		if(month<10) parsed += L"0";
		parsed += Integer::ToString(month);
		parsed += Integer::ToString(year%100); //gets the last two digits from a year ex 2011 -> 11
		return parsed;
	}
	return L"0";
}

String Request::parseTime(){
	if(dateTime != null){
		String parsed = L"";
		int min=dateTime->GetMinute();
		int hour=dateTime->GetHour();
		if(hour<10) parsed = L"0";
		parsed += Integer::ToString(hour);
		if(min<10) parsed += L"0";
		parsed += Integer::ToString(min);
		return parsed;
	}
	return L"0";
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
