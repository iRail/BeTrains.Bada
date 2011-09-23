#ifndef _RoutePlannerResults_H_
#define _RoutePlannerResults_H_

#include <FBase.h>
#include <FUi.h>
#include "HeaderForm.h"
#include "model/Request.h"
#include "model/Station.h"
#include "model/Trip.h"

using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base;
using namespace Osp::App;


class RoutePlannerResults :
	public HeaderForm,
	public ITouchEventListener
{

// Construction
public:
	RoutePlannerResults();
	virtual ~RoutePlannerResults(void);
	bool Initialize(void);

	virtual result 	OnInitializing(void);
	virtual result 	OnTerminating(void);

	void 			RequestRedraw (bool show=true)const; //todo, make it a const method

	//Action performed Listener
	virtual void 	OnActionPerformed(const Osp::Ui::Control& source, int actionId);


	/*
	 * ITouchEventListener
	 */
	virtual void 	OnTouchDoublePressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchFocusIn (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchFocusOut (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchLongPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchMoved (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchPressed (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);
	virtual void 	OnTouchReleased (const Osp::Ui::Control &source, const Osp::Graphics::Point &currentPosition, const Osp::Ui::TouchEventInfo &touchInfo);

	void ShowContextMenu(bool show);

	/*
	 * action id's
	 */
	static const int REFRESH_ACTION			= 301;
	static const int BACK_ACTION 			= 302;
	static const int SAVE_CALENDAR_ACTION 	= 303;

	/*
	 * Element id's for custom element
	 */
	static const int TIME_HEADER 			= 401;
	static const int NUMBER_CONNECTIONS 	= 402;
	static const int TOTAL_TIME 			= 403;
	static const int TIME_1					= 404;
	static const int TIME_2					= 405;
	static const int STATION_1				= 406;
	static const int STATION_2				= 407;
	static const int PLATFORM_1				= 408;
	static const int PLATFORM_2				= 409;

private:
	//DATA
	Request* 				request;
	bool*					addToResults;
	enum LIST_ITEMS{LIST_ITEM_STATIONS,LIST_ITEM_TIMES,LIST_ITEM_DELAYS,LIST_ITEM_DURATION,LIST_ITEM_VEHICLE_TYPE,LIST_ITEM_VEHICLE_NAME,LIST_ITEM_NUMBER_CONNECTIONS,LIST_ITEM_DATE};
	enum SUB_LIST_ITEMS{SUBLIST_FROM_TIME,SUBLIST_TO_TIME,SUBLIST_FROM_DELAY,SUBLIST_TO_DELAY,SUBLIST_FROM_STATION,SUBLIST_TO_STATION,SUBLIST_FROM_PLATFORM,SUBLIST_TO_PLATFORM,SUBLIST_VEHICLE};

	//Compontents
	Label*					titleLabel;
	ExpandableList*			list;
	CustomListItemFormat*	format;
	CustomListItemFormat*	subListFormat;
	ContextMenu* 			contextMenu;

	//help methods
	void addTrip(Trip* trip)const;
};

#endif	//_RoutePlannerResults_H_
