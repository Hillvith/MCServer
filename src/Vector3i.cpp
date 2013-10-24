
#include "Globals.h"  // NOTE: MSVC stupidness requires this to be the same across all modules

#include "Vector3i.h"
#include "Vector3d.h"





Vector3i::Vector3i( const Vector3d & v )
	: x( (int)v.x )
	, y( (int)v.y )
	, z( (int)v.z )
{
}