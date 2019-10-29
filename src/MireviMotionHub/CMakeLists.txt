# CmakeLists for MireviMotionHub

#osg
include_directories(${CMAKE_BINARY_DIR}/src ${OSG_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${OSG_LIBRARIES_DIR})
#k4a
include_directories(${CMAKE_BINARY_DIR}/src ${K4A_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${K4A_LIBRARIES_DIR})
#k4abt
include_directories(${CMAKE_BINARY_DIR}/src ${K4ABT_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${K4ABT_LIBRARIES_DIR})
#Cudnn
include_directories(${CMAKE_BINARY_DIR}/src ${Cudnn_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${Cudnn_LIBRARIES_DIR})
#OSCpack
include_directories(${CMAKE_BINARY_DIR}/src ${OSCp_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${OSCp_LIBRARIES_DIR})
#Qt
include_directories(${CMAKE_BINARY_DIR}/src ${Qt5ForMireviMotionHub_INCLUDE_DIR})
link_directories(${CMAKE_BINARY_DIR}/lib "${CMAKE_BINARY_DIR}/lib" ${Qt5ForMireviMotionHub_LIBRARIES_DIR})

#include internal source files
include_directories(${CMAKE_BINARY_DIR}/src/MotionHubUtil)
include_directories(${CMAKE_BINARY_DIR}/src/NetworkManagement)
include_directories(${CMAKE_BINARY_DIR}/src/TrackerManagement)
include_directories(${CMAKE_BINARY_DIR}/src/UIManagement)
include_directories(${CMAKE_BINARY_DIR}/src/3DRenderManagement)
include_directories(${CMAKE_BINARY_DIR}/src/GestureManagement)
link_directories(${CMAKE_BINARY_DIR}/lib)

file(GLOB_RECURSE MotionHub_HEADER "${CMAKE_CURRENT_SRC_DIR}" *.h)
file(GLOB_RECURSE MotionHub_SRC "${CMAKE_CURRENT_SRC_DIR}" *.cpp)
add_executable(MireviMotionHub ${MotionHub_HEADER} ${MotionHub_SRC})

target_link_libraries(MireviMotionHub
    debug osg${CMAKE_DEBUG_POSTFIX} optimized osg
    debug osgDB${CMAKE_DEBUG_POSTFIX} optimized osgDB
    debug osgGA${CMAKE_DEBUG_POSTFIX} optimized osgGA
    debug osgUtil${CMAKE_DEBUG_POSTFIX} optimized osgUtil
    debug osgViewer${CMAKE_DEBUG_POSTFIX} optimized osgViewer
    debug OpenThreads${CMAKE_DEBUG_POSTFIX} optimized OpenThreads
    debug k4a optimized k4a
	debug k4abt optimized k4abt
	debug cudnn optimized cudnn
	debug oscpack optimized oscpack
	debug Ws2_32 optimized Ws2_32
	debug winmm optimized winmm		
	debug Qt5Core${CMAKE_DEBUG_POSTFIX} optimized Qt5Core
	debug Qt5Widgets${CMAKE_DEBUG_POSTFIX} optimized Qt5Widgets
	
	debug MotionHubUtil${CMAKE_DEBUG_POSTFIX} optimized MotionHubUtil
	debug NetworkManagement${CMAKE_DEBUG_POSTFIX} optimized NetworkManagement
	debug TrackerManagement${CMAKE_DEBUG_POSTFIX} optimized TrackerManagement
	debug GestureManagement${CMAKE_DEBUG_POSTFIX} optimized GestureManagement
	debug UIManagement${CMAKE_DEBUG_POSTFIX} optimized UIManagement
	# debug 3DRenderManagement${CMAKE_DEBUG_POSTFIX} optimized 3DRenderManagement	
)

set_target_properties(MireviMotionHub PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin")