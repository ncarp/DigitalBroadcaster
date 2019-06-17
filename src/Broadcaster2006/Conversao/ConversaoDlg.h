// ConversaoDlg.h : header file
//

#if !defined(AFX_CONVERSAODLG_H__DC030F32_5726_41EA_9802_A159C01F0EDB__INCLUDED_)
#define AFX_CONVERSAODLG_H__DC030F32_5726_41EA_9802_A159C01F0EDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxdb.h>
#include "..\include\utils.h"
#include "conversao.h"

extern CString AntenaConnection;

/////////////////////////////////////////////////////////////////////////////
// CConversaoDlg dialog
#define TP_PARENT 0
#define TP_MUSICA 1
#define TP_JINGLE 2
#define TP_SINAL	3
#define TP_BLOCO	4
#define TP_SPOT	5
#define TP_PROG	6
#define TP_LISTA  7
#define TP_TAKE	8
#define TP_RM		9
#define TP_PROGRAMA 10
#define TP_MENSAGEM 11

// Registo de Tipos de Jingles ---------------------------------------------
struct TRegistoTipoJingles {
	char Codigo[4];
	char Tipo[41];
	BOOL Del;
};

// Registo de Jingles ------------------------------------------------------
struct TRegistoJingle {
	char 		Codigo[6];
	char 		Nome[41];
	char 		Genero[4];
	char 		Ritmo;
	int			Disco;
	char 		Ficheiro[260];
	long int	Duracao;
	long int	Inicio;
	long int	Fim;
	long int	Volume;
	BOOL 		Ready;
	long int	Mix;
	char 		XTra[6];
	BOOL 		Destruido;
	BOOL 		Del;
};

// Registo de autores ------------------------------------------------------
struct TRegistoAutor {
	char Codigo[5];
	char Nome[41];
	char Morada[101];
	char Clube[101];
	char Contacto[41];
	char Editora[4];
	char DataNascimento[11];
	char Nacionalidade[3];
	char Obs[51];
	__time32_t UltimaEmissao;
	__time32_t ProximaEmissao;
	long int Rotatividade;
	char XTra[34];
	BOOL Destruido;
	BOOL Del;
};

struct TRegistoMusica {
	char Codigo[8]; 		// O codigo da musica sera composto pelo codigo do
							// autor, mais o numero da faixa.
	char Titulo[41];
	char Autor[5];
	char Nacionalidade[3];
	int  Ritmo;

	char Local;

	char Disco[41];
	char Data[11];
	char Editora[4];
	char OBS[51];

	long int DuracaoTotal;
	long int Inicio;
	long int FadeIn;
	long int Intro;
	long int FadeOut;
	long int Ponte;
	long int Fim;
	BOOL ForceFadeIn;
	BOOL ForceFadeOut;
	WORD Volume;

	int  Rotatividade;
	__time32_t UltimaEmissao;
	__time32_t ProximaEmissao;

	char Lista1[4];
	char Lista2[4];
	char Special1[4];
	char Special2[4];

	char XTra[42];

    BOOL Destruido;
	BOOL Del;
};

struct TRegistoNacionalidade {
	char Codigo[3];
	char Nacionalidade[21];
	BOOL Del;
};

struct TRegistoEditora {
	char Codigo[4];
	char Nome[41];
	char Morada[101];
	char Contacto[41];
	char Telefone[41];
	char Fax[41];
	char Obs[101];
	char XTra[20];
	BOOL Destruido;
	BOOL Del;
};

struct TRegistoAngariador {
	char Codigo[11];
	char Nome[41];
	char Morada[121];
	char CP[51];
	char NC[12];
	char Telefone[41];
	char Fax[41];
	char Comissao[5];
	char OBS[161];
	BOOL Destruido;
	BOOL Del;
};

struct TRegistoClientes {
	char Codigo[11];
	char Nome[41];
	char Morada[121];
	char CP[51];
	char Telefone[41];
	char Fax[41];
	char Contacto[41];
	char Contribuinte[12];
	BOOL bAgencia,bDirecto;
	char Agencia[11];
	char Actividade[4];
	char Angariador[11];
	char OBS[161];
	BOOL Destruido;
	BOOL Del;
};

struct TRegistoActividades 
{
	char Codigo[4];
	char Actividade[41];
	BOOL Del;
};

struct TRegistoSpot {
	char 	Codigo[15];
	char 	Nome[41];
	char 	Cliente[11];
	char 	Agencia[11];
	char	Tipo[4];
	int		Disco;
	char 	Ficheiro[260];
	long int Duracao;
	long int Inicio;
	long int Mix;
	long int Fim;
	long int Volume;
	__time32_t InicioEmissao;
	__time32_t FimEmissao;
	BOOL 	Patrocinio;
	BOOL 	Ready;
	BOOL 	Destruido;
	BOOL 	Del;
};

// definicao do registo dos elementos nao publicitarios do bloco -----------
struct TRegLinhaBloco {
	char Codigo[6];
	char Tipo;
};

// Definiçao do registo das linhas de publicidade do bloco -----------------
struct TRegLinhaPubBloco {
	char Codigo[15];
	char Origem[18];
	char Genero[4];
	long int Valor;
   BOOL Emitido;
};

// definicao do registo de Parametrizacao de blocos ------------------------
struct TRegBloco {
	char Codigo[5];
	char Descricao[41];
	BOOL Dom,Seg,Ter,Qua,Qui,Sex,Sab;
	long int Hora;
	int  Precisao;  // 1=Começar, 2=Acabar, 3=quando possivel
	int  Alternativa;
	char XTra[50];
	TRegLinhaBloco Elementos[100];
	BOOL Destruido;
	BOOL Del;
};

// Definiçao do registo da componente publicitaria do bloco ----------------
struct TRegPubBloco {
	char Codigo[5];
	TRegLinhaPubBloco Primeiro;
	TRegLinhaPubBloco Segundo;
	TRegLinhaPubBloco Penultimo;
	TRegLinhaPubBloco Ultimo;
	TRegLinhaPubBloco Bloco[100];
	BOOL Destruido;
	BOOL Del;
};

// Definição do registo de calendario de emissão --------------------------
struct TRegCalendar {
	char Codigo[18];
	__time32_t DataInicio;
	__time32_t DataFinal;
	int  NEmissoes;
	long int ValorTotal;
	BOOL bEmissoes;
	BOOL Destruido;
	BOOL Del;
};

// Definição do registo de linhas do calendario ---------------------------
struct TRegCalendarLinha {
	char Codigo[21];
	char Bloco[5];
	char Dom,Seg,Ter,Qua,Qui,Sex,Sab;
	char Posicao;
	long int Valor;
	int 	NEmissoes;
	BOOL 	Del;
};

// Definicao do registo de identificaçao das musicas -----------------------
struct TMusicaLista 
{
	int	Genero;
	char  Codigo[8];
};

// Definiçao do registo de listas de musicas -------------------------------
struct TRegLista 
{
	char Codigo[4];
	char Nome[41];
	TMusicaLista Musicas[1000];
	char XTra[20];
	BOOL Destruido;
	BOOL Del;
};

class CConversaoDlg : public CDialog
{
// Construction
public:
	BOOL ConertAudioFile( CString strSource, CString strDestination );
	void ConverteFaixas();
	void ConverteInterpretes();
	void ConverteEditoras();
	void ConverteNacionalidades();
	void ConverteGeneros();
	void ConverteDiscos();
	void ConverteListas();
	void ConverteBlocos();
	void ConverteSpots();
	void ConverteActividades();
	void ConverteClientes();
	void ConverteAgencias();
	void ConverteVendedores();
	void ConverteJingles();
	void ConverteCalendarios();
	CBitmap bmTeste;
	CString strDiscos[50],strTipos[50],strDiscosV5[50];
	int		NTipos;
	int		NDisco;

	BOOL LeTipos();
	BOOL LeDiscos();
	BOOL LeDiscosV5();
	CConversaoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CConversaoDlg)
	enum { IDD = IDD_CONVERSAO_DIALOG };
	CButton	m_cDeleteOriginal;
	CStatic	m_Titulo;
	CProgressCtrl	m_Progress1;
	CProgressCtrl	m_Progress2;
	CButton	m_OK;
	CStatic	m_Texto;
	CButton	m_Teste;
	BOOL	m_Actividades;
	BOOL	m_Agencias;
	BOOL	m_Clientes;
	BOOL	m_Discos;
	BOOL	m_Editoras;
	BOOL	m_Faixas;
	BOOL	m_Generos;
	BOOL	m_Interpretes;
	BOOL	m_Jingles;
	BOOL	m_Listas;
	BOOL	m_Nacionalidades;
	BOOL	m_Spots;
	BOOL	m_Vendedores;
	BOOL	m_bDeleteOriginal;
	BOOL	m_bAudioExists;
	BOOL	m_bConvertAudio;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConversaoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CConversaoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnConvertaudio();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERSAODLG_H__DC030F32_5726_41EA_9802_A159C01F0EDB__INCLUDED_)
