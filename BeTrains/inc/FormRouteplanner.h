#ifndef _FormRouteplanner_H_
#define _FormRouteplanner_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"
#include "model/Station.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;


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
	 * Setters
	 */
	void setFromStation(Station* fromStation_);
	void setToStation(Station* toStation_);
	void setDateTime(Osp::Base::DateTime dateTime_);
	void setIsSearchDeparture(bool isSearchDeparture_);

	/*
	 * action id's
	 */
	static const int SEARCH_ACTION = 10;
private:
	//DATA
	Station* fromStation;
	Station* toStation;
	Osp::Base::DateTime dateTime;
	bool isSearchDeparture;

	//Compontents
	EditField* fromStationEditField;
	EditField* toStationEditField;
	DateTimePicker* dateTimePicker;
	Button* switchStationsButton;
	EditField* editTimeDateField;

	CheckButton * isDepart;
	CheckButton * isArrivial;
};

#endif	//_FormRouteplanner_H_
