#include "Simplifier.h"
#include <iostream>
#include <stack>
using namespace std;

Simplifier::Simplifier(int varNum, string vars)
{
	this->set_varNum(varNum);
	this->set_vars(vars);
}
void Simplifier::set_varNum(int varNum)
{
	this->varNum = varNum;
}
int Simplifier::get_varNum()
{
	return this->varNum;
}
void Simplifier::set_vars(string vars)
{
	this->vars = vars;
}
string Simplifier::get_vars()
{
	return this->vars;
}
string Simplifier::to_letters(string minterm)
{
	string tmp = "";
	for(int i = 0;i < minterm.length();i++) {
		if(minterm[i] == '1') {
			tmp.push_back(this->get_vars()[i]);
		} else if (minterm[i] == '0') {
			tmp.push_back('!');
			tmp.push_back(this->get_vars()[i]);
		}
	}
	return tmp;
}
bool Simplifier::is_gray_code(string a, string b)
{
	int check = 0;
	for(int i = 0;i < a.length();i++) {
		if(a[i] != b[i])
			check++;
	}
	return check == 1;
}
string Simplifier::replace_changes(string a, string b)
{
	string tmp = "";
	for(int i = 0;i < a.length();i++) {
		if(a[i] == b[i])
			tmp.push_back(a[i]);
		else
			tmp.push_back('-');
	}
	return tmp;
}
vector<string> Simplifier::find_minterms(vector<int> indexes)
{
	vector<string> minterms;
	string tmp = "";
	int left;
	for(int i = 0;i < indexes.size();i++) {
		while(indexes[i] != 0) {
			left = indexes[i] % 2;
			tmp.insert(tmp.begin(), (left+48));
			indexes[i] = indexes[i] / 2;
		}
		while(tmp.length() < this->get_varNum()) {
			tmp.insert(tmp.begin(), '0');
		}
		minterms.push_back(tmp);
		tmp = "";
	}
	return minterms;
}
bool Simplifier::search(vector<string> vect, string n)
{
	for(int i = 0;i < vect.size();i++) {
		if(vect[i] == n)
			return true;
	}
	return false;
} 
void Simplifier::simplify(vector<int> indexes)
{
	vector<string> newMinterms;
	vector<string> minterms = this->find_minterms(indexes);
	int opt = 1;
	int *count = new int[this->get_varNum()];
	while(opt > 0) {
		for(int i = 0;i < this->get_varNum();i++)
			count[i] = 0;
		opt = 0;
		for(int i = 0;i < minterms.size();i++) {
			for(int j = i+1;j < minterms.size();j++) {
				if(this->is_gray_code(minterms[i], minterms[j])) {
					opt++;
					count[i]++;
					count[j]++;
					if(!this->search(newMinterms, this->replace_changes(minterms[i],minterms[j])))
						newMinterms.push_back(this->replace_changes(minterms[i],minterms[j]));
				}
			}
			if(count[i] == 0)
				newMinterms.push_back(minterms[i]);
		}
		if(opt > 0) {
			minterms.swap(newMinterms);
			newMinterms.clear();
		}
	}
	string output = "";
	for(int i = 0;i < minterms.size();i++) {
		output = output + this->to_letters(minterms[i]);
		if(i != minterms.size()-1) {
			output.push_back(' ');
			output.push_back('+');
			output.push_back(' ');
		}
	}
	cout << "Result: " << output << endl;
}