#include <iostream>
#include <string>
#include <limits>
#include <time.h>

enum class Mode
{
    ALL_SOLUTIONS = 0,
    FAST_SOLUTION = 1
};

/**
 * @brief Get the integer value from std::cin object
 * @throws shall not throw exceptions 
 * @param[in] caption the caption line before input
 * @param[in] min minimal valid integer for input
 * @param[in] max maximal valid integer for input
 * @return int value after conversion
 */
int getIntFromCin(std::string caption, int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max()) noexcept
{
    std::string buffer;
    int result {0};
    bool isValid {false};
    do
    {
        std::cout << caption << "[min = " << min << ", max = " << max << "]: ";
        std::getline(std::cin, buffer);
        try
        {
            result = std::stoi(buffer);
            if (result >= min && result <= max)
            {
                isValid = true;
            }
            else
            {
                std::cerr << "Invalid value, please try again.\n";
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    } while (!isValid);
    
     return result;
}

/**
 * @brief   Find and print the parameters for the LCG (Linear Congruential Generator) 
 *          satisfying the corresponding 4 values ​​(x_1 ... x_4). It's possible to find fast solution
 *          or all solutions be switching the 'mode'.
 * @throws shall not throw exceptions 
 * @param[in] x_1 1-st value to be used for solution search
 * @param[in] x_2 2-nd value to be used for solution search
 * @param[in] x_3 3-rd value to be used for solution search
 * @param[in] x_4 4-th value to be used for solution search
 * @param[in] mode search mode 'ALL_SOLUTIONS' will print all possible combinations of LCG parameters,
 *                 'FAST_SOLUTION' - will print only the first one
 */
void findSolution(int x_1, int x_2, int x_3, int x_4, Mode mode) noexcept
{
    const int M_MAX = 65535;

    std::cout << "Searching...\n";
    int solutionsCounter {0};
    bool isFound {false};
    int a {0};
    int c {0};
    int m = x_1 > 2 ? x_1 : 2;
    clock_t start = clock();
    for (a = 0; a < M_MAX && !isFound; ++a)
    {
        for (m = x_1; m < M_MAX && !isFound; ++m)
        {
            c = x_2 - ((x_1 * a) % m);
            if (c < 0) c += m;
            
            if (x_2 == (a * x_1 + c) % m &&
                x_3 == (a * x_2 + c) % m &&
                x_4 == (a * x_3 + c) % m &&
                c >= 0)
            {
                std::cout << "a = " << a << "\n";
                std::cout << "c = " << c << "\n";
                std::cout << "m = " << m << "\n";
                std::cout << "x_5 = " << (a * x_4 + c) % m << "\n";
                std::cout << "- - - - - - - - -\n";
                ++solutionsCounter;
                if (mode == Mode::FAST_SOLUTION)
                {
                    isFound = true;
                    break;
                }
            }
        } 
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Search time: %f seconds\n", seconds);
    
    std::cout << (solutionsCounter ? "Done.\n" : "No solution is found.\n");
}


int main(int argc, char* argv[])
{
    int x_1 {0};
    int x_2 {0};
    int x_3 {0};
    int x_4 {0};

    if (argc == 4)
    {
        x_1 = atoi(argv[0]);
        x_2 = atoi(argv[1]);
        x_3 = atoi(argv[2]);
        x_4 = atoi(argv[3]);
    }
    else
    {
        x_1 = getIntFromCin("Please enter the x_1", 0, 65535);
        x_2 = getIntFromCin("Please enter the x_2", 0, 65535);
        x_3 = getIntFromCin("Please enter the x_3", 0, 65535);
        x_4 = getIntFromCin("Please enter the x_4", 0, 65535);
    }
    
        // use for test 7, 6, 9, 0
        // use for test 157; 5054; 25789; 13214
    
    findSolution(x_1, x_2, x_3, x_4, Mode::ALL_SOLUTIONS);

    return 0;
}