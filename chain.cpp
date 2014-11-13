#include "chain.h"

Chain::Chain(std::string file_name){
	std::ifstream in_stream;
	
	prev_link = -1;
	matrix_dim = 0;
	srand(time(NULL));

	in_stream.open(file_name.c_str());
	std::string line;
	int line_idx = 0;

	while(std::getline(in_stream, line)){

		//std::cout << "Reading line " << line_idx << "\n";
		line_idx++;
		std::string word;
		std::istringstream iss(line);
		while(iss >> word){
			process_link(word);
		}
	}
	std::cout << "Normalizing rows \n";
	normalize_rows();
}

std::string Chain::get_next_word(const std::string name){
	
	if (name == ""){
		int value = rand() % beginning_links.size();
		int rand_idx = beginning_links[value];
		const std::string start = names[rand_idx];
		//std::cout << "Randomly starting at " << start << "\n";
		return start;
	}
	else{
		float value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		int link_num = get_link_number(name);
		for (int j = 0; j < matrix_dim; j++){
			if(probability_matrix[link_num][j] > value){
				return names[j];
			}
		}
	}
	return "\n";
}

void Chain::normalize_rows(){
	for (int i = 0; i < matrix_dim; i++){

		float sum = 0;
		for (int j = 0; j < matrix_dim; j++){
			sum += probability_matrix[i][j];
		}
		float total = 0;
		for (int j = 0; j < matrix_dim; j++){
			if (probability_matrix[i][j] != 0){
			total += probability_matrix[i][j] / sum;
			probability_matrix[i][j] = total;
			}
		}
	}
}

int Chain::get_link_number(const std::string name){
	for(std::vector<int>::size_type i = 0; i != names.size(); i++) {
		if (names[i] == name)
			return i;
	}
	return -1;
}

void Chain::break_chain(){
	prev_link = -1;
}

void Chain::add_connection(const int prev_link, const int current_link){
	probability_matrix[prev_link][current_link] += 1;
}

void Chain::process_link(const std::string name){
	int current_link = get_link_number(name);
	if (current_link == -1){
		add_link(name);
		current_link = get_link_number(name);
	}
	int first_char = name[0];
	if (first_char >= 65 && first_char < 90){ // This is the first value
		beginning_links.push_back(current_link);
	}
	if (prev_link != -1)
		add_connection(prev_link, current_link);
	

	prev_link = current_link;

	int len = name.length();
	int last_char = name[len-1];
	if (last_char == 46)
		break_chain();
}


void Chain::add_link(const std::string name){
	names.push_back(name);
	std::vector<float> new_row;
	for (int i = 0; i < matrix_dim; i++){
		new_row.push_back(0);
		probability_matrix[i].push_back(0);
	}
	new_row.push_back(0); // Resolves off-by-one
	probability_matrix.push_back(new_row);
	matrix_dim += 1;

}