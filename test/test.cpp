#include <iostream>
#include <cstdlib>
#include <ctime>

// 生成1到100之间的随机整数
int getRandomNumber() {
    return rand() % 100 + 1;
}

// 生成随机的绝对或相对路径
std::string getRandomPath() {
    std::string path;
    int r = getRandomNumber();
    path = "file.txt" + std::to_string(r);
    return path;
}

// 生成测试样例
void generateTestCases() {
    // 生成测试样例数量
    int numTestCases = getRandomNumber() % 1000 + 1;
    
    for (int i = 0; i < numTestCases; i++) {
        // 随机选择参数
        int parameter = getRandomNumber() % 5;
        
        switch (parameter) {
            case 0:  // -c 参数
                std::cout << "sudoku.exe -c " << getRandomNumber() % 1000000 + 1 << std::endl;
                break;
            case 1:  // -s 参数
                std::cout << "sudoku.exe -s " << getRandomPath() << std::endl;
                break;
            case 2:  // -n 参数
                std::cout << "sudoku.exe -n " << getRandomNumber() % 10000 + 1 << std::endl;
                break;
            case 3:  // -m 参数
                std::cout << "sudoku.exe -n " << getRandomNumber() % 10000 + 1 << " -m " << getRandomNumber() % 3 + 1 << std::endl;
                break;
            case 4:  // -r 参数
                std::cout << "sudoku.exe -n " << getRandomNumber() % 10000 + 1 << " -r " << getRandomNumber() % 36 + 20 << "~" << getRandomNumber() % 20 + 36 << std::endl;
                break;
            case 5:  // -u 参数
                std::cout << "sudoku.exe -n " << getRandomNumber() % 10000 + 1 << " -u" << std::endl;
                break;
            default:
                break;
        }
    }
}

int main() {
    // 使用当前时间作为随机数种子
    srand(static_cast<unsigned>(time(0)));
    
    // 生成测试样例
    generateTestCases();
    
    return 0;
}
