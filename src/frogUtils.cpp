#include "frogUtils.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

string frogUtils::toLowercase(string str) {
    string strLower = "";
    for( int i=0; i<str.length(); i++ ) {
        strLower += tolower( str[i] );
    }
    return strLower;
}

int frogUtils::getVectorValuePosition(vector<string>& vect, string& val) {
    return find(vect.begin(), vect.end(), val) - vect.begin();
}