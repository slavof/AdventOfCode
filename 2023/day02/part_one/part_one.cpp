#include <bits/stdc++.h> 

using namespace std;
using i64 = long long; 

bool containsSubstring(const string& str, const string& sub) 
{
  return str.find(sub) != string::npos; 
}

int stringToInt(const string& str) 
{
    int result = 0;
  
    stringstream ss(str);
    ss >> result;

    return result;
}

void EraseSubstring(string& str, const string& sub)
{
    string::size_type i = str.find(sub);
    if (i != string::npos)
    {
        str.erase(i, sub.length());
    }
}

int GetNumberFromPair(string& str, const string& sub) 
{
    int result = 0;
    
    EraseSubstring(str, sub);

    result = stringToInt(str);

    return result;
}

bool IsCombCorrect(const string& line)
{
    bool result = true;
    string item;
    vector<string> hand;

    int r = 12;
    int g = 13;
    int b = 14;

    stringstream lineStream(line);

    while (getline(lineStream, item, ',')) 
    {
        hand.push_back(item);
    }

    for (auto& h : hand)
    {
        if (containsSubstring(h, "red"))
        {
            int redValue = GetNumberFromPair(h, "red");
            if (redValue > r)
            {
                result = false;
                cout << h << "red (NOT OK)";
                break;
            }
            else
            {
                cout << h << "red (OK)";
            }
        }
        else if (containsSubstring(h, "green"))
        {
            int greenValue = GetNumberFromPair(h, "green");
            if (greenValue > g)
            {
                result = false;
                cout << h << "green (NOT OK)";
                break;
            }
            else
            {
                cout << h << "green (OK)";
            }            
        }
        else if (containsSubstring(h, "blue"))
        {
            int blueValue = GetNumberFromPair(h, "blue");
            if (blueValue > b)
            {
                result = false;
                cout << h << "blue (NOT OK)";
                break;
            }
            else
            {
                cout << h << "blue (OK)";
            }            
        }
    }

    return result;
}

bool IsLineCorrect(const string& line)
{
    bool result = true;
    string comb;
    vector<string> hand;

    stringstream lineStream(line);

    while (getline(lineStream, comb, ';')) 
    {
        hand.push_back(comb);
    }

    for (const auto& h : hand)
    {
        if (!IsCombCorrect(h))
        {
            result = false;
            break;
        }
    }

    return result;
}

void solve()
{
    string line;
    string cell;
    vector<string> row;
    vector<int> correctLines;
    int actLineId = 0;

    cout << "Processed lines:" << "\n\n";

    while (getline(cin, line)) 
    {       
        row.clear();

        stringstream lineStream(line);

        while (getline(lineStream, cell, ':')) 
        {
            row.push_back(cell);
        }

        cout << row[0] << ":";

        if (IsLineCorrect(row[1]))
        {
            actLineId = GetNumberFromPair(row[0], "Game ");
            correctLines.push_back(actLineId);
            cout << " - LINE OK" << "\n";
        }       
        else
        {
            cout << " - LINE NOT OK" << "\n";
        } 
    }

    cout << "\nResult : ";
    cout << accumulate(correctLines.begin(), correctLines.end(), 0) << "\n\n";
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