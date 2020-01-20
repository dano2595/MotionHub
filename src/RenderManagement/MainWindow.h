#pragma once

#include "ConfigDllExportRenderManagement.h"
#include "CreateTrackerWindow.h"
#include "GlWidget.h"
#include "MotionHubUtil/Console.h"

#include <QtWidgets/QMainWindow>
#include "QtWidgets/qtreewidget.h"
#include "QtWidgets/qtablewidget.h"
#include "QtWidgets/qlineedit.h"
#include "QtCore/qstringlistmodel.h"
#include "QtCore/qstring.h"

#include <math.h>


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
	explicit MainWindow(TrackerManager* trackerManager, QWidget *parent = 0);
	/*!
	 * default destructor 
	 */
	~MainWindow();

	/*!
	 * updates Inspector and hirachy 
	 */
	void update();
	void updateConsole();

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
	void slotSelectTracker(QModelIndex index);
	/*!
	 * called when user clicks on checkbox in inspector
	 * \param item
	 */
	void slotInspectorItemChanged(QTableWidgetItem *item);

	void slotInspectorInputPosX(QString text);
	void slotInspectorInputPosY(QString text);
	void slotInspectorInputPosZ(QString text);
	void slotInspectorInputRotX(QString text);
	void slotInspectorInputRotY(QString text);
	void slotInspectorInputRotZ(QString text);
	void slotInspectorInputScaleX(QString text);
	void slotInspectorInputScaleY(QString text);
	void slotInspectorInputScaleZ(QString text);


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
	/*!
	 * reference to the tracker manager 
	 */
	TrackerManager* m_refTrackerManager;
	/*!
	 * reference to the tracker pool in the tracker manager
	 */
	std::vector<Tracker*>* m_refTrackerPool;
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

	std::map<std::string, QLineEdit*> m_inputFieldPool;

	QString toQString(float _float);


};