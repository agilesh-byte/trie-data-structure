#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <stdio.h>
#define charsize 26
#define ll long long
using namespace std;
string word;
struct Trie
{
    bool isLeafNode;
    struct Trie  *character[charsize];
};

struct Trie *getNode(void)
{
  struct Trie *newNode =  new Trie;
  newNode->isLeafNode = false;
  for (int i = 0; i < charsize; i++)
  {
        newNode->character[i] = NULL;
  }
    return newNode;
}

void display(vector<string> v)
{
    cout<<"Elements in the file are : "<<endl;
    for (auto i = v.begin(); i != v.end(); i++)
    {
        cout << *i <<endl;
    }
}
void InsertTrie(struct Trie *root,string &current){
    struct Trie *traverse=root;
    for(auto x1:current){
        ll position;
        position=x1-'a';
        if(traverse->character[position]==NULL){
            traverse->character[position]=getNode();
        }
        traverse=traverse->character[position];
    }
    traverse->isLeafNode=true;
}
int Searchword(struct Trie *root,string &current){
    struct Trie *traverse=root;
    for(auto x:current){
        ll position;
        position=x-'a';
        if(traverse->character[position]==NULL){
            return 0;
        }
        traverse=traverse->character[position];
    }
    if(traverse!=NULL && traverse->isLeafNode)
    return 1;
    return 0;
}
ll emptynode(struct Trie *root){
for(ll i=0;i<26;++i){
    if(root->character[i])
        return 0;
}
    return 1;
}
Trie* removenode(struct Trie *root,string current,ll level){
    if(root==NULL){
        return NULL;
    }

    if(level==current.size()){
        if(root->isLeafNode)
            root->isLeafNode=false;
        if(emptynode(root)){
            delete (root);
        root=NULL;}
        return root;
    }
    ll pos=current[level]-'a';
    root->character[level]=removenode(root->character[pos],current,level+1);
    if(emptynode(root) && root->isLeafNode==false){
        delete (root);
        root=NULL;
    }
    return root;
}
void recommendstrings(struct Trie *root,string prefix){
    if(root->isLeafNode){
        cout<<prefix<<"\n";
    }
    if(emptynode(root))
        return ;
    for(ll i=0;i<26;++i){
        if(root->character[i]){
            prefix.push_back(97+i);
            recommendstrings(root->character[i],prefix);
            prefix.pop_back();
        }
    }
}
ll autocomplete(struct Trie *root,string prefix){
    struct Trie *current=root;
    for(ll i=0;i<prefix.size();++i){
        ll pos=prefix[i]-'a';
        if(current->character[pos]==NULL)
            return 0;
        current=current->character[pos];
    }
    if(current->isLeafNode && emptynode(current)){
        cout<<prefix<<endl;
        return -1;
    }
    if(emptynode(current)==0){
        recommendstrings(current,prefix);
        }
}
vector<string> removeword(vector<string> v, string word,string filename)
{
    for (auto i = v.begin(); i != v.end(); i++)
    {
        if(*i==word)
        {
            v.erase(i);
        }
    }
    ofstream file(filename);
    ostream_iterator<string> output_iterator(file, "\n");
    copy(v.begin(), v.end(), output_iterator);
    cout<<"Element deleted successfully..!!"<<endl;
    return v;
}
vector<string> insert(vector<string> v,string filename)
{
    cout<<"Enter the word to insert into the file :"<<endl;
    cin>>word;
    v.push_back(word);
    ofstream file(filename);
    ostream_iterator<string> output_iterator(file, "\n");
    copy(v.begin(), v.end(), output_iterator);
    cout<<"Element inserted successfully..!!"<<endl;
    return v;
}
void WordBreak(struct Trie *root,string subresult,string main){
    if(main.size()==0){
        cout<<subresult<<endl;
    }

    for(ll i=1;i<=main.size();++i){
            string sub=main.substr(0,i);
        if(Searchword(root,sub)){
            WordBreak(root,subresult+" "+sub,main.substr(i));
        }
    }
}
int main()
{
    int exit=0;
    string filename;
    cout<<"Enter the File Name : ";
    cout<<endl;
    cin>>filename;
    ifstream file(filename);
    if(file.is_open())
    {
        vector<string> v;
        string str;
        while(file >> str)
        {
            v.push_back(str);
        }
        struct Trie *root= getNode();
        for(auto x:v){
            InsertTrie(root,x);
        }
        do
        {
            cout<<"Enter the operation to perform :"<<endl<<endl;
            cout<<"1-> Display the words"<<endl<<"2-> Insert a new word in the file"<<endl<<"3-> Delete a word in a file"<<endl<<"4-> Search a word in a file"<<endl;
            cout<<"5-> Break the sentence into given words"<<endl<<"6-> Auto Suggest Words in a file\n Enter the Value : ";
            int choice;
            cin>>choice;
            switch(choice)
            {
                case 1:
                    display(v);
                    break;
                case 2:
                    v=insert(v,filename);
                    InsertTrie(root,word);
                    break;
                case 3:
                    cout<<"Enter the word to be deleted in a file : \n";
                    cin>>word;
                    if(Searchword(root,word)){
                        removenode(root,word,0);
                        v=removeword(v,word,filename);
                    }
                    else{
                        cout<<"The given word does not exist already!\n";
                    }
                    break;
                case 4:
                    cout<<"Enter the word to be searched in a file : ";
                    cout<<endl;
                    cin>>word;
                    if(Searchword(root,word)){
                        cout<<"Word exists in the file!";
                    }
                    else{
                        cout<<"Word doesn't exist in the file!";
                    }
                    break;
                case 5:
                    cout<<"Enter the joint sentence: \n";
                    cin>>word;
                    WordBreak(root,"",word);
                    break;
                case 6:
                    cout<<"Type Your prefix query: \n";
                    cin>>word;
                    autocomplete(root,word);
                    break;
            }
            cout<<"Press '1' to continue :"<<endl;
            cin>>exit;
        }while(exit==1);
    }
    else
    {
        cout<<"File not Found..!!";
    }
    return 0;
}
