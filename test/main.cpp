#include "logger.hpp"

int main()
{
    logger::init();
    std::string str("test string\n");
    logger::log << str;
    logger::log << "logmsg" << "\n";
    logger::debug << "debugmsg" << "\n";
    logger::error << "errormsg" << "\n";
    logger::log << "concatenated" << " output char" << " sequence" << std::endl;
    logger::log << "success\n";
    return 0;
}

