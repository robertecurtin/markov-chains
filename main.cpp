#include "main.h"



void main(){
	std::string filename = "../chain.txt";
	Chain chain(filename);

	while(1){
		std::string word = "";
		while(word != "\n"){
			word = chain.get_next_word(word);
			std::cout << word << " ";
		}
		std::cout << "\n";
		system("pause");
		std::cout << "\n";
	}
}