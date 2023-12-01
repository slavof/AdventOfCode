#include <bits/stdc++.h> 

using namespace std;
using i64 = long long; 

bool substringExists(const string& str, const string& sub, size_t startPos) 
{
    if (startPos >= str.length()) 
    {
        return false; 
    }

    size_t subLen = sub.length();
    size_t maxStart = str.length() - subLen;

    if (startPos > maxStart) 
    {
        return false; 
    }

    if (str.substr(startPos, subLen) == sub) 
    {
        return true;
    }

    return false;
}

void solve()
{
    string line;
    int firstdigit = -1, lastdigit = -1;
    int strnumber = 0;
    int sum = 0;
    int pos = 0, strpos = 0;

    array<string, 9> strings = {"one", "two", "three", "four", 
                                "five", "six", "seven", "eight", "nine" };

    cout << "Processed lines:" << "\n\n";

    while (getline(cin, line)) 
    {
        firstdigit = -1; 
        lastdigit = -1;
        pos = 0;

        for (char c : line) 
        {
            if (isdigit(c)) 
            {
                if (firstdigit == -1)
                {
                    firstdigit = c - '0';
                }

                lastdigit = c - '0';
            }

            strpos = 0;
            for (auto& s : strings)
            {
                if (substringExists(line, s, pos))
                {
                    if (firstdigit == -1)
                    {
                        firstdigit = strpos + 1;
                    }

                    lastdigit = strpos + 1;

                    break;
                }
                
                strpos++;
            }

            pos++;
        }

        sum += ((firstdigit * 10) + lastdigit);

        cout << line << " " << firstdigit << lastdigit << " " << sum << "\n";
    }

    cout << "\n" << "Result:" << sum << "\n\n";
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
    using clock = chrono::high_resolution_clock;
    auto start = clock::now();
    #endif

    // i64 t;
    // cin >> t;
    
    // while (t--) 
    // {
        solve();
    // }

    #ifndef ONLINE_JUDGE
    auto end = clock::now();
    auto us = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Operation took " << us << " microseconds." << endl;
    #endif

    return 0;
}