#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    int n;
    cin >> n;
    // key: 입찰가, value: 입찰가를 제시한 사람들
    map<int, vector<string>> bidders;
    for(int i = 0; i < n; i++) {
        string name;
        int price;
        cin >> name >> price;
        bidders[price].push_back(name);
        // price key 값의 백터에 이름 추가
    }

    string result = "NONE";
    // map에 입력 = key 기준 오름차순 정렬
    // rbegin으로 가장 큰 key값부터 확인 = 입찰가가 높은 곳 부터
    for(auto iter = bidders.rbegin(); iter != bidders.rend(); iter++) {
        // 해당 가격의 value 크기가 1 = 입찰자가 한 명
        if(iter->second.size() == 1) {
            result = iter->second[0]; // 그 사람을 result로 업데이트
            break;
        }
    }

    cout << result << endl;

    return 0;
}