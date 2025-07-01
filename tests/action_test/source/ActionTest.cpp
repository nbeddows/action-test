/*
Copyright (c) 2021-2025 Nicolas Beddows <nicolas.beddows@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gtest/gtest.h>

#include "action/Action.h"

namespace action::tests
{
	class ActionGTest : public testing::Test
	{
	protected:
		static std::unique_ptr<int> actionTest_;
	public:
		static void SetUpTestCase();
	};

	std::unique_ptr<int> ActionGTest::actionTest_;

	void ActionGTest::SetUpTestCase()
	{
		actionTest_ = MakeActionTest();
		ASSERT_NE(nullptr, actionTest_);
		EXPECT_EQ(42, *actionTest_);
	}

	TEST_F(ActionGTest, Version)
	{
		EXPECT_STREQ("v0.0.1", Version());
	}
}

int main(int argc, char** argv)
{
	std::cout << "Running main() from ActionGTest.cpp" << std::endl;
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
