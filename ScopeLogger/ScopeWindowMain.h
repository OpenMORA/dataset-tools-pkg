/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

#ifndef SCOPEWINDOWMAIN_H
#define SCOPEWINDOWMAIN_H

//(*Headers(ScopeWindowDialog)
#include <wx/checklst.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/gbsizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/timer.h>
//*)

#include <mrpt/synch.h>
#include <mrpt/utils/CFileOutputStream.h>
#include <mrpt/utils/CFileGZOutputStream.h>

#include <mrpt/otherlibs/mathplot/mathplot.h>

class ScopeWindowApp;

class ScopeWindowDialog: public wxDialog
{
    public:

        ScopeWindowDialog(ScopeWindowApp *the_wx_app, wxWindow* parent,wxWindowID id = -1);
        virtual ~ScopeWindowDialog();
		void Init();

    //private:
        ScopeWindowApp *m_the_wx_app;

        //(*Handlers(ScopeWindowDialog)
        void OnbtnClearClick(wxCommandEvent& event);
        void OnbtnScopeAddClick(wxCommandEvent& event);
        void OntimSynchWithMOOSThreadTrigger(wxTimerEvent& event);
        void OnbtnScopeRefreshListClick(wxCommandEvent& event);
        void OnResize(wxSizeEvent& event);
        void OnbtnScopeClearPlotsClick(wxCommandEvent& event);
        void OnbtnTxtRefreshClick(wxCommandEvent& event);
        void OnbtnTxtStartClick(wxCommandEvent& event);
        void OnbtnTxtStopClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(ScopeWindowDialog)
        static const long ID_BUTTON1;
        static const long ID_BUTTON3;
        static const long ID_CHOICE1;
        static const long ID_BUTTON2;
        static const long ID_STATICLINE1;
        static const long ID_BUTTON4;
        static const long ID_PANEL2;
        static const long ID_PANEL5;
        static const long ID_PANEL1;
        static const long ID_BUTTON7;
        static const long ID_BUTTON10;
        static const long ID_BUTTON12;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT1;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL1;
        static const long ID_CHECKLISTBOX2;
        static const long ID_CHECKLISTBOX1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL4;
        static const long ID_PANEL3;
        static const long ID_NOTEBOOK1;
        static const long ID_TIMER1;
        //*)

        //(*Declarations(ScopeWindowDialog)
        wxPanel* Panel1;
        wxPanel* ScrolledWindow1;
        wxButton* btnTxtRefresh;
        wxButton* btnScopeClear;
        wxTextCtrl* edTxtFilename;
        wxButton* btnTxtStop;
        wxTextCtrl* edRawlogFilename;
        wxCheckListBox* lbOBS;
        wxStaticText* StaticText1;
        wxPanel* Panel2;
        wxButton* btnScopeRefreshList;
        wxTextCtrl* txtTxtLogState;
        wxStaticLine* StaticLine1;
        wxPanel* Panel3;
        wxButton* btnTxtStart;
        wxBoxSizer* BoxSizer1;
        wxStaticText* StaticText2;
        wxNotebook* Notebook1;
        wxBoxSizer* gridMain;
        wxTimer timSynchWithMOOSThread;
        wxButton* btnScopeClearPlots;
        wxChoice* cbScopeVarList;
        wxTextCtrl* txtRawlogState;
        wxButton* btnScopeAdd;
        wxCheckListBox* lbNonBinVars;
        //*)

        DECLARE_EVENT_TABLE()

		void rebuildPlotObjects();
		void redrawPlotObjects();
		

	public:
		// ------- Variables shared with the MOOS app thread -----------
		mrpt::synch::CCriticalSection m_moos_cs;

		std::set<std::string>         m_lstNonBinVars;      //!< All non-binary vars
		std::set<std::string>         m_lstAllDoubleVars;     //!< All double vars
		std::set<std::string>         m_lstAllMRPTObsVars;     //!< All MRPT binary-serialized vars (*_OBS pattern)

		volatile bool m_closing; //!< Signal the MOOS thread to end!

		struct TScopePlot
		{
			mpWindow * win;
			mpFXYVector *xyvectorPt,*xyvectorLin;

			TScopePlot() : win(NULL),xyvectorPt(NULL),xyvectorLin(NULL) {}
		};

		std::map<std::string, TScopePlot> m_active_plots; //!< List of active, live plots
		std::map<std::string, std::pair<double,double> > m_plots_rx_data; //!< Input buffer from the MOOS thread to append to plots

		struct TTxtLog
		{
			mrpt::utils::CFileOutputStream *out;

			TTxtLog() : out(NULL) {}
			~TTxtLog() { if (out) { delete out; out=NULL;} }
		};

		std::map<std::string, TTxtLog> m_active_txt_logs;
		double  m_first_time; //!< Origin of timestamps (-1: TBD)


		std::set<std::string>             m_active_rawlog_varnames;
		std::set<std::string>             m_initially_active_rawlog_varnames;
		mrpt::utils::CFileGZOutputStream  m_active_rawlog_file;
		std::string                       m_active_rawlog_filename;
		std::string                       m_active_rawlog_imgs_dir; //!< Empty if no image was recorded yet
		size_t                            m_active_rawlog_obs_count;
		



};

#endif // SCOPEWINDOWMAIN_H
