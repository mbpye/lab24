#include <iostream>

using namespace std;

struct NodeBST {
    int v; // value
    // поддеревья начального дерева левое и правое соотвественно:
    NodeBST* l;
    NodeBST* r;
    // мн-во листов наз-ся кроной
};

void insert_NodeBST(NodeBST*& root, int val) {
    if (root == NULL) {
        root = new NodeBST;
        root->v = val;
        root->l = NULL;
        root->r = NULL;
        return;
    }
    if (val <= (root->v))
        insert_NodeBST(root->l, val);
    else
        insert_NodeBST(root->r, val);

}

void print_LrootR(NodeBST*& root) {
    if (root == NULL) { return; }
    print_LrootR(root->l);
    cout << root->v << '\n';
    print_LrootR(root->r);
}

void print_rootLR(NodeBST*& root) {
    if (root == NULL) { return; }
    cout << root->v << '\n';
    print_rootLR(root->l);
    print_rootLR(root->r);
}

bool storona = 0;



NodeBST* find_NodeBST(NodeBST* root, int val) {
    if (root == NULL or (root->r == NULL and root->l == NULL)) {
        return NULL;
    }
    if (root->l != NULL and val == root->l->v) {
        storona = 0;
        return root;
    }
    else if (root->r != NULL and val == root->r->v) {
        storona = 1;
        return root;
    }
    if (val < root->v)
        return find_NodeBST(root->l, val);
    else
        return find_NodeBST(root->r, val);
}

void povorot_right(NodeBST*& root, NodeBST* node) {
    if (root == NULL or (root->r == NULL and root->l == NULL)) {
        throw - 1;
    }
    if (node == NULL or (node->r == NULL and node->l == NULL)) {
        throw - 1;
    }
    NodeBST* l1, * l2, * r4;
    l2 = node->l;
    r4 = node->l->r;
    if (node != root) {
        NodeBST* glavn = find_NodeBST(root, node->v);
        if (storona) {
            glavn->r = l2;
        }
        else {
            glavn->l = l2;
        }
    }
    else {
        root = l2;
    }
    node->l->r = node;
    node->l = r4;
}

void povorot_left(NodeBST*& root, NodeBST* node) {
    if (root == NULL or root->r == NULL) {
        throw - 1;
    }
    if (node == NULL or node->r == NULL) {
        throw - 1;
    }
    NodeBST* r1, * r2, * l4;
    r2 = node->r;
    l4 = node->r->l;
    if (node != root) {
        NodeBST* glavn = find_NodeBST(root, node->v);
        if (storona) {
            glavn->r = r2;
        }
        else {
            glavn->l = r2;
        }
    }
    else {
        root = r2;
    }
    node->r->l = node;
    node->r = l4;
}

NodeBST* find_NodeBST_v1(NodeBST* root, int val) {
    if (root == NULL) {
        return NULL;
    }
    if (val == root->v) {
        return root;
    }
    if (val < root->v)
        return find_NodeBST_v1(root->l, val);
    else
        return find_NodeBST_v1(root->r, val);
}

int depth(NodeBST* head) {
    int cnt = 0;
    if (head == NULL) { return cnt; }
    cnt += 1;
    cnt += max(depth(head->l), depth(head->r));
    return cnt;
}

bool balanced(NodeBST* head) {
    bool ans = true;
    if (head == NULL) { return true; }
    if (abs(depth(head->l) - depth(head->r)) > 1) {
        return false;
    }
    if (!(balanced(head->l) and balanced(head->r))) {
        ans = false;
    }
    return ans;
}

void balance_BST(NodeBST*& root, NodeBST* head) {
    if (balanced(head)) { return; }
    if (!(balanced(head->l) or balanced(head->r))) {
        balance_BST(root, head->l);
        balance_BST(root, head->r);
    }
    else if (!balanced(head->l)) {
        balance_BST(root, head->l);
    }
    else if (!balanced(head->r)) {
        balance_BST(root, head->r);
    }
    else {

        if (depth(head->l) < depth(head->r)) {
            if (depth(head->r->l) > depth(head->r->r)) {
                povorot_right(root, head->r);
            }
            povorot_left(root, head);
        }
        else {
            if (depth(head->l->l) < depth(head->l->r)) {
                povorot_left(root, head->l);
            }
            povorot_right(root, head);
        }
    }
}

int min_depth(NodeBST* head) {
    int cnt = 0;
    if (head == NULL) { return head->v; }
    cnt += 1;
    cnt += min(depth(head->l), depth(head->r));
    return cnt;
}

int min_depth_leaf(NodeBST* head, int lvl, int min_dep) {
    if (head == NULL) { return 0; }
    if (head->l == NULL and head->r == NULL and depth(head) + lvl == min_dep) { return head->v; }
    ++lvl;
    if (min_depth_leaf(head->l, lvl, min_dep)) {
        return min_depth_leaf(head->l, lvl, min_dep);
    }
    else if (min_depth_leaf(head->r, lvl, min_dep)) {
        return min_depth_leaf(head->r, lvl, min_dep);
    }
}

int width(NodeBST* head) {
    if (head == NULL) { return 0; }
    if (head->l == NULL and head->r == NULL) { return 1; }
    return (width(head->l) + width(head->r));
}

int listia(NodeBST* head, int a, int b, int& c) {
    if (head == NULL) { return 0; }
    if (head->l == NULL and head->r == NULL) {
        if (head->v < a or head->v > b) {
            c = 0;
        }
    }
    listia(head->l, a, b, c);
    listia(head->r, a, b, c);
    return c;
}

int main() {
    NodeBST* tree = NULL;
    insert_NodeBST(tree, 2);
    insert_NodeBST(tree, 10);
    insert_NodeBST(tree, 6);
    insert_NodeBST(tree, 7);
    insert_NodeBST(tree, 11);
    insert_NodeBST(tree, -4);
    insert_NodeBST(tree, 5);
    int l, r, c = 1;
    cout << "Enter diaposon:";
    cin >> l >> r;
    if (listia(tree, l, r, c) != 0) {
        cout << "Good";
    }
    else {
        cout << "Bad";
    }
}
