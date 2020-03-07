#pragma once
#include "Sort.h"
#include "UISupport.h"

class HeapSort : public Sort
{
public:
	HeapSort(int* Instance, int Size, UISupport* ISupport)
		:Sort(Instance, Size, ISupport) 
	{
		_ISupport->InsertOneRowForCode(0, _T("HeapSort(A)"));
		_ISupport->InsertOneRowForCode(1, _T("BUILD-MAX-HEAP(A)"));
		_ISupport->InsertOneRowForCode(2, _T("for i = A.length downto 2"));
		_ISupport->InsertOneRowForCode(3, _T("  exchange A[1] with A[i]"));
		_ISupport->InsertOneRowForCode(4, _T("  A.heap_size = A.heap_size - 1"));
		_ISupport->InsertOneRowForCode(5, _T("  MAX-HEAPIFY(A, 1)"));
	}
	virtual ~HeapSort() { };
public:
	virtual void DoSort() {
		_ISupport->InitSort(_Instance, _Size);
		_HeapSort(_Instance, _Size);
	}
	void _HeapSort(int* Instance, int Size)
	{
		int i, k;
		for (i = Size / 2 - 1; i >= 0; i--)
		{
			_ISupport->FocusL(i);
			HeapAdjust(Instance, i, Size);
		}
		for (i = Size - 1; i >= 1; i--)
		{
			_ISupport->FocusL(i);

			_ISupport->Push(0);
			k = Instance[0]; 

			_ISupport->SetHeightByIndex(0, i);
			Instance[0] = Instance[i]; 

			_ISupport->SetHeightByValue(i, _ISupport->Pop());
			Instance[i] = k;

			HeapAdjust(Instance, 0, i);
		}
	}

private:
	void HeapAdjust(int a[], int i, int m)
	{
		int k, t;

		_ISupport->Push(i);
		t = a[i]; 

		k = 2 * i + 1;
		_ISupport->FocusR(k);
		while (k < m)
		{
			if ((k < m - 1) && (a[k] < a[k + 1]))
			{
				
				k++;
				_ISupport->FocusR(k);
			}
			if (t < a[k]) { 
				a[i] = a[k];
				_ISupport->SetHeightByIndex(i, k);
				i = k; 
				_ISupport->FocusL(i);
				k = 2 * i + 1; 
				_ISupport->FocusR(k);
			}
			else 
				break;
		}
		a[i] = t;
		_ISupport->SetHeightByValue(i, _ISupport->Pop());
	}
};
