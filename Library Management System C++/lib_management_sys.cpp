
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <set>
#include <sstream>

using namespace std;

struct book_operations {
	string name;
	int id;
	int available_copies;
	int borrowed_copies;

	book_operations() {
		name = " ";
		id = -1;
		available_copies = 0;
		borrowed_copies = 0;
	}
	void read() {

		cout << "\nEnter book Name: ";
		cin >> name;
		cout << "Enter book ID: ";
		cin >> id;
		cout << "Enter no.of book Copies:";
		cin >> available_copies;
	}
	void print() {
		cout << "\n -> Book name: " << name << " -> ID: " << id
				<< " -> Quantity: " << available_copies << " copies."
				<< " -> Total borrowed: " << borrowed_copies << " copies.";
		if (available_copies == borrowed_copies)
			cout << "(not available!)";
		cout << "\n";
	}
	bool is_substring(string &substring) {
    if (substring.size() > name.size())
        return false;

    for (int i = 0; i <= name.size() - substring.size(); ++i) {  // Fix loop condition
        bool is_match = true;

        for (int j = 0; j < substring.size() && is_match; ++j) {
            if (substring[j] != name[i + j])
                is_match = false;
        }

        if (is_match)
            return true;
    }

    return false;
}


	bool borrowing() {
		if (available_copies - borrowed_copies == 0)
			return false;
		++borrowed_copies;
		return true;
	}
	void returning() {
		assert(borrowed_copies > 0);
		--borrowed_copies;
	}
};

bool compare_books_by_id(book_operations &item1, book_operations &item2) {
	return item1.id < item2.id;
}
bool compare_books_by_name(book_operations &item1, book_operations &item2) {
	return item1.name < item2.name;
}

struct user_operations {
	string name;
	int id;
	set<int> borrowed_books_ids;

	user_operations() {
		name = " ";
		id = -1;
	}

	void read() {
		cout << "\nEnter user Name:";
		cin >> name;
		cout << "Enter user CMS ID:";
		cin >> id;
	}
	void print() {
		cout << "\n-> user name : " << name << " -> ID: " << id
				<< " Borrowed books IDs: ";
		for (int book_id : borrowed_books_ids)
			cout << book_id << " ";
		if (borrowed_books_ids.empty())
			cout << "(No borrowed copies)";
		cout << "\n";
	}
	void borrow_copy(int &book_id) {
		borrowed_books_ids.insert(book_id);
	}
	void return_copy(int book_id) {
		//find the borrowed book id in the borrowed books set and returning it by removing from the set
		auto it = borrowed_books_ids.find(book_id);

		if (it != borrowed_books_ids.end())
			borrowed_books_ids.erase(it);
		else
			cout << "\nUser " << name << " never borrowed a book with id" << book_id
					<< "\n";
	}
	bool is_borrowed(int book_id) const {
    auto it = borrowed_books_ids.find(book_id);
    return it != borrowed_books_ids.end();
}

};

bool compare_users_by_id(user_operations &item1, user_operations &item2) {
	return item1.id < item2.id;
}
bool compare_users_by_name(user_operations &item1, user_operations &item2) {
	return item1.name < item2.name;
}

struct library_system {

	vector<book_operations> books;
	vector<user_operations> users;

	library_system() {

	}

//Front-End
	void run() {

		int choice = menu();

		if (choice == 3)
			return;

		while (choice == 1 && !cin.fail()) {
			int admin_choice = admin_dashboard();

			if (admin_choice == 1)
				add_new_book();
			else if (admin_choice == 2)
				add_new_user();
			else if (admin_choice == 3)
				search_for_book();
			else if (admin_choice == 4)
				list_books_by_id();
			else if (admin_choice == 5)
				list_books_by_name();
			else if (admin_choice == 6)
				list_users_by_id();
			else if (admin_choice == 7)
				list_users_by_name();
			else if (admin_choice == 8)
				list_users_borrowed_specific_book();
			else if (admin_choice == 9) {
				run();
				choice = 3;
			} else
				break;
		}
		while (choice == 2 && !cin.fail()) {
			int user_choice = user_dashboard();

			if (user_choice == 1)
				borrow_book();
			else if (user_choice == 2)
				return_book();
			else if (user_choice == 3)
				search_for_book();
			else if (user_choice == 4) {
				run();
				choice = 3;
			} else
				break;
		}
	}
	int menu() {
		int choice = -1;
		while (choice == -1) {
			cout << "\n1) Admin Dashboard\n"
					"2) User Dashboard\n"
					"3) Exit\n"
					"Enter your choice: ";
			cin >> choice;

			if (cin.fail())
				break;
			if (!(1 <= choice && choice <= 3)) {
				cout << "\nInvalid choice. Try again\n\n";
				choice = -1;
			}
		}
		return choice;
	}
	int admin_dashboard() {
		int choice = -1;
		while (choice == -1) {
			cout << "\n1) Add new book\n"
					"2) Add new user\n"
					"3) Search books\n"
					"4) List books ordered by id\n"
					"5) List books ordered by name\n"
					"6) List users ordered by id\n"
					"7) List users ordered by name\n"
					"8) List users borrowed a specific book\n"
					"9) Back\n"
					"10)Exit\n"
					"Enter your choice:";
			cin >> choice;
			if (cin.fail())
				break;

			if (!(1 <= choice && choice <= 10)) {
				cout << "\nInvalid choice. Try again!\n";
				choice = -1;
			}
		}

		return choice;
	}
	int user_dashboard() {
		int choice = -1;

		while (choice == -1) {
			cout << "\n1) Borrow book\n"
					"2) Return book\n"
					"3) Search books\n"
					"4) Back\n"
					"5) Exit\n"

					"Enter your choice:";
			cin >> choice;
			if (cin.fail())
				break;
			if (!(1 <= choice && choice <= 5)) {
				cout << "\ninvalid choice. Try again!\n";
				choice = -1;
			}
		}
		return choice;
	}

//Back-End
//Admin options: Book operations
	bool add_new_book() {
		if (books.size() >= 5) {
			cout << "\nYou are Not allowed to add more than " << books.size()
					<< " books in the system. Remove some books\n";
			return false;
		}
		book_operations book_item;
		book_item.read();
		books.push_back(book_item);
		return true;
	}
	void list_books_by_id() {
		if (books.empty()) {
			cout << "\nNo books added in the system yet\n";
			return;
		}

		sort(books.begin(), books.end(), compare_books_by_id);

		for (book_operations book_item : books)
			book_item.print();
		cout << "\n";

	}
	void list_books_by_name() {
		if (books.empty()) {
			cout << "\nNo books added in the system yet\n";
			return;
		}
		sort(books.begin(), books.end(), compare_books_by_name);

		for (book_operations book_item : books)
			book_item.print();
		cout << "\n";
	}
	void search_for_book() {
    string substring;
    cout << "\nEnter book name: ";
    cin >> substring;

    int cnt = 0;
    ifstream file("books.txt");
    if (file.is_open()) {
        book_operations book_item;
        while (file >> book_item.name >> book_item.id >> book_item.available_copies >> book_item.borrowed_copies) {
            if (book_item.is_substring(substring)) {
                cout << "\n" << book_item.name << " " << book_item.id << "\n";
                cnt++;
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for reading (books)." << endl;
        return;
    }

    if (!cnt)
        cout << "\nNo book with such name\n";
}


//Admin options: Users operations
	bool add_new_user() {
		if (users.size() >= 5) {
			cout << "\nYou are Not allowed to add more than " << users.size()
					<< " users in the system. Remove some users\n";
			return false;
		}
		user_operations user_item;
		user_item.read();
		users.push_back(user_item);
		return true;
	}
	void list_users_by_id() {
		if (users.empty()) {
			cout << "\nNo users added in the system yet\n";
			return;
		}
		sort(users.begin(), users.end(), compare_users_by_id);

		for (user_operations &user_item : users)
			user_item.print();
	}
	void list_users_by_name() {
		if (users.empty()) {
			cout << "\nNo users added in the system yet\n";
			return;
		}
		sort(users.begin(), users.end(), compare_users_by_name);

		for (user_operations &user_item : users)
			user_item.print();
	}
	void list_users_borrowed_specific_book() {
    string book_name;
    cout << "\nEnter book name: ";
    cin >> book_name;

    int book_id = find_book_id_by_book_name(book_name);

    if (book_id == -1) {
        cout << "\nInvalid book name\n";
        return;
    }

    int book_id_container = books[book_id].id;

    vector<user_operations> users_borrowed_book;

    for (const user_operations &user_item : users) {
        if (user_item.is_borrowed(book_id_container)) {
            users_borrowed_book.push_back(user_item);
        }
    }

    if (users_borrowed_book.empty()) {
        cout << "\nNo users have borrowed copies of this book\n";
        return;
    }

    cout << "\nUsers who borrowed copies of " << book_name << " (Book ID: " << book_id_container << "):\n";
    
    for (const user_operations &user_item : users_borrowed_book) {
        cout << "\n" << user_item.name << " " << user_item.id << "\n";
    }
}



//Users options
	int find_user_id_by_user_name(string user_name) {
		for (int i = 0; i < (int) users.size(); ++i)
			if (user_name == users[i].name)
				return i;

		return -1;
	}
	int find_book_id_by_book_name(string book_name) {
		for (int i = 0; i < (int) books.size(); ++i)
			if (book_name == books[i].name)
				return i;
		return -1;
	}
	bool read_user_name_and_book_name(int &user_id, int &book_id,
			int trails = 3) {
		//this function take user name and book name and generate user id and book id
		string user_name;
		string book_name;

		while (trails--) {
			//reading user name and generating user id by its name
			cout << "Enter user name: ";
			cin >> user_name;

			user_id = find_user_id_by_user_name(user_name);

			if (user_id == -1) {
				cout << "\nInvalid user name. try again\n";
				continue;
			}
			//reading book name and generating book id by its name
			cout << "Enter book name ";
			cin >> book_name;

			book_id = find_book_id_by_book_name(book_name);

			if (book_id == -1) {
				cout << "\nInvalid book name. Try again\n";
				continue;
			}
			return true;
		}
		cout << "\nYou have tried several times. Try again later\n";
		return false;
	}
	void borrow_book() {
		int user_id, book_id;

		if(!read_user_name_and_book_name(user_id, book_id))
				return;

		if (!books[book_id].borrowing()) {
			cout<< "\nNo more copies available right now. borrow another book\n";
			return;
		}

		int book_id_container = books[book_id].id;
		users[user_id].borrow_copy(book_id_container);
	}
	void return_book() {
		int user_id, book_id;

		if(!read_user_name_and_book_name(user_id, book_id))
			return;

		books[book_id].returning();

		int book_id_container = books[book_id].id;
		users[user_id].return_copy(book_id_container);
	}
	// Function to load books data from file
void load_books_from_file(const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        books.clear(); // Clear existing data

        while (file >> ws && !file.eof()) {  // Check for end-of-file
            book_operations book;
            file >> book.name >> book.id >> book.available_copies >> book.borrowed_copies;

            if (!file.fail()) {
                books.push_back(book);
            }
        }

        file.close();
    } else {
        cerr << "Error: Unable to open file for reading (books)." << endl;
    }
}

// Function to save books data to file
void save_books_to_file(const string &filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const book_operations &book : books) {
            file << book.name << " " << book.id << " " << book.available_copies << " " << book.borrowed_copies << endl;
        }

        file.close();
    } else {
        cerr << "Error: Unable to open file for writing (books)." << endl;
    }
}



/// Function to load users data from file

void load_users_from_file(const string &filename) {
    ifstream file(filename);
    if (file.is_open()) {
        users.clear(); // Clear existing data

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            user_operations user;
            iss >> user.name >> user.id;

            int book_id;
            while (iss >> book_id) {
                user.borrowed_books_ids.insert(book_id);
            }

            users.push_back(user);
        }

        file.close();
    } else {
        cerr << "Error: Unable to open file for reading (users)." << endl;
    }
}

// Function to save users data to file
void save_users_to_file(const string &filename) {
    ofstream file(filename, ios::trunc); // Use ios::trunc to overwrite the file
    if (file.is_open()) {
        for (const user_operations &user : users) {
            file << user.name << " " << user.id << " ";

            for (int book_id : user.borrowed_books_ids) {
                file << book_id << " ";
            }

            file << endl;
        }

        file.close();
    } else {
        cerr << "Error: Unable to open file for writing (users)." << endl;
    }
}


};

int main() {
    library_system library;

    // Load data from files at the beginning
    library.load_books_from_file("books.txt");
    library.load_users_from_file("users.txt");

    // Run the library system
    library.run();

    // Save data to files before exiting
    library.save_books_to_file("books.txt");
    library.save_users_to_file("users.txt");

    return 0;
}
