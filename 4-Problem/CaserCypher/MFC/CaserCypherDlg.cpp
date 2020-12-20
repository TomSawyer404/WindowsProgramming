
// CaserCypherDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CaserCypher.h"
#include "CaserCypherDlg.h"
#include "afxdialogex.h"
#include "LibFileMapping.h"
#include "LibCaser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCaserCypherDlg dialog



CCaserCypherDlg::CCaserCypherDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CASERCYPHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON_BANANA);
}

void CCaserCypherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_edit_key);
	DDX_Control(pDX, IDC_LIST_FNAME, m_list_fname);
}

BEGIN_MESSAGE_MAP(CCaserCypherDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_KEY, &CCaserCypherDlg::OnBnClickedButKey)
	ON_BN_CLICKED(IDC_BUT_CLEARITEM, &CCaserCypherDlg::OnBnClickedButClearitem)
	ON_BN_CLICKED(IDC_BUT_BROWESE, &CCaserCypherDlg::OnBnClickedButBrowese)
	ON_BN_CLICKED(IDC_BUT_CRYPT, &CCaserCypherDlg::OnBnClickedButCrypt)
	ON_BN_CLICKED(IDC_BUT_DECRYPT, &CCaserCypherDlg::OnBnClickedButDecrypt)
END_MESSAGE_MAP()


// CCaserCypherDlg message handlers

BOOL CCaserCypherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// List Contrl设置表头
	CString str[] = { L"ID", L"文件路径" };
	m_list_fname.InsertColumn(0, str[0], LVCFMT_LEFT, 40);
	m_list_fname.InsertColumn(1, str[1], LVCFMT_LEFT, 300);

	// List Contrl设置属性, 显示表格
	m_list_fname.SetExtendedStyle(m_list_fname.GetExtendedStyle()
		| LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_list_fname.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);  // 水平滚动条

	// 把临时路径添加到list contorl 
	m_list_fname.InsertItem(m_iListItemCount, L"0");
	m_list_fname.SetItemText(m_iListItemCount++, 1, L"~/please/input/a/path/");

	m_pFileSize = new DWORD;
	*m_pFileSize = 0x0;


	// TODO: END
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCaserCypherDlg::OnPaint()
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
HCURSOR CCaserCypherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCaserCypherDlg::OnBnClickedButKey() {
	// 从Edit Contrl接收输入
	CString csKey;
	m_edit_key.GetWindowTextW(csKey);

	BOOL isValidKey = TRUE;
	if (csKey.GetLength() <= 0 || csKey.GetLength() >= 4) {
		MessageBoxW(L"请输入一个3位数的非负整数!", L"密钥合法性验证");
		isValidKey = FALSE;
	}
	if (isValidKey) {
		for (int i = 0; i < csKey.GetLength(); i++) {
			WCHAR tmpChar = csKey.GetAt(i);
			if (tmpChar < '0' || tmpChar > '9') {
				MessageBoxW(L"请输入合法的数字!", L"密钥合法性验证");
				isValidKey = FALSE;
				break;
			}
		}
	}

	// 把输入转换为数字 
	if (isValidKey) {
		m_uiKey = _wtoi(csKey);
		MessageBoxW(L"输入密钥成功!", L"密钥输入过程");
	}
}


void CCaserCypherDlg::OnBnClickedButClearitem() {
	// 清除List Contrl上你选中的一条记录
	POSITION pos = m_list_fname.GetFirstSelectedItemPosition();
	while (pos) {
		int row = m_list_fname.GetNextSelectedItem(pos);
		m_list_fname.DeleteItem(row);
		m_iListItemCount--;
	}
}


void CCaserCypherDlg::OnBnClickedButBrowese() {
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
		wcscpy(m_FilePath, csName);

		// 把结果添加到List Control上
		WCHAR tmp[4] = { 0x0 };
		wsprintf(tmp, L"%d", m_iListItemCount);
		m_list_fname.InsertItem(m_iListItemCount, tmp);
		m_list_fname.SetItemText(m_iListItemCount++, 1, m_FilePath);
	}

	delete lpszOpenFile;	//释放分配的对话框
}


void CCaserCypherDlg::OnBnClickedButCrypt() {
	BOOL isValid = TRUE;

	// 获取选中的路径
	POSITION pos = m_list_fname.GetFirstSelectedItemPosition();
	while (pos) {
		int row = m_list_fname.GetNextSelectedItem(pos);

		CString szTmpGetPath = m_list_fname.GetItemText(row, 1);
		wcscpy(m_FilePath, szTmpGetPath);
	}
	if (m_FilePath == 0x0) {
		MessageBoxW(L"不能是空路径!", L"路径合法性检验");
		isValid = FALSE;
	}

	// 封装进线程------------------------------------------------

	// 获取需要加密的文件映射
	if (isValid) {
		m_pInFile = FileMapping(m_FilePath, 0x1, m_pFileSize);  // Read Mode
		if (nullptr == m_pInFile) {
			MessageBoxW(L"获取映射文件指针失败!", L"Input File");
			isValid = FALSE;
		}
	}
	
	if (isValid) {
		WCHAR szOutFile[MAX_PATH] = { 0x0 };
		wsprintf(szOutFile, L"%s", L"./crypted.txt");
		m_pOutFile = FileMapping(szOutFile, 0x0, m_pFileSize);  // Write Mode
		if (nullptr == m_pOutFile) {
			MessageBoxW(L"获取映射文件指针失败!", L"Output File");
			isValid = FALSE;
		}
	}

	// 加密数据
	if (isValid) {
		if (do_CaserCrypt(m_pOutFile, m_pInFile, m_uiKey, *m_pFileSize)) {
			MessageBoxW(L"加密成功!", L"加密过程");
		}
		else {
			MessageBoxW(L"加密失败!", L"加密过程");
			isValid = FALSE;
		}
	}

	// 关闭映射
	::UnmapViewOfFile(m_pInFile);
	::UnmapViewOfFile(m_pOutFile);

	// 封装进线程------------------------------------------------
}


void CCaserCypherDlg::OnBnClickedButDecrypt() {
	BOOL isValid = TRUE;

	// 获取选中的路径
	POSITION pos = m_list_fname.GetFirstSelectedItemPosition();
	while (pos) {
		int row = m_list_fname.GetNextSelectedItem(pos);

		CString szTmpGetPath = m_list_fname.GetItemText(row, 1);
		wcscpy(m_FilePath, szTmpGetPath);
	}
	if (m_FilePath == 0x0) {
		MessageBoxW(L"不能是空路径!", L"路径合法性检验");
		isValid = FALSE;
	}

	// 封装进线程------------------------------------------------

	// 获取需要加密的文件映射
	if (isValid) {
		m_pInFile = FileMapping(m_FilePath, 0x1, m_pFileSize);  // Read Mode
		if (nullptr == m_pInFile) {
			MessageBoxW(L"获取映射文件指针失败!", L"Input File");
			isValid = FALSE;
		}
	}
	
	if (isValid) {
		WCHAR szOutFile[MAX_PATH] = { 0x0 };
		wsprintf(szOutFile, L"%s", L"./decrypted.txt");
		m_pOutFile = FileMapping(szOutFile, 0x0, m_pFileSize);  // Write Mode
		if (nullptr == m_pOutFile) {
			MessageBoxW(L"获取映射文件指针失败!", L"Output File");
			isValid = FALSE;
		}
	}

	// 加密数据
	if (isValid) {
		if (do_CaserDecrypt(m_pOutFile, m_pInFile, m_uiKey, *m_pFileSize)) {
			MessageBoxW(L"解密成功!", L"加密过程");
		}
		else {
			MessageBoxW(L"解密失败!", L"加密过程");
			isValid = FALSE;
		}
	}

	// 关闭映射
	::UnmapViewOfFile(m_pInFile);
	::UnmapViewOfFile(m_pOutFile);

	// 封装进线程------------------------------------------------
}


