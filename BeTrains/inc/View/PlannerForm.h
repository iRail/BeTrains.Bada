
#ifndef _PLANNERFORM_H_
#define _PLANNERFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "View/BeTrains.h"
#include "Model/Request.h"

class PlannerForm :
	public Osp::Ui::Controls::Form,
	public Osp::Ui::ITouchEventListener,
	public Osp::Ui::IActionEventListener,
	public Osp::Ui::IDateTimeChangeEventListener
{
private:
	enum Constants{ACTION_SEARCH,ACTION_BACK};
	Osp::Ui::Controls::EditField* from;
	Osp::Ui::Controls::EditField* to;
	Osp::Ui::Controls::Button* switchStationsButton;
	Osp::Ui::Controls::DateTimePicker* dateTimePicker; //ownerships
	Osp::Ui::Controls::EditField* editTimeDateField;
	Osp::Ui::Controls::CheckButton* departCheckButton;
	Request* request;
public:
	PlannerForm();
	void update(Request* request);
	virtual ~PlannerForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);
	void OnActionPerformed(const Osp::Ui::Control &source, int actionId);

	void OnTouchDoublePressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

	void OnDateTimeChangeCanceled (const Osp::Ui::Control &source);
	void OnDateTimeChanged (const Osp::Ui::Control &source, int year, int month, int day, int hour, int minute);

};

#endif
