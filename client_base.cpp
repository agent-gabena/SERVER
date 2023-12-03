#include "client_base.h"
std::map <std::string,std::string> ClientBase::read(std::string way,std::string err_way)
{
    std::map <std::string,std::string> all;
    std::string line;
    std::ifstream file(way);
    if (file.peek() == EOF)
    {
        throw ServerError("База данных пуста");
    }
        while(std::getline(file,line)) {
            auto index = line.find_first_of(':');
            std::string first = line.substr(0,index);
            std::string second = line.substr(index+1,line.size());
            all.insert({first,second});
        }
            file.close();
    return all;
}
std::string ClientBase::find(std::string &name, std::map< std::string, std::string > &all)
{
    auto res = all.find(name);
    if(res != all.end()){
        return res->second;
    }
    throw ServerError("В базе данных отсутствует пользователь");
}
