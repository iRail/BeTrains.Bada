#include <FGraphics.h>
#include <FMedia.h>
#include <FSystem.h>
#include "view/Utils.h"

using namespace Osp::Media;
using namespace Osp::Graphics;
using namespace Osp::System;
using namespace Osp::Base::Collection;


Utils::Utils()
{
}

Utils::~Utils()
{
	AppLogDebug("Utils is destroyed!");
}

Osp::Graphics::Bitmap* Utils::GetBitmapN(const Osp::Base::String& name)
{
	Bitmap* pBitmap = null;
	Image* pImage = new Image();

	String fullname(L"/Res/");
	fullname.Append(name);

	pImage->Construct();
	AppLogDebug("%S",fullname.GetPointer());
	if(fullname.EndsWith(L"jpg"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	else if(fullname.EndsWith(L"bmp"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	else if(fullname.EndsWith(L"png"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_ARGB8888);
	}
	else if (fullname.EndsWith(L"gif"))
	{
		pBitmap = pImage->DecodeN(fullname, BITMAP_PIXEL_FORMAT_RGB565);
	}
	delete pImage;

	return pBitmap;
}

String Utils::GetRelativeLocationFromCoordinates(const Coordinates &myCoords, const Coordinates &theirCoords)
{
	String distString;
	if (&theirCoords == null)
		return L"None";
	else
	{
		if (&myCoords == null)
		{
			// If we don't have our co-ordinates we just return their absolute co-ordinates.
			double latitude = 0, longitude = 0;
			latitude = theirCoords.GetLatitude();
			if (latitude >= 0)
				distString.Format(10, L"N %.2f ", latitude);
			else
				distString.Format(10, L"S %.2f ", -1 * latitude);

			String tmpStr;
			longitude = theirCoords.GetLongitude();
			if (longitude >= 0)
				tmpStr.Format(10, L"W %.2f", longitude);
			else
				tmpStr.Format(10, L"E %.2f", -1 * longitude);
			distString.Append(tmpStr);

			return distString;
		}
		else
		{
			float distance = myCoords.Distance(theirCoords);
			if (distance > 1000)
			{
				distance /= 1000;
				distString.Format(20, L"%.1fkm", distance);
			}
			else
				distString.Format(20, L"%3.0fm", distance);
			return distString;
		}
	}
}

DateTime Utils::ConvertUtcTimeToStardardTime(const long long timestamp)
{
	/*
	DateTime dt;
	LocaleManager localeManager;

	dt.SetValue(TimeSpan(timestamp));
	dt.AddYears(1969);

	localeManager.Construct();
	TimeZone timeZone = localeManager.GetSystemTimeZone();
	DateTime retDt = timeZone.UtcTimeToWallTime(dt);

	return retDt;
	*/
	return DateTime();
}

String Utils::GetRelativeTimeFromTimeStamp(DateTime receivedTime)
{
	DateTime currentTime;
	//DateTime receivedTime;
	String relativeTime;
	int mins = 0;
	int hours = 0;
	int days = 0;

	SystemTime::GetCurrentTime(WALL_TIME, currentTime);
	//receivedTime = Utils::ConvertUtcTimeToStardardTime(timeStamp);

	TimeSpan timeDiff = (currentTime.GetTime() - receivedTime.GetTime());
	days = timeDiff.GetDays();
	hours = timeDiff.GetHours();
	mins = timeDiff.GetMinutes();
	if(days >= 1)
	{
		relativeTime.Format(20, L"%d days ago", days);
	}
	else if (hours > 0)
		relativeTime.Format(20, L"%dhr%dmin ago",hours, mins);

	else
		relativeTime.Format(20, L"%dmin ago", mins);

	return relativeTime;
}

String Utils::formatTime(DateTime dateTime){
	int hour = 	dateTime.GetHour();
	int min = 	dateTime.GetMinute();
	String time;
	if(hour<10) time += L"0";
	time += Integer::ToString(hour)+ L":";
	if(min < 10) time += L"0";
	time += Integer::ToString(min);
	return time;
}

String Utils::formatTime(TimeSpan duration){
	int hour = duration.GetHours();
	int min = duration.GetMinutes();
	String time;
	if(hour<10) time += L"0";
	time += Integer::ToString(hour)+ L":";
	if(min < 10) time += L"0";
	time += Integer::ToString(min);
	return time;
}

String Utils::formatDelay(TimeSpan delay){
	int hour = delay.GetHours();
	int min = delay.GetMinutes();
	if(min==0 && hour ==0)
		return L"";
	String time = L"+" + Integer::ToString(hour)+ L"H";
	if(min < 10) time += L"0";
	time += Integer::ToString(min);
	return time;
}

String Utils::formatDate(DateTime dateTime){
	int day=	dateTime.GetDay();;
	int month=	dateTime.GetMonth();
	int year=	dateTime.GetYear();
	String date = L"";
	if(day<10) date.Append('0');
	date.Append(day);
	date.Append('/');
	if(month<10) date.Append('0');
	date.Append(month);
	date.Append('/');
	date.Append(year);
	return date;
}
