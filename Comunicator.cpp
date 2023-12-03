#include "Comunicator.h"
#include "client_base.h"
#include "mdfile.h"

std::string MD(std::string sah)
{
    Weak::MD5 hash;
    std::string digest;
    StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));  // строка-приемник
    return digest;
}
int Comunicator::self_addr(int port, std::string &err_way)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);//создается сокет для сервера
    std::unique_ptr<sockaddr_in> self_addr(new sockaddr_in);
    self_addr->sin_family = AF_INET;
    self_addr->sin_port = htons(port);
    self_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    LogWriter::log(err_way, "Ожидание подключения клиента");
    std::cout << "Wait for connect client...\n";
    int b = bind(s,reinterpret_cast <const sockaddr* > (self_addr.get()),sizeof(sockaddr_in));//закрепляет сокет
    if(b == -1) {
        std::cout << "Binding error\n";
        return 1;
    }
    listen(s, SOMAXCONN);//ловит запросы к сокету
    return s;
}

int Comunicator::client_addr(int s, std::string &err_way)
{
    std::unique_ptr<sockaddr_in> client_addr(new sockaddr_in);
    socklen_t len = sizeof (sockaddr_in);
    int work_sock = accept(s, reinterpret_cast <sockaddr* > (client_addr.get()), &len);//создание сокета для клиента
    if(work_sock == -1) {
        std::cout << "Ошибка подключения";
        LogWriter::log(err_way, "Ошибка подключения");
        return 1;
    } else {
        //Успешное подключение к серверу
        std::cout << "Successfull client connection!\n";
        LogWriter::log(err_way, "Подключение прошло успешно");
        return work_sock;
    }
}
int Comunicator::autorized(int work_sock,
                           std::string file_name, 
                           std::map <std::string,std::string> &all_names, 
                           std::string &err_way) //аутентификация
{

    std::string ok = "OK";
    std::random_device rnd;
    std::mt19937_64 rnd_generator(rnd());
    uint64_t rnd_number = rnd_generator();
    std::string salt;
    StringSource((const byte*)&rnd_number,8,true,new HexEncoder(new StringSink(salt)));
    std::string err = "ERR";
    std::unique_ptr<char[]> msg(new char[256]);

    //Авторизация
    int size_m = recv(work_sock, msg.get(), 256, 0);
    std::string login(msg.get(), size_m);
    try
    {
        ClientBase::find(login, all_names);
        LogWriter::log(err_way, "Пользователь найден");
    }
    catch(const std::exception& e)
    {
        LogWriter::log(err_way, e.what());
        exit(1);
    }
    
    std::string password = ClientBase::find(login, all_names);
    //СВЕРКА ЛОГИНОВ
    

    msg = std::unique_ptr<char[]> (new char[256]);
    //соль отправленная клиенту
    send(work_sock, salt.c_str(), salt.length(), 0);
    size_m = recv(work_sock, msg.get(), 256, 0);
    std::string sah = salt + password;
    std::string digest;
    digest = MD(sah);
    std::string new_msg(msg.get(),size_m);
    //СВЕРКА ПАРОЛЕЙ
    if(digest != new_msg) {
        send(work_sock, err.c_str(), err.length(), 0);
        close(work_sock);
        return 1;
    } else {
        send(work_sock, ok.c_str(), ok.length(), 0);
    }

    return 1;
}
