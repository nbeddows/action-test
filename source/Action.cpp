#include "action/Action.h"

namespace action
{
	const char* Version()
    {
        return "v0.0.1";
    }

	std::unique_ptr<int> MakeActionTest()
    {
        return std::make_unique<int>(42);
    }
}