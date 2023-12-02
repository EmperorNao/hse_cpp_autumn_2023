#pragma once

#include <string>
#include <algorithm>

#include "gtest/gtest.h"

#include "avl_tree.hpp"


class TestAVLTree: public ::testing::Test {

protected:

    void SetUp() { }
    void TearDown() { }

};

TEST_F(TestAVLTree, testConstructorAVLTree) {
    struct custom_type {
        int32_t a;
    };
    class CustomComparator {
    public:
        bool operator()(const custom_type& l, const custom_type& r) {
            return l.a < r.a;
        }
    };

    avl::AVLTree<std::int32_t, std::int32_t> int_tree;
    avl::AVLTree<std::string, std::int32_t> string_tree;
    avl::AVLTree<custom_type, custom_type, CustomComparator> custom_type_tree;
}

TEST_F(TestAVLTree, testSubscriptionOperatorAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    tree[1] = 1;
    ASSERT_EQ(tree[1], 1);
    ASSERT_NE(tree[1], 2);
    tree[1] = 2;
    ASSERT_EQ(tree[1], 2);
    ASSERT_NE(tree[1], 1);
}

TEST_F(TestAVLTree, testInsertAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    tree[1] = 1;
    tree.insert(2);
    tree[2] = 3;
    ASSERT_EQ(tree[2], 3);
    ASSERT_NE(tree[2], 4);
    tree[2] = 4;
    ASSERT_EQ(tree[2], 4);
    ASSERT_NE(tree[2], 3);
}

TEST_F(TestAVLTree, testAtAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    tree.insert(2);
    ASSERT_THROW(tree.at(1), std::out_of_range);
    ASSERT_NO_THROW(tree.at(2));
    tree.insert(1);
    ASSERT_NO_THROW(tree.at(1));
    ASSERT_NO_THROW(tree.at(2));
}

TEST_F(TestAVLTree, testSizeAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    ASSERT_EQ(tree.size(), 0);
    tree[1] = 1;
    ASSERT_EQ(tree.size(), 1);
    tree[2] = 4;
    ASSERT_EQ(tree.size(), 2);
}

TEST_F(TestAVLTree, testClearAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    ASSERT_EQ(tree.size(), 0);
    tree[1] = 1;
    ASSERT_EQ(tree.size(), 1);
    tree.clear();
    ASSERT_EQ(tree.size(), 0);
}


TEST_F(TestAVLTree, testFindAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t, std::greater<int>> tree;
    ASSERT_EQ(tree.find(3), tree.end());
    tree.insert(3);
    ASSERT_NE(tree.find(3), tree.end());
    ASSERT_EQ(tree.find(5), tree.end());
}

TEST_F(TestAVLTree, testContainsAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t, std::greater<int>> tree;
    ASSERT_EQ(tree.contains(3), false);
    tree.insert(3);
    ASSERT_EQ(tree.contains(3), true);
    ASSERT_EQ(tree.contains(5), false);
}

TEST_F(TestAVLTree, testEmptyAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t, std::greater<int>> tree;
    ASSERT_EQ(tree.empty(), true);
    tree.insert(3);
    ASSERT_EQ(tree.empty(), false);
}

TEST_F(TestAVLTree, testEraseAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    ASSERT_EQ(tree.contains(1), true);
    ASSERT_EQ(tree.contains(2), true);
    ASSERT_EQ(tree.contains(3), true);

    tree.erase(2);
    ASSERT_EQ(tree.contains(1), true);
    ASSERT_EQ(tree.contains(2), false);
    ASSERT_EQ(tree.contains(3), true);
    ASSERT_EQ(tree.size(), 2);

    tree.erase(2);
    ASSERT_EQ(tree.contains(1), true);
    ASSERT_EQ(tree.contains(2), false);
    ASSERT_EQ(tree.contains(3), true);
    ASSERT_EQ(tree.size(), 2);
}

TEST_F(TestAVLTree, testIteratorAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    std::vector<std::int32_t> sequence;
    for (std::int32_t i = -10; i < 10; ++i) {
        sequence.push_back(i);
        tree.insert(i);
    }

    std::int32_t counter = 0;
    for (const auto& el: tree) {
        ASSERT_EQ(el.first, sequence[counter]);
        ++counter;
    }

    counter = 0;
    for (auto it = tree.end() - 1; it != tree.begin(); --it) {
        ASSERT_EQ((*it).first, sequence[sequence.size() - 1 - counter]);
        ++counter;
    }
}

TEST_F(TestAVLTree, testReverseIteratorAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    std::vector<std::int32_t> sequence;
    for (std::int32_t i = -10; i < 10; ++i) {
        sequence.push_back(i);
        tree.insert(i);
    }

    std::int32_t counter = 0;
    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
        ASSERT_EQ((*it).first, sequence[sequence.size() - 1 - counter]);
        ++counter;
    }

    counter = 0;
    for (auto it = tree.rend() - 1; it != tree.rbegin(); --it) {
        ASSERT_EQ((*it).first, sequence[counter]);
        ++counter;
    }
}

TEST_F(TestAVLTree, testLongSequenceInsertionAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    tree.insert(-10);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-5);
    tree.insert(-20);
    tree.insert(2);
    tree.insert(100);
    tree.insert(50);
    tree.insert(80);
    tree.insert(30);
    tree.insert(-50);
    tree.insert(-100);
    tree.insert(200);
    tree.insert(0);

    std::vector<std::int32_t> sequence {-10, 1, 3, -5, -20, 30, 2, 100, 50, 80, -50, -100, 200, 0};
    std::sort(sequence.begin(), sequence.end());

    std::vector<std::int32_t> tree_sequence;
    for (const auto& el: tree) {
        tree_sequence.push_back(el.first);
    }

    ASSERT_EQ(sequence, tree_sequence);
    ASSERT_TRUE(std::is_sorted(tree.begin(), tree.end()));
}

TEST_F(TestAVLTree, testLongSequenceErasureAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t> tree;
    tree.insert(-10);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-5);
    tree.insert(-20);
    tree.insert(2);
    tree.insert(100);
    tree.insert(50);
    tree.insert(80);
    tree.insert(30);
    tree.insert(-50);
    tree.insert(-100);
    tree.insert(200);
    tree.insert(0);

    tree.erase(-5);
    tree.erase(100);
    tree.erase(80);
    tree.erase(200);
    tree.erase(0);
    tree.erase(1);

    std::vector<std::int32_t> sequence {-10, 3, -20, 30, 2, 50, -50, -100};
    std::sort(sequence.begin(), sequence.end());

    std::vector<std::int32_t> tree_sequence;
    for (const auto& el: tree) {
        tree_sequence.push_back(el.first);
    }

    ASSERT_EQ(sequence, tree_sequence);
    ASSERT_TRUE(std::is_sorted(tree.begin(), tree.end()));
}

TEST_F(TestAVLTree, testComparatorAVLTree) {
    avl::AVLTree<std::int32_t, std::int32_t, std::greater<int>> tree;

    std::vector<std::int32_t> sequence;
    for (std::int32_t i = -10; i < 10; ++i) {
        sequence.push_back(i);
        tree.insert(i);
    }
    std::reverse(sequence.begin(), sequence.end());

    std::vector<std::int32_t> tree_sequence;
    for (const auto& el: tree) {
        tree_sequence.push_back(el.first);
    }

    ASSERT_EQ(sequence, tree_sequence);
}