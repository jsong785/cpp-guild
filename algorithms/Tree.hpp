#pragma once

#include <algorithm>
#include <assert.h>
#include <deque>
#include <iterator>
#include <vector>

namespace Tree {

template <typename T>
void InvertTree(T* node) {
    if(node != nullptr) {
        InvertTree(node->left);
        InvertTree(node->right);
        std::swap(node->left, node->right);
    }
}

template <typename T>
class PriorityHeap {
    public:
        PriorityHeap() = default;
        PriorityHeap(std::vector<T> list) 
            : m_heap{ CreateHeap(std::move(list)) } {}
        PriorityHeap(const PriorityHeap&) = default;
        PriorityHeap(PriorityHeap&&) noexcept = default;

        PriorityHeap& operator=(const PriorityHeap&) = default;
        PriorityHeap& operator=(PriorityHeap&&) noexcept = default;

        void Insert(T item) {
            m_heap.emplace_front(item);
            BubbleDown(m_heap, 0);
        }

        bool empty() const {
            return m_heap.empty();
        }

        const T& min() const {
            // invalid if the list is empty
            return *m_heap.begin();
        }

        T pop() {
            // invalid if the list is empty
            auto cached = *m_heap.begin();

            std::swap(*m_heap.begin(), *m_heap.rbegin());
            m_heap.erase(std::prev(m_heap.end()));
            if(!m_heap.empty()) {
                BubbleDown(m_heap, 0);
            }

            return cached;
        }

    private:
        using Heap = std::deque<T>;

        Heap CreateHeap(std::vector<T> items) const {
            Heap heap;
            for(const auto &i : items) {
                heap.emplace_front(i);
                BubbleDown(heap, 0);
            }
            return heap;
        }

        void BubbleDown(std::deque<T> &heap, const std::size_t index) const {
            assert(index < heap.size());
            const auto leftChild = [](const auto index) {
                return index * 2;
            };

            const auto updateMinIndex = [&heap](const auto minIndex, const auto compareIndex) {
                if(minIndex < heap.size() && compareIndex < heap.size() && heap[compareIndex] < heap[minIndex]) {
                    return compareIndex;
                }
                return minIndex;
            };

            auto minIndex = updateMinIndex(index, leftChild(index));
            minIndex = updateMinIndex(minIndex, leftChild(index)+1); // right child
            if(index != minIndex) {
                std::swap(heap[index], heap[minIndex]);
                BubbleDown(heap, minIndex);
            }

        }

        void BubbleUp(Heap &heap, const std::size_t index) const {
            assert(index < heap.size());
            if(index == 0) {
                return;
            }

            const auto parent = [](const auto index) {
                return static_cast<int>(index / 2); // floor
            };

            const auto parentIndex = parent(index);
            if(heap[index] < heap[parentIndex]) {
                std::swap(heap[index], heap[parentIndex]);
                BubbleUp(heap, parentIndex);
            }
        }
        
        Heap m_heap;
};

}
