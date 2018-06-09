#pragma once
#include <string>
#include <iostream>
#include <cassert>
//#define _USE_MATH_DEFINES
//#include <math.h>
#ifdef __GNUC__
#include <execinfo.h>
#include <unistd.h>
#else
typedef unsigned int uint;
#endif

#include <signal.h>
#ifdef __GNUC__
void sig_error_handler(int sig);
#endif

#ifndef HELPERS_CALL_SIG_HANDLER
#ifdef __GNUC__
#define CALL_SIG_HANDLER sig_error_handler(SIGTERM)
#else
#define HELPERS_CALL_SIG_HANDLER do {} while (false)
#endif
#endif

#ifdef DEBUG
#include "logging.hpp"
/* Blessed https://stackoverflow.com/questions/3767869/adding-message-to-assert */
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            Logging::log(Logging::ERROR, std::stringstream() <<std::endl <<  "Assertion: " #condition << std::endl << \
            "Failed in file: " << __FILE__  << std::endl << \
            "line: " << __LINE__ << std::endl << \
            "Message: " << message << std::endl << std::endl); \
            Logging::teardown();\
			HELPERS_CALL_SIG_HANDLER;\
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif


namespace helpers {
uint random_int(int min, int max);
std::string get_filename_from_path(const std::string & path);
const double MATH_PI = 3.14159265358979323846264338327950288;
static const double TO_RAD = MATH_PI / 180;

}