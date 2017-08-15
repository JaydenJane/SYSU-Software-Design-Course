#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

//一元多项式链表的定义 
struct poly
{
	double coef; // 系数 
	int expon;  //  指数 
	struct poly *next; 
};

//多项式项数的测量 
int length(poly *p)
{
	int length = 0;
	poly* re;
	re = p -> next;
	while(re != NULL)
	{
		re = re -> next;
		length ++ ;
	}
	return length;
} 

//删除值为0的节点
poly* delete0(poly* p)
{
	poly* pre;
	pre = p ;
	poly* box;
	while(pre -> next)
	{
		if(pre -> next -> coef == 0)
		{
			box = pre -> next;
			pre -> next = box -> next;
			delete(box);
		}
		else pre = pre -> next;
	}
	if(length(p) == 0) 
	{
		p = new poly;
		p -> coef = p -> expon = 0;
		p -> next = NULL;
		box = new poly;
		box -> coef = box -> expon = 0;
		box -> next = NULL;
		p -> next = box;
	} 
	return p; 
}

//一元多项式的创建 
poly* createpoly(poly *p)
{
	// pre用以保存前驱 , post用以保存后继 
	poly *re , *pre , *post;	
	// 多项式的项数 
	int num;                   
	bool judge , in;
	// 创建一个头结点 
	p = new poly;	           
	p -> next = NULL;	
	p -> coef = 0;	
	p -> expon = 0;
	in = false;
	while(in == false)
	{
		cout << "--请--输--入--多--项--式--的--项--数--：" << endl;	
		cin >> num;
		if(num <= 0)
		{
			cout << "--输--入--有--误--请--重--新--输--入--！" << endl << endl; 
			in = false;
		} 
		else in = true;
	}
	int i = 1;
	while(num--)
	{
		// 创建一个结点 
		re = new poly;	
		//判断输入的项数中是否有相同指数的指标 	
		judge = false;      
		cout << endl << "-----请输入第" << i << "项系数-----：" << endl;		
		cin >> re -> coef;		
		cout << endl << "-----请输入第" << i << "项指数-----：" << endl;		
		cin >> re -> expon;
		//特殊操作，把系数为0的项统一为指数也为0，方便进行合并操作。 
		if( re -> coef == 0) re -> expon = 0;
		pre = p ; 
		post = p -> next;
		// 为了按降序排列 ,一直找到第一个比输入的项的指数小的项 
		while(post && post -> expon >= re -> expon) 
		{
			// 在寻找过程中找到指数相同的项进行合并同类项操作 
			if(post -> expon == re -> expon)
			{
				post -> coef = post -> coef + re -> coef;
				judge = true;
				break;
			}
			pre = post;
			post = post -> next;
		}
		//进行结点插入的工作 
		if( judge == false)
		{
			pre -> next = re;
			re -> next = post; 
		}
		i++;
	}
	p = delete0(p);
	return p;
}   

//多项式的打印输出 
void print(poly *p)
{
	poly *re = p -> next;
	int len = length(p) , count = 0;
	bool flag;
	cout << " 项数 :" << len << endl; 
	while(re != NULL )
	{
		// 当指数为 0 的特殊输出 
		if(re -> expon == 0) 		 
		{
			
			cout << re -> coef ; 
		} 
		else                      
		{
			//当 系数为1的特殊输出 
			if(re -> coef == 1) 
			{
				if(re -> expon == 1) cout << "x" ;
				else cout << "x^" << re -> expon ;
			}
			//当 系数为-1的特殊输出 
			else if(re -> coef == -1) 
			{
				if(re -> expon == 1) cout << "-x" ;
				else cout << "-x^" << re -> expon ;
			}
			else 
			{
				//当 指数为1的特殊输出 
				if(re -> expon == 1) cout << re -> coef << "x" ;
				else cout << re -> coef << "x^" << re -> expon ;
			}
		}
		count++ ;
		if( count < len )
		{
			cout << " + " ;
		} 
		else cout << endl;
		re = re -> next;
	} 
}

//多项式相加 
poly* add(poly* p1 , poly* p2)
{
	//确定p1不进行操作，只进行节点的遍历，对p2的节点进行遍历以及操作，最终返回p2 
	poly* re1 , *re2 , *pre ,*add;
	bool flag ;
	pre = p2;
	re1 = p1 -> next;
	while(re1)
	{
		//令一个新的指针add的指针域指向NULL，将此时p1中的一个节点的数据复制给add。 
		add = new poly;
		add -> coef = re1 -> coef;
		add -> expon = re1 -> expon;
		add -> next = NULL;
		re2 = pre -> next;
		//flag 是用来表明有无同类项的指标 
		flag = false;
		//遍历p2找到第一个指数小于等于add的指数的项 
		while( re2 && re2 -> expon >= add -> expon)
		{
			//找到同类项，直接对此时遍历到的p2的节点的值进行更改，flag=true，释放add的空间 
			if( re2 -> expon == add -> expon )
			{
				re2 -> coef = add -> coef + re2 -> coef;
				flag = true;
				delete(add);
			}
			pre = re2;
			re2 = re2 -> next;
		}
		//遍历完并且无同类项则进行节点的插入 
		if(flag == false)
		{
			pre -> next = add;
			add -> next = re2; 
		}
		re1 = re1 -> next;
	}
	p2 = delete0(p2);
	return p2;
}

//多项式减法 
poly* sub(poly* p1 , poly* p2)
{
	//减法固定减数，对被减数的链表进行操作 
	poly* re1 , *re2 , *pre ,*sub;
	bool flag ;
	pre = p1;
	re1 = p2 -> next;
	while(re1)
	{
		//令一个新的指针sub的指针域指向NULL，将此时p1中的一个节点的数据复制给sub。 
		sub = new poly;
		sub -> coef = re1 -> coef;
		sub -> expon = re1 -> expon;
		sub -> next = NULL;
		re2 = pre -> next;
		//flag 是用来表明有无同类项的指标 	
		flag = false;
		while( re2 && re2 -> expon >= sub -> expon)
		{
			//找到同类项，直接对此时遍历到的p2的节点的值进行更改，flag=true，释放sub的空间 
			if( re2 -> expon == sub -> expon )
			{
				re2 -> coef = re2 -> coef - sub -> coef;
				flag = true;
			}
			pre = re2;
			re2 = re2 -> next;
		}
		//遍历完无同类项，进行节点的插入，此时插入的节点的系数需乘-1 
		if(flag == false)
		{
			sub -> coef = sub -> coef * (-1);
			pre -> next = sub;
			sub -> next = re2; 
		}
		re1 = re1 -> next;
	}
	p1 = delete0(p1);
	return p1;
}

//多项式相乘 
poly* mul(poly* p1 , poly* p2)
{
	poly* re1 , *re2 ,*p3 ,*box;
	int exp ;
	double coe;
	if(length(p1) > length(p2))
	{
		p3 = p1;
		p1 = p2;
		p2 = p3;
	}
	re1 = p1 -> next;
	while(re1)
	{
		//直接使用两个变量记录其中一条链上一个节点的数据，然后遍历另外一条节点进行操作。 
		exp = re1 -> expon;
		coe = re1 -> coef;
		re2 = p2 -> next;
		while(re2)
		{
			re2 -> coef = re2 -> coef * coe;
			re2 -> expon = re2 -> expon + exp;
			re2 = re2 -> next;
		}
		re1 = re1 -> next;
	}
	p2 = delete0(p2);
	return p2;
}

// 多项式求导  
poly* deri(poly* p1)
{
	//求导时需注意特殊情况，指数为0时候，求导后整项为0； 
	poly* re1 ;
	re1 = p1 -> next;
	while(re1)
	{
		if(re1 -> expon == 0)
		{
			re1 -> coef = 0;
		}
		else
		{
			re1 -> coef = re1 -> coef * re1 -> expon;
			re1 -> expon = re1 -> expon - 1 ;
		}
		re1 = re1 -> next ;
	}
	p1 = delete0(p1);
	return p1;
}

//代入进行多项式结算 
double cal(poly* p , double x)
{
	poly* re ;
	double sum = 0;
	re = p -> next;
	double coe , expon;
	while(re)
	{
		coe = re -> coef;
		expon = re -> expon;
		sum = sum + coe*pow(x,expon);
		re = re -> next;
	}
	return sum;
}

//程序使用规则的打印
void printrule()
{
	cout << "- 欢 迎 使 用 多 项 式 计 算 器 ！ -" << endl << endl; 
	cout << "----------------------------------------------" << endl;
	cout << " 多 项 式 计 算 器 的 输 入 流 程 为 先 输 入 " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 一 项 的 系 数 ， 再 输 入 一 项 的 指 数 。 " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 输 入 完 一 个 多 项 式 之 后 可 以 选 择 对 " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 此 多 项 式 的 具 体 操 作 ， 具 体 说 明 为 " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 1、输 入 + 会 进 行 多 项 式 的 加 法 运 算  " << endl;  
	cout << "----------------------------------------------" << endl;
	cout << " 2、输 入 - 会 进 行 多 项 式 的 减 法 运 算  " << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 3、输 入 * 会 进 行 多 项 式 的 乘 法 运 算  " << endl; 
	cout << "----------------------------------------------" << endl;
	cout << " 4、输 入 d 会 进 行 多 项 式 的 导 数 计 算  "<< endl;
	cout << "----------------------------------------------" << endl;
	cout << " 5、输 入 = 会 进 行 对 多 项 式 的 代 数 运 算"  << endl;
	cout << "----------------------------------------------" << endl;
	cout << " 6、输 入 c 会 进 行 数 据 的 重 新 导 入，初 始 化 "  << endl;
	cout << "----------------------------------------------" << endl << endl; 
}
 
int main()
{
	printrule();
	while(1)
	{ 
		poly *p1 , *p2 , *result;
		char ch;
		cout << endl << "--多--项--式--的--创--建--:" << endl;
		p1 = createpoly(p1);
		result -> next = NULL;
		while(1)
		{
			cout << "--请--输--入--操--作--符--号--"<< endl;
			cin >> ch;
			if(result -> next != NULL) p1 = result;
			if( ch == '+') 
			{
				cout << endl << "--多--项--式--的--创--建--:" << endl;
				p2 = createpoly(p2);
				cout << "--您--创--建--的--多--项--式--分--别--为--:" << endl << endl;
				cout << "--多--项--式--1-- ：";
				print(p1);
				cout << endl;
				cout << "--多--项--式--2-- ：";
				print(p2);
				cout << endl;
				result = add(p1 , p2);
				cout << "-----两个多项式相加结果为-----："; 
				print(result);
				cout << endl;
			}
			else if(ch == '-')
			{
				cout << "--多--项--式--的--创--建--:" << endl;
				p2 = createpoly(p2);
				cout << "--您--创--建--的--多--项--式--分--别--为--:" << endl << endl;
				cout << "--多--项--式--1-- ：";
				print(p1);
				cout << endl;
				cout << "--多--项--式--2-- ：";
				print(p2);
				cout << endl;
				result = sub(p1 , p2);
				cout << "-----多项式1减多项式2结果为-----："; 
				print(result);
				cout << endl;
			}
			else if(ch == '*')
			{
				cout << "--多--项--式--的--创--建--:" << endl;
				p2 = createpoly(p2);
				cout << "--您--创--建--的--多--项--式--分--别--为--:" << endl << endl;
				cout << "--多--项--式--1-- ：";
				print(p1);
				cout << endl;
				cout << "--多--项--式--2-- ：";
				print(p2);
				cout << endl;
				result = mul(p1,p2);
				cout << "-----两个多项式相乘结果为-----：";
				print(result);
				cout << endl;
			}
			else if(ch == 'd')
			{
				print(p1);
				result = deri(p1);
				cout << "--多--项--式--的--导--数-- : ";
				print(result);
				cout << endl;
			}
			else if(ch == '=')
			{
				cout << endl << "--请--输--入--x--的--值--" << endl ;
				double x;
				cin >> x;
				cout << "-----代入x = " << x <<" 求出的结果为-----:";
				cout << cal(p1,x) << endl << endl;;
			}
			else if(ch == 'c')
			{
				delete(p1);
				break;
			} 
		}
	}
	return 0;
}
 
