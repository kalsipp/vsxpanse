#pragma once

#include <sstream>
#include <iostream>
#include <fstream>
#include <queue>
#include <cstdint>
#include <chrono>
#include <vector>
#ifdef __GNUC__
#include <ctime>
#else
#include <time.h> 
#endif
#ifdef _MSC_VER
#undef ERROR
#endif

//#define LOGGING_TERMINAL_PRINT

class LoggingFile {
public:
	LoggingFile(const std::string filename, uint8_t verbosity):
		m_filename(filename),
		m_verbosity(verbosity) {
		m_file.open(m_filename);
#ifdef __GNUC__
		std::time_t result = std::time(nullptr);
		m_file << std::ctime(&result) << '\n';
#else
		char buf[26];

		time_t result = time(nullptr);
		m_file << ctime_s(buf, 26, &result) << '\n';
#endif
		m_file << "Time \t\t Verbosity \t\t Message\n";
		m_file.close();
	}
	void write(const std::string & text) {
#if 0
		m_file.open(m_filename, std::ios::app);
		m_file << text << std::endl;
		m_file.close();
#endif
	}
	~LoggingFile() {}
	std::string m_filename;
	uint8_t m_verbosity;
	std::ofstream m_file;
};

class LogEntry {
public:
	LogEntry(const std::string & text, int64_t timestamp, uint8_t level):
		m_text(text), m_timestamp(timestamp), m_level(level) {}
	std::string m_text;
	int64_t m_timestamp;
	uint8_t m_level;
};

class Logging {
public:
	static void add_file(const std::string & name, uint8_t verbosity);
	static void log(const std::basic_ostream<char> &, uint8_t level = Logging::INFO);
	static void log(const std::string &, uint8_t level = Logging::INFO);
	static void teardown();
	static void initialize();
	static const uint8_t TRACE;
	static const uint8_t INFO;
	static const uint8_t WARNING;
	static const uint8_t ERROR;
private:
	Logging();
	~Logging() {}
	static std::string fancify(const LogEntry &);
	static void output_to_terminal(const LogEntry &);
	static void write_loop();
	static bool m_initialized;
	static bool m_running;
	static std::vector<LoggingFile*> m_loggingfiles;
	static std::queue<LogEntry> m_write_queue;
	static const std::string RED_TEXT;
	static const std::string YELLOW_TEXT;
	static const std::string GREY_TEXT;
	static const std::string RESET_TEXT;
	static std::chrono::high_resolution_clock::time_point m_start_time;
};