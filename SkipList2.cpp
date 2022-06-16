#include <bits/stdc++.h>
using namespace std;
class Node
{
public:
    int key;
    Node **forward;
    Node(int, int);
};

Node::Node(int key, int level)
{
    this->key = key;
    forward = new Node*[level+1];
    memset(forward, 0, sizeof(Node*)*(level+1));
};

// Class for Skip list
class SkipList
{
    // Maximum level
    int MAXLVL = MAXLVL;
    // P is the fraction of the nodes
    // i pointers also having level i+1 pointers
    float P = P;
    // current level
    int level;
    // pointer to header node
    Node *header;
public:
    SkipList(int, float);
    int randomLevel();
    Node* createNode(int, int);
    void insertElement(long int);
    void deleteElement(long int);
    bool searchElement(long int);
    void displayList();
};

SkipList::SkipList(int MAXLVL, float P)
{
    this->MAXLVL = MAXLVL;
    this->P = P;
    level = 0;
    // create header node and initialize key = -1
    header = new Node(-1, MAXLVL);
};

// create random level
int SkipList::randomLevel()
{
    float r = (float)rand()/RAND_MAX;
    int lvl = 0;
    while(r < P && lvl < MAXLVL)
    {
        lvl++;
        r = (float)rand()/RAND_MAX;
    }
    return lvl;
};

// new node
Node* SkipList::createNode(int key, int level)
{
    Node *n = new Node(key, level);
    return n;
};

// Insert
void SkipList::insertElement(long int key)
{
    Node *current = header;
    // update array
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }

    current = current->forward[0];
        // Generate a random level
        int randlevel = randomLevel();
        if(randlevel > level)
        {
            for(int i=level+1;i<randlevel+1;i++)
                update[i] = header;
            // Update current level
            level = randlevel;
        }
        // create new node
        Node* n = createNode(key, randlevel);

        // insert node by rearranging pointers
        for(int i=0;i<=randlevel;i++)
        {
            n->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = n;
        }
};

// Delete element
void SkipList::deleteElement(long int key)
{
        Node *current = header;
    Node *update[MAXLVL+1];
    memset(update, 0, sizeof(Node*)*(MAXLVL+1));
    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] != NULL  &&
              current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    current = current->forward[0];
    if(current != NULL and current->key == key)
    {

        for(int i=0;i<=level;i++)
        {
            if(update[i]->forward[i] != current)
                break;

            update[i]->forward[i] = current->forward[i];
        }

        while(level>0 && header->forward[level] == 0)
            level--;
    }
     if(searchElement(key)){
            deleteElement(key);
        }

};
// Search for element
bool SkipList::searchElement(long int key)
{
    Node *current = header;

    for(int i = level; i >= 0; i--)
    {
        while(current->forward[i] &&
               current->forward[i]->key < key)
            current = current->forward[i];

    }
    current = current->forward[0];
    if(current and current->key == key)
        return true;
        return false;
};

// Display skip list
void SkipList::displayList()
{
 Node *x = header->forward[0];
 if (x== NULL){
        cout<<"empty";
    }
    else{ while (x != NULL)
    {
        cout << x->key;
        x = x->forward[0];
        if (x != NULL)
            cout << "  ";
    }}
    cout <<endl;
}
  int main()
{
    string s , number="";
    SkipList sl(10,0.25);
    srand((unsigned)time(0));
    long int x=0;
    while(cin>>s){
    if (s=="Insert") {
            cin>>number;
          stringstream stringint(number);
            stringint >> x;
           sl.insertElement(x);
}
if (s=="Delete"){
    cin>>number;
    stringstream si2(number);
    si2 >> x;
    if(sl.searchElement(x)){
        sl.deleteElement(x);
    }
    else cout<<"error"<<endl;
}
if (s=="Search"){
    cin>>number;
    stringstream si3(number);
    si3 >> x;
   if(sl.searchElement(x)){
    cout<<"true"<<endl;
   }
  else cout<<"false"<<endl;
}
if (s=="Print"){
    sl.displayList();
}
}
}
