//*******************************************************************
//    			START OF PROJECT
//*******************************************************************

#include <bits/stdc++.h>
using namespace std;

//*******************************************************************
//    			CLASS BEGINS
//*******************************************************************

class Attack
{
    vector<vector<int>> grid;
    vector<vector<pair<int, int>>> terrorist;

public:
    //***************************************************************
    //    	    FUNCTION TO INPUT A COMPLETE GRID/MAZE
    //***************************************************************

    void Take_grid(vector<vector<int>> v)
    {
        grid = v;
        int k = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] == 1)
                {
                    grid[i][j] = pow(2, k++);
                    terrorist.push_back({{i, j}});
                }
            }
        }
    }

    //***************************************************************
    //    	    FUNCTION TO MAKE A GRID OF GIVEN DIMENSIONS
    //***************************************************************

    void Make_grid(int n, int m)
    {
        vector<vector<int>> v(n, vector<int>(m, 0));
        grid = v;
    }

    //***************************************************************
    //          FUNCTION TO GET POSITION OF TERRORISTS
    //***************************************************************

    void Position_terrorists(vector<pair<int, int>> v)
    {
        for (int i = 0; i < v.size(); i++)
        {
            terrorist[i].push_back(v[i]);
        }

        // storing position of terrorists in grid by giving each terrorist an unique number
        for (int i = 0; i < v.size(); i++)
            grid[v[i].first][v[i].second] = pow(2, i);
    }

    //***************************************************************
    //          FUNCTION TO GET POSITION OF WALLS
    //***************************************************************

    void Position_walls(vector<pair<int, int>> v)
    {
        for (int i = 0; i < v.size(); i++)
            grid[v[i].first][v[i].second] = -1;
    }

    //***************************************************************
    //    	    FUNCTION TO DETERMINE THE ESCAPE PATH OF TERRORISTS
    //***************************************************************

    void Escape()
    {
        for (int i = 0; i < terrorist.size(); i++)
        {
            BFS(terrorist[i][0].first, terrorist[i][0].second, i);
        }
    }

    //*****************************************************************************************************************
    //    	    FUNCTION TO IMPLEMENT BREADTH FIRST SEARCH ALGORITHM TO FIND SHORTEST PATH OUT OF MAZE FOR EACH TERRORIST
    //*****************************************************************************************************************

    void BFS(int x, int y, int n)
    {
        vector<vector<int>> path(grid.size(), vector<int>(grid[0].size(),
                                                          0));
        queue<pair<int, int>> Q;
        int rshift[] = {1, -1, 0, 0}, cshift[] = {0, 0, 1, -1};
        Q.push({x, y});
        path[x][y] = 5;
        while (!Q.empty())
        {
            pair<int, int> box;
            box = Q.front();
            Q.pop();
            for (int i = 0; i < 4; i++)
            {
                int new_x = box.first + rshift[i], new_y = box.second +
                                                           cshift[i];
                if (new_x >= grid.size() || new_x < 0 || new_y >= grid[0].size() || new_y < 0)
                {
                    Escape_path(box.first, box.second, path, n);
                    return;
                }
                if (grid[new_x][new_y] == -1)
                    continue;
                if (path[new_x][new_y] != 0)
                    continue;
                path[new_x][new_y] = i + 1;
                Q.push({new_x, new_y});
            }
        }
    }

    //*********************************************************************
    //    	    FUNCTION FOR BACKTRACKING OF ESCAPE PATH
    //*********************************************************************

    void Escape_path(int x, int y, vector<vector<int>> path, int n)
    {
        stack<pair<int, int>> route;
        int rshift[] = {1, -1, 0, 0}, cshift[] = {0, 0, 1, -1};
        while (path[x][y] != 5)
        {
            // making a stack of co-ordinates of each box in escape path from ending position to starting position
            route.push({x, y});
            for (int i = 1; i <= 4; i++)
            {
                if (path[x][y] == i)
                {
                    x = x - rshift[i - 1];
                    y = y - cshift[i - 1];
                    break;
                }
            }
        }

        // reversing the stack and storing the elements in terrorist[n]
        while (!route.empty())
        {
            terrorist[n].push_back(route.top());
            route.pop();
        }
    }

    //*********************************************************************
    //    	    FUNCTION TO FIND THE POSITIONS WHERE BOMBS CAN BE THROWN
    //*********************************************************************

    void BFS_Spread()
    {
        vector<vector<int>> count = grid;
        for (int i = 0; i < terrorist.size(); i++)
        {
            int Time = terrorist[i].size();
            stack<pair<int, int>> s_curr, s_next;
            s_curr.push(terrorist[i][Time - 1]);
            for (int j = 0; j < Time; j++)
            {
                pair<int, int> box;
                while (!s_curr.empty())
                {
                    box = s_curr.top();
                    s_curr.pop();
                    for (int p = -1; p <= 1; p++)
                        for (int q = -1; q <= 1; q++)
                        {
                            int x = box.first + p;
                            int y = box.second + q;
                            if (x >= grid.size() || y >= grid.size() || x < 0 || y < 0)
                                continue;
                            if (count[x][y] == -1)
                                continue;
                            count[x][y] = count[x][y] | (1 << i);
                            s_next.push({x, y});
                        }
                }
                while (!s_next.empty())
                {
                    s_curr.push(s_next.top());
                    s_next.pop();
                }
            }
        }
        cout << endl
             << "Positions where bombs can be dropped :  " << endl
             << endl;
        cout << " Y Co-ordinates"
             << " "
             << "           X Co-ordinates" << endl;
        for (int i = 0; i < count.size(); i++)
        {
            for (int j = 0; j < count[0].size(); j++)
            {
                if (count[i][j] == pow(2, terrorist.size()) - 1)
                    cout << "      " << i + 1 << "\t\t\t\t" << j + 1 << endl;
            }
        }
    }

    //********************************************************************
    //    	    INTRODUCTION FUNCTION
    //********************************************************************

    void intro()
    {
        cout << "TERROR ATTACK";
        cout << "\nMADE BY : DEEPAK SINGH (2K20/MC/38)\n";
        cout << "          ABHISHEK AGGARWAL (2K20/MC/06)";
        cout << "\nCOLLEGE : DELHI TECHNOLOGICAL UNIVERSITY\n";
    }

    //*********************************************************************
    //    	    DROPBOMB FUNCTION
    //*********************************************************************

    void DropBomb(vector<vector<int>> Grid)
    {
        Take_grid(Grid);
        Escape();
        BFS_Spread();
    }
};

//*************************************************************************
//    	        MAIN FUNCTION
//*************************************************************************

int main()
{
    Attack A;
    vector<vector<int>> grid =
        {{-1, -1, 0, -1, -1, -1, -1},
         {0, 0, 0, -1, -1, 1, -1},
         {-1, -1, 1, 0, 0, 0, -1},
         {-1, -1, -1, 0, 1, -1, -1},
         {-1, 1, -1, 0, 0, 0, 0},
         {-1, 0, 0, -1, -1, -1, -1},
         {0, -1, 0, 0, 0, -1, 0}};

    A.intro();

    // 0 are empty spaces, 1 are terrorists, -1 are the walls in the maze
    A.DropBomb(grid);
    return 0;
}

//****************************************************************************
//    			END OF PROJECT
//****************************************************************************