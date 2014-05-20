/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

#ifndef CScopeApp_H
#define CScopeApp_H

#include <COpenMORAMOOSApp.h>
#include <mrpt/utils/CImage.h>

class ScopeWindowApp;

class CScopeApp : public COpenMORAApp
{
	friend class ScopeWindowApp;

public:
    CScopeApp( ScopeWindowApp *the_wx_app );
    virtual ~CScopeApp();

	inline CMissionReader2ConfigFile_adaptor & getConfigFileAdaptor()  { return m_ini; }


protected:
    /** called at startup */
    virtual bool OnStartUp();
    /** called when new mail arrives */
    virtual bool OnNewMail(MOOSMSG_LIST & NewMail);
    /** called when work is to be done */
    virtual bool Iterate();
    /** called when app connects to DB */
    virtual bool OnConnectToServer();

	bool OnCommandMsg( CMOOSMsg Msg );

	bool DoRegistrations();


	ScopeWindowApp * m_theWxApp;

	void moveExternalImage(mrpt::utils::CImage &img);

};

#endif
