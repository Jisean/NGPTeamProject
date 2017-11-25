// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool58.h"
#include "UnitTool.h"


// CUnitTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTool::IDD, pParent)
	, m_strTemp(_T(""))
	, m_strCopy(_T(""))
	, m_strName(_T(""))
	, m_fAttack(0.f)
	, m_iHp(0)
	, m_fTears(0.f)
	, m_fShotSpeed(0.f)
	, m_fRange(0.f)
	, m_iLuck(0)
	, m_fSpeed(0.f)
	, m_iCoins(0)
	, m_iKeys(0)
	, m_iBombs(0)
	, m_bStart(true)
	, m_strFindName(_T(""))
{

}

CUnitTool::~CUnitTool()
{
	for_each(m_MapUnitData.begin(), m_MapUnitData.end(), DELETEMAP());
	m_MapUnitData.clear();

}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_strName);
	DDX_Text(pDX, IDC_EDIT4, m_fAttack);
	DDX_Text(pDX, IDC_EDIT5, m_iHp);
	DDX_Text(pDX, IDC_EDIT1, m_fTears);
	DDX_Text(pDX, IDC_EDIT2, m_fShotSpeed);
	DDX_Text(pDX, IDC_EDIT6, m_fRange);
	DDX_Text(pDX, IDC_EDIT8, m_iLuck);
	DDX_Text(pDX, IDC_EDIT9, m_fSpeed);
	DDX_Text(pDX, IDC_EDIT10, m_iCoins);
	DDX_Text(pDX, IDC_EDIT11, m_iKeys);
	DDX_Text(pDX, IDC_EDIT12, m_iBombs);

	DDX_Control(pDX, IDC_LIST1, m_ListBox);


	DDX_Text(pDX, IDC_EDIT7, m_strFindName);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTool::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTool::OnUnitAdd)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTool::OnDeleteButton)
	ON_EN_CHANGE(IDC_EDIT7, &CUnitTool::OnSearchFunc)
	ON_BN_CLICKED(IDC_BUTTON6, &CUnitTool::OnSaveFunc)
	ON_BN_CLICKED(IDC_BUTTON5, &CUnitTool::OnLoadFunc)
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


void CUnitTool::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);
	
	m_strCopy = m_strTemp;

	UpdateData(FALSE);

}

void CUnitTool::OnUnitAdd()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	UNITDATA*		pUnitData = new UNITDATA;

	pUnitData->wstrName = m_strName;
	pUnitData->fAttack  = m_fAttack;
	pUnitData->iHp		= m_iHp;
	pUnitData->fTears	= m_fTears;
	pUnitData->fShotSpeed = m_fShotSpeed;
	pUnitData->fRange	= m_fRange;
	pUnitData->iLuck	= m_iLuck;
	pUnitData->fSpeed	= m_fSpeed;
	pUnitData->iCoins	= m_iCoins;
	pUnitData->iKeys	= m_iKeys;
	pUnitData->iBombs	= m_iBombs;



	m_ListBox.AddString(m_strName);
	m_MapUnitData.insert(make_pair(m_strName, pUnitData));

	
	UpdateData(FALSE);

}

void CUnitTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CString		m_strSelectName;

	int		iSelectIndex = m_ListBox.GetCurSel();	// Ŭ���� ����Ʈ �ڽ��� �� �ε����� ã���ִ� �Լ�;

	if(iSelectIndex < 0)
		return;

	m_ListBox.GetText(iSelectIndex, m_strSelectName);

	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(m_strSelectName);

	if(iter == m_MapUnitData.end())
		return;

	m_strName = iter->second->wstrName.c_str();
	m_fAttack = iter->second->fAttack;
	m_iHp     = iter->second->iHp;
	m_fTears = iter->second->fTears;
	m_fShotSpeed = iter->second->fShotSpeed;
	m_fRange = iter->second->fRange;
	m_iLuck = iter->second->iLuck;
	m_fSpeed = iter->second->fSpeed;
	m_iCoins = iter->second->iCoins;
	m_iKeys = iter->second->iKeys;
	m_iBombs = iter->second->iBombs;

	

	UpdateData(FALSE);

}

void CUnitTool::OnDeleteButton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	CString		strSelectName;

	int			iSelect = m_ListBox.GetCurSel();

	if(iSelect < 0)
		return;

	m_ListBox.GetText(iSelect, strSelectName);

	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(strSelectName);

	if(iter == m_MapUnitData.end())
		return;

	Safe_Delete(iter->second);
	m_MapUnitData.erase(iter);

	m_ListBox.DeleteString(iSelect);


	UpdateData(FALSE);

}

void CUnitTool::OnSearchFunc()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	UpdateData(TRUE);

	map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.find(m_strFindName);

	if(iter == m_MapUnitData.end())
		return;

	int		iSelect = m_ListBox.FindString(0, m_strFindName);

	if(iSelect < 0)
		return;

	m_ListBox.SetCurSel(iSelect);

	m_strName = iter->second->wstrName.c_str();
	m_fAttack = iter->second->fAttack;
	m_iHp     = iter->second->iHp;
	m_fTears = iter->second->fTears;
	m_fShotSpeed = iter->second->fShotSpeed;
	m_fRange = iter->second->fRange;
	m_iLuck = iter->second->iLuck;
	m_fSpeed = iter->second->fSpeed;
	m_iCoins = iter->second->iCoins;
	m_iKeys = iter->second->iKeys;
	m_iBombs = iter->second->iBombs;
	UpdateData(FALSE);
}

void CUnitTool::OnSaveFunc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	CFileDialog		Dlg(FALSE, L"dat", L"*.dat", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"*.dat", this);

	// 1. ���� ��� ���� 2. ������ Ȯ���ڸ� 3. ���ʿ� ��� �� ���ڿ� 
	// 4. �ߺ� ���� ó���� ���� �Ű� ���� 5. ���� ���Ŀ� ���� Ȯ���ڸ�

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);

	SetCurrentDirectory(szDirPath);
	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �������ִ� �Լ�

	PathRemoveFileSpec(szDirPath);
	// ������ ��θ� ������ ��θ� �����ϴ� �Լ�

	lstrcat(szDirPath, L"..\\Data");


	Dlg.m_ofn.lpstrInitialDir = szDirPath;		// ��� ���

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_WRITE, 
		0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte;

	for(map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.begin();
		iter != m_MapUnitData.end(); ++iter)
	{
		WriteFile(hFile, iter->second, sizeof(UNITDATA), &dwByte, NULL);
	}

	CloseHandle(hFile);


}

void CUnitTool::OnLoadFunc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CFileDialog		Dlg(TRUE, L"dat", L"*.dat", 
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,L"*.dat", this);

	// 1. ���� ��� ���� 2. ������ Ȯ���ڸ� 3. ���ʿ� ��� �� ���ڿ� 
	// 4. �ߺ� ���� ó���� ���� �Ű� ���� 5. ���� ���Ŀ� ���� Ȯ���ڸ�

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);

	SetCurrentDirectory(szDirPath);
	// ���� ���α׷��� ���� �۾� ���丮�� ������ ���丮�� �������ִ� �Լ�

	PathRemoveFileSpec(szDirPath);
	// ������ ��θ� ������ ��θ� �����ϴ� �Լ�

	lstrcat(szDirPath, L"..\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;		// ��� ���

	HANDLE	hFile = CreateFile(Dlg.GetPathName(), GENERIC_READ, 
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD	dwByte;

	while(true)
	{
		UNITDATA*		pUnitData  = new UNITDATA;

		ReadFile(hFile, pUnitData, sizeof(UNITDATA), &dwByte, NULL);

		if(dwByte == 0)
		{
			Safe_Delete(pUnitData);
			break;
		}

		m_MapUnitData.insert(make_pair(pUnitData->wstrName.c_str(), pUnitData));
		m_ListBox.AddString(pUnitData->wstrName.c_str());
	}
	

	CloseHandle(hFile);



	UpdateData(FALSE);
}	