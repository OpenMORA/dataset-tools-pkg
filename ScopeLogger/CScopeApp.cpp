/* +---------------------------------------------------------------------------+
   |                 Open MORA (MObile Robot Arquitecture)                     |
   |                  University of Almeria ARM-eCar module                    |
   |                                                                           |
   |   Copyright (C) 2014  University of Almeria                               |
   +---------------------------------------------------------------------------+ */

/**  @moos_module GUI tool: an oscilloscope module to inspect a set of variables in runtime. */

#include "CScopeApp.h"
#include "ScopeWindowApp.h"
#include "ScopeWindowMain.h"

#include <mrpt/system/string_utils.h>
#include <mrpt/system/filesystem.h>
#include <mrpt/slam/CObservation2DRangeScan.h>
#include <mrpt/slam/CObservationImage.h>
#include <mrpt/slam/CObservationStereoImages.h>
#include <mrpt/slam/CSimplePointsMap.h>
#include <mrpt/slam/CRawlog.h>

#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;

using namespace mrpt;
using namespace mrpt::utils;


CScopeApp::CScopeApp( ScopeWindowApp *the_wx_app) :
    m_theWxApp(the_wx_app)
{
	mrpt::slam::CObservation2DRangeScan  dummy1; // Just to force loading the runtime class list of [mrpt-obs]
	mrpt::slam::CSimplePointsMap dummy2;// Just to force loading the runtime class list of [mrpt-map]

}

CScopeApp::~CScopeApp()
{
}

bool CScopeApp::OnStartUp()
{
	// If want a different mode than standard:
	// - REGULAR_ITERATE_AND_MAIL
	// - COMMS_DRIVEN_ITERATE_AND_MAIL
	// - REGULAR_ITERATE_AND_COMMS_DRIVEN_MAIL
	SetIterateMode(REGULAR_ITERATE_AND_COMMS_DRIVEN_MAIL);
	SetAppFreq(10.0);
	SetCommsFreq(2000.0);
	this->m_bQuitOnIterateFail = true;

	// Read parameters from the mission configuration file.
	//! @moos_param PLOT_VARS PARAM DESCRIPTION IN ONE LINE

	std::string sVarList;
	m_MissionReader.GetConfigurationParam("PLOT_VARS",sVarList);

	std::vector<std::string> lstVarNames;
	mrpt::system::tokenize(sVarList," \t\r\n,",lstVarNames);

	MOOSTrace("[Scope] %u variables. PLOT_VARS = %s\n", (unsigned int)lstVarNames.size(), sVarList.c_str());

	// There is also a MRPT-like object (this->m_ini) that is a wrapper
	//  to read from the module config block of the current MOOS mission file.
	// m_ini.read_int(...);
	return DoRegistrations();
}

bool CScopeApp::OnCommandMsg( CMOOSMsg Msg )
{
	if(Msg.IsSkewed(MOOSTime())) return true;
	if(!Msg.IsString()) return MOOSFail("This module only accepts string command messages\n");
	const std::string sCmd = Msg.GetString();
	//MOOSTrace("COMMAND RECEIVED: %s\n",sCmd.c_str());
	// Process the command "sCmd".

	return true;
}

// Main module loop code. Do the main stuff here...
bool CScopeApp::Iterate()
{
	if (!m_theWxApp->m_theFrame) return true;

	if (m_theWxApp->m_theFrame->m_closing)
	{
		RequestQuit();
		return false;
	}

	return true;
}

bool CScopeApp::OnConnectToServer()
{
	DoRegistrations();
	return true;
}


bool CScopeApp::DoRegistrations()
{
	m_Comms.Register("*","*",0); //0.001);

	//AddMOOSVariable( ...); RegisterMOOSVariables();
	return true;
}


bool hasEnding (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

bool CScopeApp::OnNewMail(MOOSMSG_LIST &NewMail)
{
	if (!m_theWxApp->m_theFrame) return true;

	if (m_theWxApp->m_theFrame->m_closing)
	{
		RequestQuit();
		return false;
	}

	mrpt::synch::CCriticalSectionLocker csl( &m_theWxApp->m_theFrame->m_moos_cs );


	for (MOOSMSG_LIST::const_iterator it=NewMail.begin();it!=NewMail.end();++it)
	{
		const CMOOSMsg &msg = *it;

		const std::string varName = msg.GetName();

		// Special variables:
		// -----------------------------
		// Detect external imgs dir:
		if (varName=="MORA_IMAGES_DIR")
		{
			mrpt::utils::CImage::IMAGES_PATH_BASE = msg.GetString();
			MOOSTrace("Setting external images dir to: %s\n",mrpt::utils::CImage::IMAGES_PATH_BASE.c_str());
		}


		// All other variables:
		// -----------------------------

		// All non-binary vars:
		if (!msg.IsBinary())
		{
			m_theWxApp->m_theFrame->m_lstNonBinVars.insert( varName );

			std::map<std::string, ScopeWindowDialog::TTxtLog>::iterator it= m_theWxApp->m_theFrame->m_active_txt_logs.find(varName);
			if (it!= m_theWxApp->m_theFrame->m_active_txt_logs.end())
			{
				try
				{
					it->second.out->printf("%f\t", msg.GetTime());

					if (msg.IsString()) it->second.out->printf("%s", msg.GetString().c_str() );
					if (msg.IsDouble()) it->second.out->printf("%e", msg.GetDouble());

					it->second.out->printf("\n");
				}
				catch (...)
				{
				}
			}
		}

		// Double's:
		if (msg.IsDouble())
		{
			m_theWxApp->m_theFrame->m_lstAllDoubleVars.insert( varName );

			// Get data to append to plot?
			if (m_theWxApp->m_theFrame->m_active_plots.find( varName ) != m_theWxApp->m_theFrame->m_active_plots.end())
			{
				std::pair<double,double> &xy = m_theWxApp->m_theFrame->m_plots_rx_data[varName];

				if ( m_theWxApp->m_theFrame->m_first_time<0)
					 m_theWxApp->m_theFrame->m_first_time = msg.GetTime();

				xy.first = msg.GetTime() - m_theWxApp->m_theFrame->m_first_time;
				xy.second = msg.GetDouble();
			}
		}

		// binary *_OBS msgs:
		if ( msg.IsBinary() )
		{
			m_theWxApp->m_theFrame->m_lstAllMRPTObsVars.insert(varName);

			if (m_theWxApp->m_theFrame->m_active_rawlog_varnames.find(varName) != m_theWxApp->m_theFrame->m_active_rawlog_varnames.end())
			{
				try
				{
					mrpt::utils::CSerializablePtr obj;
					mrpt::utils::RawStringToObject(msg.GetString(), obj);

					// Special handle for external img files:
					using mrpt::slam::CObservationStereoImages;
					if (obj && IS_CLASS(obj,CObservationStereoImages))
					{
						mrpt::slam::CObservationStereoImagesPtr obsSt = mrpt::slam::CObservationStereoImagesPtr(obj);

						moveExternalImage(obsSt->imageLeft);
						moveExternalImage(obsSt->imageRight);
					} // end of special treatment to stereo images

					using mrpt::slam::CObservationImage;
					if (obj && IS_CLASS(obj,CObservationImage))
					{
						mrpt::slam::CObservationImagePtr obs = mrpt::slam::CObservationImagePtr(obj);

						moveExternalImage(obs->image);
					} // end of special treatment to monocular images

					// SAVE TO RAWLOG:
					m_theWxApp->m_theFrame->m_active_rawlog_file << obj;

					m_theWxApp->m_theFrame->m_active_rawlog_obs_count++;
				}
				catch (std::exception &e)
				{
					cerr << e.what() << endl;
#ifdef _MSC_VER
					::OutputDebugStringA(e.what());
#endif
				}
			}

		}

	}


	//UpdateMOOSVariables(NewMail); // Not needed
	return true;
}


// Copy external images from the temporary directory (which may be non-permanent shared memory) to the permanent rawlog directory:
void CScopeApp::moveExternalImage(mrpt::utils::CImage &img)
{
	if (!img.isExternallyStored())
		return; // No external storage.

	// Upon first case, create imgs dir:
	if (m_theWxApp->m_theFrame->m_active_rawlog_imgs_dir.empty())
	{
		m_theWxApp->m_theFrame->m_active_rawlog_imgs_dir = m_theWxApp->m_theFrame->m_active_rawlog_filename + string("_Images");
		mrpt::system::createDirectory( m_theWxApp->m_theFrame->m_active_rawlog_imgs_dir );
		std::cout << "[CScopeApp] Creating directory for rawlog images: " << m_theWxApp->m_theFrame->m_active_rawlog_imgs_dir << std::endl;
	}

	const string sFilSrc = img.getExternalStorageFileAbsolutePath();
	const string sFilDst = m_theWxApp->m_theFrame->m_active_rawlog_imgs_dir + string("/") + img.getExternalStorageFile();

	// If the image is BMP (typ. because it's stored in shared memory), convert it to a more efficient format:
	if (mrpt::system::strCmpI( mrpt::system::extractFileExtension(sFilSrc), "bmp"))
	{
		const string sFilNewDst = mrpt::system::fileNameChangeExtension(sFilDst,"png");
		mrpt::utils::CImage im;
		im.loadFromFile(sFilSrc);
		im.saveToFile(sFilNewDst, 95 /*jpg quality*/);
		// Rename external file name
		img.setExternalStorage( mrpt::system::fileNameChangeExtension(img.getExternalStorageFile(),"png") );
		;

	}
	else
	{
		// otherwise: just copy the file:
		string sErr;
		if (!mrpt::system::copyFile(sFilSrc,sFilDst, &sErr,false))
			std::cerr << "[CScopeApp] *ERROR COPYING IMAGE FILE*: " << sErr << std::endl;
	}

}
