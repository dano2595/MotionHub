#include "Skeleton.h"

Skeleton::Skeleton()
{

	m_state = NONE;

}

Skeleton::Skeleton(int sid)
{
	
	m_sid = sid;

}

void Skeleton::parseJoint(Joint::JointNames name, Vector3 position, Vector4 rotation)
{

	Joint curr_joint = Joint(position, rotation);
	m_joints.insert({ Joint::HIPS, curr_joint });	

}

int Skeleton::getSid()
{

	return m_sid;

}