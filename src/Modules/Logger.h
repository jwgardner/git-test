// ==========================================================================
// Logger class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#ifndef LOGGER_H
#define LOGGER_H

#include <mutex>
#include <string>

class Logger {
public:
  Logger();

  static void Log(std::string msg);

private:
  static std::mutex m_mutex;
  static int m_counter;
};

#define LOG(msg) Logger::Log(msg);

#endif
