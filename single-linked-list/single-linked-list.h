#pragma once

// добавьте неоходимые include-директивы сюда

class SingleLinkedList {
    
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value{};
        Node* next_node = nullptr;
    };

// внешние функции разместите здесь
