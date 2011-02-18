/*
 * DistanceSort.h
 *
 *  Created on: 18-feb-2011
 *      Author: B
 */

#ifndef DISTANCESORT_H_
#define DISTANCESORT_H_
#include <FBase.h>
#include "DistanceAndStation.h"

using namespace Osp::Base;

template <class T>
class DistanceSort:
	public Osp::Base::ComparerT<T>
{
public:
	DistanceSort(){}
	virtual ~DistanceSort(){}
	result Compare (const T &obj1, const T &obj2, int &cmp) const{
		DistanceAndStation* st1 = (DistanceAndStation*) obj1;
		DistanceAndStation* st2 = (DistanceAndStation*) obj2;
		if(st1->getDistance() < st2->getDistance())
			return -1;
		else
			return 1;
	}
};

#endif /* DISTANCESORT_H_ */
