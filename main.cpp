#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

using std::vector;
using std::string;
using std::pair;

class NestedInteger {
  private:
    bool isInt;
    int myInt;
    vector<NestedInteger> * myVec;
    
  public:
    NestedInteger() : isInt(false){
        myVec = new vector<NestedInteger>();
    }
    NestedInteger(int value) : isInt(true), myInt(value){
    }

    bool isInteger() const { return isInt; }

    int getInteger() const {
        if (isInt)
            return myInt;
    }

    void setInteger(int value) {
        if (isInt)
            myInt = value;
    }

    void add(const NestedInteger & ni) {
        if (!isInt)
            myVec->push_back(ni);
    }

    const vector<NestedInteger> & getList() const {
        if (!isInt)
            return *myVec;
    }

    void print() {
        if (isInt)
            std::cout << myInt;
        else {
            auto vec = getList();
            std::cout << "[";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i != vec.size()-1) {
                    vec[i].print();
                    std::cout << ",";
                }
                else
                    vec[i].print();
            }
            std::cout << "]";
        }
    }
};

class solution {
  public:
    NestedInteger deserialize(const string & s) {
        if (s[0] != '[') {
            return NestedInteger(std::stoi(s));
        }
        else {
            auto vec = split(s.substr(1));
            std::for_each(vec.begin(), vec.end(), [](const string & s){std::cout << s << " ";});
            std::cout << std::endl;
            // std::cout << vec.first << ", " << vec.second << std::endl;
            NestedInteger result;
            // result.add(deserialize(vec.first));
            // if (!vec.second.empty())
            //     result.add(deserialize(vec.second));
            for (auto str : vec)
                result.add(deserialize(str));
            return result;
        }
    }

  private:
    vector<string> split(const string & s) {
        vector<string> result;
        size_t start = 0, end;
        end = s.find_first_of(",]",start);
        while (true) {
            if (end != string::npos) {
                if (isValid(s.substr(start,end-start))) {
                    // size_t last;
                    // for (last = s.size()-1; last >= end+1; --last)
                    //     if (isValid(s.substr(end+1, last-end)))
                    //         break;                    
                    // result = std::make_pair(s.substr(start,end-start), s.substr(end+1,last-end));
                    // break;
                    result.push_back(s.substr(start,end-start));
                    start = s.find_first_of("0123456789-[", end);
                    end = s.find_first_of(",]",start);
                }
                else {
                    end = s.find_first_of(",]",end+1);
                }
            }
            else
                break;
        }
        return result;
    }

    bool isValid(const string & s) {
        int sum = 0;
        for (auto ch : s) {
            if (ch == '[')
                sum++;
            else if (ch == ']')
                sum--;
        }
        return sum == 0;
    }
};

int main() {
    // string ser{"324"};
    // string ser{"[123,[456,[789]]]"};
    string ser{"[[1,[2,[3]]],[4,5,[6,[7,[8]]]]]"};
    
    solution soln;
    NestedInteger ni = soln.deserialize(ser);
    ni.print();
    std::cout << std::endl;
}
