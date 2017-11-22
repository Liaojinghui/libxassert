/*
 * Assert.h
 *
 *  Created on: Oct 6, 2014
 *      Author: Alin Tomescu <alinush@mit.edu>
 */

#pragma once

#include <cassert>
#include <iostream>
#include <cstdlib>
#include <typeinfo>

// TODO: prefix macros!
// TODO: test* family of asserts that are always enabled

namespace XAssert {

    /**
     * Dereferences a null pointer and causes the program to coredump so that
     * the state can be inspected.
     */
    bool coredump();

    /**
     * Makes sure asserts are enabled or segfaults.
     */
    void assertAssertsEnabled();
}

// Exit code for when an assertion fails
# define XASSERT_RC 1

# ifndef XASSERT_OUTPUT
// This is the std::ostream object where assert error messages go to
#  define XASSERT_OUTPUT std::cerr
# endif

// Assert error messages start with this
# define XASSERT_START XASSERT_OUTPUT << "Assertion failed in function '" << __FUNCTION__ << "', " << __FILE__ << ":" << __LINE__ << ": "

// Assert errors cause the program to exit with the following call
# define XASSERT_EXIT { XAssert::coredump(); exit(XASSERT_RC); }

# define XASSERT_NO_EVAL(expr)                                         \
   {                                                          \
     true ? static_cast<void>(0) : static_cast<void>((expr)); \
   }

# ifndef NDEBUG
#  define assertInclusiveRange(start, middle, end) { \
    assertGreaterThanOrEqual(middle, start);         \
    assertLessThanOrEqual(middle, end);              \
}
// Checks if 1st > 2nd
#  define assertStrictlyGreaterThan(bigger, smaller) { \
    if((bigger) <= (smaller)) { \
        XASSERT_START << "Expected '" << #bigger << "' (" << (bigger) \
            << ") to be strictly greater than '" << #smaller << "' (" \
            << (smaller) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if 1st < 2nd
#  define assertStrictlyLessThan(smaller, bigger) { \
    if((smaller) >= (bigger)) { \
        XASSERT_START << "Expected '" << #smaller << "' (" << (smaller) \
            << ") to be strictly less than '" << #bigger << "' (" \
            << (bigger) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if 1st >= 2nd
#  define assertGreaterThanOrEqual(bigger, smaller) { \
    if((bigger) < (smaller)) { \
        XASSERT_START << "Expected '" << #bigger << "' (" << (bigger) \
            << ") to be greater than or equal to '" << #smaller << "' (" \
            << (smaller) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if 1st <= 2nd
#  define assertLessThanOrEqual(smaller, bigger) { \
    if((smaller) > (bigger)) { \
        XASSERT_START << "Expected '" << #smaller << "' (" << (smaller) \
            << ") to be less than or equal to '" << #bigger << "' (" \
            << (bigger) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if 1st == 2nd
#  define assertEqual(first, second) { \
    if((first) != (second)) { \
        XASSERT_START << "Expected '" << #first << "' (" << (first) \
            << ") to be equal to '" << #second << "' (" \
            << (second) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if 1st != 2nd
#  define assertNotEqual(first, second) { \
    if((first) == (second)) { \
        XASSERT_START << "Expected '" << #first << "' (" << (first) \
            << ") to NOT be equal to '" << #second << "' (" \
            << (second) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if first == 0
#  define assertIsZero(first) { \
    if((first)) { \
        XASSERT_START << "Expected '" << #first << "' (" << (first) \
            << ") to be zero" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if first != 0
#  define assertNotZero(first) { \
    if((first) == 0) { \
        XASSERT_START << "Expected '" << #first << "' (" << (first) \
            << ") to NOT be zero" << std::endl; XASSERT_EXIT; \
    } \
}

// Exits with the specified error message
#  define assertFail(msg) {  \
    XASSERT_START << (msg) << std::endl; XASSERT_EXIT; }

// Checks if the specified property is true for the specified value
// Useful when you're checking a complex assertion and you want to see the value that failed that assertion.
// e.g., assertProperty(finalSign, finalSign == -1 || finalSign == 1)
#  define assertProperty(value, property) { \
    if((property) == false) { \
        XASSERT_START << "'" << #property << "' is NOT true for '" << #value << "' (" \
            << (value) << ")" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if p != NULL
#  define assertNotNull(p) { \
    if((p) == nullptr) { \
        XASSERT_START << "'" << #p << "' is NULL" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if x > 0
#  define assertStrictlyPositive(x) { \
    if((x) <= 0) { \
        XASSERT_START << "'" << #x << "' is NOT greater than zero" << std::endl; XASSERT_EXIT; \
    } \
}

// Checks if p == NULL
#  define assertNull(p) { \
    if((p) != nullptr) { \
        XASSERT_START << "'" << #p << "' is NOT NULL" << std::endl; XASSERT_EXIT; \
    } \
}

#  define assertTrue(e) { \
    if((e) != true) { \
        XASSERT_START << "'" << #e << "' is NOT true" << std::endl; XASSERT_EXIT; \
    } \
}

#  define assertFalse(e) { \
    if((e) != false) { \
        XASSERT_START << "'" << #e << "' is NOT false (i.e., it's true)" << std::endl; XASSERT_EXIT; \
    } \
}

/**
 * WARNING: You need the (void)arg around every argument 'arg.' On some compilers, not having it
 * will trigger an "error: right operand of comma operator has no effect [-Werror=unused-value]"
 */
# else

#  define assertFalse(expr) XASSERT_NO_EVAL(expr)
#  define assertTrue(expr) XASSERT_NO_EVAL(expr)
#  define assertInclusiveRange(start, middle, end) XASSERT_NO_EVAL(start) XASSERT_NO_EVAL(middle) XASSERT_NO_EVAL(end)
#  define assertStrictlyGreaterThan(bigger, smaller) XASSERT_NO_EVAL(bigger) XASSERT_NO_EVAL(smaller)
#  define assertStrictlyLessThan(smaller, bigger) XASSERT_NO_EVAL(smaller) XASSERT_NO_EVAL(bigger)
#  define assertGreaterThanOrEqual(bigger, smaller) XASSERT_NO_EVAL(bigger) XASSERT_NO_EVAL(smaller)
#  define assertLessThanOrEqual(smaller, bigger) XASSERT_NO_EVAL(smaller) XASSERT_NO_EVAL(bigger)
#  define assertEqual(first, second) XASSERT_NO_EVAL(first) XASSERT_NO_EVAL(second)
#  define assertIsZero(first) XASSERT_NO_EVAL(first)
#  define assertNotZero(first) XASSERT_NO_EVAL(first)
#  define assertFail(msg) XASSERT_NO_EVAL(msg)
#  define assertProperty(value, property) XASSERT_NO_EVAL(value) XASSERT_NO_EVAL(property)
#  define assertNotNull(p) XASSERT_NO_EVAL(p)
#  define assertNotEqual(first, second) XASSERT_NO_EVAL(first) XASSERT_NO_EVAL(second)
#  define assertStrictlyPositive(x) XASSERT_NO_EVAL(x)
#  define assertNull(p) XASSERT_NO_EVAL(p)
# endif
