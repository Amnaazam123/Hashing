#include<iostream>
#include<list>
using namespace std;
class HASH {
	int tableSize;
	int totalValues;
	list<__int64 unsigned>* table;               //table array containing the address of list
	__int64 unsigned a;
	__int64 unsigned b;
	__int64 unsigned p;
public:
	HASH() {
		tableSize = 1;         //initially table size=1, cannot be 0 because need to resize it
		totalValues = 0;       
		table = new list<__int64 unsigned>[tableSize];      //maintaining list for each cell 
		p = 18361375334787046697;
		a = rand() % (p - 1) + 1;
		b = rand() % (p - 1);
	}

	__int64 unsigned hashFunction(__int64 unsigned key)
	{
		//h(k) = ((ak + b) mod p) mod m
		__int64 unsigned index = ((a * key + b) % p) % tableSize;
		return index;
	}
	void insertValueInHashTable(__int64 unsigned keyToInsert, __int64 unsigned HashedArr[])
	{
		cout << "\n*******************Insertion****************************\n";
		cout << "\nTable size is: " << tableSize;
		__int64 unsigned index = hashFunction(keyToInsert);
		if (tableSize == totalValues)                        //full table?
			tableSize = resizeDouble(tableSize,HashedArr);    //double your table
		totalValues++;                                          
		cout << "\nTotal hashed values are: " << totalValues;
		cout << "\n" << keyToInsert << " is hashed at index " << index << "\n";
		table[index].push_back(keyToInsert);                   //no checking for rehashing here, just pushing back in list if collision                            
	}

	int resizeDouble(int s, __int64 unsigned HashedArr[])
	{
		if (totalValues == tableSize)                             //if table is full?
			tableSize = tableSize * 2;                            //double your table

		cout << "\nTable is doubled i.e.\n"<<tableSize;

		delete[] table;                                           //delete initial table

		table = new list<__int64 unsigned>[tableSize];                //new table

		//after doubling table, we need to rehash all values again according to new a and b
		a = rand() % (p - 1) + 1;
		b = rand() % (p - 1);


		cout << "\n------------RE-HASHING---------------\n";
		for (int i = 0; i < totalValues; i++)          //re-Hashing values in new Table
		{
			if (HashedArr[i] != 0)
			{
				__int64 unsigned index = hashFunction(HashedArr[i]);
				cout << "\n" << HashedArr[i] << " is hashed at index " << index << "\n";
				table[index].push_back(HashedArr[i]);
			}
		}
		return tableSize;
	}
	void printTable()
	{
		cout << "\n\n		*********************HASH TABLE**********************		\n";
		for (int i = 0; i < tableSize; i++)
		{
			if (table[i].empty())
			{
				cout << "0\n";
				continue;
			}
			for (auto ele : table[i])
			{
				cout << ele << "-->";
			}
			cout << endl;
		}
	}
	bool searchValuesInHashTable(__int64 unsigned keyTosearch)
	{
		int searchIndex = hashFunction(keyTosearch);

		list <__int64 unsigned> ::iterator i;
		for (i = table[searchIndex].begin();i != table[searchIndex].end(); i++) 
		{
			if (*i == keyTosearch)
				break;
		}
		if (i != table[searchIndex].end())
		{
			cout << keyTosearch <<" Founded in hash table.\n";
			return true;
		}
		else
		{
			cout << "Key not found\n";
			return false;
		}


	}
	bool deleteValuesInHashTable( __int64 unsigned* HashedArr,int from,int to)
	{
		__int64 unsigned keyToDelete=HashedArr[from];
		cout << "\n*******************deletion****************************\n";
		int deleteIndex = hashFunction(keyToDelete);
		list <__int64 unsigned> ::iterator i;
		for (i = table[deleteIndex].begin();
			i != table[deleteIndex].end(); i++) {
			if (*i == keyToDelete)
				break;
		}
		if (i != table[deleteIndex].end())
		{
			table[deleteIndex].erase(i);
			cout << keyToDelete << " is deleted successfully.\n";
			HashedArr[from] = 0;
			totalValues--;
			if (totalValues <= tableSize / 4)                             //if 3/4th part of table is empty?
			{
				tableSize = tableSize / 2;
				delete[] table;
				table = new list<__int64 unsigned>[tableSize];
				cout << "\n------------del RE-HASHING---------------\n";
				for (int i = 0; i < to; i++)             //re-Hashing values in new Table
				{
					if (HashedArr[i] != 0)
					{
						
						__int64 unsigned index = hashFunction(HashedArr[i]);
						cout << "\n" << HashedArr[i] << " is hashed at index " << index << "\n";
						table[index].push_back(HashedArr[i]);
					}
				}
			}
			return true;
		}
		else
		{
			if (keyToDelete == 0)
			{
				cout << "This key is already removed from hash table.\n";
			}
			else
			{
				cout << keyToDelete << " is not found\n";
			}
			return false;
		}
	}
	int totalCollisions() {
		int collisions = 0;
		for (int i = 0; i < tableSize; i++) {
			if (!table[i].empty()) {
				collisions += table[i].size() - 1;
			}
			
		}
		return collisions;
	}
};

int main()
{
	srand(time(NULL));
	HASH h;
	int n;
	cout << "\n\nHow many random numbers you want to generate?\n";
	cout << "Give input :";
	cin >> n;
	__int64 unsigned* randNums = new __int64 unsigned[n];
	__int64 unsigned max = pow(2, 64) - 1;
	for (__int64 unsigned i = 0; i < n; i++)
	{
		randNums[i] = rand() % max;
	}
	cout << "\n\n--------	Random numbers generated	---------\n";
	for (int i = 0; i < n; i++)
	{
		cout << randNums[i] << "\t";
	}

	int choice = 1;
	for (int i = 0; i < n; i++)
	{
		choice = rand() % 3 + 1;
		if (choice == 1)
		{
			h.insertValueInHashTable(randNums[i], randNums);
		}
		else if (choice == 2)
		{
				int y = rand() % n;
				h.deleteValuesInHashTable(randNums, y, i);

		}
		else if (choice == 3)
		{
			int y = rand() % n;
			h.searchValuesInHashTable(randNums[y]);
		}
	}
	
	//print table
	h.printTable();
	cout << "\n\nCOLLISIONS:" << h.totalCollisions() << "\n";
	return 0;

}