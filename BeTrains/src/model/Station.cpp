/*
 * Station.cpp
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/Station.h"

using namespace Osp::Base;

Station::Station(double latitude,double longitude,Osp::Base::String name,Osp::Base::String id):
		_latitude(latitude),
		_longitude(longitude),
		_name(name),
		_id(id)
{
}

Station::~Station() {
}

//setters does not apply to this class
/*
void Station::setLocation(double latitude,double longitude){
	_latitude = latitude;
	_longitude = longitude;
}
void Station::setName(String name){
	_name = name;
}
void Station::setId(String id){
	_id = id;
}
*/
//getters
double Station::getLatitude() const{
	return _latitude;
}
double Station::getLongitude() const{
	return _longitude;
}
String Station::getName() const{
	return _name;
}
String* Station::getNameN(){
	return &_name;
}
String Station::getId() const{
	return _id;
}

bool Station::Equals (const Object &obj) const{
	return false;
	//return (_name == (static_cast<Station> (obj)).getName());
}
int Station::GetHashCode (void) const{
	return 1;
}
