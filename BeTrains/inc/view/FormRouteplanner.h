#ifndef _FormRouteplanner_H_
#define _FormRouteplanner_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"
#include "model/Request.h"
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

	virtual result 	OnInitializing(void);
	virtual result 	OnTerminating(void);

	void 			RequestRedraw (bool show=true) const;

	//Action performed Listener
	virtual void 	OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	virtual void 	recalculateComponents();

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
	 * action id's
	 */
	static const int SEARCH_ACTION = 301;
	static const int CLEAR_ACTION = 302;
	static const int IS_DEPARTURE = 304;
	static const int IS_ARRIVAL = 305;
	static const int SWITCH_ACTION = 306;
	static const int UNCHECKED = 307;

private:
	//DATA
	Request* 				request;

	//Compontents
	EditField* 				fromStationEditField;
	EditField* 				toStationEditField;
	DateTimePicker* 		dateTimePicker;
	Button* 				switchStationsButton;
	EditField* 				editTimeDateField;
	CheckButton * 			isDepart;
	CheckButton * 			isArrivial;
	ScrollPanel*			scrollPanel;
};

#endif	//_FormRouteplanner_H_
