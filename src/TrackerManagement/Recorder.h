#pragma once

#include <vector>
#include <atomic>

#include "ConfigDllExportTrackingManagement.h"
#include "MotionHubUtil/RecordingSession.h"







class __declspec(dllexport) Recorder
//class /*TrackingManagement_DLL_import_export*/ Recorder
{

public:

	static Recorder& instance();
	~Recorder() {}


	void toggleRecording();
	void addSkeletonsToFrame(std::map<int, Skeleton>* currSkeletons);
	void nextFrame();




private:


	Recorder() {}							// verhindert, dass ein Objekt von au�erhalb von Recorder erzeugt wird.
											// protected, wenn man von der Klasse noch erben m�chte
	Recorder(const Recorder&);				// verhindert, dass eine weitere Instanz via Kopier-Konstruktor erstellt werden kann
	Recorder& operator = (const Recorder&); //Verhindert weitere Instanz durch Kopie




	//std::mutex m_lock;

	RecordingSession* m_currSession;

	RecordingFrame m_currFrame;

	std::atomic<bool> m_isRecording;




	void startRecording();
	void stopRecording();



};


