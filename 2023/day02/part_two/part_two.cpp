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

int GetLinePower(const string& line)
{
    int rv = 0;

    string actComb, item;
    vector<string> hand;
    vector<string> rgbComb;

    int actMaxR = 0;
    int actMaxG = 0;
    int actMaxB = 0;

    stringstream lineStream(line);

    while (getline(lineStream, actComb, ';')) 
    {
        hand.push_back(actComb);
    }

    for (const auto& h : hand)
    {
        stringstream handStream(h);

        while (getline(handStream, item, ',')) 
        {
            rgbComb.push_back(item);
        }

        for (auto& rgb : rgbComb)
        {
            if (containsSubstring(rgb, "red"))
            {
                int redValue = GetNumberFromPair(rgb, "red");
                if (redValue > actMaxR)
                {
                    actMaxR = redValue;
                }
            }
            else if (containsSubstring(rgb, "green"))
            {
                int greenValue = GetNumberFromPair(rgb, "green");
                if (greenValue > actMaxG)
                {
                    actMaxG = greenValue;
                }           
            }
            else if (containsSubstring(rgb, "blue"))
            {
                int blueValue = GetNumberFromPair(rgb, "blue");
                if (blueValue > actMaxB)
                {
                    actMaxB = blueValue;
                }           
            }
        }
    }

    cout << " - (" << actMaxR << ", " << actMaxG << ", " << actMaxB << ") ";	
    
    rv = actMaxR * actMaxG * actMaxB;

    cout << rv << "\n";

    return rv;
}

void solve()
{
    string line;
    string cell;
    vector<string> row;
    vector<int> linePowerValues;
    int actLinePower = 0;

    cout << "Processed lines:" << "\n\n";

    linePowerValues.clear();

    while (getline(cin, line)) 
    {       
        row.clear();

        stringstream lineStream(line);

        while (getline(lineStream, cell, ':')) 
        {
            row.push_back(cell);
        }

        cout << line;

        actLinePower = GetLinePower(row[1]);
        linePowerValues.push_back(actLinePower);          
    }

    cout << "\nResult : ";
    cout << accumulate(linePowerValues.begin(), linePowerValues.end(), 0) << "\n\n";
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