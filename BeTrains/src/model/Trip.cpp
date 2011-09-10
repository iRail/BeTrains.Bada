/*
 * Trip.cpp
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/Trip.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

Trip::Trip():
	_duration(TimeSpan(0))
{
	_connections.Construct(10);
}

Trip::~Trip() {
	Connection* conn = null;
	for(int i=0;i<_connections.GetCount();i++){
		_connections.GetAt(i,conn);
		delete conn;
	}
}

//setters
void Trip::setDuration(TimeSpan duration){
	_duration = duration;
}

//getters
ArrayListT<Connection*>* Trip::getConnections(){
	return &_connections;
}
Osp::Base::TimeSpan Trip::getDuration(){
	return _duration;
}
