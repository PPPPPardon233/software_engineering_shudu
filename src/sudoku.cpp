#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <string>
#include <sstream>
#include <stdexcept>
#include <set>

// To store hash of Sudoku puzzles to ensure uniqueness
std::set<std::string> hashSet;

class Sudoku
{
public:
    int SIZE = 9;
    int UNASSIGNED = -1;

    // Constructor
    Sudoku() : grid(SIZE, std::vector<int>(SIZE, UNASSIGNED)) {}

    // Calculate hash based on grid values
    std::string hash() const
    {
        std::stringstream ss;
        for (int row = 0; row < SIZE; ++row)
        {
            for (int col = 0; col < SIZE; ++col)
            {
                ss << grid[row][col];
            }
        }
        return ss.str();
    }

    // Solve Sudoku using backtracking
    bool solve()
    {
        int row, col;

        if (!findUnassignedLocation(row, col))
        {
            return true;
        }

        for (int num = 1; num <= SIZE; ++num)
        {
            if (isSafe(row, col, num))
            {
                grid[row][col] = num;

                if (solve())
                {
                    return true;
                }

                grid[row][col] = UNASSIGNED;
            }
        }
        return false;
    }

    // Generate a unique Sudoku puzzle with given number of holes and difficulty
    void generateUnique(int holes, int difficulty)
    {
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(1, SIZE);

        while (true)
        {
            Sudoku tmp;
            std::fill(tmp.grid.begin(), tmp.grid.end(), std::vector<int>(SIZE, UNASSIGNED));
            for (int i = 0; i < SIZE * difficulty; ++i)
            {
                int row = dist(gen) - 1;
                int col = dist(gen) - 1;
                int num = dist(gen);

                if (tmp.grid[row][col] == UNASSIGNED && tmp.isSafe(row, col, num))
                {
                    tmp.grid[row][col] = num;
                }
            }

            std::string hashStr = tmp.hash();

            if (!tmp.solve())
            {
                continue;
            }

            if (hashSet.count(hashStr) == 0)
            {
                hashSet.insert(hashStr);
            }
            else
            {
                continue;
            }

            *this = tmp;

            std::uniform_int_distribution<> holeDist(0, SIZE - 1);
            std::vector<std::pair<int, int>> holesToClear;
            for (int i = 0; i < holes; ++i)
            {
                int row = holeDist(gen);
                int col = holeDist(gen);

                if (grid[row][col] != UNASSIGNED)
                {
                    holesToClear.emplace_back(row, col);
                }
                else
                {
                    --i;
                }
            }

            bool unique = true;
            for (const auto &hole : holesToClear)
            {
                int row = hole.first;
                int col = hole.second;
                //int temp = grid[row][col];
                grid[row][col] = UNASSIGNED;

                Sudoku tmp2(*this);
                std::vector<std::vector<int>> tmpGrid = tmp2.grid;

                bool multipleSolutions = false;
                for (int r = 0; r < SIZE; ++r)
                {
                    for (int c = 0; c < SIZE; ++c)
                    {
                        if (tmp2.grid[r][c] != tmpGrid[r][c])
                        {
                            multipleSolutions = true;
                            break;
                        }
                    }
                    if (multipleSolutions)
                        break;
                }
                if (multipleSolutions)
                {
                    unique = false;
                    break;
                }
            }

            if (unique)
            {
                return;
            }
        }
    }

    // Generate a Sudoku puzzle with given number of holes and difficulty
    void generate(int holes, int difficulty)
    {
        std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<> dist(1, SIZE);

        Sudoku tmp;
        std::fill(tmp.grid.begin(), tmp.grid.end(), std::vector<int>(SIZE, UNASSIGNED));
        for (int i = 0; i < SIZE * difficulty; ++i)
        {
            int row = dist(gen) - 1;
            int col = dist(gen) - 1;
            int num = dist(gen);

            if (tmp.grid[row][col] == UNASSIGNED && tmp.isSafe(row, col, num))
            {
                tmp.grid[row][col] = num;
            }
        }

        std::string hashStr = tmp.hash();

        if (!tmp.solve())
        {
            generate(holes, difficulty);
            return;
        }
        if (hashSet.count(hashStr) == 0)
        {
            hashSet.insert(hashStr);
        }
        else
        {
            generate(holes, difficulty);
            return;
        }
        *this = tmp;

        std::uniform_int_distribution<> holeDist(0, SIZE - 1);
        std::vector<std::pair<int, int>> holesToClear;
        std::set<std::pair<int, int>> holeSet;
        for (int i = 0; i < holes; ++i)
        {
            int row = holeDist(gen);
            int col = holeDist(gen);
            std::pair<int, int> currHole;
            currHole.first = row;
            currHole.second = col;
            if (holeSet.count(currHole) == 0)
            {
                holesToClear.emplace_back(row, col);
                holeSet.insert(currHole);
            }
            else
            {
                --i;
            }
        }

        for (const auto &hole : holesToClear)
        {
            int row = hole.first;
            int col = hole.second;
            //int temp = grid[row][col];
            grid[row][col] = UNASSIGNED;
        }
    }

    // Load grid from 2D matrix
    bool loadFromMatrix(const std::vector<std::vector<int>> &matrix)
    {
        if (matrix.size() != 9 || matrix[0].size() != 9)
        {
            return false;
        }
        grid = matrix;
        return true;
    }

    // Save grid to file
    void saveToFile(const std::string &filename) const
    {
        std::ofstream file(filename, std::ios::app);
        if (!file)
        {
            throw std::runtime_error("Error: Cannot open file.");
        }

        for (int row = 0; row < SIZE; ++row)
        {
            for (int col = 0; col < SIZE; ++col)
            {
                if (grid[row][col] != UNASSIGNED)
                    file << grid[row][col] << (col == SIZE - 1 ? '\n' : ' ');
                else
                    file << '$' << (col == SIZE - 1 ? '\n' : ' ');
            }
        }
        file << "\n";
    }

private:
    // Sudoku grid
    std::vector<std::vector<int>> grid;

    // Find next unassigned location
    bool findUnassignedLocation(int &row, int &col)
    {
        for (row = 0; row < SIZE; ++row)
        {
            for (col = 0; col < SIZE; ++col)
            {
                if (grid[row][col] == UNASSIGNED)
                {
                    return true;
                }
            }
        }
        return false;
    }

    // Check if assignment is safe
    bool isSafe(int row, int col, int num)
    {
        return !usedInRow(row, num) && !usedInCol(col, num) && !usedInBox(row - row % 3, col - col % 3, num);
    }

    // Check if number used in row
    bool usedInRow(int row, int num)
    {
        return std::find(grid[row].begin(), grid[row].end(), num) != grid[row].end();
    }

    // Check if number used in column
    bool usedInCol(int col, int num)
    {
        return std::any_of(grid.begin(), grid.end(), [col, num](const std::vector<int> &row)
                           { return row[col] == num; });
    }

    // Check if number used in 3x3 box
    bool usedInBox(int boxStartRow, int boxStartCol, int num)
    {
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                if (grid[row + boxStartRow][col + boxStartCol] == num)
                {
                    return true;
                }
            }
        }
        return false;
    }
};

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
        {
            throw std::runtime_error("Error: Insufficient arguments.");
        }

        int generatedCount = 0;
        int holes = 0;
        bool unique = false;
        int difficulty = 1;
        bool generateMode = false;
        bool solveMode = false;
        bool nMode = false;
        std::string inputFile;
        std::string outputFile = "sudoku.txt";
        std::string answerFile = "sudoku_ans.txt";

        /************************************************************************************
         * List of supported parameters
         * -c $numOfSudokuFinal(1-1000000)$
         * -s $pathOfSudokuProblem$
         * -n $numOfSudokuProblem(1-10000)$
         * -n $numOfSudokuProblem(1-10000)$ -m $difficulty(1-3)$
         * -n $numOfSudokuProblem(1-10000)$ -r $numOfHoles(20-55)$
         * -n $numOfSudokuProblem(1-10000)$ -u
         ************************************************************************************/

        for (int i = 1; i < argc; ++i)
        {
            std::string arg(argv[i]);

            if (arg == "-c")
            {
                if (i + 1 < argc)
                {
                    generatedCount = std::stoi(argv[++i]);
                    generateMode = true;
                }
                else
                {
                    throw std::runtime_error("Error: Missing argument for '-c'.");
                }
            }
            else if (arg == "-s")
            {
                if (i + 1 < argc)
                {
                    inputFile = argv[++i];
                    solveMode = true;
                }
                else
                {
                    throw std::runtime_error("Error: Missing argument for '-s'.");
                }
            }
            else if (arg == "-n")
            {
                if (i + 1 < argc)
                {
                    generatedCount = std::stoi(argv[++i]);
                    generateMode = true;
                    nMode = true;
                    holes = 20;
                }
                else
                {
                    throw std::runtime_error("Error: Missing argument for '-n'.");
                }
            }
            else if (arg == "-m")
            {
                if (!nMode)
                {
                    throw std::runtime_error("Error: Parameter m must be used with parameter n.");
                }
                if (i + 1 < argc)
                {
                    difficulty = std::stoi(argv[++i]);
                    if (difficulty < 1 || difficulty > 3)
                    {
                        throw std::runtime_error("Error: Difficulty must be between 1 and 3.");
                    }
                    switch (difficulty)
                    {
                    case 1:
                        holes = 20;
                        break;
                    case 2:
                        holes = 25;
                        break;
                    default:
                        holes = 30;
                        break;
                    }
                }
                else
                {
                    throw std::runtime_error("Error: Missing argument for '-m'.");
                }
            }
            else if (arg == "-r")
            {
                if (!nMode)
                {
                    throw std::runtime_error("Error: Parameter r must be used with parameter n.");
                }
                if (i + 1 < argc)
                {
                    holes = std::stoi(argv[++i]);
                }
                else
                {
                    throw std::runtime_error("Error: Missing argument for '-r'.");
                }
            }
            else if (arg == "-u")
            {
                if (!nMode)
                {
                    throw std::runtime_error("Error: Parameter u must be used with parameter n.");
                }
                unique = true;
            }
            else
            {
                throw std::runtime_error("Error: Invalid argument.");
            }
        }

        if (generateMode)
        {
            std::ofstream file(outputFile);
            if (!file)
            {
                throw std::runtime_error("Error: Cannot open output file.");
            }
            file.close();

            Sudoku sudoku;
            for (int i = 0; i < generatedCount; ++i)
            {
                if (unique)
                {
                    sudoku.generateUnique(holes, difficulty);
                }
                else
                {
                    sudoku.generate(holes, difficulty);
                }
                // sudoku.generate(holes, unique, difficulty);
                sudoku.saveToFile(outputFile);
            }
        }

        if (solveMode)
        {
            std::ifstream file(inputFile.c_str());
            if (!file)
            {
                std::cerr << "Error: Cannot open input file." << std::endl;
                return 1;
            }

            const int numRows = 9;
            const int numCols = 9;
            std::vector<std::vector<int>> inputMatrix;
            std::vector<std::vector<std::vector<int>>> inputMatrices;
            while (true)
            {
                inputMatrix.clear();
                for (int i = 0; i < numRows; i++)
                {
                    std::vector<int> row;
                    for (int j = 0; j < numCols; j++)
                    {
                        int value;
                        if (file >> value)
                        {
                            row.push_back(value);
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (row.size() == numCols)
                    {
                        inputMatrix.push_back(row);
                    }
                    else
                    {
                        break;
                    }
                }
                if (inputMatrix.empty())
                {
                    break;
                }
                inputMatrices.push_back(inputMatrix);
            }

            for (const auto &inputMatrixItor : inputMatrices)
            {
                Sudoku sudoku;
                if (sudoku.loadFromMatrix(inputMatrixItor))
                {
                    if (sudoku.solve())
                    {
                        //std::vector<std::vector<int>> answerMatrix;
                        sudoku.saveToFile(answerFile);
                    }
                    else
                    {
                        throw std::runtime_error("Error: Failed to solve the Sudoku puzzle.");
                    }
                }
                else
                {
                    throw std::runtime_error("Error: Invalid Input.");
                }
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
