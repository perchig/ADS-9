#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>
#include <memory>
class TreeNode {
 public:
    char value;
    std::vector<std::shared_ptr<TreeNode>> children;
    TreeNode() : value('\0') {}
    explicit TreeNode(char val) : value(val) {}
};
class PMTree {
 private:
    std::shared_ptr<TreeNode> root;
    std::vector<char> alphabet;
    void buildTree(std::shared_ptr<TreeNode> node, std::vector<char> remaining);
    void getPerm1Recursive(std::shared_ptr<TreeNode> node,
                          std::vector<char>& current,
                          std::vector<std::vector<char>>& allPerms) const;
 public:
    explicit PMTree(const std::vector<char>& input);
    std::shared_ptr<TreeNode> getRoot() const { return root; }
    const std::vector<char>& getAlphabet() const { return alphabet; }
    size_t size() const { return alphabet.size(); }
    void getAllPermsRecursive(std::shared_ptr<TreeNode> node, 
                             std::vector<char>& current, 
                             std::vector<std::vector<char>>& result) const;
};
std::vector<std::vector<char>> getAllPerms(const PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);
#endif
