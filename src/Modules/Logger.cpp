// ==========================================================================
// Logger class
//
// FRC 4143 "MARS WARS"
// ==========================================================================
// 2015-02-01 JKSalmon - Initial development
// ==========================================================================
#include "Logger.h"
#include <WPILib.h>
#include <time.h>

std::mutex Logger::m_mutex;
int Logger::m_counter = 0;

Logger::Logger() {}

void Logger::Log(std::string msg) {
  // DriverStation::ReportError(msg.append("\r\n"));
  std::lock_guard<std::mutex> lck(m_mutex);

  time_t rawtime;
  time(&rawtime);

  tm *timeinfo = localtime(&rawtime);

  char buffer[64];
  strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);

  int counter = ++m_counter;
  char buffer2[64];
  sprintf(buffer2, "%s %i ", buffer, counter);

  std::cout << buffer2 << msg << std::endl;
  std::cout.flush();
}
