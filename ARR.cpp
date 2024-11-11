//Cody Hathcoat		October 21st, 2024	Program #1	CS302

#include "Attendee.h"

/*The purpose of this file is to handle the implementation of the array of 
linked lists data structure. This means the file must handle the implementation
of the array of linked lists node, as well as the array of linked list management
class. This involves building the list, destroying the list, retrieving, displaying, 
and copying just to name some of the functionality. This will allow the adult
attendee to have a haunted maze to be able to traverse through.
*/


/*The purpose of this constructor is to set all of the array nodes data 
members to their 0 equivalent values. This involves setting the room 
number to 0, and the two pointers to null pointer. All of this work is
able to be done in the initialiation list.
*/
ARR_node::ARR_node() : room_number(0), next(nullptr), connecting_room(nullptr)
{}

/*The purpose of this argument contructor is to initialize the data members of the array
node class when given an integer argument. This argument is used to set the room number
of the node, and the pointers are set to null pointer. All of this is handled in the 
initialization list.
*/
ARR_node::ARR_node(int room) : room_number(room), next(nullptr), connecting_room(nullptr)
{}

/*
The purpose of this destructor is to free all of the dynamic memory the array node 
has allocated. This involves handling the next and connecting pointers since they 
point to other nodes. The destructor is important because it prevents memory leaks.
*/
ARR_node::~ARR_node()
{
	if(next)
	{
		next = nullptr;
	}
	
	if(connecting_room)
	{
		connecting_room = nullptr;
	}	
}

/*The purpose of this function is to set an array nodes next pointer.
The argument of this function is the node should be pointed to by 
the next pointer. This function returns 1 to show success.
*/
int ARR_node::set_next(ARR_node * new_next)
{
	next = new_next;
	return 1;
}

/*The purpose of this function is to set an array nodes 
connecting pointer. The argument of this function is the node 
that should be pointed to by the connecting pointer. The
function returns 1 to show success.
*/
int ARR_node::set_connecting(ARR_node * connecting)
{
	connecting_room = connecting;
	return 1;
}

/*The purpose of this function is to get the next pointer
for an array node. This function simply returns the pointer
since it is of type ARR_node.
*/
ARR_node *& ARR_node::get_next()
{
	return next;
}

/*The purpose of this function is to get the next pointer
for an array node that can't be changed in a function. This
function simply returns the next pointer since the function is 
of type ARR_node.
*/
const ARR_node * ARR_node::get_next() const
{
	return next;
}

/*The purpose of this function is to get the connecting pointer
for an array node. This function simply returns the pointer
since it is of type ARR_node.
*/
ARR_node *& ARR_node::get_connecting()
{
	return connecting_room;
}

/*The purpose of this function is to get the connecting pointer
for an array node that can't be changed in a function. This
function simply returns the connecting pointer since the function is 
of type ARR_node.
*/
const ARR_node * ARR_node::get_connecting() const
{
	return connecting_room;
}

/*The purpose of this function is to display the 
information in an array node. This involves showing
the room number, as well as the number of the rooms 
that are connected. The function will return 0 if 
no room data has been entered, and returns 1 if the 
data was successfully shown.
*/
int ARR_node::display_data() const
{
	//Don't show any info if the room doesn't exist.
	if(room_number == 0)
		return 0;

	//Show the room number. 
	cout << "\n\nRoom Number " << room_number;
	int next_num = show_connection(next, connecting_room); //Show the connections
	return next_num; //Return the result.
}

/*The purpose of this function is to show the rooms connected to 
a certain room. The first argument is the first room being displayed
and the second argument is the second room to be displayed. 
This function returns 1 to show success.
*/
int ARR_node::show_connection(ARR_node * connect, 
			      ARR_node * second_connect) const
{	
	cout << "\nConnecting rooms: " << endl;

	//Display the rooms if they exist.	
	if(connect)
		cout << "Room " << connect->room_number << " " << endl;
	
	if(second_connect)
		cout << "Room " << second_connect->room_number << endl; 

	return 1; //Return 1 to show success.
}

/*The purpose of this function is to check if the room number 
passed in as an argument matches the room number associated with 
a the room. The function simply checks if the room numbers are 
the same, and if they are it returns true, and if not returns 
false.
*/
bool ARR_node::same_room(int room_num)
{
	//Return true if the room numbers match.
	if(room_number == room_num)
		return true;
	else 
		return false;
}

/*The purpose of this function is to copy the room number into
the integer argument. If the information doesn't exist, 0 
is returned to show failure, and otherwise the room number is 
returned.
*/
int ARR_node::copy_data(int &room)
{
	//Check if the room exists.
	if(room_number == 0)
		return 0;

	//Copy the number.
	room = room_number;
	return room;	
}

/*The purpose of this function is to get the room number from 
an array node. This function is an integer, so it simply 
returns the room number from the node.
*/
int ARR_node::get_room() const
{
	return room_number;
}

/*The purpose of this constructor is to set the data in the 
array of linked lists management class to its 0 equivalent value. 
This simply involves initializing the array of linked lists and 
setting each element to null pointer.
*/
ARR::ARR() : lists(nullptr), location(nullptr), location_index(0)
{
	//Set the size.
	int default_size = ARR_SIZE;
	lists = new ARR_node *[default_size];
	
	//Initialize the lists.
	initialize(0);

	build();
}

/*The purpose of this destructor is to deallocate all dynamic
memory that has been allocated in the array of linked list. This
involves calling a function to remove all of the information in 
the lists, and then finally deleting the list itself.
*/
ARR::~ARR()
{
	//Remove all the data and delete the list.
	remove_all();
	delete [] lists;
}

/*The purpose of this copy constructor is to perform a deep 
copy. This means the argument is used as the source information
and is copied into the current object. This allows for copies 
to be made without crossing dynamic memory with shallow copies, 
which prevents memory leaks and double free errors.
*/
ARR::ARR(const ARR &to_copy)
{
	lists = new ARR_node *[ARR_SIZE];
	deep_copy(to_copy);
}

/*The purpose of this assignment operator is to allow
two existing arrays of linked lists be copied by using
a deep copy. This prevents memory leaks and double free
errors. 
*/
ARR & ARR :: operator=(const ARR &src)
{
	//Check for self assignment.
	if(this == &src)
		return *this;
	
	//Deallocate any existing memory.
	if(lists)
		remove_all();

	//Perform a deep copy.
	deep_copy(src);	

	//Return the current object.
	return *this;
}

/*The purpose of this function is to go through an 
array of linked lists and initialize each element. 
For the sake of this program, there will be 4 elements
in this array. Each element will be initialized to 
null pointer. This function returns 0 if it fails, and
otherwise returns a positive integer.
*/
int ARR::initialize(int index)
{	
	//Check if we are past the size of the array.
	if(index >= ARR_SIZE)
		return 0;

	//Set the list index to null.
	lists[index] =  nullptr;
	++index; //Increment the index.

	//Return the function call.
	return initialize(index) + 1;
}

/*The purpose of this function is to allow a node
to be inserted into the array of linked list. This 
function sets the index the room number should be in
and then calls another function to handle the 
actual insersion. The function returns 0 if the
room number is invalid, and otherwise returns 1 if
the insersion was successful. The functions 
argument is the room number, which is a float to allow
for proper division when determining the index.
*/
int ARR::insert(float room_num)
{

	//Check if the room number is valid.	
	if(room_num < 1 || room_num > 12)
		return 0;

	//Set the correct index using floor.
	int index = floor(room_num/ARR_SIZE - 0.1);
	return insert(index, lists[index], room_num); //Insert the node and 
						      //return.

}

/*The purpose of this function is actaully insert the new node
into the data structure. This function will be called the the 
previous insert function. The first argument is the index where 
the insersion will happen, the second argument is a array node
pointer to allow for traversal, and the third argument is the 
room number. This function uses recursion to properly insert
the room, and returns 1 if successful and 0 if not.
*/
int ARR::insert(int index, ARR_node * &head, int room_num)
{
	//If the list doesn't exist yet.
	if(!head)
	{
		//Create the node and return successful.
		head = new ARR_node(room_num);
		return 1;
	}

	//If we don't need to insert at the start.
	if(!head->get_next())
	{
		//Create teh node and return successful.
		head->get_next() = new ARR_node(room_num);
		return 1;
	}

	//If the room already exists.
	if(head->same_room(room_num))
		return 0; //Return 0 to show failure.

	//Recall the function with the next node and return.	
	return insert(index, head->get_next(), room_num);
}

/*The purpose of this function is to build the entire array 
of linked lists. This function sets the first room number to 1,
and calls a recursive build function to assist with recursion.
This function will return poistive to show success.
*/
int ARR::build()
{
	float room_num{1}; //Set the initial room number.
	
	int create = build(room_num); //Call the recursive function 
				      //and return.
	location = lists[0];

	//Add connections between the room.
	int connect = add_connection(4, 7);
	connect += add_connection(7, 9);
	connect += add_connection(8, 10);
	connect += add_connection(5, 11);
	connect += add_connection(9,6);
	connect += add_connection(1, 5);
	connect += add_connection(2, 6);
	connect += add_connection(11, 1);

	return create + connect;

}

/*The purpose of this function is to build the entire array of 
linked lists. The function does this by calling the 
insert function, and by recursively increasing the room number
by 1 with each call. This function will return the number of
nodes it creates.
*/
int ARR::build(float room_num)
{
	int create{0}; //Used to call the insert function

	//If the room number is to big.
	if(room_num > 12)
		return 0;

	//Insert the node and then increment the current room.	
	create = insert(room_num);
	++room_num;

	return build(room_num) + create; //Recall the function with the 
					 //updated room number.
}

/*The purpose of this function is to display all the information in 
an array of linked lists. This function a wrapper function, so it
sets the starting index variable to 0 and calls the recursive funciton
to assist in teh display. The function will return an integer which is 
from the recursive function to show success of failure.
*/
int ARR::display() const
{
	int index{0};  //Set where to start in the array.
	return display(index); //Call the recursive function and return.

}

/*The purpose of this recursive display function is to go through 
each index of the array of linked lists. With each index, this
function will call another recursive function which will 
display the information in each list. This function will 
return positive if the lists were displayed, and return 0
if the lists couldn't be displayed.
*/
int ARR::display(int index) const
{
	int show_lists{0}; //Holds the display functions result.

	//If the index is to big. 
	if(index == ARR_SIZE)
		return 0;
	
	//Call the display function for the list.
	show_lists = display(lists[index]);	

	return display(index + 1) + show_lists; //Recall the function with a
						//bigger index and return.
}

/*The purpose of this function is to display all of the 
data in a single list of items in an array of linked list. The
argument is the head pointer of the linked list index, and will be 
used to traverse the list recursively. This function will return 
positive if the data was shown, and will return 0 if no data could be
shown." 
*/
int ARR::display(ARR_node * head) const
{
	int show{0}; //Did the data appear?
	
	//If the current entry doesn't exist.
	if(!head)
		return 0;
		
	show = head->display_data(); //Display the current node.

	return display(head->get_next()) + show; //Recall the function with
						 //the next node and return.
}

/*The purpose of this function is to remove an item from the array of linked
lists. The function uses its argument which is the room number, as well as 
recursive functions to find the node to delete and then remove it. The 
function will return 0 if the room coudln't be found or is invalid, and will
return positive if the room is deleted.
*/
int ARR::remove(int room_num)
{
	int index{0}; //Set the intial starting index.

	//If the room entered is invalid, return 0. 
	if(room_num == 0)
		return 0;

	//Call the recursive function and return.
	return remove_search(index, room_num);
}

/*The purpose of this function is to search the list
to try and find the correct node to delete. The function
does this by calling another recursive function with the 
head pointer in each element to go through the list to try
and find the correct  node to remove. The function returns
0 if the node coulnd't be found, and retursn 1 if the node
was removed.
*/
int ARR::remove_search(int index, int room_num)
{
	int destroy{0}; //Was the node removed.

	ARR_node * previous = lists[index]; //Create a pointer to 
					    //help traverse.

	//If the index is larger then the array size.
	if(index >= ARR_SIZE)
		return 0;

	//If the node to delete is the first one.
	if(lists[index] && lists[index]->same_room(room_num))
	{
		//Delete the node and return 1.
		ARR_node * hold = lists[index]->get_next();
		delete lists[index];
		lists[index] = hold;
		return 1;
	}

	//If the list doesn't exist, recall the function incrementing
	//the index.
	if(!lists[index])
		return remove_search(++index, room_num);
	
	//Call the function to search an individual list for the node.	
	destroy = remove_search(previous->get_next(), previous, room_num);

	//If the node was destroyed return 1.
	if(destroy == 1)
		return 1;

	//Recall the function with the next index.
	return remove_search(++index, room_num) + destroy;
}

/*The purpose of this function is to search an individual list and try and
find and delete a specific node. The first argument is the main pointer we
will be using to traverse, the second argument is to update the list if
there is a deletion, and the third argument is the room number to delete. 
This function will return 0 if the room coulnd't be found, and return 1 if
the node was found and deleted.
*/
int ARR::remove_search(ARR_node * &head, ARR_node * &previous, int room_num)
{
	//If the node doesn't exist return.
	if(!head)
		return 0;

	//If the node is the room delete.
	if(head->same_room(room_num))
	{
		//If the room doesn't have a next pointer.
		if(!head->get_next())
		{
			//Delete head and return 1.
			delete head;
			head = nullptr;
			previous->set_next(nullptr);
			return 1;
		}
	
		//Delete head, update the list, and return 1.	
		ARR_node * hold = head->get_next();
		delete head;	
		head = hold;
		previous->set_next(hold);
		return 1;
	}
	
	//Recall the function with the next node.
	return remove_search(head->get_next(), head, room_num);
}

/*The purpose of this function is to search the array of linked lists and 
copy its informatio into the provided arguments. The room number, which is the 
first argument is what we will use to find the correct room. This is a wrapper
functionwhich will call a recursive function to assist in the repetitive part of
this problem. This function will return 0 if the room entered was invalid, and 
otherwise won't return 0 to show success.
*/
int ARR::retrieve(int room_num, int &connection, int &second_connection)
{
	int index{0}; //Set the initial index.

	//If the room entered is invalid.
	if(room_num == 0 || room_num >= 12)
		return 0;

	//Call the recursive function to find the node.
	return retrieve(index, room_num, connection, second_connection);
}

/*The purpose of this function is to recursively go through each index of 
the array of linked lists and check if any of the nodes match the one
trying to be retrieved. This function will do this by calling another 
recursive function to go through each element of the list to search the 
individual linked list. The first argument is the index use to get closer
to the base case, the second is the room number we are seraching for, and
the third and fourth arguments are the room numbers the room connects to. 
The function will return 0 if the node isn't found, and 1 if the node
was found.
*/
int ARR::retrieve(int index, int room_num, 
	          int & connection, int &second_connection)
{
	int find{0}; //Was the node found?

	//If the index is greater then the array size.
	if(index >= ARR_SIZE)
		return 0;

	//Call the function to search the element.	
	find = retrieve(lists[index], room_num, 
			    connection, second_connection);

	//If the element was found, return 1 to show success
	if(find == 1)
		return find;

	//Recall the function incrementing the index.
	return retrieve(++index, room_num, connection, second_connection);

}

/*The purpose of this function is to go through an individual linked list
and search it for the node trying to be retrieved. The first argument is the 
head pointer being used to traverse, the second is the room number being searched
for, and the third and fourth are the room numbers connected to the room. This 
function will return 0 if the node wasn't found, and return not 0 if the room 
was found and retrieved.
*/
int ARR::retrieve(ARR_node * head, int room_num,
		 int & connection, int &second_connection)
{
	int find{0}; //Was the node found?

	//If node doesn't exist.
	if(!head)
		return 0;

	//If the head is the room we are searching for.
	if(head->same_room(room_num))
	{
		//Copy the next room number if it exists.
		if(head->get_next())
			find = head->get_next()->copy_data(connection);
			
		//Copy the connecting room number if it exists
		if(head->get_connecting())
			find = head->get_connecting()->copy_data(second_connection);

		return 1; //Return 1 to show success.
	}
	//Call the function with the next node.
	return retrieve(head->get_next(), room_num, connection, 
			second_connection) + find;

}

/*The purpose of this function is to remove all the data in an 
array of linked lists. This is the wrapper function, so it is 
responsible for setting the starting index and calling the 
recursive function to go through each index. The fuction will
return 0 if the removal failed and return not 0 if the removal
was successful.
*/
int ARR::remove_all()
{	
	int index{0}; //Set the starting index.

	//Call the recursive remove all function.
	return remove_all(index);

}

/*The purpose of this function is to recursively go through each 
index of an array of linked list and remove each node. This function
does this by calling another recursive function to go through each 
node in an individual linked list and remove them. The functions argument
is the current index which will be used to go through each node. The
function returns 0 if the removal failed and returns not 0 if the 
removal was successful.
*/
int ARR::remove_all(int index)
{
	int clear_list{0}; //Did the list get cleared.

	//If the index is invalid return 0.
	if(index >= ARR_SIZE || index < 0)
		return 0;

	//Delete a certain list.
	clear_list = remove_all(lists[index]);	

	//Increment the index and recall the function.	
	++index;
	return remove_all(index) + clear_list;
}	

/*The purpose of this function is to delete an entire linked list
in an array of linked lists. The argument is a head pointer passed
by reference, which will be used to delete each node. The function
returns 0 if the deletion failed, and otherwise returns the number
of deleted nodes.
*/
int ARR::remove_all(ARR_node * &head)
{
	//If the node doens't exist.
	if(!head)
		return 0;

	//Hold the list and delete the node.
	ARR_node * hold = head->get_next();
	head->set_connecting(nullptr);
	delete head;
	head = hold;
	
	return remove_all(head) + 1; //Recall the function with a new head.
}

/*The purpose of this function is to add a connection to two nodes in 
an array of linked lists. The first argument is the room of the source 
node, and the second argument is the room of the destination node.
The function does this by calling function to find each node, and then
establishes a connectoin between them. The function returns 0 if 
the connection can't be made, and returns 1 otherwise.
*/
int ARR::add_connection(int src, int dest)
{
	int index{0}; //The starting index.
	
	//If the connection can't be made.
	if(src <= 0 || dest <= 0)
		return 0;

	//Find both nodes.
	ARR_node * src_location = find_room(index, src);
	ARR_node * dest_location = find_room(index, dest);

	src_location->set_connecting(dest_location); //Make the connection.

	return 1;
}

/*The purpose of this function is to make a complete copy of 
an array of linked lists. The argument for this function is 
an array of linked lists object, that will be used as the
source for the copy. This is a wrapper function and will
be responsible for checking if the object passed in exists,
and calls the recursive functions to handle the repetitive part of
this problem. This function returns 0 if the copy can't be complete,
and returns not 0 if the deep copy is successful
*/
int ARR::deep_copy(const ARR & src)
{
	int index{0}; //The initial start of the array.
	int set{0}; //Produces the copy.

	//Return if the source doesn't exist.
	if(!src.lists)
		return 0;

	//Initialize the data structure and start the copy.
	set = initialize(index);
	set = deep_copy(src, index) + set;
	return copy_connects(src); //Add the connections and return.
	
}

/*The purpose of this function is to go through each index of the
array of linked lists for the copy. The first argument is the array 
of linked lists being used as the source, and the second argument is
the index being used to get closer to the base case. This function
will return 0 if the index passed in is invalid, and otherwise will
return not 0 if the copy was successful. This function is also 
responsible for calling the recursive function to copy each node in 
the individual lists.
*/
int ARR::deep_copy(const ARR & src, int index)
{
	int copy_list{0}; //Was the list copied. 

	//Return if the index is invalid.
	if(index >= ARR_SIZE || index < 0)
		return 0;

	//Copy the index's linear linked list.	
	copy_list = deep_copy(src.lists[index], lists[index]);
	
	copy_list += deep_copy(src, ++index); //Recall the function with
					      //the next index.

	return copy_connects(src) + copy_list;
}

/*The purpose of this function is to perform a copy on each individual 
list. The first argument is a pointer to the source list to be copied, and
the second argument is a pointer to the new list that will be being updated.
This function will recursively go through each source node and perform a 
deep copy to produce a brand new list. This function will return 0 if 
no source was given, and will otherwise return a not 0 value.
*/
int ARR::deep_copy(const ARR_node * src, ARR_node * &dest)
{

	//If there is no source return 0.
	if(!src)
		return 0;

	//Create a new node with sources information.
	dest = new ARR_node(*src);
	int set_next = dest->set_next(nullptr); //Set the next pointer to nullptr.

	//If a connecting pointer exists create the connection.
	if(src->get_connecting())
	{
		int start = src->get_room();
		int end = src->get_connecting()->get_room();
		int connection = add_connection(start, end);
		if(connection == 0)
			return 0;
	}
	//Recall the function with the next pointers.
	return deep_copy(src->get_next(), dest->get_next()) + set_next;
}

/*The purpose of this function is to copy each of the connections between the 
nodes. The deep_copy recursive function creates the list with the next pointers,
but this function goes through to see if there is another connection between the
source nodes and make the copy if there is. This function returns 0 if no 
source list is given, and otherwise returns a non 0 value. The main 
responsibility of this function is to check if the source array of linked 
lists exists, and to call the recursive function to copy the connections. 
*/
int ARR::copy_connects(const ARR & src)
{
	int index{0}; //Initialize the starting index.

	//Return 0 if the source doesn't exist.
	if(!src.lists)
		return 0;

	//Call the function to go through each index.	
	return copy_connects(index, src);
}

/*The purpose of this function is to recursively go through each index of
the array of linked lists and call the recursive function to copy the 
connection. The first argument is the index being used to get closer to the base
case, and the second argument is the source array of linked lists. 0 will
be returned if the index given is invalid, and otherwise returns a non 0 
value.
*/
int ARR::copy_connects(int index, const ARR & src)
{
	//If the index is invalid return.
	if(index >= ARR_SIZE || index < 0)
		return 0;

	//Go through each node in the list.
	int connects = copy_connects(src.lists[index]);

	//Recall the function with the next index.
	return copy_connects(++index, src) + connects;

}

/*The purpose of this function is to copy each connection from the source 
into the new object. The argument is the array of linked list node
that will be used as the source for the copies and to traverse 
the list. The function will return 0 if the source doesn't exist, and
will otherwise return a non 0 value..
*/
int ARR::copy_connects(const ARR_node * src)
{
	int connection{0};  //Was the connection added.

	//Return if the source doesn't exist.
	if(!src)
		return 0;

	//Copy each connection
	if(src->get_connecting())
	{
		//Get the connection rooms
		int start = src->get_room();
		int end = src->get_connecting()->get_room();
		connection = add_connection(start, end); //Add the connection.

		//Return if the connection failed.
		if(connection == 0)
			return 0;
		
	}
	//Recall the function with the next node.
	return copy_connects(src->get_next()) + connection;
}

/*The purpose of this function is to find a specific room within 
the array of linked lists. The first argument is the index to search
which will be used to recursively go from index to index, and the second
argument is the room number trying to be found. This function will return 
a nullptr value if no match could be found, and otherwise returns the 
correct node being searched for.
*/
ARR_node *ARR::find_room(int index, int room_num)
{
	ARR_node * match = nullptr; // A temporary to hold the node.

	//If the index is invalid return.
	if(index >= ARR_SIZE || index < 0)
		return match;

	//All the function to go through a list.
	match = find_room(lists[index], room_num);
	
	//If the match was found return the node.
	if(match)
		return match;

	//Recall the function with next index.	
	return find_room(++index, room_num);
}

/*The purpose of this function is to go through a linked list
and check to see if a room can be found. If the room is found in the 
list, the funciton will return the node that matches the room number being
passed in as an argument. If the node can't be found no node is returned, 
and if the node is found that specific node is returned.
*/
ARR_node *ARR::find_room(ARR_node * head, int room_num)
{
	//If the node doesn't exist, return.
	if(!head)
		return head;

	//If the room matches return the node.
	if(head->same_room(room_num))
		return head;

	//Recall the function with the next node.
	return find_room(head->get_next(), room_num);
}

/*The purpose of this function is to simulate movement throughout
the data structure. This involves properly updating the location 
pointer so the user will be in an updated spot. By doing this, 
it appears that the user is moving through the data structure,
but in the code we are actually just updating a pointer.
*/
int ARR::move(int direction)
{
	//Check for invalid input
	if(!location)
		return -2;

	if(direction != 1 && direction != 2)
		return -2;

	//Move left.
	if(direction == 1)
	{
		if(!location->get_next())
		   return -1;  

		else
		   location = location->get_next();
	}
	
	//Move Right
	if(direction == 2)
	{
		if(!location->get_connecting())
		   return -1;
		else
		   location = location->get_connecting();
	}

	//Check if the maze is done.
	if(location->get_room() == 12)
		return 0;

	return 1; //Return 1 to show success.
}
