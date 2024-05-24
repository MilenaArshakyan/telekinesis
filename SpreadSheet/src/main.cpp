#include "spreadSheet.h"

int main()
{
    SpreadSheet ob(5, 5);

    std::cout << "Enter spreadsheet values:" << std::endl;
    for (int i = 0; i < ob.row(); ++i) {
        for (int j = 0; j < ob.col(); ++j) {
            std::cin >> ob[i][j];
        }
    }

    std::cout << "Original Spreadsheet:" << std::endl;
    std::cout << ob << std::endl;

    ob.rotate(90);
    std::cout << "rotate 90 Spreadsheet:" << std::endl;
    std::cout << ob << std::endl;

    ob.mirrorD();
    std::cout << "Spreadsheet after mirrorD:" << std::endl;
    std::cout << ob << std::endl;

    ob.resizeRow(7);
    ob.resizeCol(13);
    std::cout << "Spreadsheet after resize row and col:" << std::endl;
    std::cout << ob << std::endl;

    ob.resize(11, 13);
    std::cout << "Spreadsheet after resize:" << std::endl;
    std::cout << ob << std::endl;

    std::initializer_list<size_t> rows = {1, 5, 7, 8, 9};
    std::initializer_list<size_t> cols = {0, 2, 3, 4, 8, 10, 12};

    ob.mirrorH();
    std::cout << "Spreadsheet after mirrorH:" << std::endl;
    std::cout << ob << std::endl;

    ob.mirrorV();
    std::cout << "Spreadsheet after mirrorV:" << std::endl;
    std::cout << ob << std::endl;


    SpreadSheet ob2 = ob.slice(rows, cols);
    std::cout << "Spreadsheet 2 after slice:" << std::endl;
    std::cout << ob2 << std::endl;

    std::Vector<int> v1 = ob[8][7];
    std::Vector<int> v2 = ob2[4][2];

    std::cout << std::boolalpha << v1.empty() << std::endl;
    std::cout << std::boolalpha << v2.empty() << std::endl;
    
    std::cout << std::boolalpha << (v1 == v2) << std::endl;

    return 0;
}

