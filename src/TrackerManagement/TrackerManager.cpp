#include "TrackerManager.h"

TrackerManager::TrackerManager()
{
	
	createTracker(TrackerManager::AKT);

}

void TrackerManager::createTracker(TypeTracker type)
{

	// error handling in method -> work with pointers

	int idCam = 0;

	switch (type)
	{

		case AKT:

			for (auto itPoolTracker = m_poolTracker.begin(); itPoolTracker != m_poolTracker.end(); itPoolTracker++)
			{

				if (itPoolTracker->first.first == AKT)
				{

					idCam = itPoolTracker->first.second + 1;

				}
			}

			m_poolTracker.insert({ { AKT, idCam }, new AKTracker(K4A_DEVICE_CONFIG_INIT_DISABLE_ALL, idCam) });

			Console::log("TrackerManager::createTracker(): Created AKTracker with cam id = " + std::to_string(idCam) + ".");

			break;

		case XST:

			//poolTracker.insert({ "NULL", new XSTracker() });

			Console::log("Created tracker: XSTracker.");

			break;

		default:
			break;

	}
}

std::map<std::pair<TrackerManager::TypeTracker, int>, Tracker*>* TrackerManager::getPoolTracker()
{

	return &m_poolTracker;

}