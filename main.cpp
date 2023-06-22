#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <stdexcept>

class Sudoku {
public:
    int SIZE = 9;
    int UNASSIGNED = 0;

    Sudoku() : grid(SIZE, std::vector<int>(SIZE, UNASSIGNED)) {}

    bool solve() {
        int row, col;

        if (!findUnassignedLocation(row, col)) {
            return true;
        }

        for (int num = 1; num <= SIZE; ++num) {
            if (isSafe(row, col, num)) {
                grid[row][col] = num;

                if (solve()) {
                    return true;
                }

                grid[row][col] = UNASSIGNED;
            }
        }
        return false;
    }

    void generate(int holes, bool unique, int difficulty) {
        //std::random_device rd;
        //std::mt19937 gen(rd());
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(1, SIZE);

        Sudoku tmp;
        std::fill(tmp.grid.begin(), tmp.grid.end(), std::vector<int>(SIZE, UNASSIGNED));
        for (int i = 0; i < SIZE * difficulty; ++i) {
            int row = dist(gen) - 1;
            int col = dist(gen) - 1;
            int num = dist(gen);

            if (tmp.grid[row][col] == UNASSIGNED && tmp.isSafe(row, col, num)) {
                tmp.grid[row][col] = num;
            }
        }

        if (!tmp.solve()) {
            generate(holes, unique, difficulty);
            return;
        }

        *this = tmp;

        std::uniform_int_distribution<> holeDist(0, SIZE - 1);
        for (int i = 0; i < holes; ++i) {
            int row = holeDist(gen);
            int col = holeDist(gen);

            if (grid[row][col] != UNASSIGNED) {
                grid[row][col] = UNASSIGNED;
            } else {
                --i;
            }
        }

        if (unique) {
            Sudoku tmp2(*this);
            if (!tmp2.solve()) {
                generate(holes, unique, difficulty);
            }
        }
    }

    void loadFromFile(const std::string &filename) {
        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Error: Cannot open file.");
        }

        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                file >> grid[row][col];
            }
        }
    }

    bool loadFromMatrix(const std::vector<std::vector<int>>& matrix) {
        if (matrix.size() != 9 || matrix[0].size() != 9) {
            return false;
        }
        grid = matrix;
        return true;
    }

    void saveToFile(const std::string &filename) const {
        std::ofstream file(filename, std::ios::app);
        if (!file) {
            throw std::runtime_error("Error: Cannot open file.");
        }

        for (int row = 0; row < SIZE; ++row) {
            for (int col = 0; col < SIZE; ++col) {
                file << grid[row][col] << (col == SIZE - 1 ? '\n' : ' ');
            }
        }
        file << "\n";
    }

private:
    std::vector<std::vector<int>> grid;

    bool findUnassignedLocation(int &row, int &col) {
        for (row = 0; row < SIZE; ++row) {
            for (col = 0; col < SIZE; ++col) {
                if (grid[row][col] == UNASSIGNED) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isSafe(int row, int col, int num) {
        return !usedInRow(row, num) && !usedInCol(col, num) && !usedInBox(row - row % 3, col - col % 3, num);
    }

    bool usedInRow(int row, int num) {
        return std::find(grid[row].begin(), grid[row].end(), num) != grid[row].end();
    }

    bool usedInCol(int col, int num) {
        return std::any_of(grid.begin(), grid.end(), [col, num](const std::vector<int> &row) {
            return row[col] == num;
        });
    }

    bool usedInBox(int boxStartRow, int boxStartCol, int num) {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                if (grid[row + boxStartRow][col + boxStartCol] == num) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw std::runtime_error("Error: Insufficient arguments.");
        }

        int generatedCount = 0;
        int holes = 0;
        bool unique = false;
        int difficulty = 1;
        bool generateMode = false;
        bool solveMode = false;
        std::string inputFile;
        std::string outputFile = "sudoku_output.txt";
        std::string answerFile = "sudoku_ans.txt";

        for (int i = 1; i < argc; ++i) {
            std::string arg(argv[i]);

            if (arg == "-c") {
                if (i + 1 < argc) {
                    generatedCount = std::stoi(argv[++i]);
                    generateMode = true;
                } else {
                    throw std::runtime_error("Error: Missing argument for '-c'.");
                }
            } else if (arg == "-s") {
                if (i + 1 < argc) {
                    inputFile = argv[++i];
                    solveMode = true;
                } else {
                    throw std::runtime_error("Error: Missing argument for '-s'.");
                }
            } else if (arg == "-n") {
                if (i + 1 < argc) {
                    generatedCount = std::stoi(argv[++i]);
                    generateMode = true;
                } else {
                    throw std::runtime_error("Error: Missing argument for '-n'.");
                }
            } else if (arg == "-m") {
                if (i + 1 < argc) {
                    difficulty = std::stoi(argv[++i]);
                    if (difficulty < 1 || difficulty > 3) {
                        throw std::runtime_error("Error: Difficulty must be between 1 and 3.");
                    }
                } else {
                    throw std::runtime_error("Error: Missing argument for '-m'.");
                }
            } else if (arg == "-r") {
                if (i + 1 < argc) {
                    holes = std::stoi(argv[++i]);
                } else {
                    throw std::runtime_error("Error: Missing argument for '-r'.");
                }
            } else if (arg == "-u") {
                unique = true;
            } else {
                throw std::runtime_error("Error: Invalid argument.");
            }
        }

        if (generateMode) {
            std::ofstream file(outputFile);
            if (!file) {
                throw std::runtime_error("Error: Cannot open output file.");
            }
            file.close();

            Sudoku sudoku;
            for (int i = 0; i < generatedCount; ++i) {
                sudoku.generate(holes, unique, difficulty);
                sudoku.saveToFile(outputFile);
            }
        }

        if (solveMode) {
            // Sudoku sudoku;
            // sudoku.loadFromFile(inputFile);
            // if (sudoku.solve()) {
            //     sudoku.saveToFile(answerFile);
            // } 
            // else {
            //     throw std::runtime_error("Error: Failed to solve the Sudoku puzzle.");
            // }
            
            std::ifstream file(inputFile.c_str());
            if (!file) {
                std::cerr << "Error: Cannot open input file." << std::endl;
                return 1;
            }
            
            const int numRows = 9;
            const int numCols = 9;
            std::vector<std::vector<int>> inputMatrix;
            std::vector<std::vector<std::vector<int>>> inputMatrices;
            while (true) {
                inputMatrix.clear();
                for (int i = 0; i < numRows; i++) {
                    std::vector<int> row;
                    for (int j = 0; j < numCols; j++) {
                        int value;
                        if (file >> value) {
                            row.push_back(value);
                        } else {
                            break;
                        }
                    }
                    if (row.size() == numCols) {
                        inputMatrix.push_back(row);
                    } else {
                        break;
                    }
                }
                if (inputMatrix.empty()) {
                    break;
                }
                inputMatrices.push_back(inputMatrix);
            }

            for (const auto& inputMatrix : inputMatrices) {
                Sudoku sudoku;
                if (sudoku.loadFromMatrix(inputMatrix)) {
                    if (sudoku.solve()) {
                        std::vector<std::vector<int>> answerMatrix;
                        sudoku.saveToFile(answerFile);
                    } else {
                        throw std::runtime_error("Error: Failed to solve the Sudoku puzzle.");
                    }
                } else {
                    throw std::runtime_error("Error: Invalid Input.");
                }
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
