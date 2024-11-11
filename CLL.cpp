//Cody Hathcoat		October 21st, 2024 	Program #1	CS302

#include "Attendee.h"

/*The purpose of this file is to handle all of the implementation of the 
circular linked list, which will be the haunted house for the Kid. This involves
having the implementation for the nodes class methods. Also, this file will
implement the circular linked list management class as well. This means this
class is what allows the circular haunted house to be built, destroyed, retrieve,
and be copied.*/


/*The purpose of this default constructor is to initalize the data members
of a circular linked list node. This involves setting the room number to 0,
the location of the candy to 0, and setting the next pointer to nullptr. This 
essentailly sets all the data members to their 0 equivalent values by using 
an initializaiton list.
*/
CLL_node::CLL_node() : room_num(0), candy_location(0), next(nullptr)
{}

/*The prupose of this argument constructor is to create a CLL_node with arguments which 
are entered in as the arguments. This sets the room numbera and the candy location, and
automatically sets the next pointer to nullptr. This allows for a CLL_node to be created
with information entered in, and isn't reliant on the copy constructor. All of the 
initialization is handled in the initializaiton list.
*/
CLL_node::CLL_node(int a_room, int a_location) : room_num(a_room), candy_location(a_location), 
					 	 next(nullptr)
{}

/*The purpose of this destructor is to release all the dynamic memory that is within a 
circular linked list node. Since the node only manages the next pointer, all this 
destructor needs to do is delete the next pointer and set it to nullptr.
*/
CLL_node::~CLL_node()
{
	next = nullptr;
}

/*The purpose of this function is to set the next pointer for a CLL_node. The function does 
this by using the argument passed in and updates the next pointer for the node. Since the 
next pointer is private, this allows us to keep updating the list and set the next 
pointers where we need.
*/
int CLL_node::set_next(CLL_node * new_next)
{
	//Update the value of next
	next = new_next;
	return 1;
}

/*The purpose of this function is to get the next pointer for a CLL_node. Since we aren't
structures for our nodes, this getter helps us access the next pointer. This will help 
in every recursive function where we need to traverse using the next pointer. This function 
returns a CLL_node, which is always the next pointer.
*/
CLL_node *& CLL_node::get_next()
{
	return next;

}

/*The purpose of this function is to get the next poitner for a CLL_node in a safe
secure manner. The const key word means this fucntion won't accidentally change the 
node itself or the node being pointed to. This means the function will only 
access and return the next pointer.
*/
const CLL_node * CLL_node::get_next() const
{
	return next;
}

/*The purpose of this function is to display the information inside a node.
This involves showing the room number, as well as the candy location. This could
be thought of as like a cheat-sheet map to show an attendee where all of the candy
is located. The candy location is an integer value, so each integer value represents
a specific location of where the candy could be. This function returns 0 if 
the data hasn't been registered, and returns 1 if the information was displayed.
*/
int CLL_node::display_data() const
{
	//If there is no information, return 0.
	if(room_num == 0 || candy_location == 0)
		return 0;

	//Output the roo number
	cout << "Room number " << room_num << endl;

	//Say where the candy is based off the integer.
	if(candy_location == 1)
		cout << "Candy Location: Under the chair.\n" << endl;

	else if(candy_location == 2)
		cout << "Candy Location: By the ghost.\n" << endl;

	else
		cout << "Candy Location: In the Pumpkin.\n" << endl;

	return 1; //Return 1 to show success.
}

/*The purpose of this function is check and see if the integer argument
being passed in matches the nodes room number. This function has a 
boolean return type. The function will return true if the number sent
in as an argument matches the room number, and otherwise will return 
false.
*/
bool CLL_node::is_room(int a_room)
{
	//Check if the room numbers match, if so return true.
	if(room_num == a_room)
		return true;

	return false; //Return false since there isn't a match.
}

/*The purpose of this function is to copy the data from a CLL node into
the arguments being passed in. If the node does not have it's data
members set, the function simply returns 0. If the node does have it's
data members set, it copies them into the arguments and returns 1 to show
success.
*/
int CLL_node::copy_data(int &to_copy_room, int &to_copy_location)
{
	//Check if the data members have been set.
	if(room_num == 0 || candy_location == 0)
		return 0;

	//Copy the data members.
	to_copy_room = room_num;
	to_copy_location = candy_location;

	return 1; //Return 1 to show success.
}

/*The purpose of this function is to determine if the location a kid searches 
in has candy in it. This function used the integer argument passed in, and checks
to see if it doesn't match the stored location in the node. If the argument doesn't
match or is invalid, the function returns false, and otherwise returns false.
*/
bool CLL_node::is_candy(int a_location)
{
	if(a_location < 1 || a_location > 3 || a_location != candy_location)
		return false;

	return true;
}
/*The purpose of this constructor is to set the data member of the 
circular linked list to its 0 equivalent value. This means the 
rear pointer is initialized to nullptr. This all is handled in the 
initialization list.
*/
CLL::CLL() : rear(nullptr), location(nullptr)
{}

/*The purpose of this destructor is to destroy all of the dynamic memory
within the circular linked list. Since the circular linked list has a 
vast collection of nodes, there is a good amount of memory that needs to 
be deallocated. This destructor makes use of the remove_all function, and 
calls it to destroy all of the circular linked list.
*/
CLL::~CLL()
{
	remove_all(); //Destroy all nodes.

}

/*The purpose of this copy constructor is to copy all 
of the data that is being passed in as an argument into 
the current circular linked list. This essentailly will 
create a brand new circular linked list that is identical
to the one passed in as an argument. This constructor is 
able to make use of the dee_copy function, and call it to 
perform the copy needed. It is important to note the rear
pointer is initialize to nullptr in the initialization list
to make sure it has been set.
*/
CLL::CLL(const CLL & to_copy) : rear(nullptr)
{
	deep_copy(to_copy);	//Copy the entire list.

}

/*The purpose of this assignment operator is to overload the 
assignment operator since the circular linked list class manages
dynamic memory. This will allow the user to use the assignment 
operator to assign values of circular linked list objects. 
The argument for this function is the source for the 
circular linked list that is going to be copied. The 
function returns the current object.
*/
CLL & CLL :: operator=(const CLL & src)
{
	int help{0}; //Used to "catch" recursive returrns.

	//Check for self assignment.
	if(this == &src)
		return *this;

	//Delete any existing memory.
	if(rear)
	{
		help = remove_all();

		if(help == 0)
			return *this;
	}

	//Perform a deep copy
	help = deep_copy(src);

	return *this; //Return the current object.
}

/* The purpose of this function is to display the entire 
circular linked list. This function has an integer return 
type, and will return 0 if the rear is nullptr, meaning the 
list is empty. Otherwise, the function passes in the front 
of the list into the recursive function to handle the repetive 
aspects of this task. The return of the recursive function is 
then returned in this wrapper. Also, the const key word in 
this case says we won't change the list since we are only 
displaying.
*/
int CLL::display() const
{
	//Make sure the list exists.
	if(!rear)
		return 0;

	//Return and call the recursive function.
	CLL_node * r_next = rear->get_next();
	return display(r_next);
}

/*The purpose of this function is to use recursion to 
display the entire circular linked list. The argument of
this function is a circular linked list pointer which allows
us to call the function again recursviely to get to our next
smaller sub-problem. The function makes use of the CLL_node's
display_data function, and calls it with each recursive call.
The const keyword assures the program that this function
won't change anything in the list, just display the information.
*/
int CLL::display(CLL_node * rear) const
{
	int show{0}; //"Catch" function calls.

	//Check the base case.
	if(rear == this->rear)
	{
		//Show the last items data.
		show = rear->display_data();
		if(show == 0)
			return -1; //Return -1 incase of failure
	
		return 1; //Return 1 to show success
	}
	
	//Show the current nodes data.	
	show = rear->display_data();

	if(show == 0)
		return -1; //Return -1 incase of failure
	
	//Recall the function getting closer to the base case.	
	return display(rear->get_next()) + 1;
}

/*The purpose of this function is to insert an item into 
the circular linked list. The arguments are two integers, 
which represent the candy location and the room number.
The function uses this information to insert it into 
the circular linked list. This function will always 
insert at the start of the list to allow for effective
runtime performance.
*/
int CLL::insert(int candy, int room)
{
	//Chech if the rear exists.
	if(!rear)
	{
		//Create the node at the rear.
		rear = new CLL_node(room, candy);
		rear->set_next(rear);
		return 1;
	}
	
	//Create the node and set it at the start of the list.
	CLL_node * hold = new CLL_node(room, candy);
	hold->set_next(rear->get_next());
	rear->set_next(hold);
	rear = hold;
	return 1; //Return 1 to show success.
}

/*The purpose of this function is to build the entire 
circular linked list for the use of the haunted house for
this program. This is a wrapper function, which means its
recursive function will be called to take care of the 
repetitive part of this process. This function sets the 
initial room number to 1, and then returns the return value of
the recursive function.
*/
int CLL::build()
{
	int room_num{1}; //Set tothe first room number
	int create = build(rear, room_num); //Call the recursive function.
	
	if(!rear)
		return 0;
	
	else
		location = rear->get_next();

	return create;
}

/*The purpose of this function is to take care of all the 
repetitive work to build the circular linked list for this 
haunted house. The functions first argument is the rear pointer
of the list, as well as the room number. This function will use the 
room number to create a number of nodes, in this case 9, which 
will act as a haunted house. The function does this by incrementing
the room number with each call. Also, this function sets the candy
location to a completely random area. The function returns 0 if
the list was made, and otherwise returns a positive integer.
*/
int CLL::build(CLL_node * &rear, int &room_num)
{
	//If the base case is reached, return.
	if(room_num == 10)
		return 0;

	//Generate a random numbe between 1 and 3.
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution (1, 3);
	int candy_location = distribution(generator);

	//Enter the information in the node.
	int enter = insert(candy_location, room_num);
	++room_num; //Update the room number

	//Recall the function with the updated room.
	return build(rear, room_num) + enter;
}

/*The purpose of this wrapper function is to handle
the removal of an item from the circular linked list.
The function is also responsible for calling the recursive
function to handle the repetitive aspects of this problem. 
The argument of this function is the room number the user
wants to remove. The function will return 0 if the 
removal couldn't happen, and will otherwise return a positive
number.
*/
int CLL::remove(int room_number)
{
	//Check if the list exists.
	if(!rear)
		return 0;
	
	//Check if there is only 1 node.
	if(rear->get_next() == rear)
	{
		//Check if the 1 node is the node to delete.
		if(rear->is_room(room_number))
		{
			//Delete and return 1 to show success.
			delete rear;
			rear = nullptr;
			return 1;
		}
		return 0; //Return 0 to show failure.
	}

	//Call the recursive function and return the result.
	return remove(rear->get_next(), rear, room_number);	

}

/*The purpose of this function is to handle the repetitive aspects
of removing a node from a circular linked list. The arguments of this 
functio is the a pointer to search with, a previous pointer to connect
the list if a node is delete, and the room number wanting to be deleted.
The function will return 0 if the node couldn't be deleted, and will 
otherwise return 1. 
*/
int CLL::remove(CLL_node * &rear, CLL_node * &previous, int room_num)
{
	//Check the list exists.
	if(!rear)
		return 0;

	//Check for a 1 node list.
	if(rear == this->rear)
	{
		//Does the 1 node match.
		if(rear->is_room(room_num))
		{
			//Delete the node and return 1.
			previous->set_next(rear->get_next());
			delete rear;
			this->rear = previous;
			return 1;
		}
		return 0; //Return 0 to show failure.
	}
	
	//If the node matches.	
	if(rear->is_room(room_num))
	{
		//Update the previous next pointer, and then delete.
		int did_set = previous->set_next(rear->get_next());
		delete rear;
		return did_set;
	}		
	//Recall the function with updated nodes.
	return remove(rear->get_next(), previous->get_next(), room_num);

}

/*The purpose of this function is to find a node in the circular linked
list by searching for its room number. The first argument is the room
number the user wants to find, and the second argument the number that
represents the candy location. This essentailly is a cheate function and 
shows where the candy is located in the room. This is a wrapper function
so its purrpose is to check if the list exists and then call the recursive
function to handle the repetitive work. This function will return 0 if
the node wasn't found, adn otherwise will return 1.
*/
int CLL::retrieve(int &room_number, int &candy_location)
{
	//Check that the list exists
	if(!rear)
		return 0;
	
	//Call the recursive function.
	return retrieve(rear->get_next(), room_number, candy_location);
}

/*The purpose of this function is to find a node in the circular link 
list by searching for its room number. This is a recursive function that 
will be called by its wrapper function. The first argument is a circular 
linked list node pointer that will be used to traverse the list. The 
second argument is the desired room number and the third is the candy 
location represented by an integer. The function will return 0 if 
the node wasn't found, adn otherwise will return 1.
*/
int CLL::retrieve(CLL_node * rear, int &room_number, int &candy_area)
{
	//Check the list exists.
	if(!rear)
		return 0;
	
	//Check if the room number matches.
	if(rear->is_room(room_number))
	{
		//Copy the data if found.
		int did_copy = rear->copy_data(room_number, candy_area);
		if(did_copy == 0) //Did the copy actually happen?
			return 0;

		return 1; //Return 1 to show success.
	}

	//If the whole list has been traversed.
	if(rear == this->rear)
		return 0;	

	//Recall the function with the next smaller sub-problem.	
	return retrieve(rear->get_next(), room_number, candy_area);
}

/*The purpose of this function is to remove all of the data in 
the circular lined list. This function is a wrapper function, 
so it is responsible for checking that the list exists, and 
for calling the recursive function. The function also is 
responsible for breaking the circular linked list turning 
it into a linear linked list to allow for an easier removal.
This function returns 0 if the list couldn't be deleted, and 
otherwise returns the number of deleted nodes.
*/
int CLL::remove_all()
{
	//Check the list exists
	if(!rear)
		return 0;

	//Turn the CLL into a LLL
	CLL_node * hold = rear->get_next();
	int did_set = rear->set_next(nullptr);

	//Call the recursive function and return.
	did_set += remove_all(hold) - 1;
	rear = nullptr;
	return did_set;
}

/*The purpose of this funcion is to remove all of the 
nodes in a circular linked list. This function is a
recurisve function, and is called by its wrapper function.
This functions argument is a circular linked list node
passed by reference to allow for deletion. This function 
will return 0 if the deletion fails, and otherwise returns
the number of nodes deleted.
*/
int CLL::remove_all(CLL_node * &current)
{
	//Check the base case.
	if(!current)
		return 0;
	
	//Hold the next node and delete/update the current.
	CLL_node * hold = current->get_next();
	delete current;
	current = hold;
	return remove_all(current) + 1; //Recall the function.
}

/*The purpose of this function is to perform a deep copy of
the circular linked list. This essentailly means the brand new 
list is going to be made using the circular linked list object
passed in as an argument. This is a wrapper function, so it
handles the non-repetitive aspects of this task, and will call
the recursive function if needed. The function returns 0 if a
copy couldn't be made, and otherwise returns a positive number.
*/
int CLL::deep_copy(const CLL & to_copy)
{
	int count{0}; //Holds function calls.

	//If the list to copy doesn't exist.
	if(!to_copy.rear)
		return 0;
	
	//If the list to copy is only 1 node.	
	if(to_copy.rear->get_next() == to_copy.rear)
	{
		//Copy the node.
		rear = new CLL_node(*to_copy.rear);
		int connect = rear->set_next(rear);
		return connect;
	}

	//If the list being created doesn't exist.
	if(!rear)
	{
		rear = new CLL_node(*to_copy.rear);
		count += rear->set_next(rear);
	}
	
	//If the list to be copied points to itself.
	if(rear->get_next() == rear)
	{
		//Copy the first item in the list.
		CLL_node * first = new CLL_node(*to_copy.rear->get_next());
		count += first->set_next(rear);
		count += rear->set_next(first) - 1;
	}
	//Call the recursive function and return.
	return deep_copy(to_copy.rear->get_next()->get_next(), rear->get_next(), to_copy.rear) + 1;
}

/*The purpose of this function is to perform a deep copy, which will create a 
brand new copied list. This function first argument is the current poitner of the function
being copied, while the second is the current pointer for the new list. The third argument
is the rear of the list being copied so the function can know when the copy is finished. 
This function will return 0 if no copy can be made, and will otherwise return a positive number.
*/
int CLL::deep_copy(const CLL_node *to_copy_curr, CLL_node * &curr, const CLL_node * src_rear)
{
	//Base case.
	if(to_copy_curr == src_rear)
		return 0;
	
	//Create a copy of the node and set the pointers.
	CLL_node * create = new CLL_node(*to_copy_curr);
	int set = create->set_next(this->rear);
	set += curr->set_next(create);

	//Recall the function with the smaller sub-problem.
	return deep_copy(to_copy_curr->get_next(), curr->get_next(), src_rear) + 1 + set;
}

/*The purpose of this function is to allow movement throughout the data structure.
The function will update the current location pointer to simulate movement through 
the nodes in the circular linked list. If the location pointer is at the end of the
list, the function will return false since the child is at the last room, and 
otherwise updates the pointer and returns true.
*/
bool CLL::move(Kid & current_info)
{
	if(location == rear)
		return false;

	location = location->get_next();

	return true;
}

/*The purpose of this function is to check the current rooms candy location.
If the argumenet passed in matches the locations hiddenn candy area, the 
function will return true with the help of the is_candy() function.
If the location pointer is set to nullptr or the location is wrong,
the function will return false.
*/ 
bool CLL::check_for_candy(int search_location)
{
	if(!location)
		return false;

	return location->is_candy(search_location);
}
