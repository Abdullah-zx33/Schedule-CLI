
#include "main_page.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <ctime>
#include <filesystem>
#include <vector>
#include <sstream>
#include "utilities.h"
#include "themes.h"
#include <fstream>
#include <iomanip>
namespace fs = std::filesystem;
using namespace std;

bool check_bool() {
	bool check;
	while (true) {
		cin >> check;
		if (cin.fail()) {
			cout << "Error! Please Enter (1 for Yes) OR (0 for NO)!";
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}
}

void help(){
	cout << "\a\nAvailable Functions:\n=====================================\n";
	cout << "add		-Add Schedule\n";
	cout << "view		-view Schedule\n";
	cout << "edit		-Edit Schedule\n";
	cout << "delete		-Delete Schedule\n";
	cout << "mark		-Mark(done) Schedule\n";
	cout << "cls		-Clean Screen\n";
	cout << "theme		-Theme Menu\n";
	cout << "exit		-exit\n";
	cout << "=====================================\n";
}


	
void op::screen_clean() {
	system("cls");
	cout << "2025 - Schedule Manager - Final Version\n";
	cout << "========================================" << endl;
}

int time() {
	int n;
	while (true) {
		cin >> n;
		if (cin.fail()) {
			cout << "\nError! Please Enter Hour (0-23)";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
			return n;
	}
}

void op::add() {

	time_t now = time(0);

	++task_count;
	t.id = t.id + 1;
	t.is_done = false;

	cout << "\nEnter Task Name: "; getline(cin, t.title);
	cout << "\nEnter Task Description: "; getline(cin, t.details);
	cout << "\nTask Date (2XXX:12:31): "; getline(cin, t.date);
	cout << "\nEnter Task Hour (0-23): "; t.hour = time();;
	
	this->save();
}

void op::save() {
	
	tasks.push_back(t);
	string extension = t.title + ".txt";
	
	fs::path final = "Data";
	fs::path path_file = final / extension;
	
	if (fs::exists(path_file)){
		cout << "Error File with Same Title Already Exists!\n";
		cin.ignore();
		return;
	}
	
	ofstream file(path_file,ios::app);
	if (file.is_open()){
		file << t.id << '\n';
		file << t.title << '\n';
		file << t.details << '\n';
		file << t.is_done << '\n';
		file << t.date << '\n';
		file << t.hour << '\n';
		cin.ignore(10,'\n');
		cout << "\nTask Added Successfully!\n";
		file.close();
	}
	else
		cout << "\nError Opening File!"<<endl;
}

void op::edit(bool choice) {
	int count = 0;
	string edit_title;
	fs::path p = "Data";

	Task edit_t;
	edit_t.id = 0;

	if (choice)
		cout << "Choose Which Task to Mark!" << endl;

	cout << "\nCurrent Tasks in Directory:\n";
	for (const auto& f : fs::directory_iterator(p)) {
		if (f.is_regular_file() && f.path().extension() == ".txt") {
			cout << " - " << f.path().filename() << endl;
			count++;
		}
	}
	if (count == 0) {
		cout << "No Recent Schedules are added!" << endl;
		return;
	}

	cout << "\nEnter Title to Edit: ";
	getline(cin, edit_title);

	string extension_title = edit_title + ".txt";
	fs::path edit_path = p / extension_title;

	ifstream infile(edit_path);
	if (!infile.is_open()) {
		cout << "\n\aError opening the file!" << endl;
		return;
	}

	infile >> edit_t.id;
	infile.ignore();
	getline(infile, edit_t.title);
	getline(infile, edit_t.details);
	infile >> edit_t.is_done;
	infile.ignore(); 
	getline(infile, edit_t.date);
	infile >> edit_t.hour;
	infile.close();


	if (choice) {
		edit_t.is_done = true; 
		cout << "\nTask marked as done!\n";
	}
	else {
		cout << "\nEnter Task Name: ";
		getline(cin, edit_t.title);

		cout << "Enter Task Description: ";
		getline(cin, edit_t.details);

		cout << "Task Date (2XXX:12:31): ";
		getline(cin, edit_t.date);

		cout << "Enter Task Hour (0-23): ";
		edit_t.hour = time();

		cout << "Mark Done? (1 For Yes || 0 For No): ";
		edit_t.is_done = check_bool();
	}


	ofstream outfile(edit_path);
	if (!outfile.is_open()) {
		cout << "\n\aError writing to the file!" << endl;
		return;
	}

	edit_t.id++; 
	outfile << edit_t.id << '\n';
	outfile << edit_t.title << '\n';
	outfile << edit_t.details << '\n';
	outfile << edit_t.is_done << '\n';
	outfile << edit_t.date << '\n';
	outfile << edit_t.hour << '\n';
	outfile.close();

	cout << "\nTask Updated Successfully!\n";
}


void op::view() {

	cout << "Which Task to Read?" << endl;
	cout << "\nCurrent Tasks in Directory:\n";
	
	Task view_task;

	int count = 0;
	fs::path p = "Data";

	cout << "\nCurrent Tasks in Directory:\n";
	for (const auto& f : fs::directory_iterator(p)) {
		if (f.is_regular_file() && f.path().extension() == ".txt") {
			cout << " - " << f.path().filename() << endl;
			count++;
		}
	}

	if (count == 0) {
		cout << "No Recent Schedules Were added!" << endl;
		return;
	}

	cout << "\nOr all!";
	cout << "\nEnter Title to Edit: ";
	getline(cin, view_task.title);

	if (view_task.title == "all") {
		int dis = 15;

		cout << "\n<-------------------------------------------------------------------------------------------------------------------->\n";
		cout << left << setw(dis) << "ID"
			<< setw(dis) << "Title"
			<< setw(dis) << "Description"
			<< setw(dis) << "IS_Done"
			<< setw(dis) << "Date"
			<< setw(dis) << "Hour" << endl;
		cout << "<-------------------------------------------------------------------------------------------------------------------->\n";

		for (const auto& entry : fs::directory_iterator(p)) {
			if (entry.path().extension() == ".txt") {
				ifstream infile(entry.path());
				if (!infile.is_open()) {
					cout << "\aError opening file: " << entry.path().filename() << endl;
					continue;
				}
				Task temp_task;

				infile >> temp_task.id;
				infile.ignore();
				getline(infile, temp_task.title);
				getline(infile, temp_task.details);
				infile >> temp_task.is_done;
				infile.ignore();
				getline(infile, temp_task.date);
				infile >> temp_task.hour;
				infile.close();
				string complete;
				if (view_task.is_done)
					complete = "Done";
				else
					complete = "Not Done";

				cout << setw(dis) << temp_task.id
					<< setw(dis) << temp_task.title
					<< setw(dis) << temp_task.details
					<< setw(dis) << complete
					<< setw(dis) << temp_task.date
					<< setw(dis) << temp_task.hour << endl;
			}
		}
	}
	else{
		string extension_title = view_task.title + ".txt";
		fs::path view_path = p / extension_title;

		ifstream infile(view_path);
		if (!infile.is_open()) {
			cout << "\n\aError opening the file!" << endl;
			return;
		}
		infile >> view_task.id;
		infile.ignore();
		getline(infile, view_task.title);
		getline(infile, view_task.details);
		infile >> view_task.is_done;
		infile.ignore();
		getline(infile, view_task.date);
		infile >> view_task.hour;
		infile.close();
		string complete;
		int dis = 15;
		cout << "\n<-------------------------------------------------------------------------------------------------------------------->\n";
		cout <<left<< setw(15)<< "ID"<< setw(15)<<"Title"<< setw(15)<<"Description"<<setw(15)<<"IS_Done"<<setw(15) <<"Date"<<setw(15)<<"Hour";
		cout << "\n<-------------------------------------------------------------------------------------------------------------------->\n";
		if (view_task.is_done)
			complete = "Done";
		else
			complete = "Not Done";
		cout <<setw(dis)<< view_task.id<< setw(dis) << view_task.title << setw(dis) << view_task.details << setw(dis) << complete << setw(dis) << view_task.date << setw(dis) << view_task.hour <<endl;
	}


}


void op::del() {
	
	string t_del_title;
	cout << "\nEnter File Title to Delete! "; getline(cin,t_del_title);
	
	string file = t_del_title + ".txt";

	fs::path del_p = "Data/" + file;
	if (!fs::exists(del_p)) {
		cout << "\nFile Does not Exist!";
		return;
	}
	else {
		fs::remove(del_p);
		if (!fs::exists(del_p))
			cout << "Task Successfully Deleted!\n";

		else
			cout << "Error Deleting Task!";
	}
	return;
}
