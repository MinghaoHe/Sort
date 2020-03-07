#pragma once
#pragma once
#include "Sort.h"
#include "UISupport.h"

class InsertSort : public Sort
{
public:
	InsertSort(int* Instance, int Size, UISupport* ISupport)
		:Sort(Instance, Size, ISupport) { 
		_ISupport->InsertOneRowForCode(0, _T("InsertSort(A)"));
		_ISupport->InsertOneRowForCode(1, _T("for j = 2 to A.length"));
		_ISupport->InsertOneRowForCode(2, _T("  key = a[j]"));
		_ISupport->InsertOneRowForCode(3, _T("  i = j - 1"));
		_ISupport->InsertOneRowForCode(4, _T("  while i > 0 and A[i] > key"));
		_ISupport->InsertOneRowForCode(5, _T("    A[i+1] = A[j]"));
		_ISupport->InsertOneRowForCode(6, _T("    i = i - 1"));
		_ISupport->InsertOneRowForCode(7, _T("  A[i+1] = key"));
	}
	virtual ~InsertSort() { };
public:
	virtual void DoSort() {

		_ISupport->InitSort(_Instance, _Size);
		_InsertSort(_Instance, _Size);
	}

	void _InsertSort(int* Instance,int Size) {
		int i, j;
		for (i = 1; i < Size; i++) {
			_ISupport->CancelHighLight(7);
			_ISupport->SetHighLight(1);
			_ISupport->FocusL(i);
			if (Instance[i] < Instance[i - 1]) {
				_ISupport->Push(i);
				int temp = Instance[i];
				for (j = i - 1; j >= 0 && Instance[j] > temp; j--) {
					_ISupport->CancelHighLight(1);
					_ISupport->CancelHighLight(5);
					_ISupport->SetHighLight(4);
					_ISupport->FocusR(j);
					_ISupport->CancelHighLight(4);
					_ISupport->SetHighLight(5);
					_ISupport->SetHeightByIndex(j + 1, j);
					Instance[j + 1] = Instance[j];
				}
				_ISupport->CancelHighLight(5);
				_ISupport->SetHighLight(7);
				_ISupport->SetHeightByValue(j + 1, _ISupport->Pop());
				Instance[j + 1] = temp;
			}
		}
	}
};