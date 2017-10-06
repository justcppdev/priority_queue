#include <catch.hpp>
#include <vector>

#include "priority_queue.hpp"

TEST_CASE("simple test", "")
{
    priority_queue_t<int> queue;
    REQUIRE( queue.empty() );
}
