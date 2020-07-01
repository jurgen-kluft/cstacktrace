/**
 * @file x_crc.h
 *
 * Core Checksum functions
 */

// x_crc.h - Core Checksum functions 
#ifndef __XHASH_CHECKSUM_H__
#define __XHASH_CHECKSUM_H__
#include "xbase/x_target.h"
#ifdef USE_PRAGMA_ONCE
#pragma once
#endif

#include "xbase/x_buffer.h"

namespace xcore
{
	/**
	 * @group		xhash
	 * @brief		CRC implementations
	 */
	class xcrc
	{
	public:
		static u32			crc32(xcbuffer const& buffer, u32 inInitVal = 0);

		static u16			adler16(xcbuffer const& buffer, u16 inInitVal = 1);
		static u32			adler32(xcbuffer const& buffer, u32 inInitVal = 1);
	};


}
#endif
