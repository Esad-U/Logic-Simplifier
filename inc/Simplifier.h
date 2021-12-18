#include <vector>
#include <iostream>
using namespace std;

class Simplifier {
private:
	int varNum;
	string vars;
public:
	Simplifier(int, string);
	void set_varNum(int);
	int get_varNum();
	void set_vars(string);
	string get_vars();
	string to_letters(string);
	bool is_gray_code(string, string);
	string replace_changes(string, string);
	vector<string> find_minterms(vector<int>);
	bool search(vector<string>, string);
	void simplify(vector<int>);
};