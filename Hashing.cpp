#include <iostream>
using namespace std;

class Student {
public:
	string id, name;
	int age;
	double gpa;
	Student* next;
	friend class HashTable;

	Student(string key, string name, int age, double gpa) {
		this->id = key;
		this->name = name;
		this->age = age;
		this->gpa = gpa;
	}

	Student() {
		this->id = "";
		this->name = "";
		this->age = NULL;
		this->gpa = NULL;
	}

	string getId() {
		return id;
	}

	Student* getNext() {
		return next;
	}
};

class HashMap {
	Student** table;
	int size;

public:

	int getSize() {
		return size;
	}

	HashMap(int size) {
		this->size = size;
		this->table = new Student *[size];

		for (int i = 0; i < size; i++)
			table[i] = nullptr;
	}

	void put(Student* e) {
		string key = e->getId();
		int index = hash(key) % size;
		Student* newStudent = table[index];
		e->next = newStudent;
		
		table[index] = e;
	}

	Student* get(string key) {

		int index = hash(key) % size;
		int startIndex = index;
		Student* newStudent = table[index];

		while (newStudent != NULL && newStudent->getId() != key) {
			index = (index + 1) % size;
			if (index == startIndex)	
				return NULL;
		}

		cout << " " << newStudent->id;
		cout << " ---->";
		cout << " [NAME: " << newStudent->name << " | " << "AGE: " << newStudent->age << " | " << "GPA: " << newStudent->gpa << "] " << endl;

		return table[index];
	}

	Student* remove(string key) {

		int index = hash(key) % size;
		int startIndex = index;

		while (table[index] != NULL && table[index]->getId() != key) {
			index = (index + 1) % size;
			
			if (index == startIndex)	
				return NULL;
		}
		Student* e = table[index];
		delete e;
		table[index] = NULL;
		return e;
	}

	~HashMap() {
		for (int i = 0; i < size; i++)
			if (table[i] != nullptr)
				delete table[i];
		delete[] table;
	}

	unsigned long hash(string str) {
		const char* cstr = str.c_str();
		unsigned long hash = 5381;
		int c;

		while (c = *cstr++) {
			hash = hash * 33 + c;
		}

		return hash;
	}

	void displayData() {
		cout << " All students in the HashMap: \n";
		for (int i = 0; i < size; i++) {
			Student* present = table[i];
			if (present != NULL) {
				cout << "\n Hash Value: " << i << "\n";
				while (present != NULL) {
					cout << " " << present->id;
					cout << " ---->";
					cout << " [NAME: " << present->name << " | " << "AGE: " << present->age << " | " << "GPA: " << present->gpa << "] " << endl;
					present = present->next;
					
				}
			}
		}
	}
};

int main() {
	
	HashMap map(20);
	Student* student = new Student("201028222", "Dakota Swank", 25, 3.8);
	Student* student2 = new Student("234357687", "Al Weight", 35, 3.1);
	Student* student3 = new Student("154684247", "Zack Jones", 28, 3.3);
	Student* student4 = new Student("847936472", "Alex Clontz", 27, 2.5);
	Student* student5 = new Student("348649731", "Brandon Cruz", 31, 3.3);
	Student* student6 = new Student("548465342", "Alec Baldwin", 48, 2.2);
	Student* student7 = new Student("987653565", "Jim Carey", 37, 2.9);
	Student* student8 = new Student("253467567", "Drew Barry", 42, 3.6);


	cout << "\n"; 
	map.put(student);
	map.put(student2);
	map.put(student3);
	map.put(student4);
	map.put(student5);
	map.put(student6);
	map.put(student7);
	map.put(student8);
	
	map.displayData();

	cout << "\n Removing student with ID 201028222\n\n";
	map.remove("201028222");

	map.displayData();

	cout << "\n Students found in hashmap: \n";
	map.get("154684247");
	/*cout << " " << getStudent->id;
	cout << " ---->";
	cout << " [NAME: " << getStudent->name << " | " << "AGE: " << getStudent->age << " | " << "GPA: " << getStudent->gpa << "] " << endl;*/
}