#include "cbase/c_base.h"
#include "cbase/c_allocator.h"
#include "cbase/c_console.h"

#include "cunittest/cunittest.h"
#include "cunittest/private/ut_ReportAssert.h"


UNITTEST_SUITE_LIST(xStackTraceUnitTest);
UNITTEST_SUITE_DECLARE(xStackTraceUnitTest, xtrace);

namespace xcore
{
	// Our own assert handler
	class UnitTestAssertHandler : public xcore::xasserthandler
	{
	public:
		UnitTestAssertHandler()
		{
			NumberOfAsserts = 0;
		}

		virtual xcore::xbool	handle_assert(u32& flags, const char* fileName, s32 lineNumber, const char* exprString, const char* messageString)
		{
			UnitTest::reportAssert(exprString, fileName, lineNumber);
			NumberOfAsserts++;
			return false;
		}


		xcore::s32		NumberOfAsserts;
	};

	class UnitTestAllocator : public UnitTest::Allocator
	{
		xcore::alloc_t*	mAllocator;
	public:
						UnitTestAllocator(xcore::alloc_t* allocator)	{ mAllocator = allocator; }
		virtual void*	Allocate(xsize_t size)								{ return mAllocator->allocate((u32)size, sizeof(void*)); }
		virtual xsize_t	Deallocate(void* ptr)								{ return mAllocator->deallocate(ptr); }
	};

	class TestAllocator : public alloc_t
	{
		alloc_t*		mAllocator;
	public:
							TestAllocator(alloc_t* allocator) : mAllocator(allocator) { }

		virtual const char*	name() const										{ return "xhash unittest test heap allocator"; }

		virtual void*		v_allocate(xsize_t size, u32 alignment)
		{
			UnitTest::IncNumAllocations();
			return mAllocator->allocate(size, alignment);
		}

		virtual u32			v_deallocate(void* mem)
		{
			UnitTest::DecNumAllocations();
			return mAllocator->deallocate(mem);
		}

		virtual void		v_release()
		{
			mAllocator->release();
			mAllocator = NULL;
		}
	};
}

xcore::alloc_t* gTestAllocator = NULL;
xcore::UnitTestAssertHandler gAssertHandler;


bool gRunUnitTest(UnitTest::TestReporter& reporter)
{
	cbase::x_Init();

#ifdef TARGET_DEBUG
	xcore::xasserthandler::sRegisterHandler(&gAssertHandler);
#endif

	xcore::alloc_t* systemAllocator = xcore::alloc_t::get_system();
	xcore::UnitTestAllocator unittestAllocator( systemAllocator );
	UnitTest::SetAllocator(&unittestAllocator);

	xcore::console->write("Configuration: ");
	xcore::console->writeLine(TARGET_FULL_DESCR_STR);

	xcore::TestAllocator testAllocator(systemAllocator);
	gTestAllocator = &testAllocator;

	int r = UNITTEST_SUITE_RUN(reporter, xStackTraceUnitTest);
	if (UnitTest::GetNumAllocations()!=0)
	{
		reporter.reportFailure(__FILE__, __LINE__, "cunittest", "memory leaks detected!");
		r = -1;
	}

	gTestAllocator->release();

	UnitTest::SetAllocator(NULL);

	cbase::x_Exit();
	return r==0;
}

