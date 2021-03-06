#pragma once

#include "ConfigDllExportRenderManagement.h"
#include "CreateTrackerWindow.h"
#include "GlWidget.h"
#include "MotionHubUtil/Console.h"
#include "SettingsWindow.h"
#include "trackermodwindow.h"

#include "QtWidgets/qtreewidget.h"
#include "QtWidgets/qtablewidget.h"
#include "QtWidgets/qlineedit.h"
#include "QtCore/qstringlistmodel.h"
#include "QtCore/qstring.h"

#include <math.h>
#include <MotionHubUtil/MMHmath.h>



#define GET_VARIABLE_NAME(Variable) (#Variable)


#include <chrono>
#include <atomic>
#include <list>
#include <map>

namespace Ui
{

	class MainWindow;

}

/*!
 * \class MainWindow
 * 
 * \brief Qt main Window wrapper containing slot methods
 * 
 * \author Eric Jansen and Kester Evers
 * 
 */
class RenderManagement_DLL_import_export MainWindow : public QMainWindow
{
	Q_OBJECT
public:

	/*!
	 * default constructor  
	 */
	explicit MainWindow(TrackerManager* trackerManager, ConfigManager* configManager, QWidget *parent = 0);
	/*!
	 * default destructor 
	 */
	~MainWindow();

	/*!
	 * updates Inspector and hirachy 
	 */
	void update();

	/*!
	* gets new logs from the Console and displays them in the list item
	*/
	void updateConsole();

	void setTimelineValue(float time, int frameNum, int numFrames);

	bool m_timelineActive;


	GlWidget* getOglRenderer();


private slots:
	/*!
	 * called when user clicks start/stop button 
	 */
	void slotToggleTracking();
	/*!
	 * called when user clicks "add" tracker button 
	 */
	void slotAddTracker();

	void slotAddGroup();

	/*!
	 * called when user clicks "remove" tracker button
	 */
	void slotRemoveTracker();
	/*!
	 *  called when user clicks on File->Exit
	 */
	void on_actionExit_triggered();
	/*!
	 * called when user clicks on tracker in list 
	 * \param index id of clicked tracker
	 */
	void slotTrackerSelectionChanged();
	/*!
	 * called when user clicks on checkbox in inspector
	 * \param item
	 */
	void slotInspectorItemChanged(QTableWidgetItem *item);

	void slotNetworkSettings();

	void slotInspectorInputPosX(QString text);
	void slotInspectorInputPosY(QString text);
	void slotInspectorInputPosZ(QString text);
	void slotInspectorInputRotX(QString text);
	void slotInspectorInputRotY(QString text);
	void slotInspectorInputRotZ(QString text);
	void slotInspectorInputScaleX(QString text);
	void slotInspectorInputScaleY(QString text);
	void slotInspectorInputScaleZ(QString text);

	void slotResetTrackerOffset();

	void slotModifyTrackerRotations();

	void slotTimelinePressed();
	void slotTimelineReleased();
	void slotTimelineValueChanged(int newValue);

	void slotRecord();

	void slotTimelineLableModeChanged(int idx);

private:
	/*!
	 * qt class generated by the moc
	 */
	Ui::MainWindow *ui;

	GlWidget* m_oglRenderer;
	/*!
	 * createTracker dialog
	 */
	CreateTrackerWindow* m_createTrackerWindow;

	ConfigManager* m_configManager;

	SettingsWindow* m_netwokSettingsWindow;

	TrackerModWindow* m_trackerModWindow;
	

	/*!
	 * reference to the tracker manager 
	 */
	TrackerManager* m_refTrackerManager;

	/*!
	 * map of top level items in hirachy
	 * each tracker has a list of skeletons as children
	 */
	std::map<QTreeWidgetItem*, std::list<QTreeWidgetItem*>> m_hirachyItemPool;

	/*!
	 *  tracking state for changing icon
	 */
	bool m_isTracking = false;

	/*!
	 *  recording state for changing icon
	 */
	bool m_isRecording = false;
	/*!
	 * true when tracker is selected and inspector isn't empty
	 */
	bool m_isInspectorInit = false;
	/*!
	 * id of the currently selected tracker 
	 */
	int m_selectedTrackerInList;

	Tracker* m_selectedTracker;

	/*!
	 *  updates hirachy and items in it
	 */
	void updateHirachy();
	/*!
	 *  creates new rows and items in the inspector
	 */
	void drawInspector();
	/*!
	 *  updates inspector and items in it
	 */
	void updateInspector();
	/*!
	 * clears all inspector content 
	 */
	void clearInspector();
	/*!
	 * 
	 * adds new row with property and value to the inspector
	 * 
	 * \param propertyName name of the property
	 * \param valueName value connected to property
	 */
	void addRowToInspector(std::string propertyName, std::string valueName);
	/*!
	 *  switches icon of the start/stop button to the opposite icon
	 */
	void toggleTrackingButtons();

	void toggleRecButtons();


	std::map<std::string, QLineEdit*> m_inputFieldPool;

	QString toQString(float _float);

	void addTrackerToList(int id);

	enum TimelineLableMode
	{
		percentage,
		elTime,
		frame
	};

	TimelineLableMode m_timelineLableState;

	void saveRecord();

	void progressionBarThread();

	int m_recordSaveProgression;



};