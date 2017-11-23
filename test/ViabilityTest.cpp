#include <xassert/XAssert.h>

#include <iostream>
#include <memory>

int main(int argc, char * argv[]) {
    (void)argc; (void)argv;

    // NOTE: Implicitly tests XAssert's static initializer!

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

    assertNotNull(std::unique_ptr<int>(new int(3)).get());
    assertNotEqual(1, 0);

    assertStrictlyPositive(1);

    assertNull(nullptr);

    std::cout << "Test '" << argv[0] << "' passed!" << std::endl;

    return 0;
}
