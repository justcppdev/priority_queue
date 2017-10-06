#include <iostream>
#include <vector>

#include "priority_queue.hpp"

auto calculate_iteration_count( priority_queue_t<size_t> & fruit_backet, size_t fruits_size_limit) -> size_t
{
    size_t attempt_count = 0;
    while( !fruit_backet.empty() ) {
        size_t size_of_selected_fruits = 0;
        std::vector<size_t> selected_fruits;
        while( !fruit_backet.empty() && size_of_selected_fruits + *fruit_backet.top() <= fruits_size_limit ) {
            auto fruit_size = *fruit_backet.pop();
            selected_fruits.push_back( fruit_size );
            size_of_selected_fruits += fruit_size;
        }

        for( auto fruit_size : selected_fruits ) {
            if( fruit_size != 1 ) {
                fruit_size /= 2;
                fruit_backet.push( fruit_size );
            }
        }
        
        ++attempt_count;
    }

    return attempt_count;
}

int main()
{
    size_t fruits_count;
    size_t fruits_size_limit;

    std::cin >> fruits_count;
    if( std::cin ) {
        std::vector<size_t> fruits;
        fruits.reserve( fruits_count );
        for(size_t index = 0; index < fruits_count; ++index ) {
            size_t fruit_size;
            std::cin >> fruit_size;
            if( std::cin ) {
                fruits.push_back( fruit_size );
            }
            else {
                return EXIT_FAILURE;
            }
        }
        priority_queue_t<size_t> fruit_backet( fruits_count );
        fruit_backet.fill( fruits.cbegin(), fruits.cend() );
        std::cin >> fruits_size_limit;
        if( std::cin ) {
            std::cout << calculate_iteration_count( fruit_backet, fruits_size_limit );
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
