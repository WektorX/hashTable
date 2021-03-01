//============================================================================
// Author      : Wiktor Jurek
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <functional>
#include <fstream>
#include <math.h>       /* pow */
using namespace std;



class HashTable
{
private:
    string* t;
    int capacity;
    int size;
public:
    HashTable(int c);                //konstruktor tworzący pustą tablicę o pojemności c
    bool empty();
    bool full();
    int hashFunction(string s);        //funkcja haszująca dla klucza s
    int insert(string s);            //wstawienie klucza s (zwraca liczbę prób przy wystąpieniu kolizji)
    void del(string s);                //usuwa klucz s
    string search(string s);        //wyszukuje i zwraca s
    int search1(string s);            //wyszukuje s i zwraca liczbę prób przy wystąpieniu kolizji
    friend ostream& operator<<(ostream& out, HashTable& ht); //wypisuje tablicę (z numerami pól), pozostawia puste dla wolnych pól
    int getCapacity();
    string getKey(int i);
};

HashTable::HashTable(int c)
{
    this->t = new string[c]{};
    for(int i=0;i<c;i++){
        t[i]="NULL";
    }
    this->capacity = c;
    this->size =0;
}

bool HashTable::empty()
{
    if(this->size >0 )
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool HashTable::full()
{

    if(this->size == this->capacity)
    {
        return true;
    }
    else
    {
        return false;
    }
}




int HashTable::hashFunction(string s){

    int length = s.length();
    int sum=0;
    for(int i=0;i<length;i++){
        sum += ((int)s[i]) * pow(2, i);
    }
    int hash=0;
    hash = sum%this->capacity;
    return hash;


}

int HashTable::insert(string s){

    if(!this->full()){
        int hash = this->hashFunction(s);
        int trys =0;
        while(this->t[hash] != "NULL" && this->t[hash] != "FREE"){
            hash++;
            trys++;
            if(hash >= this->capacity){
                hash =0;
            }
        }
        this->t[hash] = s;
        this->size+=1;
        return trys;
    }
    else{
        return -1;
    }
}

void HashTable::del(string s){

    int id = this->hashFunction(s);
    while(this->t[id] != s){
        id++;
        if(id >= this->capacity){
            id =0;
        }
    }
    this->t[id] = "FREE";
    this->size -=1;
}

string HashTable::search(string s){

    int id = this->hashFunction(s);
    if(this->t[id] != "NULL" ){
        int count=0;
        while(this->t[id] !=  s){
            id++;
            count++;
            if(id>= this->capacity){
                id=0;
            }
            if(count >= this->capacity){
                return "nie znaleziono";
            }
        }

        return this->t[id];
    }
    else{
        return "nie znaleziono";
    }
}


int HashTable::search1(string s){

    int id = this->hashFunction(s);
    if(this->t[id] != "NULL" ){
        int trys=0;
        while(this->t[id] !=  s){
            id++;
            trys++;
            if(id>= this->capacity){
                id=0;
            }
            if(trys >= this->capacity){
                return -1;
            }
        }

        return trys;
    }
    else{
        return -1;
    }
}

int HashTable::getCapacity(){
return this->capacity;
}

string HashTable::getKey(int i){
    return this->t[i];
}

ostream& operator<<(ostream& out, HashTable* ht){

    for(int i=0; i<ht->getCapacity(); i++){
        if(ht->getKey(i) != "FREE" && ht->getKey(i) != "NULL"){
            cout<<"["<<i<<"] "<<ht->getKey(i)<<endl;
        }
        else{
            cout<<"["<<i<<"]"<<endl;
        }
    }

}

int main(int argc, char** argv)
{

    cout<<"HashTable "<<endl;
    HashTable* h = new HashTable(10);

    h->insert("Katowice");
    h->insert("Wroclaw");
    h->insert("Lodz");
    h->insert("Warszawa");
    h->insert("Krakow");
    h->insert("Gniezno");
    h->insert("Gdynia");
    h->insert("Poznan");
    h->insert("Sopot");
    cout<<h;


    cout<<endl<<"search(Lodz) :"<<h->search("Lodz");
     cout<<endl<<"search1(Krakow) :"<<h->search1("Krakow");
    cout<<endl<<"del(Gdynia)"<<endl;
    h->del("Gdynia");
    cout<<h;
    cout<<endl<<"search(Gdynia) :"<<h->search("Gdynia");

    delete h;


    cout<<endl<<"Test"<<endl;
    int n=40;
    HashTable* imiona = new HashTable(n);
    string* imionaArray = new string[n];

    fstream dataFile;
    dataFile.open("imiona.txt", ios::in);
    if(dataFile.is_open()){
        int i=0;
        string name;
        while(getline(dataFile, name)){
            imionaArray[i] = name;
            i++;

        }
    }
    //mierzymy średnią ilość kolizji dla współczynnika zapełnienia mniejszego od 0.5 dla insert lub search - wynoszą one tyle samo
    double average=0;
    int colision=0;
    for(int i=0;i<n/2;i++){


        int j;
        j = imiona->insert(imionaArray[i]);
        if(j>0){
            colision++;
        }
        average +=j;
    }

    cout<<endl;
    cout<<imiona;
    cout<<endl;
    cout<<endl<<"Sredni ilosc kolizji przy dodawaniu elementow dla wspolczynnika zapelnienia mniejszego od 0.5 :"<<(double)(colision/(double)(n/2));
    cout<<endl<<"Sredni ilosc prob przy dodawaniu elementow dla wspolczynnika zapelnienia mniejszego od 0.5 :"<<(double)(average/(double)(n/2));
    cout<<endl<<"Przy dodaniu elementow dla wspolczynnika zapelanienia <0.5 ilosc kolizji wynosi :"<<colision;
    cout<<endl<<"Przy dodaniu elementow dla wspolczynnika zapelanienia <0.5 ilosc wszystkich prob wynosi :"<<average;
    cout<<endl;

    double average2=0;
    int colision2=0;
    for(int i=n/2;i<n;i++){


        int j;
        j = imiona->insert(imionaArray[i]);
        if(j>0){
            colision2++;
        }
        average2 +=j;
    }

    cout<<endl;
    cout<<imiona;
    cout<<endl;
    cout<<endl<<"Sredni ilosc kolizji przy dodawaniu elementow dla wspolczynnika zapelnienia wiekszego od 0.5 :"<<(double)(colision2/(double)(n));
    cout<<endl<<"Sredni ilosc prob przy dodawaniu elementow dla wspolczynnika zapelnienia wiekszego od 0.5 :"<<(double)(average2/(double)(n));
    cout<<endl<<"Przy dodaniu elementow dla wspolczynnika zapelanienia >0.5 ilosc kolizji wynosi :"<<colision2;
    cout<<endl<<"Przy dodaniu elementow dla wspolczynnika zapelanienia >0.5 ilosc wszystkich prob wynosi :"<<average2;

    return 0;
}




