#include "view/FormLiveboard.h"
#include "controller/Controller.h"
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

FormLiveboard::FormLiveboard(void) {
}

FormLiveboard::~FormLiveboard(void) {
	liveBoardRequest = null;
	waitingPopup = null;
}

bool FormLiveboard::Initialize() {

	/*
	 * I18N
	 */
	String search = "zoekt";
	String clear = "wis";
	String station = "station";
	AppResource* appRes = Application::GetInstance()->GetAppResource();
	appRes->GetString(L"LB_SEARCH", search);
	appRes->GetString(L"LB_CLEAR", clear);
	appRes->GetString(L"LB_STATION",station);

	/*
	 * Set softkeys
	 */
	HeaderForm::Initialize(true, true);
	this->SetSoftkeyText(SOFTKEY_0, search);
	this->SetSoftkeyActionId(SOFTKEY_0, SEARCH_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0, *this);

	this->SetSoftkeyText(SOFTKEY_1, clear);
	this->SetSoftkeyActionId(SOFTKEY_1, CLEAR_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1, *this);
	liveBoardRequest = AppData::GetInstance()->getCurrentLiveBoardRequest();

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();
	int y = 10;
	int border = 0.05 * bounds.width;
	int widthBody = 0.9 * bounds.width;

	int heightBody = int(1.0 / 6.0 * double(bounds.height));
	/*
	 * add Controls to form
	 */
	stationEditField = new EditField();
	stationEditField->Construct(Rectangle(border, heightBody, widthBody,
			heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true,
			100);
	stationEditField->SetTitleText(station);
	AddControl(*stationEditField);
	stationEditField->AddTouchEventListener(*this);
	stationEditField->SetEnabled(false);//prevents opening default text input
	stationEditField->BeginBlock();

	editTime = new EditTime();
	Rectangle editTimeBounds = editTime->GetBounds();
	editTime->Construct(Osp::Graphics::Point(0, 3 * heightBody), L"pick a time");
	//get size from this editbounds
	editTimeBounds = editTime->GetBounds();
	int editTimeBorder = (bounds.width - editTimeBounds.width) / 2;
	//re postition to align in the middle
	editTime->SetPosition(editTimeBorder, 3 * heightBody);
	editTime->Set24HourNotationEnabled(true);
	editTime->SetCurrentTime();
	editTime->AddTimeChangeEventListener(*this);
	AddControl(*editTime);
	//waitingPopup = new WaitingPopup("Loading request",bounds.width*0.6,bounds.height/3);
	//waitingPopup->Construct(true,Dimension(bounds.width*0.6,bounds.height/3));
	waitingPopup = new Popup();
	int width = bounds.width * 0.85;
	int height = bounds.height / 3;
	AppLog("width %S height %S",Integer::ToString(width).GetPointer(),Integer::ToString(height).GetPointer());
	//int width=400;
	//int height=300;

	Dimension dim(width, height);
	waitingPopup->Construct(true, dim);
	waitingPopup->SetTitleText(L"Loading...");

	// Creates a button to close the Popup.
	Button* button = new Button();
	button->Construct(Rectangle(width * 0.15, height / 3, width * 0.6, height
			/ 4), L"Cancel");
	button->SetActionId(CANCEL_REQUEST);
	button->AddActionEventListener(*this);
	waitingPopup->AddControl(*button);
	return true;
}

result FormLiveboard::OnInitializing(void) {
	result r = E_SUCCESS;
	r = HeaderForm::OnInitializing(HEADER_ID_LIVEBOARD);
	return r;
}

result FormLiveboard::OnTerminating(void) {
	result r = E_SUCCESS;
	return r;
}

void FormLiveboard::OnActionPerformed(const Osp::Ui::Control& source,
		int actionId) {
	HeaderForm::OnActionPerformed(source, actionId);
	if (actionId == SEARCH_ACTION) {
		AppLog("Clicked FormLiveBoard::search");
		waitingPopup->SetShowState(true);
		waitingPopup->Show();
		Controller::GetInstance()->retrieveLiveBoardResults();
	} else if (actionId == CLEAR_ACTION) {
		AppLog("Clicked FormLiveBoard::clear");
		Controller::GetInstance()->clearLiveboard();
	} else if (actionId == CANCEL_REQUEST) {
		AppLogDebug("popup cancel button pressed");
		Controller::GetInstance()->cancelRequest();
		hideWaitingPopup();
	}
}

void FormLiveboard::RequestRedraw(bool show) const {
	AppLog("FormLiveboard::RequestRedraw");
	Station* station = liveBoardRequest->getStation();
	if (station != null) {
		stationEditField->SetText(station->getName());
	} else {
		stationEditField->SetText("");
	}

	DateTime* time = (liveBoardRequest->getDateTime());

	if (time != null) {
		editTime->SetTime(*time);
	} else {
		editTime->SetCurrentTime();
	}

	Form::RequestRedraw(show);
}

/*
 * ITouchEventListener & ITimeChanged methods
 */
void FormLiveboard::OnTouchMoved(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormLiveboard::OnTouchLongPressed(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormLiveboard::OnTouchReleased(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormLiveboard::OnTouchFocusIn(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormLiveboard::OnTouchDoublePressed(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormLiveboard::OnTouchFocusOut(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
}
void FormLiveboard::OnTouchPressed(const Osp::Ui::Control & source,
		const Osp::Graphics::Point & currentPosition,
		const Osp::Ui::TouchEventInfo & touchInfo) {
	Controller* controller = Controller::GetInstance();
	if (source.Equals(*stationEditField)) {
		AppLog("Clicked FormLiveboard::fromStationEditField");
		controller->selectStation(liveBoardRequest->getStation());
	}
}
void FormLiveboard::OnTimeChangeCanceled(const Osp::Ui::Control& source) {

}

void FormLiveboard::OnTimeChanged(const Osp::Ui::Control& source, int hour,
		int minute) {
	DateTime newTime = editTime->GetTime();
	Controller::GetInstance()->setLiveboardTime(newTime);
}

void FormLiveboard::hideWaitingPopup() {
	waitingPopup->SetShowState(false);
	Draw();
	Show();
}
