#include "TrackerManager.h"

TrackerManager::TrackerManager()
{
	
	m_nextFreeTrackerID = 0;
	m_nextFreeAKCamID = 0;

	Console::log("TrackerManager::TrackerManager(): Created tracker manager.");

}

int TrackerManager::createTracker(TrackerType type)
{

	// get the next tracker id based on the tracker count
	int id = m_nextFreeTrackerID;

	m_nextFreeTrackerID++;

	Tracker* tempTracker;

	// create new tracker based on the tracker type
	switch (type)
	{

		// azure kinect
		case azureKinect:

			Console::log("TrackerManager::createTracker(): Creating AKtracker ...");

			//lock the tracker pool
			m_trackerPoolLock.lock();

			//create new AK Tracker with next free Cam ID
			tempTracker = new AKTracker(id, m_nextFreeAKCamID);

			//next AK Tracker has new cam ID
			m_nextFreeAKCamID++;

			// create new azure kinect tracker and insert the tracker in the tracker pool
			m_trackerPool.push_back(tempTracker);

			//unlock the tracker pool
			m_trackerPoolLock.unlock();



			//a tracker has been added, so the tracker pool has changed
			m_hasTrackerPoolChanged = true;

			Console::log("TrackerManager::createTracker(): Created Azure Kinect tracker with cam id = " + std::to_string(m_nextFreeAKCamID - 1) + ".");

			return id;

		case optiTrack:



			//lock the tracker pool
			m_trackerPoolLock.lock();

			tempTracker = new OTTracker(id);

			// create new azure kinect tracker and insert the tracker in the tracker pool
			m_trackerPool.push_back(tempTracker);

			//unlock the tracker pool
			m_trackerPoolLock.unlock();



			//a tracker has been added, so the tracker pool has changed
			m_hasTrackerPoolChanged = true;

			Console::log("TrackerManager::createTracker(): Created OptiTrack tracker.");

			return id;

		default:
			Console::log("TrackerManager::createTracker(): Can not create tracker. Unknown tracker type!");

			return -1;

	}

}


void TrackerManager::removeTrackerAt(int positionInList)
{

	m_trackerPoolLock.lock();

	//int i = 0;


	Tracker* currTracker;

	// get key of tracker with id
	//for (auto itPoolTracker = m_trackerPool.begin(); itPoolTracker != m_trackerPool.end(); itPoolTracker++)
	for(int i = 0; i < m_trackerPool.size(); i++)
	{

		if (i == positionInList)
		{
			currTracker = m_trackerPool.at(i);
			//temp = (*itPoolTracker);

			if (currTracker->getCamID() != -1)
			{


				m_nextFreeAKCamID = currTracker->getCamID();

			}

			// remove tracker with key from tracker pool
			m_trackerPool.erase(m_trackerPool.begin() + i);

			// destroy tracker with key
			currTracker->destroy();

			//a tracker has been removed, so the tracker pool has changed
			m_hasTrackerPoolChanged = true;

			Console::log("TrackerManager::removeTracker(): Removed tracker with id = " + std::to_string(i) + ".");


			break;
		}

	}

	//unlock the tracker pool
	m_trackerPoolLock.unlock();

	return;

}

void TrackerManager::startTracker()
{

	Console::log("TrackerManager::startTracker(): Starting all tracker ...");

	//lock the tracker pool
	m_trackerPoolLock.lock();


	//loop through all tracker and start everyone of them
	for (auto itTracker = m_trackerPool.begin(); itTracker != m_trackerPool.end(); itTracker++)
	{

		(*itTracker)->start();
	
	}

	//unlock the tracker pool
	m_trackerPoolLock.unlock();

	//we are now in playMode
	m_isTracking = true;

	Console::log("TrackerManager::startTracker(): Started all tracker.");

}

void TrackerManager::stopTracker()
{

	//the playMode has ended
	m_isTracking = false;

	//lock the tracker pool
	m_trackerPoolLock.lock();

	//loop through all tracker and disable everyone of them
	for (auto itTracker = m_trackerPool.begin(); itTracker != m_trackerPool.end(); itTracker++)
	{

		(*itTracker)->stop();

	}

	//unlock the tracker pool
	m_trackerPoolLock.unlock();

	Console::log("TrackerManager::stopTracker(): Stopped all tracker.");

}

bool TrackerManager::hasTrackerPoolChanged()
{

	//m_hasTrackerPoolChanged is true, reset it to flase
	if (m_hasTrackerPoolChanged)
	{

		m_hasTrackerPoolChanged = false;
		return true;

	}
	else
	{

		return false;

	}
}

bool TrackerManager::isTracking()
{

	return m_isTracking;

}


std::vector<Tracker*> TrackerManager::getPoolTracker()
{

	m_trackerPoolLock.lock();

	std::vector<Tracker*> trackerPoolCopyTemp = m_trackerPool;

	m_trackerPoolLock.unlock();



	return trackerPoolCopyTemp;

}

Tracker* TrackerManager::getTrackerRefAt(int trackerPositionInList )
{

	//Console::log("TrackerManager::getTrackerRef(): started getting Tracker. given id is: " + std::to_string(trackerPositionInList));

	int i = 0;

	m_trackerPoolLock.lock();

	//loop through tracker pool and return the tracker with given id
	for (auto itTracker = m_trackerPool.begin(); itTracker != m_trackerPool.end(); itTracker++)
	{

		//Console::log("TrackerManager::getTrackerRef(): current Tracker ID: " + std::to_string((*itTracker)->getProperties()->id) + ", current i: " + std::to_string(i));

		if (i == trackerPositionInList)
		{

			m_trackerPoolLock.unlock();

			return *itTracker;

		}

		i++;

	}

	m_trackerPoolLock.unlock();

	//Console::logError("TrackerManager::getTrackerRefAt(): Tracker does not exist!");

	return nullptr;

}

std::mutex* TrackerManager::getTrackerPoolLock()
{
	return &m_trackerPoolLock;
}
