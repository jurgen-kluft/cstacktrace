#include "cbase/c_allocator.h"
#include "cbase/c_integer.h"

#include "cunittest/xunittest.h"

#include "ccallstack/c_callstack.h"

namespace xcore
{
	extern alloc_t* gTestAllocator;

}

UNITTEST_SUITE_BEGIN(xtrace)
{
    UNITTEST_FIXTURE(main)
    {
        UNITTEST_FIXTURE_SETUP()
		{
		}

        UNITTEST_FIXTURE_TEARDOWN()
		{
		}

		UNITTEST_TEST(trace_1)
		{
			xcore::xstacktrace::print();
		}
	}
}
UNITTEST_SUITE_END
