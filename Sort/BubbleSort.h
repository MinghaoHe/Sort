#pragma once
#include "Sort.h"
#include "UISupport.h"

class BubbleSort : public Sort
{
public:
	BubbleSort(int* Instance, int Size, UISupport* ISupport)
		:Sort(Instance, Size, ISupport) {

		_ISupport->InsertOneRowForCode(0, _T("BubbleSort(A)"));
		_ISupport->InsertOneRowForCode(1, _T("for i = 1 to length[A]"));
		_ISupport->InsertOneRowForCode(2, _T("  for j = length[A] to i + 1"));
		_ISupport->InsertOneRowForCode(3, _T("    exchane A[j] and A[j - 1]"));
	}
	virtual ~BubbleSort() { };

public:
	virtual void DoSort() {
		_ISupport->InitSort(_Instance,_Size);
		_BubbleSort(_Instance, _Size);
	}

	void _BubbleSort(int* Instance, int Size)
	{
		int temp;
		int i, j;
		for (i = 0; i < Size - 1; i++)
		{
			_ISupport->CancelHighLight(3);
			_ISupport->SetHighLight(1);
			_ISupport->FocusL(Size - 1 - i);
			for (j = 0; j < Size - 1 - i; j++) {

				_ISupport->CancelHighLight(3);
				_ISupport->CancelHighLight(1);
				_ISupport->SetHighLight(2);
				_ISupport->FocusR(j);
				if (Instance[j] > Instance[j + 1])
				{
					_ISupport->CancelHighLight(2);
					_ISupport->SetHighLight(3);
					_ISupport->Swap(j + 1, j);
					temp = Instance[j];
					Instance[j] = Instance[j + 1];
					Instance[j + 1] = temp;

				}
			}
		}
	}
};