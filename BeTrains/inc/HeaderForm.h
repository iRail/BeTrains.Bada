/*
 * HeaderForm.h
 *
 *  Created on: 10 sep. 2011
 *      Author: Jan
 */

#ifndef HEADERFORM_H_
#define HEADERFORM_H_

#include <FBase.h>
#include <FUi.h>
using namespace Osp::Ui;

class HeaderForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IOrientationEventListener
{

// Construction
public:
	HeaderForm(void);
	virtual ~HeaderForm(void);
	bool Initialize(bool leftbutton=false,bool rightbutton=false);
private:
	int settings;
// Implementation
protected:

public:
	virtual result OnInitializing(int index);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	void OnOrientationChanged(const Control& source, OrientationStatus orientationStatus);
	/*
	 * Action id's
	 */

	static const int HEADER_ID_LIVEBOARD = 0;
	static const int HEADER_ID_ROUTE_PLANNER = 1;

};

#endif /* HEADERFORM_H_ */
