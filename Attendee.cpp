//Cody Hathcoat 	October 21st, 2024 	Program #1 	CS302

#include "Attendee.h"

/*The purpose of this file is to handle the implementation of the
core hierarchy for this program. This involves handling the 
base Attendee class, as well as its derived classes. This means 
this file is responsible for all of the core hierarchy's constructors,
destructors, and the copy constructors and assignment operators if 
the class manages dynamic memory. This file also has the implementation
of all the public methods for each derived class, which allows the 
specific attendee to interact with their haunted experience.
*/


/*The purpose of this default constructor is to set the 
data members of the Attendee class to their 0 equivalent 
valuse. This involves setting the name to nullptr and the 
age to 0. This can all be done in the initialization list.
*/
Attendee::Attendee() : name(nullptr), age(0)
{}

/*The purpose of this argument constructor is to create an attendee
with the name and age passed in as arguments. The age is set in 
the initialization list, and the name is set in the body since
the name needs to be dynamically sized.
*/
Attendee::Attendee(string &a_name, int a_age) : age(a_age)
{
	//Allocate and copy the name
	name = new char[a_name.length() + 1];
	strcpy(name, a_name.c_str());
}

/*The purpose of this copy contructor is to perform a deep 
copy of a Attendee class object. This is necessary since the 
Attendee class is managing dynamic memory. The argument is 
the Attendee object we want to copy, and the age is copied 
in the initilization list. The function then needs to 
size and copy the name.
*/
Attendee::Attendee(const Attendee & to_copy) : age(to_copy.age)
{
	if(to_copy.name) 	//Check if the copy name exists
	{
		name = new char[strlen(to_copy.name) + 1];
		strcpy(name, to_copy.name);
	}
	else
		name = nullptr; //Set name to null if the copy isn't named.
}

/*The purpose of this destructor is to delete all dynamic
memory, and set all data members in the Attendee class
to their 0 equivalent values. This involves deleting
name and setting it to nullptr, as well as setting 
the age to 0.
*/
Attendee::~Attendee()
{
	//Delete name if it exists
	if(name)
	{
		delete [] name;
		name = nullptr;
	}
	age = 0;
}

/*The purpose of this assignment operator is to allow
1 Attendee object to be copied into another. Since the 
Attendee class manages dynamic memory, this class must 
have an assignment operator. This allows for the assignment
operator to be used for an Attendee object, and is able to 
perform a deep copy, making sure the program won't have 
memory leaks.
*/
Attendee & Attendee::operator=(const Attendee &src)
{
	//Check for self assignment
	if(this == &src)
		return *this;

	//Deallocate memory of the current object
	if(name)
	{
		delete [] name;
		name = nullptr;
	}

	//Deep copy
	name = new char[strlen(src.name) + 1];
	strcpy(name, src.name);
	age = src.age;

	return *this; //Return current object
}

/*The purpose of this function is to display the contents
of a Attendee object. This means the persons name and age
are outputted to the user. The function returns 0 if a name
has not been entrered, and 1 if the name and age are displayed.
*/
int Attendee::display() const
{
	//Output the name if it exists
	if(name)
		cout << "Name: " << name << endl;

	//Display nothing if there's no name.
	else 
		return 0; 

	cout << "Age: " << age << endl;
	return 1;
}

/*The purpose of this constructor is to intitalize the
data members for an adult object. Since there is one 
data member, all we have to do is set the scare level
to 0. This can be done in the initialization list.
*/
Adult::Adult() : scare_level(0)
{}

/*The purpose of this contructor is to initialize the 
data members for an adult object when being created with 
a set scare level. This sets the scare level to the desired
value by using an initialization list. 
*/
Adult::Adult(string &a_name, int a_age, int set_scare) : Attendee(a_name, a_age), scare_level(set_scare)
{}

/*The purpose of destructor is to set the data member
for an Adult object to its 0 equivalent value. This means
the scare level is set to 0.
*/
Adult::~Adult()
{
	scare_level = 0;
}

/*The purpose of this function is to display an adult
attendee's current scare level. This is something that
will be affected by the number of jump scares from the 
skeletons. This function simply shows that level to 
the user.
*/
int Adult::display_adult() const
{
	Attendee::display();
	//Show the scare level.
	cout << "Your scare level is currently " << scare_level 
	     << " out of 10." << endl;

	return 1;
}

/*The purpose of this function is to update the adults 
scare level. This function simply does this by taking the 
integer argument and adding that to their current scare level.
*/
int Adult::react(int scare)
{
	//Don't allow the scare level to go over 10.
	if(scare_level + scare > 10)
	{
		scare_level = 10;
		return 10;
	}

	//Increase the scare level
	scare_level += scare;
	return scare_level;
}

/*The purpose of this function is to determine if an adult is 
jumpscared by a skeleton. This function does this by using the 
adults scare level, the lower the scare level, the more likely 
an unexpecting guest will be jump scared. This function returns
false if there is no jump scare, and false if there is 
a jump scare. 
*/
bool Adult::is_skeleton()
{
	//Generate a random number between 1 and 10
	if(scare_level == 10)
		return false;
	
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 	
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution (0, 10);
	int random_num = distribution(generator);

	//More likely to show a skelton the lower the scare level.
	if(random_num > scare_level)
		return true;

	return false;
}

/* The purpose of this function is to allow the adult to take 
a break, lowering their scare level. This is done by asking
the adult how long they want to rest for. This number is then 
modded by the current scare level, and is then subtracted from
the scare level, updating it, and then returning the value.
*/
int Adult::take_break(int rest_time)
{
	if(scare_level == 0)
		return 0;

	//Mod the rest time by the scare level so 
	//the scare level isn't negative.
	rest_time %= scare_level;
	scare_level -= rest_time;	
	return scare_level;
}

/*The purpose of this function is to allowt the adult to 
phone a friend and ask for advice on where to go. Your 
friend isn't very reliable, and gives you completely 
random advice wheather to turn left of right. 
*/
int Adult::ask_help() const
{
	//Generate a random number between 1 and 2

	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 	
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution (1, 2);
	int random_num = distribution(generator);

	if(random_num == 1)
		cout << "I think you should go left." << endl;
	else 
		cout << "I think you should go right." << endl;
	
	return 1;
}

/*The purpose of this default constructor is to set the
data members of a Kid object to their 0 equivalent values.
This means quote is set to nullptr, and candies is set to 
0. All of this can be done in the initalization list.
*/
Kid::Kid() : quote(nullptr), candies(0)
{}

/*The purpose of this argument constructor is to set the data members
in for a Kid object using the arguments passed in. This involves setting
the candies to the integer value passed in using the initalization list, 
and setting the quote in the body of the function.
*/
Kid::Kid(string & a_name, int a_age, const string & a_quote, int some_candies) : Attendee(a_name, a_age), candies(some_candies)
{
	if(!a_quote.empty())
	{
		quote = new char[a_quote.length() + 1];
		strcpy(quote, a_quote.c_str());
	}

	else
	{
		quote = new char[1];
		quote[0] = '\0';
	}
}

/*The purpose of this copy constructor is to perform a deep
copy for a Kid object. This is necessary because a Kid 
object manages dynamic memory. The argument of this function 
is the kid object you want to use to copy. The int value for 
candies can be copied in the initialization list, and the 
body of the function is responsible for copying the 
dynamic memory.
*/
Kid::Kid(const Kid & to_copy) : Attendee(to_copy), candies(to_copy.candies)
{
	//If the quote in the original exists, do a deep copy.
	if(to_copy.quote)
	{
		quote = new char[strlen(to_copy.quote) + 1];
		strcpy(quote, to_copy.quote);
	}

	//Otherwise, set the quote of the copy to null
	else
		quote = nullptr;

}

/*The purpose of this destructor is to delete all 
dynamic memory and set all data members to their 0
equivalent value for a Kid object. This involves 
deleting the Kids dynamically allocated quote, and
setting their number of candies to 0.
*/
Kid::~Kid()
{
	//If the quote exists, delete it.
	if(quote)
	{
		delete [] quote;
		quote = nullptr;
	}
	candies = 0;
}

/*The purpose of this assignment operator is to allow
1 Kid class object be copied into another. Since the 
Kid class manages dynamic memory, it is necessary to 
write this function. By using this assignment operator
function, we are able to perform a deep copy when copying
2 pre-existing class objects, allowing for their to be no 
memory leaks.
*/
Kid & Kid::operator=(const Kid &src)
{
	//Check for self assignment
	if(this == &src)
		return * this;

	Attendee::operator=(src);

	//Deallocate dynamic memory the current object is referencing
	if(quote)
	{
		delete [] quote;
		quote = nullptr;
	}

	if(src.quote)
	{
		quote = new char[strlen(src.quote) + 1];
		strcpy(quote, src.quote);
	}
	else
		quote = nullptr;
	candies = src.candies;

	return *this;
}

/*The purpose of this function is to display a Kid objects
data members to the user. This means the current number of candies
will be shown to the user, as well as the quote registered if
it has been entered. This function returns 0 if no quote has been
entered, and 1 if a quote was entered and displayed.
*/
int Kid::display_kid() const
{
	
	int show_adult = Attendee::display(); //Display the name and age

	if(show_adult == 0)
		return 0;

	cout << "You have found " << candies << " candies!" << endl;

	//If there is no quote, tell the user.
	if(!quote)
	{
		cout << "No quote yet!" << endl;
	}

	//Otherwise, show the quote.
	else 
		cout << "Memorable quote: " << quote << endl;
	return 1;
}

/*The purpose of this function is to update the kids found
candy. This function is called when the kid has found
candy, and this determines how much candy they found.
This is determined with the integer argument, with 
the kid getting more candy the longer they search.
*/
int Kid::pick_up_candy(int search)
{
	//Mod the search by 7 so a kid can't find to much candy.
	search %= 7;
	candies += search + 1;		
	return search + 1;
}

/*The purpose of this function is to register the quote
entered by the kid. Since the Kid class has a dynamically
allocated array, this function sizes the array to match
the length of the argument, and then copies the argument
into the data member. 
*/
int Kid::register_quote(const string &kid_quote)
{
	if(!quote)
		return 0;

	if(quote)
		delete [] quote;
	//Set the kids quote.
	quote = new char[kid_quote.length() + 1];
	strcpy(quote, kid_quote.c_str());
	return 1;
}

/*The purpose of this function is to allow a kid to 
share some candies with a friend. This essentially means 
the kids total candy amount will be lowered by a pre determined
amount, which is determined by the integer argument. The 
function will return 0 if the kid tries to share more candy
then they have, and otherwise will return the amount of 
candy left. 
*/
int Kid::share_candy(int candy_to_share)
{
	if(candy_to_share > candies)
		return 0;

	candies -= candy_to_share;
	return candies;
}

/*The purpose of this function is to determine weather or not
the Kid attendee drops their candy. Since kids can be absent
minded at times, they sometimes drop their candy and its gone
forever! Since kids are unpredictable, this has a completely 
random chance of happening. The function returns true if the 
child dropped candy, and false if not.
*/
bool Kid::drop_candy()
{
	//If the child has no candy, leave the function.
	if(candies == 0)
		return false;

	//Generate a random number

	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 	
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution (0, 99);
	int random_num = distribution(generator);

	//If the number is less then 10, the kid loses a candy.
	if(random_num < 10)
	{
		--candies;
		return true;
	}	

	//Otherwise the kids doesn't loose any candy.
	return false;
}

/*The purpose of this default constructor is to 
set the data members for a Dog object to their
0 equivalent value. This means the number of treats
a dog has found is set to 0.
*/
Dog::Dog() : treats(0)
{}

/*The purpose of this argument constructor is to 
set the data members for a Dog object to a value
passed in as an argument. This means the number
of treats a dog has is pre-determined by what is 
passed in as an argument. 
*/
Dog::Dog(string &a_name, int a_age, int some_treats) : Attendee(a_name, a_age), treats(some_treats)
{}

/*The purpose of this destructor is to set the
data member of a Dog object to its 0 equivalent
value. This means the number of treats a dog has
found is set to 0.
*/
Dog::~Dog()
{
	treats = 0;
}

/*The purpose of this function is to show the user how
many treats has been found. This is done with a simple 
output statement.
*/
int Dog::display_dog() const
{
	Attendee::display();
	//Show the dog their number of treats
	cout << "You have found " << treats << " treats." << endl;
	return 0;
}

/*The purpose of this function is to allow the dog to dodge an 
obstacle. The function uses the argument, and with that, 
tells the dog how it dodged the obtacle, such as jumping. 
The function returns 1 if an option was selected, and 
returns 0 if the input was invalid.
*/
int Dog::dodge_obstacle(int reaction) const
{
	//Different ways dodging obstacles
	if(reaction == 1)
		cout << "You jumped over the obstacle! What a jump!" << endl;

	if(reaction == 2)
		cout << "You crawled under the obstacle!" << endl;
	
	if(reaction == 3)
		cout << "You straight through obstacle breaking it!" << endl;

	else
		return 0;	

	return 1;
}

/*The purpsoe of this function is to determine how 
many treats a dog found in a certain time period of 
sniffing. This will be done using the mod operator.
The max amount of treats a dog can find in a room 
is 5, so we will mod the time sniffing by 5 and that
will deterine how many treats the dog finds. This will 
increase the number of treats the dog has found.
*/
int Dog::sniff_treats(int time_sniffing, int room_treats)
{
	//Mod the time sniffing by 5 so the dog doesn't
	//find do many treats.
	int treats_found = time_sniffing % (room_treats + 1);
	treats += treats_found;
	return treats_found;
}

/*The purpose of this function is to allow the dog to
eat some of thier found treats. Since sometimes dogs 
can't manage themselves, this function has the dog eat 
a random amount of treats, and doesn't simply just decrease
the number of treats by 1. 
*/
int Dog::eat_treats()
{
	//Generate a random number between 0 and the number
	//of treats the dog has found.

	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 	
	default_random_engine generator(seed);
	uniform_int_distribution<int> distribution (0, treats);
	int random_num = distribution(generator);

	//Decrease the treats by the random number.
	treats -= random_num;
	
	return random_num;
}
