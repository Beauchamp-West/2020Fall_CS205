//
// Created by 陆彦青 on 2020/10/1.
//

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

string add(string& a, string& b){ //高精度加法
    string sub(string& a, string b);
    string str;
    if (a[0] == '-'){
        if (b[0] == '-'){
            str = '-'+ add(a.erase(0,1),b.erase(0,1));
            return str;
        } else {
            return sub(b,a.erase(0,1));
        }
    } else {
        if (b[0] == '-'){
            return sub(a,b.erase(0,1));
        } else {
            string :: size_type a_int = a.find('.'),b_int = b.find('.'); //比较整数、小数部分，补0
            string :: size_type a_dec,b_dec;
            if (a_int == string::npos){
                a_int = a.size();
                a_dec = 0;
            } else {
                a_dec = a.size()-a_int-1;
            }
            if (b_int == string::npos){
                b_int = b.size();
                b_dec = 0;
            } else {
                b_dec = b.size()-b_int-1;
            }
            if (a_int > b_int){
                for (int i = 0; i < a_int-b_int; ++i)
                    b = '0' + b;
            } else if (a_int < b_int){
                for (int i = 0; i < b_int-a_int; ++i)
                    a = '0' + a;
            }
            if (a_dec > b_dec){
                if (b_dec == 0) b += '.';
                for (int i = 0; i < a_dec-b_dec; ++i)
                    b += '0';
            } else if (a_dec < b_dec){
                if (a_dec == 0) a += '.';
                for (int i = 0; i < b_dec-a_dec; ++i)
                    a += '0';
            }

            int carry = 0,res;
            for (int i = a.size()-1; i > -1; --i) {
                if (a[i] == '.'){
                    str = '.' + str;
                } else {
                    char c = a[i], d = b[i];
                    res = (c - '0' + d - '0' + carry) % 10;
                    carry = (c - '0' + d - '0' + carry) / 10;
                    str = char(res + '0') + str;
                }
            }
            if (carry != 0) str = char(carry + '0') + str;

            return str;
        }
    }
}
string sub(string& a, string b){ //高精度减法
    string str;
    if (b[0] == '-'){
        return add(a,b.erase(0,1));
    } else {
        if (a[0] == '-'){
            str = '-' + add(a.erase(0,1),b);
            return str;
        } else {
            if (stod(a) < stod(b)) return '-' + sub(b,a);
            else {
                string::size_type a_int = a.find('.'), b_int = b.find('.'); //比较整数、小数部分，补0
                string::size_type a_dec, b_dec;
                if (a_int == string::npos) {
                    a_int = a.size();
                    a_dec = 0;
                } else {
                    a_dec = a.size() - a_int - 1;
                }
                if (b_int == string::npos) {
                    b_int = b.size();
                    b_dec = 0;
                } else {
                    b_dec = b.size() - b_int - 1;
                }
                if (a_int > b_int) {
                    for (int i = 0; i < a_int - b_int; ++i)
                        b = '0' + b;
                } else if (a_int < b_int) {
                    for (int i = 0; i < b_int - a_int; ++i)
                        a = '0' + a;
                }
                if (a_dec > b_dec) {
                    if (b_dec == 0) b += '.';
                    for (int i = 0; i < a_dec - b_dec; ++i)
                        b += '0';
                } else if (a_dec < b_dec) {
                    if (a_dec == 0) a += '.';
                    for (int i = 0; i < b_dec - a_dec; ++i)
                        a += '0';
                }

                int carry = 0, res;
                for (int i = a.size() - 1; i > 0; --i) {
                    char c = a[i], d = b[i];
                    if (a[i] == '.') {
                        str = '.' + str;
                    } else {
                        res = c - d - carry;
                        if (res < 0) {
                            res += 10;
                            carry = 1;
                        } else carry = 0;
                        str = char(res + '0') + str;
                    }
                }
                if (a[0] != '.') {
                    res = a[0] - b[0] - carry;
                    if (res != 0) str = to_string(res) + str;
                } else if (carry == 0) {
                    str = "0." + str;
                } else {
                    str = "-1." + str;
                }
                return str;
            }
        }
    }
}

string mul(string& a, string& b){
    if (a[0] == '-'){
        if (b[0] == '-'){
            return mul(a.erase(0,1),b.erase(0,1));
        } else {
            return '-' + mul(a.erase(0,1),b);
        }
    } else {
        if (b[0] == '-'){
            return '-' + mul(a,b.erase(0,1));
        } else {
            string::size_type a_int = a.find('.'), b_int = b.find('.');
            string::size_type a_dec = 0, b_dec = 0;
            if (a_int != string::npos){
                while (a[a.size()-1]=='0') a.pop_back();
                a = a.erase(a_int,1);
                a_dec = a.size()-a_int;
            }
            if (b_int != string::npos){
                while (b[b.size()-1]=='0') b.pop_back();
                b = b.erase(b_int,1);
                b_dec = b.size()-b_int;
            }
            string rows[b.size()];
            for (int i = b.size()-1; i >= 0; --i) {
                string row;
                int over = 0;
                for (int j = a.size()-1; j >= 0; --j) {
                    string tmp = to_string((a[j]-'0') * (b[i]-'0') + over);
                    if (tmp.size() > 1){
                        row = tmp[1] + row;
                        over = tmp[0]-'0';
                    } else {
                        row = tmp + row;
                        over = 0;
                    }
                }
                if (over != 0) row = char(over + '0') + row;
                int k = i;
                while ((b.size()-k-1) > 0){
                    row += '0';
                    k++;
                }
                rows[i] = row;
            }
            string result = "0";
            for (int i = 0; i < b.size(); ++i) {
                result = add(result,rows[i]);
            }
            string::size_type num = a_dec + b_dec;
//            cout << "num " << num << endl;
            if (num != 0){
                result = result.insert(result.size()-num,".");
                while (result[result.size()-1] == '0' || result[result.size()-1] == '.') result.pop_back(); //去掉多余的0
            }
            while (result[0] == '0') result.erase(0,1);
            if (result[0] == '.') result = '0'+result;
            return result;
        }
    }
}

string compute(const vector<float>& a,const vector<float>& b){
    string res = "0";
    for (int i = 0; i < a.size(); ++i) {
        string val1 = to_string(a[i]);
        string val2 = to_string(b[i]);
        string tmp = mul(val1,val2);
        res = add(res,tmp);
//        cout << res << endl;
    }
    return res;
}

int main(){
    cout << "Please input two vectors with the same length" << endl;
    float in;
    vector<float> vector1,vector2;

    while (true){
        cin >> in;
        vector1.push_back(in);
        if (cin.get() == '\n') break;
    }
    while (true){
        cin >> in;
        vector2.push_back(in);
        if (cin.get() == '\n') break;
    }

    if (vector1.size() != vector2.size()){
        cout << "You should input two vectors with the same length!" << endl;
        main();
    }
    auto start = chrono::system_clock::now();

    string out = compute(vector1,vector2);
    cout << out << endl;

    auto end = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << duration.count() <<"ms" << endl;
}