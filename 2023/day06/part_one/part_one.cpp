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
    i64 result = 1;
    vector<i64> resultsVec;

    string inputLine;

    string timePart;
    vector<i64> timeVec;

    string distancePart;
    vector<i64> distanceVec;
 
    while (getline(cin, inputLine)) 
    {       
        if (StartsWith(inputLine, "Time:"))
        {
            string timeStr = RemoveSubstring(inputLine, "Time:");
            timeStr = TrimString(timeStr);
            timeStr = CompressWhitespaces(timeStr);

            stringstream timeStream(timeStr);

            while (getline(timeStream, timePart, ' ')) 
            {
                timeVec.push_back(stoll(timePart));
            }
        }

        if (StartsWith(inputLine, "Distance:"))
        {
            string distanceStr = RemoveSubstring(inputLine, "Distance:");
            distanceStr = TrimString(distanceStr);
            distanceStr = CompressWhitespaces(distanceStr);

            stringstream distanceStream(distanceStr);

            while (getline(distanceStream, distancePart, ' ')) 
            {
                distanceVec.push_back(stoll(distancePart));
            }
        }

        if (inputLine.empty()) 
        {
            break;
        }
    }

    PrintVector("Time :\t\t", timeVec);
    PrintVector("Distance :\t", distanceVec);

    for (int i = 0; i < timeVec.size(); i++)
    {
        i64 actTime = timeVec[i];
        i64 actMaxDistance = distanceVec[i];

        i64 resultCounter = 0;

        for (int j = 0; j <= actTime; j++)
        {
            i64 actDistance = j * (actTime - j);

            if (actDistance > actMaxDistance)
            {
                resultCounter++;
            }
        }

        resultsVec.push_back(resultCounter);
    }

    for (int i = 0; i < resultsVec.size(); i++)
    {
        result = result * resultsVec[i];
    }

    cout << "\nResult : " << result << "\n\n";
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
 