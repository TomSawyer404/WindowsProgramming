
// CaserCypherDlg.h : header file
//

#pragma once


// CCaserCypherDlg dialog
class CCaserCypherDlg : public CDialog
{
// Construction
public:
	CCaserCypherDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CASERCYPHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	UINT m_iListItemCount = 0;
	UINT m_uiKey = 0x0;
	WCHAR m_FilePath[MAX_PATH] = {0x0};
	CEdit m_edit_key;
	CListCtrl m_list_fname;
	char* m_pInFile = nullptr;
	char* m_pOutFile = nullptr;
	DWORD* m_pFileSize = nullptr;

public:
	afx_msg void OnBnClickedButKey();
	afx_msg void OnBnClickedButClearitem();
	afx_msg void OnBnClickedButBrowese();
	afx_msg void OnBnClickedButCrypt();
	afx_msg void OnBnClickedButDecrypt();
};
