#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <signal.h>
#ifdef __GNUC__
#include <execinfo.h>
#include <unistd.h>
void sig_error_handler(int sig);
#define CALL_SIG_HANDLER sig_error_handler(SIGTERM)
#else
typedef unsigned int uint;
#define HELPERS_CALL_SIG_HANDLER do {} while (false)  /* Do fuckall */
#endif


/*-------------------------------------------------------
Terminates if condition is false. Turn off with DEBUG flag.
Outside namespace for convenience.
---------------------------------------------------------
@param condition - asserts if false
@param message - Gets logged
---------------------------------------------------------*/
void ASSERT(bool condition, const std::string & message);

namespace helpers {
	/*-------------------------------------------------------
	Get random int.
	---------------------------------------------------------
	@param min, inclusive
	@param max, inclusive
	@return result
	---------------------------------------------------------*/
	int random_int(int min, int max);

	/*-------------------------------------------------------
	Extracts the filename from path.
	C:\path\to\file.exe -> file.exe
	---------------------------------------------------------
	@param path
	@return filename
	---------------------------------------------------------*/
	std::string get_filename_from_path(const std::string & path);

	/*-------------------------------------------------------
	Parameters
	---------------------------------------------------------*/
	const double MATH_PI = 3.14159265358979323846264338327950288;
	const double TO_RAD = MATH_PI / 180;
}