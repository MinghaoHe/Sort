
// SortDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SortApp.h"
#include "SortDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSortDlg dialog



CSortDlg::CSortDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SORT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	_ISupport = nullptr;
	_ISort = nullptr;
	_Instance = nullptr;
	_hSortThread = NULL;
	_bRandom  = false;
	_bSorting = false;
}

void CSortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_SLIDER_SPEED, _SpeedSlider);
	DDX_Control(pDX, IDC_LIST_PSEUDOCODE, _ListCtrlCode);
}

BEGIN_MESSAGE_MAP(CSortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CSortDlg::OnBnClickedButtonRandom)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE,  &CSortDlg::OnBnClickedButtonStop  )
	ON_BN_CLICKED(IDC_BUTTON_START,  &CSortDlg::OnBnClickedButtonStart )
	ON_BN_CLICKED(IDC_BUTTON_END,    &CSortDlg::OnBnClickedButtonEnd   )

	ON_BN_CLICKED(IDC_BUTTON_BUBBLE_SORT, &CSortDlg::OnBnClickedButtonBubbleSort)
	ON_BN_CLICKED(IDC_BUTTON_MERGE_SORT , &CSortDlg::OnBnClickedButtonMergeSort )
	ON_BN_CLICKED(IDC_BUTTON_QUICK_SORT , &CSortDlg::OnBnClickedButtonQuickSort )
	ON_BN_CLICKED(IDC_BUTTON_INSERT_SORT, &CSortDlg::OnBnClickedButtonInsertSort)
	ON_BN_CLICKED(IDC_BUTTON_SHELL_SORT , &CSortDlg::OnBnClickedButtonShellSort )
	ON_BN_CLICKED(IDC_BUTTON_HEAP_SORT  , &CSortDlg::OnBnClickedButtonHeapSort  )
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CSortDlg message handlers

BOOL CSortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	_pDC = GetDC();
	_RandomEngine = std::default_random_engine((unsigned)time(0));
	GetClientRect(_ClientRect);
	_SpeedSlider.SetRange(0, 500);
	_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	_ListCtrlCode.InsertColumn(0, _T("Code"), LVCFMT_LEFT, 200, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSortDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSortDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSortDlg::OnBnClickedButtonBubbleSort()
{
	DWORD dwThreadId;
	if (_bRandom && !_bSorting) {

		_SpeedSlider.SetPos(250);
		_bSorting = true;
		if (_ISupport != nullptr)
			delete _ISupport;
		if (_ISort != nullptr)
			delete _ISort;
		if (_hSortThread != NULL)
			CloseHandle(_hSortThread);
		_pDC->UpdateColors();
		_ListCtrlCode.DeleteAllItems();
		_ISupport = new MFCSupport(_pDC, m_hWnd, 
			&_ListCtrlCode, &_SpeedSlider, _hStopEvent, this);
		_ISort = new BubbleSort(_Instance, _Size,_ISupport);
		_hSortThread = CreateThread(
			NULL, NULL,
			(LPTHREAD_START_ROUTINE)SortProc,
			this, NULL, &dwThreadId);
	}
	else {

		if (!_bRandom)
			MessageBox(_T("Please Random Value"), _T("Note"), MB_OK);
		else
			MessageBox(_T("We can't change algorithm in the process"), _T("Warning"), MB_OK);
	}
}


void CSortDlg::OnBnClickedButtonMergeSort()
{
	DWORD dwThreadId;
	if (_bRandom&&!_bSorting) {

		_SpeedSlider.SetPos(250);
		_bSorting = true;
		if (_ISupport != nullptr)
			delete _ISupport;
		if (_ISort != nullptr)
			delete _ISort;
		if (_hSortThread != NULL)
			CloseHandle(_hSortThread);
		_ListCtrlCode.DeleteAllItems();
		_pDC->UpdateColors();
		_ISupport = new MFCSupport(_pDC, m_hWnd, 
			&_ListCtrlCode, &_SpeedSlider, _hStopEvent, this);
		_ISort = new MergeSort(_Instance, _Size, _ISupport);
		_hSortThread = CreateThread(
			NULL, NULL,
			(LPTHREAD_START_ROUTINE)SortProc,
			this, NULL, &dwThreadId);
	}
	else {

		if(!_bRandom)
			MessageBox(_T("Please Random Value"), _T("Note"), MB_OK);
		else
			MessageBox(_T("We can't change algorithm in the process"), _T("Warning"), MB_OK);
	}
}

void CSortDlg::OnBnClickedButtonQuickSort()
{
	DWORD dwThreadId;
	if (_bRandom && !_bSorting) {

		_SpeedSlider.SetPos(250);
		_bSorting = true;
		if (_ISupport != nullptr)
			delete _ISupport;
		if (_ISort != nullptr)
			delete _ISort;
		if (_hSortThread != NULL)
			CloseHandle(_hSortThread);
		_ListCtrlCode.DeleteAllItems();
		_pDC->UpdateColors();
		_ISupport = new MFCSupport(_pDC, m_hWnd, 
			&_ListCtrlCode, &_SpeedSlider, _hStopEvent, this);
		_ISort = new QuickSort(_Instance, _Size, _ISupport);
		_hSortThread = CreateThread(
			NULL, NULL,
			(LPTHREAD_START_ROUTINE)SortProc,
			this, NULL, &dwThreadId);
	}
	else {
		if (!_bRandom)
			MessageBox(_T("Please Random Value"), _T("Note"), MB_OK);
		else
			MessageBox(_T("We can't change algorithm in the process"), _T("Warning"), MB_OK);
	}
}

void CSortDlg::OnBnClickedButtonInsertSort()
{
	DWORD dwThreadId;
	if (_bRandom && !_bSorting) {

		_SpeedSlider.SetPos(250);
		_bSorting = true;
		if (_ISupport != nullptr)
			delete _ISupport;
		if (_ISort != nullptr)
			delete _ISort;
		if (_hSortThread != NULL)
			CloseHandle(_hSortThread);
		_ListCtrlCode.DeleteAllItems();
		_pDC->UpdateColors();
		_ISupport = new MFCSupport(_pDC, m_hWnd, &_ListCtrlCode, 
			&_SpeedSlider, _hStopEvent, this);
		_ISort = new InsertSort(_Instance, _Size, _ISupport);
		_hSortThread = CreateThread(
			NULL, NULL,
			(LPTHREAD_START_ROUTINE)SortProc,
			this, NULL, &dwThreadId);
	}
	else {
		if (!_bRandom)
			MessageBox(_T("Please Random Value"), _T("Note"), MB_OK);
		else
			MessageBox(_T("We can't change algorithm in the process"), _T("Warning"), MB_OK);
	}
}

void CSortDlg::OnBnClickedButtonShellSort()
{
	DWORD dwThreadId;
	if (_bRandom && !_bSorting) {

		_SpeedSlider.SetPos(250);
		_bSorting = true;
		if (_ISupport != nullptr)
			delete _ISupport;
		if (_ISort != nullptr)
			delete _ISort;
		if (_hSortThread != NULL)
			CloseHandle(_hSortThread);
		_ListCtrlCode.DeleteAllItems();
		_pDC->UpdateColors();
		_ISupport = new MFCSupport(_pDC, m_hWnd, 
			&_ListCtrlCode, &_SpeedSlider, _hStopEvent, this);
		_ISort = new ShellSort(_Instance, _Size, _ISupport);
		_hSortThread = CreateThread(
			NULL, NULL,
			(LPTHREAD_START_ROUTINE)SortProc,
			this, NULL, &dwThreadId);
	}
	else {
		if (!_bRandom)
			MessageBox(_T("Please Random Value"), _T("Note"), MB_OK);
		else
			MessageBox(_T("We can't change algorithm in the process"), _T("Warning"), MB_OK);
	}
}

void CSortDlg::OnBnClickedButtonHeapSort()
{
	DWORD dwThreadId;
	if (_bRandom && !_bSorting) {

		_SpeedSlider.SetPos(250);
		_bSorting = true;
		if (_ISupport != nullptr)
			delete _ISupport;
		if (_ISort != nullptr)
			delete _ISort;
		if (_hSortThread != NULL)
			CloseHandle(_hSortThread);
		_ListCtrlCode.DeleteAllItems();
		_pDC->UpdateColors();
		_ISupport = new MFCSupport(_pDC, m_hWnd, 
			&_ListCtrlCode, &_SpeedSlider, _hStopEvent, this);
		_ISort = new HeapSort(_Instance, _Size, _ISupport);
		_hSortThread = CreateThread(
			NULL, NULL,
			(LPTHREAD_START_ROUTINE)SortProc,
			this, NULL, &dwThreadId);
	}
	else {
		if (!_bRandom)
			MessageBox(_T("Please Random Value"), _T("Note"), MB_OK);
		else
			MessageBox(_T("We can't change algorithm in the process"), _T("Warning"), MB_OK);
	}
}

void CSortDlg::OnBnClickedButtonRandom()
{
	_bRandom = true;
	if (_Instance == nullptr)
		_Instance = new INT[20];
	_Size = 20;

	auto rand = std::uniform_real_distribution<double>(5, 30);
	
	for (int i = 0; i < 20; i++)
		_Instance[i] = (int)rand(_RandomEngine);
}

DWORD CSortDlg::SortProc(LPVOID lpParam)
{
	CSortDlg* This = (CSortDlg*)lpParam;
	This->_ISort->DoSort();
	::MessageBox(This->m_hWnd, _T("The Sort is OK"), _T("Note"), MB_OK);
	This->_bSorting = false;
	This->_bRandom  = false;
	ResetEvent(This->_hStopEvent);
	return 0;
}


void CSortDlg::OnBnClickedButtonStop()
{
	ResetEvent(_hStopEvent);
}


void CSortDlg::OnBnClickedButtonStart()
{
	SetEvent(_hStopEvent);
}


void CSortDlg::OnBnClickedButtonEnd()
{
	if (_hSortThread != NULL)
	{
		TerminateThread(_hSortThread, 0);
		CloseHandle(_hSortThread);
		_hSortThread = NULL;
	}
	_bSorting = false;
	_bRandom  = false;
	ResetEvent(_hStopEvent);
}


void CSortDlg::OnClose()
{
	delete _ISupport;
	delete _ISort;
	delete[] _Instance;

	_pDC->DeleteDC();
	CloseHandle(_hStopEvent);
	if (_hSortThread != NULL)
		CloseHandle(_hSortThread);
	CDialogEx::OnClose();
}
