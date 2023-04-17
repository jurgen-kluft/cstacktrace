#include "cbase/c_allocator.h"
#include "cbase/c_integer.h"

#include "cunittest/cunittest.h"

#include "ccallstack/c_callstack.h"


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
			ncore::xstacktrace::print();
		}
	}
}
UNITTEST_SUITE_END
