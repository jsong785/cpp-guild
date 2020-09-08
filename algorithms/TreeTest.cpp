#include "Tree.hpp"
#include "catch.hpp"
#include <array>

namespace {

struct Node {
    unsigned id{ 0 };
    Node* left{ nullptr };
    Node* right{ nullptr };
};

template <typename T, unsigned DEPTH>
std::array<T, 2*DEPTH+1> CreateBinaryTree() {
    std::array<T, 2*DEPTH+1> array;

    for(unsigned i{ 0 }; i < 2*DEPTH+1; ++i) {
        array[i].id = i;

        const unsigned leftIndex{ 2*i + 1 };
        if(leftIndex < 2*DEPTH+1) {
            array[i].left = &array[leftIndex];
            array[i].right = &array[leftIndex+1]; // means there is room for the right as well
        }
    }

    return array;
}


}

using namespace Tree;

TEST_CASE("Invert binary tree", "[tree]")
{
    SECTION("Depth 1, 1 node")
    {
        auto tree{ CreateBinaryTree<Node, 1>() };
        auto root{ &tree[0] };
        CHECK(root->id == 0);

        InvertTree(root);
        CHECK(root->id == 0);
    }

    SECTION("Depth 2, 3 nodes")
    {
        auto tree{ CreateBinaryTree<Node, 2>() };
        auto root{ &tree[0] };
        CHECK(root->id == 0);
        CHECK(root->left->id == 1);
        CHECK(root->right->id == 2);

        InvertTree(root);
        CHECK(root->id == 0);
        CHECK(root->left->id == 2);
        CHECK(root->right->id == 1);
    }

    SECTION("Depth 3, 7 nodes")
    {
        auto tree{ CreateBinaryTree<Node, 3>() };
        auto root{ &tree[0] };
        CHECK(root->id == 0);
        CHECK(root->left->id == 1);
        CHECK(root->right->id == 2);

        CHECK(root->left->left->id == 3);
        CHECK(root->left->right->id == 4);

        CHECK(root->right->left->id == 5);
        CHECK(root->right->right->id == 6);

        InvertTree(root);
        CHECK(root->id == 0);
        CHECK(root->left->id == 2);
        CHECK(root->right->id == 1);

        CHECK(root->left->left->id == 6);
        CHECK(root->left->right->id == 5);

        CHECK(root->right->left->id == 4);
        CHECK(root->right->right->id == 3);
    }
}

/*
TEST_CASE("Priority Heap", "[tree]") {
    SECTION("Compare Empty")
    {
        CHECK(PriorityHeap<int>{}.empty());
        CHECK(!PriorityHeap<int>{{1}}.empty());
    }

    SECTION("Compare Min") {
        CHECK(PriorityHeap<int>{{1}}.min() == 1);
        CHECK(PriorityHeap<int>{{1, 2, 3, 4, 5}}.min() == 1);
        CHECK(PriorityHeap<int>{{5, 4, 3, 2, 1}}.min() == 1);
        CHECK(PriorityHeap<int>{{4, 5, 1, 3, -1, 10}}.min() == -1);
    }

    SECTION("Pop Min 1") {
        PriorityHeap<int> heap{{1, 2, 3, 4, 5}};
        CHECK(heap.pop() == 1); CHECK(!heap.empty());
        CHECK(heap.pop() == 2); CHECK(!heap.empty());
        CHECK(heap.pop() == 3); CHECK(!heap.empty());
        CHECK(heap.pop() == 4); CHECK(!heap.empty());
        CHECK(heap.pop() == 5); CHECK(heap.empty());
    }

    SECTION("Pop Min 2") {
        PriorityHeap<int> heap{{4, 5, 1, 3, -1, 10}};
        CHECK(heap.pop() == -1); CHECK(!heap.empty());
        CHECK(heap.pop() == 1); CHECK(!heap.empty());
        CHECK(heap.pop() == 3); CHECK(!heap.empty());
        CHECK(heap.pop() == 4); CHECK(!heap.empty());
        CHECK(heap.pop() == 5); CHECK(!heap.empty());
        CHECK(heap.pop() == 10); CHECK(heap.empty());
    }

    SECTION("Insert") {
        PriorityHeap<int> heap;
        for(const auto i : {4, 5, 1, 3, -1, 10}) {
            heap.Insert(i);
        }
        CHECK(heap.pop() == -1); CHECK(!heap.empty());
        CHECK(heap.pop() == 1); CHECK(!heap.empty());
        CHECK(heap.pop() == 3); CHECK(!heap.empty());
        CHECK(heap.pop() == 4); CHECK(!heap.empty());
        CHECK(heap.pop() == 5); CHECK(!heap.empty());
        CHECK(heap.pop() == 10); CHECK(heap.empty());
    }
}
*/

