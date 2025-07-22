
#pragma once

#include<iostream>
#include<string>
#include <vector>
void help();

class op {

private:
	struct Task {
		int id;
		std::string title;
		std::string details , category;
		bool is_done;
		std::string date; 
		int hour;
	};

	Task t;
	std::vector<Task> tasks;
	int task_count = 0;

public:
	
	void edit(bool choice);
	void save();
	void add();
	void screen_clean();
	void view();
	void del();

};