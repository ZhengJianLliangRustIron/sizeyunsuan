

#include "stdafx.h"
#include<iostream>
#include<string>
#include<stdlib.h>
#include<ctime>
#include<deque>
#include<stack>
#include<fstream>
#include<windows.h>
using namespace std;

string charToString(char c);
bool isOperator(string o);
bool isPar(string par);
int getPar(string par);
void check(string c, stack<string>& coll2, deque<string>& coll3);
void allocate(deque<string>& coll1, stack<string>& coll2, deque<string>& coll3);
void calculate(deque<string>& coll3, stack<int>& coll4);
string turnString(int a);
string addParentheses(string operCharToString,int Num[],deque<string>& coll1);
bool repeatMulCover(int Num[],int **mulCover,int left);
bool repeatAddCover(int Num[],int **addCover,int left);
string GetProgramDir();
bool isOperatorChar(char o);

bool isOK;

int main()
{
	string cinStr[4];
	string n,r,e,a;
	for(int i=0;i<4;i++)
		cin>>cinStr[i];
	for(int i=0;i<4;i++){
		if(cinStr[i]=="-n")
			n=cinStr[i+1];
		if(cinStr[i]=="-r")
			r=cinStr[i+1];
		if(cinStr[i]=="-e")
			e=cinStr[i+1];
		if(cinStr[i]=="-a")
			a=cinStr[i+1];
	}
	string programDir=GetProgramDir();
	if(n!="" && r!="")
	{
		/*DWORD start_time=GetTickCount();*/
		ofstream oufQuestion;
		ofstream oufAnswer;
		oufQuestion.open(programDir+"Exercises.txt");
		oufAnswer.open(programDir+"Answers.txt");
		int N,R;
		N=atoi(n.c_str());
		R=atoi(r.c_str());
		//题目
		string *question=new string[N];
		//答案
		string *answer=new string[N];
		//题目中含有的数字（随机生成）
		int **Num=new int*[N];
		//题目中包含运算符的数量（随机生成，最多为3，最少为1）
		int *operCharNumber=new int[N];
		//题目中含有的运算符（随机生成）
		char **operatorChar=new char*[N];
		//用二维数组判断一个加法运算符的重复
		int **addCover=new int*[R];
		//用二维数组判断一个乘法运算符的重复
		int **mulCover=new int*[R];
		for(int i=0;i<R;i++){
			addCover[i]=new int[R];
			mulCover[i]=new int[R];
			memset(addCover[i], 0, sizeof(int)*R);
			memset(mulCover[i], 0, sizeof(int)*R);
		}
		//用一维数组遍历的方法判断一位运算符减和除的重复
		int one=0;
		string *oneOperator=new string[N];
		//用一维数组遍历的方法判断二个运算符的重复
		int two=0;
		string *twoOperator=new string[N];
		//用一维数组遍历的方法判断三个运算符的重复
		int three=0;
		string *threeOperator=new string[N];
		srand((unsigned)time(NULL));
		for(int i=0;i<N;i++){
			Num[i]=new int[4];
			operatorChar[i]=new char[3];
			isOK=false;//判断算式是否合法，不合法则重新生成算式
			while(!isOK){
				string operCharToString="";
				//随机生成运算符的个数
				operCharNumber[i]=(rand()%3)+1;
				//随机生成数字
				for(int j=0;j<=operCharNumber[i];j++){
					Num[i][j]=rand()%R;
				}
				//随机生成运算符
				for(int j=0;j<operCharNumber[i];j++){
					switch((rand()%4)+1){
						case 1:operatorChar[i][j]='+';break;
						case 2:operatorChar[i][j]='-';break;
						case 3:operatorChar[i][j]='*';break;
						case 4:operatorChar[i][j]='/';break;
					}
					operCharToString+=operatorChar[i][j];
				}
				deque<string> coll1;  //盛放中缀表达式  
				stack<string> coll2;  //盛放操作符  
				deque<string> coll3;    //盛放后缀表达式  
				stack<int>	coll4;  //计算后缀表达式的辅助容器
				//运算符个数大于1和等于1分开处理和计算
				if(operCharToString.length()>1){
					question[i]=addParentheses(operCharToString,Num[i],coll1)+"=";
					bool twoCover=false;
					bool threeCover=false;
					//二个和三个运算符判断是否合法
					if(operCharToString.length()==2){
						for(int j=0;j<two;j++){
							if(twoOperator[j]==question[i]){
								twoCover=true;
								break;
							}
						}
					}
					else
					{
						for(int j=0;j<three;j++){
							if(threeOperator[j]==question[i]){
								threeCover=true;
								break;
							}
						}
					}
					if(twoCover || threeCover)
						continue;
					//从coll中取出元素，分配元素到coll2和coll3中  
					allocate(coll1,coll2,coll3);
					//计算后缀表达式  
					calculate(coll3,coll4);
					if(isOK)
					{
						if(operCharToString.length()==2)
						{
							twoOperator[two]=question[i];
							two++;
						}
						else
						{
							threeOperator[three]=question[i];
							three++;
						}
						oufQuestion<<i+1<<'.'<<question[i]<<'\n';
						oufAnswer<<i+1<<'.'<<coll4.top()<<'\n';
						//cout<<"题目："<<i<<"   "<<question[i]<<coll4.top()<<endl;
					}
				}
				else{
					//一位运算符判断是否合法
					if(operatorChar[i][0]=='/'){
						while(Num[i][1]==0){
							Num[i][1]=rand()%R;
						}
					}
					if(operatorChar[i][0]=='/'){
						while(Num[i][0]%Num[i][1]!=0){
							Num[i][1]=rand()%R;
							while(Num[i][1]==0){
								Num[i][1]=rand()%R;
							}
							Num[i][0]=rand()%R;
						}
					}
					if(operatorChar[i][0]=='-'){
						while(Num[i][0]<Num[i][1]){
							if(Num[i][1]>=R/2 && Num[i][0]>=R/2){
								Num[i][1]=rand()%R;
							}
							else if(Num[i][1]>=R/2 && Num[i][0]<=R/2){
								Num[i][1]=rand()%R;
								Num[i][0]=rand()%R;
							}
							else{
								Num[i][0]=rand()%R;
							}
						}
					}
					switch(operatorChar[i][0]){
						case '+':
							while(repeatAddCover(Num[i],addCover,0)){
								Num[i][0]=rand()%R;
								Num[i][1]=rand()%R;
							 }
							break;
						case '*':
							while(repeatMulCover(Num[i],mulCover,0)){
								Num[i][0]=rand()%R;
								Num[i][1]=rand()%R;
							 }
							break;
					}
					question[i]=turnString(Num[i][0])+operatorChar[i][0]+turnString(Num[i][1])+"=";
					bool cover=false;
					if(operatorChar[i][0]=='/' || operatorChar[i][0]=='-'){
						for(int j=0;j<one;j++){
							if(oneOperator[j]==question[i]){
								cover=true;
								break;
							}
						}
					}
					if(cover)
						continue;
					oneOperator[one]=question[i];
					one++;
					int result=-1;
					switch(operatorChar[i][0]){
						case '+':result=Num[i][0]+Num[i][1];break;
						case '-':result=Num[i][0]-Num[i][1];break;
						case '*':result=Num[i][0]*Num[i][1];break;
						case '/':result=Num[i][0]/Num[i][1];break;
					}
					isOK=true;
					oufQuestion<<i+1<<'.'<<question[i]<<'\n';
					oufAnswer<<i+1<<'.'<<result<<'\n';
					//cout<<"题目："<<i<<"   "<<question[i]<<result<<endl;
				}
			}
		}
		//DWORD end_time=GetTickCount();
		//cout<<programDir<<endl;
		//cout<<"The run time is:"<<(end_time-start_time)<<"ms!"<<endl;//输出运行时间
		oufQuestion.close();
		oufAnswer.close();
	}
	else if(e!="" && a!=""){
		fstream openQuestion;
		openQuestion.open(programDir+e,ios::in);
		if(!openQuestion.good()){
			cout<<e+"文件打开失败";
			return 0;
		}
		fstream openAnswer;
		openAnswer.open(programDir+a,ios::in);
		if(!openAnswer.good()){
			cout<<a+"文件打开失败";
			return 0;
		}
		/*exercisefile*/
		//streampos sizeQuestion = openQuestion.tellg();  // 得到文件位置
		//openQuestion.seekg(0, ios::end); // 定位至文件末端
		//size_t filesizeQuestion = openQuestion.tellg() - sizeQuestion; // 相差值为文件大小
		//openQuestion.seekg(sizeQuestion); // 返回文件开头
		string *strQuestion = new string[10000]; // 开空间，注意 + 1
		/*answerfile*/
		//streampos sizeAnswer = openAnswer.tellg();  // 得到文件位置
		//openAnswer.seekg(0, ios::end); // 定位至文件末端
		//size_t filesizeAnswer = openAnswer.tellg() - sizeAnswer; // 相差值为文件大小
		//openAnswer.seekg(sizeAnswer); // 返回文件开头
		string *strAnswer = new string[10000]; // 开空间，注意 + 1
		//处理
		int i=0;
		while(!openQuestion.eof()){
			char c[100];
			openQuestion.getline(c,100,'\n');
			strQuestion[i]=c;
			char c1[100];
			openAnswer.getline(c1,100,'\n');
			strAnswer[i]=c1;
			i++;
		}
		openQuestion.close();
		openAnswer.close();
		int correct[10000];
		int cor=0;
		int wrong[10000];
		int wro=0;
		for(int j=0;j<i;j++){
			string question,answer;
			for(int k=0;k<strQuestion[j].length();k++){
				if(strQuestion[j][k]=='.'){
					strQuestion[j]=strQuestion[j].substr(k+1);
					break;
				}
			}
			question=strQuestion[j];
			for(int k=0;k<strAnswer[j].length();k++){
				if(strAnswer[j][k]=='.'){
					strAnswer[j]=strAnswer[j].substr(k+1);
					break;
				}
			}
			answer=strAnswer[j];
			deque<string> coll1;  //盛放中缀表达式  
			stack<string> coll2;  //盛放操作符  
			deque<string> coll3;    //盛放后缀表达式  
			stack<int>	coll4;  //计算后缀表达式的辅助容器
			string s="";
			bool b=false;
			if(question!=""){
				for(int k=0;k!=question.length()-1;++k)   
				{  
					//逐一加入每个字符，这里使用deque因为deque在两端删除添加的速度最快
					if(question[k]=='('){
						coll1.push_back("(");
						continue;
					}
					if(isOperatorChar(question[k])){
						if(s!="")
							coll1.push_back(s);
						string str=charToString(question[k]);
						coll1.push_back(str);
						s="";
						continue;
					}
					s+=question[k];
				}  
				if(question[question.length()-2]!=')')
					coll1.push_back(s);
				//从coll中取出元素，分配元素到coll2和coll3中 
				allocate(coll1,coll2,coll3);
				//计算后缀表达式  
				calculate(coll3,coll4);
				if(coll4.top()==atoi(answer.c_str())){
					correct[cor]=j+1;
					cor++;
				}
				else{
					wrong[wro]=j+1;
					wro++;
				}
			}
		}
		ofstream grade;
		grade.open(programDir+"Grade.txt");
		grade<<"Correct:"<<cor<<"(";
		for(int j=0;j<cor;j++){
			grade<<correct[j];
			if(j!=cor-1)
				grade<<",";
		}
		grade<<")"<<'\n';
		grade<<"Wrong:"<<wro<<"(";
		for(int j=0;j<wro;j++){
			grade<<wrong[j];
			if(j!=wro-1)
				grade<<",";
		}
		grade<<")"<<'\n';
		grade.close();
	}
	return 0;
}

//char toChange string
string charToString(char c)
{
	string t(&c);
	return t;
}
//int toChange string
string turnString(int i){
	char turnChar[10];
	sprintf(turnChar,"%d",i);
	return turnChar;
}
//判断是否是运算符
bool isOperator(string o)
{
	if(o=="+" || o=="-" || o=="*" || o=="/" || o=="(" || o==")")
		return true;
	return false;
}
//判断是否是运算符（参数：char）
bool isOperatorChar(char o)
{
	if(o=='+' || o=='-' || o=='*' || o=='/' || o=='(' || o==')')
		return true;
	return false;
}
//判断是否是括号
bool isPar(string par)   
{  
    if(par=="("||par==")")   
        return true;   
    else   
        return false;  
}  
  
//获得符号的优先性  
int getPar(string par)   
{  
    switch(par[0])   
    {  
    case '+':  
    case '-':  
        return 0;   //如果是加减，返回0  
        break;  
    case '*':  
    case '/':  
        return 1;   //如果是乘除，返回1  
        break;  
    case '(':  
    case ')':  
        return -1;  //注意，这里将括号设为最低优先级，因此括号不会被弹出，除非遇到右括号  
        break;  
     }  
}  
  
//判断符号的优先性  
void check(string c, stack<string>& coll2, deque<string>& coll3)   
{    
    if(coll2.empty())   
    {  
        coll2.push(c);  
        return;  
    }  
   
    if(isPar(c))   
    {  
        if(c=="(")   
            coll2.push(c);  
        else   
        {  
            //弹出所有元素直到遇到左括号  
            while(coll2.top()!="(")   
            {    
                string ch = coll2.top();  
                coll3.push_back(ch);  
                coll2.pop();  
            }  
  
            //当遇到左括号时，弹出但不加入coll3(后缀表达式中）  
            coll2.pop();    
        }  
    }  
    else    //如果不是括号  
    {  
        //取出栈顶元素，与当前符号进行优先性比较  
        string sym = coll2.top();    
  
        //比较两符号的优先性  
        if(getPar(c)<=getPar(sym))    
        {  
            //如果c的优先性比栈顶符号小或等于，弹出栈顶元素  
            coll2.pop();  
            //并将其压入coll3（后缀表达式）中  
            coll3.push_back(sym);  
            //递归调用check,比较当前符号c与下一个栈顶符号的优先性  
            check(c,coll2,coll3);     
        }  
        else   
        {  
            //如果c比栈顶符号优先级大，那将c压入coll2(操作符栈）中  
            coll2.push(c);    
        }  
    }  
}  
  
//从coll中取出元素，分配元素到coll2和coll3中  
void allocate(deque<string>& coll1, stack<string>& coll2, deque<string>& coll3)   
{    
    while(!coll1.empty())   
    {  
        string c = coll1.front();  
        coll1.pop_front();  
  
        if(!isOperator(c))  
        {  
            coll3.push_back(c);  
        }  
        else   
        {  
            //调用check函数，针对不同情况作出不同操作  
            check(c,coll2,coll3);    
        }  
  
    }  
  
    //如果输入结束，将coll2的元素全部弹出，加入后缀表达式中  
    while(!coll2.empty())   
    {    
        string c = coll2.top();  
        coll3.push_back(c);  
        coll2.pop();  
    }  
}  
  
//计算后缀表达式  
void calculate(deque<string>& coll3, stack<int>& coll4)   
{    
    while(!coll3.empty())   
    {  
        string c = coll3.front();  
        coll3.pop_front();  
          
        //如果是操作数，压入栈中  
        if(!isOperator(c))   
        {  
            //减去'0'得出偏移值，即为真实数值（如果直接转换成int，结果不对，因为char 转换为int是其编码值，例如'1'的编码值为49  
            int op =atoi(c.c_str());      
            coll4.push(op);       
        }  
        else     //如果是操作符，从栈中弹出元素进行计算  
        {   
            int op1 = coll4.top();  
            coll4.pop();  
            int op2 = coll4.top();  
            coll4.pop();  
            switch(c[0])   
            {  
            case '+':  
                coll4.push(op2+op1);  
                break;  
            case '-':  
				if(op2<op1)
					return;
                coll4.push(op2-op1);  
                break;  
            case '*':  
                coll4.push(op2*op1);  
                break;  
            case '/':  
				if(op1==0 || op2%op1!=0)
					return;
                coll4.push(op2/op1);  //注意是op2(op)op1而不是op1(op)op2  
                break;  
            }  
        }  
    }  
	isOK=true;
}



//将数字与运算符整合成算式并将元素压入桟
string addParentheses(string operCharToString,int Num[],deque<string>& coll1)
{
	string t="";
	bool first=false;
	bool second=false;
	bool third=false;
	if(rand()%2==1){
		first=true;
		t+='('+turnString(Num[0])+operCharToString[0]+turnString(Num[1])+')';
		coll1.push_back("(");
		coll1.push_back(turnString(Num[0]));
		coll1.push_back(charToString(operCharToString[0]));
		coll1.push_back(turnString(Num[1]));
		coll1.push_back(")");
	}
	else{
		t+=turnString(Num[0])+operCharToString[0];
		coll1.push_back(turnString(Num[0]));
		coll1.push_back(charToString(operCharToString[0]));
	}
	if(rand()%2==1 && !first){
		second=true;
		t+='('+turnString(Num[1])+operCharToString[1]+turnString(Num[2])+')';
		coll1.push_back("(");
		coll1.push_back(turnString(Num[1]));
		coll1.push_back(charToString(operCharToString[1]));
		coll1.push_back(turnString(Num[2]));
		coll1.push_back(")");
	}
	else if(first){
		t+=operCharToString[1];
		coll1.push_back(charToString(operCharToString[1]));
	}
	else{
		t+=turnString(Num[1])+operCharToString[1];
		coll1.push_back(turnString(Num[1]));
		coll1.push_back(charToString(operCharToString[1]));
	}
	if(operCharToString.length()==3){
		if(rand()%2==1 && !second){
			t+='('+turnString(Num[2])+operCharToString[2]+turnString(Num[3])+')';
			coll1.push_back("(");
			coll1.push_back(turnString(Num[2]));
			coll1.push_back(charToString(operCharToString[2]));
			coll1.push_back(turnString(Num[3]));
			coll1.push_back(")");
		}
		else if(!second){
			t+=turnString(Num[2])+operCharToString[2]+turnString(Num[3]);
			coll1.push_back(turnString(Num[2]));
			coll1.push_back(charToString(operCharToString[2]));
			coll1.push_back(turnString(Num[3]));
		}
		else{
			t+=operCharToString[2]+turnString(Num[3]);
			coll1.push_back(charToString(operCharToString[2]));
			coll1.push_back(turnString(Num[3]));
		}
	}
	else if(!second){
		t+=turnString(Num[2]);
		coll1.push_back(turnString(Num[2]));
	}
	//cout<<operCharToString<<"      "<<t<<endl;
	return t;
}

//判断加法重复
bool repeatAddCover(int Num[],int **addCover,int left)
{
	if(addCover[Num[left]][Num[left+1]]==1)
		return false;
	addCover[Num[left]][Num[left+1]]=1;
	addCover[Num[left+1]][Num[left]]=1;
	return true;
}

//判断乘法重复
bool repeatMulCover(int Num[],int **mulCover,int left)
{
	if(mulCover[Num[left]][Num[left+1]]==1)
		return false;
	mulCover[Num[left]][Num[left+1]]=1;
	mulCover[Num[left+1]][Num[left]]=1;
	return true;
}

//获取执行文件路径
string GetProgramDir()  
{   
    char exeFullPath[MAX_PATH]; // Full path
    string strPath = "";
 
    GetModuleFileName(NULL,exeFullPath,MAX_PATH);
    strPath=(string)exeFullPath;    // Get full path of the file
    int pos = strPath.find_last_of('\\', strPath.length());
	strPath=strPath.substr(0, pos);
	int t=1,j=0;
	string s="";
	for(int i=0;i<strPath.length();i++){
		if(strPath[i]=='\\'){
			s+=strPath.substr(j,t);
			s+="\\";
			t=0;
			j=i+1;
		}
		t++;
	}
	s+=strPath.substr(j,t);
	strPath=s;
	strPath+="\\";
	strPath+="\\";
    return strPath;  // Return the directory without the file name
}


//初始化输入数据类
class InitInput{
	public:
	void init(int argc,char *argv[],string &n,string &r,string &e,string &a){
		for(int i=1;i<argc;i++){
			string s(argv[i]);
			if(s=="-n"){
				if(i+1<argc){
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a"){
						n=str;
					}
					if(n==""){
						cout<<"请输入-n的值！";
						return;
					}
				}
			}
			if(s=="-r"){
				if(i+1<argc){
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a"){
						r=str;
					}
					if(r==""){
						cout<<"请输入-r的值！";
						return;
					}
				}
			}
			if(s=="-e"){
				if(i+1<argc){
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a"){
						e=str;
					}
					if(e==""){
						cout<<"请输入-e的值！";
						return;
					}
				}
			}
			if(s=="-a"){
				if(i+1<argc){
					string str(argv[i+1]);
					if(str!="-n" && str!="-r" && str!="-e" && str!="-a"){
						a=str;
					}
					if(a==""){
						cout<<"请输入-a的值！";
						return;
					}
				}
			}
		}
	}
};