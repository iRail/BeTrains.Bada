/*
 * DistanceAndStation.h
 *
 *  Created on: 17-feb-2011
 *      Author: B
 */

#ifndef DISTANCEANDSTATION_H_
#define DISTANCEANDSTATION_H_

#include <FBase.h>
#include "Model/Station.h"

using namespace Osp::Base::Utility;

class DistanceAndStation {
public:
	DistanceAndStation(Station* st,double longitude,double latitude):station(st){
		//Spherical Law of Cosines
		//source: http://www.movable-type.co.uk/scripts/latlong.html
		//form d = acos(sin(lat1).sin(lat2)+cos(lat1).cos(lat2).cos(long2-long1)).R
		double lat1 = st->getLatitude()*3.14/180.0;
		double lat2 = latitude*3.14/180.0;
		double long1 = st->getLongitude()*3.14/180.0;
		double long2 = longitude*3.14/180.0;
		//RADIUS = 6371KM
		distance = Math::Acos(Math::Sin(lat1)*Math::Sin(lat2)+Math::Cos(lat1)*Math::Cos(lat2)*Math::Cos(long2-long1))*6371;
		distance = (Math::Round(distance*10.0))/10.0; // rounds up to xxx.x km
	}
	virtual ~DistanceAndStation(){}
	Station* getStation(){return station;}
	double getDistance(){return distance;}
private:
	Station* station;
	double distance;
	static const double DEG_TO_RAD = 0.017453292519943295769236907684886;
	static const double EARTH_RADIUS_IN_METERS = 6372797.560856;

};

#endif /* DISTANCEANDSTATION_H_ */
