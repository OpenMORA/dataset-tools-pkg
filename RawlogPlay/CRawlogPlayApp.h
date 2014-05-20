/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

#ifndef CRawlogPlayApp_H
#define CRawlogPlayApp_H

#include <COpenMORAMOOSApp.h>

#include <mrpt/slam/CObservation.h>
#include <mrpt/utils/CTicTac.h>
#include <mrpt/utils/CFileGZInputStream.h>
#include <mrpt/system/datetime.h>

class CRawlogPlayApp : public COpenMORAApp
{
public:
    CRawlogPlayApp();
    virtual ~CRawlogPlayApp();

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

	// DATA:

	mrpt::utils::CTicTac             m_runtime;
	mrpt::utils::CFileGZInputStream  m_input_file;
	mrpt::system::TTimeStamp         m_time_first_obs;

	double m_time_warp; //!< =1:real time, <1: slower than real time


};
#endif
