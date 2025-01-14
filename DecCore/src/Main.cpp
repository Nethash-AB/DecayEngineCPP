#include "GlobalEnvironment.hpp"
#include <cassert>

using namespace DecFramework;
using namespace DecFramework::Database;
using namespace DecFramework::Graph;
using namespace DecFramework::Log;
using namespace DecFramework::Object;
using namespace DecFramework::Tracking;

using namespace DecCore;

int main(int argc, const char* argv[])
{
    IGlobalEnvironment* gEnv = new GlobalEnvironment();
    const IDatabaseId* id = gEnv->GetObjectDatabase()->GetDatabaseIdForString("0001-00000000-0000000000000000");
    assert(!gEnv->GetObjectDatabase()->IsValidReference(id));

    return 0;
}