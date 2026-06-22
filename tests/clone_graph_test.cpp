#include "leetcode.hpp"

#include <gtest/gtest.h>

namespace clone_graph {

struct Node {
    int val;
    vector<Node*> neighbors;

    Node() : val(0) {}
    explicit Node(int _val) : val(_val) {}
    Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(std::move(_neighbors)) {}
};

class Solution {
    std::unordered_map<Node*, Node*> nodeMap;
public:
    Node* cloneGraph(Node* node) {
        // LeetCode 133: implement here.
        if (node == nullptr) {
            return node;
        }
        
        if (auto it = nodeMap.find(node); it != nodeMap.end()) {
            return it->second;
        }

        Node* clone = new Node(node->val);
        nodeMap.emplace(node, clone);

        for (auto nodeptr : node->neighbors) {
            clone->neighbors.push_back(cloneGraph(nodeptr));
        }

        return clone;
    }
};

namespace {

Node* buildGraph(const vector<vector<int>>& adj) {
    if (adj.empty()) {
        return nullptr;
    }

    vector<Node*> nodes(adj.size());
    for (size_t i = 0; i < adj.size(); ++i) {
        nodes[i] = new Node(static_cast<int>(i + 1));
    }

    for (size_t i = 0; i < adj.size(); ++i) {
        for (int neighbor : adj[i]) {
            nodes[i]->neighbors.push_back(nodes[neighbor - 1]);
        }
    }

    return nodes[0];
}

void deleteGraph(Node* node) {
    if (!node) {
        return;
    }

    unordered_set<Node*> visited;
    deque<Node*> q;
    q.push_back(node);
    visited.insert(node);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop_front();

        for (Node* neighbor : cur->neighbors) {
            if (!visited.contains(neighbor)) {
                visited.insert(neighbor);
                q.push_back(neighbor);
            }
        }

        delete cur;
    }
}

unordered_set<Node*> collectNodes(Node* node) {
    unordered_set<Node*> nodes;
    if (!node) {
        return nodes;
    }

    deque<Node*> q;
    q.push_back(node);
    nodes.insert(node);

    while (!q.empty()) {
        Node* cur = q.front();
        q.pop_front();

        for (Node* neighbor : cur->neighbors) {
            if (!nodes.contains(neighbor)) {
                nodes.insert(neighbor);
                q.push_back(neighbor);
            }
        }
    }

    return nodes;
}

vector<vector<int>> serializeGraph(Node* node) {
    if (!node) {
        return {};
    }

    unordered_map<Node*, int> index;
    vector<Node*> q;
    q.push_back(node);
    index[node] = 1;

    for (size_t i = 0; i < q.size(); ++i) {
        for (Node* neighbor : q[i]->neighbors) {
            if (!index.contains(neighbor)) {
                index[neighbor] = static_cast<int>(index.size()) + 1;
                q.push_back(neighbor);
            }
        }
    }

    vector<vector<int>> adj(index.size());
    for (Node* cur : q) {
        vector<int> neighbors;
        for (Node* neighbor : cur->neighbors) {
            neighbors.push_back(index[neighbor]);
        }
        sort(neighbors.begin(), neighbors.end());
        adj[index[cur] - 1] = std::move(neighbors);
    }

    return adj;
}

void expectDeepCopy(Node* original, Node* clone) {
    ASSERT_NE(original, nullptr);
    ASSERT_NE(clone, nullptr);
    ASSERT_NE(original, clone);

    const auto originalNodes = collectNodes(original);
    const auto cloneNodes = collectNodes(clone);

    EXPECT_EQ(originalNodes.size(), cloneNodes.size());
    EXPECT_EQ(serializeGraph(original), serializeGraph(clone));

    for (Node* node : originalNodes) {
        EXPECT_FALSE(cloneNodes.contains(node));
    }
}

struct TestCase {
    vector<vector<int>> adj;
};

class CloneGraphTest : public testing::TestWithParam<TestCase> {};

TEST_P(CloneGraphTest, DeepCopyMatchesOriginal) {
    Solution solution;
    Node* original = buildGraph(GetParam().adj);
    Node* clone = solution.cloneGraph(original);

    expectDeepCopy(original, clone);

    deleteGraph(original);
    deleteGraph(clone);
}

INSTANTIATE_TEST_SUITE_P(
    Cases,
    CloneGraphTest,
    testing::Values(
        // LeetCode examples
        TestCase{{{2, 4}, {1, 3}, {2, 4}, {1, 3}}},
        TestCase{{{}}},

        // // Two nodes
        TestCase{{{2}, {1}}},

        // // Chain
        TestCase{{{2}, {3}, {}}},

        // // Triangle
        TestCase{{{2, 3}, {1, 3}, {1, 2}}},

        // // Star centered at node 1
        TestCase{{{2, 3, 4}, {1}, {1}, {1}}},

        // // Complete graph on four nodes
        TestCase{{{2, 3, 4}, {1, 3, 4}, {1, 2, 4}, {1, 2, 3}}}
    ));

TEST(CloneGraph, NullInput) {
    Solution solution;
    EXPECT_EQ(solution.cloneGraph(nullptr), nullptr);
}

}  // namespace

}  // namespace clone_graph
