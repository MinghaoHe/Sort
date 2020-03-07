#include "stdafx.h"
#include "Sort.h"
#include "UISupport.h"

class MergeSort : public Sort
{
public:
	MergeSort(int* Instance, int Size, UISupport* ISupport)
		:Sort(Instance, Size, ISupport) {
		_ISupport->InsertOneRowForCode(0, _T("MergeSort(A, p, r)"));
		_ISupport->InsertOneRowForCode(1, _T("if p < r"));
		_ISupport->InsertOneRowForCode(2, _T("  q = [(p + r) / 2]"));
		_ISupport->InsertOneRowForCode(3, _T("  MergeSort(A, p, q)"));
		_ISupport->InsertOneRowForCode(4, _T("  MergeSort(A, q + 1, r)"));
		_ISupport->InsertOneRowForCode(5, _T("  MergeSort(A, p, q, r)"));
	}
	virtual ~MergeSort() { };
public:
	virtual void DoSort() {

		_ISupport->InitSort(_Instance, _Size);  
		tmp.reserve(100);                       
		tmp.resize(100);                        
		_ISupport->_AuxilArray.clear();         
		_ISupport->_AuxilArray.reserve(1000);   
		_ISupport->_AuxilArray.resize(100);      
		_MergeSort(_Instance, 0, _Size - 1);

	}

	void _MergeSort(int q[], int l, int r)
	{

		if (l >= r) return;

		int mid = (l + r) >> 1;

		_ISupport->CancelHighLight(4);
		_ISupport->CancelHighLight(5);
		_ISupport->SetHighLight(3);
		_ISupport->Wait();
		_MergeSort(q, l, mid); 
		
		_ISupport->CancelHighLight(3);
		_ISupport->CancelHighLight(5);
		_ISupport->SetHighLight(4);
		_ISupport->Wait();
		_MergeSort(q, mid + 1, r);

		int k = 0, i = l, j = mid + 1;
		while (i <= mid && j <= r)
		{
			_ISupport->CancelHighLight(3);
			_ISupport->CancelHighLight(4);
			_ISupport->SetHighLight(5);
			_ISupport->FocusL(i);
			_ISupport->FocusR(j);
			if (q[i] <= q[j])
			{
				_ISupport->_AuxilArray[k] = _ISupport->GetHeightByIndex(i);
				tmp[k++] = q[i++];
			}
			else
			{
				_ISupport->_AuxilArray[k] = _ISupport->GetHeightByIndex(j);
				tmp[k++] = q[j++];
			}
		}
		while (i <= mid)
		{
			_ISupport->_AuxilArray[k] = _ISupport->GetHeightByIndex(i);
			tmp[k++] = q[i++];
		}
		while (j <= r)
		{
			_ISupport->_AuxilArray[k] = _ISupport->GetHeightByIndex(j);
			tmp[k++] = q[j++];
		}

		for (int i = l, j = 0; i <= r; i++, j++)
		{
			_ISupport->FocusL(i);
			_ISupport->FocusR(j);
			_ISupport->SetHeightByValue(i, _ISupport->_AuxilArray[j]);
			q[i] = tmp[j];
		}

	}
private:
	std::vector<int> tmp;
};