// ApcInjectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ApcInject.h"
#include "ApcInjectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CApcInjectDlg 对话框




CApcInjectDlg::CApcInjectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CApcInjectDlg::IDD, pParent)
	, m_strExePath(_T(""))
	, m_strDllPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CApcInjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strExePath);
	DDX_Text(pDX, IDC_EDIT2, m_strDllPath);
}

BEGIN_MESSAGE_MAP(CApcInjectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CApcInjectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CApcInjectDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CApcInjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CApcInjectDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CApcInjectDlg 消息处理程序

BOOL CApcInjectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CApcInjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CApcInjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CApcInjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//APC inject 
//
typedef LONG NTSTATUS, *PNTSTATUS;
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

typedef enum _SECTION_INHERIT 
{
	ViewShare = 1,
	ViewUnmap = 2
} SECTION_INHERIT;



DWORD APCInject(PCHAR sProcName,PCHAR sDllName){
	DWORD dRet=0;
	OutputDebugString("[+] APCInject  enter !");

	//定义指向NtMapViewOfSection的函数指针类型
	typedef DWORD (WINAPI *tNtMapViewOfSection)(HANDLE,HANDLE,LPVOID,ULONG,SIZE_T,LARGE_INTEGER*,SIZE_T*,SECTION_INHERIT,ULONG,ULONG);
	tNtMapViewOfSection NtMapViewOfSection=(tNtMapViewOfSection)GetProcAddress(GetModuleHandle("ntdll.dll"),"NtMapViewOfSection");
	if(!NtMapViewOfSection)
	{
		OutputDebugString("[-] APCInject GetProcAddress NtMapViewOfSection error!");
		return -1;
	}
		

	//创建buffer
	HANDLE hFile=CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,strlen(sDllName)+1,NULL);
	if(!hFile)
	{
		OutputDebugString("[-] APCInject CreateFileMapping error!");
		return -2;
	}
		
	PCHAR hView=(PCHAR)MapViewOfFile(hFile,FILE_MAP_ALL_ACCESS,0,0,0);
	if(!hView)
	{
		OutputDebugString("[-] APCInject MapViewOfFile error!");
		CloseHandle(hFile);
		return -3;
	}
	else
	{
		//给buffer设置待注入的dll路径
		strcpy(hView,sDllName);
	}
		

	// 启动目标进程
	PROCESS_INFORMATION pi;STARTUPINFO st;
	ZeroMemory(&pi,sizeof(pi));
	ZeroMemory(&st,sizeof(st));
	st.cb=sizeof(STARTUPINFO);
	//以suspend方式创建进程
	if(CreateProcess(sProcName,NULL,NULL,NULL,FALSE,CREATE_SUSPENDED,NULL,NULL,&st,&pi))
	{
		LPVOID RemoteString=NULL;
		ULONG ViewSize=0;
		void * lpDllName   = NULL;
		
		///////////////////////////////////////////////////////////////////////////////////////////////////
		//目标进程地址空间分配待注入dll路径空间
		//lpDllName = VirtualAllocEx(pi.hProcess, NULL, (strlen(sDllName) + 1), MEM_COMMIT, PAGE_READWRITE); 
		//if(lpDllName)
		//{
		//	//把待注入dll路径写入目标进程空间
		//	if(WriteProcessMemory(pi.hProcess, lpDllName, sDllName,strlen(sDllName), NULL))
		//	{
		//		LPVOID nLoadLibrary=(LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA");
		//		//调用QueueUserAPC向远线程插入一个APC，这个APC就是LoadLibrary
		//		if(!QueueUserAPC((PAPCFUNC)nLoadLibrary,pi.hThread,(ULONG_PTR)lpDllName))
		//		{
		//			OutputDebugString("[-] APCInject QueueUserAPC call  error!");
		//			dRet=-6;
		//		}
		//	}
		//	else
		//	{
		//		OutputDebugString("[-] APCInject WriteProcessMemory call  error!");
		//		dRet=-5;
		//	}
		//}
		//else
		//{
		//	OutputDebugString("[-] APCInject VirtualAllocEx call  error!");
		//	dRet=-4;
		//}
		///////////////////////////////////////////////////////////////////////////////////////////////////

		//将待注入dll路径映射到目标进程地址空间
		if(NtMapViewOfSection(hFile,pi.hProcess,&RemoteString,0,0,NULL,&ViewSize,ViewShare,0,PAGE_READONLY)==0)
		{
			LPVOID nLoadLibrary=(LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"),"LoadLibraryA");
			//调用QueueUserAPC向远线程插入一个APC，这个APC就是LoadLibrary
			if(!QueueUserAPC((PAPCFUNC)nLoadLibrary,pi.hThread,(ULONG_PTR)0))
			{
				OutputDebugString("[-] APCInject QueueUserAPC call  error!");
				dRet=-6;
			}
				
		}
		else
		{
			OutputDebugString("[-] APCInject NtMapViewOfSection call  error!");
			dRet=-5;
		}
		//恢复主线程
		ResumeThread(pi.hThread);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
	else
	{
		OutputDebugString("[-] APCInject CreateProcess error!");
		dRet=-4;
	}
		
	UnmapViewOfFile(hView);
	CloseHandle(hFile);
	OutputDebugString("[+] APCInject  exit !");
	return dRet;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CApcInjectDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CApcInjectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
#define DLG_FILTER "ALL Files (*.*)|*.*||" 
#define DLG_EXT   "* " 

	CFileDialog dlg(TRUE, _T(DLG_EXT), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T(DLG_FILTER)); 

	if (dlg.DoModal() == IDOK) 
	{ 
		POSITION pos = dlg.GetStartPosition(); 

		while (pos != 0) 
		{ 
			m_strExePath = dlg.GetNextPathName(pos); 
		} 
		UpdateData(FALSE);
	} 
}

void CApcInjectDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
#define DLG_FILTER "ALL Files (*.*)|*.*||" 
#define DLG_EXT   "* " 

	CFileDialog dlg(TRUE, _T(DLG_EXT), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, _T(DLG_FILTER)); 

	if (dlg.DoModal() == IDOK) 
	{ 
		POSITION pos = dlg.GetStartPosition(); 

		while (pos != 0) 
		{ 
			m_strDllPath = dlg.GetNextPathName(pos); 
		} 
		UpdateData(FALSE);
	} 
}

void CApcInjectDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	APCInject( m_strExePath.GetBuffer(m_strExePath.GetLength()),m_strDllPath.GetBuffer(m_strDllPath.GetLength()));
}
