//============================================================================
// Name        : homework.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>
using namespace std;

fstream in;
ofstream out;
vector <int> numbers;

int strtoint(string str){           //Function that takes in a string with numbers and converts
    int integer;                    //it to an integer
    istringstream(str) >> integer;
    return integer;
}

int extraction_method(int val)//extracts the 3rd 5th 7th and 8th digits of social and uses it as key
{
	int num;
	string temp;
	stringstream ss;
	ss << val;
	string social = ss.str();
	temp += social[2];
	temp += social[4];
	temp += social[6];
	temp += social[7];
	num = strtoint(temp);
	return num;
}
int quadratic_probing(int key, int *& hash_table, int M, int userNumber){
	int index;
	index =(extraction_method(key)+ (userNumber^2))%M;//updates index
	return index;
}

int read_file(){//reads numbers from file, seperates them by comma, adds to numbers

	string file_name,line;

	cout<<"Enter file to read: ";
	cin>>file_name;


	in.open(file_name.c_str());//opens file
	if(in.is_open()){
		while(in.peek()!=EOF){//reads all lines of file
			getline(in,line);//gets line and stores in line
			stringstream ss(line);//stores line in ss
			out<<line<<endl;
			while(ss){
				string s;
				if(!getline(ss,s,',')){//separates line by commas and stores in s
					break;
				}
				int temp = strtoint(s);
				numbers.push_back(temp);//adds numbers to vector
			}
		}

	}
	else{
		cout<<"Could not read file"<<endl;
		read_file();
	}
	in.close();

	return 0;
}

int write_file(int *& hash_table,int M){//writes hash table to file.
	out.open("hashed_socials.txt");

	for(int i =0; i<M; i++){
		if(M-1==i){
			cout<<hash_table[i];
		}else{
			out<<hash_table[i]<<",";
		}
	}
	out.close();
	return 0;
}

int main() {
	int user,temp;

	read_file();
	cout<<"Please enter a number between 1 and 450 Million"<<endl;//asks user for number to be used in
																//quadratic probing
	cin>> user;

	while(user>450000000 || user<1){//number check
		cout<<"Please enter a number between 1 and 450 Million"<<endl;
		cin>> user;
	}

	int index;

	int M=100000;
	int *hash_table=new int [100000];

	for(int i=0;i<M;i++){    //initialize the hash table to contain 0s
	        hash_table[i]=0;
	        cout<<hash_table[i];
	}
	for(int i=0;i<M;i++)    //hash the elements in array_of_numbers into the hash_table
	{
		index=extraction_method(numbers[i]);
		if(hash_table[index]==0){//if spot is empty
			hash_table[index]=numbers[i];
			cout<<numbers[i]<<endl;
		}
		else//collision
		{
			cout << "COLLISION! Fear not... I'll resolve it!\n";
			temp = quadratic_probing(index,hash_table, M, user);//find new location
			while(hash_table[temp]!=0){//if location is not empty
				temp = quadratic_probing(index,hash_table, M, user);
			}
			hash_table[temp]= numbers[i];
			cout<<hash_table[temp]<<endl;
		}
	}
	write_file(hash_table,M);
	return 0;
}
