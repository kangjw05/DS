#include <bits/stdc++.h>

using namespace std;

#define REP(i, j, k) for(int i = j; i < k; ++i)

int K;
string TOKEN;
vector<string> IMAGE;
string QTS_STRING;

// r (행), c (열), 크기, 이터레이터를 받아서 IMAGE 벡터에 디코드
void decode(int r, int c, int size, string::iterator& it){
    char curChar = *it;

    if (curChar == '0' || curChar == '1'){
        char color = curChar;
        REP(i, r, r + size){
            REP(j, c, c + size){
                IMAGE[i][j] = color;
            }
        }
        ++it;
    } else if (curChar == '(') {  // 여는 괄호면 새로운 브랜치
        ++it;
        int newSize = size/2; // 브랜치로 갈라졌으니까 한 변의 길이가 반이 됨

        decode(r, c+newSize, newSize, it); // 1사분면 
        decode(r, c, newSize, it); // 2사분면
        decode(r+newSize, c, newSize, it); // 3사분면 
        decode(r+newSize, c+newSize, newSize, it); // 4사분면 

        ++it; // 닫히는 괄호 '(' 넘기기
    }
}

bool is_homogeneous(int r, int c, int size) {
    if (size == 0) return true;
    char first_color = IMAGE[r][c];
    REP(i, r, r + size){
        REP(j, c, c + size){
            if (IMAGE[i][j] != first_color){
                return false; // 다른 색 발견
            }
        }
    }
    return true; // 모두 같은 색
}

string encode(int r, int c, int size) {
    if (size == 1) {
        return string(1, IMAGE[r][c]);
    }

    if (is_homogeneous(r, c, size)) {
        return string(1, IMAGE[r][c]); // '0' 또는 '1' 반환
    }
    int newSize = size/2; // 색이 섞여있는 경우 노드 나눠짐
    
    string qt1 = encode(r, c+newSize, newSize);
    string qt2 = encode(r, c, newSize);
    string qt3 = encode(r+newSize, c, newSize);
    string qt4 = encode(r+newSize, c+newSize, newSize);

    return "(" + qt1 + qt2 + qt3 + qt4 + ")";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K >> TOKEN;
    int size = 1 << K; // 2^K

    if (TOKEN == "IMG") {
        IMAGE.resize(size, string(size, ' '));
        REP(i, 0, size) cin >> IMAGE[i];
        string qts_result = encode(0, 0, size);
        cout << qts_result << '\n';
    } else if (TOKEN == "QTS") {
        IMAGE.resize(size, string(size, ' '));
        cin >> QTS_STRING;
        string::iterator it = QTS_STRING.begin();
        decode(0, 0, size, it);
        REP(i, 0, size) cout << IMAGE[i] << '\n';
    }

    return 0;
}