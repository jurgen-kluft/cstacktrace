#ifndef __XSTACKTRACE_STACK_TRACE_H__
#define __XSTACKTRACE_STACK_TRACE_H__
#include "cbase/c_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif


namespace ncore
{
	class xstacktrace
	{
	public:
		static void			print();
	};
}

#endif	// __XSTACKTRACE_STACK_TRACE_H__