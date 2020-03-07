#pragma once
#include "UISupport.h"
#include <vector>
class Sort
{
public:
	Sort(int* Instance,int Size,UISupport* ISupport)
		:_Instance(Instance),_Size(Size),_ISupport(ISupport){}
	~Sort() { };
public:
	virtual void DoSort() = 0;
protected:
	int* _Instance;
	int  _Size;
	UISupport* _ISupport;
};