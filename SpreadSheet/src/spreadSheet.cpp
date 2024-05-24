#include "spreadSheet.h"

SpreadSheet::SpreadSheet() : 
    board {new Cell*[2]}, rowcnt{2}, colcnt{2}
{
    for (int i = 0; i < rowcnt; ++i){
        board[i] = new Cell[colcnt];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : 
    rowcnt {rhv.rowcnt}, colcnt {rhv.colcnt}
{
    board = new Cell* [rowcnt];

    for (int i = 0; i < rowcnt; ++i){
        board[i] = new Cell[colcnt];
    }
    for (int i = 0; i < rowcnt; ++i){
        for (int j = 0; j < colcnt; ++j){
            board[i][j] = rhv.board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv) : 
    rowcnt {rhv.rowcnt}, colcnt {rhv.colcnt}
{
    board = new Cell* [rowcnt];

    for (int i = 0; i < rowcnt; ++i){
        board[i] = new Cell[colcnt];
    }
    for (int i = 0; i < rowcnt; ++i){
        for (int j = 0; j < colcnt; ++j){
            board[i][j] = rhv.board[i][j];
        }
    }

    for (int i = 0; i < rowcnt; ++i) {
        delete [] rhv.board[i];
    }
    delete [] rhv.board;

    rhv.board = nullptr;
    rhv.rowcnt = 0;
    rhv.colcnt = 0;
}

SpreadSheet::SpreadSheet(size_t size) : 
    rowcnt {size}, colcnt {size}
{
    board = new Cell* [rowcnt];

    for (int i = 0; i < rowcnt; ++i){
        board[i] = new Cell[colcnt];
    }
    for (int i = 0; i < rowcnt; ++i){
        for (int j = 0; j < colcnt; ++j){
            board[i][j] = 0;
        }
    }
}

SpreadSheet::SpreadSheet(size_t row, size_t col) : 
    rowcnt {row}, colcnt {col}
{
    board = new Cell* [rowcnt];

    for (int i = 0; i < rowcnt; ++i){
        board[i] = new Cell[colcnt];
    }

    for (int i = 0; i < rowcnt; ++i){
        for (int j = 0; j < colcnt; ++j){
            board[i][j] = 0;
        }
    }
}

SpreadSheet::~SpreadSheet() {
    clear();
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv)
{
    if (this != &rhv){
        for(int i = 0; i < rowcnt; ++i){
            delete[] this->board[i];
        }
        delete[] board;
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        board = new Cell*[rowcnt];
        for(int i = 0; i < rowcnt; ++i){
            board[i] = new Cell[colcnt];
        }
        for(int i = 0; i < rowcnt; ++i){
            for(int j = 0; j < colcnt; ++j){
                board[i][j] = rhv.board[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv)
{
    if (this != &rhv){
        for(int i = 0; i < rowcnt; ++i){
            delete[] board[i];
        }
        delete[] board;
        rowcnt = rhv.rowcnt;
        colcnt = rhv.colcnt;
        board = new Cell*[rowcnt];
        for(int i = 0; i < rowcnt; ++i){
            board[i] = new Cell[colcnt];
        }
        for(int i = 0; i < rowcnt; ++i){
            for(int j = 0; j < colcnt; ++j){
                board[i][j] = rhv.board[i][j];
            }
        }

        for(int i = 0; i < rowcnt; ++i){
            delete[] rhv.board[i];
        }
        delete[] rhv.board;
        rhv.rowcnt = 0; 
        rhv.colcnt = 0;
        rhv.board = nullptr;
    }
    return *this;
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos) 
{
    if (pos >= colcnt) {
        throw std::out_of_range("Column index out of range");
    }
    return Column(board[pos]);
}
    
const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const 
{
    if (pos >= colcnt) {
        throw std::out_of_range("Column index out of range");
    }
    return Column(board[pos]);
}

void SpreadSheet::clear() noexcept 
{
    if (board) {
        for (size_t i = 0; i < rowcnt; ++i) {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
        rowcnt = 0;
        colcnt = 0;
    }
}

size_t SpreadSheet::row() const
{
    return rowcnt;
}

size_t SpreadSheet::col() const
{
    return colcnt;
}

void SpreadSheet::mirrorH() 
{
    if (board) {
        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = 0; j < colcnt / 2; ++j) {
                std::swap(board[i][j], board[i][colcnt - j - 1]);
            }
        }
    }
}

void SpreadSheet::mirrorV() 
{
    if (board) {
        for (size_t i = 0; i < rowcnt / 2; ++i) {
            for (size_t j = 0; j < colcnt; ++j) {
                std::swap(board[i][j], board[rowcnt - i - 1][j]);
            }
        }
    }
}

void SpreadSheet::mirrorD() 
{
    if (board) {
        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = i + 1; j < rowcnt; ++j) {
                std::swap(board[i][j], board[j][i]);
            }
        }
    }
}

void SpreadSheet::mirrorSD() 
{
    if (board) {
        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = 0; j < rowcnt - i - 1; ++j) {
                std::swap(board[i][j], board[rowcnt - j - 1][rowcnt - i - 1]);
            }
        }
    }
}

void SpreadSheet::rotate(int cnt) 
{
    if (cnt < 0) {
        cnt = -cnt;
        cnt %= 4;
        cnt = 4 - cnt;
    } else {
        cnt %= 4;
    }

    for (int k = 0; k < cnt; ++k) {
        Cell** temp = new Cell*[colcnt];
        for (size_t i = 0; i < colcnt; ++i) {
            temp[i] = new Cell[rowcnt];
            for (size_t j = 0; j < rowcnt; ++j) {
                temp[i][j] = board[j][colcnt - i - 1];
            }
        }

        for (size_t i = 0; i < rowcnt; ++i) {
            delete[] board[i];
        }
        delete[] board;

        std::swap(rowcnt, colcnt);
        board = new Cell*[rowcnt];
        for (size_t i = 0; i < rowcnt; ++i) {
            board[i] = new Cell[colcnt];
            for (size_t j = 0; j < colcnt; ++j) {
                board[i][j] = temp[i][j];
            }
        }

        for (size_t i = 0; i < colcnt; ++i) {
            delete[] temp[i];
        }
        delete[] temp;
    }
}

void SpreadSheet::removeRow(size_t row) 
{
    if (row >= rowcnt) {
        throw std::out_of_range("Row index out of range");
    }

    delete[] board[row];
    for (size_t i = row; i < rowcnt - 1; ++i) {
        board[i] = board[i + 1];
    }
    --rowcnt;
}
    
void SpreadSheet::removeRows(std::initializer_list<size_t> rows) 
{
    for (size_t row : rows) {
        removeRow(row);
    }
}

void SpreadSheet::removeCol(size_t col) 
{
    if (col >= colcnt) {
        throw std::out_of_range("Column index out of range");
    }

    for (size_t i = 0; i < rowcnt; ++i) {
        for (size_t j = col; j < colcnt - 1; ++j) {
            board[i][j] = board[i][j + 1];
        }
        board[i] = (Cell*)realloc_(board[i], (colcnt - 1) * sizeof(Cell));
    }
    --colcnt;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols) 
{
    for (size_t col : cols) {
        removeCol(col);
    }
}

void SpreadSheet::resizeRow(size_t r) 
{
    if (r == rowcnt) {
        return; 
    } else if (r < rowcnt) {
        Cell** newBoard = new Cell*[r];
        for (size_t i = 0; i < r; ++i) {
            newBoard[i] = board[i];
        }
        for (size_t i = r; i < rowcnt; ++i) {
            delete[] board[i];
        }
        delete[] board;
        board = nullptr;
        board = newBoard;
        rowcnt = r;
    } else {
     Cell** newBoard = new Cell*[r];
        for (size_t i = 0; i < rowcnt; ++i) {
            newBoard[i] = board[i];
        }
        for (size_t i = rowcnt; i < r; ++i) {
            newBoard[i] = new Cell[colcnt];
            for (size_t j = 0; j < colcnt; ++j) {
                newBoard[i][j] = Cell(0);
            }
        }
        delete[] board;
        board = nullptr; 
        board = newBoard;
        rowcnt = r;
    }
}
    
void SpreadSheet::resizeCol(size_t c) 
{
    if (c == colcnt) {
        return;
    } else if (c < colcnt) {
        for (size_t i = 0; i < rowcnt; ++i) {
            Cell* newRow = new Cell[c];
            for (size_t j = 0; j < c; ++j) {
                newRow[j] = board[i][j];
            }
            delete[] board[i];
            board[i] = newRow;
        }
        colcnt = c;
    } else {
        Cell** newBoard = new Cell*[rowcnt];
        for (size_t i = 0; i < rowcnt; ++i) {
            newBoard[i] = new Cell[c];
        }

        for (size_t i = 0; i < rowcnt; ++i) {
            for (size_t j = 0; j < colcnt; ++j) {
                newBoard[i][j] = board[i][j];
            }

            for (size_t j = colcnt; j < c; ++j) {
                newBoard[i][j] = 0;
            }
        }
        delete[] board;
        board = nullptr; 
        board = newBoard;
        colcnt = c;
    }
}

void SpreadSheet::resize(size_t r, size_t c) 
{
    resizeRow(r);
    resizeCol(c);
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) 
{
    SpreadSheet sliced_sheet(rows.size(), cols.size()); 
    size_t i = 0;
    for (size_t row_index : rows) {
        size_t j = 0;
        for (size_t col_index : cols) {
            if (row_index >= rowcnt || col_index >= colcnt) {
                throw std::out_of_range("Row or column index out of range");
            }
            sliced_sheet.board[i][j] = board[row_index][col_index];
            ++j;
        }
        ++i;
    }
    return sliced_sheet;
}

SpreadSheet::Column::Column(Cell* col) : col(col) {}

Cell& SpreadSheet::Column::operator[](size_t pos) 
{
    return col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const 
{
    return col[pos];
}

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv) 
{
    if (lhv.row() != rhv.row() || lhv.col() != rhv.col()) {
        return false;
    }

    for (size_t i = 0; i < lhv.row(); ++i) {
        for (size_t j = 0; j < lhv.col(); ++j) {
            if (lhv[i][j] != rhv[i][j]) {
                return false; 
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv) 
{
    return !(lhv == rhv); 
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) 
{
    int width = 8;
    double tbl_width = ob.col() * 9.1;
    int h_line = 1;
    for (size_t i = 0; i < ob.row(); ++i)
    {
        for(size_t j = 0; j < tbl_width; ++j)
        {
            out << std::setw(1) << "-";
        }

        out << "\n";

        for(size_t k = 0; k < ob.col(); ++k)
       	{
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << ob[i][k];
        }
        out << std::setw(h_line) << "|";

        out << "\n";
    }
    
    for(size_t i = 0; i < tbl_width; ++i)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}
