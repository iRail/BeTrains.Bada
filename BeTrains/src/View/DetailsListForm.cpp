
#include "View/DetailsListForm.h"

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;


DetailsListForm::DetailsListForm(void)
{
}

DetailsListForm::~DetailsListForm(void)
{
}

bool
DetailsListForm::Initialize()
{
	Form::Construct(L"DETAILS_LIST_FORM");

	return true;
}

result
DetailsListForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result
DetailsListForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}


