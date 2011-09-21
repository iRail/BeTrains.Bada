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
	_time = null;
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
	results.RemoveAll();
}

Station*& LiveBoardRequest::getStation()
{
	return _station;
}

DateTime* LiveBoardRequest::getDateTime() const
{
	return _time;
}

void LiveBoardRequest::setStation(Station *station)
{
	_station = station;
}

void LiveBoardRequest::setDateTime(Osp::Base::DateTime time)
{
	if(_time)
		delete _time;
	_time = new DateTime(time);
}

void LiveBoardRequest::clearTime(){
	if(_time){
		delete _time;
		_time = null;
	}
}

Osp::Base::Collection::ArrayListT<LiveBoardResult*>* LiveBoardRequest::getResults(){
	return &results;
}

void LiveBoardRequest::clear(){
	_station = null;
	clearTime();
}
