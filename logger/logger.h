#pragma once

#include <cstdio>
#include <string>
#include <cstring>
#include <filesystem>
#include <string_view>
#include <iostream>
#include <format>

#define PREFIX_LEN 10
#define FILENAME_LEN 40

#define FILENAME std::filesystem::path(__FILE__).filename().string()


/// @brief Enumerated type defining possible log text's color
enum TextColor 
{
    RED,
    WHITE,
    YELLOW,
    TEXT_COLOR_COUNT
};

/// @brief Simple logger function for debug purposes
/// @tparam ...Args     template for variadic arguments
/// @param prefix       prefix of log to be used, ex. DEBUG, ERROR
/// @param msg          message to be logged to console, should follow syntax "{} msg {}"
/// @param color        color of the log message
/// @param filename     name of the filed that log was print in
/// @param fileline     line of the file in which log has been printed
/// @param ...args      variadic arguments to be placed in {} in the msg
template<typename ...Args>
void _log(std::string_view prefix, std::string_view msg, TextColor color, std::string_view filename, int fileline, Args... args) 
{
    static const char* textColorTable[TEXT_COLOR_COUNT] = {
        "\033[31m", // color code for red
        "\033[0m",  // color code for white
        "\033[33m"  // color code for yellow
    };

    std::string prefix_spacing = std::string(PREFIX_LEN - prefix.size(), ' ');

    std::string filename_part = std::format("{}:{}", filename, fileline);
    std::string filename_spacing = std::string(FILENAME_LEN - filename_part.size(), ' ');
    filename_part += filename_spacing;

    std::string formatted_msg = std::vformat(msg, std::make_format_args(args...));
    std::string output = std::format("{} [{}]{}{} {} \033[0m", 
        textColorTable[color], prefix, prefix_spacing.c_str(), filename_part.c_str(), formatted_msg);


    std::cout << output.c_str() << "\n";
};

#define LOG_DBG(msg, ...) _log("DEBUG", msg, TextColor::WHITE, FILENAME, __LINE__, ##__VA_ARGS__);
#define LOG_ERR(msg, ...) _log("ERROR", msg, TextColor::RED, FILENAME, __LINE__, ##__VA_ARGS__);
#define LOG_WRN(msg, ...) _log("WARN",  msg, TextColor::YELLOW, FILENAME, __LINE__, ##__VA_ARGS__);

// template<typename ...Args>
// void _log(const char* prefix, const char* msg, TextColor color, std::string_view filename_, int fileline, Args... args) 
// {
//     static const char* textColorTable[TEXT_COLOR_COUNT] = 
//     {
//         "\033[31m", // color code for red
//         "\033[0m",  // color code for white
//         "\033[33m"  // color code for yellow
//     };

//     std::string prefix_spacing = std::string(PREFIX_LEN - strlen(prefix), ' ');

//     std::string filename = std::string(filename_);
//     std::string filename_part = std::string(filename) + ":" + std::to_string(fileline);
//     std::string filename_spacing = std::string(FILENAME_LEN - filename_part.size(), ' ');
//     filename_part += filename_spacing;

//     char formatBuffer[8192] = {};
//     sprintf(formatBuffer, "%s [%s]%s%s %s \033[0m", textColorTable[color], prefix, prefix_spacing.c_str(), filename_part.c_str(), msg);

//     char textBuffer[8192] = {};
//     sprintf(textBuffer, formatBuffer, args...);

//     puts(textBuffer);
// };

// #define LOG_DBG(msg, ...) _log("DEBUG", msg, TextColor::WHITE, FILENAME, __LINE__, ##__VA_ARGS__);
// #define LOG_ERR(msg, ...) _log("ERROR", msg, TextColor::RED, FILENAME, __LINE__, ##__VA_ARGS__);
// #define LOG_WRN(msg, ...) _log("WARN",  msg, TextColor::YELLOW, FILENAME, __LINE__, ##__VA_ARGS__);