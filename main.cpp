//Cody Hathcoat 	October 21st, 2024 	Program #1 	CS302

#include "Attendee.h"

/*The purpose of this file is contain the main implementaition of
the program. This primarily involves testing the core hierarcy and 
the data structure. The file will do this by allowing the user to
decide what attendee to be, and then to go through a haunted house
using the attendees public methods and methods of the data structure.
*/


int main()
{
	vector<int> dog_path {3, 6, 1, 5, 2}; //Vector with treats.

	int choice{0};	 //What does the user want to do.

	string name; //How the user identifies.

	int age{0};  //The users age.

	int being{0}; //What is the user?

	int num{0}; //Used for various ints.

	int left{0};  //Shows what the left connection is.
	
	int right{0}; //Shows what the right connection is.
	
	int length{0}; //Holds things such as time values.

	int candy_area{0}; //Where the candy is located.
	
	int index{0}; //The current index.

	int value{0};  //Holds function calls.

	bool did_occur{0}; //Checks if a function call occured.

	string quote;    //Holds a childs quote.

	//Figure out what kind of attendee is using the program.
	while(being != 1 && being != 2 && being != 3)
	{
	   cout << "Enter what you are. " << endl;
   	   cout << "1. Adult" << endl;
   	   cout << "2. Kid" << endl;
   	   cout << "3. Dog" << endl;

   	   cin >> being;
   	   cin.ignore(100, '\n');

	   if(being != 1 && being != 2 && being != 3)
		cout << "Invalid input" << endl;
	}

	//Get name and age.
	cout << "Please enter your name." << endl;
	getline(cin, name);

	do
	{
	   cout << "Please enter your age." << endl;
	   cin >> age;
	   cin.ignore(100, '\n');
	   
	   if(age < 1)
	      cout << "Invalid input" << endl;
	} while(age < 1);

	//If the attendee is an adult
	if(being == 1)
	{
	   cout << "Welcome to a Haunted House Maze for adults!" << endl;
	  
	   //Create adult and haunted house object. 
	   Adult a_adult(name, age, 0);
	   ARR adult_haunted_house;
	   //value = adult_haunted_house.build();

	   //Allow the user to make chocies.
	   while(choice != 4)
	   {
	      cout << "\nSelect an option." << endl;
	      cout << "1. Move." << endl;
	      cout << "2. Ask a friend for advice." << endl;
	      cout << "3. Take a short break." << endl;
	      cout << "4. Give up." << endl; 
	      cout << "5. Show information." << endl;
	      cout << "6. Show all room information." << endl;
	      cout << "7. Show information on specific room." << endl;
	      cout << "8. Test Copy Constructor." << endl;
	      cout << "9. Test assignment operator." << endl;
	    
	      cin >> choice;
	      cin.ignore(100, '\n');

	      //If the user wants to move.
	      if(choice == 1)
	      {
		   //Decide where the user wants to go.
	           cout << "Do you wish to go:\n1. Left\n2. Right " << endl;
		   cin >> num;
		   cin.ignore(100, '\n');

		   //Move the user.
		   value = adult_haunted_house.move(num);
	
		   //If the move was successful.	
		   if(value == 1)
		   {
		      cout << "You moved rooms successfully!" << endl;
		      did_occur = a_adult.is_skeleton();
	
		      //If a skeleton jump scares the user.	
		      if(did_occur)
		      {
		         cout << "BOO\n\n A skeleton jumped out and scared you!" << endl;
			 cout << "Enter how scared you were on a scale of 1 to 10: ";

			 do
			 {
			    cin >> num;
			    cin.ignore(100, '\n');

			    if(num < 0 || num > 10)
			        cout << "Try again." << endl;

			 } while(num < 0 || num > 10);

			 //Update the scare level.
			 value = a_adult.react(num);
			 cout << "Scare level is now at level " << value << endl;
		      }
		   }

		   //If the user finishes the maze.
		   if(value == 0)
		   {
		      cout << "You completed the maze!" << endl;
		      choice = 4;
		   }
		  
		   //If not a valid move choice was made. 
		   if(value == -2)
		      cout << "Thats not a move choice!" << endl;

		   //If the user hits a trap door.
		   if(value == -1)
		   {
		      cout << "You tried to change rooms but feel into a trap door! " 
		              "You had a long fall and lose the game, better luck next time!" << endl;
		      choice = 4;
		   }
	      }

	      //If the user wants random advice from a friend.
	      if(choice == 2)
	      {
	         cout << "Asking a friend for random advice now..." << endl;
		 cout << "Advice: " << endl;
		 value = a_adult.ask_help();
	      }

	      //If the user wants to rest.
	      if(choice == 3)
	      {
	         cout << "How many seconds do you rest for?" << endl;
		 do
		 {
		    cin >> num;
		    cin.ignore(100, '\n');

		    if(num < 0)
		       cout << "Invalid input." << endl;

		 }while (num < 0);

		 value = a_adult.take_break(num);
		 cout << "Your new scare level is: " << value << endl;
	      }	 

	      if(choice == 5)
	      {
	         value = a_adult.display_adult();

	      }
	      //Test the display function.
	      if(choice == 6)
	      {
	         value = adult_haunted_house.display();

		 cout << "Displayed " << value << " rooms" << endl;
	      }

	      //Test the retrieve function.
	      if(choice == 7)
	      {
	         cout << "Enter the room number to see information on: ";
		 cin >> num;
		 cin.ignore(100, '\n');
		 value = adult_haunted_house.retrieve(num, left, right);
		
		 if(left != 0)
		    cout << "Left connection room number: " << left << endl;

		 if(right != 0)
	            cout << "Right connection room number: " << right << endl;

		 if(value == 0)
		    cout << "No connections found!" << endl;
	      }

	      //Copy constructor test.
	      if(choice == 8)
	      {
	         cout << "Testing Copy Constructor for the haunted house." << endl;
		 ARR new_haunted_house(adult_haunted_house);
		 cout << "Displaying the new haunted house created "
			 "the copy contructor." << endl;

		 value = new_haunted_house.display();
		 cout << "Displayed " << value << " rooms.\n\n" << endl;
	      }

	      //Test the assignment operator.
	      if(choice == 9)
	      {
	         cout << "Testing the Assignment Operator for the haunted house." << endl;
		 ARR new_haunted_house;
		 new_haunted_house = adult_haunted_house;
		
		 cout << "The copy was made using the assignment operator, verified using "
			 "gdb. Displaying the copy now." << endl;

		 value = new_haunted_house.display();
		 cout << "Displayed " << value << " rooms.\n\n" << endl;
	      }

	         
	      //If the user wants to give up.	
	      if(choice == 4)
	         cout << "Thanks for attending!" << endl;

	      //If a valid choice wasn't made.
	      if(choice < 1 || choice > 9)
	         cout << "Invalid input" << endl;
	   }

	}
	   
	//Kid haunted house.
	if(being == 2)
	{

	   cout << "Welcome to haunted house for kids!." << endl;

	   //Create a Kid and haunted house (CLL) object.
	   Kid a_kid(name, age, "", 0);
	   CLL kid_haunted_house;
	   kid_haunted_house.build();

	   //Allow the user to make choices.
	   while(choice != 6)
	   {	
	        cout << "\nSelect an option." << endl;
	        cout << "1. Search for candy." << endl;
		    cout << "2. Share candy." << endl;
		    cout << "3. Register quote." << endl;
		    cout << "4. Move to the next room." << endl;
		    cout << "5. Show information." << endl;
            cout << "6. Quit." << endl;
            cout << "7. Display all room information." << endl;
            cout << "8. Show specific room information." << endl;
            cout << "9. Test copy constructors." << endl;
            cout << "10.Test assignment operator.\n" << endl;
        
            cin >> choice;
            cin.ignore(100, '\n');	

            //If the user wants to search for candy.
            if(choice == 1)
            {
                //Get a search choice.
                cout << "Where do you wishe to search?" << endl;
                cout << "1. Under the chair." << endl;
                cout << "2. By the ghost." << endl;
                cout << "3. In the pumpkin." << endl;
                cin >> num;
                cin.ignore(100, '\n');

                //How long the user searches for.
                cout << "How many seconds do you search for?" << endl;
                cin >> length;
                cin.ignore(100, '\n');

                //Did the kid find candy.
                did_occur = kid_haunted_house.check_for_candy(num);
        
                //If candy wasn't found
                if(did_occur == false)
                     cout << "Found 0 candies!" << endl;

                //If candy was found, how much.
                else
                {
                     num = a_kid.pick_up_candy(length);
                     cout << "Found " << num << " candies!" << endl;	
                }
            }

            //If the user wants to share candy with their friends.
            if(choice == 2)
            {
                 //Get the amount of candy to share.
                 cout << "How much candy would you like to share with your friends?" << endl;
                 do
                 {
                    cin >> num;
                    cin.ignore(100, '\n');
        
                if(num < 0)
                   cout << "Invalid number." << endl;

                 } while(num < 0);

                 value = a_kid.share_candy(num);

                 //If no candy could be shared.
                 if(value == 0)
                       cout << "You don't have that much candy to share!" << endl;
            
                 //Say how much candy was shared.	
                 else
                       cout << "You shared candy! You now have " << value << " candies!" << endl;
            }

            //If the user wants to enter a quote.	
            if(choice == 3)
            {
                 //Get the users quote
                 cout << "Please enter your quote: ";
                 getline(cin, quote);
                 num = a_kid.register_quote(quote);	
            
                 //If the quote was registered.	
                 if(num == 1)
                      cout << "Your quote has been registered!" << endl;
            }
            
            //If the kid wants to move to the next room	
            if(choice == 4)
            {
                 //Was the move successful or not
                 did_occur = kid_haunted_house.move(a_kid);
                 if(did_occur == false)
                      cout << "You are in the last room!\n" << endl;
        
                 else
                      cout << "Now in the next room!\n" << endl;
            }	

            //If the kid wants to see their information
            if(choice == 5)
            {
                 value = a_kid.display_kid();
            
                 if(value == 1)
                      cout << "\nThats all your info!" << endl;

                 else
                      cout << "Not all info could be accessed." << endl;
            }

            //Display all room information.
            if(choice == 7)
            {
                 value = kid_haunted_house.display();
                 cout << "Displayed " << value << " rooms." << endl;
                }

            //Retrieve room information.
            if(choice == 8)
            {
                cout << "Enter a room to get information for: ";
                cin >> num;
                cin.ignore(100, '\n');

                value = kid_haunted_house.retrieve(num, candy_area);

                if(value == 0)
                   cout << "Room information couldn't be found." << endl;

                if(candy_area == 1)
                   cout << "Candy location: Under the chair." << endl;
            
                if(candy_area == 2)
                   cout << "Candy location: By the ghost." << endl;

                if(candy_area == 3)
                cout << "Candy loactoin: In the pumpkin." << endl;
            }
            
            //Test the copy constructor.
            if(choice == 9)
            {
               cout << "Testing the copy constructors now." << endl;
               Kid copy_kid(a_kid);
               CLL copy_kid_house(kid_haunted_house);
               
               cout << "A Kid and Haunted house have been copied using "
                   "the copy constructor, displaying copies now." << endl;
               value = copy_kid.display_kid();
               if(value == 1)
                  cout << "Kid information displayed.\n" << endl;

               value = copy_kid_house.display();
               cout << "Displayed " << value << " rooms." << endl;	
            }

            //Test the assignment operator.
            if(choice == 10)
            {
               cout << "Testing the assignment operator now." << endl;
               Kid kid_copy;
               CLL kid_house_copy;

               kid_copy = a_kid;
               kid_house_copy = kid_haunted_house;

               cout << "Copied the Kid and Haunted House using the assingment "
                   "operator. Displaying copies now." << endl;

               value = kid_copy.display_kid();
               if(value == 1)
                  cout << "Kid information displayed.\n" << endl;
        
               value = kid_house_copy.display();
               cout << "Displayed " << value << " rooms." << endl; 
            }

            if(choice < 1 || choice > 10)
               cout << "Invalid input." << endl;
	    }
     }
	//If the user is a dog.
	if(being == 3)    
	{
	   cout << "Welcome to a Haunted House for dogs!" << endl;	

	   //Create a dog object.
	   Dog a_dog(name, age, 0);
	
	   //Allow the user to make choices.
	   while(choice != 4 || index == 5)
	   {	
	        cout << "\nSelect an option." << endl;
	        cout << "1. Sniff for treats." << endl;
            cout << "2. Eat treats." << endl;
            cout << "3. Move to the next room." << endl;
            cout << "4. Quit." << endl;
            cout << "5. Show information." << endl;

            do
            {
               cin >> choice;
               cin.ignore(100, '\n');	

               if(choice < 1 || choice > 5)
                  cout << "Invalid input" << endl;

            } while(choice < 1 || choice > 5);

            //Sniff treats
            if(choice == 1)
            {
                 cout << "\nHow long are you sniffing for? Round to the nearest second." << endl;

                 do
                 {
                    cin >> num;
                    cin.ignore(100, '\n');

                if(num < 0)
                   cout << "Invalid input" <<  endl;

                 } while(num < 0);
                    
                 value = a_dog.sniff_treats(num, dog_path[index]);
                 dog_path[index] -= value;
                 cout << "Found " << value << " treats." << endl;
            }

            //Eat treats.
            if(choice == 2)
            {
                 num = a_dog.eat_treats();
                 cout << "\nYou ate " << num << " treats." << endl;		
            }

            //Move.
            if(choice == 3)
            {
                 if(index >= 4)
                      cout << "You've reached the last room!" << endl;
                 else
                 {
                  ++index;
                      cout << "You've entered the next room." << endl;
                  cout << "Moving ghost is approachign you! How do you dodge?" << endl;
                  cout << "1. Jump." << endl;
                  cout << "2. Crawl under." << endl;
                  cout << "3. Challenge the ghost." << endl;

                  do
                  {
                     cin >> num;
                     cin.ignore(100, '\n');
        
                     if(num < 1 || num > 3)
                        cout << "Invalid input" << endl;

                  } while (num < 1 || num > 3);
                    
                  value = a_dog.dodge_obstacle(num);
                 }
            }

            //Display
            if(choice == 5)
            {
                 cout << "Showing your information now." << endl;
                 value = a_dog.display_dog();
            }
	    }	
	}

	return 0;
}
