#include <iostream>
#include <cstring>
#include <cmath>
#include <stack>
using namespace std;

int color[1001];
bool edge[1001][1001];
bool output;

void dfs(int keypos , int color_ , int n)
{
	color[keypos] = color_;
	for(int i = 0 ; i < n ; i ++)
	{
		if(edge[keypos][i]) // 假如两个节点有连线 
		{
			if(color[i] == color_) // 若两个节点染色相同，不存在这样的二部图 
			{
				output = false;
				break;
			}
			else if( color[i] == 0 ) //若该结点没染色，则进行染色 
			{
				dfs(i , 3-color_ , n);
			}
		}
		if(edge[i][keypos])
		{
			if(color[i] == color_)
			{
				output = false;
				break;
			}
			else if( color[i] == 0 )
			{
				dfs(i , 3-color_ , n);
			}
		}
	}
} 

int main()
{
	int n;
	int num[1001] ;
	int postmin[1001]; //在每个位置后面的最小数
	while(cin >> n)
	{
		// 初始化
		for(int i = 0 ; i < 1001 ;i++) 
		{
			color[i] = 0;
			for(int j = 0 ; j < 1001 ; j++)
			{
				edge[i][j] = false;
			}
		}
		output = true;
		
		for(int i = 0 ; i < n; i++)
		{
			cin >> num[i];
		}
		//把每个位置后面最小的数赋值 ,方便进行遍历比较 ，减少算术复杂度 
		for( int i = n-1 ; i >= 0 ; i--)
		{
			if(i == n-1) postmin[i] = num[i];
			else postmin[i] = min(num[i] , postmin[i+1]);	
		}
		//划线 
		for(int i = 0 ; i < n-1 ; i++)
		{
			for(int j = i+1 ; j < n ; j++)
			{
				if(num[i] < num[j] && postmin[j] < num[i]) // 不能放入同一个栈的条件 
				{
					edge[i][j] = edge[j][i] = true; // 连线 
				}
			}
		}
		
		//染色
		for(int i = 0 ; i <n ; i++)
		{
			if(color[i] == 0)
			{
				dfs(i , 1 , n );
			}
		} 
		
		stack<int> s1 ,s2;
		string minorder;
		if(output)
		{
			int outputnum = 1;
			int pos = 0;
			while(outputnum <= n)
			{
				if(color[pos] == 1)
				{
					minorder = minorder + "a";
					s1.push(num[pos]);
					pos++;
				}
				while(s1.empty() == 0 && s1.top() == outputnum)
				{
					s1.pop();
					minorder = minorder + "b";
					outputnum++;
				}
				if (color[pos] == 1 && (s1.empty() || s1.top() > num[pos])) {  
          			continue;  
        		} 
        		while(s2.empty() == 0 && s2.top() == outputnum)
				{
					s2.pop();
					minorder = minorder + "d";
					outputnum++;
				}
				if(color[pos] == 2)
				{
					minorder = minorder + "c";
					s2.push(num[pos]);
					pos++;
				}
			}
			for(int i = 0 ; i < minorder.length() ; i++)
			{
				if(i != 0)
				{
					cout << " ";
				}
				cout << minorder[i] ;
			}
			cout << endl;
		}
		else cout << "0" << endl;
		while(s1.empty() == 0)
		{
			s1.pop();
		}
		while(s2.empty() == 0)
		{
			s2.pop();
		}
		minorder.clear();
	} 
	return 0;
} 
