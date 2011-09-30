/*
 * Request.cpp
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/Request.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::App;

Request::Request():
	_from(null),
	_to(null),
	_pDateTime(null),
	_isDepart(true)

{
	_trips.Construct(10);
	_errors.Construct(2);
}

Request::~Request() {
	clear();
}

//setters
void Request::setFromStation(Station* station){
	_from = station;
}
void Request::setToStation(Station* station){
	_to = station;
}
void Request::setDateTime(DateTime dateTime){
	if(_pDateTime)
		delete _pDateTime;
	_pDateTime = new DateTime(dateTime);
}
void Request::setIsDepart(bool isDepart){
	_isDepart = isDepart;
}

//getters
//doesnt give back a copy of the pointer, but a reference to it
Station*& Request::getFromStation(){
	return _from;
}

Station*& Request::getToStation(){
	return _to;
}

DateTime* Request::getDateTime() const{
	return _pDateTime;
}

bool Request::isDepart() const{
	return _isDepart;
}

ArrayListT<Trip*>* Request::getTrips(){
	return &_trips;
}

//methods
void Request::switchStations(){
	Station* h = _from;
	_from = _to;
	_to = h;
}

void Request::clearTrips(){
	Trip* trip = null;
	AppLogDebug("delete all current trips");
	for(int i=0;i<_trips.GetCount();i++){
		_trips.GetAt(i,trip);
		delete trip;
	}
	_trips.RemoveAll();
}

void Request::clearTime(){
	if(_pDateTime){
		delete _pDateTime;
		_pDateTime = null;
	}
}

void Request::clear(){
	_from = null;
	_to = null;
	_isDepart = true;
	clearTime();
	clearTrips();
}

bool Request::validate(){
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	_errors.RemoveAll();
	bool validate = true;
	if(_from == null){
		validate = false;
		String error;
		appRes->GetString(L"ERROR_FROM", error);
		_errors.Add(error);
	}
	if(_to == null){
		validate = false;
		String error;
		appRes->GetString(L"ERROR_TO", error);
		_errors.Add(error);
	}
	if(_to == _from && _to != null){
		validate = false;
		String error;
		appRes->GetString(L"ERROR_SAME_STATIONS", error);
		_errors.Add(error);
	}
	return validate;
}

Osp::Base::Collection::ArrayListT<Osp::Base::String>* Request::getErrors(){
	return &_errors;
}
