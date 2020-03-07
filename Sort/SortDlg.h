
// SortDlg.h : header file
//

#pragma once

#include <vector>
#include <ctime>
#include <random>


#include "Sort.h"
#include "BubbleSort.h"
#include "InsertSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "ShellSort.h"
#include "HeapSort.h"
#include "UISupport.h"
#include "MFCSupport.h"

// CSortDlg dialog
class CSortDlg : public CDialogEx
{
// Construction
public:
	CSortDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SORT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnBnClickedButtonBubbleSort();
	afx_msg void OnBnClickedButtonMergeSort();
	afx_msg void OnBnClickedButtonQuickSort();
	afx_msg void OnBnClickedButtonInsertSort();
	afx_msg void OnBnClickedButtonShellSort();
	afx_msg void OnBnClickedButtonHeapSort();

	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonEnd();

private:
	HICON m_hIcon;
	CRect _ClientRect;
	
	UISupport* _ISupport;
	Sort* _ISort;
	CDC* _pDC;
	BOOL _bRandom;
	BOOL _bSorting;
	HANDLE _hStopEvent;
	HANDLE _hSortThread;
	CSliderCtrl _SpeedSlider;
	INT* _Instance;
	INT _Size;
	CListCtrl _ListCtrlCode;
	std::default_random_engine _RandomEngine;


public:
	static DWORD SortProc(LPVOID lpParam);
	
};
