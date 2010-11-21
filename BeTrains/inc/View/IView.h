/*
 * IView.h
 *
 *  Created on: 21-nov-2010
 *  Author: Bart Bruynooghe
 */

#ifndef IVIEW_H_
#define IVIEW_H_

class IView {
public:
	IView();
	virtual ~IView();
	virtual void update()=0;
};

#endif /* IVIEW_H_ */
