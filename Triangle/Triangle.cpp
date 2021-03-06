
// Triangle.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "Triangle.h"
#include "TriangleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTriangleApp

BEGIN_MESSAGE_MAP(CTriangleApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTriangleApp 构造

CTriangleApp::CTriangleApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CTriangleApp 对象

CTriangleApp theApp;


// CTriangleApp 初始化

BOOL CTriangleApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CTriangleDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}



Triangle::Triangle()
{
}

Triangle::Triangle(CPoint pp1, CPoint pp2, CPoint pp3)
{
	if (pp1.x < pp2.x && pp1.x < pp3.x)
	{
		left = pp1;
		if (pp2.x < pp3.x)
		{
			mid = pp2;
			right = pp3;
		}
		else
		{
			mid = pp3;
			right = pp2;
		}
	}
	else if (pp2.x < pp1.x && pp2.x < pp3.x)
	{
		left = pp2;
		if (pp1.x < pp3.x)
		{
			mid = pp1; right = pp3;
		}
		else
		{
			mid = pp3; right = pp1;
		}
	}
	else
	{
		left = pp3;
		if (pp1.x < pp2.x)
		{
			mid = pp1;
			right = pp2;
		}
		else
		{
			mid = pp2; right = pp1;
		}
	}


	//计算外接圆圆心和半径平方
	double ax = mid.x - left.x;
	double ay = mid.y - left.y;
	double bx = right.x - left.x;
	double by = right.y - left.y;

	const double m = mid.x * mid.x - left.x*left.x + mid.y * mid.y - left.y * left.y;
	const double u = right.x * right.x + right.y *right.y - left.x * left.x - left.y * left.y;
	const double s = 1. / (2 * (ax * by - ay * bx));

	circle_centerx = ((right.y - left.y)*m + (left.y - mid.y)*u)*s;
	circle_centery = ((left.x - right.x) * m + (mid.x - left.x)*u)*s;

	double dx = left.x - circle_centerx;
	double dy = left.y - circle_centery;
	radius2 = dx * dx + dy * dy;

}

Triangle::Triangle(const Triangle & t):
	left(t.left),mid(t.mid),right(t.right),
	radius2(t.radius2),circle_centerx(t.circle_centerx),circle_centery(t.circle_centery)
{
}

Triangle & Triangle::operator=(const Triangle & t)
{
	left = t.left; mid = t.mid; right = t.right;
	radius2 = t.radius2; circle_centerx = t.circle_centerx, circle_centery = t.circle_centery;
	return *this;
}

//该点是否在外接圆内
bool Triangle::CircleContain(const CPoint & p)const
{
	double d = ((p.x - circle_centerx)*(p.x - circle_centerx) + (p.y - circle_centery)*(p.y - circle_centery));
	return d < radius2;
}

bool Triangle::Contain(const CPoint & p)
{
	CPoint vec1(p.x - left.x, p.y - left.y);
	CPoint vec2(p.x - mid.x, p.y - mid.y);
	CPoint vec3(p.x - right.x, p.y - right.y);
	CPoint vec12(vec1.x + vec2.x, vec1.y + vec2.y);
	if (vec12.x * vec3.x + vec12.y * vec3.y > 0)
		return false;
	else
		return true;
}

void Triangle::Draw(CDC * pDC)
{
	if (pDC)
	{
		pDC->MoveTo(left); pDC->LineTo(mid);
		pDC->MoveTo(mid); pDC->LineTo(right);
		pDC->MoveTo(right); pDC->LineTo(left);
	}
}

void Triangle::GetBoundingCircle(CPoint * center, int * radius)
{

}

Triangle::~Triangle()
{
}


bool cmp(const Edge & e1, const Edge & e2)
{
	if (min(e1.p1.x, e1.p2.x) < min(e2.p1.x, e2.p2.x))
		return true;
	else if (min(e1.p1.x, e1.p2.x) == min(e2.p1.x, e2.p2.x))
		return min(e1.p1.y, e1.p2.y) < min(e2.p1.y, e2.p2.y);
	else
		return false;
}

void swap(Triangle & t1, Triangle & t2)
{
	//确定两个三角形是否有公共边
	
}


bool cmpPoint(const CPoint& p1, const CPoint& p2)
{
	if (p1.x == p2.x)return p1.y < p2.y;
	else return p1.x < p2.x;
}
