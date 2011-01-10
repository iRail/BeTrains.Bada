#include "SearchStationName.h"
#include <FBaseColArrayList.h>

using namespace Osp::Base;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Base::Collection;
SearchStationName::SearchStationName(void) {
}

SearchStationName::~SearchStationName(void) {
}

bool SearchStationName::Initialize() {
	Form::Construct(L"IDF_FORM2");

	 pScrollPanel = static_cast<ScrollPanel *> (GetControl(L"IDC_SCROLLPANEL1",false));
	 pEditField = static_cast<EditField *>(GetControl(L"IDPC_EDITFIELD1",true));
	 pResultList = static_cast<List *>(GetControl(L"IDPC_LIST1",true));

	//3
	 pEditField->AddActionEventListener(*this);
	 pEditField ->AddScrollPanelEventListener(*this);
	 pEditField->AddTextEventListener((*this));
	//4
	 pEditField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_LEFT, L"Done", ID_BUTTON_EDITFIELD_DONE);
	 pEditField ->SetOverlayKeypadCommandButton(COMMAND_BUTTON_POSITION_RIGHT, L"Close", ID_BUTTON_EDITFIELD_CLOSE);

	//AppLog("hmm %S",stations[0]);
	return true;
}

result SearchStationName::OnInitializing(void) {
	result r = E_SUCCESS;

	// TODO: Add your initialization code here

	return r;
}

result SearchStationName::OnTerminating(void) {
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void SearchStationName::OnActionPerformed(const Osp::Ui::Control& source,
		int actionId) {

	switch (actionId) {
	case ID_BUTTON_EDITFIELD_DONE: {
		pScrollPanel->CloseOverlayWindow();
		pEditField->Draw();
		pEditField->Show();

	}
		break;
	case ID_BUTTON_EDITFIELD_CLOSE:
		pScrollPanel->CloseOverlayWindow();
		pEditField->Draw();
		pEditField->Show();
		break;

	default:
		break;
	}
}

//6
void SearchStationName::OnOverlayControlCreated(const Osp::Ui::Control& source) {

}

void SearchStationName::OnOverlayControlOpened(const Osp::Ui::Control& source) {

}

void SearchStationName::OnOverlayControlClosed(const Osp::Ui::Control& source) {

	SetFocus();
}

void SearchStationName::OnOtherControlSelected(const Osp::Ui::Control& source) {

}

void SearchStationName::OnTextValueChanged(const Osp::Ui::Control& source){
	AppLog("----------------------------------------------------------");
	ArrayListT<String>* pDummyLijst = new ArrayListT<String>();
	pDummyLijst->Add(String("Gent"));
	pDummyLijst->Add(String("Tielt"));
	pDummyLijst->Add(String("Lichtervelde"));

	//clearen van de lijst
	if(pResultList != 0)
		pResultList->RemoveAllItems();

	//ophalen matches adhv string in de editfield
	String text = pEditField->GetText();
	//AppLog("3");
	for(int i=0; i < pDummyLijst->GetCount(); i++){
		String item;
		pDummyLijst->GetAt(i,item);
		//AppLog("4");
		AppLog("string : %S",item.GetPointer());
		AppLog("string2 : %S",text.GetPointer());
		String cmp;
		item.SubString(0,text.GetLength(),cmp);
		AppLog("string3 : %S",cmp.GetPointer());
		if(cmp.Equals(text,false)){
			//AddItem(&String("Add Databases"), &String("adds all the databases"), bitmap1, bitmap3, 0);
			AppLog("Item added");
			pResultList->AddItem(&item,0,0,0,0);
			//AppLog("Text Changed");
			pResultList->Draw();
			pScrollPanel->Draw();
			this->Draw();
			//pScrollPanel->DrawChildControls();

		}
	}



}

void SearchStationName::OnTextValueChangeCanceled(const Osp::Ui::Control& source){

}

