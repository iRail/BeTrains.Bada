/*
 * Station.h
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#ifndef STATION_H_
#define STATION_H_

#include <FBase.h>

class Station: public Osp::Base::Object {
public:
	Station(double latitude,double longitude,Osp::Base::String name,Osp::Base::String id);
	virtual ~Station();

	//setters
	//void setLocation(double latitude,double longitude);
	//void setName(Osp::Base::String name);
	//void setId(Osp::Base::String id);

	//getters
	double getLatitude() const;
	double getLongitude() const;
	Osp::Base::String getName() const;
	Osp::Base::String* getNameN();
	Osp::Base::String getId() const;

	//inherit from Object
	bool Equals (const Object &obj) const;
	int GetHashCode (void) const;

private:
	double _latitude;
	double _longitude;
	Osp::Base::String _name;
	Osp::Base::String _id;
};

#endif /* STATION_H_ */
