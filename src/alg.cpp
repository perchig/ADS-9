#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <algorithm>
#include  <numeric>
#include  "tree.h"
PMTree::PMTree(const std::vector<char>& input) : alphabet(input) {
    std::sort(alphabet.begin(), alphabet.end());
    root = std::make_shared<TreeNode>();
    buildTree(root, alphabet);
}
void PMTree::buildTree(std::shared_ptr<TreeNode> node, std::vector<char> remaining) {
    if (remaining.empty()) {
        return;
    }
    for (size_t i = 0; i < remaining.size(); ++i) {
        auto child = std::make_shared<TreeNode>(remaining[i]);
        node->children.push_back(child);
        std::vector<char> newRemaining;
        for (size_t j = 0; j < remaining.size(); ++j) {
            if (j != i) {
                newRemaining.push_back(remaining[j]);
            }
        }
        buildTree(child, newRemaining);
    }
}
std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> current;
    if (tree.getRoot()) {
        PMTree& nonConstTree = const_cast<PMTree&>(tree);
        nonConstTree.getAllPermsRecursive(tree.getRoot(), current, result);
    }
    return result;
}
void PMTree::getAllPermsRecursive(std::shared_ptr<TreeNode> node, 
                                  std::vector<char>& current, 
                                  std::vector<std::vector<char>>& result) const {
    if (node->value != '\0') {
        current.push_back(node->value);
    }
    if (node->children.empty() && !current.empty()) {
        result.push_back(current);
    } else {
        for (auto& child : node->children) {
            getAllPermsRecursive(child, current, result);
        }
    }
    if (node->value != '\0') {
        current.pop_back();
    }
}
std::vector<char> getPerm1(PMTree& tree, int num) {
    if (num <= 0) {
        return std::vector<char>();
    }
    std::vector<std::vector<char>> allPerms = getAllPerms(tree);
    if (num > static_cast<int>(allPerms.size())) {
        return std::vector<char>();
    }
    return allPerms[num - 1];
}
long long factorial(int n) {
    if (n <= 1) return 1;
    long long result = 1;
    for (int i = 2; i <= n; ++i) {
        result *= i;
    }
    return result;
}
std::vector<char> getPerm2(PMTree& tree, int num) {
    if (num <= 0) {
        return std::vector<char>();
    }
    int n = tree.size();
    long long totalPerms = factorial(n);
    if (num > totalPerms) {
        return std::vector<char>();
    }
    std::vector<char> result;
    std::vector<char> remaining = tree.getAlphabet();
    int index = num - 1;
    for (int level = 0; level < n; ++level) {
        long long permsPerBranch = factorial(n - level - 1);
        int branchIndex = index / permsPerBranch;
        result.push_back(remaining[branchIndex]);
        remaining.erase(remaining.begin() + branchIndex);
        index %= permsPerBranch;
    }
    return result;
}

