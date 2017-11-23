#include "date_time.hpp"
#include "constants.hpp"
#include "logger.hpp"
#include <iostream>
#include <fstream>
#include <string>

bool mstd::logger::_run = false;
std::string mstd::logger::file = "../debug/log.txt";

void mstd::logger::debug(const std::string &context, const std::string &message, int type) {
    if (!_run) {
        new_run();
        _run = true;
    }
    std::string outp_str = mstd::date_time::now()() + " - [DEBUG] \t-- "
                            + context + " : " + message;
    if (type == STDOUT || type == BOTH) {
        std::cout << outp_str << std::endl;
    }

    if (type == LOGFILE || type == BOTH) {
        std::ofstream outp(file.c_str(), std::ios::app);
        outp << outp_str << std::endl;
        outp.flush();
        outp.close();
    }
}

void mstd::logger::warn(const std::string &context, const std::string &message, int type) {
    if (!_run) {
        new_run();
        _run = true;
    }
    mstd::date_time now;
    if (type == STDOUT || type == BOTH) {
        std::cout << "\033[1;33m " << now()
                    << " - [WARNING] \t-- " << context << " : " << message << "\033[0m" << std::endl;
    }

    if (type == LOGFILE || type == BOTH) {
        std::ofstream outp(file.c_str(), std::ios::app);
        outp << now.to_string()
                << " - [WARNING] \t-- " << context << " : " << message << std::endl;
        outp.flush();
        outp.close();
    }
}

void mstd::logger::success(const std::string &context, const std::string &message, int type) {
    if (!_run) {
        new_run();
        _run = true;
    }
    mstd::date_time now;
    if (type == STDOUT || type == BOTH) {
        std::cout << "\033[1;32m " << now()
                    << " - [SUCCESS] \t-- " << context << " : " << message << "\033[0m" << std::endl;
    }

    if (type == LOGFILE || type == BOTH) {
        std::ofstream outp(file.c_str(), std::ios::app);
        outp << now()
                << " - [SUCCESS] \t-- " << context << " : " << message << std::endl;
        outp.flush();
        outp.close();
    }
}


void mstd::logger::error(const std::string &context, const std::string &message, int type, bool stderr) {
    if (!_run) {
        new_run();
        _run = true;
    }
    mstd::date_time now;
    if (type == STDOUT || type == BOTH) {
        std::ostream *outp;
        if (stderr) {
            outp = &std::cerr;
        } else {
            outp = &std::cout;
        }
        *outp << "\033[1;31m " << now() << " - [ERROR] \t-- " << context << " : "
                    << message << "\033[0m" << std::endl;
    }

    if (type == LOGFILE || type == BOTH) {
        std::ofstream outp(file.c_str(), std::ios::app);
        outp << now() << " - [ERROR] \t-- " << context << " : " << message << std::endl;
        outp.flush();
        outp.close();
    }
}

void mstd::logger::new_run() {
    std::ofstream outp(file.c_str(), std::ios::app);
    // There *must* be a better way to make new runs obvious -_-
    outp << "====================================================================================" << std::endl;
    outp.flush();
    outp.close();
}


