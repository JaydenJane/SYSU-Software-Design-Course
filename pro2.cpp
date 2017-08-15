#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <sstream>
using namespace std;

//界面函数
void printrule()
{
	cout << "  **************************************" << endl;
	cout << "  ********欢迎使用算术表达式计算器******" << endl;
	cout << "  **************************************" << endl << endl;
}

//新建一个结构体，为了方便将算式分解之后进行存储 
struct Linkstring
{
	string data;
	struct Linkstring *next;
};

//将输入的算术表达式分解，每一部分存储成链表的节点的形式 
Linkstring* transform(string str)
{
	Linkstring *first = new Linkstring;
	first -> next = NULL;
	Linkstring *p;
	p = first;
	for(int i = 0 ; i < str.length(); i++)
	{
		//为算术符号时 
		if(str[i] == '(' || str[i] == ')' || str[i] == '+'  || str[i] == '-' || str[i] == '*' || str[i] == '/'|| str[i] == '#') 
		{
			//进行节点的插入 
			string tmp;
			tmp.push_back(str[i]);
			Linkstring *q = new Linkstring;
			q -> data = tmp; 
			q -> next = p -> next;
			p -> next = q ;
			p = q;
		} 
		//为数字时 
		else if(str[i] >= '0' && str[i] <= '9')
		{
			bool judge = false;
			string tmp;  
            while(str[i]>='0' && str[i]<='9')  
            {
                tmp.push_back(str[i]);  
                ++i;  
            }
            //小数的情况 
            if(str[i] == '.')  
            {  
            	judge = true;
                ++i;  
                if((str[i]>='0' && str[i]<='9'))  
                {  
                    tmp.push_back('.');  
                    while((str[i]>='0' && str[i]<='9') || str[i] == '^')  
                    {  
                        tmp.push_back(str[i]);  
                        ++i;  
                    }  
                    Linkstring *q = new Linkstring;
					q -> data = tmp; 
					q -> next = p -> next;
					p -> next = q ;
					p = q;
                }
                //若小数点后没有数字，格式有错，此节点存入FALSE； 
				else    
                {  
                    Linkstring *q = new Linkstring;
					q -> data = "FALSE"; 
					q -> next = p -> next;
					p -> next = q ; 
					p = q;
                }    
			}
			//为乘方时 
			else if(str[i] == '^')
			{
				judge = true;
                ++i;  
                if(str[i]>='0' && str[i]<='9')  
                {  
                    tmp.push_back('^');  
                    while((str[i]>='0' && str[i]<='9') || str[i] == '.')  
                    {  
                        tmp.push_back(str[i]);  
                        ++i;  
                    }  
                    Linkstring *q = new Linkstring;
					q -> data = tmp; 
					q -> next = p -> next;
					p -> next = q ;
					p = q;
                }
                //乘方符号后面没有数字，格式错误，存入FALSE 
				else    
                {  
                    Linkstring *q = new Linkstring;
					q -> data = "FALSE"; 
					q -> next = p -> next;
					p -> next = q ; 
					p = q;
                }    
			}
			//由于在判断小数和乘方时已进行节点的插入，所以进行判断此项是否为小数或者乘方，否则进行节点插入 
			if(judge == false)
			{
				Linkstring *q = new Linkstring;
				q -> data = tmp; 
				q -> next = p -> next;
				p -> next = q ;
				p = q;
			}
			i--;
		}
		//当此项为其他符号或字母，插入FALSE 
		else    
        {  
            Linkstring *q = new Linkstring;
			q -> data = "FALSE"; 
			q -> next = p -> next;
			p -> next = q ; 
			p = q;
        } 
	} 
	return first;
}
// 异常类的定义
class lstackexception
{
	public:
		lstackexception(const char* msg);
		const char* what() const;
	private:
		const char* message; 
}; 
lstackexception::lstackexception(const char* msg)
{
	message = msg;
}
const char* lstackexception::what() const
{
	return message;
}

// 链栈的定义
template <class DT>
class Lstack
{
	public:
		Lstack();
		~Lstack();
		void push(DT n);
		DT pop();
		DT gettop();
		void printf();
		bool empty();
	private:
		struct snode{
			DT data;
			struct snode *next;
		}; 
		snode *top;
};

template <class DT>
Lstack<DT>::Lstack()
{
	top = NULL;
}

template <class DT>
Lstack<DT>::~Lstack()
{
	while(top != NULL)
	{
		snode *tmp;
		tmp = top;
		top = top->next;
		delete tmp;
	} 
}

template <class DT>
void Lstack<DT>::push(DT n)
{
	snode *tmp ;
	tmp = new snode;
	tmp->data = n;
	tmp->next = top;
	top = tmp;
}

template <class DT>
DT Lstack<DT>::pop()
{
	if(top == NULL) 
	{
		throw lstackexception("Linkstack is empty!"); //抛出异常 
	}
	DT databox = top->data;
	snode *p = top;
	top = top->next;
	delete p;
	return databox;
}

template <class DT>
DT Lstack<DT>::gettop()
{
	if(top == NULL) 
	{
		throw lstackexception("Linkstack is empty!"); //抛出异常 
	}
	return top->data;
}

template <class DT>
void Lstack<DT>::printf()
{
	if(top == NULL) 
	{
		cout << setw(30) << setiosflags(ios::left) << "NULL" ;
	}
	else
	{
		string s;
		snode* p;
		p = top;
		while(p)
		{
			s =  p->data + " " +s ;
			p = p->next;			
		}
		cout << setw(30) << setiosflags(ios::left) << s ;
	}
}

template <class DT>
bool Lstack<DT>::empty()
{
	if(top == NULL)
	{
		return true;
	}
	return false;
}

//优先级函数的定义 
int priority(string ch)
{
	if(ch == "#") return 0; 
	else if( ch == "(" || ch ==")") return 1;
	else if( ch == "*" || ch == "/") return 3;
	else if( ch == "+" || ch == "-") return 4;
	else return -2;
} 

//栈外优先级函数定义
int priorityOUT(string ch)
{
	if(ch == "#") return 0; 
	else if( ch == "(") return 8;
	else if (ch == ")") return 1;
	else if( ch == "*" || ch == "/") return 3;
	else if( ch == "+" || ch == "-") return 2;
	else return -2;
} 

 
//栈内优先级函数的定义 
int priorityIN(string ch)
{
	if(ch == "#") return 0; 
	else if( ch == ")") return 8;
	else if (ch == "(") return 1;
	else if( ch == "*" || ch == "/") return 5;
	else if( ch == "+" || ch == "-") return 3;
	else return -2;
} 

//输入异常函数检验
bool correction(Linkstring* str)
{
	bool judge = true;
	int rcount = 0 , lcount = 0; //计数器，计量左右括号数是否相等 
	Linkstring* pre = str->next;
	Linkstring* post ;
	cout << "----analysis:---" << endl;
	//若存在非法字符的输入， 输入有误 
	while(pre)
	{
		cout << "    <" << pre->data <<"  , "<< priority(pre->data)<< ">"<< endl;
		if(pre->data == "FALSE")
		{
			 judge = false;
			 break;
		}
		pre = pre -> next;
	}
	cout << endl;
	if( judge == false) return judge;
	//判断是否存在输入格式的错误 
	pre = str->next;
	post = pre->next;
	//判断是否存在开头为算术符号 
	if(priority(pre->data) != -2 && pre->data != "(")
	{
		return false;
	}
	while(post->next)
	{
		//当为右括号时，其前一位数不能为除数字和右括号之外的； 
		if(post->data == ")")
		{
			rcount++;
			if(priority(pre->data) != -2)
			{
				if( pre->data != post->data)
				{
//				cout << "gg1" << endl;
					judge = false;
					break;
				}
			}
		}
		//当为左括号时，其后一位数不能为除数字和右括号之外的；
		else if(pre->data == "(")
		{
			lcount++;
			if(priority(post->data) != -2)
			{
				if(post->data != pre->data)
				{
//					cout << "gg2" << endl;
					judge = false;
					break;
				}
			}
		}
		//相邻两个数据的优先级绝对值之差小于2 
		else if( abs( priority(post->data) - priority(pre->data) ) < 2)
		{
//			cout << "gg3" << endl;
			judge = false;
			break;
		}
		pre = post;
		post= post->next;
	}
	if (priority(pre->data) == 3 || priority(pre->data) == 4) judge = false;
	//如果右括号数和左括号数不等 
	if(rcount != lcount) judge = false;
	return judge;
} 

//去掉字符串空格的函数
string replace(string ls)
{
	string s;
	for(int i = 0 ; i < ls.length() ; i++)
	{
		if(ls[i] != ' ') s = s + ls[i];
	}
	return s;
} 

//转换成数字函数
long double transform_to_num(string s)
{
	int pos = s.find(".");
	int chengfang = s.find("^");
	long double sum = 0;
	//当该数为小数时； 
	if(pos != -1) 
	{
		//当没有乘方时 
		if(chengfang == -1)
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
		//有乘方 
		else
		{
			if(pos < chengfang)
			{
				for(int i = 0; i < pos ; i++)
				{
					sum = sum + 1.0*pow(10,pos-i-1)*(s[i] - '0');
				}
				for(int j = pos + 1; j < chengfang ; j++)
				{
					sum = sum + 1.0*pow(0.1,j-pos)*(s[j] - '0');
				}
				long double jieshu = 0;
				for(int j = chengfang + 1; j < s.length() ; j++)
				{
					jieshu = jieshu + 1.0*pow(10,j-chengfang-1)*(s[j] - '0');
				}
				return pow(sum,jieshu);
			}
			else
			{
				for(int i = 0; i < chengfang ; i++)
				{
					sum = sum + 1.0*pow(10,chengfang-i-1)*(s[i] - '0');
				}
				long double jieshu = 0;
				for(int j = chengfang + 1; j < pos ; j++)
				{
					jieshu = jieshu + 1.0*pow(10,pos-j-1)*(s[j] - '0');
				}
				for(int j = pos+1 ; j < s.length() ; j++)
				{
					jieshu = jieshu + 1.0*pow(0.1,j-pos) *(s[j] - '0');
				}
				return pow(sum,jieshu);
			}
		}
	}
	//不为小数时； 
	else 
	{
		if(chengfang == -1)
		{
			for(int i = 0 ; i < s.length() ; i++)
			{
				sum = sum + 1.0*pow(10,s.length()-1-i)*(s[i] - '0');
			}
			return sum;
		}
		else
		{
			for(int i = 0; i < chengfang ; i++)
			{
				sum = sum + 1.0*pow(10,chengfang-i-1)*(s[i] - '0');
			}
			long double jieshu = 0;
			for(int j = chengfang + 1; j < s.length() ; j++)
			{
				jieshu = jieshu + 1.0*pow(10,j-chengfang-1)*(s[j] - '0');
			}
			return pow(sum,jieshu);
		}
	}
} 


//计算函数 
long double calculate(long double num1_, string op , long double num2_)
{
	if(op == "+") return num1_ + num2_;
	else if(op == "-") return num1_ - num2_;
	else if(op == "*") return num1_ * num2_;
	else if(op == "/") return num1_ / num2_;
	else throw lstackexception("Does not conform to the rules of calculation！");
}

//算术运行函数 
void run()
{
	//out记录操作内容
	string str , op , out , stmp;
	stringstream ss;
	long double num1, num2 ,tmpnum;
	bool step = true;
	long double result;
	int process , len;
	while(1) 
	{ 	
		Lstack<long double> OPRD;       //数字栈 
		Lstack<string> OPTD , OR , OT;  // OPTD是运算符栈 ，OT模拟当前运算符栈，OR模拟当前数字栈  
		bool judge;
		if(step == false) 
		{
			cout << "    输入算术表达式格式有误，请重新输入: " << endl;
			step = true;
		}
		else cout << "   请输入算术表达式：" << endl; 
		getline(cin,str,'\n');
		str = replace(str);       //去空格 
		str = str + "#";          //补# 
		Linkstring* ls = transform(str);
		judge = correction(ls);
		//cout << judge << endl;
		if(judge == false)
		{
			step = false;
		}
		else 
		{
			process = 1;
			//初始格式打印 
			cout << setw(30) << setiosflags(ios::left ) << "process"  ;
			cout << setw(30) << setiosflags(ios::left) << "operand stack" ;
			cout << setw(30) << setiosflags(ios::left) << "opertor stack" ;
			cout << setw(30) << setiosflags(ios::left) << "operation";
			cout << endl;
			cout << setw(30) << setiosflags(ios::left) << process ;
			cout << setw(30) << setiosflags(ios::left) << "NULL" ;
			cout << setw(30) << setiosflags(ios::left) << "NULL" ;
			cout << endl;
			OPTD.push("#");
			OT.push("#");
			Linkstring* p;
			p = ls->next;
			while(p)
			{
				if( priority(p->data) == -2) //该部分为数字时 
				{
					tmpnum = transform_to_num(p->data);
					OPRD.push(tmpnum);
					result = tmpnum;
					process++;
					cout << setw(30) << setiosflags(ios::left) << process ; 
					OR.push(p->data);
					OR.printf();
					OT.printf();
					out = p->data + "进入数字栈";
					cout << setw(30) << setiosflags(ios::left) << out;
					cout << endl;
					p = p->next;
					
				}
				else  //为操作符时 
				{
					try{
						string tmp = OPTD.gettop();
						if(priorityOUT(p->data) >= priorityIN(tmp) ) // 判断优先级 
						{
							process++;
							OPTD.push(p->data);
							cout << setw(30) << setiosflags(ios::left) << process ;
							OT.push(p->data);
							OR.printf();
							OT.printf();
							out = p->data + "进入操作符栈";
							cout << setw(30) << setiosflags(ios::left) << out;
							cout << endl;
						}
						else
						{
							if(p->data == ")")
							{
								while(tmp != "(")
								{
									num2 = OPRD.pop();
									num1 = OPRD.pop();
									op = OPTD.pop();
									result = calculate(num1,op,num2);
									OPRD.push(result);
									process++;
									OR.pop();
									OR.pop();
									OT.pop();
									ss << result; //将double转化为string型 
									ss >> stmp;
									ss.clear();  // 清空 
									cout << setw(30) << setiosflags(ios::left) << process ;
									OR.printf();
									OT.printf();
									out = op + "出栈计算";
									cout << setw(30) << setiosflags(ios::left) << out;
									cout << endl;
									OR.push(stmp);
									op.clear();
									tmp = OPTD.gettop();
									process++;
									cout << setw(30) << setiosflags(ios::left) << process;
									OR.printf();
									OT.printf();
									out = "得出结果入栈";
									cout << setw(30) << setiosflags(ios::left) << out;
									cout << endl;
								}
								OPTD.pop();	
								OT.pop();
							} 
							else if(p->data != "#")
							{
								num2 = OPRD.pop();
								num1 = OPRD.pop();
								op = OPTD.pop();
								result = calculate(num1,op,num2);
								OPRD.push(result);
								OPTD.push(p->data);
								process++;
								OR.pop();
								OR.pop();
								OT.pop();
								ss << result;
								ss >> stmp;
								ss.clear();
								cout << setw(30) << setiosflags(ios::left) << process ;
								OR.printf();
								OT.printf();
								out = op + "出栈计算";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
								OR.push(stmp);
								op.clear();
								process++;
								cout << setw(30) << setiosflags(ios::left) << process;
								OR.printf();
								OT.printf();
								out = "得出结果入栈";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
								process++;
								cout << setw(30) << setiosflags(ios::left) << process;
								OT.push(p->data);
								OR.printf();
								OT.printf();
								out = p->data + "进入操作符栈";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
							}
							else if(p->data == "#")
							{
								while(tmp!="#")
								{
									num2 = OPRD.pop();
									num1 = OPRD.pop();
									op = OPTD.pop();
									result = calculate(num1,op,num2);
									OPRD.push(result);
									ss << result;
									ss >> stmp;
									ss.clear();
									process++;
									OR.pop();
									OR.pop();
									OT.pop();
									cout << setw(30) << setiosflags(ios::left) << process ;
									OR.printf();
									OT.printf();
									out = op + "出栈计算";
									cout << setw(30) << setiosflags(ios::left) << out;
									cout << endl;
									OR.push(stmp);
									op.clear();
									tmp = OPTD.gettop();
								}
								process++;
								cout << setw(30) << setiosflags(ios::left) << process;
								OR.printf();
								OT.printf();
								out = "得出最后结果";
								cout << setw(30) << setiosflags(ios::left) << out;
								cout << endl;
								OR.pop();
								op.clear();
							}
						}
						p = p->next;
					}
					catch(lstackexception ex)
					{
						cout << ex.what() << endl;
						break;
					}
				}
			}
			cout <<"   计算结果为：  " <<  result << endl << endl << endl;
			str.clear();		
		}
	}
}

int main()
{
	printrule();
	while(1)
	{
		run();
	}
	return 0;
}
