#pragma once
#include <vector>
#include <tchar.h>

class UISupport
{
public:
	UISupport() { };
	virtual ~UISupport() { };
public:
	virtual void InitSort(int* Instance, int Size) = 0;
	virtual void FlashSort() = 0;

	virtual void FocusL(int lhs) = 0;
	virtual void FocusR(int rhs) = 0;

	virtual void Swap(int lhs,int rhs) = 0;

	virtual void SetHeightByIndex(int lhs, int rhs) = 0;
	virtual void SetHeightByValue(int index, int val) = 0;
	virtual int  GetHeightByIndex(int val)const = 0;

	virtual void Push(int val) = 0;
	virtual int  Pop() = 0;

	virtual void InsertOneRowForCode(int index, _TCHAR* szCode){ }
	virtual void SetHighLight(int index){ }
	virtual void CancelHighLight(int index) { }

	virtual void Wait()const = 0;

public:
	std::vector<int> _AuxilArray;
};