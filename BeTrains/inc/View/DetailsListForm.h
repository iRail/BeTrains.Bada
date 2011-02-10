
#ifndef _DETAILSLISTFORM_H_
#define _DETAILSLISTFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Model/Trip.h"


class DetailsListForm :
	public Osp::Ui::Controls::Form
{

// Construction
public:
	DetailsListForm(void);
	void update(Trip *trip);
	virtual ~DetailsListForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:

};

#endif
