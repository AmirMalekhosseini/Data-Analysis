import sys
input = sys.stdin.readline


class RegularNode:
    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None


class SpecialNode:
    def __init__(self):
        self.left = None
        self.right = None


def build_tree(values):
    if not values:
        return None

    root = None
    queue = []

    for value in values:
        if value == '-':
            new_node = SpecialNode()
            # Special nodes should not be added to the queue
        else:
            new_node = RegularNode(int(value))
            if root is None:
                root = new_node

        if queue:
            current = queue[0]
            if current.left is None:
                current.left = new_node
            elif current.right is None:
                current.right = new_node
                # Remove node from queue if both children are assigned
                queue.pop(0)

        if isinstance(new_node, RegularNode):
            queue.append(new_node)

    # After building the tree, add two special nodes to each regular leaf
    add_special_children(root)

    return root


def add_special_children(node):
    if not node:
        return

    # If it's a regular node and both children are None, add two special nodes
    if isinstance(node, RegularNode) and node.left is None and node.right is None:
        node.left = SpecialNode()
        node.right = SpecialNode()
    else:
        add_special_children(node.left)
        add_special_children(node.right)


def is_weighted_path(root, target_sum):
    if not root:
        return False

    def dfs(node, current_sum):
        if not node:
            return False

        current_sum += (0 if isinstance(node, SpecialNode) else node.value)

        # If we reach a special node
        if isinstance(node, SpecialNode):
            return current_sum == target_sum

        return dfs(node.left, current_sum) or dfs(node.right, current_sum)

    return dfs(root, 0)


def main():
    
    tree_values = input().strip().split()

    root = build_tree(tree_values)

    target_sum = int(input().strip())

    if is_weighted_path(root, target_sum):
        print("YES")
    else:
        print("NO")


main()
