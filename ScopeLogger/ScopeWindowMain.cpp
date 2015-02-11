/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

#include "ScopeWindowApp.h"
#include "ScopeWindowMain.h"
#include <wx/msgdlg.h>
#include <wx/utils.h>

#include <mrpt/gui/WxUtils.h>


//(*InternalHeaders(ScopeWindowDialog)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
//*)

//(*IdInit(ScopeWindowDialog)
const long ScopeWindowDialog::ID_BUTTON1 = wxNewId();
const long ScopeWindowDialog::ID_BUTTON3 = wxNewId();
const long ScopeWindowDialog::ID_CHOICE1 = wxNewId();
const long ScopeWindowDialog::ID_BUTTON2 = wxNewId();
const long ScopeWindowDialog::ID_STATICLINE1 = wxNewId();
const long ScopeWindowDialog::ID_BUTTON4 = wxNewId();
const long ScopeWindowDialog::ID_PANEL2 = wxNewId();
const long ScopeWindowDialog::ID_PANEL5 = wxNewId();
const long ScopeWindowDialog::ID_PANEL1 = wxNewId();
const long ScopeWindowDialog::ID_BUTTON7 = wxNewId();
const long ScopeWindowDialog::ID_BUTTON10 = wxNewId();
const long ScopeWindowDialog::ID_BUTTON12 = wxNewId();
const long ScopeWindowDialog::ID_STATICTEXT2 = wxNewId();
const long ScopeWindowDialog::ID_STATICTEXT1 = wxNewId();
const long ScopeWindowDialog::ID_TEXTCTRL3 = wxNewId();
const long ScopeWindowDialog::ID_TEXTCTRL1 = wxNewId();
const long ScopeWindowDialog::ID_CHECKLISTBOX2 = wxNewId();
const long ScopeWindowDialog::ID_CHECKLISTBOX1 = wxNewId();
const long ScopeWindowDialog::ID_TEXTCTRL2 = wxNewId();
const long ScopeWindowDialog::ID_TEXTCTRL4 = wxNewId();
const long ScopeWindowDialog::ID_PANEL3 = wxNewId();
const long ScopeWindowDialog::ID_NOTEBOOK1 = wxNewId();
const long ScopeWindowDialog::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ScopeWindowDialog,wxDialog)
    //(*EventTable(ScopeWindowDialog)
    //*)
END_EVENT_TABLE()

ScopeWindowDialog::ScopeWindowDialog(ScopeWindowApp *my_app, wxWindow* parent,wxWindowID id) :
    m_the_wx_app(my_app),
	m_closing(false),
	m_first_time(-1),
	m_active_rawlog_obs_count(0)
{
    //(*Initialize(ScopeWindowDialog)
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer2;
    wxGridBagSizer* GridBagSizer2;

    Create(parent, wxID_ANY, _("UAL MOOS Scope app"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxFRAME_SHAPED|wxVSCROLL|wxHSCROLL, _T("wxID_ANY"));
    SetMinSize(wxSize(-1,400));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
    Notebook1->SetMinSize(wxSize(-1,400));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Panel1->SetMinSize(wxSize(0,0));
    FlexGridSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(1);
    Panel2 = new wxPanel(Panel1, ID_PANEL2, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    FlexGridSizer2 = new wxFlexGridSizer(1, 10, 0, 0);
    btnScopeClear = new wxButton(Panel2, ID_BUTTON1, _("Clear list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    FlexGridSizer2->Add(btnScopeClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnScopeRefreshList = new wxButton(Panel2, ID_BUTTON3, _("Refresh \'double\' var list"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    FlexGridSizer2->Add(btnScopeRefreshList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    cbScopeVarList = new wxChoice(Panel2, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    cbScopeVarList->SetMinSize(wxSize(200,-1));
    FlexGridSizer2->Add(cbScopeVarList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnScopeAdd = new wxButton(Panel2, ID_BUTTON2, _("Add plot"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    btnScopeAdd->SetDefault();
    FlexGridSizer2->Add(btnScopeAdd, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticLine1 = new wxStaticLine(Panel2, ID_STATICLINE1, wxDefaultPosition, wxSize(1,25), wxLI_VERTICAL, _T("ID_STATICLINE1"));
    FlexGridSizer2->Add(StaticLine1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 1);
    btnScopeClearPlots = new wxButton(Panel2, ID_BUTTON4, _("Clear all plots"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FlexGridSizer2->Add(btnScopeClearPlots, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel2->SetSizer(FlexGridSizer2);
    FlexGridSizer2->Fit(Panel2);
    FlexGridSizer2->SetSizeHints(Panel2);
    FlexGridSizer1->Add(Panel2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    ScrolledWindow1 = new wxPanel(Panel1, ID_PANEL5, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL5"));
    gridMain = new wxBoxSizer(wxVERTICAL);
    ScrolledWindow1->SetSizer(gridMain);
    gridMain->Fit(ScrolledWindow1);
    gridMain->SetSizeHints(ScrolledWindow1);
    FlexGridSizer1->Add(ScrolledWindow1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Panel1->SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(Panel1);
    FlexGridSizer1->SetSizeHints(Panel1);
    Panel3 = new wxPanel(Notebook1, ID_PANEL3, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    GridBagSizer2 = new wxGridBagSizer(0, 0);
    btnTxtRefresh = new wxButton(Panel3, ID_BUTTON7, _("Refresh var lists..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON7"));
    GridBagSizer2->Add(btnTxtRefresh, wxGBPosition(0, 0), wxGBSpan(2, 1), wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTxtStop = new wxButton(Panel3, ID_BUTTON10, _("STOP"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON10"));
    btnTxtStop->Disable();
    GridBagSizer2->Add(btnTxtStop, wxGBPosition(0, 5), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    btnTxtStart = new wxButton(Panel3, ID_BUTTON12, _("START"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    wxFont btnTxtStartFont(wxDEFAULT,wxDEFAULT,wxFONTSTYLE_NORMAL,wxBOLD,false,wxEmptyString,wxFONTENCODING_DEFAULT);
    btnTxtStart->SetFont(btnTxtStartFont);
    GridBagSizer2->Add(btnTxtStart, wxGBPosition(0, 4), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(Panel3, ID_STATICTEXT2, _("Text files prefix:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridBagSizer2->Add(StaticText2, wxGBPosition(0, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(Panel3, ID_STATICTEXT1, _("Rawlog name:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridBagSizer2->Add(StaticText1, wxGBPosition(1, 1), wxDefaultSpan, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    edTxtFilename = new wxTextCtrl(Panel3, ID_TEXTCTRL3, _("LOG_%Y_%m_%d_%H_%M_%S_"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    edTxtFilename->SetMinSize(wxSize(200,-1));
    GridBagSizer2->Add(edTxtFilename, wxGBPosition(0, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    edRawlogFilename = new wxTextCtrl(Panel3, ID_TEXTCTRL1, _("LOG_%Y_%m_%d_%H_%M_%S.rawlog"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    GridBagSizer2->Add(edRawlogFilename, wxGBPosition(1, 2), wxDefaultSpan, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lbNonBinVars = new wxCheckListBox(Panel3, ID_CHECKLISTBOX2, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX2"));
    GridBagSizer2->Add(lbNonBinVars, wxGBPosition(2, 0), wxGBSpan(2, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    lbOBS = new wxCheckListBox(Panel3, ID_CHECKLISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHECKLISTBOX1"));
    GridBagSizer2->Add(lbOBS, wxGBPosition(4, 0), wxGBSpan(2, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtRawlogState = new wxTextCtrl(Panel3, ID_TEXTCTRL2, _("State..."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    txtRawlogState->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    GridBagSizer2->Add(txtRawlogState, wxGBPosition(4, 3), wxGBSpan(1, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    txtTxtLogState = new wxTextCtrl(Panel3, ID_TEXTCTRL4, _("State..."), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    txtTxtLogState->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    GridBagSizer2->Add(txtTxtLogState, wxGBPosition(2, 3), wxGBSpan(1, 3), wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel3->SetSizer(GridBagSizer2);

    GridBagSizer2->AddGrowableCol(2);
    GridBagSizer2->AddGrowableRow(2);
    GridBagSizer2->AddGrowableRow(3);
    GridBagSizer2->AddGrowableRow(4);
    GridBagSizer2->AddGrowableRow(5);

    GridBagSizer2->Fit(Panel3);
    GridBagSizer2->SetSizeHints(Panel3);
    Notebook1->AddPage(Panel1, _("Live Scope"), true);
    Notebook1->AddPage(Panel3, _("Logger"), false);
    BoxSizer1->Add(Notebook1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    SetSizer(BoxSizer1);
    timSynchWithMOOSThread.SetOwner(this, ID_TIMER1);
    timSynchWithMOOSThread.Start(100, true);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnClearClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnScopeRefreshListClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnScopeAddClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnScopeClearPlotsClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnTxtRefreshClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnTxtStopClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ScopeWindowDialog::OnbtnTxtStartClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&ScopeWindowDialog::OntimSynchWithMOOSThreadTrigger);
    Connect(wxEVT_SIZE,(wxObjectEventFunction)&ScopeWindowDialog::OnResize);
    //*)
}

ScopeWindowDialog::~ScopeWindowDialog()
{
    //(*Destroy(ScopeWindowDialog)
    //*)

	m_closing = true;
	mrpt::system::sleep(2000);
}

void ScopeWindowDialog::Init()
{
	//is there a request to start logging some variables from the start?	
	for (std::set<std::string>::iterator it = m_initially_active_rawlog_varnames.begin(); it != m_initially_active_rawlog_varnames.end(); it++)
		m_lstAllMRPTObsVars.insert(*it);											//Add variables to the list of all available variables
	
	wxCommandEvent evt = wxCommandEvent(wxEVT_COMMAND_BUTTON_CLICKED, wxID_OK);
	ScopeWindowDialog::OnbtnTxtRefreshClick(evt);									//simulate the refresh variables button

	//Check only variables the user is interested in	
	for (size_t i = 0; i<lbOBS->GetCount(); i++)
	{
		std::string varName = lbOBS->GetString(i);
		if (m_initially_active_rawlog_varnames.find(varName) != m_initially_active_rawlog_varnames.end())
		{
			lbOBS->Check(i);
		}
	}
	ScopeWindowDialog::OnbtnTxtStartClick(evt);										//simulate the start button	
}

void ScopeWindowDialog::OnbtnClearClick(wxCommandEvent& event)
{
	m_lstAllDoubleVars.clear();
	cbScopeVarList->Clear();
}

void ScopeWindowDialog::OnbtnScopeAddClick(wxCommandEvent& event)
{
	if (!cbScopeVarList->GetStringSelection().IsEmpty())
	{
		m_active_plots[ std::string(cbScopeVarList->GetStringSelection().mb_str()) ];
		rebuildPlotObjects();
	}
}

void ScopeWindowDialog::OntimSynchWithMOOSThreadTrigger(wxTimerEvent& event)
{
	try
	{
		{
			mrpt::synch::CCriticalSectionLocker csl(&m_moos_cs);

			// Plots:
			for (std::map<std::string, std::pair<double,double> >::iterator it=m_plots_rx_data.begin();it!=m_plots_rx_data.end();++it)
			{
				const std::string &name = it->first;
				const std::pair<double,double> & xy = it->second;

				std::map<std::string, TScopePlot>::iterator itPlot = m_active_plots.find(name);
				if (itPlot != m_active_plots.end())
				{
					itPlot->second.xyvectorPt->AppendDataPoint(xy.first, xy.second);
					itPlot->second.xyvectorLin->AppendDataPoint(xy.first, xy.second);


					//bbox[0] = m_minX;
					//bbox[1] = m_maxX;
					//bbox[2] = m_minY;
					//bbox[3] = m_maxY;

					itPlot->second.win->UpdateBBox();
					double bb[4];
					itPlot->second.win->GetBoundingBox(bb);

					double minX = bb[0];
					double maxX = bb[1];
					double minY = bb[2];
					double maxY = bb[3];
					const double Ax = 0.1*std::max(1.0,maxX-minX);
					const double Ay = 0.1*std::max(1e-6,maxY-minY);

					itPlot->second.win->Fit(minX-Ax,maxX+Ax,minY-Ay,maxY+Ay);
				}
			}

			m_plots_rx_data.clear();

			// TXT state:
			txtTxtLogState->Clear();

			if (m_active_txt_logs.empty())
			{
				txtTxtLogState->AppendText( wxString::Format(_("Idle.")) );
			}
			else
			{
				txtTxtLogState->AppendText( wxString::Format(_("Saving %u vars..."), (unsigned int)m_active_txt_logs.size()  ) );
			}

			// Rawlog state:
			txtRawlogState->Clear();

			if (m_active_rawlog_varnames.empty())
			{
				txtRawlogState->AppendText( wxString::Format(_("Idle.")) );
			}
			else
			{
				txtRawlogState->AppendText( wxString::Format(_("Saving %u vars...\n"), (unsigned int)m_active_rawlog_varnames.size()  ) );
				txtRawlogState->AppendText( wxString::Format(_("Grabbed objects till now: %u\n"), (unsigned int)m_active_rawlog_obs_count ) );

			}




		}

		redrawPlotObjects();

	}
	catch(...)
	{
	}

	timSynchWithMOOSThread.Start(100,true);
}

void ScopeWindowDialog::OnbtnScopeRefreshListClick(wxCommandEvent& event)
{
	wxBusyCursor wait;

	std::set<std::string> allDoubleVars;
	{
		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );
		allDoubleVars = m_lstAllDoubleVars;
	}

	cbScopeVarList->Clear();
	for (std::set<std::string>::const_iterator it=allDoubleVars.begin();it!=allDoubleVars.end();++it)
	{
		cbScopeVarList->Append( _U( it->c_str()) );
	}

}


void ScopeWindowDialog::redrawPlotObjects()
{
	mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );

	for (std::map<std::string, TScopePlot>::iterator it = m_active_plots.begin();it != m_active_plots.end();++it)
	{
		if (it->second.win)
		{
			it->second.win->Refresh();
		}
	}
}


void ScopeWindowDialog::rebuildPlotObjects()
{
	{
		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );

		for (std::map<std::string, TScopePlot>::iterator it = m_active_plots.begin();it != m_active_plots.end();++it)
		{
			if (!it->second.win)
			{
				TScopePlot &p = it->second;

				p.win = new mpWindow( ScrolledWindow1, wxNewId() );
				p.win->AddLayer( new mpScaleX() );
				p.win->AddLayer( new mpScaleY() );
				p.win->LockAspect( false );
				p.win->EnableDoubleBuffer(true);
				p.win->Fit( -10,10,-10,10 );
				gridMain->Add(p.win, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);


				p.xyvectorLin = new mpFXYVector( _U(it->first.c_str()) );
				p.xyvectorLin->SetContinuity(true);
				wxPen  pen( wxColour(0x00,0x00,0xFF), 1.0, wxSOLID );
				p.xyvectorLin->SetPen(pen);
				p.xyvectorLin->ShowName(false);
				p.win->AddLayer( p.xyvectorLin );

				p.xyvectorPt = new mpFXYVector( _("Y") );
				p.xyvectorPt->SetContinuity(false);
				wxPen  pen2( wxColour(0x00,0x00,0xFF), 5.0, wxSOLID );
				p.xyvectorPt->SetPen(pen2);
				p.xyvectorLin->ShowName(true);
				p.win->AddLayer( p.xyvectorPt );
			}
		}

	}

	gridMain->Layout();

	redrawPlotObjects();
}


void ScopeWindowDialog::OnResize(wxSizeEvent& event)
{
	event.Skip();
}

void ScopeWindowDialog::OnbtnScopeClearPlotsClick(wxCommandEvent& event)
{
	{
		mrpt::synch::CCriticalSectionLocker csl(&m_moos_cs);

		for (std::map<std::string, TScopePlot>::iterator itPlot = m_active_plots.begin();itPlot!=m_active_plots.end();++itPlot)
		{
			if (itPlot->second.xyvectorPt)
			{
				itPlot->second.xyvectorPt->Clear();
				itPlot->second.xyvectorLin->Clear();
			}
		}
		m_first_time=-1;
	}

	redrawPlotObjects();
}

void ScopeWindowDialog::OnbtnTxtRefreshClick(wxCommandEvent& event)
{
	wxBusyCursor wait;

	std::set<std::string> allNonBinVars;
	std::set<std::string> allOBSVars;
	{
		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );
		allNonBinVars = m_lstNonBinVars;
		allOBSVars = m_lstAllMRPTObsVars;
	}

	lbNonBinVars->Clear();
	for (std::set<std::string>::const_iterator it=allNonBinVars.begin();it!=allNonBinVars.end();++it)
	{
		lbNonBinVars->Append( _U( it->c_str()) );
	}

	lbOBS->Clear();
	for (std::set<std::string>::const_iterator it=allOBSVars.begin();it!=allOBSVars.end();++it)
	{
		lbOBS->Append( _U( it->c_str()) );
	}

}

void ScopeWindowDialog::OnbtnTxtStartClick(wxCommandEvent& event)
{
	bool some_grabbing = false;

	// Txt log:
	wxArrayInt sels;
	sels.clear();
	for (size_t i=0;i<lbNonBinVars->GetCount();i++)
	    if (lbNonBinVars->IsChecked(i))
			sels.push_back(i);
	if (sels.size()>0)
	{
		some_grabbing = true;

		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );
		this->m_active_txt_logs.clear();

		time_t rawtime;
		struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);

		char filprefix[1024];
		strftime (filprefix, sizeof(filprefix), edTxtFilename->GetValue().mb_str() ,timeinfo );

		const std::string sPrefix = std::string(filprefix);

		for (size_t i=0;i<sels.size();i++)
		{
			const std::string sVar = std::string(lbNonBinVars->GetString( sels[i] ).mb_str());
			TTxtLog & l = m_active_txt_logs[ sVar ];

			l.out = new mrpt::utils::CFileOutputStream();

			if (!l.out->open( (sPrefix+sVar+std::string(".txt")).c_str() ) )
			{
				wxMessageBox(_("Error writing txt file!"));
				return;
			}
			l.out->printf("%%  Timestamp     Value of '%s' \n", sVar.c_str() );
		}
	}

    // Rawlog:
	sels.clear();
	for (size_t i=0;i<lbOBS->GetCount();i++)
	    if (lbOBS->IsChecked(i))
			sels.push_back(i);

	if (sels.size()>0)
	{
		some_grabbing = true;

		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );
		this->m_active_rawlog_varnames.clear();

		m_active_rawlog_obs_count = 0;
		m_active_rawlog_imgs_dir.clear();

		time_t rawtime;
		struct tm * timeinfo;
		time (&rawtime);
		timeinfo = localtime (&rawtime);

		char fil[1024];
		strftime (fil, sizeof(fil), edRawlogFilename->GetValue().mb_str() ,timeinfo );
		const std::string sFil = std::string(fil);
		m_active_rawlog_filename = fil;

		if (!m_active_rawlog_file.open(fil) )
		{
			wxMessageBox(_("Error writing rawlog file!"));
			return;
		}

		for (size_t i=0;i<sels.size();i++)
		{
			const std::string sVar = std::string(lbOBS->GetString( sels[i] ).mb_str());
			m_active_rawlog_varnames.insert(sVar);
		}
	}

	if (some_grabbing)
	{
		btnTxtStart->Disable();
		btnTxtStop->Enable();
	}
}

void ScopeWindowDialog::OnbtnTxtStopClick(wxCommandEvent& event)
{
    // Stop txt log:
	{
		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );
		this->m_active_txt_logs.clear();
	}

    // Stop rawlog:
	{
		mrpt::synch::CCriticalSectionLocker csl( &m_moos_cs );
		this->m_active_rawlog_varnames.clear();
		m_active_rawlog_file.close();
	}

	btnTxtStart->Enable();
	btnTxtStop->Disable();
}
