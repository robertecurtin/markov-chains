#include "main.h"



void main(){
	std::string input = "../chain.txt";
	Chain chain(input);
	
	std::string output = "../output.txt";
	std::ofstream out_stream;
	out_stream.open(output.c_str());
	for(int i = 1; i < 100; i++){
		std::string word = "";
		while(word != "\n"){
			word = chain.get_next_word(word);
			out_stream << word << " ";
		}
		out_stream << "\n";
	}
	out_stream.close();
}