/*
 * Vehicle.h
 *
 *  Created on: 24-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <FBase.h>

class Vehicle {
public:
	Vehicle(Osp::Base::String name);
	virtual ~Vehicle();
	Osp::Base::String getName() const;
private:
	Osp::Base::String _name;
};

#endif /* VEHICLE_H_ */
