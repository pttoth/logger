#include "logger.hpp"

#include <chrono>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include <cstring>

logger::output_channel logger::log;
logger::output_channel logger::debug;
logger::output_channel logger::error;

void logger::init(){
        std::time_t now_c = std::chrono::system_clock::to_time_t(
                                    std::chrono::system_clock::now() );
        std::stringstream ss;
        ss << std::put_time(std::localtime(&now_c), "%F %T");
        std::string time = ss.str();

        std::string filename(time);
        std::replace( filename.begin(), filename.end(), ':', '_');
        filename.append(".log");

        log.setFile(filename);
        debug.setFile(filename);
        error.setFile(filename);
        logger::loadSettings();
}

//implement fetch of settings from file here
void logger::
        loadSettings(){
}

logger::output_channel::
        output_channel(): _enabled(true),
                          _file(""){
}

logger::output_channel::
        ~output_channel(){
}

void logger::output_channel::
        setEnabled(bool val){
    _enabled = val;
}

//need valid filename check? can be a security risk?
//  shouldn't contain "../"
//  is it enough?
inline bool PathIsValid(const std::string& path){
    if (path.find("../") != std::string::npos){
        return false;
    }
    return true;
}

//directory creation relies on native OS functions
//      other functions need to use void CreateDirectory(std::string& path)
//      which is (will be) a platform independent solution

#ifdef _WIN32
inline void CreateDirectory(const std::string& path){
    throw std::runtime_error("CreateDirectory has not yet been implemented for Windows!\n    File logging won't be available, unless directories already exist!");
}
#elif __linux__
    #include <sys/types.h>
    #include <sys/stat.h>

    inline void CreateDirectory(const std::string& path){
        int result = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                                        //  r/w/search for usr + group
                                        //  r/search for other
        //if not created and doesn't exist already, it's a relevant error
        if( !(0 == result)
            && !((-1 == result) && (EEXIST == errno) )){
            std::stringstream ss;
            ss << "error creating directory: " << path << "\n"
                  << "    result(" << result << "), errno(" << errno << ")";
            throw std::string(ss.str());
        }
    }
#else
    inline void CreateDirectory(const std::string& path){
        throw std::runtime_error("CreateDirectory has not yet been implemented for this platform!\n    File logging won't be available, unless directories already exist!");
    }
#endif

inline void EnsureExistingDirectory(const std::string& path){
    std::string dir;
    dir.reserve(path.size());
    size_t prev = 0;
    size_t curr = 0;
    while( (curr = path.find('/', prev+1)) != std::string::npos ){
        dir += path.substr(prev, curr-prev);
        CreateDirectory(dir);
        prev = curr;
    }
}

void logger::output_channel::
        setFile(const char *filename){
    try{
        char dir[] = "log/";
        std::string path;
        path.reserve( strlen(dir) + strlen(filename) + 1 );
        path += dir;
        //path += '/'; //solves possible missing slash in dir
        path += filename;

        if(PathIsValid(path)){
            std::string str = path;
            EnsureExistingDirectory(str);
            _file = path;
        }else{
            std::string msg("invalid path or filename: ");
            msg += path;
            throw std::domain_error(msg);
        }
    }catch(const std::string& e){
        _file = "";
        std::cout << e << "\n";
    }catch(const std::runtime_error& e){
        _file = "";
        std::cout << e.what() << "\n";
    }
}

void logger::output_channel::
        setFile(const std::string &filename){
    setFile(filename.c_str());
}
