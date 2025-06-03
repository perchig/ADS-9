// Copyright 2025 NNTU-CS
#include "tree.h"
#include <memory>
#include <vector>

PMTree::PMTree(const std::vector<char>& input) : alphabet(input) {
  root = std::make_shared<TreeNode>();
  buildTree(root, alphabet);
}

void PMTree::buildTree(std::shared_ptr<TreeNode> node,
                       std::vector<char> remaining) {
  if (remaining.empty()) return;
  for (size_t i = 0; i < remaining.size(); ++i) {
    auto child = std::make_shared<TreeNode>(remaining[i]);
    node->children.push_back(child);
    std::vector<char> next;
    for (size_t j = 0; j < remaining.size(); ++j) {
      if (j != i) next.push_back(remaining[j]);
    }
    buildTree(child, next);
  }
}

void PMTree::getAllPermsRecursive(std::shared_ptr<TreeNode> node,
                                  std::vector<char>& current,
                                  std::vector<std::vector<char>>& result)
                                  const {
  if (node->children.empty()) {
    result.push_back(current);
    return;
  }
  for (auto& child : node->children) {
    current.push_back(child->value);
    getAllPermsRecursive(child, current, result);
    current.pop_back();
  }
}

void PMTree::getPerm1Recursive(std::shared_ptr<TreeNode> node,
                               std::vector<char>& current,
                               std::vector<std::vector<char>>& allPerms)
                               const {
  if (node->children.empty()) {
    allPerms.push_back(current);
    return;
  }
  for (auto& child : node->children) {
    current.push_back(child->value);
    getPerm1Recursive(child, current, allPerms);
    current.pop_back();
  }
}

std::vector<std::vector<char>> getAllPerms(const PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> current;
  tree.getAllPermsRecursive(tree.getRoot(), current, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  std::vector<std::vector<char>> allPerms;
  std::vector<char> current;
  tree.getPerm1Recursive(tree.getRoot(), current, allPerms);
  if (num <= 0 || num > static_cast<int>(allPerms.size())) {
    return std::vector<char>();
  }
  return allPerms[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  if (num <= 0) return std::vector<char>();
  int64_t n = tree.size();
  int64_t totalPerms = 1;
  for (int64_t i = 1; i <= n; ++i) {
    totalPerms *= i;
  }
  if (num > totalPerms) return std::vector<char>();
  std::vector<char> result;
  auto node = tree.getRoot();
  int64_t currentNum = num - 1;
  for (int64_t level = n; level > 0; --level) {
    int64_t permsPerChild = 1;
    for (int64_t i = 1; i < level; ++i) {
      permsPerChild *= i;
    }
    int64_t childIndex = currentNum / permsPerChild;
    result.push_back(node->children[childIndex]->value);
    node = node->children[childIndex];
    currentNum %= permsPerChild;
  }
  return result;
}

