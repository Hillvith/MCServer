#pragma once

#include "Socket.h"

class cTCPLink																	//tolua_export
{																				//tolua_export
public:																			//tolua_export
	cTCPLink();																	//tolua_export
	~cTCPLink();																//tolua_export

	bool Connect   (const AString & a_Address, unsigned int a_Port );					//tolua_export
	int Send       (const char * a_Data, unsigned int a_Size, int a_Flags = 0 );				//tolua_export
	int SendMessage(const char * a_Message, int a_Flags = 0 );					//tolua_export
	void CloseSocket();															//tolua_export
protected:																		//tolua_export
	virtual void ReceivedData( char a_Data[256], int a_Size ) = 0;		//tolua_export

	static void ReceiveThread( void* a_Param );

	cSocket m_Socket;
	cEvent* m_StopEvent;
};	//tolua_export