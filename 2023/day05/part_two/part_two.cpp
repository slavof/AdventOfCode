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
            cout << ", ";
        }

        cout << vec[i];
        counter++;
    }
    cout << "] \n";
}

void solve()
{
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

    string inputLine;

    string idestPart;
    vector<i64> idestVec;

    i64 globalMin = INT64_MAX;
 
    while (getline(cin, inputLine)) 
    {       
        if (StartsWith(inputLine, "seeds:"))
        {
            string seedsStr = RemoveSubstring(inputLine, "seeds:");
            seedsStr = TrimString(seedsStr);
            seedsStr = CompressWhitespaces(seedsStr);

            stringstream seedsStream(seedsStr);

            while (getline(seedsStream, idestPart, ' ')) 
            {
                idestVec.push_back(stoll(idestPart));
            }
        }

        if (inputLine.empty()) 
        {
            break;
        }
    }

    PrintVector("init seeds :\t", idestVec);  

    vector<i64> transDestStart;
    vector<i64> transSrcStart;    
    vector<i64> transRange;
    vector<int> transType;

    int counter = 0;
    for (const string& transformation : transformations)
    {
        string tLine, itLine;

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

                        transDestStart.push_back(itLineVec[0]);
                        transSrcStart.push_back(itLineVec[1]);
                        transRange.push_back(itLineVec[2]);
                        transType.push_back(counter);
                    }
                }   

                if (therewasBreak)
                {
                    break;
                } 
            }        
        }

        counter++;
    }

    for (int i = 0; i < idestVec.size(); i=i+2)
    {
        i64 start = idestVec[i];
        i64 range = idestVec[i+1];

        i64 srcNumber;
        i64 destNumber;

        i64 minDestValue = INT64_MAX;

        for (int j = 0; j < range; j++)
        {
            srcNumber = start + j;
            destNumber  = -1;

            //cout << "[ " << srcNumber << ", ";

            int tt = 0;
            for (int k = 0; k < transDestStart.size(); k++)
            {
                i64 destStart = transDestStart[k];
                i64 srcStart = transSrcStart[k];
                i64 range = transRange[k];

                if (transType[k] != tt)
                {
                    if (destNumber == -1)
                    {
                       destNumber = srcNumber;
                    }

                    //cout << destNumber << " ";

                    srcNumber = destNumber;
                    destNumber = -1;

                    tt++;
                }   

                if (srcNumber >= srcStart && srcNumber < srcStart + range)
                {
                    destNumber = destStart + (srcNumber - srcStart);
                }  
            }

            if (destNumber == -1)
            {
                destNumber = srcNumber;
            }

            if (destNumber < minDestValue)
            {
                minDestValue = destNumber;
            }

            //cout << "]\n";
        }

        cout << "min value for seeds pair: (" << start << ", " << range << ") is: " << minDestValue << "\n";

        if (minDestValue < globalMin)
        {
            globalMin = minDestValue;
        }
    }    

    cout << "\nResult : " << globalMin << "\n\n";
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
 
