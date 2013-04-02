#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include <iostream>
#include <fstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std ;

#define VAR(a,b) __typeof (b) a = b
#define REP(i,n) for (int _n=(n), i=0; i<_n; ++i)
#define FOR(i,a,b) for (int _b=(b), i=(a); i<=_b; ++i)
#define FORD(i,a,b) for (int _b=(b), i=(a); i>=_b; --i)
#define FORE(i,a) for (VAR(i,a.begin ()); i!=a.end (); ++i)

template<class T> struct node {
  T key;
  int balance,size,counter;   //counter - used to implement multiset
  node<T>* left;
  node<T>* right;
};

template<class T> class SET {

public:

  SET(): t(NULL) {}
  inline void insert(T x) {bool h=false; insert(x,t,h);}
  inline void erase(T x) {bool h=false; erase(x,t,h);}
  inline int count(T x) {return count(x,t);}
  inline T kOrder(int k) {return kOrder(k,t);}    // k-th order statistics
  inline T kOrderH(int k) {return kOrder(t->size-k+1,t);}   // k-th order statistics from above
  inline int countLess(T x) {return countLess(x,t);}      // how many smaller elements there are in the set
  inline int countGreat(T x) {return countGreat(x,t);}      // how many greater elements there are in the set
  inline int position(T x) {return position(x,t);}        // how many greater or equal elements there are in the set
  inline T lowerBound(T x) {return lowerBound(x,t);}     // returns the first element in the set greater than x 
  inline T upperBound(T x) {return upperBound(x,t);}     //returns the first element in the set less than x
  inline int size() {return size(t);}

//private:

  node<T>* t;

  inline int position(T x, node<T>* t) {
    return t->size-countGreat(x,t);
  }

  inline T upperBound(T x, node<T>* t) {
    return kOrder(countLess(x,t),t);
  }

  inline T lowerBound(T x, node<T>* t) {
    return kOrder(position(x,t)+1,t);
  }

  inline int countGreat(T x, node<T>* t) {
    int res=0;
    while (t!=NULL) {
      if (x<t->key) {res+=t->counter+size(t->right); t=t->left;}
      else if (x==t->key) {res+=size(t->right); break;}
      else t=t->right;
    }
    return res;
  }

  inline int countLess(T x, node<T>* t) {
    int res=0;
    while (t!=NULL) {
      if (x<t->key) t=t->left;
      else if (x==t->key) {res+=size(t->left); break;}
      else {res+=size(t->left)+t->counter; t=t->right;}
    }
    return res;
  }

  inline int size(node<T>* t) {
    if (t==NULL) return 0;
    else return t->size;
  }

  inline T kOrder(int k, node<T>* t) {
    while (k<=size(t->left) || k>size(t->left)+t->counter) {
      if (k<=size(t->left)) t=t->left;
      else {k-=size(t->left)+t->counter; t=t->right;}
    }
    return t->key;
  }

  int height(node<T>* t) {
    if (t==NULL) return 0;
    return max(height(t->left),height(t->right))+1;
  }

  int count(T x, node<T>* t) {
    if (t==NULL) return 0;
    if (x==t->key) return t->counter;
    if (x<t->key) return count(x,t->left);
    return count(x,t->right);
  }

  inline void update(node<T>* &t) {
    int l,r;
    if (t->left==NULL) l=0; else l=t->left->size; 
    if (t->right==NULL) r=0; else r=t->right->size;
    t->size=l+r+t->counter; 
    t->balance = r - l;
  }

  void insert(T x, node<T>* &t, bool &h) {     //Niklaus Wirth "Algorytmy + struktury danych = programy"
    if (t==NULL) {
      t=new(node<T>);
      h=true;
      t->key=x;
      t->balance=0;
      t->size=1;
      t->counter=1;
      t->left=t->right=NULL;
    }
    else if (x<t->key) {
      ++(t->size);
      insert(x,t->left,h);
      if (h) switch (t->balance) {
        case 1: t->balance=0; 
                h=false; 
                break;

        case 0: t->balance=-1;
                break;

        case -1: node<T>* t1=t->left;
                 if (t1->balance==-1) {
                   t->left=t1->right;
                   update(t);
                   t1->right=t;
                   t->balance=0;
                   t=t1;
                   update(t);
                 }
                 else {
                   node<T>* t2=t1->right;
                   t1->right=t2->left;
                   update(t1);
                   t2->left=t1;
                   t->left=t2->right;
                   update(t);
                   t2->right=t;
                   if (t2->balance==-1) t->balance=1; else t->balance=0;
                   if (t2->balance==1) t1->balance=-1; else t1->balance=0;
                   t=t2;
                   update(t);
                 }
                 t->balance=0;
                 h=false;
                 break;
      } //if (h)
    }  // if x<t->key
    else if (x>t->key) {
      ++(t->size);
      insert(x,t->right,h);
      if (h) switch (t->balance) {
        case -1: t->balance=0;
                 h=false;
                 break;

        case 0: t->balance=1;
                break;

        case 1: node<T>* t1=t->right;
                if (t1->balance==1) {
                  t->right=t1->left;
                  update(t);
                  t1->left=t;
                  t->balance=0;
                  t=t1;
                  update(t);
                }
                else {
                  node<T>* t2=t1->left;
                  t1->left=t2->right;
                  update(t1);
                  t2->right=t1;
                  t->right=t2->left;
                  update(t);
                  t2->left=t;
                  if (t2->balance==1) t->balance=-1; else t->balance=0;
                  if (t2->balance==-1) t1->balance=1; else t1->balance=0;
                  t=t2;
                  update(t);
                }
                t->balance=0;
                h=false;
                break;
      }  // if (h)
    }  // if (x>t->key)
    else /* x==t->key */ {
      ++(t->counter);
      ++(t->size);
      h=false;
    }
  }

  inline void balance1(node<T>* &t, bool &h) {
    switch (t->balance) {
      case -1: t->balance=0;
               break;

      case 0: t->balance=1; 
              h=false;
              break;

      case 1: node<T>* t1=t->right;
              int b1=t->balance; 
              if (b1>=0) { 
                t->right=t1->left; 
                update(t); 
                t1->left=t;
                if (!b1) {t->balance=1; t1->balance=-1; h=false;}
                else {t->balance=0; t1->balance=0;}
                t=t1;
                update(t);
              }
              else {
                node<T>* t2=t1->left; 
                int b2=t2->balance;
                t1->left=t2->right;
                update(t1);
                t2->right=t1;
                update(t2);
                t->right=t2->left;
                update(t);
                t2->left=t;
                update(t2);
                if (b2==1) t->balance=-1; else t->balance=0;
                if (b2==-1) t1->balance=1; else t1->balance=0;
                t=t2;
                t2->balance=0;
              }
              break;
    }
  }

  inline void balance2(node<T>* &t, bool &h) {
    switch (t->balance) {
      case 1: t->balance=0;
              break;

      case 0: t->balance=-1;
              h=false;
              break;

      case -1: node<T>* t1=t->left;
               int b1=t1->balance;
               if (b1<=0) {
                 t->left=t1->right;
                 update(t);
                 t1->right=t;
                 if (!b1) {t->balance=-1; t1->balance=1; h=false;}
                 else {t->balance=0; t1->balance=0;}
                 t=t1;
                 update(t);
               }
               else {
                 node<T>* t2=t1->right;
                 int b2=t2->balance;
                 t1->right=t2->left;
                 update(t1);
                 t2->left=t1;
                 update(t2);
                 t->left=t2->right;
                 update(t);
                 t2->right=t;
                 update(t2);
                 if (b2==-1) t->balance=1; else t->balance=0;
                 if (b2==1) t1->balance=-1; else t1->balance=0;
                 t=t2;
                 t2->balance=0;
               }
               break;
    }
  }

  void er(node<T>* &t, node<T>* &q, bool &h) {
    if (t->right!=NULL) {
      er(t->right,q,h); 
      update(t);
      if (h) balance2(t,h);
      update(t);
    }  
    else {
      q->key=t->key;
      q->counter=t->counter;
      update(q);
      q=t;
      t=t->left;
      h=true;
    }
  }

  void erase(T x, node<T>* &t, bool &h) { 
    if (t==NULL) /* there is no such an element in the tree */ h=false;
    else if (x < t->key) {erase(x,t->left,h); update(t); if (h) balance1(t,h); update(t);}
    else if (x > t->key) {erase(x,t->right,h); update(t); if (h) balance2(t,h); update(t);}
    else { 
      --(t->counter);
      update(t);
      if (!t->counter) {
        node<T>* q=t;
        if (q->right==NULL) {t=q->left; h=true;}
        else if (q->left==NULL) {t=q->right; h=true;}
        else {er(q->left,q,h); update(t);  if (h) balance1(t,h); update(t);} 	
        delete(q);
      } 
    }
  }
  
};

int main() {
  SET<int> S;
  REP(j,100) S.insert(j);
  REP(j,100) cout << S.upperBound(j+1) << endl;
  //REP(i,10) REP(j,100) S.erase(j);
  S.erase(100);
  //REP(j,100) cout << S.count(j) << endl;
  //cout << S.count(100) << endl;
  return 0;
}
