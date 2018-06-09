#include <random>
#include "helpers.hpp"

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
namespace helpers {

uint random_int(int min, int max) {
	// std::mt19937 rng;
	// rng.seed(std::random_device()());
	// rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
	// std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return rand()%min +max;
	// return 5;
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