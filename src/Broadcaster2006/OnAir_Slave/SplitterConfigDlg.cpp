// SplitterConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OnAir_Slave.h"
#include "SplitterConfigDlg.h"
#include ".\splitterconfigdlg.h"
#include "..\include\rsradiostations.h"
#include "..\onair\externalobjects.h"


// CSplitterConfigDlg dialog

IMPLEMENT_DYNAMIC(CSplitterConfigDlg, CDialog)
CSplitterConfigDlg::CSplitterConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplitterConfigDlg::IDD, pParent)
	, m_bLine(FALSE)
{
}

CSplitterConfigDlg::~CSplitterConfigDlg()
{
}

void CSplitterConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RADIO, m_cRadio);
	DDX_Control(pDX, IDC_AUDIO, m_cAudio);
	DDX_Control(pDX, IDC_LINEIN, m_cLine);
	DDX_Check(pDX, IDC_MIXERENABLE, m_bLine);
}


BEGIN_MESSAGE_MAP(CSplitterConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSplitterConfigDlg message handlers

BOOL CSplitterConfigDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRSRadioStations	rs(g_strMainConnect);
	rs.m_strSort = "Name";
	rs.Open();

	while( !rs.IsEOF() )
	{
		rs.m_Name.TrimRight();
		int nPos = m_cRadio.AddString(rs.m_Name);
		m_cRadio.SetItemData(nPos,rs.m_ID);
		rs.MoveNext();
	}

	DirectSoundEnumerate(DSEnumCallback,this);

	GetLineIns();

	return TRUE; 
}

BOOL CALLBACK CSplitterConfigDlg::DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	CSplitterConfigDlg *This=(CSplitterConfigDlg *)lpContext;
	CString strTemp;
	int Count=1;
	int Pos = This->m_cAudio.FindStringExact(-1,lpcstrDescription);
	
	strTemp.Format("%s",lpcstrDescription);

	while( Pos!=CB_ERR )
	{
		Count++;
		strTemp.Format("%s (%d)",lpcstrDescription,Count);
		Pos = This->m_cAudio.FindStringExact(-1,strTemp);
	}
	
	This->m_cAudio.AddString(strTemp);

	return TRUE;
}


void CSplitterConfigDlg::GetLineIns()
{
	int		nMixer = mixerGetNumDevs(),
			nLine,
			nLineCount;
	long	Pos;
	MIXERCAPS	MixerCaps;
	MIXERLINE	MixerLine;
	MMRESULT	uError;

	for( int Cont=0; Cont<nMixer; Cont++ )
	{
		mixerGetDevCaps(Cont,&MixerCaps,sizeof(MIXERCAPS));

		MixerLine.cbStruct=sizeof(MIXERLINE);
		MixerLine.dwDestination=0;
			
		uError=mixerGetLineInfo((HMIXEROBJ)Cont,&MixerLine,MIXER_GETLINEINFOF_DESTINATION|MIXER_OBJECTF_MIXER);
		nLineCount = MixerLine.cConnections;

		for( nLine=0; nLine<nLineCount; nLine++ )
		{
			MixerLine.cbStruct=sizeof(MIXERLINE);
			MixerLine.dwDestination=0;
			MixerLine.dwSource=nLine;
			uError=mixerGetLineInfo((HMIXEROBJ)Cont,&MixerLine,MIXER_GETLINEINFOF_SOURCE|MIXER_OBJECTF_MIXER);
			if( uError==MMSYSERR_NOERROR )
			{
				typeMixerLine *pLine = new typeMixerLine;
				pLine->dwLineID = MixerLine.dwLineID;
				pLine->dwMixerID = Cont;

				Pos=m_cLine.AddString(CString(MixerCaps.szPname)+" - "+CString(MixerLine.szName));
				m_cLine.SetItemData(Pos,(DWORD)pLine);
			}
		}
	}
}

void CSplitterConfigDlg::OnBnClickedOk()
{
	UpdateData();

	int nRadio = m_cRadio.GetCurSel(),
		nAudio = m_cAudio.GetCurSel(),
		nLine = m_cLine.GetCurSel();

	if( nRadio==CB_ERR )
		return;
	
	if( nAudio==CB_ERR )
		return;

	if( m_bLine && (nLine==CB_ERR) )
		return;

	typeMixerLine *pMixer;

	pMixer = (typeMixerLine *)m_cLine.GetItemData(nLine);
	m_Mixer.dwLineID = pMixer->dwLineID;
	m_Mixer.dwMixerID = pMixer->dwMixerID;

	m_cAudio.GetLBText(nAudio,m_strAudioOut);

	long lRadioID = m_cRadio.GetItemData(nRadio);
	CRSRadioStations	rs( g_strMainConnect );

	rs.m_strFilter.Format("ID = '%d'",lRadioID);
	rs.Open();
	if( rs.GetRecordCount()==0 )
	{
		rs.Close();
		return;
	}
	m_strConnect = rs.m_DSN;
	m_strConnect.TrimRight();

	m_strRadioName = rs.m_Name;
	m_strRadioName.TrimRight();

	rs.Close();

	OnOK();
}
