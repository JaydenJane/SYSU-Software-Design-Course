#include <iostream>
#include <cstring>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

char invalid = '#';
char error = '@';

struct bnode
{
	string data;
	bnode* lchild ;
	bnode* rchild ;
};  

//去除空格 
string removeblank(string s)
{
	string str;
	for(int i = 0 ; i < s.length() ; i++)
	{
		if(s[i] == ' ' );
		else str = str + s[i]; 
	}
	return str;
}

//字符串转数字 
long double transform(string s)
{
	int pos = s.find(".");
	long double sum = 0;
	if(s[0] != '-')
	{
		//当该数为小数时； 
		if(pos != -1) 
		{
			for(int i = 0; i < pos ; i++)
			{
				sum = sum + 1.0*pow(10,pos-i-1)*(s[i] - '0');
			}
			for(int j = pos + 1; j < s.length() ; j++)
			{
				sum = sum + 1.0*pow(0.1,j-pos)*(s[j] - '0');
			}
			return sum;
		}
		//不为小数时； 
		else 
		{
			for(int i = 0 ; i < s.length() ; i++)
			{
				sum = sum + 1.0*pow(10,s.length()-1-i)*(s[i] - '0');
			}
			return sum;
		}
	}
	else
	{
		//当该数为小数时； 
		if(pos != -1) 
		{
			for(int i = 1; i < pos ; i++)
			{
				sum = sum + 1.0*pow(10,pos-i-1)*(s[i] - '0');
			}
			for(int j = pos + 1; j < s.length() ; j++)
			{
				sum = sum + 1.0*pow(0.1,j-pos)*(s[j] - '0');
			}
			return (-1.0)*sum;
		}
		//不为小数时； 
		else 
		{
			for(int i = 1 ; i < s.length() ; i++)
			{
				sum = sum + 1.0*pow(10,s.length()-1-i)*(s[i] - '0');
			}
			return (-1.0)*sum;
		}
	}
} 

//计算函数 
long double cal(long double num1_ , char op , long double num2_)
{
	if(op == '+') return num1_ + num2_;
	else if(op == '-') return num1_ - num2_;
	else if(op == '*') return num1_ * num2_;
	else if(op == '/') return num1_ / num2_;
	else if(op == '^') return pow(num1_,num2_);
	
}

//树的建立 
bnode* createtree(string s , int &pos)
{
	bnode* root = NULL;
	if(pos < s.length() && s[pos] != invalid)//当该位置不为空时 
	{
		root = new bnode;
		root->data = s[pos];
		root->lchild = createtree(s , ++pos);
		root->rchild = createtree(s , ++pos);
	}
	return root;
}

//前缀的读取和改造函数 ，因为叶子节点必定为0-9或者a-z,所以在每个叶子节点后面位置加两个##，代表其为叶子节点  
string ReadExpr(string s)
{
	string str;
	for(int i = 0 ; i < s.length() ; i++)
	{
		if( (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z'))
		{
			str = str + s[i];
			str = str + invalid;
			str = str + invalid;
		}
		else 
		{
			if(s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
			{
				str = str + s[i];
			}
			else//非法字符的输入判断 
			{
				str = error + str;
				break;
			}
		}
	}
	return str;
}

//遍历后缀式函数 
void postorder(bnode* root , string &posexpr)
{
	bnode* p = root;
	if(p == NULL) return;
	else
	{
		postorder(p->lchild,posexpr);
		postorder(p->rchild,posexpr);
		posexpr = posexpr + p->data + " ";
	}
}

//输出中缀式函数 
void WriteExpr(string por, bool &flag)
{
	stack<string> op;
	string tmp; 
	for(int i = 0 ; i < por.length(); i++)
	{
		while(por[i] != ' ') //空格是为了区分例如 12 和 1 2 的区别 
		{
			tmp = tmp + por[i];
			i++;
		}
		if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^")
		{
			string opr1 , opr2 , exp;
			opr1 = op.top();
			op.pop();
			if(op.empty() == 1)//当操作符过多 
			{
				op.push("false");
				break;
			}
			else
			{
				if(i == por.length()-1)
				{
					opr2 = op.top();
					op.pop();
					if(opr1 == "0" && tmp == "+")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "+")
					{
						exp = opr1;
					}
					else if(opr1 == "0" && tmp == "-")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "-")
					{
						exp = "-" + opr1;
					}
					else exp =  opr2 + tmp + opr1 ;
					op.push(exp);
				}
				else
				{
					opr2 = op.top();
					op.pop();
					if(opr1 == "0" && tmp == "+")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "+")
					{
						exp = opr1;
					}
					else if(opr1 == "0" && tmp == "-")
					{
						exp = opr2;
					}
					else if(opr2 == "0" && tmp == "-")
					{
						exp ="(-" + opr1 + ")";
					}
					else exp = "(" + opr2 + tmp + opr1 + ")";
					op.push(exp);
				}
			}
		}
		else 
		{
			op.push(tmp);
		}
		tmp.clear();
	}
	cout << op.top() << endl;
	if(op.top() == "false") flag = false;
}

//对某变量进行赋值函数 
void assign(bnode* root , string V , string value)
{
	bnode* tmp = root;
	queue<bnode*> q;
	q.push(tmp);
	while( !q.empty() ) // 层次遍历进行查找 
	{
		bnode* top = q.front();
		if(top->data == V)
		{
			top->data = value;
		}
		q.pop();
		if(top->lchild != NULL) q.push(top->lchild);
		if(top->rchild != NULL) q.push(top->rchild);
	} 
}

//求值函数 
void Value(string posexpr)
{
	stack<string> op;
	string tmp; 
	long double opra1 , opra2,re;
	stringstream ss;
	for(int i = 0 ; i < posexpr.length(); i++)
	{
		while(posexpr[i] != ' ') 
		{
			tmp = tmp + posexpr[i];
			i++;
		}
		if(tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "^")
		{
			string opr1 , opr2 , exp;
			opr1 = op.top();
			op.pop();
			opra1 = transform(opr1);
			opr2 = op.top();
			op.pop();
			opra2 = transform(opr2);
			re = cal(opra2,tmp[0],opra1);
			ss << re;
			ss >> exp;
			op.push(exp);
			ss.clear();
		}
		else
		{
			if(tmp[0] >= 'a' && tmp[0] <= 'z')
			{
				op.push("0");
			}
			else op.push(tmp);
		}
		tmp.clear();
	}
	cout << op.top() << endl;	
}

//两个表达式的复合 
bnode* CompoundExpr(char op , bnode* root1 , bnode* root2)
{
	bnode *newroot = new bnode;
	newroot->data = op;
	newroot->lchild = root1;
	newroot->rchild = root2;
	return newroot;
} 

//合并常数项函数 
void MergeConst(bnode *root)
{
	bnode* tmp = root;
	long double a,b ,re;
	bool flag1 , flag2; // 判断是否操作符两端都为数字 
	stringstream ss;
	string s;
	if(tmp == NULL) return ;
	else
	{	
		flag1 = true;	
		flag2 = true;	
		if((tmp->lchild->data == "+" || tmp->lchild->data == "-" || tmp->lchild->data == "*"|| tmp->lchild->data == "/"|| tmp->lchild->data == "^") && tmp->lchild->data.length()==1)
		{
			MergeConst(tmp->lchild); // 是操作符继续遍历 
            flag1 = false;
		}
		else flag1 = false;
		if( tmp->lchild->data[0] >= '0' && tmp->lchild->data[0] <= '9' || tmp->lchild->data.length() > 1) //判断操作符遍历后更新之后是否为一个数字 
		{
			a = transform(tmp->lchild->data);
			flag1 = true;
		}
		if((tmp->rchild->data == "+" || tmp->rchild->data == "-" || tmp->rchild->data == "*"|| tmp->rchild->data == "/"|| tmp->rchild->data == "^") & tmp->rchild->data.length()==1)
		{
			MergeConst(tmp->rchild);
			flag2 = false;
		}
		else flag2 = false;
		if(tmp->rchild->data[0] >= '0' && tmp->rchild->data[0] <= '9' || tmp->rchild->data.length() > 1)
		{
			b = transform(tmp->rchild->data);
			flag2 = true;
		}
		if(flag1 == true && flag2 == true) //左右都是数字，进行计算并更新该节点。 
		{
			re = cal(a,tmp->data[0],b);
			ss << re;
			ss >> s;
			tmp->data = s;
			tmp->lchild = NULL;
			tmp->rchild = NULL;
		}
	}
}

//二叉树复制函数 
bnode* Copy(bnode* root)
{	
	bnode* first ;
	first = new bnode;
	queue<bnode*> qformer;
	queue<bnode*> qcopy;
	if(root != NULL)
	{
		first->data = root->data;
		first->lchild = NULL;
		first->rchild = NULL;
		qformer.push(root);
		qcopy.push(first);
	}
	while(!qformer.empty())
	{
		bnode* pf = qformer.front();
		bnode *pc = qcopy.front();
		if(pf->lchild != NULL)
		{
			bnode* temp ;
			temp = new bnode;
			temp -> data = pf->lchild->data;
			temp->lchild = NULL;
			temp->rchild = NULL;
			qformer.push(pf->lchild);
			qcopy.push(temp);
			pc->lchild = temp;
		}
		if(pf->rchild != NULL)
		{
			bnode* temp ;
			temp = new bnode;
			temp -> data = pf->rchild->data;
			temp->lchild = NULL;
			temp->rchild = NULL;
			qformer.push(pf->rchild);
			qcopy.push(temp);
			pc->rchild = temp;	
		}
		qformer.pop();
		qcopy.pop();
	}
	return first;
}

//求导函数 
void Diff(bnode* root , string var)
{
	bnode* tmp = root;
	if( tmp->lchild == NULL && tmp->rchild == NULL) return; 
	else
	{
		if(tmp->data == "+" || tmp->data == "-")  // + , - 求导 
		{
			if(tmp->lchild->data == var) tmp->lchild->data = "1";
			else
			{
				if(tmp->lchild->data == "+" || tmp->lchild->data == "-" || tmp->lchild->data == "*"|| tmp->lchild->data == "/"|| tmp->lchild->data == "^")
				{
					Diff(tmp->lchild,var);	
				}
				else
				{
					tmp->lchild->data = "0";
				}
			}
			if(tmp->rchild->data == var) tmp->rchild->data = "1";
			else
			{
				if(tmp->rchild->data == "+" || tmp->rchild->data == "-" || tmp->rchild->data == "*"|| tmp->rchild->data == "/"|| tmp->rchild->data == "^")
				{
					Diff(tmp->rchild,var);	
				}
				else
				{
					tmp->rchild->data = "0";
				}
			}
		}
		
		else if(tmp->data == "*")  // 乘法求导 ， 原理 （ab）' = a'b + ab' ,所以进行新子树的建立 
		{
			bnode *newr , *newl , *pl , *pr;
			newl = Copy(tmp);
			newr = Copy(tmp);
			tmp->data = "+";
			tmp->lchild = newl;
			tmp->rchild = newr;
			pl = tmp->lchild; 
			pr = tmp->rchild;
			if(pl->lchild->data == var)
			{
				pl->lchild->data = "1"; 
			}
			else
			{
				if(pl->lchild->data == "+" || pl->lchild->data == "-" || pl->lchild->data == "*"|| pl->lchild->data == "/"|| pl->lchild->data == "^")
				{
					Diff(pl->lchild,var);
				}
				else
				{
					pl->lchild->data = "0";
					pl->data = "0";   // 只要左子树为0，无论右子树为什么，值恒为0 
					pl->lchild = NULL;
					pl->rchild = NULL;
				}
			}
			if(pr->rchild->data == var)
			{
				pr->rchild->data = "1"; 
			}
			else
			{
				if(pr->rchild->data == "+" || pr->rchild->data == "-" || pr->rchild->data == "*"|| pr->rchild->data == "/"|| pr->rchild->data == "^")
				{
					Diff(pr->rchild,var);
				}
				else
				{
					pr->rchild->data = "0";
					pr->data = "0";
					pr->lchild = NULL;
					pr->rchild = NULL;
				}
			}
		}
		
		else if(tmp->data == "/") //除法求导原理, (a/b)'  =  (a'b - ab') / b*b ，也是进行新子树的建立 
		{
			bnode *newr , *newl , *newl_, *newr_ , *tmpnewl ,*tmpnewr, *pl ,*pr;
			newl = Copy(tmp);
			newr = Copy(tmp);
			newl->data = "*";
			newr->data = "*";
			newl_ = Copy(tmp->rchild);
			newr_ = Copy(tmp->rchild);
			
			tmpnewl = new bnode;
			tmpnewl->data = "-";
			tmpnewl->lchild = newl;
			tmpnewl->rchild = newr;
			tmp->lchild = tmpnewl;
			tmpnewr = new bnode;
			tmpnewr->data = "*";
			tmpnewr->lchild = newl_;
			tmpnewr->rchild = newr_;
			tmp->rchild = tmpnewr;
			
			pl = tmp->lchild->lchild;
			pr = tmp->lchild->rchild;
			if(pl->lchild->data == var)
			{
				pl->lchild->data = "1";
			}
			else
			{
				if(pl->lchild->data == "+" || pl->lchild->data == "-" || pl->lchild->data == "*"|| pl->lchild->data == "/"|| pl->lchild->data == "^")
				{
					Diff(pl->lchild,var);
				}
				else
				{
					pl->lchild->data = "0";
					pl->data = "0";
					pl->lchild = NULL;
					pl->rchild = NULL; 
				}
			}
			if(pr->rchild->data == var)
			{
				pr->rchild->data = "1"; 
			}
			else				
			{
				if(pr->rchild->data == "+" || pr->rchild->data == "-" || pr->rchild->data == "*"|| pr->rchild->data == "/"|| pr->rchild->data == "^")
				{
					Diff(pr->rchild,var);
				}
				else
				{
					pr->rchild->data = "0";
					pr->data = "0";
					pr->lchild = NULL;
					pr->rchild = NULL; 
				}
			}
		}
		
		else if(tmp->data == "^") // 乘方求导原理，a^n = n*a'*a^(n-1) ，也是进行新子树的建立 
		{
			bnode *newr , *newl , *pl , *pr;
			stringstream ss;
			string da;
			newl = Copy(tmp);
			newr = Copy(tmp);
			newl->data = "*";
			tmp->data = "*";
			tmp->lchild = newl;
			tmp->rchild = newr;
			long double d = transform(newr->rchild->data);
			d--;
			ss << d ;
			ss >> da ;
			newr->rchild->data = da;
			Diff(tmp->lchild,var);
		}		
	}
}


int main()
{
	string s , posexpr;
	bool flag , con;
	cout << "                       --------------------------"<< endl;
	cout << "                       -欢迎使用前缀表达式运算器-"<< endl;
	cout << "                       --------------------------"<< endl;
	while(1)
	{
		posexpr.clear();
		flag = true;
		con = true;
		bnode* root;
		cout << "  请输入前缀表达式 ： "<< endl;
		cin >> s;
		s = removeblank(s);
		string str = ReadExpr(s);
		if(str[0] == error)
		{
			cout << "输入不合法，请重新输入。" << endl;
			con = false;
		}
		else
		{
			int pos = 0;
			root = createtree(str,pos); 		
			postorder(root , posexpr);
			cout << posexpr << endl;
			WriteExpr(posexpr,flag);
		}
		if(flag == false)
		{
			 con = false;
			 cout << " 对不起，您的输入有误；请重新输入。" << endl;
		}
		while(con)
		{
			cout << "  请输入你想进行的操作 ：" << endl;
			cout << "  --对变量进行赋值输入1；" << endl;
			cout << "  --对表达式进行求值请输入2；" << endl;
			cout << "  --对表达式进行与新表达式合并请输入3；" << endl;
			cout << "  --对表达式进行偏导操作请输入4；" << endl;
			cout << "  --对表达式进行合并常数项请输入5；" << endl;
			cout << "  --退出请按除1,2,3,4,5的任意键" << endl;
			char n;
			cin >> n;
			if(n == '1')
			{
				cout << "请输入要操作的变量:" << endl;
				string var;
				cin >> var;
				cout << "请输入要赋予的值:"  << endl;
				string value;
				cin >> value;
				assign(root,var,value);
				cout << "表达式变为："  << endl;
				posexpr.clear();
				postorder(root,posexpr);
				WriteExpr(posexpr,flag);
			}
			else if(n == '2')
			{
				cout << "求出的值为：" << endl;
				Value(posexpr);
			}	
			else if(n == '3')
			{
				cout << " --请输入新的前缀表达式：" << endl;
				string snew , posexprnew;
				bool flagnew = true , connew = true;
				cin >> snew;
				snew = removeblank(snew);
				snew = ReadExpr(snew);
				int posnew = 0;
				bnode* rootnew = createtree(snew,posnew); 		
				postorder(rootnew , posexprnew);
				WriteExpr(posexprnew,flagnew);
				if(flagnew == false)
				{
					 connew = false;
					 cout << " 对不起，您的输入有误；无法计算。" << endl;
				}
				if(connew)
				{
					cout << "请输入对于两个多项式的操作：（+,-,*,/,^）" << endl; 
					char op;
					cin >> op;
					root = CompoundExpr(op,root,rootnew);
					MergeConst(root);
					cout << "表达式变为："  << endl;
					posexpr.clear();
					postorder(root,posexpr);
					WriteExpr(posexpr,flag);
				}
			}
			else if(n == '4')
			{
				cout << "请输入要求微分的变量：" << endl;
				string var;
				cin >> var;
				MergeConst(root);
				Diff(root,var);
				MergeConst(root);
				posexpr.clear();
				postorder(root,posexpr);
				cout << "微分后的表达式为： " << endl; 
				WriteExpr(posexpr,flag);
				
			} 
			else if(n == '5')
			{
				MergeConst(root);
				cout << "表达式变为： " << endl; 
				posexpr.clear();
				postorder(root,posexpr);
				WriteExpr(posexpr,flag);
			}
			else break;
		}
	}
	return 0;
}
