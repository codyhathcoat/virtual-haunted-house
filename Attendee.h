//Cody Hathcoat 	October 21st, 2024 	Program #1 	CS302

/*The purpose of this .h file is to outline the core hierarchy for the program. 
This means within the file, there will be classes outlining the main work of
what is going into this program. This includes an attendee class, which will be 
the base class for its derived classes, which will include a kid, adult and dog 
class. The base class will hold the similarities between the 3 attendees, such as
thier name and age, while the derived classes will contain the information unique
to the particular attendee. Also outlined in this file, is the data structures 
that will be used to create the haunted houses. This includes a circular linked
list, a circular linked list node, an array of linked lists with a linked list
node class, as well as a class to maintain the vector. These data structures
will be used to support the haunted house experience for the individual attendees.
*/


#include <iostream>
#include <cctype>
#include <string>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
using namespace std;

const int ARR_SIZE {4}; //The size of the array for the array of linked lists

/*The purpose of this class is to act as a base class for the derived classes
which are Adult, Kid, and Dog. Since this is a base class, its purpose is to 
hold the commonalities that have been pushed up from derived classes. This 
includes the name and age of the attendees.
*/
class Attendee
{

	public:
		Attendee(); 		//Default constructor

		Attendee(string &a_name, int a_age);	//Argument constructor

		Attendee(const Attendee & to_copy); //Copy constructor

		~Attendee();    //Destructor to deallocate dynamic name

		Attendee & operator=(const Attendee &src); //Assignment Operator

		int display() const; //Displays the name and age.

	protected:
		char * name; 	//How to address the attendee
		int age;	//How old the attendee is
};

/*The purpose of this derived class is to handle the case where the 
attendee is an adult. This is why this class is derived from the
attendee class. This class allows an adult to move through a maze,
be jump scared by a skelton, and register how scared they are.  
*/
class Adult : public Attendee
{
	public:
		Adult(); 	//Default constructor
	
		Adult(string &a_name, int a_age, int set_scare);  //Argument constructor

		~Adult();	//Destructor to set data to 0 equivalent value

		int display_adult() const;	//Shows the adults scare level.

		int react(int scare);  //Updates the adults current scare level.

		bool is_skeleton();   //Determines wheather an adult is jump scared.

		int take_break(int rest_time); //Allows the adult to catch their breath, lowering their scare level.				

		int ask_help() const;   //Allows the adult to call for help to get random advice.

	protected:
		int scare_level;	//How scared an adult was on a scale of 1-10 
};

/*The purpose of this class is to handle when the attendee is a child, which
is why the Kid class is derived from the Attendee class. This kid class has 
a default constructor, as well as a copy construction since it handles 
dynamic memory, which is also why the class has a destructor. This class 
allows a child to search for candy, enter a quote about their experience, 
and continue through pathway. 
*/
class Kid : public Attendee
{
	public:
		Kid();			//Default constructor

		Kid(string &a_name, int a_age, const string & a_quote, int some_candy); //Argument constructor.

		Kid(const Kid & to_copy);  //Copy Constructor

		~Kid();			//Destructor to deallocate dynmic memory
		
		Kid & operator=(const Kid &src);  //Assignment operator

		int display_kid() const;		//Shows the kids memorable quote.

		int pick_up_candy(int search); //Allows the child to update their found candy
	
		int register_quote(const string & kid_quote); //Allows the kid to submit a quote.

		int share_candy(int candy_to_share); //Kid gives some candy to a friend.		
		
		bool drop_candy(); //Randomly determines if kid loses some candy.

	protected:
		char * quote; 	//A memorable expression from the child for feedback
		
		int candies; 	//The number of treats collected.
};

/*The purpose of this class is to handle the haunted house when a dog is
the attendee, which is why the dog class is derived from the attendee class.
This class allows the dog to dodge obstacles that appear, sniff for treats,
and continue through the path.
*/
class Dog : public Attendee
{
	public:
		Dog();		//Defualt constructor.
	
		Dog(string &a_name, int a_age, int some_treats); //Argument contructor.

		~Dog();		//Destructor to set data to its 0 equivalent value

		int display_dog() const;	//Shows how many treats the dog found.

		int dodge_obstacle(int reaction) const; //How does the animal avoid a roadblock

		int sniff_treats(int time_sniffing, int room_treats); //Try and find treats for a certain time

		int eat_treats(); 		//Eats a random amount of found treats.	
	
	protected:
		int treats; 	//The number of snacks the dog found
};

/*This class's purpose is to manage the information that will be in 
the circular linked list for the kid haunter house. This class is able to
set and get next pointers, as well as a copy constructor since it manages 
dynamic memory. Each node will have a key to represent a candy location for
the kid to try and find.
*/
class CLL_node : public Kid
{
	public:
		CLL_node(); 		//Defualt constructor.

		~CLL_node();  			//Destructor

		CLL_node(int a_room, int a_location); //Argument constructor

		int set_next(CLL_node * new_next); //Set the next pointer.

		CLL_node *& get_next(); 	//Access the next pointer

		const CLL_node * get_next() const; //Set the next pointer when const/

		int display_data() const;    //Show the data to the user.

		bool is_room(int a_room);  //Does the current room match the argument.

		int copy_data(int &to_copy_room, int &to_copy_location); //Copy the arguments
									 //in the node.
		bool is_candy(int a_location); //Is there candy at the location?

	private:
		int room_num;		//Room identification.

		int candy_location;   	//Where the candy is hidden.

		CLL_node * next;    	//A pointer to the next node.

};

/*The prupose of this class is to manage the kid haunted house,
which will be using a circular linked list. This class will allow an 
object to display, insert, create, delete, find, and destroy. This CLL has
a rear pointer which will be used to keep track of the list.
*/
class CLL
{
	public:
		CLL(); 		//Default constructor

		~CLL();  	//Destruction 

		CLL(const CLL & to_copy); //Copy Constructor

		CLL & operator=(const CLL & src); //Assignment operator

		int display() const; 	//Show all entries in the list.

		int insert(int candy, int room);   //Insert a single item.

		int build();    //Build the entire list.

		int remove(int room_number);   //Remove a node.

		int retrieve(int &room_number, int &candy_location); //Find a node.

		int remove_all(); //Destroy the list.

		int deep_copy(const CLL & to_copy);  //Copies the whole list

		bool move(Kid & current_info); 	     //Updates the Kids location.

		bool check_for_candy(int search_location); //Searches for candy.

	private:
		CLL_node * rear;  //A pointer to the end of the list.

		CLL_node * location;	//Points to the Kid's current node.

		//Does the recursive work to insert.
		int insert(int room_number, int candy_location, CLL_node * &rear); 

		//Recursively builds the whole list.
		int build(CLL_node * &rear, int &room_num);
	
		//Recursively finds and deletes the the correct node.	
		int remove(CLL_node * &rear, CLL_node * &previous, int room_num);

		//Display all the data recursively.
		int display(CLL_node * rear) const;

		//Find a node in the list and copy over the data.	
		int retrieve(CLL_node * rear, int &room_number, int &candy_location);
	
		//Delete the whole list.	
		int remove_all(CLL_node * &current);
		
		//Deep copy the entire list.	
		int deep_copy(const CLL_node *to_copy_curr, CLL_node * &curr, const CLL_node * src_rear);
};
/*The purpose of this class is to manage the nodes in the array of 
linked lists. This class is derived from the Adult class since it 
will be a part of the adult's haunted house maze. This class 
can set pointers, get th next pointer, as well as the necessary
constructors.
*/
class ARR_node : public Adult
{
	public:
		ARR_node(); 			   //Default constructor

		ARR_node(int room);          //Set the data member.

		~ARR_node();			  //Destructor

		int set_next(ARR_node * new_next); //Set the next pointers.

		int set_connecting(ARR_node * connecting); //Set the connecting pointer.

		ARR_node *& get_next();            //Getter for the next pointer.

		const ARR_node * get_next() const; //Set the next pointer when const/

		ARR_node *& get_connecting();      //Getter for the connect pointer.

		const ARR_node * get_connecting() const; //Set the next pointer when const/

		int display_data() const; 		//Shows the rooms data.

		int show_connection(ARR_node * connect,          //Shows a rooms connection data.
				    ARR_node * second_connect) const;	

		bool same_room(int room_num);   //Checks if the room entered is the same.

		int copy_data(int &room);   //Copies the data from the room.

		int get_room() const;   	//Returns the room number

	private:
		int room_number;    	    //The room identifier
		ARR_node * next;	    //The next room in the data structure.
		ARR_node * connecting_room; //The second connecting room
};

/*The purpose of this class is to manage the adult haunted house.
This will allow a class object to show all rooms, create a room,
build the maze, remove a room, find a room, remove all rooms,
and add a connection between the rooms. 
*/
class ARR
{
	public:
		ARR();  		    //Default constructor.
	
		~ARR();  		    //Destructor to deallocate dynamic memory.

		ARR(const ARR &to_copy);    //Copy Constructor

		ARR &operator=(const ARR & src); //Assignment operator

		int initialize(int index); 	 //Initialize the list

		int insert(float room_num);   //Creates a room.

		int build();    	    //Builds the maze.

		int display() const;  	    //Shows all rooms and their connections.

		int remove(int room_num);   //Destroys a room.

		int retrieve(int room_num, int &connection, //Find a room and what it
			     int &second_connection); 	    //connects to.

		int remove_all(); 	    //Destroys the maze.

		int add_connection(int src, int dest); //Connects two rooms.

		int deep_copy(const ARR & src);	       //Copy an entire array of linked lists

		int move(int direction); 	     //Updates the location pointer.

	private:
		ARR_node **lists;  //The pointer to the array of linked lists.

		ARR_node * location; //Where the adult is located.
	
		int location_index; //What index the adult is in.

		int insert(int index, ARR_node * &head, int room_num);  //Recursively inserts a room
	
		int display(int index) const;  	//Recursively displays using the index.
		
		int display(ARR_node * head) const; //Recursively displays using the head pointer.

		int build(float room_num);  //Recursively build the data structure. 

		int remove_search(int index, int room_num); //Search for the index with the node to remove

		int remove_search(ARR_node * &head, ARR_node * &previous, int room_num); //Search the list for
											 //the index to remove.
	
		int retrieve(int index, int room_num,  			//Recursively find the desired room
		 	     int & connection, int &second_connection); //using the index.

		int retrieve(ARR_node * head, int room_num,             //Recursively find the desired room
		             int &connection, int &second_connection);  //using a list.

		int remove_all(int index);   		//Remove all the data in each index.

		int remove_all(ARR_node * &head);      //Remove all the data in each list.

		int deep_copy(const ARR & src, int index); //Deep copy each index.

		int deep_copy(const ARR_node * src, ARR_node * &dest); //Deep copy each list.

		ARR_node *find_room(int index, int room_num);    //Find a room using the index.

		ARR_node *find_room(ARR_node * head, int room_num); //Find a room in a list.
	
		int copy_connects(const ARR & src);                 //Copy the connections from a source.

		int copy_connects(int index, const ARR & src);    //Copy the connections by index.

		int copy_connects(const ARR_node * src);        //Copy the connections by the nodes.
};

