#ifndef CHAIN_H
#define CHAIN_H
#include <vector>
#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

class Chain{
public:
	Chain(std::string file_name);
	void normalize_rows();
	void process_link(const std::string name);
	void break_chain();
	std::string get_next_word(const std::string name);

private:
	void add_link(const std::string name);
	void add_connection(const int prev_link, const int current_link);
	int get_link_number(const std::string name);
	std::vector<std::string> names;
	std::vector<int> beginning_links;
	std::vector<std::vector<float>> probability_matrix; 
	int matrix_dim;
	int prev_link;
	bool verbose;
};

#endif