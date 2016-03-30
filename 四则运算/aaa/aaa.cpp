

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
		//��Ŀ
		string *question=new string[N];
		//��
		string *answer=new string[N];
		//��Ŀ�к��е����֣�������ɣ�
		int **Num=new int*[N];
		//��Ŀ�а����������������������ɣ����Ϊ3������Ϊ1��
		int *operCharNumber=new int[N];
		//��Ŀ�к��е��������������ɣ�
		char **operatorChar=new char*[N];
		//�ö�ά�����ж�һ���ӷ���������ظ�
		int **addCover=new int*[R];
		//�ö�ά�����ж�һ���˷���������ظ�
		int **mulCover=new int*[R];
		for(int i=0;i<R;i++){
			addCover[i]=new int[R];
			mulCover[i]=new int[R];
			memset(addCover[i], 0, sizeof(int)*R);
			memset(mulCover[i], 0, sizeof(int)*R);
		}
		//��һά��������ķ����ж�һλ��������ͳ����ظ�
		int one=0;
		string *oneOperator=new string[N];
		//��һά��������ķ����ж϶�����������ظ�
		int two=0;
		string *twoOperator=new string[N];
		//��һά��������ķ����ж�������������ظ�
		int three=0;
		string *threeOperator=new string[N];
		srand((unsigned)time(NULL));
		for(int i=0;i<N;i++){
			Num[i]=new int[4];
			operatorChar[i]=new char[3];
			isOK=false;//�ж���ʽ�Ƿ�Ϸ������Ϸ�������������ʽ
			while(!isOK){
				string operCharToString="";
				//�������������ĸ���
				operCharNumber[i]=(rand()%3)+1;
				//�����������
				for(int j=0;j<=operCharNumber[i];j++){
					Num[i][j]=rand()%R;
				}
				//������������
				for(int j=0;j<operCharNumber[i];j++){
					switch((rand()%4)+1){
						case 1:operatorChar[i][j]='+';break;
						case 2:operatorChar[i][j]='-';break;
						case 3:operatorChar[i][j]='*';break;
						case 4:operatorChar[i][j]='/';break;
					}
					operCharToString+=operatorChar[i][j];
				}
				deque<string> coll1;  //ʢ����׺���ʽ  
				stack<string> coll2;  //ʢ�Ų�����  
				deque<string> coll3;    //ʢ�ź�׺���ʽ  
				stack<int>	coll4;  //�����׺���ʽ�ĸ�������
				//�������������1�͵���1�ֿ�����ͼ���
				if(operCharToString.length()>1){
					question[i]=addParentheses(operCharToString,Num[i],coll1)+"=";
					bool twoCover=false;
					bool threeCover=false;
					//����������������ж��Ƿ�Ϸ�
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
					//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��  
					allocate(coll1,coll2,coll3);
					//�����׺���ʽ  
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
						//cout<<"��Ŀ��"<<i<<"   "<<question[i]<<coll4.top()<<endl;
					}
				}
				else{
					//һλ������ж��Ƿ�Ϸ�
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
					//cout<<"��Ŀ��"<<i<<"   "<<question[i]<<result<<endl;
				}
			}
		}
		//DWORD end_time=GetTickCount();
		//cout<<programDir<<endl;
		//cout<<"The run time is:"<<(end_time-start_time)<<"ms!"<<endl;//�������ʱ��
		oufQuestion.close();
		oufAnswer.close();
	}
	else if(e!="" && a!=""){
		fstream openQuestion;
		openQuestion.open(programDir+e,ios::in);
		if(!openQuestion.good()){
			cout<<e+"�ļ���ʧ��";
			return 0;
		}
		fstream openAnswer;
		openAnswer.open(programDir+a,ios::in);
		if(!openAnswer.good()){
			cout<<a+"�ļ���ʧ��";
			return 0;
		}
		/*exercisefile*/
		//streampos sizeQuestion = openQuestion.tellg();  // �õ��ļ�λ��
		//openQuestion.seekg(0, ios::end); // ��λ���ļ�ĩ��
		//size_t filesizeQuestion = openQuestion.tellg() - sizeQuestion; // ���ֵΪ�ļ���С
		//openQuestion.seekg(sizeQuestion); // �����ļ���ͷ
		string *strQuestion = new string[10000]; // ���ռ䣬ע�� + 1
		/*answerfile*/
		//streampos sizeAnswer = openAnswer.tellg();  // �õ��ļ�λ��
		//openAnswer.seekg(0, ios::end); // ��λ���ļ�ĩ��
		//size_t filesizeAnswer = openAnswer.tellg() - sizeAnswer; // ���ֵΪ�ļ���С
		//openAnswer.seekg(sizeAnswer); // �����ļ���ͷ
		string *strAnswer = new string[10000]; // ���ռ䣬ע�� + 1
		//����
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
			deque<string> coll1;  //ʢ����׺���ʽ  
			stack<string> coll2;  //ʢ�Ų�����  
			deque<string> coll3;    //ʢ�ź�׺���ʽ  
			stack<int>	coll4;  //�����׺���ʽ�ĸ�������
			string s="";
			bool b=false;
			if(question!=""){
				for(int k=0;k!=question.length()-1;++k)   
				{  
					//��һ����ÿ���ַ�������ʹ��deque��Ϊdeque������ɾ����ӵ��ٶ����
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
				//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3�� 
				allocate(coll1,coll2,coll3);
				//�����׺���ʽ  
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
//�ж��Ƿ��������
bool isOperator(string o)
{
	if(o=="+" || o=="-" || o=="*" || o=="/" || o=="(" || o==")")
		return true;
	return false;
}
//�ж��Ƿ����������������char��
bool isOperatorChar(char o)
{
	if(o=='+' || o=='-' || o=='*' || o=='/' || o=='(' || o==')')
		return true;
	return false;
}
//�ж��Ƿ�������
bool isPar(string par)   
{  
    if(par=="("||par==")")   
        return true;   
    else   
        return false;  
}  
  
//��÷��ŵ�������  
int getPar(string par)   
{  
    switch(par[0])   
    {  
    case '+':  
    case '-':  
        return 0;   //����ǼӼ�������0  
        break;  
    case '*':  
    case '/':  
        return 1;   //����ǳ˳�������1  
        break;  
    case '(':  
    case ')':  
        return -1;  //ע�⣬���ｫ������Ϊ������ȼ���������Ų��ᱻ��������������������  
        break;  
     }  
}  
  
//�жϷ��ŵ�������  
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
            //��������Ԫ��ֱ������������  
            while(coll2.top()!="(")   
            {    
                string ch = coll2.top();  
                coll3.push_back(ch);  
                coll2.pop();  
            }  
  
            //������������ʱ��������������coll3(��׺���ʽ�У�  
            coll2.pop();    
        }  
    }  
    else    //�����������  
    {  
        //ȡ��ջ��Ԫ�أ��뵱ǰ���Ž��������ԱȽ�  
        string sym = coll2.top();    
  
        //�Ƚ������ŵ�������  
        if(getPar(c)<=getPar(sym))    
        {  
            //���c�������Ա�ջ������С����ڣ�����ջ��Ԫ��  
            coll2.pop();  
            //������ѹ��coll3����׺���ʽ����  
            coll3.push_back(sym);  
            //�ݹ����check,�Ƚϵ�ǰ����c����һ��ջ�����ŵ�������  
            check(c,coll2,coll3);     
        }  
        else   
        {  
            //���c��ջ���������ȼ����ǽ�cѹ��coll2(������ջ����  
            coll2.push(c);    
        }  
    }  
}  
  
//��coll��ȡ��Ԫ�أ�����Ԫ�ص�coll2��coll3��  
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
            //����check��������Բ�ͬ���������ͬ����  
            check(c,coll2,coll3);    
        }  
  
    }  
  
    //��������������coll2��Ԫ��ȫ�������������׺���ʽ��  
    while(!coll2.empty())   
    {    
        string c = coll2.top();  
        coll3.push_back(c);  
        coll2.pop();  
    }  
}  
  
//�����׺���ʽ  
void calculate(deque<string>& coll3, stack<int>& coll4)   
{    
    while(!coll3.empty())   
    {  
        string c = coll3.front();  
        coll3.pop_front();  
          
        //����ǲ�������ѹ��ջ��  
        if(!isOperator(c))   
        {  
            //��ȥ'0'�ó�ƫ��ֵ����Ϊ��ʵ��ֵ�����ֱ��ת����int��������ԣ���Ϊchar ת��Ϊint�������ֵ������'1'�ı���ֵΪ49  
            int op =atoi(c.c_str());      
            coll4.push(op);       
        }  
        else     //����ǲ���������ջ�е���Ԫ�ؽ��м���  
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
                coll4.push(op2/op1);  //ע����op2(op)op1������op1(op)op2  
                break;  
            }  
        }  
    }  
	isOK=true;
}



//����������������ϳ���ʽ����Ԫ��ѹ��C
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

//�жϼӷ��ظ�
bool repeatAddCover(int Num[],int **addCover,int left)
{
	if(addCover[Num[left]][Num[left+1]]==1)
		return false;
	addCover[Num[left]][Num[left+1]]=1;
	addCover[Num[left+1]][Num[left]]=1;
	return true;
}

//�жϳ˷��ظ�
bool repeatMulCover(int Num[],int **mulCover,int left)
{
	if(mulCover[Num[left]][Num[left+1]]==1)
		return false;
	mulCover[Num[left]][Num[left+1]]=1;
	mulCover[Num[left+1]][Num[left]]=1;
	return true;
}

//��ȡִ���ļ�·��
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


//��ʼ������������
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
						cout<<"������-n��ֵ��";
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
						cout<<"������-r��ֵ��";
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
						cout<<"������-e��ֵ��";
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
						cout<<"������-a��ֵ��";
						return;
					}
				}
			}
		}
	}
};