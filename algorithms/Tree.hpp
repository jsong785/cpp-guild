#pragma once

#include <algorithm>

namespace Tree {

template <typename T>
void InvertTree(T* node) {
    if(node != nullptr) {
        InvertTree(node->left);
        InvertTree(node->right);
        std::swap(node->left, node->right);
    }
}

}
