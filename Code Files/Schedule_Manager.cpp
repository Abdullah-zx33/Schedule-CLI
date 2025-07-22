
#include <iostream>
#include "utilities.h"
#include "themes.h"
#include <string>
#include "main_page.h"
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

 int main()
{
	 fs::path storage = "Data";
	 if (!fs::exists(storage))
		 fs::create_directories(storage);
	 string choice;
	 op object_main{};
	 animate("Welcome to the Schedule Manager!\n'help' To view Functions!\n");
	 
	 do{
		cout << "\nShadow> ";
		getline(cin, choice);
	 
		if (choice == "help")
			help();

		else if (choice == "exit") {
			cout << "\nThanks For Using Schedule Manager!\n\n<----------------------------------------------->\n";
			break;
		}

		else if (choice == "add")
			object_main.add();

		else if (choice == "edit")
			object_main.edit(0);

		else if (choice == "mark")
			object_main.edit(1);

		else if (choice == "view")
			object_main.view();

		else if (choice == "cls")
			object_main.screen_clean();

		else if (choice == "delete")
			object_main.del();

		else if (choice == "theme")
			custom::theme_selector();

		else
			 cout << "Invalid or Unrecognized Command '"<<choice<<"' \n";
	 
	 }while(true);
}

