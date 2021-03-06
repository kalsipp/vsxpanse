#include "logging.hpp"
#include "helpers.hpp"
bool Logging::m_initialized = false;
bool Logging::m_running = false;
std::vector<LoggingFile*> Logging::m_loggingfiles;
std::queue<LogEntry> Logging::m_write_queue;

const uint8_t Logging::TRACE = 1;
const uint8_t Logging::INFO = 3;
const uint8_t Logging::WARNING = 5;
const uint8_t Logging::ERROR = 7;
const std::string Logging::RED_TEXT = "\033[0;31m";
const std::string Logging::YELLOW_TEXT = "\033[0;33m";
const std::string Logging::GREY_TEXT = "\033[0;37m";
const std::string Logging::RESET_TEXT = "\033[0m";
std::chrono::high_resolution_clock::time_point Logging::m_start_time;

void Logging::add_file(const std::string & name, uint8_t verbosity) {
#ifdef DEBUG
	LoggingFile* newlog = new LoggingFile(name, verbosity);
	m_loggingfiles.push_back(newlog);
#endif
}

void Logging::log(const std::basic_ostream<char> & stream, uint8_t level) {
#ifdef DEBUG
	std::stringstream ss;
	ss << stream.rdbuf();
	Logging::log(ss.str(), level);
#else
	(void)level;
	(void)stream;
#endif
}

void Logging::log(const std::string & text, uint8_t level) {

#ifdef DEBUG
	if (!m_initialized) Logging::initialize();

	int64_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_start_time).count();
	LogEntry entry(text, duration, level);
	std::string out = Logging::fancify(entry);
	for (int i = 0; i < m_loggingfiles.size(); i++)
	{
		if (entry.m_level >= m_loggingfiles[i]->m_verbosity) {
			m_loggingfiles[i]->write(out);
		}
	}
#ifdef LOGGING_TERMINAL_PRINT
	Logging::output_to_terminal(entry);
#endif
#else
	(void)level;
	(void)text;
#endif
}

void Logging::initialize() {
#ifdef DEBUG
	m_initialized = true;
	m_running = true;
	m_start_time = std::chrono::high_resolution_clock::now();
	Logging::add_file("everything.log", Logging::TRACE);
#else
#endif
}

void Logging::teardown() {
#ifdef DEBUG
	m_running = false;
	for (auto it = m_loggingfiles.begin(); it != m_loggingfiles.end(); ++it) {
		delete *it;
	}
	m_loggingfiles.clear();
#else
#endif
}

std::string Logging::fancify(const LogEntry & entry) {
#ifdef DEBUG
	std::string output_string = "";
	output_string += std::to_string(int(entry.m_timestamp)) + "\t\t";
	switch (entry.m_level) {
	case TRACE:
		output_string += "TRACE";
		break;
	case INFO:
		output_string += "INFO";
		break;
	case WARNING:
		output_string += "WARNING";
		break;
	case ERROR:
		output_string += "ERROR";
		break;
	}
	output_string += "\t\t";
	output_string += entry.m_text;
	return output_string;
#endif
}

void Logging::output_to_terminal(const LogEntry & entry) {
#ifdef DEBUG
	switch (entry.m_level) {
	case TRACE:
		break;
	case INFO:
		std::cout << GREY_TEXT << entry.m_text << RESET_TEXT << std::endl;
		break;
	case WARNING:
		std::cout << YELLOW_TEXT << entry.m_text << RESET_TEXT << std::endl;
		break;
	case ERROR:
		std::cerr << RED_TEXT << entry.m_text << RESET_TEXT << std::endl;
		break;
	}
#endif
}

void Logging::write_loop() {
#ifdef DEBUG
	while (m_running || !m_write_queue.empty()) {
		if (!m_write_queue.empty()) {
			LogEntry entry = m_write_queue.front();
			m_write_queue.pop();
			entry.m_text = Logging::fancify(entry);
			for (auto it = m_loggingfiles.begin(); it != m_loggingfiles.end(); ++it) {
				if (entry.m_level >= (*it)->m_verbosity) {
					(*it)->write(entry.m_text);
				}
			}
			Logging::output_to_terminal(entry);
		}

	}
#endif
}

