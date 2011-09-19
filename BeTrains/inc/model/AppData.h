/*
 * File: AppData.h
 *
 * Abstract: The singleton class of representing global central data of BuddyFix
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

#ifndef APPDATA_H_
#define APPDATA_H_

#include <FBase.h>
#include <FLocations.h>
#include <FLocales.h>
#include <FIo.h>
#include <FSystem.h>

#include "model/IRailAPI.h"

#include "Model/Request.h"
#include "Model/LiveBoardRequest.h"
#include "Model/Station.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Base::Utility;
using namespace Osp::Graphics;
using namespace Osp::Io;
using namespace Osp::Locations;
using namespace Osp::Locales;
using namespace Osp::System;

class AppData
{
public:
	// The AppData class is a singleton which provides an interface to all the
	// application's data.  Access to data objects should be done through this
	// class (particularly creating/removing/loading)
	static AppData* 	GetInstance();
	void 				DistroyInstance();

	//String ConvertTimeToString(DateTime time);

	//returns null if not found
	Station* 			getStationById(const String& id);

	//returns list of stations, can be used to add station if it does not exists
	ArrayListT<Station*>* getStationList();

	//returns current Route Planner Request
	Request*			getCurrentRequest();
	void 				clearTripListFromCurrentRequest();

	//returns current  Live Board Request�
	LiveBoardRequest* 	getCurrentLiveBoardRequest();
	void				clearLiveBoardResults();
private:
	AppData();
	~AppData();
	result Construct(void);
	result initialiseStations();

	DateTimeFormatter*	__pDtFormatter;

	static AppData*		__pInstance;
	static bool			__instanceFlag;


	//data
	ArrayListT<Station *>	_stations; //ownership
	Request*				_currentRequest; //ownership
	LiveBoardRequest*		_currentLiveBoardRequest; //ownership

};
#endif /* APPDATA_H_ */
