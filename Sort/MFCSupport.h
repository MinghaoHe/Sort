#pragma once
#include "stdafx.h"
#include "SortDlg.h"
#include "UISupport.h"
#include <vector>
#include "RGB.h"


class MFCSupport :public UISupport
{
public:
	MFCSupport(CDC* pDC, HWND hWnd, CListCtrl* pListCtrlCode,
		CSliderCtrl* pSpeedSlider, HANDLE hStopEvent, CDialog* Dlg)
		:_pDC(pDC), _hWnd(hWnd), _pListCtrlCode(pListCtrlCode),
		_pSpeedSlider(pSpeedSlider), _hStopEvent(hStopEvent),
		_Dlg(Dlg), _FocBrush(new CBrush), _NolBrush(new CBrush) {
		
		_FocBrush->CreateSolidBrush(RED);
		_NolBrush->CreateSolidBrush(BLUE);
	}

	virtual ~MFCSupport() {
		for (auto i : _Rects)
			delete i;
		_FocBrush->DeleteObject();
		_NolBrush->DeleteObject();
		delete _FocBrush;
		delete _NolBrush;
	}
public:
	virtual void InitSort(int* Instance, int Size);
	virtual void FlashSort();

	virtual void FocusL(int lhs);
	virtual void FocusR(int rhs);
	
    virtual void Swap(int lhs, int rhs);

	virtual void SetHeightByIndex(int lhs, int rhs);
	virtual void SetHeightByValue(int index, int val);
	virtual int  GetHeightByIndex(int val) const;

	virtual void Push(int val);
	virtual int  Pop();

	virtual void InsertOneRowForCode(int index, _TCHAR* szCode);
	virtual void SetHighLight(int index);
	virtual void CancelHighLight(int index);

	virtual void Wait()const;
		

private:
	CDialog* _Dlg;
	CDC*   _pDC;
	HWND   _hWnd;
	CListCtrl* _pListCtrlCode;
	CSliderCtrl* _pSpeedSlider;
	HANDLE _hStopEvent;

	INT _lhs;
	INT _rhs;
	CBrush* _FocBrush;
	CBrush* _NolBrush;

	INT* _Instance;

	CRect* _ShowRect;
	std::vector<RECT*> _Rects;
	
};


