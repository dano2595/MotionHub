#pragma once

#include "ConfigDllExportMotionHubUtil.h"

#include "Joint.h"
#include <map>



/*!
 * \class Skeleton
 *
 * \brief Default Skeleton with all Joint poses
 *
 * \author Kester Evers and Eric Jansen
 */
class MotionHubUtil_DLL_import_export Skeleton
{

public:
	/*!
	 * default constructor
	 * creates empty skeleton with state NONE
	 */
	Skeleton();
	/*!
	 * constructor with skeleton id as argument
	 * \param sid skeleton id
	 */
	Skeleton(int sid);

	/*!
	 *  takes the joint poses and saves them in the joint map
	 * \param name name of the joint
	 * \param position
	 * \param rotation
	 */
	void parseJoint(Joint::JointNames name, Vector4f position, Quaternionf rotation, Joint::JointConfidence confidence);
	int getSid();

	std::map<Joint::JointNames, Joint> m_joints;

	enum StateSkeleton
	{
		NONE,
		INIT,
		ACTIVE,
		INACTIVE
	};

	enum StatePosture
	{
		UNKNOWN,
		STAND,
		SIT,
		CROUCH,
		JUMP,
		LIE
	};

	StatePosture getPosture();
	void setPosture(StatePosture posture);
	float getHeight();
	void setHeight(float height);

private:
	int m_sid;
	StateSkeleton m_state;
	StatePosture m_posture;
	float m_height;
};