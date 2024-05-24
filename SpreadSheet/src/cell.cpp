#include "cell.h"

std::ostream& operator<<(std::ostream& out, const std::Vector<int>& ob) {
    out << "[";
    for (size_t i = 0; i < ob.size(); ++i) {
        out << ob[i];
        if (i < ob.size() - 1)
            out << ", ";
    }
    out << "]";
    return out;
}

Cell::Cell() : 
    val("") 
{}

Cell::Cell(const Cell& rhv) : 
    val(rhv.val) 
{}

Cell::Cell(Cell&& rhv) : 
    val(std::move(rhv.val)) 
{}

Cell::Cell(int val) : 
    val(std::to_string(val))
{}

Cell::Cell(double val) : 
    val(std::to_string(val)) 
{}

Cell::Cell(char val) : 
    val(1, val) 
{}

Cell::Cell(bool val) : 
    val(val ? "1" : "0") 
{}

Cell::Cell(std::string val) : 
    val(val) 
{}

Cell::Cell(const std::Vector<int>& val) 
{
    std::string VectorString = "";
    for (size_t i = 0; i < val.size(); ++i) {
        VectorString += std::to_string(val[i]);
        if (i < val.size() - 1) {
            VectorString += ", ";
		}
    }
    this->val = std::to_string(val.size()) + " elements: " + VectorString;
}

const Cell& Cell::operator=(const Cell& rhv) 
{
	if (this != &rhv) {
		this->val = rhv.val;
	}
	return *this;
}

const Cell& Cell::operator=(Cell&& rhv) 
{
	if (this != &rhv) {
        this->val = std::move(rhv.val);
    }
    return *this;
}

const Cell& Cell::operator=(int rhv)
{
	this->val = std::to_string(rhv);
	return *this; 
}

const Cell& Cell::operator=(double rhv) 
{
	this->val = std::to_string(rhv);
	return *this;
}

const Cell& Cell::operator=(char rhv) 
{
	this->val = rhv;
	return *this;
}

const Cell& Cell::operator=(bool rhv) {
    this->val = rhv ? "1" : "0";
    return *this;
}

const Cell& Cell::operator=(std::string rhv) 
{
	this->val = std::move(rhv);
    return *this;
}

const Cell& Cell::operator=(const std::Vector<int>& rhv) 
{
    std::string VectorString = "";
    for (size_t i = 0; i < rhv.size(); ++i) {
        VectorString += std::to_string(rhv[i]);
        if (i < rhv.size() - 1) {
            VectorString += ", ";
		}
    }
    this->val = std::to_string(rhv.size()) + VectorString;
    return *this;
}

Cell::operator int() 
{
	int res = 0;
	try {
		res = std::stoi(this->val);
	}
	catch (std::exception& e) {};
	return res;
}

Cell::operator double() 
{
	double res = 0;
	try {
		res = std::stod(this->val);
	}
	catch (std::exception& e) {};
	return res;
}

Cell::operator char() 
{
    return this->val[0];
}

Cell::operator bool() 
{
    return !this->val.empty();
}

Cell::operator std::string() 
{
    return this->val;
}

Cell::operator std::Vector<int>() 
{
    std::Vector<int> result;
    size_t start = this->val.find("[") + 1;
    size_t end = this->val.find("]");
    if (start != std::string::npos && end != std::string::npos && start < end) {
        std::string elements = this->val.substr(start, end - start);
        size_t pos = 0;
        while ((pos = elements.find(",")) != std::string::npos) {
            result.push_back(std::stoi(elements.substr(0, pos)));
            elements.erase(0, pos + 2);
        }
        result.push_back(std::stoi(elements));
    }
    return result;
}

std::string Cell::getVal() const 
{ 
    return val; 
}

void Cell::setVal(const std::string& newVal) 
{
    val = newVal; 
}

bool operator==(const Cell& lhv, const Cell& rhv) 
{
    return lhv.getVal() == rhv.getVal();
}

bool operator!=(const Cell& lhv, const Cell& rhv) 
{
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const Cell& ob) 
{
    out << ob.getVal();
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) 
{
    std::string str;
	in >> str;
	ob = str;
	return in;
}

