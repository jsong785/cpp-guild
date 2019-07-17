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
class BinaryTreeRaii {
    public:
        BinaryTreeRaii() :
            m_array{ CreateBinaryTree() } {}
        BinaryTreeRaii(const BinaryTreeRaii&) = delete;
        BinaryTreeRaii(BinaryTreeRaii&&) = delete;
        ~BinaryTreeRaii() = default;

        BinaryTreeRaii& operator=(const BinaryTreeRaii&) = delete;
        BinaryTreeRaii& operator=(BinaryTreeRaii&&) = delete;

        T* root()
        { return &m_array[0]; }

    private:
        std::array<T, 2*DEPTH+1> CreateBinaryTree() const;

        std::array<T, 2*DEPTH+1> m_array;
};

}

using namespace Tree;

TEST_CASE("Invert binary tree", "[tree]")
{
    SECTION("Depth 1, 1 node")
    {
        BinaryTreeRaii<Node, 1> tree;
        auto root{ tree.root() };
        CHECK(root->id == 0);

        InvertTree(root);
        CHECK(root->id == 0);
    }

    SECTION("Depth 2, 3 nodes")
    {
        BinaryTreeRaii<Node, 2> tree;
        auto root{ tree.root() };
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
        BinaryTreeRaii<Node, 3> tree;
        auto root{ tree.root() };
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

template <typename T, unsigned DEPTH>
std::array<T, 2*DEPTH+1> BinaryTreeRaii<T, DEPTH>::CreateBinaryTree() const {
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


