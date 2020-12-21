
// VigenereCypherDlg.h : header file
//

#pragma once


// CVigenereCypherDlg dialog
class CVigenereCypherDlg : public CDialog
{
// Construction
public:
	CVigenereCypherDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIGENERECYPHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	UINT m_iListItemCount = 0;				// 列表条目计数
	CHAR m_szKey[130] = { 0x0 };			// 用户输入的密钥, 用于运算
	WCHAR m_FilePath[MAX_PATH] = { 0x0 };	// 输入的路径
	CEdit m_edit_key;						// 编辑控件
	CListCtrl m_list_fname;					// 列表控件
	char* m_pInFile = nullptr;				// 探测输入的映射文件的指针
	char* m_pOutFile = nullptr;				// 探测输出的映射文件的指针
	DWORD* m_pFileSize = nullptr;			// 标识文件大小的指针
	BOOL isValid = FALSE;					// 过程合法性标识

	static DWORD __stdcall ThreadFuncCrypt(VOID* lpParam);
	static DWORD __stdcall ThreadFuncDecrypt(VOID* lpParam);

public:
	afx_msg void OnBnClickedBtnKey();
	afx_msg void OnBnClickedBtnBrowse();
	afx_msg void OnBnClickedBtnClearitem();
	afx_msg void OnBnClickedBtnCrypt();
	afx_msg void OnBnClickedBtnDecrypt();
};
