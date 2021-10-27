#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
using namespace std;

vector<char> ops = {'+', '-', '*', '/', '%', '=', '&', '|', '^'};

bool isOperator(char c) {
    if (any_of(ops.begin(), ops.end(), [&](auto a)
               { return a == c; }))
        return true;
    return false;
}
bool isNum(string sub) {
    if (any_of(sub.begin(), sub.end(), [&](auto a) { 
        return a >= '0' && a <= '9'; 
        }))
        return true;
    return false;
}

int main() {
    cout << "Enter a valid equation: \n\n";
    string s;
    getline(cin, s);
    string ans = "", res = "";
    vector<pair<ll, ll>> oper;
    for (auto it : s) {
        if (it != ' ')
            res += it;
    }
    for (ll i = 0; i < res.length(); i++) {
        if (isOperator(res[i])) {
            if (i + 1 < res.length() && isOperator(res[i + 1]))
                oper.push_back({i, i + 1}), i++;
            else
                oper.push_back({i, i});
        }
    }
    string sub = res.substr(0, oper[0].first);
    string id = "id,";
    ll n = oper.size(), nxt = 1;
    ans += '<' + id + to_string(nxt) + '>' + '<' + res[oper[0].first];
    if (oper[0].first != oper[0].second)
        ans += res[oper[0].second];
    ans += '>';
    nxt++;
    for (ll i = 1; i < n; i++) {
        sub = res.substr(oper[i - 1].second + 1, oper[i].first - oper[i - 1].second - 1);
        if (isNum(sub))
            ans += '<' + sub + '>';
        else
            ans = ans + '<' + id + to_string(nxt) + '>', nxt++;
        ans = ans + '<' + res[oper[i].first];
        if (oper[i].first != oper[i].second)
            ans += res[oper[i].second];
        ans += '>';
    }
    if (!isOperator(res[res.size() - 1])) {
        sub = res.substr(oper[n - 1].second + 1, res.size() - oper[n - 1].second);
        if (isNum(sub))
            ans += '<' + sub + '>';
        else
            ans = ans + '<' + id + to_string(nxt) + '>', nxt++;
    }
    cout << "\n"
         << ans << "\n";
}