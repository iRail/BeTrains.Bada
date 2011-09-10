/*
 * LiveBoardRequest.cpp
 *
 *  Created on: 25-apr-2011
 *  Author: Bart Bruynooghe
 */

#include "Model/LiveBoardRequest.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;

LiveBoardRequest::LiveBoardRequest() {
	results.Construct(10); //default size = 10
}

LiveBoardRequest::~LiveBoardRequest() {
	clearResults();
}

void LiveBoardRequest::clearResults(){
	LiveBoardResult* result = null;
	for(int i=0;i<results.GetCount();i++){
		results.GetAt(i,result);
		delete result;
	}
}

Station *LiveBoardRequest::getStation() const
{
	return _station;
}

DateTime LiveBoardRequest::getTime() const
{
	return _time;
}

void LiveBoardRequest::setStation(Station *station)
{
	_station = station;
}

void LiveBoardRequest::setTime(Osp::Base::DateTime time)
{
	_time = time;
}

Osp::Base::Collection::ArrayListT<LiveBoardResult*>* LiveBoardRequest::getResults(){
	return &results;
}
