#include <bits/stdc++.h> 

using namespace std;
using i64 = long long; 

vector<pair<int,int>> GetNearStars(vector<string> lines, int x, int y, int numberSize, int xSize, int ySize)
{
    vector<pair<int,int>> stars;

    // check positions directly above number
    if (y > 0)
    {
        for (int i = x; i < x + numberSize; i++)
        {
            if (lines[y - 1][i] == '*')
            {
                stars.push_back(make_pair(y - 1, i));
            }
        }
    }

    // check positions directly bellow number
    if (y < ySize - 1)
    {
        for (int i = x; i < x + numberSize; i++)
        {
            if (lines[y + 1][i] == '*')
            {
                stars.push_back(make_pair(y + 1, i));
            }
        }
    }

    // check positions left of number
    if (x > 0) 
    {
        if (lines[y][x - 1] == '*')
        {
            stars.push_back(make_pair(y, x - 1));
        }  

        if ((y-1) >= 0)
        {
            if (lines[y - 1][x - 1] == '*')
            {
                stars.push_back(make_pair(y - 1, x - 1));
            }
        }

        if ((y+1) < ySize) 
        {
            if (lines[y + 1][x - 1] == '*')
            {
                stars.push_back(make_pair(y + 1, x - 1));
            }
        }          
    }

    // check positions right of number
    if((x + numberSize) < xSize) 
    {
        if (lines[y][x + numberSize] == '*')
        {
            stars.push_back(make_pair(y, x + numberSize));
        }    

        if ((y-1) >= 0)
        {
            if (lines[y - 1][x + numberSize] == '*')
            {
                stars.push_back(make_pair(y - 1, x + numberSize));
            }
        }

        if ((y+1) < ySize) 
        {
            if (lines[y + 1][x + numberSize] == '*')
            {
                stars.push_back(make_pair(y + 1, x + numberSize));
            }
        }
    }

    return stars;
}

void solve()
{
    vector<int> numbers;
    vector<string> lines;
    int x = 0, y = 0;
    string actNumber;
    int actNumStartX = -1, actNumStartY = -1;

    map<pair<int,int>, string> gears;
  
    string line;
    while (getline(cin, line)) 
    {
        lines.push_back(line); 
    }

    x = lines[0].size();
    y = lines.size();

    cout << "Found gears:" << "\n\n";

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
                    vector<pair<int,int>> stars = GetNearStars(lines, actNumStartX, actNumStartY, actNumber.size(), x, y);

                    for (auto star : stars)
                    {
                        if (gears[star].size() == 0)
                        {
                            gears[star] = gears[star].append(actNumber); 
                        }
                        else
                        {
                            gears[star] = gears[star].append("," + actNumber);                        
                        }
                    }

                    actNumber.clear();
                }
            }
        }
    }

    for (auto gear : gears)
    {
        int gearValue = 1;
        string numbersAsStr;
        vector<int> gearNumbers;

        stringstream lineStream(gear.second);

        while (getline(lineStream, numbersAsStr, ',')) 
        {
            gearNumbers.push_back(stoi(numbersAsStr));
        }

        if (gearNumbers.size() == 2)
        {
            for (const auto& gn : gearNumbers)
            {
                gearValue = gearValue * gn;
            } 

            numbers.push_back(gearValue);

            cout << "star [" << gear.first.first << "," << gear.first.second << "] : ";
            cout << gear.second << " (" << gearValue << ") \n";
        }
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
 