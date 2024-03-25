#pragma once
#include <assert.h>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <type_traits>
#include <vector>

#include "Colours.h"

#define MAX_ARGS 256

namespace alx {

namespace __alx {

    template <typename T>
    concept Stringable = std::convertible_to<T, std::string>;

    template <typename T>
    concept Number = std::is_arithmetic_v<T> && !
    std::is_same_v<T, bool>;

    template <typename T>
    concept Boolean = std::is_same_v<T, bool>;

    template <__alx::Stringable T>
    std::string string_cast(T from) { return from; }

    template <Boolean T>
    std::string string_cast(T from) { return from ? "true" : "false"; }

    template <__alx::Number T>
    std::string string_cast(T from) { return std::to_string(from); }

    template <typename... Param>
    class VariadicArgParser {

        std::string _text;
        std::string _format;
        std::vector<std::string> _args;

        template <typename T, typename... Rest>
        void SetArgs(T& first, Rest&... rest)
        {
            _args.push_back(string_cast(first));
            SetArgs(rest...);
        }

        void SetArgs() { }

        std::string parseColourSequence(const std::string& str)
        {
            std::stringstream stream(str);
            std::string item;
            std::string out = "\033[38;2";
            int matches = 0;
            while (std::getline(stream, item, ';'))
                if (item.length() > 0) {
                    ++matches;
                    out += ";" + item;
                }
            for (int i = matches; i < 3; ++i)
                out += ";0";
            return out;
        }

        std::string parseVector(const std::string& str)
        {
            static std::string componentColours[] = { ";200;0;0m", ";0;200;0m", ";0;0;200m", ";200;200;0m" };
            std::stringstream base(str);
            std::stringstream stream(str);
            std::string item;
            std::string out = "{";
            int matches = 0;
            int maxMatches = 0;
            while (std::getline(base, item, ','))
                ++maxMatches;

            while (std::getline(stream, item, ',')) {
                out += "\033[38;2" + componentColours[matches % 4] + item + "\033[0m" + (matches != maxMatches - 1 ? "," : "");
                ++matches;
            }

            out += "}";
            return out;
        }

        void ParseParams()
        {
            std::string parsed = _format;
            auto length = parsed.length();
            size_t bodyArgs = 0;
            const auto argCount = _args.size();

            bool paramSequence = false;
            uint seqStartIndex;

            for (uint i = 0; i < length; ++i) {
                if (parsed[i] == '{') {
                    paramSequence = true;
                    seqStartIndex = i;
                    continue;
                }
                if (paramSequence && parsed[i] == 'v') {
                    paramSequence = false;
                    const auto vector = _args.at(bodyArgs);
                    auto span = parseVector(vector.substr(1, vector.length() - 2));
                    parsed.replace(seqStartIndex, 3, span);
                    ++bodyArgs;
                    continue;
                }

                if (parsed[i] == '}' && paramSequence) {
                    paramSequence = false;
                    const auto n = i - seqStartIndex + 1;
                    if (n > 2) {
                        // Hey {} dwad => 4, 5. 5-4+1=2
                        // Hey {;255} dwadw => 4, 9. 9-4+1=6.

                        const auto colourSequence = parsed.substr(seqStartIndex + 1, i - seqStartIndex - 1);
                        auto span = parseColourSequence(colourSequence);

                        span += "m" + _args.at(bodyArgs) + "\033[0m";
                        parsed.replace(seqStartIndex, n, span);
                    } else
                        parsed.replace(seqStartIndex, i - seqStartIndex + 1, _args.at(bodyArgs));

                    assert(bodyArgs <= argCount && "Error: format argument count cannot exceed argument count.");
                    ++bodyArgs;
                    length = parsed.length();
                }
            }
            assert(argCount == bodyArgs && "Error: argument count cannot exceed format argument count.");
            _text = parsed;
        }

    public:
        VariadicArgParser() = delete;

        explicit VariadicArgParser(const std::string& format, const Param&... args)
            : _format(format)
        {
            SetArgs(args...);
            ParseParams();
        }

        operator std::string() const { return _text; }
    };

}

template <typename... Param>
std::string getFormatted(const std::string& format, const Param&... arguments)
{
    const __alx::VariadicArgParser<Param...> parser { format, arguments... };
    return parser;
}

template <typename... Param>
void println(const std::string& format, const Param&... arguments)
{
    const auto text = getFormatted(format, arguments...);
    std::cout << text << '\n';
}

template <typename...>
void println()
{
    std::cout << "\n";
}

template <typename... Param>
void println(Colour colour, const std::string& format, const Param&... arguments)
{
    const auto text = getFormatted(format, arguments...);
    println("\033[38;2;{};{};{}m{}\033[0m", colour.r, colour.g, colour.b, text);
}

template <typename... Param>
void print(const std::string& format, const Param&... arguments)
{
    const auto text = getFormatted(format, arguments...);
    std::cout << text;
}

template <typename... Param>
void print(Colour colour, const std::string& format, const Param&... arguments)
{
    const auto text = getFormatted(format, arguments...);
    print("\033[38;2;{};{};{}m{}\033[0m", colour.r, colour.g, colour.b, text);
}
}
