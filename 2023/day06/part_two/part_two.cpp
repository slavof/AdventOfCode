#include <bits/stdc++.h> 

using namespace std;
using i64 = long long; 

string TrimString(string s) 
{
    int start = 0;
    int end = s.length() - 1;
    
    while(start < end && isspace(s[start]))   
    {
        start++; 
    }
    
    while(end > start && isspace(s[end])) 
    {
        end--;
    }
    
    return s.substr(start, end - start + 1);
}

string CompressWhitespaces(const string& str) 
{
    string result;
    bool lastWasSpace = false;

    for (char c : str) 
    {
        if (isspace(c)) 
        {
            if (!lastWasSpace) 
            {
                result += ' ';
                lastWasSpace = true;
            }
        } 
        else 
        {
            result += c;
            lastWasSpace = false; 
        }
    }

    return result;
}

string RemoveWhitespace(string str) 
{
  str.erase(remove(str.begin(), str.end(), ' '), str.end());

  return str;
}

bool StartsWith(const string& str, const string& prefix) 
{
    if (prefix.size() > str.size())
    { 
        return false;
    }
  
    return equal(prefix.begin(), prefix.end(), str.begin());
}

string RemoveSubstring(string str, string toRemove) 
{
    size_t pos = str.find(toRemove);

    while(pos != string::npos) 
    {
        str.erase(pos, toRemove.length());
        pos = str.find(toRemove);
    }

    return str;
}

void PrintVector(string label, vector<i64> vec)
{
    int counter = 0;
        
    cout << label << "[";
    for (int i = 0; i < vec.size(); i++)
    {
        if (counter > 0)
        {
            cout << " ,";
        }

        cout << vec[i];
        counter++;
    }
    cout << "] \n";
}

void solve()
{
    i64 timeNumber = 0;
    i64 distanceNumber = 0; 

    string inputLine;
 
    while (getline(cin, inputLine)) 
    {       
        if (StartsWith(inputLine, "Time:"))
        {
            string timeStr = RemoveSubstring(inputLine, "Time:");
            timeStr = TrimString(timeStr);
            timeStr = CompressWhitespaces(timeStr);
            timeStr = RemoveWhitespace(timeStr);

            timeNumber = stoll(timeStr);
        }

        if (StartsWith(inputLine, "Distance:"))
        {
            string distanceStr = RemoveSubstring(inputLine, "Distance:");
            distanceStr = TrimString(distanceStr);
            distanceStr = CompressWhitespaces(distanceStr);
            distanceStr = RemoveWhitespace(distanceStr);

            distanceNumber = stoll(distanceStr);
        }

        if (inputLine.empty()) 
        {
            break;
        }
    }

    cout << "Time: " << timeNumber << "\n";
    cout << "Distance: " << distanceNumber << "\n";

    i64 resultCounter = 0;

    for (int j = 0; j <= timeNumber; j++)
    {
        i64 actDistance = j * (timeNumber - j);

        if (actDistance > distanceNumber)
        {
                resultCounter++;
        }
    }

    cout << "\nResult: " << resultCounter << "\n\n";
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
 