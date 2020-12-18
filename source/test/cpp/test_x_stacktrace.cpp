#include "xbase/x_allocator.h"
#include "xbase/x_integer.h"

#include "xunittest/xunittest.h"

#include "xcallstack/x_callstack.h"

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
