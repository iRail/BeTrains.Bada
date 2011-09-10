/*
 * File: Utils.h
 *
 * Abstract: The static utilities used by BuddyFix
 * Version: 1.0
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * 	http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <FBase.h>
#include <FUi.h>
#include <FLocations.h>

#include "AppData.h"
using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Locations;
using namespace Osp::Base::Runtime;

class WaitingPopup :
	public Osp::Ui::Controls::Popup,
	public IAnimationEventListener,
	public Osp::Ui::IActionEventListener
{
public:
	WaitingPopup();
	result Construct(const Osp::Base::String& title,RequestId cancelRequestId);
	result ShowAnimation();
	~WaitingPopup(void);
	void OnAnimationStopped(const Control& source){__pAnimation->Play();};
	void OnActionPerformed (const Osp::Ui::Control &source, int actionId);


private:
	static const int CANCEL_BUTTON_ID = 300;
	RequestId							__cancelRequestId;
	Osp::Base::Collection::ArrayList* 	__pAnimationFrameList;
	Osp::Ui::Controls::Animation* 		__pAnimation;
	Osp::Ui::Controls::Button* 			__pCancelButton;
	//Osp::Ui::Controls::Form*			__pParentForm;
};
/*
class ListPopup: public Osp::Ui::Controls::Popup
{
public:
	ListPopup(const Osp::Base::String& title, SlidableList* pList, int actionId1, int actionId2, IActionEventListener *pListener);
	~ListPopup(void);

private:
	Button* __pButton1;
	Button* __pButton2;
	SlidableList* __pList;
};

class IconPopup: public Osp::Ui::Controls::Popup
{
public:
	IconPopup(const Osp::Base::String& title, IconList* pList, int actionId, IActionEventListener *pListener);
	~IconPopup(void);

private:
	//static const int POPUP_BUTTON_ADD = 400;
	Button* __pButton;
	IconList* __pList;
};

*/
class Utils:
	public ITimerEventListener
{
public:
	Utils();
	~Utils();
	//Pop-up utility functions
	static void ShowMessage(const String &title, const String &message);
	static void ShowTimeoutMessage(const String &title, const String &message, const long &timeout);
	static void ShowTimeoutNote(const String &message, const long &timeout);

	//void ShowListPopup(const Osp::Base::String& title, SlidableList* pList, int actionId1, int actionId2, IActionEventListener *pListener);
	//void CloseListPopup(void);
	//void ShowIconPopup(const Osp::Base::String& title, IconList* pList, int actionId, IActionEventListener *pListener, int buddyIndex);
	//int CloseIconPopup(void);

	//Global utility functions
	static Bitmap* GetBitmapN(const Osp::Base::String& name);
	static String GetRelativeLocationFromCoordinates(const Coordinates &myCoords, const Coordinates &theirCoords);
	static String GetRelativeTimeFromTimeStamp(const long long timeStamp);
	static DateTime ConvertUtcTimeToStardardTime(const long long timeStamp);
	//static DateTime ConvertUTCTimeToStandardTime(DateTime dt);
	//static DateTime ConvertStandardTimeToUtcTime(DateTime &time);



	static String formatTime(DateTime time);
	static String formatTime(TimeSpan duration);
	static String formatDelay(TimeSpan delay);
	static String formatDate(DateTime time);


private:
	void OnTimerExpired(Timer &timer);
public:
	static const RequestId UTILS_TIMEOUT = 300;

private:
	//ListPopup*		__pListPopup;
	//WaitingPopup*	__pWaitingPopup;
	//IconPopup*		__pIconPopup;
	//int				__iconPopupBuddyIndex;
	Form*			__pParentForm;
	int				__timeoutValueInSec;
	Timer*			__pTimer;
};
#endif /* UTILS_H_ */
