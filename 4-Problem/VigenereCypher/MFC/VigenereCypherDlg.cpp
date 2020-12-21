
// VigenereCypherDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VigenereCypher.h"
#include "VigenereCypherDlg.h"
#include "afxdialogex.h"
#include "LibFileMapping.h"
#include "LibVigenere.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
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
public:
};

CAboutDlg::CAboutDlg() : CDialog(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVigenereCypherDlg dialog



CVigenereCypherDlg::CVigenereCypherDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_VIGENERECYPHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_VIGENERE);
}

void CVigenereCypherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_edit_key);
	DDX_Control(pDX, IDC_LIST_FILE, m_list_fname);
}

BEGIN_MESSAGE_MAP(CVigenereCypherDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_KEY, &CVigenereCypherDlg::OnBnClickedBtnKey)
	ON_BN_CLICKED(IDC_BTN_BROWSE, &CVigenereCypherDlg::OnBnClickedBtnBrowse)
	ON_BN_CLICKED(IDC_BTN_CLEARITEM, &CVigenereCypherDlg::OnBnClickedBtnClearitem)
	ON_BN_CLICKED(IDC_BTN_CRYPT, &CVigenereCypherDlg::OnBnClickedBtnCrypt)
	ON_BN_CLICKED(IDC_BTN_DECRYPT, &CVigenereCypherDlg::OnBnClickedBtnDecrypt)
END_MESSAGE_MAP()


// CVigenereCypherDlg message handlers

BOOL CVigenereCypherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// List Control设置表头
	CString str[] = { L"ID", L"文件路径" };
	m_list_fname.InsertColumn(0, str[0], LVCFMT_LEFT, 40);
	m_list_fname.InsertColumn(1, str[1], LVCFMT_LEFT, 300);

	// List Control设置属性, 显示表格
	m_list_fname.SetExtendedStyle(m_list_fname.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_fname.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);  // 水平滚动条

	// 把临时路径添加到List Control 
	m_list_fname.InsertItem(m_iListItemCount, L"0");
	m_list_fname.SetItemText(m_iListItemCount++, 1, L"~/please/input/a/path/");

	// 设置文件大小
	m_pFileSize = new DWORD;
	*m_pFileSize = 0x0;


	// TODE: END
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVigenereCypherDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVigenereCypherDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVigenereCypherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CVigenereCypherDlg::OnBnClickedBtnKey() {
	// 从Edit Contrl接收输入
	CString csKey;
	m_edit_key.GetWindowTextW(csKey);

	BOOL isValidKey = TRUE;
	if (csKey.GetLength() <= 0 || csKey.GetLength() >= 129) {
		MessageBoxW(L"请输入一个小于128位的字符串!", L"密钥合法性验证");
		isValidKey = FALSE;
	}
	
	if (isValidKey) {
		WCHAR tmpKey[130] = { 0x0 };
		wcscpy_s(tmpKey, 128, csKey);
		sprintf_s(m_szKey, 128, "%ws", tmpKey);
		
		// 限定密码只能是大小写字母和数字
		char* ptr = m_szKey;
		for (ptr; *ptr != '\0'; ptr++) {
			if ( (*ptr >= '0' && *ptr <= '9') 
				|| (*ptr >= 'a' && *ptr <= 'z') 
				|| (*ptr >= 'A' && *ptr <= 'Z') 
			) 
			{
				isValidKey = TRUE;
			}
			else {
				isValidKey = FALSE;
				MessageBoxW(L"密钥只能是字母和数字!", L"密钥合法性验证");
				break;
			}
		}
	}

	// 计算密钥的相对偏移量, 防止后续运算直接使用他们的ASCII码时发生溢出
	if (isValidKey) {
		char* ptr = m_szKey;
		for (ptr; *ptr != '\0'; ptr++) {
			if (*ptr >= '0' && *ptr <= '9')
				*ptr -= '0';
			if (*ptr >= 'a' && *ptr <= 'z')
				*ptr -= 'a';
			if (*ptr >= 'A' && *ptr <= 'Z')
				*ptr -= 'A';
		}
		MessageBoxW(L"密钥输入成功!", L"密钥合法性验证");
	}
}


void CVigenereCypherDlg::OnBnClickedBtnBrowse() {
	// 获取输入文件的名字
	CFileDialog* lpszOpenFile = new CFileDialog(
		TRUE,		// TRUE为打开文件, 否则为保存文件
		NULL,		// 默认扩展名
		NULL,		// 初始文件名
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		NULL		// 无过滤文件格式的选项
	);
	if (lpszOpenFile->DoModal() == IDOK) {
		CString csName = lpszOpenFile->GetPathName();	//得到打开文件的路径
		wcscpy_s(m_FilePath, MAX_PATH,csName);

		// 把结果添加到List Control上
		WCHAR tmp[4] = { 0x0 };
		wsprintf(tmp, L"%d", m_iListItemCount);
		m_list_fname.InsertItem(m_iListItemCount, tmp);
		m_list_fname.SetItemText(m_iListItemCount++, 1, m_FilePath);
	}

	delete lpszOpenFile;	//释放分配的对话框
}


void CVigenereCypherDlg::OnBnClickedBtnClearitem() {
	// 清除List Contrl上你选中的一条记录
	POSITION pos = m_list_fname.GetFirstSelectedItemPosition();
	while (pos) {
		int row = m_list_fname.GetNextSelectedItem(pos);
		m_list_fname.DeleteItem(row);
		m_iListItemCount--;
	}
}


DWORD __stdcall CVigenereCypherDlg:: ThreadFuncCrypt(VOID* lpParam) {
	// 转换指针类型
	CVigenereCypherDlg* me = reinterpret_cast<CVigenereCypherDlg*>(lpParam);

	// 获取需要加密的文件映射
	if (me->isValid) {
		me->m_pInFile = FileMapping(me->m_FilePath, 0x1, me->m_pFileSize);  // Read Mode
		if (nullptr == me->m_pInFile) {
			me->MessageBoxW(L"获取映射文件指针失败!", L"Input File");
			me->isValid = FALSE;
		}
	}

	if (me->isValid) {
		WCHAR szOutFile[MAX_PATH] = { 0x0 };
		wsprintf(szOutFile, L"%s", L"./crypted.txt");
		me->m_pOutFile = FileMapping(szOutFile, 0x0, me->m_pFileSize);  // Write Mode
		if (nullptr == me->m_pOutFile) {
			me->MessageBoxW(L"获取映射文件指针失败!", L"Output File");
			me->isValid = FALSE;
		}
	}

	// 加密数据
	if (me->isValid) {
		UINT keyNum = strlen(me->m_szKey);

		if (
			do_VigenereCrypt(
				me->m_pOutFile, 
				me->m_pInFile, 
				keyNum, 
				me->m_szKey,
				*(me->m_pFileSize))
		) 
		{
			me->MessageBoxW(L"加密成功!", L"加密过程");
		}
		else {
			me->MessageBoxW(L"加密失败!", L"加密过程");
			me->isValid = FALSE;
		}
	}

	// 关闭映射
	::UnmapViewOfFile(me->m_pInFile);
	::UnmapViewOfFile(me->m_pOutFile);
	return 0;
}


void CVigenereCypherDlg::OnBnClickedBtnCrypt() {
	this->isValid = TRUE;

	// 如果密钥为空, 不加密
	if (m_szKey == "") {
		isValid = FALSE;
	}

	// 获取选中的路径
	if (isValid) {
		POSITION pos = m_list_fname.GetFirstSelectedItemPosition();
		while (pos) {
			int row = m_list_fname.GetNextSelectedItem(pos);

			CString szTmpGetPath = m_list_fname.GetItemText(row, 1);
			wcscpy_s(m_FilePath, MAX_PATH, szTmpGetPath);
		}
		if (m_FilePath == 0x0) {
			MessageBoxW(L"不能是空路径!", L"路径合法性检验");
			isValid = FALSE;
		}
	}

	// 创建一个线程, 并执行加密过程
	DWORD ID_mainThread = 0x0;
	HANDLE hCryptThread = ::CreateThread(
		NULL,	// Default safe attribute
		0x0,	// Default stack size
		ThreadFuncCrypt,
		this,	// A pointer to a variable to be passed to the thread
		0x0,	// The thread runs immediately after creation
		&ID_mainThread
	);

	::CloseHandle(hCryptThread);
}


DWORD __stdcall CVigenereCypherDlg::ThreadFuncDecrypt(VOID* lpParam) {
	// 转换指针类型
	CVigenereCypherDlg* me = reinterpret_cast<CVigenereCypherDlg*>(lpParam);

	// 获取需要加密的文件映射
	if (me->isValid) {
		me->m_pInFile = FileMapping(me->m_FilePath, 0x1, me->m_pFileSize);  // Read Mode
		if (nullptr == me->m_pInFile) {
			me->MessageBoxW(L"获取映射文件指针失败!", L"Input File");
			me->isValid = FALSE;
		}
	}

	if (me->isValid) {
		WCHAR szOutFile[MAX_PATH] = { 0x0 };
		wsprintf(szOutFile, L"%s", L"./decrypted.txt");
		me->m_pOutFile = FileMapping(szOutFile, 0x0, me->m_pFileSize);  // Write Mode
		if (nullptr == me->m_pOutFile) {
			me->MessageBoxW(L"获取映射文件指针失败!", L"Output File");
			me->isValid = FALSE;
		}
	}

	// 解密数据
	if (me->isValid) {
		UINT keyNum = strlen(me->m_szKey);

		if (
			do_VigenereDecrypt(
				me->m_pOutFile,
				me->m_pInFile,
				keyNum,
				me->m_szKey,
				*(me->m_pFileSize))
			) {
			me->MessageBoxW(L"解密成功!", L"解密过程");
		}
		else {
			me->MessageBoxW(L"解密失败!", L"解密过程");
			me->isValid = FALSE;
		}
	}

	// 关闭映射
	::UnmapViewOfFile(me->m_pInFile);
	::UnmapViewOfFile(me->m_pOutFile);
	return 0;
}


void CVigenereCypherDlg::OnBnClickedBtnDecrypt() {
	this->isValid = TRUE;

	// 如果密钥为空, 不加密
	if (m_szKey == "") {
		isValid = FALSE;
	}

	// 获取选中的路径
	if (isValid) {
		POSITION pos = m_list_fname.GetFirstSelectedItemPosition();
		while (pos) {
			int row = m_list_fname.GetNextSelectedItem(pos);

			CString szTmpGetPath = m_list_fname.GetItemText(row, 1);
			wcscpy_s(m_FilePath, MAX_PATH, szTmpGetPath);
		}
		if (m_FilePath == 0x0) {
			MessageBoxW(L"不能是空路径!", L"路径合法性检验");
			isValid = FALSE;
		}
	}


	// 创建一个线程, 并执行解密过程
	DWORD ID_mainThread = 0x0;
	HANDLE hCryptThread = ::CreateThread(
		NULL,	// Default safe attribute
		0x0,	// Default stack size
		ThreadFuncDecrypt,
		this,	// A pointer to a variable to be passed to the thread
		0x0,	// The thread runs immediately after creation
		&ID_mainThread
	);

	::CloseHandle(hCryptThread);
}
