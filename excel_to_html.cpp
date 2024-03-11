

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const string DELIMIT = ",";

const string TITLE_START = "<!-- TITLE -->";
const string TITLE_END = "<!-- TITLE END -->";

class ExcelToTable {
    public:
    string titleFont = "";
    string titleRowFont = "";
    string rowFont = "";

    string titleFontSize = "50";
    string titleRowFontSize = "40";
    string rowFontSize = "30";

    string fullHtml = "";
    string title = "";
    vector<vector<string>> title_rows = vector<vector<string>>{};
    vector<vector<string>> rows = vector<vector<string>>{};
    vector<vector<string>> rowsSmall = vector<vector<string>>{};
    
    vector<int> num_rows = vector<int>{};

    void addRows(string a, string b) {
        rows.push_back(vector<string>{a, b});
    }
    void addRows(vector<string> strs) {
        rows.push_back(strs);
    }
    
    void findInTemplet() {

    }

    void replaceHtmlBy(string& s, string start, string end, string by) {
        int a = s.find(start);
        int b = s.find(end) + end.length();
        
        s.replace(a, b-a, by + "\n");
    }

    string getReplaceHtml() {

        string titleMargin = to_string(atoi(this->titleFontSize.c_str())-10);
        string titleRowMargin = to_string(atoi(this->titleRowFontSize.c_str())-10);
        string titleRowMargintop = to_string(atoi(this->titleRowFontSize.c_str())+40);
        string rowMargin = to_string(atoi(this->rowFontSize.c_str())-10);

        string titleFont = " font-family: " + this->titleFont + "; ";
        string titleRowFont = " font-family: " + this->titleRowFont + "; ";
        string rowFont = " font-family: " + this->rowFont + "; ";

        if (this->titleFont == "") {
            titleFont = "";
        }
        if (this->titleRowFont == "") {
            titleRowFont = "";
        }
        if (this->rowFont == "") {
            rowFont = "";
        }

        string s = "";
        s = s + "<h1 class=\"display-4\" style=\"text-align: center; margin-bottom: " + titleMargin + "px; font-size: " + this->titleFontSize + "px;" + titleFont + "\">" + this->title + "</h1>\n\n";


        int curr_num_row_index = 0;
        for (int i = 0; i < rows.size(); i++) {
            
            if (i >= this->num_rows.at(curr_num_row_index) && curr_num_row_index < this->title_rows.size()) {
                s = s + "<div class=\"two-columns\" style=\"margin-bottom: " + titleRowMargin + "px; margin-top: " + titleRowMargintop + "px;\">\n";
                s = s +    "<div class=\"name float-left\">\n";
                s = s +         "<h1 class=\"display-6\" style=\"font-size: " + this->titleRowFontSize + "px;" + titleRowFont + "\">" + this->title_rows.at(curr_num_row_index).at(0) + "</h1>\n";
                s = s +     "</div>\n";
                s = s +     "<div class=\"info float-right\">\n";
                s = s +         "<h1 class=\"display-6 float-right\" style=\"font-size: " + this->titleRowFontSize + "px;" + titleRowFont + "\">" + this->title_rows.at(curr_num_row_index).at(1) + "</h1>\n";
                s = s +     "</div>\n";
                s = s + "</div>\n\n";
                curr_num_row_index++;
            }

            // string backgroundColorText = "";
            // if (i%2 == 1) {
            //     backgroundColorText = "background-color: #d9d9d9";
            // }
            string underline = "border-bottom: solid 1px";
            if (this->rows.at(i).at(0) == " " || this->rows.at(i).at(0) == "") {
                underline = "";
            }

            s = s + "<div class=\"two-columns\" style=\"margin-bottom: " + rowMargin + "px;" + underline + "\">\n";
            s = s +    "<div class=\"name float-left\" style=\"display: flex;\">\n";
            s = s +         "<h1 class=\"display-6\" style=\"font-size: " + this->rowFontSize + "px;" + rowFont + "\">" + this->rows.at(i).at(0) + "</h1>\n";
            if (this->rowsSmall.at(i).at(0) != "") {
                s = s +     "<h1 class=\"display-6\" style=\"align-self: flex-end; margin-left: 10px; font-size: " + to_string(atoi(this->rowFontSize.c_str())-10) + "px;" + rowFont + "\">" + this->rowsSmall.at(i).at(0) + "</h1>\n";
                
            }
            s = s +     "</div>\n";
            s = s +     "<div class=\"info float-right\">\n";
            s = s +         "<h1 class=\"display-6 float-right\" style=\"font-size: " + this->rowFontSize + "px;" + rowFont + "\">" + this->rows.at(i).at(1) + "</h1>\n";
            s = s +     "</div>\n";
            s = s + "</div>\n\n";


            // if ( !(this->rows.at(i).at(0) == "" && this->rows.at(i).at(1) == "") ) {
                
            // }

        }
        return s;
    }

    void modifyHtml() {
        int a = 0;
        int b = 0;
        string s = this->fullHtml;

        ofstream fout;

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
    string temp;

    //reading directory excel format
    fin.open("directory.csv");

    getline(fin, s);
    temp = getSubstrByDelimiter(s, 1);
    if (temp != "") {
        formatData.titleFontSize = temp;
    }
    temp = getSubstrByDelimiter(s, 3);
    if (temp != "") {
        formatData.titleFont = temp;
    }

    getline(fin, s);
    temp = getSubstrByDelimiter(s, 1);
    if (temp != "") {
        formatData.titleRowFontSize = temp;
    }
    temp = getSubstrByDelimiter(s, 3);
    if (temp != "") {
        formatData.titleRowFont = temp;
    }
    
    
    getline(fin, s);
    temp = getSubstrByDelimiter(s, 1);
    if (temp != "") {
        formatData.rowFontSize = temp;
    }
    temp = getSubstrByDelimiter(s, 3);
    if (temp != "") {
        formatData.rowFont = temp;
    }

    getline(fin, s);
    formatData.title = getSubstrByDelimiter(s, 1);

    int num_rows = 0;
    while (!fin.eof()) {
        getline(fin, s);
        if (getSubstrByDelimiter(s, 1) == "END") {
            break;
        }
        vector<string> temp = {getSubstrByDelimiter(s, 1), getSubstrByDelimiter(s, 3)};
        if (getSubstrByDelimiter(s, 0) != "") {
            formatData.title_rows.push_back(temp);
            formatData.num_rows.push_back(num_rows);
            num_rows = 0;
        } else {
            formatData.rows.push_back(temp);
            formatData.rowsSmall.push_back({getSubstrByDelimiter(s, 2), getSubstrByDelimiter(s, 4)});
            num_rows++;
        }
    }
    formatData.num_rows.push_back(num_rows);

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

    formatData.modifyHtml();

    
    return 0;
}


