#include <bits/stdc++.h>
using namespace std;

struct NodeInfo {
    string name;
    int descendantCount = 0;
    int depth = 0;
};

// key : 부모, value : 자식 벡터
map<string, vector<string>> tree;

vector<NodeInfo> nodeInfos;

int countDescendatns(const string& node, int currendDepth) {
    int cnt = 0;
    // 현재 노드가 key로 존재하는지 확인 (자식 있는지)
    if (tree.find(node) != tree.end()) {
        // 현재 노드의 직계 자식 순회
        for (const string& child : tree.at(node)) {
            // recursive하게 자식들 수 셈 + 깊어질 때마다 depth 추가
            cnt += (1 + countDescendatns(child, currendDepth + 1));
        }
    }

    nodeInfos.push_back({node, cnt, currendDepth});

    return cnt;
}

string findRoot (const set<string>& allNodes, const set<string>& allChildren) {
    for(const string& node : allNodes) {
        if (allChildren.count(node) == 0) return node;
    }
}

int main() {
    int N;
    cin >> N;
    set<string> allNodes;
    set<string> allChildren;
    while(N--) {
        string child, parent;
        cin >> child >> parent;

        tree[parent].push_back(child);

        allNodes.insert(child);
        allNodes.insert(parent);
        allChildren.insert(child);
    }
    string root = findRoot(allNodes, allChildren);

    countDescendatns(root, 0);

    sort(nodeInfos.begin(), nodeInfos.end(), [](const NodeInfo& a, const NodeInfo& b) {
        if(a.descendantCount != b.descendantCount) return a.descendantCount > b.descendantCount;
        if(a.depth != b.depth) return a.depth < b.depth;
        return a.name < b.name;
    });

    for(const auto& info : nodeInfos) {
        cout << info.name << '\n';
    }

    return 0;
}