#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class h
{
private:
    static const int tableSize = 5; //sets table size
    
    struct item //defines each "array cell"
    {
        string name;
        string drink;
        item* next;
    };
    
    item* HashTable[tableSize];
    
public:
    h();
    int Hash(string key); // determines index
    void AddItem(string name,string drink);
    int NumberOfItemsInIndex(int index);
    void PrintTable();
    void PrintItemsInIndex(int index);
    void FindDrink(string name);
    void RemoveItem(string name);
};

h::h() //constructor
{
    for(int i = 0; i < tableSize; i++)
    {
        HashTable[i] = new item;
        HashTable[i]-> name = "empty";
        HashTable[i]-> drink = "empty";
        HashTable[i]-> next = NULL;
    }
}

void h::AddItem(string name, string drink)
{
    int index  = Hash(name);
    
    if(HashTable[index]-> name == "empty")
    {
        HashTable[index]-> name = name;
        HashTable[index]-> drink = drink;
    }
    else
    {
        item* Ptr = HashTable[index];
        item* n = new item;
        n-> name = name;
        n-> drink = drink;
        n-> next = NULL;
        while(Ptr-> next != NULL)
        {
            Ptr = Ptr-> next;
        }
        Ptr-> next = n;
    }
}

int h::NumberOfItemsInIndex(int index) // check to see how many items in bucket
{
    int count = 0;
    
    if(HashTable[index]-> name == "empty")
    {
        return count;
    }
    else
    {
        count++;
        item* Ptr = HashTable[index];
        while(Ptr-> next != NULL)
        {
            count++;
            Ptr = Ptr-> next;
        }
    }
    return count;
}

void h::PrintTable()
{
    int number;
    for(int i = 0; i < tableSize; i++)
    {
        number = NumberOfItemsInIndex(i);
        cout << "---------------------\n";
        cout << "index = " << i << endl;
        cout << HashTable[i]-> name << endl;
        cout << HashTable[i]-> drink << endl;
        cout << "# of items = " << number << endl;
        cout << "---------------------\n";
    }
}

void h::PrintItemsInIndex(int index)
{
    item* Ptr = HashTable[index];//check just this bucket or index
    
    if(Ptr-> name == "empty")
    {
        cout << "bucket " << index << " is empty";
        cout << endl;
    }
    else
    {
        cout << "bucket " << index << " contains the following item\n";
        
        while(Ptr != NULL) // as long as bucket is not empty
        {
            cout << "--------------------\n";
            cout << Ptr-> name << endl;
            cout << Ptr-> drink << endl;
            cout << "--------------------\n";
            Ptr = Ptr-> next; // check for next name
        }
    }
    
}

void h::FindDrink(string name)
{
    int bucket = Hash(name);
    bool foundName = false;
    string drink;
    
    item* Ptr = HashTable[bucket];//bucket is the first name
    while(Ptr != NULL) //as long as bucket is not empty
    {
        if(Ptr-> name == name)
        {
            foundName = true;//easy enough
            drink = Ptr-> drink;
        }
        Ptr = Ptr-> next; //check next
    }
    if(foundName == true)
    {
        cout << "Favorite drink = " << drink << endl;
    }
    else
    {
        cout << name << "'s info was not found in the Hash Table\n";
    }
}

void h::RemoveItem(string name)
{
    int index = Hash(name);
    
    item* delPtr;
    item* P1;
    item* P2;
    
    //case 0 - bucket is empty
    if(HashTable[index]-> name == "empty" && HashTable[index]-> drink == "empty")
    {
        cout << name << " was not found in the Hash Table\n";
    }
    //case 1 - only 1 item in bucket & item has matching name
    else if(HashTable[index]-> name == name && HashTable[index]-> next == NULL)
    {
        HashTable[index]-> name = "empty";
        HashTable[index]-> drink = "empty";
        
        cout << name << " was removed from Hash Table\n";
    }
    //case 2 - match 1st item in bucket but there more items in bucket
    else if(HashTable[index]-> name == name)
    {
        delPtr = HashTable[index];
        HashTable[index] = HashTable[index]-> next;
        delete delPtr;
        
        cout << name << " was removed from Hash Table\n";
    }
    //case 3 - bucket contains items but 1st item not a match
    else
    {
        P1 = HashTable[index]-> next;
        P2 = HashTable[index];
        
        while(P1 != NULL && P1-> name != name)
        {
            P2 = P1;
            P1 = P1-> next;
        }
        //case 3.1 - no match
        if(P1 == NULL)
        {
            cout << name << " was not found in the Hash Table\n";
        }
        //case 3.2 - match is found after 1st item
        else
        {
            delPtr = P1;
            P1 = P1-> next;
            P2-> next = P1;
            delete delPtr;
            cout << name << " was removed from Hash Table\n";
        }
    }
}

int h::Hash(string key)
{
    int hash = 0;
    int index;
    
    for(int i = 0; i < key.length(); i++)
    {
        hash = hash + (int)key[i];
    }
    
    index = hash % tableSize; //Modulo - Remainder comes index
    
    return index;
}

int main() {
    
    h Hashy;
    string name = "";
    
    Hashy.AddItem("Jack", "Balvenie");
    Hashy.AddItem("Dan", "McCallan");
    Hashy.AddItem("Randy", "Soju");
    Hashy.AddItem("Hugh", "Heineken");
    Hashy.AddItem("Rose", "Chardonnay");
    Hashy.AddItem("Kay", "Merlot");
    Hashy.AddItem("Sophia", "POG");
    Hashy.AddItem("Isabelle", "Water");
    Hashy.AddItem("Oreo", "Milk");
    Hashy.AddItem("Mother", "Ginger Ale");
    
    Hashy.PrintTable();
    //Hashy.PrintItemsInIndex(4); //to find who is in each bucket where there is more than one
    
    /*while(name != "exit")//To look for someone's favorite drink
    {
        cout << "Search for: ";
        cin >> name;
        if(name != "exit")
        {
            Hashy.FindDrink(name);
        }
    }*/
    
    while(name != "exit")//To look for someone's favorite drink
    {
        cout << "Remove: ";
        cin >> name;
        if(name != "exit")
        {
            Hashy.RemoveItem(name);
        }
    }
    //Hashy.PrintTable();
    
    return 0;
}
