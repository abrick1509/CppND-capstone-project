#ifndef LOGGER_H
#define LOGGER_H

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <mutex>
#include <sstream>
#include <string>
#include <type_traits>

class Logger {
public:
  Logger(const std::string &filename) {
    const auto now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::stringstream unique_filename;
    unique_filename << now << "_" << filename;
    myfile.open(unique_filename.str());
  }
  Logger(const Logger &rhs) = delete;            // Logger can't be copied
  Logger &operator=(const Logger &rhs) = delete; // Logger can't be copied
  Logger(Logger &&rhs) { myfile = std::move(rhs.myfile); }
  Logger &operator=(Logger &&rhs) {
    this->myfile = std::move(rhs.myfile);
    return *this;
  }
  ~Logger() { myfile.close(); }
  void LogMessage(const std::string &message) {
    std::lock_guard<std::mutex> lock(mutex);
    const std::time_t now =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    myfile << "[" << std::ctime(&now) << "]:" << message << "\n";
  }

private:
  std::ofstream myfile;
  std::mutex mutex;
};

#endif