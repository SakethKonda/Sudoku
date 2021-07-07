#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

#define usi unordered_set<int>
#define vui vector<usi>
#define vvc vector<vector<char>>
#define vc vector<char>

void printv(vvc v)
{
    int i,j;
    int m=v.size();
    int n=v[0].size();
    cout<<"Solved!\n";
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
            cout<<v[i][j]<<" ";
        cout<<"\n";
    }
}

bool isNotSafe(int i,int t,int xpos,int ypos,vui &rows,vui &cols,vui &tiles)
{
    if(rows[xpos].find(i)!=rows[xpos].end() || cols[ypos].find(i)!=cols[ypos].end())
        return true;
    return tiles[t].find(i)!=tiles[t].end();
}

bool fillSudoku(vvc &res,vui &rows,vui &cols,vui &tiles, int xpos=0,int ypos=0,int nrow=9,int ncol=9)
{
    int i,j;
    if(xpos>=nrow)
        return true;
    int nx=xpos,ny=ypos+1;
    if(ypos == ncol-1)
    {       
        ny=0;
        nx=xpos+1;
    }
    if(res[xpos][ypos]!='.')
    {
        if(fillSudoku(res,rows,cols,tiles,nx,ny))
            return true;
        return false;
    }
    int t= (xpos/3)*3+(ypos/3);
    for(i=1;i<10;i++)
    {
        if(isNotSafe(i,t,xpos,ypos,rows,cols,tiles))
            continue;
        rows[xpos].insert(i);
        cols[ypos].insert(i);
        tiles[t].insert(i);
        res[xpos][ypos]=(i+'0');
        if(fillSudoku(res,rows,cols,tiles,nx,ny))
            return true;
        res[xpos][ypos]='.';
        rows[xpos].erase(i);
        cols[ypos].erase(i);
        tiles[t].erase(i);
    }
    return false;
}

int main()
{
    int i,j;
    usi num;
    vc r(9,'.');
    vvc inp(9,r);
    vui rows(9,num);
    vui cols(9,num);
    vui tiles(9,num);
    int tile;
    string s;
    cout<<"Enter your input : \n";
    cout<<"Note : input should contain 9lines each representing one row of sudoku ,";
    cout<<"each line should contain 9 characters , empty character should be represented by '.'\n";
    for(i=0;i<9;i++)
    {
        cin>>s;
        for(j=0;j<9;j++)
        {
            inp[i][j]=s[j];
            if(s[j]=='.')
                continue;
            tile=(i/3)*3 + (j/3);
            rows[i].insert(s[j]-'0');
            cols[j].insert(s[j]-'0');
            tiles[tile].insert(s[j]-'0');
        }
    }
    if(!fillSudoku(inp,rows,cols,tiles))
        cout<<"Your input has no solution\n";
    printv(inp);
    return 0;
}