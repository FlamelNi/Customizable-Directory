

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string DELIMIT = ",";

const string TITLE_START = "<!-- TITLE -->";
const string TITLE_END = "<!-- TITLE END -->";

const string COLUMN_START = "<!-- COLUMN -->";
const string COLUMN_END = "<!-- COLUMN END -->";


class ExcelToTable {
    public:
    string fullHtml = "";
    string title = "";
    string column_left = "";
    string column_right = "";
    vector<vector<string>> rows = vector<vector<string>>{};

    void addRows(string a, string b) {
        rows.push_back(vector<string>{a, b});
    }
    void addRows(vector<string> strs) {
        rows.push_back(strs);
    }

    // string getTitle() {
    //     return "<h1 class=\"display-4\" id=\"station_name\">"+ this->title + "</h1>";
    // }
    
    void findInTemplet() {

    }

    void replaceHtmlBy(string& s, string start, string end, string by) {
        int a = s.find(start);
        int b = s.find(end) + end.length();
        
        s.replace(a, b-a, by + "\n");
    }

    string getReplaceHtml() {
        string s = "";
        s =  s + "<h1 class=\"display-4\" style=\"margin-bottom: 35px;\">" + this->title + "</h1>\n\n";

        s = s + "<div class=\"two-columns\" style=\"margin-bottom: 35px;\">\n";
        s = s +    "<div class=\"name\">\n";
        s = s +         "<h1 class=\"display-6\">" + this->column_left + "</h1>\n";
        s = s +     "</div>\n";
        s = s +     "<div class=\"info\">\n";
        s = s +         "<h1 class=\"display-6 float-right\">" + this->column_right + "</h1>\n";
        s = s +     "</div>\n";
        s = s + "</div>\n\n";

        for (int i = 0; i < rows.size(); i++) {
            s = s + "<div class=\"two-columns\" style=\"margin-bottom: 35px;\">\n";
            s = s +    "<div class=\"name\">\n";
            s = s +         "<h1 class=\"display-6\">" + this->rows.at(i).at(0) + "</h1>\n";
            s = s +     "</div>\n";
            s = s +     "<div class=\"info\">\n";
            s = s +         "<h1 class=\"display-6 float-right\">" + this->rows.at(i).at(1) + "</h1>\n";
            s = s +     "</div>\n";
            s = s + "</div>\n\n";
        }
        return s;
    }

    void modifyHtml() {
        int a = 0;
        int b = 0;
        string s = this->fullHtml;

        ofstream fout;

        // cout << getReplaceHtml();
        replaceHtmlBy(s, TITLE_START, TITLE_END, getReplaceHtml());
        
        fout.open("index.html");
        fout << s;
        fout.close();

    }
};

string getSubstrByDelimiter(string s, int index) {
    string temp = "";
    for (int i = 0; i <= index; i++) {
        int nextFound = s.find(DELIMIT);
        temp = s.substr(0, nextFound);
        s = s.substr(nextFound+1);
    }
    return temp;
}

ExcelToTable readExcelFormat() {
    ExcelToTable formatData;
    ifstream fin;
    string s;

    //reading directory excel format
    fin.open("directory.csv");

    getline(fin, s);
    // cout << getSubstrByDelimiter(s, 1) << endl;
    formatData.title = getSubstrByDelimiter(s, 1);

    getline(fin, s);
    formatData.column_left = getSubstrByDelimiter(s, 1);
    formatData.column_right = getSubstrByDelimiter(s, 3);

    
    while (!fin.eof()) {
        getline(fin, s);
        
        vector<string> temp = {getSubstrByDelimiter(s, 1), getSubstrByDelimiter(s, 3)};
        formatData.rows.push_back(temp);
    }

    fin.close();
    return formatData;
}

string readHtmlTemplet() {
    string tempHTML = "";
    ifstream fin;
    string s = "";

    fin.open("indexTemplet.html");
    
    while (!fin.eof()) {
        getline(fin, s);
        tempHTML = tempHTML + s + "\n";
    }
    fin.close();
    return tempHTML;
}


int main() {
    string s = "";
    string title = "";
    string left = "";
    string right = "";

    ifstream fin;
    // ofstream fout;

    ExcelToTable formatData = readExcelFormat();
    
    formatData.fullHtml = readHtmlTemplet();
    // std::cout << formatData.fullHtml;

    formatData.modifyHtml();

    
    return 0;
}


