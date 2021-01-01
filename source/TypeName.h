#pragma once
#include <string_view>

namespace DarkMagic
{
    // ********************************
    // Compile time type information
    // ******************************** 
    template <typename T>
    constexpr std::string_view TypeName()
    {
        std::string_view Name, Prefix, Suffix;
#ifdef __clang__
        Name = __PRETTY_FUNCTION__;
        Prefix = "std::string_view TypeName() [T = ";
        Suffix = "]";
#elif defined(__GNUC__)
        Name = __PRETTY_FUNCTION__;
        Prefix = "constexpr std::string_view TypeName() [with T = ";
        Suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined(_MSC_VER)
        Name = __FUNCSIG__;
        Prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl TypeName<";
        Suffix = ">(void)";
#endif
        Name.remove_prefix(Prefix.size());
        Name.remove_suffix(Suffix.size());
        return Name;
    }
}
