/*
 * Vehicle.cpp
 *
 *  Created on: 24-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/Vehicle.h"

using namespace Osp::Base;

Vehicle::Vehicle(String name):
	_name(name)
{}

Vehicle::~Vehicle(){}

String Vehicle::getName() const{
	return _name;
}
