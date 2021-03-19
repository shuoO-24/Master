# Linked List

Created Time: Feb 19, 2021 9:38 PM
Functions: destructor; single linked list
Property: Mar 16, 2021 11:55 PM
掌握/Check: No
描述/Description & Usage: Always need to use private friend functions if using recursion
类型/Type: Data Structure and Algorithm
难度/不熟练度: ****

# A first linked list

A common use of pointers is to create a list of items such that an item can be efficiently inserted somewhere in the middle of the list, without the shifting of later items as required for a vector. The following program illustrates how such a list can be created. A class is defined to represent each list item, known as a ***list node***. A node is comprised of the data to be stored in each list item, in this case just one int, and a pointer to the next node in the list. A special node named head is created to represent the front of the list, after which regular items can be inserted.

```cpp
class IntNode {
public:
   IntNode(int dataInit = 0, IntNode* nextLoc = nullptr);
   void InsertAfter(IntNode* nodeLoc);
   IntNode* GetNext();
   void PrintNodeData();
private:
   int dataVal;
   IntNode* nextNodePtr;
};

// Constructor
IntNode::IntNode(int dataInit, IntNode* nextLoc) {
   this->dataVal = dataInit;
   this->nextNodePtr = nextLoc;
}

/* Insert node after this node.
 * Before: this -- next
 * After:  this -- node -- next
 */
void IntNode::InsertAfter(IntNode* nodeLoc) {
   IntNode* tmpNext = nullptr;
   
   tmpNext = this->nextNodePtr;    // Remember next
   this->nextNodePtr = nodeLoc;    // this -- node -- ?
   nodeLoc->nextNodePtr = tmpNext; // this -- node -- next
}

// Print dataVal
void IntNode::PrintNodeData() {
   cout << this->dataVal << endl;
}

// Grab location pointed by nextNodePtr
IntNode* IntNode::GetNext() {
   return this->nextNodePtr;
}
```

# Destructors

A ***destructor*** is a special class member function that is called automatically when a variable of that class type is destroyed. C++ class objects commonly use dynamically allocated data that is deallocated by the class's destructor.
Ex: A linked list class dynamically allocates nodes when adding items to the list. Without a destructor, the link list's nodes are not deallocated. The linked list class destructor should be implemented to deallocate each node in the list.

```cpp
IntList::~IntList(){
   if (!empty()){
      delete head;
   }
}
```

```cpp
class LinkedListNode {
public:
   ...
   int data;
   LinkedListNode* next;
};

class LinkedList {
public:
   ...
   LinkedListNode* head;
};

int main() {
   LinkedList* list1; // Null
   list1 = new LinkedList();
   ... // Add items to list1
//After adding 2 items, 3 dynamically allocated objects exist:
// the list itself and 2 nodes.
   delete list1; 
// Without a destructor, deleting list1 only 
//deallocates the list1 object, but not the 2 nodes.
}
```

# Copy constructors

The solution is to create a ***copy constructor***, a constructor that is automatically called when an object of the class type is passed by value to a function and when an object is initialized by copying another object during declaration. Ex: `MyClass classObj2 = classObj1;` or `obj2Ptr = new MyClass(classObj1);`. The copy constructor makes a new copy of all data members (including pointers), known as a ***deep copy***.

If the programmer doesn't define a copy constructor, then the compiler implicitly defines a constructor with statements that perform a memberwise copy, which simply copies each member using assignment: `newObj.member1 = origObj.member1`, `newObj.member2 = origObj.member2`, etc. Creating a copy of an object by copying only the data members' values creates a ***shallow copy*** of the object. A shallow copy is fine for many classes, but typically a deep copy is desired for objects that have data members pointing to dynamically allocated memory.

The copy constructor can be called with a single pass-by-reference argument of the class type, representing an original object to be copied to the newly-created object. A programmer may define a copy constructor, typically having the form: `MyClass(const MyClass& origObject);`

```cpp
   public:
      ...
      **MyClass(const MyClass& origObject);**
      ...
```

When copy constructor be called:

1. `EncBlock* lastBlock = new EncBlock(myBlock);`
2. `EncBlock vidBlock = myBlock;`

### With Copy Destructor, Only Copying Once

After copying to be constructed, change in the original object does not effect the copy.

```cpp
class IntNode {
   public:
      IntNode(int value) {
         numVal = new int;
         *numVal = value;
      } 
      **IntNode(const IntNode& origObject) {
         cout << "Copying " << *(origObject.numVal) << "; ";
         numVal = new int;
         *numVal = *(origObject.numVal);
      }** 
      ~IntNode() {
         delete numVal;
      } 
      void SetNumVal(int val) { *numVal = val; }
      int GetNumVal() { return *numVal; }
   private:
      int* numVal;
};

int main() {
   IntNode node1(1);
   IntNode node2 = node1;

   node1.SetNumVal(5);
   cout << node2.GetNumVal() << " " << node1.GetNumVal() << endl; // Copying 1; 5

   return 0;
}
```

```cpp
class IntNode {
   public:
      IntNode(int value) {
         numVal = new int;
         *numVal = value;
      }
      void SetNumVal(int val) { *numVal = val; }
      int GetNumVal() { return *numVal; }
   private:
      int* numVal;
};

int main() {
   IntNode node1(1);
   IntNode node2(2);
   IntNode node3(3);

   node2 = node1;
   node1.SetNumVal(5);

   cout << node2.GetNumVal() << " " << node1.GetNumVal() << endl; // 5 5

   return 0;
}
```

If the private data type is not a pointer:

```cpp
private:
      int carCount;
};
/*
	Write a copy constructor for CarCounter that assigns origCarCounter.carCount to the constructed object's carCount. Sample output for the given program:
*/
CarCounter::CarCounter(const CarCounter &p){
	carCount = p.carCount;
}
```

### Problem: **Copying an object without a copy constructor**

The animation below shows a typical problem that arises when an object is passed by value to a function and no copy constructor exists for the object.

![Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled.png](Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled.png)

---

# Operator =

`MyClass& operator=(const MyClass& objToCopy);`

```cpp
MyClass& MyClass::operator=(const MyClass& objToCopy) {
	 cout << "Assignment op called." << endl;
   
   **if (this != &objToCopy) {     // 1. Don't self-assign
      delete dataObject;         // 2. Delete old dataObject
      dataObject = new int;      // 3. Allocate new dataObject
      *dataObject = *(objToCopy.dataObject); // 4. Copy dataObject
   }**
   
   return *this;
}

```

A copy assignment operator for CarCounter that assigns objToCopy.carCount to the new objects's carCount, then returns *this. Sample output for the given program:

```cpp
CarCounter& CarCounter::operator=(const CarCounter& objToCopy){
   delete carCount;
   carCount = new int;
   *carCount = *(objToCopy.carCount);
   **return *this;**
}
```

---

# Single linked list

### **Implementing the LinkedList class destructor**

The syntax for a class's destructor function is similar to a class's constructor function, but with a "~" (called a "tilde" character) prepended to the function name. A destructor has no parameters and no return value. So the LinkedListNode and LinkedList class destructors are declared as `~LinkedListNode();` and `~LinkedList();`, respectively.

The LinkedList class destructor is implemented to free each node in the list. **The LinkedListNode destructor is not required.** Using delete to free a dynamically allocated LinkedListNode or LinkedList will call the object's destructor.

```cpp
class LinkedListNode {
public:
   LinkedListNode(int dataValue) {
      cout << "In LinkedListNode constructor (" << dataValue << ")" << endl;
      data = dataValue;
   }
    
   **~LinkedListNode() {
      cout << "In LinkedListNode destructor (";
      cout << data << ")" << endl;
   }**
    
   **int data;
   LinkedListNode* next;**
};

class LinkedList {
public:
   LinkedList();
   ~LinkedList();
   void Prepend(int dataValue);
    
   LinkedListNode* head;
};

LinkedList::LinkedList() {
   cout << "In LinkedList constructor" << endl;
   head = nullptr;
}

**LinkedList::~LinkedList() {
   cout << "In LinkedList destructor" << endl;
    
   // The destructor deletes each node in the linked list
   while (head) {
      LinkedListNode* next = head->next;
      delete head;
      head = next;
   }
}**

void LinkedList::Prepend(int dataValue) {
   LinkedListNode* newNode = new LinkedListNode(dataValue);
   newNode->next = head;
   head = newNode;
}

int main() {
   // Create a linked list
   LinkedList* list = new LinkedList;
   for (int i = 1; i <= 5; ++i)
      list->**Prepend**(i * 10);
      
   // Free the linked list.
   // The LinkedList class destructor frees each node.
   delete list; // **head is the last item in the list**

   return 0;
}
```

Using the delete operator on an object allocated with the new operator calls the destructor, as shown in the previous example. For an object that is not declared by reference or by pointer, the object's destructor is called automatically when the object goes out of scope.

listToDisplay is not passed by pointer or by reference and goes out of scope at the end of the DisplayList function. Thus, listToDisplay's destructor is called.

```cpp
void DisplayList(LinkedList listToDisplay) {
   LinkedListNode* node = listToDisplay.head;
   while (node) {
      cout << node->data << " ";
      node = node->next;
   }
}
```

### looping linked list

```cpp
ostream & operator<<(ostream &out, const IntList & list){
    for (IntNode* node = list.head; node != nullptr; node = node->next){
        out << node->value;
        if (node == list.tail){
            break;
        }
        out << ' ';    
    }
    return out;
}
/* if写成这样：
	  IntNode* node = list.head;
    **out << node->value; //当链表为空时会有segmentation fault（undefined behavior）**
    for (**node = node->next**; **node != nullptr**; node = node->next){
```

Remember to add a case to hold (head == nullptr)

![Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%201.png](Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%201.png)

### **Inserting/erasing in vectors vs. linked lists**

A vector (or array) stores a list of items in contiguous memory locations, which enables immediate access to any element of a vector userGrades by using `userGrades.at(i)` (or `userGrades[i]`). However, inserting an item requires making room by shifting higher-indexed items. Similarly, erasing an item requires shifting higher-indexed items to fill the gap. Shifting each item requires a few operations. If a program has a vector with thousands of elements, a single call to insert() or erase() can require thousands of instructions and cause the program to run very slowly, often called the ***vector insert/erase performance problem***.

Appending just places the new item at the end of the vector. No shifting of existing elements is necessary.

A programmer can use a linked list to make inserts or erases faster. A **linked list** consists of **items that contain both data and a pointer**—a link—to the next list item. Thus, **inserting a new item B between existing items A and C just requires changing A to point to B's memory** **location, and B to point to C's location**, as shown in the following animation. **No shifts occur**.

![Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%202.png](Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%202.png)

A vector is like people ordered by their seat in a theater row; if you want to insert yourself between two adjacent people, other people have to shift over to make room. A linked list is like people ordered by holding hands; if you want to insert yourself between two people, only those two people have to change hands, and nobody else is affected.

[Comparing vectors and linked lists](https://www.notion.so/d1263712165c4706ba41df3cdeb02003)

---

## pop_front()

```cpp
void IntList::pop_front(){
    // the same three senarios
    if (!empty()){ 
        if (head != nullptr){
            IntNode* node = head->next;
            head = node;
        }
        else if(head == tail){
            head = nullptr;
            tail = nullptr; // avoid the dangling pointer
        }
    }
    
}
```

---

## Delete a node from list

### from head

```cpp
void IntList::deleteFromBeg(){
	if (head != nullptr){
		IntNode* temp = head;
		head = head->next; // or head = temp->next;
		delete temp;
	}
}
```

![Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%203.png](Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%203.png)

### from end

```cpp
void IntList::deleteFromEnd(){
	IntNode* temp = head;

	// traverse a list
	while (temp){
		if (temp->next->value % 2 == 1 && temp->next->next == nullptr){
			temp->next = nullptr;
		}
		temp = temp->next;
	
			
```

![Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%204.png](Linked%20List%205b0ec1fe99ca4e5785d203eb141dc7ed/Untitled%204.png)

```c
IntNode* prev;
IntNode* temp = head;

// traverse the list
while(temp->next != 0){
	prev = temp;
	temp = temp->next;
}

if (temp == head){
	head = 0;
} else {
	prev->next == 0;
}
free(temp);
```

```cpp
IntNode* prev = nullptr;
IntNode* temp = head;

// traverse the list
while(temp->next != nullptr){
	prev = temp;
	temp = temp->next;
}

if (temp == head){
	delete head;
	head = nullptr;
} else {
	prev->next == nullptr;
}
delete temp;
```

### From middle

```cpp
void IntList::deleteFromPos(int pos){
	IntNode* prev = head;
	IntNode* temp = nullptr;
	int i = 1;
	while (i < pos-1){
		prev = prev->next;
		i++;
	}
	temp = prev->next;
	prev->next = temp->next; 
	delete temp;
}
	
```

---

## Traverse the linked list