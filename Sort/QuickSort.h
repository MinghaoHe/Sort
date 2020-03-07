#pragma once
#include "Sort.h"
#include "UISupport.h"

class QuickSort :public Sort
{
public:
	QuickSort(int* Instance, int Size, UISupport* ISupport)
		:Sort(Instance, Size, ISupport) {

		_ISupport->InsertOneRowForCode(0,  _T("QuickSort(A, lo, hi)"));
		_ISupport->InsertOneRowForCode(1,  _T("if lo < hi"));
		_ISupport->InsertOneRowForCode(2,  _T("  p = partition(A, lo, hi)"));
		_ISupport->InsertOneRowForCode(3,  _T("  quicksort(A, lo, p - 1)"));
		_ISupport->InsertOneRowForCode(4,  _T("  quicksort(A, p + 1, hi)"));
		_ISupport->InsertOneRowForCode(5,  _T(""));
		_ISupport->InsertOneRowForCode(6,  _T("partition(A, lo, hi)"));
		_ISupport->InsertOneRowForCode(7,  _T("i = lo"));
		_ISupport->InsertOneRowForCode(8,  _T("pivot = A[hi]"));
		_ISupport->InsertOneRowForCode(9,  _T("for j = lo to hi - 1"));
		_ISupport->InsertOneRowForCode(10, _T("  if A[j] <= pivot"));
		_ISupport->InsertOneRowForCode(11, _T("    swap A[i] with A[j]"));
		_ISupport->InsertOneRowForCode(12, _T("    i = i + 1"));
		_ISupport->InsertOneRowForCode(13, _T("    swap A[i] with A[hi]"));
		_ISupport->InsertOneRowForCode(14, _T("    return i"));
					
	}
	virtual ~QuickSort() { };
public:
	virtual void DoSort() {
		_ISupport->InitSort(_Instance, _Size);
		_QuickSort(_Instance, 0, _Size - 1);
	}

	void _QuickSort(int a[], int start, int end)
	{
		
		if (start > end)     
			return;
		int i = start;
		int j = end;
		_ISupport->FocusL(i);
		_ISupport->FocusR(j);

		int k = a[i];
		_ISupport->Push(i);

		while (i < j) {

			_ISupport->CancelHighLight(3);
			_ISupport->CancelHighLight(4);
			_ISupport->SetHighLight(2);
			while ((i < j) && a[j] >= k) {

				j--;
				_ISupport->FocusR(j);
			}
			if (i < j) {
				a[i] = a[j];
				_ISupport->SetHeightByIndex(i, j);
			}
			while (i < j && a[i] < k) {
				i++;
				_ISupport->FocusL(i);
			}
			if (i < j) {
				a[j] = a[i];
				_ISupport->SetHeightByIndex(j, i);
			}
		}
		a[i] = k;
		_ISupport->SetHeightByValue(i, _ISupport->Pop());

		_ISupport->CancelHighLight(2);
		_ISupport->CancelHighLight(4);
		_ISupport->SetHighLight(3);
		_ISupport->Wait();
		_QuickSort(a, i + 1, end);

		_ISupport->CancelHighLight(2);
		_ISupport->CancelHighLight(3);
		_ISupport->SetHighLight(4);
		_ISupport->Wait();
		_QuickSort(a, start, i - 1);
	}
};