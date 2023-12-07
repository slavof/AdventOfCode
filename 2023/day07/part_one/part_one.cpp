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

vector<int> charFrequency(const string& str) 
{
    vector<int> rv;
    vector<int> freq(256, 0);
    
    for(char c : str) 
    {
        freq[c]++; 
    }

    for(int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            rv.push_back(freq[i]);
        }
    }
    
    return rv;
}

int CardValue(char c)
{
    if (c == 'A')
    {
        return 14;
    }
    else if (c == 'K')
    {
        return 13;
    }
    else if (c == 'Q')
    {
        return 12;
    }
    else if (c == 'J')
    {
        return 11;
    }
    else if (c == 'T')
    {
        return 10;
    }
    else
    {
        return (c - '0');
    }
}

bool CardCompare(vector<string> hand, vector<int> handType, int p, int q)
{
    if (handType[p] > handType[q])
    {
        return true;
    }
    else if (handType[p] < handType[q])
    {
        return false;
    }
    else // (handType[p] == handType[q])
    {
        int pValue = 0;
        int qValue = 0;

        for (int i = 0; i < hand[0].size(); i++)
        {
            pValue = CardValue(hand[p][i]);
            qValue = CardValue(hand[q][i]);

            if (pValue > qValue)
            {
                return true;
            }
            else if (pValue < qValue)
            {
                return false;
            }
            else // (pValue == qValue)
            {
                continue;
            }
        }
    }

    return false;
}

string GetHandType(int handType)
{
    if (handType == 7)
    {
        return "Five of a kind";
    }
    else if (handType == 6)
    {
        return "Four of a kind";
    }
    else if (handType == 5)
    {
        return "Full house";
    }
    else if (handType == 4)
    {
         return "Three of a kind";
    }
        else if (handType == 3)
    {
        return "Two pair";
    }
    else if (handType == 2)
    {
        return "One pair";
    }
    else if (handType == 1)
    {
         return "High card";
    }
    else
    {
        return "UNKNOWN";
    }

    return "UNKNOWN";
}

void solve()
{
    i64 result = 0;
    vector<i64> resultsVec;

    string inputLine;

    string inputPart;
    vector<string> inputVec;

    vector<string> hand;
    vector<i64> bid;

    int counter = 0;

    while (getline(cin, inputLine)) 
    {       
        inputVec.clear();

        string inputStr = TrimString(inputLine);
        inputStr = CompressWhitespaces(inputStr);

        stringstream inputStream(inputStr);

        while (getline(inputStream, inputPart, ' ')) 
        {
            inputVec.push_back(inputPart);
        }

        hand.push_back(inputVec[0]);
        bid.push_back(stoll(inputVec[1]));

        if (inputLine.empty()) 
        {
            break;
        }
    }

    vector<int> handType(hand.size(), 0);

    for (int i = 0; i < hand.size(); i++)
    {
        int max = 0;
        int ones = 0;
        int twos = 0;

        vector<int> freq = charFrequency(hand[i]);

        for (int j = 0; j < freq.size(); j++)
        {
            if (freq[j] > max)
            {
                max = freq[j];
            }

            if (freq[j] == 1)
            {
                ones++;
            }

            if (freq[j] == 2)
            {
                twos++;
            }
        }        
        
        if (max == 5)
        {
            handType[i] = 7; // FiveOfKind
        }
        else if (max == 4)
        {
            handType[i] = 6; // FourOfKind
        }
        else if (max == 3)
        {
            if (twos > 0)
            {
                handType[i] = 5; // FullHouse
            }
            else
            {
                handType[i] = 4; // ThreeOfKind
            }            
        }
        else if (max == 2)
        {
            if (twos > 1)
            {
                handType[i] = 3; // TwoPairs
            }
            else
            {
                handType[i] = 2; // OnePair
            }   
        }
        else
        {
            handType[i] = 1; // HighCard
        }        
    }

    bool swapped = true;

    int n = hand.size();
    while (swapped) 
    {
        swapped = false;
        
        for (int i = 1; i < n; i++) 
        {    
            //if (vec[i - 1] < vec[i]) 
            if (CardCompare(hand, handType, i-1, i))
            {
                std::swap(hand[i - 1], hand[i]);
                std::swap(bid[i - 1], bid[i]);
                std::swap(handType[i - 1], handType[i]);
                swapped = true; 
            }
        }

        n--;
    }    

    cout << "Results : \n\n";
    
    for (int k = 0; k < bid.size() ; k++)
    {
        result = result + (bid[k] * (k+1));
        cout << hand[k] << " " << bid[k] 
             << " (" << GetHandType(handType[k]) << ") " 
             << result << " \n";
    }

    cout << "\nTotal winnings : " << result << "\n\n";
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