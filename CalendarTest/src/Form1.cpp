#include "Form1.h"

#include <FSocial.h>
#include <FLocales.h>
#include <FUi.h>

using namespace Osp::Social;
using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Locales;

Form1::Form1(void) {
}

Form1::~Form1(void) {
}

bool Form1::Initialize() {
	// Construct an XML form
	Construct(L"IDF_FORM1");

	return true;
}

result Form1::OnInitializing(void) {
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	// Get a button via resource ID


	Button *pButton_ok = static_cast<Button *> (GetControl("IDC_BUTTON_OK"));
	if (pButton_ok) {
		pButton_ok->SetActionId(22);
		pButton_ok->AddActionEventListener(*this);
	}
	return r;
}

result Form1::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void Form1::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	AppLog("calenderbook start");
	Calendarbook* pCalendarbook = new Calendarbook();
	result r = E_SUCCESS;
	r = pCalendarbook->Construct(null);
	if (IsFailed(r)) {
		AppLogException( "initializing the calendar book has failed");
		delete pCalendarbook;
		return;
	}

	DateTime startRange;
	DateTime endRange;
	IList* pEventList = null;

	startRange.SetValue(2009, 3, 1);
	endRange.SetValue(2011, 12, 12);

	// Gets the time zone of the system
	LocaleManager localeManager;
	localeManager.Construct();

	TimeZone timeZone = localeManager.GetSystemTimeZone();

	// Gets the events
	pEventList = pCalendarbook->GetEventsN(startRange, endRange, timeZone, 1,
			20, EVENT_CATEGORY_APPOINTMENT);
	if (IsFailed(GetLastResult()) || pEventList == null) {
		AppLogException( "GetEvents is failed");
		delete pCalendarbook;
		return;
	}
	if (pEventList->GetCount() == 0)
		AppLog("empty event list");
	// Gets a specific event
	for (int i = 0; i < pEventList->GetCount(); i++) {
		Osp::Social::CalEvent* pCalEvt =
				(Osp::Social::CalEvent*) pEventList->GetAt(i);
		if (pCalEvt != null) {
			String desc = pCalEvt->GetDescription();
			String subj = pCalEvt->GetSubject();
			AppLog("subj: %S",subj.GetPointer());
			AppLog("desc: %S\n\n",desc.GetPointer());
			MessageBox *messageBox = new MessageBox();
			messageBox->Construct(subj, desc, MSGBOX_STYLE_OK, 3000);
			int res;
			messageBox->ShowAndWait(res);
		}

	}
	pEventList->RemoveAll(true);
	delete pEventList;
	delete pCalendarbook;
}

