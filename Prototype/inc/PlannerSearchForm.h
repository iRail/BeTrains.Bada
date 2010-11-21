
#ifndef _PLANNERSEARCHFORM_H_
#define _PLANNERSEARCHFORM_H_

#include <FBase.h>
#include <FUi.h>
#include "Constants.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;

class PlannerSearchForm :
	public Osp::Ui::Controls::Form,
 	public Osp::Ui::IActionEventListener,
 	public Osp::Ui::IFocusEventListener,
 	public Osp::Ui::IKeyEventListener,
 	public Osp::Ui::ITouchEventListener,
 	public Osp::Ui::ITouchModeChangedEventListener
{
// Construction
public:
	PlannerSearchForm(void);
	virtual ~PlannerSearchForm(void);
	bool Initialize();
	result OnInitializing(void);
	result OnTerminating(void);

// Implementation
protected:

// Generated call-back functions
public:
	void OnActionPerformed(const Osp::Ui::Control &source, int actionId);
	void OnFocusGained(const Osp::Ui::Control &source);
	void OnFocusLost(const Osp::Ui::Control &source);
	void OnKeyLongPressed(const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode);
	void OnKeyPressed(const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode);
	void OnKeyReleased(const Osp::Ui::Control &source, Osp::Ui::KeyCode keyCode);
	void OnTouchDoublePressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchFocusIn(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchFocusOut(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchLongPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchMoved(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchPressed(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchReleased(const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchModeChanged(const Osp::Ui::Control& source, bool isInTouchMode);
};

#endif
