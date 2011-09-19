#ifndef _FormLiveboard_H_
#define _FormLiveboard_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"
#include "model/LiveBoardRequest.h"

class FormLiveboard :
	public HeaderForm,
	public Osp::Ui::ITouchEventListener,
	public ITimeChangeEventListener
{

// Construction
public:
	FormLiveboard(void);
	virtual ~FormLiveboard(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Osp::Ui::Control& source, int actionId);
	void RequestRedraw (bool show=true) const;
	/*
	 * ITouchEventListeners
	 */
	void OnTouchDoublePressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	void OnTimeChanged(const Osp::Ui::Control& source, int hour, int minute);
	void OnTimeChangeCanceled(const Osp::Ui::Control& source);
	/*
	 * Action id's
	 */

	static const int SEARCH_ACTION 		= 301;
	static const int CLEAR_ACTION 		= 302;
private:
	/*
	 * Data
	 */
	LiveBoardRequest*					liveBoardRequest;

	/*
	 * Controls
	 */
	Osp::Ui::Controls::EditField* 		stationEditField;
	Osp::Ui::Controls::EditTime*		editTime;
};

#endif	//_FormLiveboard_H_
