#include <iostream>

#include "priority_queue.hpp"

class request
{
public:
    using size_type = std::size_t;
    request( size_type start, size_type duration ) : 
        start_{ start }, 
        finish_{ start + duration } 
    {
    }

    auto start() const -> size_type
    {
        return start_;
    }

    auto finish() const -> size_type
    {
        return finish_;
    }
private:
    size_type start_;
    size_type finish_;
};

int main()
{
    /*
     В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое может быть удовлетворено. Число заявок ≤ 100000.
     
     Формат ввода
     
     Вход содержит только пары целых чисел — начала и продолжительности заявок.
     
     Формат вывода
     
     Выход должен содержать натуральное число — максимальное число заявок.
     
    1 1
    2 3
    7 3
    2 1
    6 1
    4 3
    3 3
    3 2
    1 1
    4 1
     
     5
    */
    
    auto comparator = []( request const & lhs, request const & rhs ) {
        return rhs.finish() < lhs.finish();
    };
    priority_queue_t<request, decltype(comparator)> queue( 0, comparator );
    
    for( size_t start, duration; std::cin >> start && std::cin >> duration; ) {
        queue.push( {start, duration} );
    }
    
    unsigned int max_request_count = 0;
    request::size_type finish = 0;
    while( !queue.empty() ) {
        auto request = queue.top();
        queue.pop();
        
        if( request->start() >= finish ) {
            ++max_request_count;
            finish = request->finish();
        }
    }
    
    std::cout << max_request_count << std::endl;
    
    return 0;
}
