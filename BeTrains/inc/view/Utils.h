#ifndef UTILS_H_
#define UTILS_H_

#include <FBase.h>
#include <FUi.h>
#include <FLocations.h>

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Graphics;
using namespace Osp::Locations;

class Utils
{
public:
	Utils();
	~Utils();

	//Global utility functions
	static Bitmap* GetBitmapN(const Osp::Base::String& name);
	static String GetRelativeLocationFromCoordinates(const Coordinates &myCoords, const Coordinates &theirCoords);
	static String GetRelativeTimeFromTimeStamp(DateTime receivedTime);
	static DateTime ConvertUtcTimeToStardardTime(const long long timeStamp);

	static String formatTime(DateTime time);
	static String formatTime(TimeSpan duration);
	static String formatDelay(TimeSpan delay);
	static String formatDate(DateTime time);

};
#endif /* UTILS_H_ */
