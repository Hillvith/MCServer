#include "cMCLogger.h"
#include "cWebPlugin_Lua.h"
#include "cPlugin_NewLua.h"

#include <string>
#include "tolua++.h"
#include "cWebAdmin.h"

extern bool report_errors(lua_State* lua, int status);
extern std::vector<std::string> StringSplit(std::string str, std::string delim);

struct cWebPlugin_Lua::sWebPluginTab
{
	std::string Title;
	std::string SafeTitle;

	int Reference;
};

cWebPlugin_Lua::cWebPlugin_Lua( cPlugin_NewLua* a_Plugin )
	: cWebPlugin( a_Plugin->GetLuaState() )
	, m_Plugin( a_Plugin )
{

}

cWebPlugin_Lua::~cWebPlugin_Lua()
{
	for( TabList::iterator itr = m_Tabs.begin(); itr != m_Tabs.end(); ++itr )
	{
		delete *itr;
	}
	m_Tabs.clear();
}

bool cWebPlugin_Lua::AddTab( const char* a_Title, lua_State * a_LuaState, int a_FunctionReference )
{
	if( a_LuaState != m_Plugin->GetLuaState() )
	{
		LOGERROR("Only allowed to add a tab to a WebPlugin of your own Plugin!");
		return false;
	}
	sWebPluginTab* Tab = new sWebPluginTab();
	Tab->Title = a_Title;
	Tab->SafeTitle = a_Title; // TODO - Convert all non alphabet/digit letters to underscores

	Tab->Reference = a_FunctionReference;

	m_Tabs.push_back( Tab );
	return true;
}

std::string cWebPlugin_Lua::HandleRequest( HTTPRequest* a_Request )
{
	lua_State* LuaState = m_Plugin->GetLuaState();
	std::string RetVal = "";

	std::string TabName = GetTabNameForRequest(a_Request);
	if( TabName.empty() )
		return "";

	sWebPluginTab* Tab = 0;
	for( TabList::iterator itr = m_Tabs.begin(); itr != m_Tabs.end(); ++itr )
	{
		if( (*itr)->Title.compare( TabName ) == 0 ) // This is the one! Rawr
		{
			Tab = *itr;
			break;
		}
	}

	if( Tab )
	{
		LOGINFO("1. Stack size: %i", lua_gettop(LuaState) );
		lua_rawgeti( LuaState, LUA_REGISTRYINDEX, Tab->Reference); // same as lua_getref()

		LOGINFO("2. Stack size: %i", lua_gettop(LuaState) );
		// Push HTTPRequest
		tolua_pushusertype( LuaState, a_Request, "HTTPRequest" );
		LOGINFO("Calling bound function! :D");
		int s = lua_pcall( LuaState, 1, 1, 0);
		if( report_errors( LuaState, s ) )
		{
			LOGINFO("error. Stack size: %i", lua_gettop(LuaState) );
			return false;
		}


		if( !lua_isstring( LuaState, -1 ) )
		{
			LOGWARN("WARNING: WebPlugin tab '%s' did not return a string!", Tab->Title.c_str() );
			lua_pop(LuaState, 1); // Pop return value
			return "";
		}

		RetVal += tolua_tostring(LuaState, -1, 0);
		lua_pop(LuaState, 1); // Pop return value
		LOGINFO("ok. Stack size: %i", lua_gettop(LuaState) );
	}

	return RetVal;
}

void cWebPlugin_Lua::Initialize()
{
}

std::string cWebPlugin_Lua::GetTabNameForRequest( HTTPRequest* a_Request )
{
	std::vector<std::string> Split = StringSplit( a_Request->Path, "/" );

	if( Split.size() > 1 )
	{
		sWebPluginTab* Tab = 0;
		if( Split.size() > 2 )	// If we got the tab name, show that page
		{
			for( TabList::iterator itr = m_Tabs.begin(); itr != m_Tabs.end(); ++itr )
			{
				if( (*itr)->SafeTitle.compare( Split[2] ) == 0 ) // This is the one! Rawr
				{
					Tab = *itr;
					break;
				}
			}
		}
		else	// Otherwise show the first tab
		{
			if( m_Tabs.size() > 0 )
				Tab = *m_Tabs.begin();
		}

		if( Tab )
		{
			return Tab->Title;
		}
	}

	return "";
}

std::list< std::string > cWebPlugin_Lua::GetTabNames()
{
	std::list< std::string > NameList;
	for( TabList::iterator itr = m_Tabs.begin(); itr != m_Tabs.end(); ++itr )
	{
		NameList.push_back( (*itr)->Title );
	}
	return NameList;
}