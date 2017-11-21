/*
 * Assert.h
 *
 *  Created on: Nov 8, 2014
 *      Author: Alin Tomescu <alinush@mit.edu>
 */

#include <cstdio>
#include <cstdlib>

//#include <signal.h>

#ifndef _WIN32
#include <execinfo.h>
#include <unistd.h>
#endif

#include <xassert/XAssert.h>

namespace XAssert {

    bool coredump() {
        std::cerr << "Segfaulting so that you can get a coredump and check the backtrace..." << std::endl;
#ifndef _WIN32
        __builtin_trap();
#else
        abort();
#endif
        return true;
    }

    void assertAssertsEnabled() {
#ifdef NDEBUG
        XASSERT_START << "Asserts are NOT enabled and they should be. Please recompile with NDEBUG undefined." << std::endl;
        XASSERT_EXIT;
#endif
    }

    /**
     * Makes sure the compiler doesn't evaluate expressions passed in to assertX() calls when NDEBUG is defined.
     * If it does, the program will "segfault" instantly to indicate something's wrong.
     */
    class XAssertInitializer {
    private:
        static XAssertInitializer xassertInit;

    private:
        XAssertInitializer() {
        // If we're in "no debug" mode, make sure assertTrue(expr) doesn't actually evaluate 'expr'!
#ifdef NDEBUG
            assertTrue(shouldNotBeCalled());
            assertFalse(shouldNotBeCalled());
            assertInclusiveRange(shouldNotBeCalled(), shouldNotBeCalled(), shouldNotBeCalled());
            assertStrictlyGreaterThan(shouldNotBeCalled(), shouldNotBeCalled());
            assertStrictlyLessThan(shouldNotBeCalled(), shouldNotBeCalled());
            assertGreaterThanOrEqual(shouldNotBeCalled(), shouldNotBeCalled());
            assertLessThanOrEqual(shouldNotBeCalled(), shouldNotBeCalled());
            assertEqual(shouldNotBeCalled(), shouldNotBeCalled());
            assertIsZero(shouldNotBeCalled());
            assertNotZero(shouldNotBeCalled());
            assertFail(shouldNotBeCalled());
            assertProperty(4, shouldNotBeCalled());
            assertNotNull(shouldNotBeCalled());
            assertNotEqual(shouldNotBeCalled(), shouldNotBeCalled());
            assertStrictlyPositive(shouldNotBeCalled());
            assertNull(shouldNotBeCalled());

            std::clog << "Compiler successfully avoids evaluating expressions in 'assertCall(expr())' calls" << std::endl;
#else
            assertTrue(true);
            assertFalse(false);

            assertInclusiveRange(0, 0, 0);
            assertInclusiveRange(0, 0, 1);
            assertInclusiveRange(-1, 0, 0);

            assertStrictlyGreaterThan(1, 0);
            assertStrictlyLessThan(0, 1);

            assertGreaterThanOrEqual(1, 1);
            assertGreaterThanOrEqual(2, 1);

            assertLessThanOrEqual(0, 0);
            assertLessThanOrEqual(0, 1);

            assertEqual(0, 0);
            assertIsZero(0);
            assertNotZero(1);

            // This one is a hard one to test!
            //assertFail(shouldNotBeCalled());

            int val = 3;
            assertProperty(val, val % 2 == 1 && val > 2);

            assertNotNull(this);
            assertNotEqual(1, 0);

            assertStrictlyPositive(1);

            assertNull(nullptr);
#endif
        }

        bool shouldNotBeCalled() {
            std::cerr << "Oops, your compiler is not optimizing out expressions passed into XAssert calls." << std::endl;
            return coredump();
        }
    };

    /**
     * The triggered constructor call makes sure that assert expressions
     * are or aren't evaluated depending on compilation mode.
     */
    XAssertInitializer XAssertInitializer::xassertInit;
}
