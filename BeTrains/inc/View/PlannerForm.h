
#ifndef _PLANNERFORM_H_
#define _PLANNERFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "View/BeTrains.h"
class BeTrains;

class PlannerForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::IActionEventListener
{
private:
		enum Constants{ACTION_SEARCH,ACTION_BACK};
public:
	PlannerForm(void);
	virtual ~PlannerForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
	void searchAction(BeTrains* app);
};

#endif
