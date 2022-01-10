#include <iostream>
using namespace std;

struct UserNames {
    int size = 100;
    string* user = new string[size];
    int ind = 0;
    bool accept(string y)
    {
        if (ind == 0)
        {
            user[ind] = y;
            ++ind;
        }
        else
        {
            for (int i = 0; i < ind; ++i)
            {
                if (user[i] == y)
                {
                    return false;
                }
            }
            if (ind == size)
            {
                newarray(size);
                user[ind] = y;
                ++ind;
            }
        }
        return true;
    }
    void newarray(int& s)
    {
        string* newuser = new string[s];
        for (int i = 0; i < s; ++i)
        {
            newuser[i] = user[i];
        }
        delete user;
        s *= 2;
        user = new string[s];
        for (int i = 0; i < s / 2; ++i)
        {
            user[i] = newuser[i];
        }
        delete newuser;
    }

}x;

class User{
public:
    class Treap {
    public:
        class TreapNode {

        public:
            TreapNode* leftChild;
            TreapNode* rightChild;
            TreapNode* parent;
            User* u = new User() ;
            int priority;
            //template <class Q>
            TreapNode(User tempKey, int tempPriority)
            {
                this->priority = tempPriority;
                *u = tempKey;
                this->leftChild = NULL;
                this->rightChild = NULL;
                this->parent = NULL;
            }
        };
    private:
        TreapNode* root;
        bool usedPriority[RAND_MAX];

    public:
        Treap()
        {
            //memset(usedPriority, false, sizeof(usedPriority));
            this->root = NULL;
        }
        int SetNodePriority()
        {
            int val;
            while (usedPriority[val = rand()]);
            usedPriority[val] = true;
            return val;
        }
        void LeftRotate(TreapNode* tempTPNode)
        {
            TreapNode* rChild = tempTPNode->rightChild;
            if (NULL == rChild)return;
            if (NULL != tempTPNode->parent)//Not the root node
            {
                if (tempTPNode->parent->leftChild == tempTPNode) {
                    tempTPNode->parent->leftChild = rChild;
                }
                else {
                    tempTPNode->parent->rightChild = rChild;
                }
            }
            rChild->parent = tempTPNode->parent;
            tempTPNode->parent = rChild;
            if (rChild->leftChild != NULL) {
                rChild->leftChild->parent = tempTPNode;
            }
            tempTPNode->rightChild = rChild->leftChild;
            rChild->leftChild = tempTPNode;
            if (NULL == rChild->parent) {
                this->root = rChild;
            }
        }
        void RightRotate(TreapNode* tempTPNode)
        {
            TreapNode* lChild = tempTPNode->leftChild;
            if (NULL == lChild)return;
            if (NULL != tempTPNode->parent)//Not the root node
            {
                if (tempTPNode->parent->rightChild == tempTPNode) {
                    tempTPNode->parent->rightChild = lChild;
                }
                else {
                    tempTPNode->parent->leftChild = lChild;
                }
            }
            lChild->parent = tempTPNode->parent;
            tempTPNode->parent = lChild;
            if (lChild->rightChild != NULL) {
                lChild->rightChild->parent = tempTPNode;
            }
            tempTPNode->leftChild = lChild->rightChild;
            lChild->rightChild = tempTPNode;
            if (NULL == lChild->parent) {
                this->root = lChild;
            }
        }
        void ModifyTreap(TreapNode* tempTPNode)
        {
            TreapNode* parTempTPNode = tempTPNode->parent;
            while (parTempTPNode != NULL && parTempTPNode->priority > tempTPNode->priority)//priority of parent is greater than child's priority
            {
                if (tempTPNode == parTempTPNode->leftChild) {
                    RightRotate(parTempTPNode);
                }
                else {
                    LeftRotate(parTempTPNode);
                }
                parTempTPNode = tempTPNode->parent;
            }
        }
        void InsertTreap(User& input)
        {
            TreapNode* pre = NULL, * cur = this->root;
            while (cur != NULL) {

                pre = cur;
                if (cur->u->getusername() > input.getusername()) {         //tempKey inserted into the left subtree
                    cur = cur->leftChild;
                }
                else {
                    cur = cur->rightChild;          //Insert to the left subtree
                }
            }
            TreapNode* tempTPNode = new TreapNode(input, SetNodePriority());
            tempTPNode->parent = pre;
            if (pre == NULL) {                   //If the root node is inserted
                this->root = tempTPNode;
            }
            else if (pre->u->getusername() > tempTPNode->u->getusername()) {
                pre->leftChild = tempTPNode;
            }
            else {
                pre->rightChild = tempTPNode;
            }
            ModifyTreap(tempTPNode);  //Adjustment
        }
        string FindTreap(string tempKey)
        {
            TreapNode* cur = this->root;
            while (cur != NULL)
            {
                if (cur->u->getusername() == tempKey) {
                    break;
                }
                else if (cur->u->getusername() > tempKey) {
                    cur = cur->leftChild;
                }
                else {
                    cur = cur->rightChild;
                }
            }

            if(cur == NULL){
                return "Not Found" ;
            }
            return cur->u->getname() ;
        }
        void DeleteNoOrOneChildTPNode(TreapNode* pre, TreapNode* cur)
        {
            if (NULL == cur->leftChild && NULL == cur->rightChild)//Left and right children are empty
            {
                if (NULL == pre) {
                    this->root = NULL;
                }
                else if (pre->leftChild == cur) {
                    pre->leftChild = NULL;
                }
                else {
                    pre->rightChild = NULL;
                }
                delete cur;
            }
            else if (cur->rightChild != NULL)//If the right subtree is not empty
            {
                if (NULL == pre)
                {
                    this->root = cur->rightChild;
                    cur->rightChild->parent = NULL;
                }
                else if (pre->leftChild == cur)
                {
                    pre->leftChild = cur->rightChild;
                    cur->rightChild->parent = pre;
                }
                else
                {
                    pre->rightChild = cur->rightChild;
                    cur->rightChild->parent = pre;
                }
                delete cur;
            }
            else if (cur->leftChild != NULL)//If the left subtree is not empty
            {
                if (NULL == pre)
                {
                    this->root = cur->leftChild;
                    cur->leftChild->parent = NULL;
                }
                else if (pre->leftChild == cur)
                {
                    pre->leftChild = cur->leftChild;
                    cur->leftChild->parent = pre;
                }
                else
                {
                    pre->rightChild = cur->leftChild;
                    cur->leftChild->parent = pre;
                }
                delete cur;
            }
        }
        bool DeleteTreap(string tempKey)
        {
            TreapNode* pre = NULL, * cur = root;
            while (cur != NULL)//Find the element to be deleted
            {
                if (cur->u->getusername() == tempKey) {
                    break;
                }
                else {

                    pre = cur;
                    if (cur->u->getusername() > tempKey) {
                        cur = cur->leftChild;
                    }
                    else {
                        cur = cur->rightChild;
                    }
                }
            }
            if (NULL == cur)return false;
            if (NULL == cur->leftChild || NULL == cur->rightChild) {
                DeleteNoOrOneChildTPNode(pre, cur);
            }
            else //The left and right subtrees are not empty
            {
                TreapNode* rPre = cur, * rCur = cur->rightChild;//Find the smallest element of the right subtree
                bool isLeft;
                while (rCur->leftChild != NULL)
                {
                    rPre = rCur;
                    rCur = rCur->leftChild;
                }
                cur->u->getusername() = rCur->u->getusername();//Fill the element directly without copying the priority
                if (rPre->leftChild == rCur) {
                    isLeft = true;
                }
                else {
                    isLeft = false;
                }

                DeleteNoOrOneChildTPNode(rPre, rCur);

                if (isLeft) {
                    ModifyTreap(rPre->leftChild);
                }
                else {
                    ModifyTreap(rPre->rightChild);
                }
            }
            return true;
        }
        bool UpdateTreap(string oldKey, User newKey)
        {
            if (DeleteTreap(oldKey))
            {
                InsertTreap(newKey);
                return true;
            }
            return false;
        }
        void InOrderTPPrint(TreapNode* tempTPNode)
        {
            if (NULL == tempTPNode)
                return;
            InOrderTPPrint(tempTPNode->leftChild);
            cout  << tempTPNode->u->getusername() << " , " <<tempTPNode->u->getname() << endl;
            InOrderTPPrint(tempTPNode->rightChild);
        }
        void InOrderTPPrint()
        {
            InOrderTPPrint(this->root);
        }
        void RotateTPPrint(TreapNode* tempTPNode, int tempColumn) {

            if (NULL == tempTPNode) {
                return;
            }
            RotateTPPrint(tempTPNode->leftChild, tempColumn + 1);
            for (int i = 0;i < tempColumn;i++) {
                cout << "    ";
            }
            cout << "(" << tempTPNode->u->getusername() << "," << tempTPNode->priority << ")" << endl;
            RotateTPPrint(tempTPNode->rightChild, tempColumn + 1);
        }
        void RotateTPPrint() {

            RotateTPPrint(this->root, 0);
        }
    };


private:

    string name;
    string username;
    string email;
    static int orderOfCreate;
    Treap friends;

public:

    User()
    {
        name = "";
        username = "";
        email = "";
    }
    User(string n, string u, string mail)
    {
        name = n;
        email = mail;
        if (!x.accept(u))
        {
            string y;
            while (true) {
                cout << "Enter Another User Name" << endl;
                cin >> y;
                if (x.accept(y))
                {
                    username = y;
                    orderOfCreate++;
                    break;
                }
            }
        }
        else
        {
            username = u;
            orderOfCreate++;
        }

    }

    User(User& u) {
        name = u.name;
        username = u.username;
        email = u.email;
        orderOfCreate = u.orderOfCreate;
    }

    void setname(string z)
    {
        name = z;
    }
    void setemail(string z)
    {
        email = z;
    }
    void setusername(string z)
    {
        if (!x.accept(z))
        {
            string y;
            while (true) {
                cout << "Enter Another User Name" << endl;
                cin >> y;
                if (x.accept(y))
                {
                    username = y;
                    break;
                }
            }
        }
        else
        {
            username = z;
        }
        username = z;
    }

    int getOrder() {
        return orderOfCreate;
    }
    string getname()
    {
        return this->name;
    }
    string getusername()
    {
        return this->username;
    }
    string getemail()
    {
        return email;
    }
    void displayfriends()
    {
        friends.InOrderTPPrint();
    }
    string searchfriend(string nam)
    {
        return friends.FindTreap(nam) ;
    }

    string getAllData() {
        return "Name: "+name + " userName: "+username+" Email: "+email;
    }
    void addfriend(User& z)
    {
        friends.InsertTreap(z);
        z.friends.InsertTreap(*this);
    }
    void removefriend(User& z)
    {
        string s=z.getusername();
        friends.DeleteTreap(s);
        z.friends.DeleteTreap(this->username);
    }
};
int User::orderOfCreate = 0;
