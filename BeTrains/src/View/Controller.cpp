/*
 * Controller.cpp
 *
 *  Created on: 10-dec-2010
 *      Author: B
 */

#include "Controller/Controller.h"

Controller::Controller() {
	// TODO Auto-generated constructor stub

}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

void Controller::addView(IView *view){
	view->update();
}
