#include <gtest/gtest.h>
#include <c4/yml/std/std.hpp>
#include <c4/yml/yml.hpp>
#include <initializer_list>
#include <string>
#include <iostream>

#include "./test_case.hpp"

namespace c4 {
namespace yml {

// The other test executables are written to contain the declarative-style
// YmlTestCases. This executable does not have any but the build setup
// assumes it does, and links with the test lib, which requires an existing
// get_case() function. So this is here to act as placeholder until (if?)
// proper test cases are added here. This was detected in #47 (thanks
// @cburgard).
Case const* get_case(csubstr)
{
    return nullptr;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

const ParseOptions use_locations{ParseOptions::TRACK_LOCATION};


TEST(locations, basic)
{
    csubstr yaml = R"(---
foo: bar
bar:
  - 1
  - 2
baz:
    - 1_
    - 2_
)";
    Tree t = parse("myfile.yml", yaml, use_locations);
    ASSERT_TRUE(t.locations());
    EXPECT_EQ(t.rootref().location().name, csubstr{});
    EXPECT_EQ(t.rootref().location().offset, 0);
    EXPECT_EQ(t.rootref().location().line, 0);
    EXPECT_EQ(t.rootref().location().col, 0);
    const NodeRef stream = t.rootref();
    EXPECT_EQ(stream.location().name, "myfile.yml");
    EXPECT_EQ(stream.location().offset, 0);
    EXPECT_EQ(stream.location().line, 0);
    EXPECT_EQ(stream.location().col, 0);
    const NodeRef map = t.rootref().child(0);
    ASSERT_TRUE(map.is_map());
    ASSERT_TRUE(map.is_doc());
    EXPECT_EQ(map.location().name, "myfile.yml");
    EXPECT_EQ(map.location().offset, 4);
    EXPECT_EQ(map.location().line, 1);
    EXPECT_EQ(map.location().col, 0);
    const NodeRef foo = map["foo"];
    EXPECT_EQ(foo.location().name, "myfile.yml");
    EXPECT_EQ(foo.location().offset, 4 + 1);
    EXPECT_EQ(foo.location().line, 1);
    EXPECT_EQ(foo.location().col, 0);
    const NodeRef bar = map["bar"];
    EXPECT_EQ(bar.location().name, "myfile.yml");
    EXPECT_EQ(bar.location().offset, 4);
    EXPECT_EQ(bar.location().line, 2);
    EXPECT_EQ(bar.location().col, 0);
    const NodeRef one = bar[0];
    EXPECT_EQ(one.location().name, "myfile.yml");
    EXPECT_EQ(one.location().offset, 4);
    EXPECT_EQ(one.location().line, 3);
    EXPECT_EQ(one.location().col, 4);
    const NodeRef two = bar[1];
    EXPECT_EQ(two.location().name, "myfile.yml");
    EXPECT_EQ(two.location().offset, 4);
    EXPECT_EQ(two.location().line, 4);
    EXPECT_EQ(two.location().col, 4);
    const NodeRef baz = map["bar"];
    EXPECT_EQ(baz.location().name, "myfile.yml");
    EXPECT_EQ(baz.location().offset, 4);
    EXPECT_EQ(baz.location().line, 5);
    EXPECT_EQ(baz.location().col, 0);
    const NodeRef one_ = baz[0];
    EXPECT_EQ(one_.location().name, "myfile.yml");
    EXPECT_EQ(one_.location().offset, 4);
    EXPECT_EQ(one_.location().line, 6);
    EXPECT_EQ(one_.location().col, 4);
    const NodeRef two_ = baz[1];
    EXPECT_EQ(two_.location().name, "myfile.yml");
    EXPECT_EQ(two_.location().offset, 4);
    EXPECT_EQ(two_.location().line, 7);
    EXPECT_EQ(two_.location().col, 4);
}

} // namespace yml
} // namespace c4
