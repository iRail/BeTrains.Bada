/*
 * Controller.cpp
 *
 *  Created on: 10-dec-2010
 *      Author: Bart Bruynooghe
 */

#include "Controller/Controller.h"

Controller::Controller() {
	// Prints all station names
	/*
	for(int i=0;i<stations->GetCount();i++){
		Station *s;
		stations->GetAt(i,s);
		AppLog("station: %S",s->getName()->GetPointer());
	}
	*/
	//test find station
	/*
	String stname = L"Aalst";
	Station * st = getStation(stname);
	if(st){
		AppLog("station found %S country:%S",st->getName()->GetPointer(),st->getCountry()->GetPointer());
		AppLog("station location %S",Float::ToString(st->getLongtitude()).GetPointer());
	}else{
		AppLog("station not found");
	}
	*/

	//PRINTS info about trip
	testRoutePlanner();

}

Controller::~Controller() {

}

void Controller::addView(IView *view){
	view->update();
}

void Controller::getTrainInfo(Request * const req){
	//TODO
}
void Controller::nextTrains(){
	//TODO
}
void Controller::previousTrains(){
	//TODO
}
