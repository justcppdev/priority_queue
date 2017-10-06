#ifndef QUEUE_PRIORITY_HPP 
#define QUEUE_PRIORITY_HPP

#include <memory>
#include <stdexcept>
#include <vector>
#include <algorithm>

template <typename T, typename Compare = std::less<T>>
class priority_queue_t
{
public:
    explicit priority_queue_t( size_t size = 0 );
    
    auto elements() const -> std::vector<T>;
    
    template <typename InputIterator>
    void fill( InputIterator begin, InputIterator end ) /*strong*/;
    
    void push( T const & value ) /*strong*/;
    
    auto pop() -> std::shared_ptr<T>;
    
    bool on_top( T const & value ) const;
    
    auto top() -> std::shared_ptr<T>;
    
    bool empty() const noexcept;
private:
    std::vector<std::shared_ptr<T>> elements_;
    
    auto sift_up( size_t index ) /*noexcept(<))*/ -> void;
    
    auto sift_down( size_t index ) -> void;
    
    auto build_heap() -> void;
};

template <typename T, typename Compare>
void priority_queue_t<T, Compare>::sift_up( size_t index ) /*noexcept(<))*/
{
    Compare comparator;
    while( index != 0 ) {
        auto parent = ( index - 1 ) / 2;
        if( comparator( *elements_[ index ], *elements_[ parent ] ) ) {
            elements_[ index ].swap( elements_[ parent ] );
            index = parent;
        }
        else {
            break;
        }
    }
}

template <typename T, typename Compare>
void priority_queue_t<T, Compare>::sift_down( size_t index )
{
    auto left = index * 2 + 1;
    auto right = index * 2 + 2;
    
    auto largest = index;
    Compare comparator;
    if( left < elements_.size() && comparator( *elements_[ left ], *elements_[ largest ] ) ) {
        largest = left;
    }
    if( right < elements_.size() && comparator( *elements_[ right ], *elements_[ largest ] ) ) {
        largest = right;
    }
    
    if( largest != index ) {
        elements_[ index ].swap( elements_[ largest ] );
        sift_down( largest );
    }
}

template <typename T, typename Compare>
auto priority_queue_t<T, Compare>::build_heap() -> void
{
    for( size_t index = elements_.size() / 2; index != 0; ) {
        --index;
        sift_down( index );
    }
}

template <typename T, typename Compare>
priority_queue_t<T, Compare>::priority_queue_t( size_t size ) : elements_{}
{
    elements_.reserve( size );
}

template <typename T, typename Compare>
auto priority_queue_t<T, Compare>::elements() const -> std::vector<T>
{
    std::vector<T> result;
    result.reserve( elements_.size() );
    
    std::transform( elements_.cbegin(), elements_.cend(), std::back_inserter( result ), []( std::shared_ptr<T> element ) {
        return *element;
    } );
    
    return result;
}

template <typename T, typename Compare>
template <typename InputIterator>
void priority_queue_t<T, Compare>::fill( InputIterator begin, InputIterator end ) /*strong*/
{
    std::vector<std::shared_ptr<T>> elements;
    std::transform( begin, end, back_inserter( elements ), []( auto && value ) {
        return std::make_shared<T>( value );
    } );
    
    elements_.swap( elements );
    
    build_heap();
}

template <typename T, typename Compare>
auto priority_queue_t<T, Compare>::push( T const & value ) /*strong*/ -> void
{
    elements_.push_back( std::make_shared<T>( value ) );
    sift_up( elements_.size() - 1 );
}

template <typename T, typename Compare>
auto priority_queue_t<T, Compare>::pop() -> std::shared_ptr<T>
{
    if( elements_.size() == 0 ) {
        throw std::logic_error{ "is empty" };
    }
    
    std::shared_ptr<T> result;
    elements_.front().swap( elements_.back() );
    result.swap( elements_.back() );
    elements_.pop_back();
    
    sift_down( 0 );
    
    return result;
}

template <typename T, typename Compare>
bool priority_queue_t<T, Compare>::on_top( T const & value ) const 
{
    if( elements_.size() == 0 ) {
        throw std::logic_error{ "is empty" };
    }
    
    return *elements_[ 0 ] == value;
}

template <typename T, typename Compare>
auto priority_queue_t<T, Compare>::top() -> std::shared_ptr<T>
{
    if( elements_.size() == 0 ) {
        throw std::logic_error{ "is empty " };
    }
    
    return elements_[ 0 ];
}

template <typename T, typename Compare>
bool priority_queue_t<T, Compare>::empty() const noexcept
{
    return elements_.size() == 0;
}

#endif
