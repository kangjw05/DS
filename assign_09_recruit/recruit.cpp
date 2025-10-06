#include <bits/stdc++.h>

#define ALL(x) (x).begin(), (x).end()

using namespace std;

struct Student {
    int id;
    int cote;

    // 1. COTE
    // 2. ID
    bool operator<(const Student& other) const {
        if (cote != other.cote) {
            return cote > other.cote;
        }
        return id > other.id;
    }
};

struct Grad {
    string name;
    int studentCount;
    long long totalCote;

    // 1. 학생 수 
    // 2. COTE 총합
    bool operator<(const Grad& other) const {
        if (studentCount != other.studentCount) {
            return studentCount > other.studentCount;
        }
        return totalCote > other.totalCote;
    }
};


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int N, k;
    cin >> N >> k;

    // 대학별 지원자
    map<string, set<Student>> applicants;

    // 대학 정보
    map<string, pair<int, long long>> gradInfo;

    for (int i = 0; i < N; ++i) {
        string type;
        cin >> type;

        // pop 일 때
        if (type == "POP") {
            int p, q;
            cin >> p >> q;

            // k명 이상 지원한 대학 리스트
            vector<Grad> canGrads;
            for (auto const& [gradName, info] : gradInfo) {
                if (info.first >= k) {
                    canGrads.push_back({gradName, info.first, info.second});
                }
            }

            // 대학 순위 정렬
            sort(ALL(canGrads));

            // 전체 등수 리스트
            vector<Student> finalRank;
            bool studentExists = true;
            // 루프가 면 번 돌아갈지 몰라서 bool 변수로 체크
            for (int rank = 0; studentExists; ++rank) {
                studentExists = false;
                // 각 대학에서 rank 등수 학생 선발
                for (const auto& grad : canGrads) {
                    if (applicants[grad.name].size() > rank) {
                        auto it = applicants[grad.name].begin();
                        // it를 rank만큼 이동시켜 해당 등수 학생을 가리킴
                        advance(it, rank);
                        finalRank.push_back(*it);
                        studentExists = true;
                    }
                }
            }
            
            // p~q 학생 선발 및 출력, DB에서 삭제
            for (int i = p - 1; i < q && i < finalRank.size(); ++i) {
                cout << finalRank[i].id << " ";

                // DB에서 삭제
                for (const auto& grad : canGrads) {
                    auto it = applicants[grad.name].find(finalRank[i]);
                    if (it != applicants[grad.name].end()) {
                        applicants[grad.name].erase(it);
                        gradInfo[grad.name].first--; // 학생 수 감소
                        gradInfo[grad.name].second -= finalRank[i].cote; // COTE 총합 감소
                        break;
                    }
                }
            }
            cout << "\n";
        } else { // 지원자 정보일 때
            string gradName = type;
            int id, cote;
            cin >> id >> cote;

            // 지원자 추가
            Student newStudent = {id, cote};
            applicants[gradName].insert(newStudent);
            
            gradInfo[gradName].first++; // 학생 수 증가
            gradInfo[gradName].second += cote; // COTE 총합 증가
        }
    }

    return 0;
}