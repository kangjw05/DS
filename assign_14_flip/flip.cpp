#include <bits/stdc++.h>

using namespace std;

int main() {
    long long N;
    int K;
    cin >> N >> K;
    // key: 인덱스, value: 해당 좌표에서 값이 바뀐 횟수
    // map으로 정의해서 나중에 인덱스 순서대로 정리됨
    map<long long, int> points;
    
    for(int k = 0; k < K; k++) {
        long long i, j;
        cin >> i >> j;
        // i 인덱스에서 flip 시작했다고 표시
        points[i]++;
        // j+1 인덱스에서 flip 종료됐다고 표시
        points[j+1]--;
    }
    long long R = 0, W = 0;

    // 이전 위치
    long long prev = 0;
    // 현재 구간에서 적용된 flip 누적 횟수
    int flipCnt = 0;
    // 바로 이전 구간이 1이었는지
    bool isRun = false;

    for(auto const& [pos, val] : points) {
        //길이가 1 이상인 구간에서만 실행
        if (prev < pos) {
            // flipCnt가 홀수 = 1인 상태
            if (flipCnt % 2 != 0) {
                // 이전 구간이 0이었으면 새로운 run 시작
                if (!isRun) R++;
                // prev ~ pos 까지의 범위는 전부 1이니까 
                // pos - prev만큼 1이 있음
                W += pos-prev;
                // 1이니까 isRun을 true로 바꿈
                isRun = true;
            } else isRun = false;
        }
        // 현재 좌표에서 flip 상태 업데이트
        flipCnt += val;
        prev = pos;
    }

    // 마지막 구간 [마지막 좌표, N-1] 처리
    if (prev < N) {
        if (flipCnt % 2 != 0) {
            if (!isRun) R++;
            W += N-prev;
        }
    }

    cout << R << " " << W;

    return 0;
}