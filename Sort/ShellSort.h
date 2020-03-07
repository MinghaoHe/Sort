#pragma once
#include "stdafx.h"
#include "Sort.h"
#include "UISupport.h"

class ShellSort :public Sort
{
public:
	ShellSort(int* Instance, int Size, UISupport* ISupport)
		:Sort(Instance, Size, ISupport) 
	{
		_ISupport->InsertOneRowForCode(0,  _T("ShellSort(A, n)"));
		_ISupport->InsertOneRowForCode(1,  _T("d = n / 2"));
		_ISupport->InsertOneRowForCode(2,  _T("for i = d to n"));
		_ISupport->InsertOneRowForCode(3,  _T("  t = A[i];"));
		_ISupport->InsertOneRowForCode(4,  _T("  j = i - d"));
		_ISupport->InsertOneRowForCode(5,  _T("  while j >= 0"));
		_ISupport->InsertOneRowForCode(6,  _T("    if (t < A[j])"));
		_ISupport->InsertOneRowForCode(7,  _T("    A[j + d] = A[j]"));
		_ISupport->InsertOneRowForCode(8,  _T("    j = j - d"));
		_ISupport->InsertOneRowForCode(9,  _T("    else A[j + d] = t break"));
		_ISupport->InsertOneRowForCode(10, _T("  d = d / 2;"));
	}
	virtual ~ShellSort() { };
public:
	virtual void DoSort() {
		_ISupport->InitSort(_Instance, _Size);
		_ShellSort(_Instance, _Size);
	}

	void _ShellSort(int* Instance, int Size)
	{
		int i, gap;
		for (gap = Size / 2; gap > 0; gap /= 2)
		{
			for (i = gap; i < Size; i++)
			{
				_ISupport->FocusL(i);
				if (Instance[i] < Instance[i - gap])
				{
					_ISupport->Push(i);
					int temp = Instance[i];
					int j;
					for (j = i - gap; j >= 0 && Instance[j] > temp; j -= gap)
					{
						_ISupport->FocusR(j);
						_ISupport->SetHeightByIndex(j + gap, j);
						Instance[j + gap] = Instance[j];
					}
					_ISupport->SetHeightByValue(j + gap, _ISupport->Pop());
					Instance[j + gap] = temp;
				}
			}
		}
	}
};