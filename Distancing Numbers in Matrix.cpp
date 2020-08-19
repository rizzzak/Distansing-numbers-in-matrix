// Distancing Numbers in Matrix.cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int DirX[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
int DirY[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
void printMatrInt(vector<vector<int>> matr, string name)
{
    cout << "\n" << name << ", size = " << matr.size() << ": \n";
    for (int i = 0; i < matr.size(); i++)
    {
        for (int j = 0; j < matr[i].size(); j++)
        {
            cout << " " << matr[i][j];
        }
        cout << "\n";
    }
}
//Greatest Common Divisor. Condition of task - must be equal to 1.
long gcd(long a, long b) {
    long nod = 1L;
    long tmp;
    if (a == 0L)
        return b;
    if (b == 0L)
        return a;
    if (a == b)
        return a;
    if (a == 1L || b == 1L)
        return 1L;
    while (a != 0 && b != 0) {
        if (((a & 1L) | (b & 1L)) == 0L) {
            nod <<= 1L;
            a >>= 1L;
            b >>= 1L;
            continue;
        }
        if (((a & 1L) == 0L) && (b & 1L)) {
            a >>= 1L;
            continue;
        }
        if ((a & 1L) && ((b & 1L) == 0L)) {
            b >>= 1L;
            continue;
        }
        if (a > b) {
            tmp = a;
            a = b;
            b = tmp;
        }
        tmp = a;
        a = (b - a) >> 1L;
        b = tmp;
    }
    if (a == 0)
        return nod * b;
    else
        return nod * a;
}
inline bool isConficting(int &num1, int &num2)
{
    if (gcd(num1, num2) > 1)
        return true;
    else
        return false;
}
void printVectorInt(vector<int> vec, string name)
{
    cout << "\n" << name << ", size = " << vec.size() << ": ";
    for (int i = 0; i < vec.size(); i++)
        cout <<  " " << vec[i];
}
inline bool isIndexOutOfBounds(int index, int bound1, int bound2)
{
    if ((index <= bound2) && (index >= bound1))
        return false;
    else
        return true;
}
bool isBoardHaveConflicts(vector<vector<int>>& board, bool mute)
{
    for(int i = 0; i < board.size(); i++)
        for (int j = 0; j < board.size(); j++)
        {
            int num1 = board[i][j];
            if (num1 == 0)
                continue;
            if(!mute) cout << "\nNumber 1 checking: " << num1;
            int num2;
            for (int k = 0; k < 8; k++)
            {
                int dx = i + DirX[k];
                int dy = j + DirY[k];
                if (isIndexOutOfBounds(dx, 0, board.size() - 1))
                    continue;
                else if (isIndexOutOfBounds(dy, 0, board.size() - 1))
                    continue;
                else
                {
                    num2 = board[dx][dy];
                    if (!mute) cout << "\n\tCurrent number 2: " << num2;
                    if (num2 == 0)
                    {
                        if (!mute) cout << ". Null element, skipping.";
                        continue;
                    }
                    else if (isConficting(num1, num2))
                    {
                        if (!mute) cout << ". Seems like numbers conflicting. Returning True.";
                        return true;
                    }
                }
            }
        }
    return false;
}
void wallCenterConfilct(vector<int>& possibleMoves, vector<vector<int>>& board)
{
    int num1 = board[1][2];//first wall cell
    int num2 = board[2][2];//center cell
    if (isConficting(num1, num2))
        possibleMoves[6] = 0;
    num1 = board[2][1];
    if (isConficting(num1, num2))
        possibleMoves[14] = 0;
    num1 = board[2][3];
    if (isConficting(num1, num2))
        possibleMoves[16] = 0;
    num1 = board[3][2];
    if (isConficting(num1, num2))
        possibleMoves[24] = 0;
}
void cornerWallWallConfilct(vector<int>& possibleMoves, vector<vector<int>>& board)
{
    int num1 = board[1][1];//corner cell
    int num2 = board[1][2];//wall cell
    if (isConficting(num1, num2))
    {
        num2 = board[2][1];
        if (isConficting(num1, num2))
        {
            possibleMoves[0] = 0;
            possibleMoves[1] = 0;
            possibleMoves[2] = 0;
            possibleMoves[3] = 0;
            possibleMoves[4] = 0;
        }
    }
    num1 = board[1][3];//corner cell
    num2 = board[1][2];//wall cell
    if (isConficting(num1, num2))
    {
        num2 = board[2][3];
        if (isConficting(num1, num2))
        {
            possibleMoves[8] = 0;
            possibleMoves[9] = 0;
            possibleMoves[10] = 0;
            possibleMoves[11] = 0;
            possibleMoves[12] = 0;
        }
    }
    num1 = board[3][1];//corner cell
    num2 = board[2][1];//wall cell
    if (isConficting(num1, num2))
    {
        num2 = board[3][2];
        if (isConficting(num1, num2))
        {
            possibleMoves[18] = 0;
            possibleMoves[19] = 0;
            possibleMoves[20] = 0;
            possibleMoves[21] = 0;
            possibleMoves[22] = 0;
        }
    }
    num1 = board[3][3];//corner cell
    num2 = board[2][3];//wall cell
    if (isConficting(num1, num2))
    {
        num2 = board[3][2];
        if (isConficting(num1, num2))
        {
            possibleMoves[26] = 0;
            possibleMoves[27] = 0;
            possibleMoves[28] = 0;
            possibleMoves[29] = 0;
            possibleMoves[30] = 0;
        }
    }
}
bool H_move_away(int &num1x, int &num1y, vector<vector<int>> &board)
{
    if (!isIndexOutOfBounds(num1x, 1,3)&&(num1y == 1))
    {
        if (board[num1x][num1y - 1] == 0)
        {
            board[num1x][num1y - 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if (!isIndexOutOfBounds(num1x, 1, 3) && (num1y == 3))
    {
        if (board[num1x][num1y + 1] == 0)
        {
            board[num1x][num1y + 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    return true;
}
bool V_move_away(int& num1x, int& num1y, vector<vector<int>> &board)
{
    if (!isIndexOutOfBounds(num1y, 1, 3) && (num1x == 1))
    {
        if (board[num1x - 1][num1y] == 0)
        {
            board[num1x - 1][num1y] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if (!isIndexOutOfBounds(num1y, 1, 3) && (num1x == 3))
    {
        if (board[num1x + 1][num1y] == 0)
        {
            board[num1x + 1][num1y] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    return true;
}
bool H_move_closer(int& num1x, int& num1y, vector<vector<int>> &board)
{
    if ((num1x == 1 || num1x == 3) && num1y == 1)
    {
        if (board[num1x][num1y + 1] == 0)
        {
            board[num1x][num1y + 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if ((num1x == 1 || num1x == 3) && num1y == 3)
    {
        if (board[num1x][num1y - 1] == 0)
        {
            board[num1x][num1y - 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    return true;
}
bool V_move_closer(int& num1x, int& num1y, vector<vector<int>>& board)
{
    if ((num1y == 1 || num1y == 3) && num1x == 1)
    {
        if (board[num1x + 1][num1y] == 0)
        {
            board[num1x + 1][num1y] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if ((num1y == 1 || num1y == 3) && num1x == 3)
    {
        if (board[num1x - 1][num1y] == 0)
        {
            board[num1x - 1][num1y] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    return true;
}
bool D_move(int& num1x, int& num1y, vector<vector<int>>& board)
{
    if ((num1x == 1) && (num1y == 1))
    {
        if (board[num1x - 1][num1y - 1] == 0)
        {
            board[num1x - 1][num1y - 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if ((num1x == 1) && (num1y == 3))
    {
        if (board[num1x - 1][num1y + 1] == 0)
        {
            board[num1x - 1][num1y + 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if ((num1x == 3) && (num1y == 1))
    {
        if (board[num1x + 1][num1y - 1] == 0)
        {
            board[num1x + 1][num1y - 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    if ((num1x == 3) && (num1y == 3))
    {
        if (board[num1x + 1][num1y + 1] == 0)
        {
            board[num1x + 1][num1y + 1] = board[num1x][num1y];
            board[num1x][num1y] = 0;
        }
        else
            return false;
    }
    return true;
}
vector<vector<int>> constructNewBoard(vector<int> &path, vector<vector<int>> board)
{
    vector<vector<int>> emptyBoard;
    int group;
    int operation;
    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] / 6 == 0)
        {
            group = 0;
            operation = path[i];
        }
        else if (path[i] / 2 == 3)
        {
            group = 1;
            operation = path[i] % 2;
        }
        else if ((path[i] >= 8) && (path[i] <= 13))
        {
            group = 2;
            operation = path[i] % 8;
        }
        else if ((path[i] / 2 == 7))
        {
            group = 3;
            operation = path[i] % 2;
        }
        else if ((path[i] / 2 == 8))
        {
            group = 5;
            operation = path[i] % 2;
        }
        else if ((path[i] >= 18) && (path[i] <= 23))
        {
            group = 6;
            operation = path[i] % 18;
        }
        else if ((path[i] / 2 == 12))
        {
            group = 7;
            operation = path[i] % 2;
        }
        else
        {
            group = 8;
            operation = path[i] - 26;
        }
        //do nothing code
        if (operation == 0)
            continue;
        //decode group in x and y coordinate in table 5x5
        int x = group / 3 + 1;
        int y = group % 3 + 1;
        if ((group == 3) || (group == 5))
        {
            if (!H_move_away(x, y, board))
                return emptyBoard;
        }
        else if ((group == 1) || (group == 7))
        {
            if (!V_move_away(x, y, board))
                return emptyBoard;
        }
        else
        {
            if (operation == 1)
            {
                if (!H_move_away(x, y, board))
                    return emptyBoard;
            }
            else if (operation == 2)
            {
                if (!V_move_away(x, y, board))
                    return emptyBoard;
            }
            else if (operation == 3)
            {
                if (!H_move_closer(x, y, board))
                    return emptyBoard;
            }
            else if (operation == 4)
            {
                if (!V_move_closer(x, y, board))
                    return emptyBoard;
            }
            else
            {
                if (!D_move(x, y, board))
                    return emptyBoard;
            }
        }
    }
    return board;
}
void recursiveSolution(vector<int> path, vector<vector<vector<int>>>& solVec, vector<vector<int>> &solPathVec, vector<int> lockedGroups, vector<int>& possibleMoves, vector<vector<int>>& board, bool mute)
{
    for (int i = 0; i < possibleMoves.size(); i++)
    {
        //we cant implement moves which we blocked
        if (possibleMoves[i] == 0)
            continue;
        int currentGroup(0);
        //det group of i
        if (i / 6 == 0)
            currentGroup = 1;
        else if (i / 2 == 3)
            currentGroup = 2;
        else if ((i >= 8) && (i <= 13))
            currentGroup = 3;
        else if (i / 2 == 7)
            currentGroup = 4;
        else if (i / 2 == 8)
            currentGroup = 6;
        else if ((i >= 18) && (i <= 23))
            currentGroup = 7;
        else if (i / 2 == 12)
            currentGroup = 8;
        else
            currentGroup = 9;
        //if group was used before
        if (find(lockedGroups.begin(), lockedGroups.end(), currentGroup) != lockedGroups.end())
            continue;
        path.push_back(i);
        vector<vector<int>> newBoard;
        //construct new board()
        newBoard = constructNewBoard(path, board);
        if (newBoard.size() == 0)
            continue;
        if (!isBoardHaveConflicts(newBoard, mute))
        {
            if (find(solVec.begin(), solVec.end(), newBoard) == solVec.end())
            {
                solVec.push_back(newBoard);
                solPathVec.push_back(path);
            }
            
        }
        lockedGroups.push_back(currentGroup);
        recursiveSolution(path, solVec, solPathVec, lockedGroups, possibleMoves, board, mute);
        lockedGroups.pop_back();
        path.pop_back();
    }
}
vector<int> findContactlessNums(vector<vector<int>>& board)
{
    vector<int> result;
    bool isContactless;
    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board.size(); j++)
        {
            isContactless = true;
            int num1 = board[i][j];
            if (num1 == 0)
                continue;
            int num2;
            for (int k = 0; k < 8; k++)
            {
                int dx = i + DirX[k];
                int dy = j + DirY[k];
                if (isIndexOutOfBounds(dx, 0, board.size() - 1))
                    continue;
                else if (isIndexOutOfBounds(dy, 0, board.size() - 1))
                    continue;
                num2 = board[dx][dy];
                if (num2 != 0)
                {
                    isContactless = false;
                }
            }
            if (isContactless == true)
                result.push_back(board[i][j]);
        }
    return result;
}
int findMatrixSize(vector<vector<int>> &board)
{
    int n = board.size();
    int m = board.size();
    //row counter
    bool isRowClear = true;
    for (int i = 0; i < board.size(); i++)
    {
        //check is there numbers on first and last rows
        if (board[0][i] != 0)
        {
            isRowClear = false;
            break;
        }
    }
    if (isRowClear)
        n--;
    isRowClear = true;
    for (int i = 0; i < board.size(); i++)
    {
        //check is there numbers on first and last rows
        if (board[board.size() - 1][i] != 0)
        {
            isRowClear = false;
            break;
        }
    }
    if (isRowClear)
        n--;
    //col counter
    bool isColClear = true;
    for (int i = 0; i < board.size(); i++)
    {
        
        if (board[i][0] != 0)
        {
            isColClear = false;
            break;
        }
        
        
    }
    if (isColClear)
        m--;
    isColClear = true;
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i][board.size() - 1] != 0)
        {
            isColClear = false;
            break;
        }
    }
    if (isColClear)
        m--;
    return n * m;
}
int main()
{
    bool mute = true;
    vector<int> possibleMoves;
    vector<int> enteredNumbers;
    int boardSize = 5;
    vector<vector<int>> board;
    for (int i = 0; i < 32; i++)
    {
        possibleMoves.push_back(1);
    }
    
    //1. entering section
    for (int i = 0; i < 9; i++)
    {
        int buffer;
        cin >> buffer;
        enteredNumbers.push_back(buffer);
    }
    //enteredNumbers = { 1,2,3,4,5,6,7,8,9 };
    //enteredNumbers = { 2,3,5,7,11,13,17,19,23 };
    //enteredNumbers = { 23,33,12,1,2,5,25,6,10 };
    //enteredNumbers = { 2,4,6,16,1,8,14,12,10 };

    //2. building board section
    for (int i = 0; i < boardSize; i++)
    {
        vector<int> boardString;
        for (int j = 0; j < boardSize; j++)
        {
            if ((i == 0) || (i == boardSize - 1))
                boardString.push_back(0);
            else if ((j == 0) || (j == boardSize - 1))
                boardString.push_back(0);
            else
                boardString.push_back(enteredNumbers[(i - 1) * 3 + j - 1]);
        }
        board.push_back(boardString);
    }

    //3. checking priorited conflicts
    //3.1 checking wall-center conflict
    wallCenterConfilct(possibleMoves, board);
    //3.2 checking corners-wall-wall conflict
    cornerWallWallConfilct(possibleMoves, board);
    printMatrInt(board, "Board");

    //4. finding solutions
    vector<vector<vector<int>>> solVec;
    vector<vector<int>> solPathVec;
    vector<int> lockedGroups = {};
    vector<int> path = {};
    int num1, num2;
    int buffer = 1;
    int operationNumber;
    bool isReset = false;
    recursiveSolution(path, solVec, solPathVec, lockedGroups, possibleMoves, board, mute);
    cout << "\nThere is " << solVec.size() << " unique solutions: \n";
    /*for (int i = 0; i < solVec.size(); i++)
    {
            printMatrInt(solVec[i], ("Solution " + to_string(i)));
    }*/

    //5. Trimming results to get best ones
    cout << "\n\n Trimming solutions:";
    cout << "\n Rule 4: shortest paths";
    int minPath = 8;
    vector<vector<int>> trimmedPathVec;
    vector<vector<vector<int>>> trimmedSolVec;
    for (int i = 0; i < solPathVec.size(); i++)
    {
        int pathCounter = 0;
        for (int j = 0; j < solPathVec[i].size(); j++)
        {
            if (solPathVec[i][j] / 6 == 0)
            {
                if (solPathVec[i][j] != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] / 2 == 3)
            {
                if (solPathVec[i][j] % 2 != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] >= 8 && solPathVec[i][j] <= 13)
            {
                if (solPathVec[i][j] % 8 != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] / 2 == 7)
            {
                if (solPathVec[i][j] % 2 != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] / 2 == 8)
            {
                if (solPathVec[i][j] % 2 != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] >= 18 && solPathVec[i][j] <= 23)
            {
                if (solPathVec[i][j] % 18 != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] / 2 == 12)
            {
                if (solPathVec[i][j] % 2 != 0)
                    pathCounter++;
            }
            else if (solPathVec[i][j] - 26 != 0)
                pathCounter++;

        }
        if (pathCounter == minPath)
        {
            trimmedPathVec.push_back(solPathVec[i]);
            trimmedSolVec.push_back(solVec[i]);
        }
        else if (pathCounter < minPath)
        {
            trimmedPathVec.clear();
            trimmedSolVec.clear();
            minPath = pathCounter;
            trimmedSolVec.push_back(solVec[i]);
            trimmedPathVec.push_back(solPathVec[i]);
        }
    }
    /*for (int i = 0; i < solPathVec.size(); i++)
    {
        printVectorInt(solPathVec[i], ("Board " + to_string(i)));
    }*/
    cout << "\n Min path is " << minPath;
    cout << "\n Paths with min length: " << trimmedPathVec.size();

    cout << "\n\n Rule 4: contactless numbers";
    int minContactlessNumsCount = 10;
    vector<vector<vector<int>>> trimmedSolVec2;
    for (int i = 0; i < trimmedSolVec.size(); i++)
    {
        vector<int> allContactlessNumbers = findContactlessNums(trimmedSolVec[i]);
        if (allContactlessNumbers.size() == minContactlessNumsCount)
        {
            trimmedSolVec2.push_back(trimmedSolVec[i]);
        }
        else if (allContactlessNumbers.size() < minContactlessNumsCount)
        {
            trimmedSolVec2.clear();
            minContactlessNumsCount = allContactlessNumbers.size();
            trimmedSolVec2.push_back(trimmedSolVec[i]);
        }
    }
    cout << "\n Min contactless nums: " << minContactlessNumsCount;
    cout << "\n Found " << trimmedSolVec2.size() << " with it. Here they are:";
    for (int i = 0; i < trimmedSolVec2.size(); i++)
    {
        printMatrInt(trimmedSolVec2[i], ("Board " + to_string(i)));
    }

    cout << "\n\n Rule 5: comparing sizes of matrixes";
    int minSizeOfMatr = boardSize * boardSize;
    vector<vector<vector<int>>> trimmedSolVec3;
    for (int i = 0; i < trimmedSolVec2.size(); i++)
    {
        if (minSizeOfMatr == findMatrixSize(trimmedSolVec2[i]))
            trimmedSolVec3.push_back(trimmedSolVec2[i]);
        else if (minSizeOfMatr > findMatrixSize(trimmedSolVec2[i]))
        {
            trimmedSolVec3.clear();
            minSizeOfMatr = findMatrixSize(trimmedSolVec2[i]);
            trimmedSolVec3.push_back(trimmedSolVec2[i]);
        }
    }
    
    cout << "\n Min size of matr: " << minSizeOfMatr;
    cout << "\n Found " << trimmedSolVec3.size() << " with it.";

    cout << "\n\n Rule 6: trying to lock largest number";
    vector<vector<vector<int>>> trimmedSolVec4;
    int largestNumber = 0;
    int x, y;
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (largestNumber < board[i][j])
            {
                largestNumber = board[i][j];
                x = i;
                y = j;
            }
        }
    }
    for (int i = 0; i < trimmedSolVec3.size(); i++)
    {
        if (trimmedSolVec3[i][x][y] == largestNumber)
            trimmedSolVec4.push_back(trimmedSolVec3[i]);
    }
    if (trimmedSolVec4.size() == 0)
    {
        cout << "\nThere are no answers with locked number. Here previous ones:";
        for (int i = 0; i < trimmedSolVec3.size(); i++)
        {
            printMatrInt(trimmedSolVec3[i], ("Board " + to_string(i)));
        }
    }
    else
    {
        cout << "\nThere are " << trimmedSolVec4.size() << " answers with locked number. Here they are:";
        for (int i = 0; i < trimmedSolVec4.size(); i++)
        {
            printMatrInt(trimmedSolVec4[i], ("Board " + to_string(i)));
        }
    }
    if (minContactlessNumsCount == 0)
        cout << "None";
    else
    {
        vector<int> contactlessNumbers;
        if (trimmedSolVec4.size() > 0)
            contactlessNumbers = findContactlessNums(trimmedSolVec4[0]);
        else
            contactlessNumbers = findContactlessNums(trimmedSolVec3[0]);
        sort(contactlessNumbers.begin(), contactlessNumbers.end());
        for (int i = 0; i < contactlessNumbers.size(); i++)
        {
            cout << contactlessNumbers[i] << " ";
        }
    }
    cout << "\n\n";
    system("pause");
    return 0;
}
