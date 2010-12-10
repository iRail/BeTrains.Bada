/*
 * Controller.h
 *
 *  Created on: 10-dec-2010
 *      Author: B
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "View/IView.h"

class Controller {
public:
	Controller();
	virtual ~Controller();
	void addView(IView *view);
};

#endif /* CONTROLLER_H_ */
