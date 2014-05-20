/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

/**  @moos_module Reproduces a rawlog dataset as if it was "live" */

#include "CRawlogPlayApp.h"

#include <mrpt/system/threads.h> // sleep()
#include <mrpt/slam/CRawlog.h>

#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

using namespace mrpt;
using namespace mrpt::slam;
using namespace mrpt::utils;
using namespace mrpt::slam;


CRawlogPlayApp::CRawlogPlayApp()  :
	m_time_first_obs( INVALID_TIMESTAMP ),
	m_time_warp(1.0)
{
}

CRawlogPlayApp::~CRawlogPlayApp()
{
}

bool CRawlogPlayApp::OnStartUp()
{
	// If want a different mode than standard:
	// - REGULAR_ITERATE_AND_MAIL
	// - COMMS_DRIVEN_ITERATE_AND_MAIL
	// - REGULAR_ITERATE_AND_COMMS_DRIVEN_MAIL
	//SetIterateMode(REGULAR_ITERATE_AND_MAIL);


	std::string sRawlogFile;

	//! @moos_param INPUT_RAWLOG  (Mandatory) Path to the rawlog file to open
	m_MissionReader.GetConfigurationParam("INPUT_RAWLOG",sRawlogFile);
	printf("Opening rawlog file: '%s'...\n", sRawlogFile.c_str());

	if (!m_input_file.open(sRawlogFile) )
		return false;

	// Autodetect images directory:
	const string sImgsDir = mrpt::slam::CRawlog::detectImagesDirectory(sRawlogFile);

	//!  @moos_var     MORA_IMAGES_DIR The directory where mrpt::utils::CImage store delay-load images (may be a shared memory directory)
	m_Comms.Notify("MORA_IMAGES_DIR", sImgsDir);


	//! @moos_param TIME_WARP  (Default=1.0) Time warping: <1=slower than real time.
	m_MissionReader.GetConfigurationParam("TIME_WARP",m_time_warp);

	return DoRegistrations();
}

bool CRawlogPlayApp::OnCommandMsg( CMOOSMsg Msg )
{
	if(Msg.IsSkewed(MOOSTime())) return true;
	if(!Msg.IsString()) return MOOSFail("This module only accepts string command messages\n");
	const std::string sCmd = Msg.GetString();
	//MOOSTrace("COMMAND RECEIVED: %s\n",sCmd.c_str());
	// Process the command "sCmd".

	return true;
}

bool CRawlogPlayApp::Iterate()
{
	mrpt::utils::CSerializablePtr obj;
	try
	{
		obj = m_input_file.ReadObject();
	}
	catch (mrpt::utils::CExceptionEOF &)
	{
		// This is OK, we are done:
		cout << "********* RAWLOG EOF REACHED!! *********** \n";
		this->RequestQuit();
		return false;
	}

	ASSERT_(obj.present())

	if (!IS_DERIVED(obj, CObservation))
	{
		cerr << "Read object is not mrpt::slam::CObservation!!! Ignoring...\n";
		return true;
	}

	CObservationPtr obs = CObservationPtr(obj);
	const string sensor_label = obs->sensorLabel;
	const string sVAR = sensor_label +string("_OBS");

	// Delay:
	double obs_tim_relative = .0;
	if (m_time_first_obs!=INVALID_TIMESTAMP)
	{
		obs_tim_relative = mrpt::system::timeDifference(m_time_first_obs, obs->timestamp);
	}
	else
	{
		m_time_first_obs = obs->timestamp;
		m_runtime.Tic();
	}

	obs_tim_relative = obs_tim_relative/m_time_warp;

	const double tim_delay = obs_tim_relative - m_runtime.Tac();
	printf("[%f] Label='%s' object of type %s delay=%f...\n", obs_tim_relative, sensor_label.c_str(), obs->GetRuntimeClass()->className, tim_delay );

	if (tim_delay>1e-3) {
		mrpt::system::sleep(tim_delay / 1e-3);
	}

	mrpt::vector_byte bObs;
	mrpt::utils::ObjectToOctetVector(obs.pointer(), bObs);
	//!  @moos_publish   <SENSOR_LABEL>_OBS
	//!  @moos_var     <SENSOR_LABEL>_OBS
	m_Comms.Notify(sVAR, bObs );

	return true;
}

bool CRawlogPlayApp::OnConnectToServer()
{
	DoRegistrations();
	return true;
}


bool CRawlogPlayApp::DoRegistrations()
{
	//! @moos_subscribe	MY_SUBSCRIBED_VAR1, MY_SUBSCRIBED_VAR2, MY_SUBSCRIBED_VAR3
	AddMOOSVariable(
		"MY_SUBSCRIBED_VAR1", "MY_SUBSCRIBED_VAR1", "MY_SUBSCRIBED_VAR1",
		0 /* Minimum time in seconds between updates */ );

	RegisterMOOSVariables();
	RegisterMOOSVariables_OpenMORA();
	return true;
}


bool CRawlogPlayApp::OnNewMail(MOOSMSG_LIST &NewMail)
{
	UpdateMOOSVariables(NewMail);
	UpdateMOOSVariables_OpenMORA(NewMail);
	return true;
}
