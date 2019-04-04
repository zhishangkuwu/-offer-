#include<iostream>
#include<vector>
#include<stack>
#include<queue>

using namespace std;

struct ListNode{
    int val;
    struct ListNode * next;
    ListNode(int x):val(x),next(NULL){}

};

struct TreeNode{
    int val;
    struct TreeNode * left;
    struct TreeNode * right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};

class Solution{
public:
    /*在一个二维数组中（每个一维数组的长度相同），
    每一行都按照从左到右递增的顺序排序，
    每一列都按照从上到下递增的顺序排序。
    请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。*/
    bool p1(vector<vector<int>> array,int target){
        int len1 = array.size();
        int len2 = array[0].size();
        int startx = len1-1;
        int starty = 0;
        while(startx>=0&&starty<len2){
            if(array[startx][starty]>target)
                startx--;
            if(array[startx][starty]<target)
                starty++;
            if(array[startx][starty]==target)
                return true;
        }
        return false;

    }
    /*请实现一个函数，将一个字符串中的每个空格替换成“%20”。
    例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。*/
public:
    void replaceSpace(char *str,int length){
        if(str==NULL||length<0)
            return;
        int ori_len,blank_len=0;
        for(ori_len=0;str[ori_len]!='\0';ori_len++){
            if(str[ori_len]==' '){
                blank_len++;
            }
        }
        int new_len = ori_len + blank_len*2;
        //cout<<"ori_len"<<ori_len<<endl;
        //cout<<"blank_len"<<blank_len<<endl;
        //cout<<"new_len"<<new_len<<endl;
        if(new_len>length)
            return;
        str[new_len] = '\0';
        int old = ori_len-1,neww = new_len-1;
        while(old>=0&&neww>old){
            if(str[old]==' '){
                old--;
                str[neww--] = '0';
                str[neww--] = '2';
                str[neww--] = '#';
            }
            else{
                str[neww--] = str[old--];
            }          
        }
    }
public:
    //输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。
    vector<int> printListFromTailToHead(ListNode* head){
        vector<int> res;
        stack<int> tem;
        ListNode* sh = head;
        while(sh){
            tem.push(sh->val);
            sh = sh->next;
        }
        while(!tem.empty()){
            res.push_back(tem.top());
            tem.pop();
        }
        return res;
    }
public:
    /*输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
    假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
    例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列
    {4,7,2,1,5,3,8,6}，则重建二叉树并返回*/
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        
        int n1 = pre.size();
        int n2 = vin.size();
        return func(pre,0,n1-1,vin,0,n2-1);

    }
    TreeNode* func(vector<int> pre,int pstart,int pend,vector<int> vin,int vstart,int vend){
        int i;
        if(pstart>pend||vstart>vend)
            return NULL;
        //cout<<1<<endl;
        TreeNode* node = new TreeNode(pre[pstart]);
        i=vstart;
        //cout<<"vstart"<<vstart<<endl;
        //cout<<3<<endl;
        while(i<=vend){
            if(vin[i] == pre[pstart]){
                break;
            }
            i++;
        }
        //cout<<"the pos is "<<i<<endl;
        node->left = func(pre,pstart+1,pstart+i,vin,vstart,i-1);
        node->right = func(pre,pstart+i+1,pend,vin,i+1,vend);
        return node;
        
    }
    void tree_bianli1(TreeNode* node){
        if(node == NULL)
            return;
        cout<<node->val;
        tree_bianli1(node->left);
        tree_bianli1(node->right);
    }
    void tree_bianli2(TreeNode* node){
        if(node == NULL)
            return;
        tree_bianli2(node->left);
        cout<<node->val;
        tree_bianli2(node->right);
    }
public:
    TreeNode* reConstructBinaryTree2(vector<int> pre,vector<int> vin){
        int n = pre.size();
        if(n==0)
            return NULL;
        TreeNode* head = new TreeNode(pre[0]);
        int gen;
        vector<int> pre1,pre2,vin1,vin2;
        for(int i=0;i<n;i++){
            if(vin[i]==pre[0]){
                gen = i;
                break;
            }
        }
        for(int j = 0;j<gen;j++){
            vin1.push_back(vin[j]);
            pre1.push_back(pre[j+1]);
        }
        for(int k = gen+1;k<n;k++){
            vin2.push_back(vin[k]);
            pre2.push_back(pre[k]);
        }
        head->left = reConstructBinaryTree2(pre1,vin1);
        head->right = reConstructBinaryTree2(pre2,vin2);
        return head;
    }

public:
    /*用两个栈实现队列*/
    void push(int node){
        stack1.push(node);
    }
    int pop(){
        if(stack2.empty()){
            while(!stack1.empty()){
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int res = stack2.top();
        stack2.pop();
        return res;
    }
private:
    stack<int> stack1;
    stack<int> stack2;

public:
    /*把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。 
    输入一个非减排序的数组的一个旋转，输出旋转数组的最小元素。 
    例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。 N
    OTE：给出的所有元素都大于0，若数组大小为0，请返回0*/
    int minNumberInRotateArray(vector<int> rotateArray) {
        int n = rotateArray.size();
        if(n==0)
            return 0;
        int start = 0,end = n-1;
        int mid = (end-start)/2  +start;
        while((start+1)<end){
            if(rotateArray[start]<rotateArray[end])
                return rotateArray[start];
            if(rotateArray[mid]>rotateArray[end]){
                start = mid;
                mid = (end-start)/2  + start;
            }
            else{
                end = mid;
                mid = (end-start)/2  + start;
            }
        }
        return min(rotateArray[start],rotateArray[end]);
    }

public:
    /*大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0）*/
    int Fibonacci(int n) {
        if(n==0)
            return 0;
        if(n==1)
            return 1;
        int i=0,j=1;
        for(int k=0;k<n-1;k++){
            j = i + j;
            i = j - i;
        }
        return j;
    }
public:
    /*一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法*/
    int jumpFloor(int number){
        if(number==1)
            return 1;
        if(number==2)
            return 2;
        return jumpFloor(number-1)+jumpFloor(number-2);
    }
public:
    /*一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。*/
    int jumpFloorII(int number) {
        if(number==1)
            return 1;
        return 2*jumpFloorII(number-1);
    }
public:
    /*我们可以用2*1的小矩形横着或者竖着去覆盖更大的矩形。
    请问用n个2*1的小矩形无重叠地覆盖一个2*n的大矩形，总共有多少种方法？*/
    int rectCover(int number) {
        if(number == 1)
            return 1;
        if(number == 2)
            return 2;
        return rectCover(number-1)+rectCover(number-2);
    }

public:
    /*输入一个整数，输出该数二进制表示中1的个数。其中负数用补码表示。*/
    int  NumberOf1(int n) {
        if(n==0)
            return 0;
        int count = 0;
        int len = sizeof(int)*8;
        for(int i=0;i<len;i++){
            if(n>>i&1)
                count++;
        }
         return count;
     }
public:
    /*给定一个double类型的浮点数base和int类型的整数exponent。求base的exponent次方。*/
    double Power(double base, int exponent) {
        if(exponent==0)
            return 1;
        else if(exponent>0){
            int s=1;
            for(int i=0;i<exponent;i++){
                s = s*base;
            }
            return s;
        }
        else{
            int s=1;
            for(int i=0;i<-exponent;i++){
                s = s*base;
            }
            return 1.0/s;
        }
    }

public:
    /*输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
    使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分，
    并保证奇数和奇数，偶数和偶数之间的相对位置不变。*/
    void reOrderArray(vector<int> &array){
        if(array.size()==1)
            return;
        vector<int> tem;
        int blank = 0;
        for(int i=0;i<array.size();i++){
            if(array[i] % 2 == 0){
                tem.push_back(array[i]);
                blank++;
            }
            else
            {
                array[i-blank] = array[i]; 
            }
        }
        if(tem.size()==0)
            return;
        for(int j=0;j<tem.size();j++){
            array[array.size()-1-j] = tem[tem.size()-1-j];
        }

        
    }

public:
    /*输入一个链表，输出该链表中倒数第k个结点。*/
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        ListNode* one;
        ListNode* two;
        one = pListHead;
        two = pListHead;
        if(pListHead==NULL || k==0)
            return NULL;

        for(int i=1;i<k;i++){
            if(two->next != NULL)
                two = two->next;
            else{
                return NULL;
            }
        }
        cout<<"one: "<<one->val<<endl;
        cout<<"two: "<<two->val<<endl;;
        while(two->next!=NULL){
            one = one->next;
            two = two->next;
        }
        cout<<"one: "<<one->val<<endl;
        cout<<"two: "<<two->val<<endl;
        return one;
    }

public:
    /*输入一个链表，反转链表后，输出新链表的表头*/
    ListNode* ReverseList(ListNode* pHead) {
        //头插法插入，同时tem暂存下一个结点
        ListNode* head = new ListNode(0);
        head->next = pHead;
        ListNode* tem = pHead->next;
        pHead->next = NULL;
        ListNode* temm;
        while(tem != NULL){
            temm = tem->next;
            tem->next = head->next;
            head->next = tem;
            tem = temm;
        }
        
        return head->next;        
    }
public:
    /*输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。*/
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        ListNode* newList = new ListNode(0);
        ListNode* head = newList;
        ListNode* p1 = pHead1;
        ListNode* p2 = pHead2;
        while(p1!=NULL&&p2!=NULL){
            if(p1->val<=p2->val){
                newList->next = p1;
                newList = newList->next;
                p1 = p1->next;
            }
            else
            {
                newList->next = p2;
                newList = newList->next;
                p2 = p2->next;
            } 
        }
        if(p1!=NULL){
            newList->next = p1;
        }
        if(p2!=NULL){
            newList->next = p2;
        }
        return head->next;
    }
public:
    /*输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）*/
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2){
        if(pRoot1==NULL||pRoot2==NULL)
            return false;
        bool flag = false;
        if(pRoot1->val == pRoot2->val){
            flag = find_truth(pRoot1,pRoot2);
        }
        if(!flag)
            flag = HasSubtree(pRoot1->left,pRoot2);
        if(!flag)
            flag = HasSubtree(pRoot2->right,pRoot2);
        return flag;
    }
public:
    bool find_truth(TreeNode* t1,TreeNode* t2){
        if(t2==NULL)
            return true;
        if(t1==NULL)
            return false;
        bool flag = true;
        if(t1->val!=t2->val)
            flag =  false;
        
        if(flag)
            flag = find_truth(t1->left,t2->left);
        if(flag)
            flag = find_truth(t1->right,t2->right);
        return flag;
    }

public:
    //操作给定的二叉树，将其变换为源二叉树的镜像。
    void Mirror(TreeNode *pRoot) {
        if(pRoot->left==NULL&&pRoot->right==NULL)
            return;
        TreeNode* tem;
        tem = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tem;
        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }

public:
    //输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，
    //例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 
    //则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> res;
        int len1 = matrix.size();
        int len2 = matrix[0].size();
        int circles = (min(len1,len2)+1)/2;
        for(int i=0;i<circles;i++){
            for(int i1=i;i1<(len2-i);i1++){
                res.push_back(matrix[i][i1]);
            }
            for(int i2=i+1;i2<len1-i;i2++){
                res.push_back(matrix[i2][len2-i-1]);
            }
            for(int i3=len2-i-2;i3>=i;i3--){
                res.push_back(matrix[len1-i-1][i3]);
            }
            for(int i4=len1-i-2;i4>=i;i4--){
                res.push_back(matrix[i4][i]);
            }
        }
        return res;
    }

public:
    /*输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。
    假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是
    该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。
    （注意：这两个序列的长度是相等的）*/
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        stack<int> tem;
        int size1 = pushV.size();
        int size2 = popV.size();
        for(int i=0,j=0;i<size1;i++){
            tem.push(pushV[i]);
            while(j<size2&&tem.top()==popV[j]){
                tem.pop();
                j = j + 1;
            }
        }
        return tem.empty();

    }

public:
    //从上往下打印出二叉树的每个节点，同层节点从左至右打印。
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        
        vector<int> v;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            TreeNode* front = q.front();
            q.pop();
            v.push_back(front->val);
            if(front->left!=NULL)
                q.push(front->left);
            if(front->right!=NULL)
                q.push(front->right);
        }
        return v;
    }
public:
    //输入一个整数数组，判断该数组是
    //不是某二叉搜索树的后序遍历的结果。如果是则输出Yes,否则输出No。
    //假设输入的数组的任意两个数字都互不相同。
    bool VerifySquenceOfBST(vector<int> sequence) {
        return true;
    }
};

//定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的min函数（时间复杂度应为O（1））。
class Solution2{
public:
    void push(int value) {
        StackInt.push(value);
        if(StackMin.empty()){
            StackMin.push(value);
        }
        else
        {
            if(value<StackMin.top()){
                StackMin.push(value);
            }
        }
        
    }
    void pop() {
        if(StackInt.top()==StackMin.top()){
            StackInt.pop();
            StackMin.pop();
        }
        else
        {
            StackInt.pop();
        }
        
    }
    int top() {
        return StackInt.top();
    }
    int min() {
        return StackMin.top();
    }
private:
    stack<int> StackInt;
    stack<int> StackMin;
};




int main(){
    Solution s;
    TreeNode* root = new TreeNode(0);
    root->left = new TreeNode(1);
    root->right = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->left->left = new TreeNode(3);
    root->right->left = new TreeNode(5);
    root->right->right = new TreeNode(6);
    vector<int> v;
    v = s.PrintFromTopToBottom(root);
    for(auto res:v){
        cout<<res<<endl;
    }
}