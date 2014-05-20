/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

#ifndef SCOPEWINDOWAPP_H
#define SCOPEWINDOWAPP_H

#include <wx/app.h>

#include "CScopeApp.h"

#include <queue>
#include <mrpt/synch.h>
#include <mrpt/system/threads.h>
#include <mrpt/gui/WxUtils.h>

#include <MOOS/libMOOS/Utils/ProcessConfigReader.h> // for CProcessConfigReader

class ScopeWindowDialog;

class ScopeWindowApp : public wxApp
{
    public:
        ScopeWindowApp();

        virtual bool OnInit();
		virtual int OnExit();

		CScopeApp theMOOSApp;   //!< The MOOS App object
		void moos_app_thread(); //!< The thread theMOOSApp runs in.
		mrpt::system::TThreadHandle 	m_moos_thread;

		std::string sMissionFile;
		std::string sMOOSName;
		CProcessConfigReader  m_pcr; //!< A parser of the mission file, independent of that one inside the MOOSAPP object

		ScopeWindowDialog *m_theFrame;


		// ================  Shared objects between wxApp and MOOSApp ================
		std::queue< std::pair<std::string,std::string> > 	m_lstToSendToMOOS;
		mrpt::synch::CCriticalSection 						m_lstToSendToMOOS_cs;

		std::map<std::string,std::string> 	m_lstFromMOOS;  // var name -> most recent value
		mrpt::synch::CCriticalSection 		m_lstFromMOOS_cs;
		// ===========================================================================

};

#endif // SCOPEWINDOWAPP_H
