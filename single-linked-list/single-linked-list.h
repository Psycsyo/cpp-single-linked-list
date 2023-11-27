#include <iterator>
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>
 
template <typename Type>
class SingleLinkedList {
 
    struct Node {
        Node() = default;
        Node(const Type& val, Node* next)
            : value(val)
            , next_node(next) {
        }
        Type value;
        Node* next_node = nullptr;
    };
 
 
    template <typename ValueType>
    class BasicIterator {
 
        friend class SingleLinkedList;
 
    public:
 
        using iterator_category = std::forward_iterator_tag;
        using value_type = Type;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueType*;
        using reference = ValueType&;
 
        BasicIterator() = default;
        BasicIterator(const BasicIterator<Type>& other) noexcept {
            node_ = other.node_;
        }
        explicit BasicIterator(Node* node) :node_(node) {
 
        }
 
        BasicIterator& operator=(const BasicIterator& rhs) = default;
 
        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
 
            return node_ == rhs.node_;
 
        }
 
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
 
            return node_ != rhs.node_;
        }
 
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
 
            return node_ == rhs.node_;
 
        }
 
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
 
            return node_ != rhs.node_;
 
        }
 
        BasicIterator& operator++() noexcept {
 
            node_ = node_->next_node;
 
            return *this;
        }
 
        BasicIterator operator++(int) noexcept {
 
            assert(this != nullptr);
 
            auto temp(*this);
 
            ++(*this);
 
            return temp;
 
        }
 
        [[nodiscard]] reference operator*() const noexcept {
 
            assert(node_ != nullptr);
 
            return node_->value;
        }
 
        [[nodiscard]] pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return &(node_->value);
        }
 
 
    private:
 
        Node* node_ = nullptr;
    };
 
public:
 
    SingleLinkedList() = default;
 
    SingleLinkedList(std::initializer_list<Type> values) :size_(0) {
        auto temp = new SingleLinkedList();
 
        for (auto it = values.end() - 1; it != values.begin(); --it)
        {
            temp->PushFront(*it);
        }
        temp->PushFront(*values.begin());
        this->Clear();
        assert(this->GetSize() == 0);
        swap(*temp);
    }
    SingleLinkedList(const SingleLinkedList& other) {
        SingleLinkedList* temp = new SingleLinkedList();
        for (auto it = other.begin(); it != other.end(); ++it) {
            temp->PushFront(*it);
        }
    }
    ~SingleLinkedList() {
        Clear();
    }
 
    SingleLinkedList& operator=(const SingleLinkedList& rhs) {
        if (rhs.begin() != this->begin()) {
 
            auto temp = SingleLinkedList(rhs);
 
            swap(temp);
 
        }
        return *this;
    }
 
    void PushBack(const Type& value) {
        Node* ptr = head_.next_node;
        Node* current;
        while (ptr != nullptr) {
            current = ptr;
            ptr = ptr->next_node;
        }
        current->next_node = new Node(value);
        ++size_;
    }
 
    void swap(SingleLinkedList& other) noexcept {
 
        std::swap(head_.next_node, other.head_.next_node);
 
        std::swap(other.size_, this->size_);
 
    }
 
    void PushFront(const Type& value) {
        auto temp = new Node(value, head_.next_node);
        head_.next_node = temp;
        ++size_;
    }
 
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using Iterator = BasicIterator<Type>;  
    using ConstIterator = BasicIterator<const Type>; 
 
    [[nodiscard]] Iterator begin() noexcept {
 
        return Iterator(head_.next_node);
 
    }
 
    [[nodiscard]] Iterator end() noexcept {
 
        return Iterator(nullptr);
 
    }
 
    [[nodiscard]] ConstIterator begin() const noexcept {
 
        return ConstIterator(head_.next_node);
    }
 
    [[nodiscard]] ConstIterator end() const noexcept {
 
 
        return ConstIterator(nullptr);
    }
 
    [[nodiscard]] ConstIterator cbegin() const noexcept {
        return ConstIterator(head_.next_node);
    }
 
    [[nodiscard]] ConstIterator cend() const noexcept {
 
        return ConstIterator(nullptr);
    }
 
    [[nodiscard]] Iterator before_begin() noexcept {
        return Iterator(&head_);
    };
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
 
        return ConstIterator(const_cast<SingleLinkedList<Type>::Node*>(&head_));
    }
 
    [[nodiscard]] ConstIterator before_begin() const noexcept {
        return ConstIterator(const_cast<SingleLinkedList<Type>::Node*>(&head_));
    }
 
    void Clear() noexcept {
 
        while (head_.next_node != nullptr) {
            auto next_node_ = head_.next_node->next_node;
            delete head_.next_node;
            head_.next_node = next_node_;
        }
        size_ = 0;
        head_.next_node = nullptr;
    }
 
    Iterator InsertAfter(ConstIterator pos, const Type& value) {
        assert(pos.node_ != nullptr);
        auto temp = new Node(value, pos.node_->next_node);
        pos.node_->next_node = temp;
        size_++;
        return Iterator(temp);
 
    }
 
    void PopFront() {
 
        auto tmp = head_.next_node->next_node;
        delete head_.next_node;
        head_.next_node = tmp;
        size_--;
    }
 
 
    Iterator EraseAfter(ConstIterator pos) noexcept {
 
        assert(pos != this->end() && pos.node_->next_node != nullptr);
 
        auto  node_to_delete = pos.node_->next_node;
 
        pos.node_->next_node = pos.node_->next_node->next_node;
 
        delete node_to_delete;
 
        --size_;
 
        return Iterator(pos.node_->next_node);
 
    }
    
    [[nodiscard]] size_t GetSize() const noexcept {
 
        return size_;
 
    }
 
    [[nodiscard]] bool IsEmpty() const noexcept {
 
        return size_ == 0;
    }
 
private:
 
    Node  head_;
    size_t size_ = 0;
};
template <typename Type>
void swap(SingleLinkedList<Type>& lhs, SingleLinkedList<Type>& rhs) noexcept {
 
    lhs.swap(rhs);
 
}
   
template <typename Type>
bool operator==(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
    if (lhs.GetSize() != rhs.GetSize()) {
        return false;
    }
    return std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
 
}
 
template <typename Type>
bool operator!=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
 
    return !(lhs == rhs);
 
}
 
template <typename Type>
bool operator<(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
 
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
 
 
template <typename Type>
bool operator>=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
 
    return !(lhs < rhs);
 
}
 
 
template <typename Type>
bool operator>(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
 
    return (rhs < lhs);
 
}
 
template <typename Type>
bool operator<=(const SingleLinkedList<Type>& lhs, const SingleLinkedList<Type>& rhs) {
 
    return !(rhs > lhs);
 
}
