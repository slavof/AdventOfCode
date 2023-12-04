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

void solve()
{
    vector<int> cardPoints;

    string cardLine;

    string cardPart;
    vector<string> cardVec;

    vector<string> cardNumbers;
    string numbersPart;

    vector<int> winNumbers;
    string winNumStr;

    vector<int> handNumbers;
    string handNumStr;    

    int counter = 0;
    int actCardPoints = 0;

    cout << "Processed cards:" << "\n\n";

    while (getline(cin, cardLine)) 
    {       
        actCardPoints = 0;

        cardVec.clear();    
        cardNumbers.clear();    
        winNumbers.clear();
        handNumbers.clear();   

        stringstream lineStream(cardLine);

        while (getline(lineStream, cardPart, ':')) 
        {
            cardVec.push_back(cardPart);
        }

        stringstream numbersStream(cardVec[1]);

        while (getline(numbersStream, numbersPart, '|'))   
        {
            cardNumbers.push_back(numbersPart);
        }

        string winNumbersStr = TrimString(cardNumbers[0]);
        winNumbersStr = CompressWhitespaces(winNumbersStr);

        stringstream winnersStream(winNumbersStr);
        while (getline(winnersStream, winNumStr, ' '))   
        {
            winNumbers.push_back(stoi(winNumStr));
        }

        string handNumbersStr = TrimString(cardNumbers[1]);
        handNumbersStr = CompressWhitespaces(handNumbersStr);

        stringstream handStream(handNumbersStr);
        while (getline(handStream, handNumStr, ' '))   
        {
            handNumbers.push_back(stoi(handNumStr));
        }        

        sort(winNumbers.begin(), winNumbers.end()); 
        sort(handNumbers.begin(), handNumbers.end()); 

        vector<int> commonNumbers(winNumbers.size() + handNumbers.size()); 
        vector<int>::iterator it, st; 
  
        it = set_intersection(winNumbers.begin(),  winNumbers.end(), 
                              handNumbers.begin(), handNumbers.end(), 
                              commonNumbers.begin()); 
  
        counter = 0;
        cout << cardVec[0] << " : ("; 

        for (st = commonNumbers.begin(); st != it; ++st) 
        {
            if (counter > 0)
            {
                cout << ", " ;
            }
            cout << *st ; 
            counter++;
        }
        cout << ")"; 

        actCardPoints = pow(2, counter - 1);
        cardPoints.push_back(actCardPoints);

        cout << " -> " << actCardPoints << " points \n";

    }

    cout << "\nResult : ";
    cout << accumulate(cardPoints.begin(), cardPoints.end(), 0) << "\n\n";

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