#include <bits/stdc++.h>

using namespace std;
// insert에서 노드를 만들어서 연결하거나 재귀 호출
#define MOVE(DIR) \
    if (cur->DIR == nullptr) { \
        cur->DIR = new Node(val); \
        cur->DIR->par = cur; \
    } else _insert(cur->DIR, val)

// Node 구조체. 부모, left, right, string 값을 저장함
struct Node {
    string val;
    Node *par = nullptr, *left = nullptr, *right = nullptr;
    Node(string v) : val(v){}
};
// Bin tree class
class BTS {
    Node* root;
public:
    BTS():root(nullptr) {}
    // 호출용 insert 메소드. root가 비어있으면 root 생성, val을 넣음
    void insert(string val) {
        if (root == nullptr) root = new Node(val);
        // root가 아니면 재귀 호출용 private 함수로 넘어감
        else _insert(root, val);
    }
    // 호출용 erase 메소드
    void erase(string val) {
        // finder로 위치를 찾고 null이 아니면 재귀용 _erase 함수로 노드를 넘김
        Node* cur = finder(root, val);
        if (cur) _erase(cur);
    }
    // finder 메소드
    Node* finder(Node* cur, string val) {
        // cur이 NULL이거나 cur의 value가 찾으려는 value와 같으면 cur을 return
        if (!cur || cur->val == val) return cur;
        // 만약에 val 값이 cur->val과 같지 않으면 val의 크기를 cur의 val 크기랑 비교해서 left 또는 right로 이동, 재귀적 호출
        return (cur->val > val) ? finder(cur->left, val) : finder(cur->right, val);
    }
    // _getLeaf로 루트부터 recursive하게 leaf 노드를 찾음
    void getLeaf() { _getLeaf(root); cout << "\n"; }
    // cnt로 찾은 노드의 수를 세면서 _getDepth로 recursive하게 노드 찾음
    void getDepth(int targetDepth) { 
        int cnt = 0;
        _getDepth(root, 1, targetDepth, cnt); 
        // 하나도 못찾으면 cnt == 0, NO를 출력
        if (cnt == 0) cout << "NO";
        cout << "\n"; 
    }
private:
    // erase 메소드에서 필요한 _getMin
    Node* _getMin(Node* node) {
        // 노드들의 left를 타고 null이 될 때까지 내려감
        while (node->left) node = node->left;
        return node;
    }
    // erase 메소드에서 필요한 _getMax
    Node* _getMax(Node* node) {
        // 노드들의 right를 타고 null이 될 때까지 내려감
        while (node->right) node = node->right;
        return node;
    }
    // 재귀 호출용 _insert 함수
    void _insert(Node* cur, string val) {
        // val이 cur의 val보다 크면 right로 이동
        if (val > cur->val) MOVE(right); 
        // 아니면 left로 이동
        else MOVE(left);
    }
    // 삭제하려는 node가 내부인지 leaf인지 판단, 삭제하는 함수
    void _erase(Node* cur) {
        // left subtree가 있으면
        if (cur->left != nullptr) {
            // left의 최댓값을 찾아서
            Node* successor = _getMax(cur->left);
            // 현재 val을 최댓값의 val로 바꿈
            cur->val = successor->val;
            // successor을 _erase에 넣어서 삭제 (successor은 최댓값 = leaf여서 지워짐)
            _erase(successor);
            return;
        }
        // 만약 left subtree가 없고 right는 있으면
        else if (cur->right != nullptr) {
            // right의 최솟값을 찾아서
            Node* successor = _getMin(cur->right);
            // 현재 val을 최솟값의 val로 바꿈
            cur->val = successor->val;
            // successor을 _erase에 넣어서 삭제 (successor은 최솟값 = leaf여서 지워짐)
            _erase(successor);
            return;
        } else { // 둘 다 없다 = leaf임
            // 부모 있는지 확인
            if (cur->par != nullptr) {
                // 있을 때 현재 노드가 부모의 왼쪽이면 왼쪽을 nullptr로 바꿔줌
                if (cur->par->left == cur) cur->par->left = nullptr;
                // 오른쪽이면 부모의 오른쪽 포인터를 null로 바꿈
                else cur->par->right = nullptr;
            } else root = nullptr; // 부모 없으면 걍 루트를 null로
        }
        delete cur; // 현재 노드 삭제
    }
    // inorder로 순회하면서 leaf 찾고 출력하는 함수 -> inorder로 순회하면 알아서 사전순으로 나옴
    void _getLeaf(Node* cur) {
        if (!cur) return; // 노드가 null이면 걍 return
        // 왼쪽 먼저 순회 (왼쪽 subtree의 leaf 부터 출력 됨)
        _getLeaf(cur->left);
        // 현재 leaf 출력
        if(!cur->left && !cur->right) cout << cur->val << " ";
        // 오른쪽 순회
        _getLeaf(cur->right);
    }
    // preorder로 순회하면서 targetDepth에 있는 노드들 출력, cnt 참조로 getDepth의 cnt++
    void _getDepth(Node* cur, int curDepth, int targetDepth, int& cnt) {
        // cur가 null이거나 curDepth가 targetDepth보다 크면 (= 넘어갔다는 말) return
        if (!cur || curDepth > targetDepth) return;
        // 현재 깊이가 타겟이랑 같으면 노드의 val 출력
        if (curDepth == targetDepth) {
            cout << cur->val << " ";
            cnt++;
            // 이미 도달했으면 밑에는 더 볼 필요가 없으니까 return
            return;
        }
        // left 순회
        _getDepth(cur->left, curDepth + 1, targetDepth, cnt);
        // right 순회
        _getDepth(cur->right, curDepth + 1, targetDepth, cnt);
        // depth라는 조건이 있기 때문에 preorder로 찾아도 사전순으로 나옴 (부모 노드는 짜피 깊이 안맞아서 무시되니까)
    }
};

int main() {
    BTS binTree;
    string input;
    while (cin>>input && input != "quit") {
        if (input == "+") {
            string str;
            cin >> str;
            binTree.insert(str);
        }
        else if (input == "-"){ 
            string str;
            cin >> str;
            binTree.erase(str);}
        else if (input == "leaf") binTree.getLeaf();
        else if (input == "depth") {
            int k;
            cin >> k;
            binTree.getDepth(k);
        }
    }

    return 0;
}