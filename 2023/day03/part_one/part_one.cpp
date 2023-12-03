#include <bits/stdc++.h> 

using namespace std;
using i64 = long long; 

bool IsValidSymbol(char symbol)
{
    if (symbol == '.' || isdigit(symbol) || isalpha(symbol))
    {
        return false;
    }

    return true;
}


bool IsSymbolNear(vector<string> lines, int x, int y, int numberSize, int xSize, int ySize)
{
    // check positions directly above number
    if (y > 0)
    {
        for (int i = x; i < x + numberSize; i++)
        {
            if (IsValidSymbol(lines[y - 1][i]))
            {
                return true;
            }
        }
    }

    // check positions directly bellow number
    if (y < ySize - 1)
    {
        for (int i = x; i < x + numberSize; i++)
        {
            if (IsValidSymbol(lines[y + 1][i]))
            {
                return true;
            }
        }
    }

    // check positions left of number
    if (x > 0) 
    {
        if (IsValidSymbol(lines[y][x - 1]))
        {
            return true;
        }  

        if ((y-1) >= 0)
        {
            if (IsValidSymbol(lines[y - 1][x - 1]))
            {
                return true;
            }
        }

        if ((y+1) < ySize) 
        {
            if (IsValidSymbol(lines[y + 1][x - 1]))
            {
                return true;
            }
        }          
    }

    // check positions right of number
    if((x + numberSize) < xSize) 
    {
        if (IsValidSymbol(lines[y][x + numberSize]))
        {
            return true;
        }    

        if ((y-1) >= 0)
        {
            if (IsValidSymbol(lines[y - 1][x + numberSize]))
            {
                return true;
            }
        }

        if ((y+1) < ySize) 
        {
            if (IsValidSymbol(lines[y + 1][x + numberSize]))
            {
                return true;
            }
        }
    }

    return false;
}

void solve()
{
    vector<int> numbers;
    vector<string> lines;
    int x = 0, y = 0;
    string actNumber;
    int actNumStartX = -1, actNumStartY = -1;
  
    string line;
    while (getline(cin, line)) 
    {
      lines.push_back(line); 
    }

    x = lines[0].size();
    y = lines.size();

    cout << "Found numbers:" << "\n\n";

    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < x; j++)
        {
            if (isdigit(lines[i][j]))
            {
                if (actNumber.size() == 0)
                {
                    actNumStartX = j;
                    actNumStartY = i;
                }

                actNumber.append(1, lines[i][j]);                
            }
            else
            {
                if (actNumber.size() > 0)
                {
                    if (IsSymbolNear(lines, actNumStartX, actNumStartY, actNumber.size(), x, y))
                    {
                        numbers.push_back(stoi(actNumber));
                        cout << actNumber << " (OK) ";
                    }
                    else
                    {
                        cout << actNumber << " (NOT OK) ";
                    }

                    actNumber.clear();
                }
            }
        }
        cout << "\n";
    }

    cout << "\nResult : ";
    cout << accumulate(numbers.begin(), numbers.end(), 0) << "\n\n";
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