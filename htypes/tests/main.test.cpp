#define CATCH_CONFIG_RUNNER
#ifdef _MSC_VER
#define CATCH_CONFIG_WINDOWS_CRTDBG
#endif
#include "catch_include.hpp"
#include <catch2/catch_session.hpp>

int main(int argc, char* argv[])
{
    Catch::Session session;  // There must be exactly once instance

    // writing to session.configData() here sets defaults
    // this is the preferred way to set them

    //    session.configData().waitForKeypress =
    //    Catch::WaitForKeypress::BeforeExit;
    //    session.configData().showSuccessfulTests = true;
    int returnCode = session.applyCommandLine(argc, argv);
    if (returnCode != 0)  // Indicates a command line error
        return returnCode;

    // writing to session.configData() or session.Config() here
    // overrides command line args
    // only do this if you know you need to

    return session.run();
}
