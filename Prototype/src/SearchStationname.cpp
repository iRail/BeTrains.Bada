
#include "SearchStationName.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


Search_Station_Name::Search_Station_Name(void)
{
}

Search_Station_Name::~Search_Station_Name(void)
{
}

bool
Search_Station_Name::Initialize()
{
	Form::Construct(L"IDF_SEARCH_STATION");

	return true;
}

result
Search_Station_Name::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here


	return r;
}

result
Search_Station_Name::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


