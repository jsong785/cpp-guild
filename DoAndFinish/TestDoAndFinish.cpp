#include "catch.hpp"
#include "DoAndFinish.h"
#include <functional>

TEST_CASE("DoAndFinish Primitive", "")
{
    int doCount{ 0 };
    int finishCount{ 0 };

    const auto doFunc{ 
        DoAndFinish(
                [&doCount](){ ++doCount; }, 
                [&doCount](){ return (doCount%2) != 0; },
                [&finishCount](){ ++finishCount; }
                ) 
    };

    CHECK(doCount == 0);
    CHECK(finishCount == 0);

    doFunc();
    CHECK(finishCount == 0);
    CHECK(doCount == 1);

    doFunc();
    CHECK(finishCount == 1);
    CHECK(doCount == 2);

    const auto finish{ doFunc() };
    CHECK(finishCount == 1);
    CHECK(doCount == 3);

    finish();
    CHECK(finishCount == 2);
    CHECK(doCount == 3);

    finish();
    CHECK(finishCount == 3);
    CHECK(doCount == 3);
}

TEST_CASE("DoAndFinish With Arguments", "")
{
    int doCount{ 0 };
    int finishCount{ 0 };

    const auto doFunc{ 
        DoAndFinish(
                [&doCount](const auto injectDoCount){ doCount = injectDoCount; }, 
                [&doCount](){ return (doCount%2) != 0; },
                [&finishCount](const auto injectDoCount){ finishCount = injectDoCount; }
                ) 
    };

    CHECK(doCount == 0);
    CHECK(finishCount == 0);

    doFunc(0);
    CHECK(finishCount == 0);

    doFunc(2);
    CHECK(finishCount == 0);
    CHECK(doCount == 2);
}
