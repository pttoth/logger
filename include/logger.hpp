/*
 * -------------------------------------------------------------------------
 * FILE:    logger.hpp
 * AUTHOR:  Peter Toth - 2017.07.31.
 * E-MAIL:  peter.t.toth92@gmail.com
 * PURPOSE: Lightweight logger writing simultaneously to
 *            std::cout and to a logfile
 * -------------------------------------------------------------------------
 */

#define DEFINE_STREAM_OUT_OPERATOR(STREAM_OUT_VAR_1)	\
    output_channel& operator<<(STREAM_OUT_VAR_1 data){	\
        std::cout << data; \
        WriteToFile<STREAM_OUT_VAR_1>(data); \
        return *this; \
    }

#define DEFINE_STREAM_OUT_FUNC_OPERATOR(STREAM_OUT_VAR_1, FUNC_PARAMS)	\
    output_channel& operator<<(STREAM_OUT_VAR_1 (*data) FUNC_PARAMS){	\
        std::cout << data; \
        WriteToFile<STREAM_OUT_VAR_1 FUNC_PARAMS>(data); \
        return *this; \
    }

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>

namespace logger{
    class output_channel{
        bool _enabled;
        std::string _file;

        template<typename T>
        void WriteToFile(T data) const{
            if( (_enabled) && (_file != "") ){
                std::fstream fs;
                fs.open( _file.c_str(), std::fstream::out
                                        | std::fstream::app);
                fs << data;
                fs.close();
            }
        }

    public:
        output_channel();
        ~output_channel();
        output_channel(const output_channel& other)=delete;
        output_channel(output_channel&& source)=delete;

        output_channel operator=(const output_channel& other)=delete;
        output_channel operator=(output_channel&& source)=delete;

        void setEnabled(bool val);
        void setFile(const char *filename);
        void setFile(const std::string &filename);

        DEFINE_STREAM_OUT_OPERATOR(const bool)
        DEFINE_STREAM_OUT_OPERATOR(const short)
        DEFINE_STREAM_OUT_OPERATOR(const unsigned short)
        DEFINE_STREAM_OUT_OPERATOR(const int)
        DEFINE_STREAM_OUT_OPERATOR(const unsigned int)
        DEFINE_STREAM_OUT_OPERATOR(const long)
        DEFINE_STREAM_OUT_OPERATOR(const unsigned long)
        DEFINE_STREAM_OUT_OPERATOR(const float)
        DEFINE_STREAM_OUT_OPERATOR(const double)
        DEFINE_STREAM_OUT_OPERATOR(const long double)
        DEFINE_STREAM_OUT_OPERATOR(const void*)
        DEFINE_STREAM_OUT_OPERATOR(const std::streambuf*)

        DEFINE_STREAM_OUT_OPERATOR(const char*)
        DEFINE_STREAM_OUT_OPERATOR(const std::string&)

        DEFINE_STREAM_OUT_FUNC_OPERATOR(std::ostream&, (std::ostream&))
        DEFINE_STREAM_OUT_FUNC_OPERATOR(std::ios&, (std::ios&))
        DEFINE_STREAM_OUT_FUNC_OPERATOR(std::ios_base&, (std::ios_base&))

    };

    //--------------
    //   global
    //--------------

    extern output_channel log;
    extern output_channel debug;
    extern output_channel error;

    extern void init();
    extern void loadSettings();
}

#endif
