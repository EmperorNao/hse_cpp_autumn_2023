#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "avl_allocator.hpp"
#include "avl_iterator.hpp"


namespace avl {

    enum class DIR {LEFT = 0, RIGHT = 1, NONE = 2};

    template <class Key, class Value> 
    struct Node {
        using key_type = Key;
        using value_type = Value;
        Node* parent;
        Node* left;
        Node* right;
        int64_t height;
        Key key;
        Value value;

        inline int64_t left_height() const {
            return left ? left->height: 0;
        }

        inline int64_t right_height() const {
            return right ? right->height: 0;
        }

        inline int64_t balance_factor() const {
            return right_height() - left_height();
        }

        inline void recalculate_height() {
            height = std::max(left_height(), right_height()) + 1;
        }

        inline bool is_root() {
            return !parent;
        }

    };

    template <class Key, class Value>
    Node<Key, Value>* rotate_left(Node<Key, Value>* node) {
        auto q = node;
        auto p = q->right;

        if (q->parent) {
            if (q->parent->left == q) {
                q->parent->left = p;
            }
            else {
                q->parent->right = p;
            }
        }

        q->right = p->left;
        if (q->right) {
            q->right->parent = q;
        }

        p->left = q;
        p->parent = q->parent;
        q->parent = p;

        q->recalculate_height();
        p->recalculate_height();

        return p;
    }

    template <class Key, class Value>
    Node<Key, Value>* rotate_right(Node<Key, Value>* node) {
        auto p = node;
        auto q = p->left;

        if (p->parent) {
            if (p->parent->left == p) {
                p->parent->left = q;
            }
            else {
                p->parent->right = q;
            }
        }

        p->left = q->right;
        if (p->left) {
            p->left->parent = p;
        }

        q->right = p;
        q->parent = p->parent;
        p->parent = q;

        p->recalculate_height();
        q->recalculate_height();

        return q;
    }

    template <class Key, class Value>
    Node<Key, Value>* rebalance(Node<Key, Value>* node) {
        node->recalculate_height();
        if (node->balance_factor() == 2) {
            if (node->right && node->right->balance_factor() < 0) {
                node->right = rotate_right(node->right);
            }
            return rotate_left(node);
        }
        else if (node->balance_factor() == -2) {
            if (node->left && node->left->balance_factor() > 0) {
                node->left = rotate_left(node->left);
            }
            return rotate_right(node);
        }
        return node;
    }

    template <class Key, class Value, class Compare = std::less<Key>, class Allocator = avl::AVLAllocator<Key, Value>>
    class AVLTree {
    public:
        using TNode = Node<Key, Value>;
        using PtrNode = TNode*;
        using avl_iterator = AVLIterator<Key, Value>;
        using avl_reverse_iterator = AVLReverseIterator<Key, Value>;

    private:
        PtrNode root_;
        PtrNode end_node_;
        Allocator allocator_;
        Compare comparator_;
        size_t size_;

        PtrNode allocate_node() {
            return allocator_.allocate(1);
        }

        PtrNode find_node(const Key& key) const {
            PtrNode save_node = root_;
            PtrNode cur_node = root_;
            while (cur_node && cur_node->key != key) {
                save_node = cur_node;
                if (!comparator_(cur_node->key, key)) {
                    cur_node = cur_node->left;
                }
                else {
                    cur_node = cur_node->right;
                }
            }
            if (cur_node) {
                return cur_node;
            }
            return save_node;
        }

        PtrNode insert(PtrNode node, const Key& key) {
            if (!node) {
                auto new_node = allocate_node();
                new_node->key = key;
                new_node->height = 1;
                new_node->left = nullptr;
                new_node->right = nullptr;
                return new_node;
            }
            if (comparator_(key, node->key)) {
                node->left = insert(node->left, key);
                node->left->parent = node;
            }
            else if (!comparator_(key, node->key)) {
                node->right = insert(node->right, key);
                node->right->parent = node;
            }
            return rebalance(node);
        }

        PtrNode most_left(PtrNode node) {
            if (!node) {
                return node;
            }
            while (node->left) {
                node = node->left;
            }
            return node;
        }

        PtrNode remove_left(PtrNode node) {
            if(!node->left) {
                return node->right;
            }
            node->left = remove_left(node->left);
            if (node->left) {
                node->left->parent = node;
            }
            return rebalance(node);
        }

        PtrNode erase(PtrNode node, Key key) {
            if (!node) {
                return nullptr;
            }

            if (key == node->key) {
                PtrNode q = node->left;
                PtrNode r = node->right;
                allocator_.deallocate(node, 1);
                if (!r) {
                    return q;
                }
                PtrNode min_node = most_left(r);
                min_node->right = remove_left(r);
                if (min_node->right) {
                    min_node->right->parent = min_node;
                }
                min_node->left = q;
                if (q) {
                    q->parent = min_node;
                }
                return rebalance(min_node);
            }
            if(comparator_(key, node->key)) {
                node->left = erase(node->left, key);
                if (node->left) {
                    node->left->parent = node;
                }
            }
            else {
                node->right = erase(node->right, key);
                if (node->right) {
                    node->right->parent = node;
                }
            }

            return rebalance(node);
        }

        void fill_end_node() {
            end_node_->parent = root_;
            end_node_->left = end_node_;
            end_node_->right = end_node_;
        }

        void clear(PtrNode node) {
            if (!node) {
                return;
            }
            clear(node->left);
            clear(node->right);
            allocator_.deallocate(node, 1);
        }

    public:
        Value& at(const Key& key) {
            PtrNode nearest_node = find_node(key);
            if (nearest_node->key == key) {
                return nearest_node->value;
            }
            throw std::out_of_range("AVLTree doesn't have key that you are provide");
        }
        const Value& at(const Key& key) const {
            PtrNode nearest_node = find_node(key);
            if (nearest_node->key == key) {
                return nearest_node->value;
            }
            throw std::out_of_range("AVLTree doesn't have key that you are provide");
        }

        Value& operator[](const Key& key) {
            PtrNode nearest_node = find_node(key);
            if (root_) {
                PtrNode nearest_node = find_node(key);
                if (nearest_node->key == key) {
                    return nearest_node->value;
                }
            }
            auto [inserted_node, _] = insert(key);
            return (*inserted_node).second;
        }

        Value& operator[](Key&& key) {
            if (root_) {
                PtrNode nearest_node = find_node(key);
                if (nearest_node->key == key) {
                    return nearest_node->value;
                }
            }
            auto [inserted_node, _] = insert(key);
            return (*inserted_node).second;
        }

        void fix_root() {
            if (!root_->is_root()) {
                while (root_->parent) {
                    root_ = root_->parent;
                }
            }
        }

        std::pair<avl_iterator, bool> insert(const Key& key) {

            if (!root_) {
                root_ = allocate_node();
                root_->key = key;
                root_->height = 1;
                root_->left = nullptr;
                root_->right = nullptr;
                root_->parent = nullptr;
                size_ = 1;
                fill_end_node();
                return std::make_pair(avl_iterator(root_), true);
            }

            PtrNode nearest_node = find_node(key);
            if (nearest_node && nearest_node->key == key) {
                return std::make_pair(avl_iterator(nearest_node), false);
            }

            size_ += 1;
            root_ = insert(root_, key);
            fill_end_node();
            return std::make_pair(avl_iterator(find_node(key)), true);
        }

        bool erase(const Key& key) {
            PtrNode nearest_node = find_node(key);
            if (!nearest_node || nearest_node->key != key) {
                return false;
            }

            size_ -= 1;
            root_ = erase(root_, key);
            root_->parent = nullptr;
            fill_end_node();
            return true;
        }

        avl_iterator find(const Key& key) {
            PtrNode nearest_node = find_node(key);
            if (nearest_node && nearest_node->key == key) {
                return avl_iterator(nearest_node);
            }
            return avl_iterator(end());
        }

        bool contains(const Key& key ) const {
            PtrNode nearest_node = find_node(key);
            if (nearest_node && nearest_node->key == key) {
                return true;
            }
            return false;
        };

        bool empty() const {
            return size_ == 0;
        };

        size_t size() const {
            return size_;
        };

        void clear() {
            clear(root_);
            root_ = nullptr;
            size_ = 0;
            fill_end_node();
        }

        avl_iterator begin() {
            if (!root_) {
                return avl_iterator(end_node_);
            }
            auto left = root_;
            while (left->left) {
                left = left->left;
            }
            return avl_iterator(left);
        };
        avl_iterator end() {
            return avl_iterator(end_node_);
        }

        avl_reverse_iterator rbegin() {
            if (!root_) {
                return avl_reverse_iterator(end_node_);
            }
            auto right = root_;
            while (right->right) {
                right = right->right;
            }
            return avl_reverse_iterator(right);
        };
        avl_reverse_iterator rend() {
            return avl_reverse_iterator(end_node_);
        }

    public:

        AVLTree() {
            root_ = nullptr;
            end_node_ = allocate_node();
            fill_end_node();
            allocator_ = Allocator();
            comparator_ = Compare();
            size_ = 0;
        }

        ~AVLTree() {
            clear();
            allocator_.deallocate(end_node_, 1);
        }

    };


}


