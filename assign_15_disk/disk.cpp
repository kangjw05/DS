#include <bits/stdc++.h>

using namespace std;

#define listBlock list<Block>
#define iter listBlock::iterator
#define mp map<string, vector<iter>>
#define REPDISK(i, list) for (auto i = (list).begin(); i != (list).end(); )

struct Block { string name; int start; int size; };

listBlock disk;
mp fileMap;
int capa, freeSpace = 0;

void writeFile(const string& fileName, int fileSize) {
    if(fileMap.count(fileName)) return void(cout << "error\n");
    if(freeSpace < fileSize) return void(cout << "diskfull\n");

    // 한 번에 넣을 수 있는 공간 이는지 확인
    REPDISK(it, disk) {
        if(it->name == "" && it->size >= fileSize){
            // 삽입
            auto newIt = disk.insert(it, {fileName, it->start, fileSize});
            fileMap[fileName].push_back(newIt);         

            // 남은 빈 공간 조정
            it->start += fileSize;
            it->size -= fileSize;
            // 다 넣었으면 종료
            if (it->size == 0) disk.erase(it);
            freeSpace -= fileSize;
            return;
        }
        it++;
    }

    // 한 번에 못넣으면 쪼개서 넣음
    int remain = fileSize;
    REPDISK(it, disk) {
        if(it->name != ""){ ++it; continue; }
        // 넣을 수 있는 크기
        int use = min(remain, it->size);
        // 부분 블록 삽입
        fileMap[fileName].push_back(disk.insert(it, {fileName, it->start, use}));

        // 남은 빈 공간 조정
        it->start += use;
        it->size -= use;
        remain -= use;
        freeSpace -= use;

        if(it->size == 0) it = disk.erase(it);
        else ++it;
    }
}

void deleteFile(const string& fileName) {
    if(!fileMap.count(fileName)) return void(cout << "error\n");

    for (auto &it : fileMap[fileName]){
        freeSpace += it->size;
        it->name = "";
        // 빈 블록 병합 
        auto prevIt = it;
        if(prevIt != disk.begin()){
            --prevIt;
            if (prevIt->name == ""){
                it->start = prevIt->start;
                it->size += prevIt->size;
                disk.erase(prevIt);
            }
        }
        auto nextIt = next(it);
        if(nextIt != disk.end() && nextIt->name == ""){
            it->size += nextIt->size;
            disk.erase(nextIt);
        }
    }

    fileMap.erase(fileName);
}


void showFile (const string& fileName) {
    if(!fileMap.count(fileName)) return void (cout << "error\n");
    // 해당 파일의 블록 시작 주소들
    vector<int> addresses;
    for(auto it : fileMap[fileName]) addresses.push_back(it->start);
    // 주소 오름차순 정렬
    sort(addresses.begin(), addresses.end());
    for(size_t i = 0; i < addresses.size(); i++) 
        cout << (i ? " " : "") << addresses[i];
    cout << "\n";
}

void compact() {
    int pos = 0;
    listBlock newDisk;
    mp newFileMap;

    // 빈 공간 제와하고 새 디스크에 복사
    for(auto it : disk){
        if (it.name == "") continue;
        auto newBlock = newDisk.insert(newDisk.end(), {it.name, pos, it.size});
        newFileMap[it.name].push_back(newBlock);
        pos += it.size;
    }

    // 남은 공간 빈 블록으로 추가
    if(pos < capa) newDisk.push_back({"", pos, capa - pos});

    // 연속된 같은 파일 합치기
    REPDISK(it, newDisk) {
        auto nextIt = next(it);
        if(nextIt != newDisk.end() && it->name == nextIt->name && it->name != ""){
            it->size += nextIt->size;
            newDisk.erase(nextIt);
            newFileMap[it->name].clear();
            newFileMap[it->name].push_back(it);
        } else ++it; // 병합할 거 없으면 넘김
    }

    // 원본 disk, fileMap 갱신
    disk = move(newDisk);
    fileMap = move(newFileMap);
}

int main() {
    cin >> capa;
    // 디스크 초기화
    disk.push_back({"", 0, capa});
    freeSpace = capa;

    string command;
    while (cin >> command && command != "end") {
        if(command[0] == 'w'){
            string fileName; int fileSize;
            cin >> fileName >> fileSize;
            writeFile(fileName, fileSize);
        } else if(command[0] == 'd'){
            string fileName;
            cin >> fileName;
            deleteFile(fileName);
        } else if(command[0] == 's'){
            string fileName;
            cin >> fileName;
            showFile(fileName);
        } else if(command[0] == 'c') compact();
    }

    return 0;
}