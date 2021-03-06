
// TriangleDlg.h: 头文件
//

#pragma once
#include <vector>
#include <list>

// CTriangleDlg 对话框
class CTriangleDlg : public CDialogEx
{
// 构造
public:
	CTriangleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRIANGLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CButton groupbox;
	size_t rand_num;
	std::vector<CPoint>points;
	std::list<Triangle>triangles;
	afx_msg void OnBnClickedBtnRandpoints();
	afx_msg void OnBnClickedBtnTriangle();
private:
	int maxX = 0;
	int minX = INT_MAX;
	int minY = INT_MAX;
	int maxY = 0;
	void Bowyer_Lawson();
public:
	afx_msg void OnEnUpdateEdit1();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};
