#ifndef _FormRouteplanner_H_
#define _FormRouteplanner_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"

class FormRouteplanner :
	public HeaderForm
{

// Construction
public:
	FormRouteplanner(void);
	virtual ~FormRouteplanner(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	/*
	 * action id's
	 */
	static const int SEARCH_ACTION = 10;
};

#endif	//_FormRouteplanner_H_
