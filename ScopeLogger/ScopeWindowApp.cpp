/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

#include "ScopeWindowApp.h"

//(*AppHeaders
#include "ScopeWindowMain.h"
#include <wx/image.h>
//*)

using namespace std;

IMPLEMENT_APP(ScopeWindowApp);

ScopeWindowApp::ScopeWindowApp() :
    theMOOSApp		(this),
    sMissionFile 	("Mission.moos"),
    sMOOSName 		("ScopeLogger"),
    m_theFrame 		(NULL)
{
}

bool ScopeWindowApp::OnInit()
{
	// Starting in wxWidgets 2.9.0, we must reset numerics locale to "C",
	//  if we want numbers to use "." in all countries. The App::OnInit() is a perfect place to undo
	//  the default wxWidgets settings. (JL @ Sep-2009)
	wxSetlocale(LC_NUMERIC,wxString(wxT("C")));

    switch(argc)
    {
    case 3:
        sMOOSName = string( wxString(argv[2]).mbc_str() );
    case 2:
        sMissionFile = string( wxString(argv[1]).mbc_str() );
    }

	// Before launching the MOOS APP, load the mission file from the (this) main thread:
    m_pcr.SetAppName(sMOOSName);
    if (!m_pcr.SetFile(sMissionFile))
		cerr << mrpt::format("iRobotGUI: Error parsing mission file:'%s'\n",sMissionFile.c_str());

    // launch MOOS APP thread:
	m_moos_thread = mrpt::system::createThreadFromObjectMethod(this,&ScopeWindowApp::moos_app_thread);

    wxInitAllImageHandlers();
    m_theFrame = new ScopeWindowDialog(this,0);
    SetTopWindow(m_theFrame);
    m_theFrame->ShowModal();

    return false;
}


int ScopeWindowApp::OnExit()
{
	theMOOSApp.RequestQuit();
	cout << "[ScopeApp] Waiting for MOOS-app thread to exit." << endl;
	mrpt::system::joinThread(m_moos_thread);
	return wxApp::OnExit();
}

void ScopeWindowApp::moos_app_thread()
{
	try
	{
		cout << "[ScopeApp] Starting MOOS-app thread." << endl;

		this->theMOOSApp.Run(sMOOSName.c_str(),sMissionFile.c_str());

		cout << "[ScopeApp] Exiting MOOS-app thread." << endl;
	}
	catch (std::exception &e)
	{
		wxMessageBox( _U(e.what()), _("Exception in MOOS-app thread") );
	}
	catch (...)
	{
		wxMessageBox( _("Untyped exception"), _("Exception in MOOS-app thread") );
	}
}
