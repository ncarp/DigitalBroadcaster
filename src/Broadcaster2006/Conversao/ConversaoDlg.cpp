// ConversaoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConversaoDlg.h"
#include <io.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include "..\include\RSPath.h"
#include "..\include\RSCategories.h"
#include "..\include\RSExpressions.h"
#include "..\include\RSNationalities.h"
#include "..\include\RSRecordLabel.h"
#include "..\include\RSArtists.h"
#include "..\include\RSPlayListsDefinition.h"
#include "..\include\RSMusicTracks.h"
#include "..\include\RSJingles.h"
#include "..\include\RSTypeOfJingle.h"
#include "..\include\RSCustomer.h"
#include "..\include\RSSpots.h"
#include "..\include\RSBusiness.h"
#include "..\common\include\wavefile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <share.h>

CString strMainConnect="Broadcaster";
CString strAntenaConnect="Broadcaster-OnAir";

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConversaoDlg dialog

CConversaoDlg::CConversaoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConversaoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConversaoDlg)
	m_Actividades = FALSE;
	m_Agencias = FALSE;
	m_Clientes = FALSE;
	m_Discos = FALSE;
	m_Editoras = FALSE;
	m_Faixas = FALSE;
	m_Generos = FALSE;
	m_Interpretes = FALSE;
	m_Jingles = FALSE;
	m_Listas = FALSE;
	m_Nacionalidades = FALSE;
	m_Spots = FALSE;
	m_Vendedores = FALSE;
	m_bDeleteOriginal = FALSE;
	m_bAudioExists = FALSE;
	m_bConvertAudio = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConversaoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConversaoDlg)
	DDX_Control(pDX, IDC_DELETEORIGINAL, m_cDeleteOriginal);
	DDX_Control(pDX, IDC_TITULO, m_Titulo);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress1);
	DDX_Control(pDX, IDC_PROGRESS2, m_Progress2);
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_TEXTO, m_Texto);
	DDX_Control(pDX, IDCANCEL, m_Teste);
	DDX_Check(pDX, IDC_ACTIVIDADES, m_Actividades);
	DDX_Check(pDX, IDC_Agencias, m_Agencias);
	DDX_Check(pDX, IDC_Clientes, m_Clientes);
	DDX_Check(pDX, IDC_DISCOS, m_Discos);
	DDX_Check(pDX, IDC_EDITORAS, m_Editoras);
	DDX_Check(pDX, IDC_FAIXAS, m_Faixas);
	DDX_Check(pDX, IDC_GENEROS, m_Generos);
	DDX_Check(pDX, IDC_INTERPRETES, m_Interpretes);
	DDX_Check(pDX, IDC_JINGLES, m_Jingles);
	DDX_Check(pDX, IDC_LISTAS, m_Listas);
	DDX_Check(pDX, IDC_NACIONALIDADES, m_Nacionalidades);
	DDX_Check(pDX, IDC_SPOTS, m_Spots);
	DDX_Check(pDX, IDC_Vendedores, m_Vendedores);
	DDX_Check(pDX, IDC_DELETEORIGINAL, m_bDeleteOriginal);
	DDX_Check(pDX, IDC_AUDIOEXISTS, m_bAudioExists);
	DDX_Check(pDX, IDC_CONVERTAUDIO, m_bConvertAudio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CConversaoDlg, CDialog)
	//{{AFX_MSG_MAP(CConversaoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONVERTAUDIO, OnConvertaudio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConversaoDlg message handlers

BOOL CConversaoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	bmTeste.LoadBitmap(IDB_INTERROGACAO);
	m_Teste.SetBitmap( bmTeste );
	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	LeDiscos();
	LeDiscosV5();
	LeTipos();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConversaoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConversaoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConversaoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CConversaoDlg::OnOK() 
{
	UpdateData( TRUE );

	if( m_Discos )
		ConverteDiscos();

	if( m_Generos )
		ConverteGeneros();

	if( m_Nacionalidades )
		ConverteNacionalidades();

	if( m_Editoras )
		ConverteEditoras();

	if( m_Interpretes )
		ConverteInterpretes();

	if( m_Listas )
		ConverteListas();

	if( m_Faixas )
		ConverteFaixas(); 

	if( m_Jingles )
		ConverteJingles();
/*
	if( m_Vendedores )
		ConverteVendedores();

	if( m_Agencias )
		ConverteAgencias();
*/
	if( m_Actividades )
		ConverteActividades();

	if( m_Clientes )
		ConverteClientes(); 

	if( m_Spots )
		ConverteSpots(); 
/*
	if( m_Blocos )
		ConverteBlocos();
*/

	AfxMessageBox( "Conversão concluida com exito" );
	CDialog::OnOK();
}

void CConversaoDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CConversaoDlg::LeDiscos()
{
	CFile File;
	CString strFile="C:\\Digital RM 3.0\\Discos.cfg";
	char	Buffer[10];
	int		Cont;
	long int Tamanho;

	NDisco=0;
	memset(Buffer,0,10);
	
	if( !File.Open(strFile,CFile::modeRead|CFile::shareDenyNone) )
	{
		AfxMessageBox("O ficheiro\nC:\\Digital RM 3.0\\discos.cfg\nnão pode ser encontrado!");
		return FALSE;
	}

	Tamanho=(long)File.GetLength();
	strDiscos[0]="";
	for( Cont=0; Cont<Tamanho; Cont++ ) {
		File.Read(Buffer,1);
		if( Buffer[0]!=13 )
			strDiscos[NDisco]+=Buffer;
		else {
			strDiscos[NDisco].Delete(0,3);
			Cont++;
			File.Read(Buffer,1);
			NDisco++;
			strDiscos[NDisco]="";
		}
	}
	File.Close();

	return TRUE;
}

BOOL CConversaoDlg::LeDiscosV5()
{
	CFile File;
	CString strFile="C:\\Digital RM 3.0\\Discos_v5.cfg";
	char	Buffer[10];
	int		Cont;
	long int Tamanho;

	NDisco=0;
	memset(Buffer,0,10);
	if( !File.Open(strFile,CFile::modeRead|CFile::shareDenyNone) )
	{
		AfxMessageBox("O ficheiro\nC:\\Digital RM 3.0\\Discos_V5.cfg\nnão pode ser encontrado!");
		return FALSE;
	}

	Tamanho=(long)File.GetLength();
	strDiscosV5[0]="";
	for( Cont=0; Cont<Tamanho; Cont++ ) {
		File.Read(Buffer,1);
		if( Buffer[0]!=13 )
			strDiscosV5[NDisco]+=Buffer;
		else 
		{
			strDiscosV5[NDisco].Delete(0,3);
			Cont++;
			File.Read(Buffer,1);
			NDisco++;
			strDiscosV5[NDisco]="";
		}
	}
	File.Close();

	return TRUE;
}


BOOL CConversaoDlg::LeTipos()
{
	CFile File;
	CString strFile;
	char Buffer[5];
	int Cont;
	int Tamanho;

	NTipos=0;
	memset(Buffer,0,5);
	strFile.Format("%s\\Dados\\Musica\\Tipos.Cfg",strDiscos[0]);

	if( !File.Open(strFile,CFile::modeRead|CFile::shareDenyNone) )
	{
		AfxMessageBox("O ficheiro\n"+strFile+"\nnão pode ser encontrado.");
		return FALSE;
	}

	Tamanho=(long)File.GetLength();
	strTipos[0]="";
	for( Cont=0; Cont<Tamanho; Cont++ ){
		File.Read(Buffer,1);
		if( Buffer[0]!=13 )
			strTipos[NTipos]+=Buffer;
		else{
			Cont++;
			File.Read(Buffer,1);
			NTipos++;
			strTipos[NTipos]="";
		}
	}
	return TRUE;
}

void CConversaoDlg::ConverteJingles()
{
	TRegistoJingle		rJingles;
	TRegistoTipoJingles	rTipoJingles;
	MSG					Msg;

	CRSJingles			rsJingles(strMainConnect);
	CRSTypeOfJingle	rsTipos(strMainConnect);
	CRSPath			rsDiscos(strMainConnect);	

	CString		strFile;
	CString		strSQL;
	CString		strSrc,
				strDst;
	CFile		file;
	long int	nRead;
	BOOL		bConvertion;

	strFile.Format("%s\\dados\\Gestao de Antena\\Tipos de Jingles.dta",strDiscos[0]);
	file.Open(strFile,CFile::shareDenyNone|CFile::modeRead);
	nRead=sizeof(rTipoJingles);
	m_Titulo.SetWindowText("Tipos de Jingles");
	m_Progress2.SetRange32(0,(int)file.GetLength() );

	rsTipos.m_strFilter.Format("ID=1");
	rsTipos.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rTipoJingles,nRead);
		m_Texto.SetWindowText(rTipoJingles.Tipo);

		rsTipos.m_strFilter.Format("DRM35 = '%s'",rTipoJingles.Codigo);
		rsTipos.Requery();
		if( rsTipos.GetRecordCount()==0 )
			rsTipos.AddNew();
		else
			rsTipos.Edit();

		rsTipos.m_Name = CString(rTipoJingles.Tipo);
		rsTipos.m_Activ = !(rTipoJingles.Del);
		rsTipos.m_DRM35 = rTipoJingles.Codigo;
		rsTipos.Update();

		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();

	rsJingles.Open();
	rsDiscos.Open();

	strFile.Format("%s\\dados\\gestao de antena\\jingles.dta",strDiscos[0]);
	file.Open(strFile,CFile::shareDenyNone|CFile::modeRead);

	nRead=sizeof(rJingles);

	m_Titulo.SetWindowText("Jingles");
	m_Progress2.SetRange32(0,(int)file.GetLength() );

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rJingles,nRead);
		m_Texto.SetWindowText(rJingles.Nome);

		if( rJingles.Destruido )
			continue;

		rsTipos.m_strFilter.Format("DRM35 = '%s'",rJingles.Genero);
		rsTipos.Requery();
		if( rsTipos.GetRecordCount()!=0 ) 
		{
			rsDiscos.m_strFilter.Format("Path = '%s'",strDiscosV5[rJingles.Disco-1]);
			rsDiscos.Requery();

			rsJingles.m_strFilter.Format("DRM35 = '%s'",rJingles.Codigo);
			rsJingles.Requery();

			if( rsJingles.GetRecordCount()==0 )
			{
				rsJingles.AddNew();
			
				rsJingles.m_Activ=!rJingles.Del;
				rsJingles.m_Finish=rJingles.Fim;
				rsJingles.m_Start=rJingles.Inicio;
				rsJingles.m_PathID=rsDiscos.m_ID;
				rsJingles.m_Mix=rJingles.Mix;
				rsJingles.m_Name=rJingles.Nome;
				rsJingles.m_FileName=rJingles.Ficheiro;
				rsJingles.m_Rythm=rJingles.Ritmo*50;
				rsJingles.m_TypeID=rsTipos.m_ID;
				rsJingles.m_DRM35=rJingles.Codigo;
				rsJingles.m_Ready=0;

				rsJingles.Update();
				rsJingles.Requery();

				strSrc.Format("%s\\%s",strDiscos[rJingles.Disco-1],rJingles.Ficheiro);
				strDst.Format("%s\\%s",strDiscosV5[rJingles.Disco-1],rJingles.Ficheiro);

				if( (access(strSrc,0)==0) || (m_bAudioExists) )
				{
					if( m_bConvertAudio )
						bConvertion = ConertAudioFile(strSrc,strDst);
					else
						bConvertion = TRUE;

					if( bConvertion )
					{
						if( rJingles.Ready )
						{
							rsJingles.Edit();
							rsJingles.m_Ready=1;
						}	

						rsJingles.Update();

						if( m_bDeleteOriginal )
							DeleteFile(strSrc);
					}
				}
					
			}
			else
			{
				rsJingles.Edit();
			
				rsJingles.m_Activ=!rJingles.Del;
				rsJingles.m_Finish=rJingles.Fim;
				rsJingles.m_Start=rJingles.Inicio;
				rsJingles.m_PathID=rsDiscos.m_ID;
				rsJingles.m_Mix=rJingles.Mix;
				rsJingles.m_Name=rJingles.Nome;
				rsJingles.m_FileName=rJingles.Ficheiro;
				rsJingles.m_Rythm=rJingles.Ritmo*50;
				rsJingles.m_TypeID=rsTipos.m_ID;
				rsJingles.m_DRM35=rJingles.Codigo;
				rsJingles.m_Ready= (!rJingles.Del);

				rsJingles.Update();
				
			}
		}
		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}

	rsDiscos.Close();
	rsJingles.Close();
	rsTipos.Close();
}

// --------------------------------------------------------------------------
//	Rotina para converter a base de dados de Vendedores
/*
void CConversaoDlg::ConverteVendedores()
{
	TRegistoAngariador	rVendedor;
	MSG					Msg;

	CVendedoresRec	rsVendedores;

	CString		strFile;
	CFile		file;
	long int	nRead;

	strFile.Format("%s\\dados\\Gestao Comercial\\Angariadores.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead);
	nRead=sizeof(rVendedor);
	m_Titulo.SetWindowText("Vendedores");
	m_Progress2.SetRange32(0,file.GetLength() );

	rsVendedores.m_strFilter.Format("ID=1");
	rsVendedores.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rVendedor,nRead);
		m_Texto.SetWindowText(rVendedor.Nome);

		rsVendedores.m_strFilter.Format("DRM35 = '%s'",rVendedor.Codigo);
		rsVendedores.Requery();
		if( rsVendedores.GetRecordCount()==0 )
			rsVendedores.AddNew();
		else
			rsVendedores.Edit();

		rsVendedores.m_Activo=(!rVendedor.Del);
		rsVendedores.m_Comissao=atof(rVendedor.Comissao);
		rsVendedores.m_CP=rVendedor.CP;
		rsVendedores.m_Fax=rVendedor.Fax;
		rsVendedores.m_Morada=rVendedor.Morada;
		rsVendedores.m_NC=rVendedor.NC;
		rsVendedores.m_Nome=rVendedor.Nome;
		rsVendedores.m_OBS=rVendedor.OBS;
		rsVendedores.m_Telefone=rVendedor.Telefone;
		rsVendedores.m_DRM35=rVendedor.Codigo;

		rsVendedores.Update();

		m_Progress2.SetPos( file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();

}

// ------------------------------------------------------------------------------
//	Rotina para converter agencias

void CConversaoDlg::ConverteAgencias()
{
	TRegistoClientes	rAgencia;
	MSG					Msg;

	CAgenciasRec		rsAgencias;
	CVendedoresRec		rsVendedores;

	CString		strFile;
	CFile		file;
	long int	nRead;

	strFile.Format("%s\\dados\\Gestao Comercial\\Clientes.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead);
	nRead=sizeof(rAgencia);
	m_Titulo.SetWindowText("Agencias Publicitárias");
	m_Progress2.SetRange32(0,file.GetLength() );

	rsAgencias.m_strFilter.Format("ID=1");
	rsAgencias.Open();

	rsVendedores.m_strFilter.Format("ID=1");
	rsVendedores.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rAgencia,nRead);
		m_Texto.SetWindowText(rAgencia.Nome);

		if( rAgencia.bAgencia ) 
		{
			rsAgencias.m_strFilter.Format("DRM35 = '%s'",rAgencia.Codigo);
			rsAgencias.Requery();
			if( rsAgencias.GetRecordCount()==0 )
				rsAgencias.AddNew();
			else
				rsAgencias.Edit();	

			rsAgencias.m_Activo=(!rAgencia.Del);
			rsAgencias.m_Contacto=rAgencia.Contacto;
			rsAgencias.m_Contribuinte=rAgencia.Contribuinte;
			rsAgencias.m_CP=rAgencia.CP;
			rsAgencias.m_DRM35=rAgencia.Codigo;
			rsAgencias.m_Fax=rAgencia.Fax;
			rsAgencias.m_Morada=rAgencia.Morada;
			rsAgencias.m_Nome=rAgencia.Nome;
			rsAgencias.m_OBS=rAgencia.OBS;
			rsAgencias.m_Telefone=rAgencia.Telefone;
			
			rsVendedores.m_strFilter.Format("DRM35 = '%s'",rAgencia.Angariador);
			rsVendedores.Requery();
			if( rsVendedores.GetRecordCount() )
				rsAgencias.m_Vendedor=rsVendedores.m_ID;

			rsAgencias.Update();
		}

		m_Progress2.SetPos( file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();

}
*/
void CConversaoDlg::ConverteClientes()
{
	TRegistoClientes	rCliente;
	MSG					Msg;

	CRSCustomer		rsClientes("Broadcaster");


	CRSBusiness	rsActividades("Broadcaster");

	CString		strFile,
				strCliente;
	CFile		file;
	long int	nRead;

	strFile.Format("%s\\dados\\Gestao Comercial\\Clientes.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
	nRead=sizeof(rCliente);
	m_Titulo.SetWindowText("Clientes");
	m_Progress2.SetRange32(0,(int)file.GetLength() );

	rsClientes.m_strFilter.Format("ID=1");
	rsClientes.Open();

	rsActividades.m_strFilter.Format("ID=1");
	rsActividades.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rCliente,nRead);
		m_Texto.SetWindowText(rCliente.Nome);

		strCliente=rCliente.Nome;
		strCliente.Trim();
		if( strCliente.GetLength()!=0 )
		{
			rsClientes.m_strFilter.Format("Cli35 = '%s'",rCliente.Codigo);
			rsClientes.Requery();
			if( rsClientes.GetRecordCount()==0 )
				rsClientes.AddNew();
			else
				rsClientes.Edit();	

			rsClientes.m_Cli35=rCliente.Codigo;
			rsClientes.m_Activ=!rCliente.Del;
			rsClientes.m_Contact=rCliente.Contacto;
			rsClientes.m_nc=rCliente.Contribuinte;
			rsClientes.m_ZIP=rCliente.CP;

			rsClientes.m_Fax=rCliente.Fax;
			rsClientes.m_Adress=rCliente.Morada;
			rsClientes.m_Name=rCliente.Nome;
			rsClientes.m_Obs=rCliente.OBS;
			rsClientes.m_Phone=rCliente.Telefone;

			rsClientes.Update();
		}

		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();

}

void CConversaoDlg::ConverteActividades()
{
	TRegistoActividades	rActi;
	MSG					Msg;

	CRSBusiness	rsActividades("Broadcaster");

	CString		strFile;
	CFile		file;
	long int	nRead;

	strFile.Format("%s\\dados\\Gestao Comercial\\Actividades.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
	nRead=sizeof(rActi);
	m_Titulo.SetWindowText("Actividades Comerciais");
	m_Progress2.SetRange32(0,(int)file.GetLength() );

	rsActividades.m_strFilter.Format("ID=1");
	rsActividades.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rActi,nRead);
		m_Texto.SetWindowText(rActi.Actividade);


		rsActividades.m_strFilter.Format("Name = '%s'",rActi.Actividade);
		rsActividades.Requery();

		if( rsActividades.GetRecordCount() )
			rsActividades.Edit();
		else
			rsActividades.AddNew();
	
		rsActividades.m_Name=rActi.Actividade;
		rsActividades.m_Activ=!rActi.Del;

		rsActividades.Update();

		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();
}



void CConversaoDlg::ConverteSpots()
{
	TRegistoSpot	rSpot;
	CRSSpots		rsSpots("Broadcaster");


	CRSBusiness rsActividades("Broadcaster");
	CRSCustomer	rsClientes("Broadcaster");
	CRSPath		rsDiscos("Broadcaster");
	
	MSG			Msg;
	CString		strFile;
	CFile		file;
	long int	nRead;
	BOOL		bConvertion;
//	tm			*T;

	strFile.Format("%s\\dados\\Gestao Comercial\\Spots Publicitarios.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
	nRead=sizeof(rSpot);
	m_Titulo.SetWindowText("Spots Comerciais");
	m_Progress2.SetRange32(0,(int)file.GetLength() );

	rsSpots.m_strFilter.Format("ID=1");
	rsSpots.Open();


	rsActividades.Open();
	rsClientes.Open();
	rsDiscos.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rSpot,nRead);
		m_Texto.SetWindowText(rSpot.Nome);

		if( rSpot.Destruido )
			continue;

		rsSpots.m_strFilter.Format("DRM35 = '%s'",rSpot.Codigo);
		rsSpots.Requery();
		if( rsSpots.GetRecordCount()==0 )
		{
			rsSpots.AddNew();

			rsSpots.m_Activ=!rSpot.Destruido;
			rsSpots.m_FileName=rSpot.Ficheiro;
			rsSpots.m_Start=rSpot.Inicio;
			rsSpots.m_Mix=rSpot.Mix;
			rsSpots.m_Finish=rSpot.Fim;
			rsSpots.m_DRM35=rSpot.Codigo;
			rsSpots.m_Ready=0;
			rsSpots.m_Name=rSpot.Nome;
			rsSpots.m_TypeOfBusinessID = atol(rSpot.Tipo);

			rsClientes.m_strFilter.Format("Cli35 = '%s'",rSpot.Cliente);
			rsClientes.Requery();
			if( rsClientes.GetRecordCount() )
				rsSpots.m_CustomerID=rsClientes.m_ID;

			rsDiscos.m_strFilter.Format("ID = %d",rSpot.Disco);
			rsDiscos.Requery();
			if( rsDiscos.GetRecordCount() )
				rsSpots.m_PathID=rsDiscos.m_ID;
		
			rsSpots.Update();
			rsSpots.Requery();

			CString strSrc,
					strDst;

			strSrc.Format("%s\\%s",strDiscos[rSpot.Disco-1],rSpot.Ficheiro);
			strDst.Format("%s\\%s",strDiscosV5[rSpot.Disco-1],rSpot.Ficheiro);

			if( (access(strSrc,0)==0) || (!m_bAudioExists) )
			{
				if( m_bConvertAudio )
					bConvertion = ConertAudioFile(strSrc,strDst);
				else
					bConvertion = TRUE;

				if( bConvertion )
				{
					DeleteFile(strSrc);

					if( rSpot.Ready )
					{
						rsSpots.Edit();
						rsSpots.m_Ready=1;
						rsSpots.Update();
					}
				}
			}
		}
		else
		{
			rsSpots.Edit();

			rsSpots.m_Activ=!rSpot.Destruido;
			rsSpots.m_FileName=rSpot.Ficheiro;
			rsSpots.m_Start=rSpot.Inicio;
			rsSpots.m_Mix=rSpot.Mix;
			rsSpots.m_Finish=rSpot.Fim;
			rsSpots.m_DRM35=rSpot.Codigo;
			rsSpots.m_Ready=0;
			rsSpots.m_Name=rSpot.Nome;
			rsSpots.m_TypeOfBusinessID = atol(rSpot.Tipo);
			rsSpots.m_Ready = (!rSpot.Del);

			rsClientes.m_strFilter.Format("Cli35 = '%s'",rSpot.Cliente);
			rsClientes.Requery();
			if( rsClientes.GetRecordCount() )
				rsSpots.m_CustomerID=rsClientes.m_ID;

			rsDiscos.m_strFilter.Format("ID = %d",rSpot.Disco);
			rsDiscos.Requery();
			if( rsDiscos.GetRecordCount() )
				rsSpots.m_PathID=rsDiscos.m_ID;
		
			rsSpots.Update();
		}

		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();
}

/*
void CConversaoDlg::ConverteBlocos()
{
	TRegBloco			rBloco;
	CBlocosDefRec		rsBlocosDef;
	CBlocoContentsRec rsBlocosCont;
	CJinglesRec			rsJingles;
	TIMESTAMP_STRUCT	tsInicio={1900,1,1,0,0,0,0};
	TIMESTAMP_STRUCT	tsFim={2500,1,1,0,0,0,0};

	MSG			Msg;
	CString		strFile;
	CFile		file;
	long int	nRead;
	long int	Cont;

	strFile.Format("%s\\dados\\Gestao de Antena\\Parametros dos Blocos.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead);
	nRead=sizeof(rBloco);
	m_Titulo.SetWindowText("Blocos Comerciais");
	m_Progress2.SetRange32(0,file.GetLength() );

	rsBlocosDef.m_strFilter.Format("BlocoID = 0");
	rsBlocosDef.Open();
	
	rsBlocosCont.m_strFilter.Format("BlocoID = 0");
	rsBlocosCont.Open();

	rsJingles.Open();

	while( file.GetPosition()<file.GetLength() )
	{
		file.Read(&rBloco,nRead);
		m_Texto.SetWindowText(rBloco.Descricao);

		rsBlocosDef.m_strFilter.Format("Bloco35 = '%s'",rBloco.Codigo);
		rsBlocosDef.Requery();
		if( rsBlocosDef.GetRecordCount()==0 )
			rsBlocosDef.AddNew();
		else
			rsBlocosDef.Edit();	

		rsBlocosDef.m_Bloco35=rBloco.Codigo;
		rsBlocosDef.m_BlocoActivo=!rBloco.Del;
		rsBlocosDef.m_BlocoDom=rBloco.Dom;
		if( rBloco.Precisao!=2 )
			rsBlocosDef.m_BlocoHora=rBloco.Hora;
		else if (rBloco.Hora!=0)
			rsBlocosDef.m_BlocoHora=rBloco.Hora-1;
		else
			rsBlocosDef.m_BlocoHora=86399999;
		rsBlocosDef.m_BlocoNome=rBloco.Descricao;
		rsBlocosDef.m_BlocoPatrocinio=0;
		rsBlocosDef.m_BlocoPrecisao=rBloco.Precisao;
		rsBlocosDef.m_BlocoQua=rBloco.Qua;
		rsBlocosDef.m_BlocoQui=rBloco.Qui;
		rsBlocosDef.m_BlocoSab=rBloco.Sab;
		rsBlocosDef.m_BlocoSeg=rBloco.Seg;
		rsBlocosDef.m_BlocoSex=rBloco.Sex;
		rsBlocosDef.m_BlocoTer=rBloco.Ter;
		rsBlocosDef.Update();
		rsBlocosDef.Requery();

		rsBlocosCont.m_strFilter.Format("BlocoID = %d",rsBlocosDef.m_BlocoID);
		rsBlocosCont.Requery();
		if( rsBlocosCont.GetRecordCount() )
		{
			rsBlocosCont.MoveFirst();
			
			rsBlocosCont.Edit();
		}
		else
			rsBlocosCont.AddNew();

		Cont=0;
		while( rBloco.Elementos[Cont].Codigo[0] )
		{
			
			switch (rBloco.Elementos[Cont].Tipo)
			{
			case TP_JINGLE:
				rsJingles.m_strFilter.Format("Jingle35 = '%s'",rBloco.Elementos[Cont].Codigo);
				rsJingles.Requery();
				if( rsJingles.GetRecordCount() )
				{
					rsBlocosCont.m_BlocoElemento=rsJingles.m_JinglesID;
					rsBlocosCont.m_BlocoID=rsBlocosDef.m_BlocoID;
					rsBlocosCont.m_BlocoPos=Cont+1;
					rsBlocosCont.m_BlocoTipo=TP_JINGLE;
					rsBlocosCont.m_BlocoInicio=tsInicio;
					rsBlocosCont.m_BlocoFim=tsFim;
					
					rsBlocosCont.Update();

					try 
					{
						rsBlocosCont.MoveNext();
						rsBlocosCont.Edit();
					}
					catch (CDBException *) {
						rsBlocosCont.AddNew();
					}
						
				}
				break;
			case TP_SPOT:
				rsBlocosCont.m_BlocoElemento=0;
				rsBlocosCont.m_BlocoID=rsBlocosDef.m_BlocoID;
				rsBlocosCont.m_BlocoPos=Cont+1;
				rsBlocosCont.m_BlocoInicio=tsInicio;
				rsBlocosCont.m_BlocoFim=tsFim;
				switch( rBloco.Elementos[Cont].Codigo[0] )
				{
				case 1:
				case 2:
				case 4:
				case 5:
					rsBlocosCont.m_BlocoTipo=TYPE_SPOT;
					break;
				case 3:
					rsBlocosCont.m_BlocoTipo=TYPE_BLOCOSPOT;
					break;
				}
				rsBlocosCont.Update();

				try {
					rsBlocosCont.MoveNext();
					rsBlocosCont.Edit();
				}
				catch( CDBException * ) {
					rsBlocosCont.AddNew();
				}
				

				break;
			}
			Cont++;
		}

		for( int I=Cont; Cont<rsBlocosCont.GetRecordCount(); Cont++ )
			rsBlocosCont.Delete();

		m_Progress2.SetPos( file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();
}

void CConversaoDlg::ConverteCalendarios()
{
	CCalendarioDef		CalendarioDef(strMainConnect);
	CCalendarioSpots	CalendarioSpots(strMainConnect);
	CCalendarioBlocos	CalendarioBlocos(strAntenaConnect);
	CBlocosDefRec		Blocos;
	CSpotsRec			Spots;
	CAgendaComercial	Agenda;
	CClientesRec		Clientes(strMainConnect);

	TRegCalendar		RegCalendar;
	TRegCalendarLinha	RegCalendarLinhas;

	CFile fileDef;
	CFile fileLinhas;
	CString strFileDef;
	CString strFileLinhas;

	CString strCliente,
			strDelete,
			strTexto;
	int		nRead;
	CTime	T,
			tInicio,
			tFinal,
			tData;
	MSG		Msg;
	BOOL	bTeste;
	TIMESTAMP_STRUCT tsInicio;
	TIMESTAMP_STRUCT tsFinal;

	CalendarioDef.Open();
	CalendarioSpots.Open();
	CalendarioBlocos.Open();
	Blocos.Open();
	Spots.Open();
	Agenda.Open();
	Clientes.Open();

	strFileDef.Format("%s\\Dados\\Gestao Comercial\\Calendarizaçao de Spots.dta",strDiscos[0]);
	strFileLinhas.Format("%s\\Dados\\Gestao Comercial\\Calendarizaçao de Spots - Linhas.Dta",strDiscos[0]);
	fileDef.Open(strFileDef,CFile::modeRead);
	fileLinhas.Open(strFileLinhas,CFile::modeRead);
	m_Titulo.SetWindowText("Calendarios de Emissão");
	m_Progress2.SetRange32(0,fileDef.GetLength() );

	nRead=sizeof(TRegCalendar);
	while( fileDef.GetPosition()<fileDef.GetLength() )
	{
		fileDef.Read(&RegCalendar,nRead);
		
		strCliente=RegCalendar.Codigo;
		strCliente.Delete(13,3);
		Spots.m_strFilter.Format("Spot35 = '%s'",strCliente);
		Spots.Requery();

		if( Spots.GetRecordCount() )
		{
			strCliente.Delete(10,4);
			Clientes.m_strFilter.Format("Cli35 = '%s'",strCliente);
			Clientes.Requery();
			if( Clientes.GetRecordCount() )
			{
				Clientes.m_CliNome.TrimRight();
				Spots.m_SpotNome.TrimRight();
				strTexto=Clientes.m_CliNome+" - "+Spots.m_SpotNome;
				m_Texto.SetWindowText(strTexto);
				CalendarioDef.m_strFilter.Format("DRM35 = '%s'",RegCalendar.Codigo);
				CalendarioDef.Requery();

				Spots.m_strFilter.Format("DRM35 = '%s'",RegCalendar.Codigo);
				if( CalendarioDef.GetRecordCount() )
					CalendarioDef.Edit();
				else
					CalendarioDef.AddNew();

				T=RegCalendar.DataFinal;
				tsFinal.year=T.GetYear();
				tsFinal.month=T.GetMonth();
				tsFinal.day=T.GetDay();
				tsFinal.hour=T.GetHour();
				tsFinal.minute=T.GetMinute();
				tsFinal.second=T.GetSecond();
				tsFinal.fraction=0;

				T=RegCalendar.DataInicio;
				tsInicio.year=T.GetYear();
				tsInicio.month=T.GetMonth();
				tsInicio.day=T.GetDay();
				tsInicio.hour=T.GetHour();
				tsInicio.minute=T.GetMinute();
				tsInicio.second=T.GetSecond();
				tsInicio.fraction=0;

				CalendarioDef.m_Cliente=Clientes.m_CliID;
				CalendarioDef.m_DRM35=RegCalendar.Codigo;
				CalendarioDef.m_NEmissoes=RegCalendar.NEmissoes;
				CalendarioDef.m_Radio=1;
				CalendarioDef.m_DataFinal=tsFinal;
				CalendarioDef.m_DataInicio=tsInicio;
				CalendarioDef.m_Suspenso=0;
				CalendarioDef.m_TipoFim=RegCalendar.bEmissoes;
				CalendarioDef.m_Valor=RegCalendar.ValorTotal;
				CalendarioDef.Update();
				CalendarioDef.Requery();

				strDelete.Format("DELETE FROM CalendarioSpots WHERE CaleID = %d",CalendarioDef.m_ID);
				CalendarioDef.m_pDatabase->ExecuteSQL( strDelete );
				CalendarioSpots.AddNew();
				CalendarioSpots.m_CaleID=CalendarioDef.m_ID;
				CalendarioSpots.m_CaleOrdem=1;
				CalendarioSpots.m_CaleSpot=Spots.m_SpotID;
				CalendarioSpots.Update();

				strDelete.Format("DELETE FROM AgendaComercial WHERE PubCalendario = %d",CalendarioDef.m_ID);
				Agenda.m_pDatabase->ExecuteSQL( strDelete );
			}
		}

		m_Progress2.SetPos( fileDef.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}

	nRead=sizeof(RegCalendarLinhas);
	while( fileLinhas.GetPosition()<fileLinhas.GetLength() )
	{
		m_Progress2.SetPos( fileLinhas.GetPosition() );

		fileLinhas.Read(&RegCalendarLinhas,nRead);

		strCliente=RegCalendarLinhas.Codigo;
		strCliente.Delete(17,3);

		CalendarioDef.m_strFilter.Format("DRM35 = '%s'",strCliente);
		CalendarioDef.Requery();
		if( CalendarioDef.GetRecordCount() )
		{
			Blocos.m_strFilter.Format("Bloco35 = '%s'",RegCalendarLinhas.Bloco);
			Blocos.Requery();
			if( Blocos.GetRecordCount() )
			{
				strDelete.Format("DELETE FROM CalendarioBlocos WHERE BlocoID = %d AND CaleID = %d",Blocos.m_BlocoID,CalendarioDef.m_ID);
				CalendarioBlocos.m_pDatabase->ExecuteSQL(strDelete);

				if( !RegCalendarLinhas.Del )
				{
					CalendarioBlocos.AddNew();
					CalendarioBlocos.m_BlocoID=Blocos.m_BlocoID;
					CalendarioBlocos.m_CaleID=CalendarioDef.m_ID;
					CalendarioBlocos.m_Dom=RegCalendarLinhas.Dom;
					CalendarioBlocos.m_Seg=RegCalendarLinhas.Seg;
					CalendarioBlocos.m_Ter=RegCalendarLinhas.Ter;
					CalendarioBlocos.m_Qua=RegCalendarLinhas.Qua;
					CalendarioBlocos.m_Qui=RegCalendarLinhas.Qui;
					CalendarioBlocos.m_Sex=RegCalendarLinhas.Sex;
					CalendarioBlocos.m_Sab=RegCalendarLinhas.Sab;
					CalendarioBlocos.m_Estacao=1;
					CalendarioBlocos.m_Pos=RegCalendarLinhas.Posicao-2;
					CalendarioBlocos.m_Valor=RegCalendarLinhas.Valor;
					CalendarioBlocos.Update();
					
					CalendarioSpots.m_strFilter.Format("CaleID = %d",CalendarioDef.m_ID);
					CalendarioSpots.Requery();

					tInicio=CTime(CalendarioDef.m_DataInicio.year,
						CalendarioDef.m_DataInicio.month,
						CalendarioDef.m_DataInicio.day,
						CalendarioDef.m_DataInicio.hour,
						CalendarioDef.m_DataInicio.minute,
						CalendarioDef.m_DataInicio.second);
					tFinal=CTime(CalendarioDef.m_DataFinal.year,
						CalendarioDef.m_DataFinal.month,
						CalendarioDef.m_DataFinal.day,
						CalendarioDef.m_DataFinal.hour,
						CalendarioDef.m_DataFinal.minute,
						CalendarioDef.m_DataFinal.second);

					tData=tInicio;
					while( tData<=tFinal )
					{
						switch( tData.GetDayOfWeek() ) {
						case 1:
							bTeste=RegCalendarLinhas.Dom;
							break;
						case 2:
							bTeste=RegCalendarLinhas.Seg;
							break;
						case 3:
							bTeste=RegCalendarLinhas.Ter;
							break;
						case 4:
							bTeste=RegCalendarLinhas.Qua;
							break;
						case 5:
							bTeste=RegCalendarLinhas.Qui;
							break;
						case 6:
							bTeste=RegCalendarLinhas.Sex;
							break;
						case 7:
							bTeste=RegCalendarLinhas.Sab;
							break;
						}

						if( bTeste )
						{
							Agenda.AddNew();
							Agenda.m_BlocoData.year=tData.GetYear();
							Agenda.m_BlocoData.month=tData.GetMonth();
							Agenda.m_BlocoData.day=tData.GetDay();
							Agenda.m_BlocoData.hour=0;
							Agenda.m_BlocoData.minute=0;
							Agenda.m_BlocoData.second=0;
							Agenda.m_BlocoData.fraction=0;
							Agenda.m_BlocoID=Blocos.m_BlocoID;
							Agenda.m_Posicao=RegCalendarLinhas.Posicao-3;
							Agenda.m_PubCalendario=CalendarioDef.m_ID;
							Agenda.m_PubID=CalendarioSpots.m_CaleSpot;
							Agenda.m_PubValor=RegCalendarLinhas.Valor;
							Agenda.Update();
						}

						tData+=CTimeSpan(1,0,0,0);
					}
				}
			}
		}
		
		m_Progress2.SetPos( fileLinhas.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}

	fileDef.Close();
	fileLinhas.Close();
	CalendarioDef.Close();
	CalendarioSpots.Close();
	CalendarioBlocos.Close();
	Blocos.Close();
	Spots.Close();
	Agenda.Close();
	Clientes.Close();
}
*/
void CConversaoDlg::ConverteListas()
{
	CRSPlayListsDefinition		ListasDef("Broadcaster-OnAir");

	CFile	file;
	CString	strFile,
			strSQL;
	int		nRead;
	MSG		Msg;
	TRegLista	RegLista;

	ListasDef.m_strFilter.Format("ID = 0");
	ListasDef.Open();

	strFile.Format("%s\\Dados\\Gestao de Antena\\Listas de Musicas.Dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);

	m_Titulo.SetWindowText("Listas de Musica");
	m_Progress2.SetRange32(0,(int)file.GetLength() );
	m_Progress1.SetRange32(0,1000);

	nRead=sizeof(TRegLista);
	while( file.GetPosition()<file.GetLength() )
	{
		m_Progress2.SetPos((int)file.GetPosition());
		file.Read(&RegLista,nRead);
		m_Texto.SetWindowText(RegLista.Nome);
		
		ListasDef.m_strFilter.Format("Name = '%s'",RegLista.Nome);
		ListasDef.Requery();
		if( ListasDef.GetRecordCount() )
			ListasDef.Edit();
		else
			ListasDef.AddNew();

		ListasDef.m_DRM35=RegLista.Codigo;
		ListasDef.m_Activ=ListasDef.m_OnAir=!RegLista.Del;
		ListasDef.m_Name=RegLista.Nome;
		ListasDef.Update();

		ListasDef.Requery();
		strSQL.Format("Delete From [PlayLists-Contents] where ListID = '%d'",ListasDef.m_ID);
		ListasDef.m_pDatabase->ExecuteSQL(strSQL);
		
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	ListasDef.Close();
}

void CConversaoDlg::ConverteDiscos()
{
	CRSPath	rsDiscos("Broadcaster");
	LONG		Cont=0;
	MSG			Msg;
	
	rsDiscos.Open();
	m_Titulo.SetWindowText("Conversão Discos CFG");
	m_Progress2.SetRange(0,NDisco);
	m_Progress1.SetRange(0,NDisco);

	while( strDiscos[Cont].GetLength() ) 
	{
		m_Texto.SetWindowText(strDiscos[Cont]);

		rsDiscos.m_strFilter.Format("Path = '%s'",strDiscosV5[Cont]);
		rsDiscos.Requery();

		if( !rsDiscos.GetRecordCount() )
		{
			rsDiscos.AddNew();
			rsDiscos.m_Path=strDiscosV5[Cont];
			rsDiscos.Update();
		}
		
		Cont++;
		m_Progress1.SetPos(Cont);
		m_Progress2.SetPos(Cont);

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
}

void CConversaoDlg::ConverteGeneros()
{
	CRSCategories	rsGeneros("Broadcaster");
	LONG		Cont=0;
	MSG			Msg;

	rsGeneros.Open( );
	m_Progress1.SetRange(0,NTipos);
	m_Progress2.SetRange(0,NTipos);

	while( Cont<NTipos ) 
	{
		rsGeneros.m_strFilter.Format( "Name = '%s'",strTipos[Cont] );
		rsGeneros.Requery();

		if( !rsGeneros.GetRecordCount() )
		{
			rsGeneros.AddNew();
	
			rsGeneros.m_Name=strTipos[Cont];
			rsGeneros.m_Activ=1;

			rsGeneros.Update();
		}

		Cont++;

		m_Progress1.SetPos(Cont);
		m_Progress2.SetPos(Cont);
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
}

void CConversaoDlg::ConverteNacionalidades()
{
	CString				strFile;
	CFile				file;
	CRSExpressions		rsLinguas("Broadcaster");
	CRSNationalities	rsNacionalidades("Broadcaster");
	int					nRead;
	MSG					Msg;
	TRegistoNacionalidade rNacionalidade;

	strFile.Format("%s\\Dados\\Musica\\Nacionalidades.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
	nRead=sizeof(rNacionalidade);

	rsNacionalidades.Open( );
	rsLinguas.Open();

	m_Progress2.SetRange32(0,(int)file.GetLength() );
	m_Titulo.SetWindowText("Nacionalidades");

	while( nRead==sizeof(rNacionalidade) )
	{
		nRead=file.Read(&rNacionalidade,sizeof(rNacionalidade));
		m_Texto.SetWindowText(rNacionalidade.Nacionalidade);

		if( nRead==sizeof(rNacionalidade) ) 
		{

			rsNacionalidades.m_strFilter.Format("Nationality = '%s'",rNacionalidade.Nacionalidade);
			rsNacionalidades.Requery();
			if( !rsNacionalidades.GetRecordCount() )
				rsNacionalidades.AddNew();
			else
				rsNacionalidades.Edit();

			rsNacionalidades.m_Nationality=rNacionalidade.Nacionalidade;
			rsNacionalidades.m_Activ=(!rNacionalidade.Del);
			rsNacionalidades.m_ZoneID=0;
			rsNacionalidades.Update();

			rsLinguas.m_strFilter.Format("Name = '%s'",rNacionalidade.Nacionalidade);
			rsLinguas.Requery();
			if( !rsLinguas.GetRecordCount() )
				rsLinguas.AddNew();
			else
				rsLinguas.Edit();

			rsLinguas.m_Name=rNacionalidade.Nacionalidade;
			rsLinguas.m_Activ=(!rNacionalidade.Del);
			rsLinguas.m_DRM35=rNacionalidade.Codigo;
			rsLinguas.Update();
		}
		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();
}

void CConversaoDlg::ConverteEditoras()
{
	CRSRecordLabel	rsEditoras("Broadcaster");
	CString			strFile;
	CFile			file;
	MSG				Msg;
	int				nRead;
	TRegistoEditora rEditora;

	strFile.Format("%s\\dados\\Musica\\Editoras.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
	nRead=sizeof(rEditora);
	m_Progress2.SetRange32(0,(int)file.GetLength() );
	m_Titulo.SetWindowText( "Editoras" );

	rsEditoras.Open( );
	while( nRead==sizeof(TRegistoEditora) )
	{
		nRead=file.Read(&rEditora,sizeof(rEditora));
		m_Texto.SetWindowText(rEditora.Nome);

		if( nRead==sizeof(rEditora) )
		{
			if( strlen(rEditora.Codigo)<4 ) 
			{
				CString strTemp=rEditora.Nome;
				strTemp.Replace("'","''");
				rsEditoras.m_strFilter.Format("Name = '%s'",strTemp);
				rsEditoras.Requery();
				if( !(rsEditoras.GetRecordCount()) ) 
					rsEditoras.AddNew();
				else
					rsEditoras.Edit();

				rsEditoras.m_Name=rEditora.Nome;
				if( !rEditora.Del )
					rsEditoras.m_Activ=1;

				rsEditoras.Update();
			}
		}
		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 
	}
	file.Close();

	rsEditoras.Close();
}

void CConversaoDlg::ConverteInterpretes()
{
	CRSArtists	rsInterpretes("Broadcaster",NULL);
	CRSNationalities rsNacionalidades("Broadcaster");
	CRSRecordLabel	rsEditoras("Broadcaster");
	TRegistoAutor	rInterprete;
	CString			strFile;
	CString			strTemp;
	int				nRead,
					Ano,
					Mes,
					Dia;
	CFile			file;
	MSG				Msg;

	strFile.Format("%s\\dados\\musica\\autores.dta",strDiscos[0]);
	file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
	nRead=sizeof(rInterprete);

	m_Progress2.SetRange32(0,(int)file.GetLength() );
	m_Titulo.SetWindowText("Interpretes");

	rsInterpretes.m_strFilter.Format("ID = 0");
	rsInterpretes.Open();

	rsNacionalidades.m_strFilter="ID = 0";
	rsNacionalidades.Open();
	
	rsEditoras.m_strFilter="ID = 0";
	rsEditoras.Open();

	while( nRead==sizeof(TRegistoAutor) )
	{
		nRead=file.Read(&rInterprete,sizeof(TRegistoAutor));
		if( nRead==sizeof(rInterprete) )
		{
			m_Texto.SetWindowText(rInterprete.Nome);
			strTemp=rInterprete.Nome;
			strTemp.Replace("'","''");

			rsInterpretes.m_strFilter.Format("Name = '%s'",strTemp);
			rsInterpretes.Requery();
			if( !rsInterpretes.GetRecordCount() )
				rsInterpretes.AddNew();
			else
				rsInterpretes.Edit();

			rsInterpretes.m_Name=rInterprete.Nome;
			rsInterpretes.m_Adress=rInterprete.Morada;
			rsInterpretes.m_Activ=(!rInterprete.Del);
			rsInterpretes.m_Obs=rInterprete.Obs;
			rsInterpretes.m_DRM35=rInterprete.Codigo;
			rsInterpretes.m_FanClub=rInterprete.Clube;
				
			Ano=atoi(rInterprete.DataNascimento);
			Mes=atoi(rInterprete.DataNascimento+5);
			Dia=atoi(rInterprete.DataNascimento+8);
			if((Ano>2500) || (Ano<1900)) Ano=1900;
			if((Mes<1) || (Mes>12)) Mes=1;
			if((Dia<1) || (Dia>31)) Dia=1;

			rsInterpretes.m_Birthdate.year=Ano;
			rsInterpretes.m_Birthdate.month=Mes;
			rsInterpretes.m_Birthdate.day=Dia;
			rsInterpretes.m_Birthdate.fraction=0;
			rsInterpretes.m_Birthdate.hour=0;
			rsInterpretes.m_Birthdate.minute=0;
			rsInterpretes.m_Birthdate.second=0;
				
			rsInterpretes.Update();
		}
		m_Progress2.SetPos( (int)file.GetPosition() );
		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		} 

	}
	file.Close();
}

void CConversaoDlg::ConverteFaixas()
{
	CRSMusicTracks		rsFaixas("Broadcaster");
	CRSArtists rsInterpretes("Broadcaster",NULL);
	CRSCategories		rsGeneros("Broadcaster");
	CRSExpressions		rsLinguas("Broadcaster");
	CString			strFile,
					strSQL;
	CDatabase		db;
	CRSPath			rsDiscos("Broadcaster");

	CRSPlayListsDefinition		rsListas("Broadcaster-OnAir");
	CFile			file;
	int				nRead;
	MSG				Msg;
	TRegistoMusica	rFaixa;
	BOOL			bConvertion,
					bRecordExists;

	rsListas.Open();
	db.Open("Broadcaster-OnAir");

	rsFaixas.m_strFilter.Format("ID = 0");
	rsFaixas.Open();

	rsInterpretes.m_strFilter="ID = 0";
	rsInterpretes.Open();

	rsGeneros.m_strFilter="ID = 0";
	rsGeneros.Open();

	rsDiscos.m_strFilter="ID = 0";
	rsDiscos.Open();



	rsLinguas.m_strFilter="ID = 0";
	rsLinguas.Open();

	for( int i=0; i<NTipos; i++ ) 
	{
		nRead=sizeof(TRegistoMusica);
		rsGeneros.m_strFilter.Format("Name = '%s'",strTipos[i]);
		rsGeneros.Requery();

		if( rsGeneros.GetRecordCount() ) 
		{
			strFile.Format("%s\\dados\\musica\\%s.dta",strDiscos[0],strTipos[i]);
			file.Open(strFile,CFile::modeRead|CFile::shareDenyNone);
			m_Progress2.SetRange32(0,(long)file.GetLength() );
			m_Titulo.SetWindowText(strTipos[i] );

			while( nRead==sizeof(TRegistoMusica) ) 
			{
				nRead=file.Read(&rFaixa,sizeof(rFaixa) );
				if( nRead==sizeof(rFaixa) )
				{
					
					m_Texto.SetWindowText(rFaixa.Titulo);
					m_Progress1.SetWindowText(rFaixa.Titulo);
					rsFaixas.m_strFilter.Format("Storage = '%s' AND CategoryID = '%d'",rFaixa.Codigo,rsGeneros.m_ID );
					rsFaixas.Requery();
					if( rsFaixas.GetRecordCount()==0 )
					{
						rsFaixas.AddNew();
						bRecordExists=FALSE;
					}
					else
					{
						rsFaixas.Edit();
						bRecordExists=TRUE;
					}
					
						rsInterpretes.m_strFilter.Format("DRM35 = '%s'",rFaixa.Autor);
						rsInterpretes.Requery();
						if( rsInterpretes.GetRecordCount() )
						{
							//	rFaixa.Local=13;
							rsDiscos.m_strFilter.Format("Path = '%s'",strDiscosV5[rFaixa.Local-1]);
							rsDiscos.Requery();
							if( rsDiscos.GetRecordCount() )
							{
								CString strTemp;
								rsDiscos.m_Path.TrimRight();
								rsInterpretes.m_Name.TrimRight();
								strTemp=strDiscos[rFaixa.Local-1]+"\\"+rsInterpretes.m_Name+" - "+rFaixa.Titulo+".wav";
								if( (access(strTemp,0)==0) || (m_bAudioExists==FALSE) || (bRecordExists) )
								{
									CString strNewFile = strDiscosV5[rFaixa.Local-1]+"\\"+rsInterpretes.m_Name+" - "+rFaixa.Titulo+".wav";

									rsLinguas.m_strFilter.Format( "DRM35 = '%s'",rFaixa.Nacionalidade);
									rsLinguas.Requery();
									if( rsLinguas.GetRecordCount() )
										rsFaixas.m_LanguageID=rsLinguas.m_ID;
									else
										rsFaixas.SetFieldNull(&rsFaixas.m_LanguageID);
			
									rsFaixas.m_ArtistID=rsInterpretes.m_ID;
									rsFaixas.m_Title=rFaixa.Titulo;
									rsFaixas.m_CategoryID=rsGeneros.m_ID;
									rsFaixas.m_Obs=rFaixa.OBS;
									rsFaixas.m_Start=rFaixa.Inicio;
									rsFaixas.m_FadeIn=rFaixa.FadeIn;
									rsFaixas.m_Intro=rFaixa.Intro;
									rsFaixas.m_FadeOut=rFaixa.FadeOut;
									rsFaixas.m_Mix=rFaixa.Ponte;
									rsFaixas.m_Finish=rFaixa.Fim;
									rsFaixas.m_Available=0;
									rsFaixas.m_Activ=0;
									rsFaixas.m_PathID=rsDiscos.m_ID;
									rsFaixas.m_Storage=rFaixa.Codigo;
						
									//rsFaixas.m_FaixaData=1;
									rsFaixas.m_Rythm=rFaixa.Ritmo*50;
									rsFaixas.m_FileType = ".wav";
									rsFaixas.Update();
							
									rsFaixas.Requery();
									
									if( !rFaixa.Del )
									{
										if( (m_bConvertAudio) && (!bRecordExists) )
											bConvertion = ConertAudioFile(strTemp,strNewFile);
										else
											bConvertion = TRUE;

										if( bConvertion )
										{
											if( (m_Listas) && (!rFaixa.Del) )
											{
												rsListas.m_strFilter.Format("DRM35 = '%s'",rFaixa.Lista1);
												rsListas.Requery();
												if( rsListas.GetRecordCount() )
												{
													strSQL.Format("INSERT INTO [PlayLists-Contents] (ListID,MusicTrackID) VALUES (%d,%d)",rsListas.m_ID,rsFaixas.m_ID);
													db.ExecuteSQL(strSQL);
												}
									
												rsListas.m_strFilter.Format("DRM35 = '%s'",rFaixa.Lista2);
												rsListas.Requery();
												if( rsListas.GetRecordCount() )
												{
													strSQL.Format("INSERT INTO [PlayLists-Contents] (ListID,MusicTrackID) VALUES (%d,%d)",rsListas.m_ID,rsFaixas.m_ID);
													db.ExecuteSQL(strSQL);
												}
		
												rsListas.m_strFilter.Format("DRM35 = '%s'",rFaixa.Special1);
												rsListas.Requery();
												if( rsListas.GetRecordCount() )
												{
													strSQL.Format("INSERT INTO [PlayLists-Contents] (ListID,MusicTrackID) VALUES (%d,%d)",rsListas.m_ID,rsFaixas.m_ID);
													db.ExecuteSQL(strSQL);
												}
	
												rsListas.m_strFilter.Format("DRM35 = '%s'",rFaixa.Special2);
												rsListas.Requery();
												if( rsListas.GetRecordCount() )
												{
													strSQL.Format("INSERT INTO [PlayLists-Contents] (ListID,MusicTrackID) VALUES (%d,%d)",rsListas.m_ID,rsFaixas.m_ID);
													db.ExecuteSQL(strSQL);
												} 
											}

											if( !rFaixa.Del )
											{
												strSQL.Format("UPDATE MusicTracks SET Activ='1', Available='1' WHERE Storage='%s'",rFaixa.Codigo);
												rsFaixas.m_pDatabase->ExecuteSQL(strSQL);
											}
			
											if( m_bDeleteOriginal )
												DeleteFile(strTemp);
										}
									}
								}
							}
							else
								rsFaixas.CancelUpdate();
						}
						else
							rsFaixas.CancelUpdate();
					

					m_Progress2.SetPos( (int)file.GetPosition() );
					while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
					{
						TranslateMessage(&Msg);
						DispatchMessage(&Msg);
					} 
				}
			}
			file.Close();
		}
	}
}

BOOL CConversaoDlg::ConertAudioFile(CString strSource, CString strDestination)
{
	CWaveFile		fileSrc,
					fileDst;
	CFile			fileTmp;
	BOOL			bPCM = FALSE;
	CString			strTempFile="C:\\Temp\\tempfile.tmp";
	HANDLE			hBufferSRC;
	HANDLE			hBufferDST;
	BYTE			*lpBufferSRC;
	short			*lpBufferDST;
	MMRESULT		mmr;
	MSG				Msg;
	WAVEFORMATEX	wfPCM;
	MPEG1WAVEFORMAT	wfMPEG;

	fileSrc.Open(strSource.GetBuffer(0),NULL,WAVEFILE_READ);
	if( fileSrc.m_pwfx->wFormatTag==WAVE_FORMAT_PCM )
	{
		bPCM=TRUE;
		wfPCM.cbSize		= 0;
		wfPCM.wFormatTag	= WAVE_FORMAT_PCM;
		wfPCM.nChannels		= fileSrc.m_pwfx->nChannels;
		wfPCM.nSamplesPerSec= fileSrc.m_pwfx->nSamplesPerSec;
		wfPCM.nAvgBytesPerSec=fileSrc.m_pwfx->nAvgBytesPerSec;
		wfPCM.wBitsPerSample= fileSrc.m_pwfx->wBitsPerSample;
		wfPCM.nBlockAlign	= fileSrc.m_pwfx->nBlockAlign;
	} 
	else
	{
		HACMSTREAM		hasPCM;
		ACMSTREAMHEADER ashPCM;
		LPMPEG1WAVEFORMAT tempFmt;

		if( (fileSrc.m_pwfx->wFormatTag==WAVE_FORMAT_MPEG) )
		{
			tempFmt=(LPMPEG1WAVEFORMAT)fileSrc.m_pwfx;
			tempFmt->wfx.cbSize=sizeof(MPEG1WAVEFORMAT)-sizeof(WAVEFORMATEX);
			tempFmt->dwPTSHigh	= 0;
			tempFmt->dwPTSLow	= 0;
		}

		m_Progress1.SetRange32(0,fileSrc.GetSize());

		fileTmp.Open(strTempFile,CFile::modeCreate|CFile::modeReadWrite,NULL);

		wfPCM.cbSize		= 0;
		wfPCM.wFormatTag	= WAVE_FORMAT_PCM;
		wfPCM.nChannels		= fileSrc.m_pwfx->nChannels;
		wfPCM.nSamplesPerSec= fileSrc.m_pwfx->nSamplesPerSec;
		wfPCM.nAvgBytesPerSec=fileSrc.m_pwfx->nChannels*wfPCM.nSamplesPerSec*2;
		wfPCM.wBitsPerSample= 16;
		wfPCM.nBlockAlign	= wfPCM.nChannels*2;
		
		// Abrir os streams de conversão ---------------------------------
		if( acmStreamOpen(&hasPCM,NULL,fileSrc.m_pwfx,&wfPCM,NULL,NULL,NULL,ACM_STREAMOPENF_NONREALTIME) )
		{
			return FALSE;
		}

		// Preparar os buffers -------------------------------------------
		long int	nBlocks=fileSrc.m_pwfx->nAvgBytesPerSec/fileSrc.m_pwfx->nBlockAlign;
		DWORD		nBufferSizeSRC=nBlocks*fileSrc.m_pwfx->nBlockAlign;
		DWORD		nBufferSizeDST;
		DWORD		nBytesRead;
		DWORD		dwOffset=0;
		DWORD		ReadPos=0;
		BOOL		bStopDecompress=FALSE;
	
		// Calculo do tamanho dos buffers
		acmStreamSize(hasPCM,nBufferSizeSRC,&nBufferSizeDST,ACM_STREAMSIZEF_SOURCE);

		// Reservar espaço
		hBufferSRC = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeSRC);
		if( hBufferSRC == NULL ) 
		{
			return FALSE;
		}
		lpBufferSRC=(BYTE *)GlobalLock(hBufferSRC);

		hBufferDST = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeDST);
		if( hBufferDST == NULL )
		{
			return FALSE;
		}
		lpBufferDST=(short *)GlobalLock(hBufferDST);
	
		// Prepara os Headers para a compressao --------------------------
		memset(&ashPCM,0,sizeof(ACMSTREAMHEADER) );
		ashPCM.cbStruct=sizeof(ACMSTREAMHEADER) ;
		ashPCM.pbSrc=(LPBYTE)lpBufferSRC;
		ashPCM.cbSrcLength=nBufferSizeSRC;
		ashPCM.pbDst=(LPBYTE)lpBufferDST;
		ashPCM.cbDstLength=nBufferSizeDST;
		if( acmStreamPrepareHeader(hasPCM,&ashPCM,0) )
			return FALSE;

		while( !bStopDecompress )
		{
			fileSrc.Read( (LPBYTE)(lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset,&nBytesRead);

			ReadPos+=nBytesRead;

			if( nBytesRead<nBufferSizeSRC-dwOffset )
			{
				ashPCM.cbSrcLength=nBytesRead;
				bStopDecompress=TRUE;
			}
		
			mmr=acmStreamConvert(hasPCM,&ashPCM,ACM_STREAMCONVERTF_BLOCKALIGN);
		
			if( ashPCM.cbSrcLength>ashPCM.cbSrcLengthUsed )
			{
				dwOffset=ashPCM.cbSrcLength-ashPCM.cbSrcLengthUsed;
				memcpy(lpBufferSRC,lpBufferSRC+ashPCM.cbSrcLengthUsed,dwOffset);
			}
			else
				dwOffset=0;

			fileTmp.Write(lpBufferDST,ashPCM.cbDstLengthUsed);
			
			m_Progress1.SetPos(ReadPos);

			while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			} 
		}
	
		acmStreamUnprepareHeader( hasPCM,&ashPCM,0 );
		acmStreamClose(hasPCM,0);

		GlobalUnlock( hBufferSRC );
		GlobalFree( hBufferSRC );
	
		GlobalUnlock( hBufferDST );
		GlobalFree( hBufferDST );
	}

	HACMSTREAM		hasMPEG;
	ACMSTREAMHEADER ashMPEG;


	wfMPEG.wfx.cbSize			= sizeof(MPEG1WAVEFORMAT)-sizeof(WAVEFORMATEX);
	wfMPEG.wfx.nAvgBytesPerSec	= 128000*wfPCM.nChannels/8;
	wfMPEG.wfx.nBlockAlign		= 1;
	wfMPEG.wfx.nChannels		= wfPCM.nChannels;
	wfMPEG.wfx.nSamplesPerSec	= wfPCM.nSamplesPerSec;
	wfMPEG.wfx.wBitsPerSample	= 16;
	wfMPEG.wfx.wFormatTag		= WAVE_FORMAT_MPEG;
	wfMPEG.fwHeadLayer			= ACM_MPEG_LAYER2;
	wfMPEG.wHeadEmphasis		= 1;
	wfMPEG.fwHeadFlags			= ACM_MPEG_ID_MPEG1;
	if( wfPCM.nChannels==2 )
		wfMPEG.fwHeadMode = ACM_MPEG_JOINTSTEREO;
	else
		wfMPEG.fwHeadMode = ACM_MPEG_SINGLECHANNEL;
	wfMPEG.dwHeadBitrate		= 128000*wfPCM.nChannels;
	wfMPEG.dwPTSHigh			= 0;
	wfMPEG.dwPTSLow				= 0;
	wfMPEG.fwHeadModeExt		= 0;
	
	mmr = acmStreamOpen(&hasMPEG,NULL,&wfPCM,(LPWAVEFORMATEX)&wfMPEG,NULL,NULL,NULL,ACM_STREAMOPENF_NONREALTIME);

	// Preparar os buffers -------------------------------------------
	long int	nBlocks=wfPCM.nAvgBytesPerSec/wfPCM.nBlockAlign;
	DWORD		nBufferSizeSRC=nBlocks*wfPCM.nBlockAlign;
	DWORD		nBufferSizeDST;
	DWORD		nBytesRead;
	DWORD		dwOffset=0;
	DWORD		ReadPos;
	BOOL		bStopDecompress=FALSE;
	UINT		uWrite;
	
	// Calculo do tamanho dos buffers
	acmStreamSize(hasMPEG,nBufferSizeSRC,&nBufferSizeDST,ACM_STREAMSIZEF_SOURCE);

	// Reservar espaço
	hBufferSRC = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeSRC);
	if( hBufferSRC == NULL ) 
	{
		return FALSE;
	}
	lpBufferSRC=(BYTE *)GlobalLock(hBufferSRC);

	hBufferDST = GlobalAlloc(GMEM_MOVEABLE|GMEM_SHARE,nBufferSizeDST);
	if( hBufferDST == NULL )
	{
		return FALSE;
	}
	lpBufferDST=(short *)GlobalLock(hBufferDST);
	
	// Prepara os Headers para a compressao --------------------------
	memset(&ashMPEG,0,sizeof(ACMSTREAMHEADER) );
	ashMPEG.cbStruct=sizeof(ACMSTREAMHEADER) ;
	ashMPEG.pbSrc=(LPBYTE)lpBufferSRC;
	ashMPEG.cbSrcLength=nBufferSizeSRC;
	ashMPEG.pbDst=(LPBYTE)lpBufferDST;
	ashMPEG.cbDstLength=nBufferSizeDST;

	if( acmStreamPrepareHeader(hasMPEG,&ashMPEG,0) )
		return FALSE;

	if( bPCM )
	{
		ReadPos = fileSrc.GetSize();
	}
	else
	{
		ReadPos = (DWORD)fileTmp.GetLength();
		fileTmp.SeekToBegin();
	}

	fileDst.Open(strDestination.GetBuffer(0),(LPWAVEFORMATEX)&wfMPEG,WAVEFILE_WRITE);
	m_Progress1.SetRange32(0,ReadPos);

	while( !bStopDecompress )
	{
		if( bPCM )
			fileSrc.Read( (LPBYTE)(lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset,&nBytesRead);
		else
			nBytesRead = fileTmp.Read( (LPVOID)(lpBufferSRC+dwOffset),nBufferSizeSRC-dwOffset);

		ReadPos-=nBytesRead;

		if( nBytesRead<nBufferSizeSRC-dwOffset )
		{
			ashMPEG.cbSrcLength=nBytesRead;
			bStopDecompress=TRUE;
		}
		
		mmr=acmStreamConvert(hasMPEG,&ashMPEG,ACM_STREAMCONVERTF_BLOCKALIGN);
		
		if( ashMPEG.cbSrcLength>ashMPEG.cbSrcLengthUsed )
		{
			dwOffset=ashMPEG.cbSrcLength-ashMPEG.cbSrcLengthUsed;
			memcpy(lpBufferSRC,lpBufferSRC+ashMPEG.cbSrcLengthUsed,dwOffset);
		}
		else
			dwOffset=0;

		fileDst.Write(ashMPEG.cbDstLengthUsed,(LPBYTE)lpBufferDST,&uWrite);
	//	fileTmp.Write(lpBufferDST,ashMPEG.cbDstLengthUsed);
			
		m_Progress1.SetPos(ReadPos);

		while( PeekMessage(&Msg,NULL,0,0,PM_REMOVE) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	
	acmStreamUnprepareHeader( hasMPEG,&ashMPEG,0 );
	acmStreamClose(hasMPEG,0);

	GlobalUnlock( hBufferSRC );
	GlobalFree( hBufferSRC );
	
	GlobalUnlock( hBufferDST );
	GlobalFree( hBufferDST );

	return TRUE;
}

void CConversaoDlg::OnConvertaudio() 
{
	UpdateData();

	if( m_bConvertAudio )
	{
		m_cDeleteOriginal.EnableWindow();
	}
	else
	{
		m_cDeleteOriginal.EnableWindow(FALSE);
		m_cDeleteOriginal.SetCheck(0);
	}
}
