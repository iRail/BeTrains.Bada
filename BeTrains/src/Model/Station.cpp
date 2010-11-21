/*
 * Station.cpp
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#include "Model/Station.h"

Station::~Station() {
}

int Station::getLatitude() const {
	return latitude;
}
int Station::getLongtitude() const{
	return longtitude;
}
String const & Station::getCountry() const{
	return country;
}
String const & Station::getName() const{
	return name;
}
