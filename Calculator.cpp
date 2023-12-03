#include "Calculator.h"
void Calculator::math(int work_sock, std::string &err_way)
{
    uint32_t amount;
    uint32_t vector_size;
    uint32_t vect;
    recv(work_sock, &amount, sizeof(amount), 0);
    //цикл векторов
    for(uint32_t j=0; j<amount; j++) {
        recv(work_sock, &vector_size, sizeof(vector_size), 0);//прием длинны для первого вектора
        uint32_t sum = 0;
//цикл значений
        for(uint32_t i=0; i<vector_size; i++) {
            recv(work_sock, &vect, sizeof(vect), 0);
            if (sum > std::numeric_limits<uint32_t>::max() - vect) {
                sum = std::numeric_limits<uint32_t>::max();
                break;
            }
            sum = sum+vect;
        }
        uint32_t mfc;
        mfc = sum/vector_size;
        send(work_sock, &mfc, sizeof(mfc), 0);
    }
    LogWriter::log(err_way, "Результат вычислений получен и отправлен клиенту");
    std::cout << "Program finish!" <<std::endl;
    close(work_sock);
}
