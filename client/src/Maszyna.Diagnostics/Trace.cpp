#include <Maszyna.Diagnostics/Trace.h>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>

namespace Maszyna
{
namespace Diagnostics
{
namespace
{
    //
    //  Globals are OK here, because we implement SERVICE for engine. It acts as a wrapper for
    //  operating system API and it's intended to be globally accessible.
    //
    //  Note: this is not singleton.
    //  Note:
    //      this is module-private global variable, because we don't want to leak-out internals
    //      in header file.
    //
    FILE* GTraceFile = NULL;
}

TraceLevel::Enum Trace::_trace_level = TraceLevel::Debug;

bool Trace::Initialize(const char* filename)
{
#ifdef _MSC_VER
    return fopen_s(&GTraceFile, filename, "w") == 0;
#else
    GTraceFile = std::fopen(filename, "w");
    return GTraceFile != nullptr;
#endif
}

bool Trace::Shutdown()
{
    std::fclose(GTraceFile);
    GTraceFile = nullptr;
    return true;
}

void Trace::Fail()
{
    Dispatch(TraceLevel::Critical, "General", "Failed");
    std::exit(-1);
}

void Trace::Fail(const char* message)
{
    Dispatch(TraceLevel::Critical, "General", "Failed: %s", message);
    std::exit(-1);
}

void Trace::Fail(const char* message, const char* details)
{
    Dispatch(TraceLevel::Critical, "General", "Failed: %s. Details: %s", message, details);
    std::exit(-1);
}

bool Trace::Dispatch(TraceLevel::Enum level, const char* category, const char* format, ...)
{
    char buffer[512];
    const char* level_str = TraceLevel::ToString(level);

    //
    // Format prefix.
    //
#ifdef _MSC_VER
    sprintf_s(buffer, "%s:%s: ", category, level_str);
#else
    snprintf(buffer, 512, "%s:%s: ", category, level_str);
#endif

    //
    // Output prefix.
    //
    ::OutputDebugStringA(buffer);
    std::fputs(buffer, GTraceFile);

    //
    // Format message.
    //
    va_list args;
    va_start(args, format);
#ifdef _MSC_VER
    const int result = vsnprintf_s(buffer, sizeof(buffer) / sizeof(buffer[0]) - 1, format, args);
#else
    const int result = std::vsnprintf(&buffer[0], sizeof(buffer) / sizeof(buffer[0]) - 1, format, args);
#endif
    va_end(args);

    //
    // Output message.
    //
    ::OutputDebugStringA(buffer);
    std::fputs(buffer, GTraceFile);

    //
    // Output new line
    //
    ::OutputDebugStringA("\n");
    std::fputc('\n', GTraceFile);

    return result >= 0;
}

}
}
