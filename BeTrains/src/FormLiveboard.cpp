#include "FormLiveboard.h"
#include "Controller.h"
using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Graphics;

FormLiveboard::FormLiveboard(void) {
}

FormLiveboard::~FormLiveboard(void) {
}

bool FormLiveboard::Initialize() {
	HeaderForm::Initialize(true,true);
	this->SetSoftkeyText(SOFTKEY_0,"Search");
	this->SetSoftkeyActionId(SOFTKEY_0,SEARCH_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_0,*this);

	this->SetSoftkeyText(SOFTKEY_1,"Clear");
	this->SetSoftkeyActionId(SOFTKEY_1,CLEAR_ACTION);
	this->AddSoftkeyActionListener(SOFTKEY_1,*this);

	/*
	 * Calculate sizes for all controls
	 */
	Rectangle bounds = this->GetClientAreaBounds();
	int y = 10;
	int border = 0.05 * bounds.width;
	int widthBody = 0.9 * bounds.width;

	int heightBody = int( 1.0 / 6.0 * double(bounds.height));
	/*
	 * add Controls to form
	 */
	stationEditField = new EditField();
	stationEditField->Construct( Rectangle(border, heightBody, widthBody, heightBody), EDIT_FIELD_STYLE_NORMAL, INPUT_STYLE_FULLSCREEN, true, 100);
	stationEditField->SetTitleText(L"Station");
	AddControl(*stationEditField);
	stationEditField->AddTouchEventListener(*this);
	stationEditField->SetEnabled(false);//prevents opening default text input
	stationEditField->BeginBlock();

	editTime = new EditTime();
	Rectangle editTimeBounds = editTime->GetBounds();
	editTime->Construct(Osp::Graphics::Point(0,3*heightBody),L"pick a time");
	//get size from this editbounds
	editTimeBounds = editTime->GetBounds();
	int editTimeBorder = (bounds.width - editTimeBounds.width)/2;
	//re postition to align in the middle
	editTime->SetPosition(editTimeBorder,3*heightBody);
	editTime->Set24HourNotationEnabled(true);
	editTime->SetCurrentTime();
	AddControl(*editTime);
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

void FormLiveboard::OnActionPerformed(const Osp::Ui::Control& source, int actionId) {
	HeaderForm::OnActionPerformed(source,actionId);
	if(actionId == SEARCH_ACTION){
		AppLog("Clicked FormLiveBoard::search");
	}else if(actionId == CLEAR_ACTION){
		AppLog("Clicked FormLiveBoard::clear");
	}
}

/*
 * ITouch Event Listerer methods
 */
void FormLiveboard::OnTouchMoved(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormLiveboard::OnTouchLongPressed(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormLiveboard::OnTouchReleased(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormLiveboard::OnTouchFocusIn(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormLiveboard::OnTouchDoublePressed(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormLiveboard::OnTouchFocusOut(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo){}
void FormLiveboard::OnTouchPressed(const Osp::Ui::Control & source, const Osp::Graphics::Point & currentPosition, const Osp::Ui::TouchEventInfo & touchInfo)
{
	Controller* controller = Controller::GetInstance();
	if(source.Equals(*stationEditField)){
		AppLog("Clicked FormLiveboard::fromStationEditField");
		//controller->selectStation(*station);
	}
}

