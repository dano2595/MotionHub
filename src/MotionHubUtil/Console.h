#pragma once

#include "ConfigDllExportMotionHubUtil.h"

#include <windows.h>
#include <iostream>
#include <fstream>

#include <thread>
#include <list>
#include <vector>


#include "Timer.h"
#include "defines.h"

#include <atomic>
#include <mutex>
#include <thread>
#include <chrono>


/*!
 * \class Console
 *
 * \brief Utility Class for Console output
 *
 * \author Eric Jansen
 */
class MotionHubUtil_DLL_import_export Console
{

public:

	struct Message
	{
		std::string time;
		std::string type;
		std::string message;
	};



	/*!
	 * outputs info message to console
	 * \param message output message
	 */
	static void log(std::string message);
	/*!
	 * outputs warning message to console
	 * \param message output message
	 */
	static void logWarning(std::string message);
	/*!
	 * outputs error message to console
	 * \param message output message
	 */
	static void logError(std::string message);
	/*!
	 * prints Application header with author names 
	 */
	static void printHeader();
	/*!
	 * prints message to logfile 
	 * \param message output message
	 */
	static void writeToLogfile(std::string message);

	/*!
	 * temporary list of messages, which are pulled by the Console Widget in MainWindow
	 * 
	 */
	static std::vector<Message> m_messagePool;

	static std::vector<Message> getMessages();


	
};