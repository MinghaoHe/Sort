#include "stdafx.h"
#include "MFCSupport.h"


void MFCSupport::InitSort(int* Instance, int Size)
{
	
	DWORD dwNewStyle = _pListCtrlCode->GetExtendedStyle();
	dwNewStyle |= LVS_EX_FULLROWSELECT;
	_pListCtrlCode->SetExtendedStyle(dwNewStyle);

	_ShowRect = new CRect(10, 70, 550, 450);
	_pDC->FillSolidRect(_ShowRect, RGB(255, 255, 255));

	_Rects.clear();
	_Instance = Instance;
	RECT* rect;
	for (int i = 0; i < Size;i++) {
		// l t r b
		rect = new CRect(
			25 * i + 30,
			400 - _Instance[i] * 10,
			25 * i + 50,
			400);
		_Rects.push_back(rect);
	}

	_pDC->SelectObject(&_NolBrush);
	for (auto i : _Rects) {
		_pDC->FillRect(i, _NolBrush);
	}

}

void MFCSupport::FlashSort()
{
	WaitForSingleObject(_hStopEvent,INFINITE);
	Sleep( 500 
		- _pSpeedSlider->GetPos());
	
	_pDC->FillSolidRect(_ShowRect, RGB(255, 255, 255));

	for (SIZE_T i = 0; i < _Rects.size();i++) {

		if (i == _rhs || i == _lhs) {
			_pDC->SelectObject(&_FocBrush);
			_pDC->FillRect(_Rects[i], _FocBrush);
		}
		else {
			_pDC->SelectObject(&_NolBrush);
			_pDC->FillRect(_Rects[i], _NolBrush);
		}
	}
}

void MFCSupport::FocusL(int lhs)
{
	_lhs = lhs;
	FlashSort();
}

void MFCSupport::FocusR(int rhs)
{
	_rhs = rhs;
	FlashSort();
}

void MFCSupport::Swap(int lhs, int rhs)
{
	int temp = _Rects[lhs]->top;
	_Rects[lhs]->top = _Rects[rhs]->top;
	_Rects[rhs]->top = temp;
	FlashSort();
}

void MFCSupport::SetHeightByIndex(int lhs, int rhs)
{
	_Rects[lhs]->top = _Rects[rhs]->top;
	FlashSort();
}

void MFCSupport::SetHeightByValue(int index, int val)
{
	_Rects[index]->top = val;
	FlashSort();
}

int  MFCSupport::GetHeightByIndex(int val)const
{
	return _Rects[val]->top;
}

void MFCSupport::Push(int val)
{
	_AuxilArray.push_back(_Rects[val]->top);
}

int  MFCSupport::Pop()
{
	int tmp = _AuxilArray[_AuxilArray.size() - 1];
	_AuxilArray.pop_back();
	return tmp;
}

void MFCSupport::InsertOneRowForCode(int index, _TCHAR * szCode)
{
	_pListCtrlCode->InsertItem(index, szCode);
}

void MFCSupport::SetHighLight(int index)
{
	_pListCtrlCode->SetFocus();
	_pListCtrlCode->SetItemState(index, 
		LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	_pListCtrlCode->EnsureVisible(index, FALSE);
}

void MFCSupport::CancelHighLight(int index)
{
	_pListCtrlCode->SetItemState(
		index, 0, LVIS_SELECTED | LVIS_FOCUSED);

	_pListCtrlCode->SetFocus();
}

void MFCSupport::Wait()const
{
	Sleep(500
		- _pSpeedSlider->GetPos());
}









