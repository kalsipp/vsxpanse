#include <random>
#include "helpers.hpp"
#include "logging.hpp"
#include "vector2dint.hpp"
#include <random>
#ifdef __GNUC__
void sig_error_handler(int sig) {
	void *array[10];
	size_t size;
	size = backtrace(array, 10);
	std::string meaning;
	switch (sig) {
	case (SIGABRT):
		meaning = "SIGABRT";
		break;
	case (SIGTERM):
		meaning = "SIGTERM";
		break;
	case (SIGSEGV):
		meaning = "SIGSEGV";
		break;
	case (SIGILL):
		meaning = "SIGILL";
		break;
	case (SIGFPE):
		meaning = "SIGFPE";
		break;
	case (SIGINT):
		meaning = "SIGINT";
		break;
	default:
		meaning = "UNKNOWN";
	}
	std::cerr << "Error: signal: " << meaning << std::endl;
	backtrace_symbols_fd(array, size, STDERR_FILENO);
	exit(1);
}
#endif


#ifdef DEBUG
void ASSERT(bool condition, const std::string & message)
{
	if (!condition)
	{
		Logging::log(std::stringstream() << std::endl << "Assertion: " << condition << std::endl <<
			"Message: " << message << std::endl << std::endl, Logging::ERROR);
		Logging::teardown();
		HELPERS_CALL_SIG_HANDLER;
		std::terminate();

	}
}
#endif

namespace helpers {
	static std::random_device random_int_rd;
	static std::mt19937 random_int_rng(random_int_rd());
	
	
	int random_int(int min, int max) {
		std::uniform_int_distribution<int> uni(min, max);
		return uni(random_int_rng);
	}
	
	int round_to_int(float v)
	{
		return int(v + 0.5);
	}

	
	int round_to_int(double v)
	{
		return int(v + 0.5);
	}

	
	double get_squared_distance_between_positions(const Vector2DInt & a, const Vector2DInt & b)
	{
		const double xdiff = b.x - a.x;
		const double ydiff = b.y - a.y;
		return xdiff * xdiff + ydiff * ydiff;
	}

	
	std::string get_filename_from_path(const std::string & path) {
		std::size_t found = path.find_last_of("/\\");
		if (found == std::string::npos) {
			return "";
		} else {
			return path.substr(found + 1);
		}
	}

}