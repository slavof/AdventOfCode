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
    string inputLine;

    string srcPart;
    vector<i64> srcVec;

    string destPart;
    vector<i64> destVec;
 
    while (getline(cin, inputLine)) 
    {       
        if (StartsWith(inputLine, "seeds:"))
        {
            string seedsStr = RemoveSubstring(inputLine, "seeds:");
            seedsStr = TrimString(seedsStr);
            seedsStr = CompressWhitespaces(seedsStr);

            stringstream seedsStream(seedsStr);

            while (getline(seedsStream, destPart, ' ')) 
            {
                destVec.push_back(stoll(destPart));
            }
        }

        if (inputLine.empty()) 
        {
            break;
        }
    }

    PrintVector("seeds :\t\t\t", destVec);

    for (int i = 0; i < destVec.size(); i++)
    {
        srcVec.push_back(-1);
    }

    vector<string> transformations 
    {
        "seed-to-soil map:",
        "soil-to-fertilizer map:",
        "fertilizer-to-water map:",
        "water-to-light map:",
        "light-to-temperature map:",
        "temperature-to-humidity map:",
        "humidity-to-location map:"
    };

    vector<string> labels 
    {
        "soil :\t\t\t",
        "fertilizer :\t",
        "water :\t\t\t",
        "light :\t\t\t",
        "temperature :\t",
        "humidity :\t\t",
        "location :\t\t"
    };

    int counter = 0;
    for (const string& transformation : transformations)
    {
        string tLine, itLine;

        for (int i = 0; i < destVec.size(); i++)
        {
            srcVec[i] = destVec[i];
            destVec[i] = -1;
        }

        bool therewasBreak = false;
        while (getline(cin, tLine)) 
        {
            if (StartsWith(tLine, transformation))
            {
                while (getline(cin, itLine)) 
                {
                    if (itLine.empty()) 
                    {
                        therewasBreak = true;
                        break;
                    }
                    else
                    {
                        vector<i64> itLineVec;
                        string itLinePart;

                        string itLineStr = TrimString(itLine);
                        itLineStr = CompressWhitespaces(itLineStr);

                        stringstream itLineStream(itLineStr);

                        while (getline(itLineStream, itLinePart, ' ')) 
                        {
                            itLineVec.push_back(stoll(itLinePart));
                        }

                        i64 destStart = itLineVec[0];
                        i64 srcStart = itLineVec[1];
                        i64 range = itLineVec[2];

                        for (int i = 0; i < srcVec.size(); i++)
                        {
                            if (srcVec[i] >= srcStart && srcVec[i] < srcStart + range)
                            {
                                int diff = srcVec[i] - srcStart;
                                destVec[i] = destStart + (srcVec[i] - srcStart);
                            }
                        }
                    }

                }

                if (therewasBreak)
                {
                    break;
                }
            }
        }

        for (int i = 0; i < srcVec.size(); i++)
        {
            if (destVec[i] == -1)
            {
                destVec[i] = srcVec[i];
            }
        }

        PrintVector(labels[counter], destVec);
        counter++;
    }

    auto minDestElem = min_element(destVec.begin(), destVec.end());
    int minDestValue = *minDestElem; 

    cout << "\nResult : " << minDestValue << "\n\n";
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
 