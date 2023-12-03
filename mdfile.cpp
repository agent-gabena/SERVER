#include "mdfile.h"
void LogWriter::log(std::string &way, std::string msg ){
    std::ofstream log_file(way, std::ios_base::app);
    if (log_file.fail()){
        std::cerr << "Ошибка записи в файл log"<<std::endl;
        exit(EXIT_FAILURE);
    }
    std::time_t cur_time = std::time(nullptr);
    char buf[sizeof("dd/mmm/yyyy:HH:MM:SS")];
    std::strftime(buf, sizeof(buf), "%d/%b/%Y:%H:%M:%S", std::localtime(&cur_time));
    log_file << std::string(buf, sizeof(buf)) + '\t';
    log_file << msg << std::endl << std::flush;
    log_file.close();
}