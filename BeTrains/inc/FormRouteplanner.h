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
	public HeaderForm,
	public Osp::Ui::ITouchEventListener,
	public Osp::Ui::IDateTimeChangeEventListener
{

// Construction
public:
	FormRouteplanner(void);
	virtual ~FormRouteplanner(void);
	bool Initialize(void);

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);

	//Action performed Listener
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);

	//IDateTimeChangeEventListener
	virtual void 	OnDateTimeChangeCanceled (const Osp::Ui::Control &source);
	virtual void 	OnDateTimeChanged (const Osp::Ui::Control &source, int year, int month, int day, int hour, int minute);

	//ITouchEventListener
	virtual void 	OnTouchDoublePressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

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
	static const int SEARCH_ACTION = 301;
	static const int CLEAR_ACTION = 302;
	static const int SWITCH_ACTION = 303;
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
