#include "avl_tree_tests.hpp"


int main(int argc, char** argv) {

//    std::cout << "WHAT?\n";
//    avl::AVLTree<std::int32_t, std::int32_t> tree;
//    std::string key;
//    std::string value;
//
//    std::cout << "Tree1: \n";
//    tree.write();
//
//    std::cout << "Tree2: \n";
//    for(auto el: tree) {
//        std::cout << "Key = " << el.first << " | " << "Value = " << el.second << "\n";
//    }
//
//    std::cout << "Tree3: \n";
//    for (auto it = tree.end() - 1; it != tree.begin(); it = it - 1) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    std::cout << "Tree4: \n";
//    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    tree[-20] = 0;
//    tree[-3] = 4;
//    tree[-1] = 10;
//    tree[0] = 20;
//    tree[1] = 2;
//    tree[4] = 3;
//    tree[5] = 6;
//    tree[7] = 8;
//    tree[9] = 4;
//    tree[10] = -1;
////    auto [d, _] = tree.insert(3);
//    tree[3] = 3;
//
//    std::cout << "Tree1: \n";
//    tree.write();
//
//    std::cout << "Tree2: \n";
//    for(auto el: tree) {
//        std::cout << "Key = " << el.first << " | " << "Value = " << el.second << "\n";
//    }
//
//    std::cout << "Tree3: \n";
//    for (auto it = tree.end() - 1; it != tree.begin(); it = it - 1) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    std::cout << "Tree4: \n";
//    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    std::cout << "erase";
//
//    tree.erase(4);
//    tree.erase(3);
//    tree.erase(0);
//    tree.erase(-20);
//
//    std::cout << "Tree1: \n";
//    tree.write();
//
//    std::cout << "Tree2: \n";
//    for(auto el: tree) {
//        std::cout << "Key = " << el.first << " | " << "Value = " << el.second << "\n";
//    }
//
//    std::cout << "Tree3: \n";
//    for (auto it = tree.end() - 1; it != tree.begin(); it = it - 1) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    std::cout << "Tree4: \n";
//    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    tree[-10] = 0;
//    tree[10] = 0;
//    tree[9] = 4;
//    tree[8] = 10;
//    tree[7] = 20;
//    tree[6] = 2;
//    tree[5] = 3;
//    tree[4] = 6;
//    tree[3] = 8;
//    tree[2] = 4;
//    tree[1] = -1;
//
//    std::cout << "Tree1: \n";
//    tree.write();
//
//    std::cout << "Tree2: \n";
//    for(auto el: tree) {
//        std::cout << "Key = " << el.first << " | " << "Value = " << el.second << "\n";
//    }
//
//    std::cout << "Tree3: \n";
//    for (auto it = tree.end() - 1; it != tree.begin(); it = it - 1) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    std::cout << "Tree4: \n";
//    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    tree.clear();
//
//    std::cout << "Tree1: \n";
//    tree.write();
//
//    std::cout << "Tree2: \n";
//    for(auto el: tree) {
//        std::cout << "Key = " << el.first << " | " << "Value = " << el.second << "\n";
//    }
//
//    std::cout << "Tree3: \n";
//    for (auto it = tree.end() - 1; it != tree.begin(); it = it - 1) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }
//
//    std::cout << "Tree4: \n";
//    for (auto it = tree.rbegin(); it != tree.rend(); ++it) {
//        std::cout << "Key = " << (*it).first << " | " << "Value = "  << (*it).second << "\n";
//    }

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}