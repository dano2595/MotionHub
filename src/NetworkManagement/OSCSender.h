#pragma once

#include "NetworkSender.h"

#include "UdpSocket.h"
#include "OscOutboundPacketStream.h"

#include "defines.h"
#include "MotionHubUtil/Vector3.h"
#include "MotionHubUtil/Vector4.h"
#include "MotionHubUtil/Skeleton.h"
#include "MotionHubUtil/Console.h"

/*!
 * \class OSCSender
 *
 * \brief Implements OSC Protocol
 *
 * \author Kester Evers and Eric Jansen
 */
class OSCSender : public NetworkSender
{

private:
	char buffer[OUTPUT_BUFFER_SIZE];
	UdpTransmitSocket* m_transmitSocket = nullptr;
	osc::OutboundPacketStream* m_packetStream = nullptr;

public:

	OSCSender();
	OSCSender(std::string address, int port);

	void sendSkeleton(Skeleton* skeleton, const char* uri) override;

};