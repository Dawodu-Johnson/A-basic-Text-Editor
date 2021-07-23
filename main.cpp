//------------------About the project------------------------
/*This is a very basic(meaning so many features can still be added if time permits)text editor
 It consist of a structure called document which holds a list containing vectors of characters
 (basically everything in the input file), it stores it in the list line by line.
 We wanted to be able to iterate, which birth forth the functions begin() and end() in the document structure.
 but it has to have a type such that upon dereferencing gives a single character and ++ gives the next character.
 that's why the textIterator was created, we basically defined two iterators in it
 The class stores the iterators to the list<vector<char> and vector<char> in  document to keep track of it.
 necessary operations were defined e.g ++,* to aid the necessary abstraction.
 doing that a simple for loop over a document type will be possible, printing individual characters
 i.e for(const auto&s: documentobject){cout << s;}
 */

#include <bits/stdc++.h>
using namespace std;

class TextIterator{
private:

   vector<char>::iterator chs;
   list<vector<char> >::iterator lchs;


public:

    TextIterator(list<vector<char> >::iterator ll, vector<char>::iterator ls)
                                                          :chs(ls),lchs(ll){}
   char& operator *(){ return *chs;}
   TextIterator& operator ++();
   bool operator ==(const TextIterator& other){
    return (other.chs==chs)&&(other.lchs==lchs);
   }
   bool operator !=(const TextIterator& other){
     return !(*this==other);
   }
};

TextIterator& TextIterator:: operator ++(){
 ++chs;
 if(chs==(*lchs).end()){
    ++lchs;
    chs=(*lchs).begin();
 }
  return *this;
}

struct Document{
  list<vector<char> >lines;    // stores each line of a text-document.
  Document(){ lines.push_back(vector<char>{});}
  TextIterator begin(){return TextIterator(lines.begin(),(*lines.begin()).begin());}
  TextIterator end(){
   auto last= lines.end();
   --last;
   return TextIterator(last,(*last).end());
  }
};

istream& operator >> (istream& is,Document& d){
 for(char x; is.get(x);){
    d.lines.back().push_back(x);
    if(x=='\n')d.lines.push_back(vector<char>{});
  }
  if(d.lines.back().size())d.lines.push_back(vector<char>{});
  return is;
}

void print(Document &d){
 for(auto &x:d){
    cout << x;
 }
}

void eraseline(Document &d,int n){
 if(n>=d.lines.size()-1|| n<0)return;
 auto ll=d.lines.begin();
 advance(ll,n);
 d.lines.erase(ll);
}


int main()
{
  ifstream is{"input.txt"};
  if(!is){cerr << "file not opened!" << endl; exit(1);}

  else {
    Document example;
    is >>example;
    print(example);
    cout << "\n\n";
    eraseline(example,3);  // application of erase function.
    print(example);
  }
  return 0;
}
