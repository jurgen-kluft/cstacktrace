#ifndef __XSTACKTRACE_STACK_TRACE_H__
#define __XSTACKTRACE_STACK_TRACE_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif


namespace xcore
{
	class xstacktrace
	{
	public:
		static void			print();
	};
}

#endif	// __XSTACKTRACE_STACK_TRACE_H__