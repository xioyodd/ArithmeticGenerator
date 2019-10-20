#ifndef TNODE_H
#define TNODE_H

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include<math.h>
using namespace std;

class TNode//节点类
{  public:
    char oper;
    TNode *left;
    TNode *right;
    int s; int t;
    TNode()
    {   left=right=NULL;
        oper=0;
    }
    TNode(char op)
    {   left=right=NULL;
        oper=op;}};
bool isOper(char op)//判断是否为运算符
{
    char oper[]={'(',')','+','-','*','/','^'};
    for(int i=0;i<sizeof(oper);i++)
    {  if(op==oper[i])
        {
            return true;
        } }
    return false;}

int getOperOrder(char op)//返回运算符op所对应的优先级
{  switch(op)
    {  case '(':
        return 1;
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
        return 4;
    default:
        //定义在栈中的右括号和栈底字符的优先级最低
        return 0;
    } }
void freeTree(TNode *&p) //释放树
{  if(p->left!=NULL)
        freeTree(p->left);
    if(p->right!=NULL)
        freeTree(p->right);
    delete(p);
    cout<<"Memory free "; }

void postOrder(TNode *p) //先序遍历
{  if(p)
    {  postOrder(p->left);
        postOrder(p->right);
        cout<<p->oper;
    } }

void preOrder(TNode *p) //后序遍历
{  if(p)
    {  cout<<p->oper;
        preOrder(p->left);
        preOrder(p->right);
    } }

void inOrder(TNode *p)//中序遍历
{  if(p)
    {  if(p->left)
        {  if(isOper(p->left->oper)
                    && getOperOrder(p->left->oper)
                    <getOperOrder(p->oper))
            {  cout<<"(";
                inOrder(p->left);
                cout<<")";
            }else{
                inOrder(p->left);
            }  }
        cout<<p->oper;
        if(p->right)
        {  if(isOper(p->right->oper)
                    && getOperOrder(p->right->oper)
                    <=getOperOrder(p->oper))
            {  cout<<"(";
                inOrder(p->right);
                cout<<")";
            }else{
                inOrder(p->right);
            }  }  }  }

void ExpTree1(TNode *&p,string str)//后缀表达式生成二叉树
{stack <TNode*> nodeStack;
    char temp;
    int i=0;
    temp=str[i++];
    while(temp!='\0')
    {  if(temp!='\0'&&!isOper(temp))//不是运算符，则进栈
        {  p=new TNode(temp);//以temp为结点值构造二叉树结点
            nodeStack.push(p);
            temp=str[i++];}
        else
        {   p=new TNode(temp);
            if(nodeStack.size())
            {  p->right=nodeStack.top();//若非空则弹栈并设为结点的右孩子
                nodeStack.pop();  }
            if(nodeStack.size())
            {  p->left=nodeStack.top();//若非空则弹栈并设为结点的左孩子
                nodeStack.pop();  }
            nodeStack.push(p);
            temp=str[i++];
        } } }
void ExpTree3(TNode *&p, string str)//前缀表达式生成二叉树
{ stack <TNode*> nodeStack;
    char temp;
    int i=str.size()-1;
    temp=str[i--];
    while(temp!='\0')
    {  if(temp!='\0'&&!isOper(temp))
        {  p=new TNode(temp);//以temp为内容来建立新的结点
            nodeStack.push(p);
            temp=str[i--];}
        else
        {  p=new TNode(temp);
            if(nodeStack.size())//若栈顶指针所指结点左孩子为空
            {   p->left=nodeStack.top(); //则当前结点设置成其左孩子
                nodeStack.pop();
            } if(nodeStack.size())//若栈顶指针所指结点右孩子为空
            {  p->right=nodeStack.top();//则当前结点设置成其右孩子
                nodeStack.pop();}//栈顶元素左右孩子指针设置完毕弹出
                nodeStack.push(p);
                temp=str[i--];
            } } }

    void ExpTree2(TNode *&p, string str)//中缀表达式转换成后缀表达式生成二叉树
    {  stack<char> a;
        char temp;
        string Postfixexp="";
        int i=0;
        temp=str[i++];
        while(temp!='\0')
        {  if(!isOper(temp))
            {  Postfixexp+=temp;
                temp=str[i++];}
            else if(temp=='(')//进栈
            {  a.push(temp);
                temp=str[i++];}
            else if(temp==')'){
                while(a.top()!='(')//脱括号
                {  Postfixexp+=a.top();
                    a.pop();}//在碰到开括号和栈为空前反复弹出栈中元素
                    a.pop();
                    temp=str[i++];
                }else if(temp=='+'||temp=='-'||temp=='*'||temp=='/'){//出栈
                    while(!a.empty()&&a.top()!='('&&getOperOrder(a.top())>=getOperOrder(temp))//若栈非空栈顶不是左括号且栈顶元素优先级不低于输入运算符时，
                        //将栈顶元素弹出到后缀表达式中，并且str下标加1
                    {  Postfixexp+=a.top();
                        a.pop();  }
                a.push(temp);
                temp=str[i++];
            } }
        while(!a.empty())
        {  Postfixexp+=a.top();
            a.pop();
        }
        ExpTree1(p,Postfixexp); }
    void count(TNode *p,int &height,int n)//求值函数
    {  if(p->left==NULL&&p->right==NULL)
        {  if(n>height)
                height=n;}
        if(p->left!=NULL)
            count(p->left,height,n+1);
        if(p->right!=NULL)
            count(p->right,height,n+1); }
    void paint(TNode *p)//输出函数
    {  int height=0;
        int h=0;
        int i;
        using std::queue;
        queue<TNode*> aQueue;
        count(p,height,1);
        TNode *pointer=p;
        TNode *lastpointer;
        if(pointer)
        { pointer->s=1;
            pointer->t=1;
            aQueue.push(pointer);  }
        while(!aQueue.empty())
        {  lastpointer=pointer;
            pointer=aQueue.front();
            aQueue.pop();
            if(pointer->s>h)
            {cout<<endl;
                h=pointer->s;}
            if(pointer->t==1)
            {for(i=0;i<pow(2,height-pointer->s)-1;i++)
                    cout<<" ";}
            else if(lastpointer->s!=pointer->s){
                for(i=0;i<(pointer->t-1)*(pow(2,height-pointer->s+1)-1)+(pointer->t-1)-1+pow(2,height-pointer->s);i++)
                    cout<<" ";  }
            else
            { for(i=0;i<(pointer->t-lastpointer->t)*(pow(2,height-pointer->s+1)-1)+(pointer->t-lastpointer->t)-1;i++)
                    cout<<" ";  }
            cout<<pointer->oper;
            if(pointer->left!=NULL){
                pointer->left->s=pointer->s+1;
                pointer->left->t=pointer->t*2-1;
                aQueue.push(pointer->left);}
            if(pointer->right!=NULL){
                pointer->right->s=pointer->s+1;
                pointer->right->t=pointer->t*2;
                aQueue.push(pointer->right);
            }  }  }

#endif // TNODE_H
