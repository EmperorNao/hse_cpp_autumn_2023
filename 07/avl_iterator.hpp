#pragma once

#include <iterator>
#include <utility>


namespace avl {

    template <class Key, class Value> 
    struct Node;

    template <class Key, class Value, class Compare, class Allocator>
    class AVLTree;

    enum class DIR;

    template <class Key, class Value> 
    class AVLIterator: std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>> {
        using value_type = std::pair<Key, Value>;
        using reference = std::pair<Key, Value&>;
        using pointer = std::pair<Key, Value&>*;

        avl::Node<Key, Value>* node_;

        bool is_end() const {
            return !node_ || (node_->left != nullptr && node_->left == node_->right);
        }

        public:
        AVLIterator(avl::Node<Key, Value>* node) {
            node_ = node;
        }

        reference operator*() const {
            return std::make_pair(std::ref(node_->key), std::ref(node_->value));
        }

        AVLIterator& operator++() {
            return (*this) + 1;
        }

        AVLIterator& operator--() {
            return (*this) - 1;
        }

        AVLIterator& operator+(int64_t n) {
            if (n < 0) {
                return (*this) - std::abs(n);
            }
            auto current_node = node_;
            for (int64_t iter = 0; iter < n; ++iter) {
                if (current_node->right) {
                    current_node = current_node->right;
                    while (current_node->left) {
                        current_node = current_node->left;
                    }
                    continue;
                }
                if (current_node->parent && current_node->parent->left == current_node) {
                    current_node = current_node->parent;
                    continue;
                }
                while (current_node->parent && current_node->parent->right == current_node) {
                    current_node = current_node->parent;
                }
                if (current_node->parent) {
                    current_node = current_node->parent;
                    continue;
                }
                current_node = nullptr;
                break;
            }
            this->node_ = current_node;
            return *this;
        }

        AVLIterator& operator-(int64_t n) {
            if (n < 0) {
                return (*this) - std::abs(n);
            }
            if (is_end()) {
                --n;
                auto root = node_->parent;
                if (!root) {
                    return *this;
                }
                while (root->right) {
                    root = root->right;
                }
                node_ = root;
            }
            auto current_node = node_;
            for (int64_t iter = 0; iter < n; ++iter) {
                if (current_node->left) {
                    current_node = current_node->left;
                    while (current_node->right) {
                        current_node = current_node->right;
                    }
                    continue;
                }
                if (current_node->parent && current_node->parent->right == current_node) {
                    current_node = current_node->parent;
                    continue;
                }
                while (current_node->parent && current_node->parent->left == current_node) {
                    current_node = current_node->parent;
                }
                if (current_node->parent) {
                    current_node = current_node->parent;
                    continue;
                }
                current_node = nullptr;
                break;
            }
            this->node_ = current_node;
            return *this;
        }

        bool operator==(const AVLIterator& rhs) const {
            auto lhs = *this;
            return (lhs.is_end() && rhs.is_end()) ||
                    (!lhs.is_end() && !rhs.is_end() && lhs.node_->key == rhs.node_->key);
        }

        bool operator!=(const AVLIterator& rhs) const {
            return !(*this == rhs);
        }

    };

    template <class Key, class Value> 
    class AVLReverseIterator: std::iterator<std::bidirectional_iterator_tag, std::pair<Key, Value>> {
        using value_type = std::pair<Key, Value>;
        using reference = std::pair<Key, Value&>;
        using pointer = std::pair<Key, Value&>*;

        avl::Node<Key, Value>* node_;

        bool is_end() const {
            return !node_ || (node_->left != nullptr && node_->left == node_->right);
        }

    public:
        AVLReverseIterator(avl::Node<Key, Value>* node) {
            node_ = node;
        }

        reference operator*() const {
            return std::make_pair(std::ref(node_->key), std::ref(node_->value));
        }

        AVLReverseIterator& operator++() {
            return (*this) + 1;
        }

        AVLReverseIterator& operator--() {
            return (*this) - 1;
        }

        AVLReverseIterator& operator-(int64_t n) {
            if (n < 0) {
                return (*this) + std::abs(n);
            }
            if (is_end()) {
                --n;
                auto root = node_->parent;
                if (!root) {
                    return *this;
                }
                while (root->left) {
                    root = root->left;
                }
                node_ = root;
            }
            auto current_node = node_;
            for (int64_t iter = 0; iter < n; ++iter) {
                if (current_node->right) {
                    current_node = current_node->right;
                    while (current_node->left) {
                        current_node = current_node->left;
                    }
                    continue;
                }
                if (current_node->parent && current_node->parent->left == current_node) {
                    current_node = current_node->parent;
                    continue;
                }
                while (current_node->parent && current_node->parent->right == current_node) {
                    current_node = current_node->parent;
                }
                if (current_node->parent) {
                    current_node = current_node->parent;
                    continue;
                }
                current_node = nullptr;
                break;
            }
            this->node_ = current_node;
            return *this;
        }

        AVLReverseIterator& operator+(int64_t n) {
            if (n < 0) {
                return (*this) - std::abs(n);
            }
            auto current_node = node_;
            for (int64_t iter = 0; iter < n; ++iter) {
                if (current_node->left) {
                    current_node = current_node->left;
                    while (current_node->right) {
                        current_node = current_node->right;
                    }
                    continue;
                }
                if (current_node->parent && current_node->parent->right == current_node) {
                    current_node = current_node->parent;
                    continue;
                }
                while (current_node->parent && current_node->parent->left == current_node) {
                    current_node = current_node->parent;
                }
                if (current_node->parent) {
                    current_node = current_node->parent;
                    continue;
                }
                current_node = nullptr;
                break;
            }
            this->node_ = current_node;
            return *this;
        }

        bool operator==(const AVLReverseIterator& rhs) const {
            auto lhs = *this;
            return (lhs.is_end() && rhs.is_end()) ||
                   (!lhs.is_end() && !rhs.is_end() && lhs.node_->key == rhs.node_->key);
        }

        bool operator!=(const AVLReverseIterator& rhs) const {
            return !(*this == rhs);
        }

    };
};