#ifndef __Maszyna_Diagnostics_Trace_hxx__
#define __Maszyna_Diagnostics_Trace_hxx__

#include <cstdint>

namespace Maszyna
{
namespace Diagnostics
{
    namespace TraceLevel
    {
        enum Enum
        {
            Disabled,
            Debug,
            Normal,
            Warning,
            Error,
            Critical
        };

        //
        // Converts trace-level to string.
        //
        inline const char* ToString(TraceLevel::Enum value)
        {
            switch (value)
            {
            case TraceLevel::Disabled:
                return "Disabled";
            case TraceLevel::Debug:
                return "Debug";
            case TraceLevel::Normal:
                return "Normal";
            case TraceLevel::Warning:
                return "Warning";
            case TraceLevel::Error:
                return "Error";
            case TraceLevel::Critical:
                return "Critical";
            default:
                return "Unknown";
            }
        }
    }

    class Trace final
    {
    public:
        static bool Initialize(const char* filename);
        static bool Shutdown();

    public:
        static void Fail();
        static void Fail(const char* message);
        static void Fail(const char* message, const char* details);
        // Unconditionally dispatches message.
        static bool Dispatch(TraceLevel::Enum level, const char* category, const char* format, ...);
        // Called by macros, to check whether need to emit Dispatch call (along with built call frame).
        static bool CanDispatch(TraceLevel::Enum level);
        static void SetLevel(TraceLevel::Enum level);

    private:
        static TraceLevel::Enum _trace_level;
    };

    inline bool Trace::CanDispatch(TraceLevel::Enum level)
    {
        return static_cast<uintptr_t>(level) < static_cast<uintptr_t>(_trace_level);
    }

    inline void Trace::SetLevel(TraceLevel::Enum level)
    {
        _trace_level = level;
    }

    // Base for trace switches.
    struct TraceSwitchBase
    {
    private:
        const char* _name;
        TraceLevel::Enum _level;
        TraceLevel::Enum _compileTimeLevel;

    public:
        TraceSwitchBase(const char* name, TraceLevel::Enum defaultLevel, TraceLevel::Enum compileTimeLevel)
            : _name(name)
            , _level(defaultLevel)
            , _compileTimeLevel(compileTimeLevel)
        {
        }

    public:
        inline const char* GetName() const
        {
            return _name;
        }

        inline bool CanDispatch(TraceLevel::Enum level) const
        {
            return level <= _level;
        }

        inline void SetLevel(TraceLevel::Enum level)
        {
            _level = level;
        }
    };

    // Trace switch implementation. Default level and compile time levels
    template <TraceLevel::Enum VDefaultLevel, TraceLevel::Enum VCompileTimeLevel>
    struct TraceSwitch : public TraceSwitchBase
    {
    public:
        enum
        {
            DefaultLevel = VDefaultLevel,
            CompileTimeLevel = VCompileTimeLevel
        };

    public:
        inline TraceSwitch(const char* name)
            : TraceSwitchBase(name, VDefaultLevel, VCompileTimeLevel)
        {
        }
    };
}
}


#define __MASZYNA_DECLARE_TRACE_SWITCH_EXTERN(SwitchName, DefaultLevel, CompileTimeLevel) \
    struct TraceSwitch_##SwitchName : public Maszyna::Diagnostics::TraceSwitch<Maszyna::Diagnostics::TraceLevel::DefaultLevel, Maszyna::Diagnostics::TraceLevel::CompileTimeLevel> \
    { \
        __forceinline TraceSwitch_##SwitchName() \
            : TraceSwitch(#SwitchName) \
        { \
        } \
    }; \
    extern TraceSwitch_##SwitchName SwitchName

#define __MASZYNA_DECLARE_TRACE_SWITCH_STATIC(SwitchName, DefaultLevel, CompileTimeLevel) \
    struct TraceSwitch_##SwitchName : public Maszyna::Diagnostics::TraceSwitch<Maszyna::Diagnostics::TraceLevel::DefaultLevel, Maszyna::Diagnostics::TraceLevel::CompileTimeLevel> \
    { \
        __forceinline TraceSwitch_##SwitchName() \
            : TraceSwitch(#SwitchName) \
        { \
        } \
    }; \
    static TraceSwitch_##SwitchName SwitchName

#define __MASZYNA_TRACE_CAN_DISPATCH(TargetLevel, ActualLevel) (((uintptr_t)(ActualLevel)) <= ((uintptr_t)(TargetLevel)))
#define __MASZYNA_TRACE_SWITCH_CAN_DISPATCH(TraceSwitchName, ActualLevel) \
    __MASZYNA_TRACE_CAN_DISPATCH(TraceSwitch_##TraceSwitchName::CompileTimeLevel, Maszyna::Diagnostics::TraceLevel::ActualLevel)

#define MASZYNA_DEFINE_TRACE_SWITCH(SwitchName) struct TraceSwitch_##SwitchName SwitchName{}
#define MASZYNA_DECLARE_TRACE_SWITCH(SwitchName, DefaultLevel, CompileTimeLevel)           __MASZYNA_DECLARE_TRACE_SWITCH_EXTERN(SwitchName, DefaultLevel, CompileTimeLevel)

#define MASZYNA_DEFINE_TRACE_SWITCH_CLASS(Class, SwitchName) Class::TraceSwitch_##SwitchName Class::SwitchName{}
#define MASZYNA_DECLARE_TRACE_SWITCH_CLASS(SwitchName, DefaultLevel, CompileTimeLevel)     protected: __MASZYNA_DECLARE_TRACE_SWITCH_STATIC(SwitchName, DefaultLevel, CompileTimeLevel)

#define MASZYNA_TRACE_WRITELINE(SwitchName, Level, Format, ...) \
    do \
    { \
        if (__MASZYNA_TRACE_SWITCH_CAN_DISPATCH(SwitchName, Level)) \
        { \
            Maszyna::Diagnostics::Trace::Dispatch(Maszyna::Diagnostics::TraceLevel::Level, SwitchName.GetName(), Format, __VA_ARGS__); \
        } \
    } while (false)

#define MASZYNA_TRACE_WRITELINE_COND(Condition, SwitchName, Level, Format, ...) \
    do \
    { \
        if (Condition) \
        { \
            if (__MASZYNA_TRACE_SWITCH_CAN_DISPATCH(SwitchName, Level)) \
            { \
                Maszyna::Diagnostics::Trace::Dispatch(Maszyna::Diagnostics::TraceLevel::Level, SwitchName.GetName(), Format, __VA_ARGS__); \
            } \
        } \
    } while (false)

#endif // __Maszyna_Diagnostics_Trace_hxx__