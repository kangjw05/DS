#include <bits/stdc++.h>
#define REP(i,n) for(int i=0;i<n;i++)

using namespace std;

void callFunction(char func, unordered_map<char, vector<string>>& inputs, vector<string>& sequence, set<char>& activeCalls) {
    // 현재 함수를 목록에 추가
    activeCalls.insert(func);

    for (const auto& act : inputs.at(func)) {
        if (act.length() == 1) {
            char nextFunc = act[0];
            // 이미 호출된 함수면 DEADLOCK 출력 후 종료
            if (activeCalls.count(nextFunc)) {
                cout << "DEADLOCK" << endl;
                exit(0);
            }
            // 아니면 재귀
            callFunction(nextFunc, inputs, sequence, activeCalls);
        } else sequence.push_back(act);
    }

    // 현재 함수의 실행이 끝나면 호출된 함수 목록에서 제거
    activeCalls.erase(func);
}

void printResult(int k, const vector<string>& sequence) {
    int totalSize = sequence.size();
    int idx;
    
    // k가 양수면 k-1, 음수면 전체 크기 + k
    if (k > 0) idx = k - 1;
    else idx = totalSize + k;

    // 계산한 idx가 범위 내면 출력, 아니면 NONE
    if (idx >= 0 && idx < totalSize) cout << sequence[idx] << endl;
    else cout << "NONE" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, k1, k2;
    cin >> N >> k1 >> k2;

    unordered_map<char, vector<string>> inputs;

    REP(i, N) {
        char func;
        cin >> func;
        string token;
        // $ 나오기 전까지 입력
        while(cin >> token && token != "$") {
            // 입력이 대문자 한글자(함수)면 그냥 넣음
            if(token.length() == 1 && isupper(token[0])) inputs[func].push_back(token);
            // 아니면 F-act 형식으로
            else inputs[func].push_back(string(1, func) + "-" + token);
        }
    }

    vector<string> callStack;
    set<char> callFunctionSet; // 현재 호출 중인 함수들 추적
    callFunction('M', inputs, callStack, callFunctionSet);

    printResult(k1, callStack);
    printResult(k2, callStack);

    return 0;
}