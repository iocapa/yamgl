#ifndef _Y_LIST_FORWARD_HPP_
#define _Y_LIST_FORWARD_HPP_

#include "y_platform.hpp"

namespace yamgl {

/// @brief simple node base template linked list (forward only) 
template <typename T>
class y_list_forward {
public:
    Y_DECL_CONSTEXPR y_list_forward();

    class node {
    friend class y_list_forward;        
    public:
        Y_DECL_CONSTEXPR node(T data);
    private:
        T _data;
        node* _next;
    };
    
    class iterator {
    friend class node;
    public:
        Y_DECL_CONSTEXPR iterator(node* data);

        Y_DECL_CONSTEXPR bool is_valid() const;
        Y_DECL_CONSTEXPR iterator& operator++();
        Y_DECL_CONSTEXPR T& operator*() const;
    
    private:
        node* _current;
    };
    
    Y_DECL_CONSTEXPR iterator begin() const;
    Y_DECL_CONSTEXPR void add_node(node& nd);

private:
    node* _head;
};

/// @brief Default constructor
template <typename T>
Y_DECL_CONSTEXPR y_list_forward<T>::y_list_forward() 
    : _head(nullptr) {}

/// @brief Return a iterator relating to the first element in the list
template <typename T>
Y_DECL_CONSTEXPR typename y_list_forward<T>::iterator y_list_forward<T>::begin() const { 
    return y_list_forward<T>::iterator(_head); 
}

/// @brief Adds a node to the list
template <typename T>
Y_DECL_CONSTEXPR void y_list_forward<T>::add_node(y_list_forward<T>::node& nd) {
    if (_head) { nd._next = _head; }
    _head = &nd;
}

/// @brief Default node constructor
template <typename T>
Y_DECL_CONSTEXPR y_list_forward<T>::node::node(T data) 
    : _data(data), _next(nullptr) {}

// @brief Default constructor for iterator
template <typename T>
Y_DECL_CONSTEXPR y_list_forward<T>::iterator::iterator(y_list_forward<T>::node* data)
    : _current(data) {}

/// @brief Return true if current iterator data is valid
template <typename T>
Y_DECL_CONSTEXPR bool y_list_forward<T>::iterator::is_valid() const {
    return (_current != nullptr);
}

/// @brief Overloaded ++ operator for iterator
template <typename T>
Y_DECL_CONSTEXPR typename y_list_forward<T>::iterator& y_list_forward<T>::iterator::operator++() {
    _current = _current->_next;
    return *this;
}

/// @brief Dereference operator overloading for iterator
template <typename T>
Y_DECL_CONSTEXPR T& y_list_forward<T>::iterator::operator*() const {
    return _current->_data;
}

} //End yamgl   

#endif