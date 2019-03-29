#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

//Insert new student
void insert_student();
//Remove a student by id
void remove_student();
//Insert new subject
void insert_subject();
//Remove a subject by id
void remove_subject();
//Insert new student-subject relation
void insert_StudentSubject();
//Remove a student-subject relation by student and subject id
void remove_StudentSubject();
//
void search_student();
//
void search_subject();
//Asks for the operation type {turn system off(0), searching(1), insertion and deletion(2)} 
void type_asker(int &type);
//Asks for the operation
void cmd_asker(int type, int &cmd);
//Returns attributes from txt lines
vector<string> parse(string l, char delim);

int main(){
	int cmd, type;
	//Welcome message
	system("clear");
	cout << "Bem-vindo ao gerenciador da faculdade. ";
	type_asker(type);
	//State machine loop
	while(type){	
		if(type==1 || type == 2) cmd_asker(type, cmd);
		else{
			type = 0;
			continue;
		}
		//Searching student and subject commands
		if(type==1){
			switch(cmd){
				case 0:
					search_student();
					break;
				case 1:
					search_subject();
					break;
			}
		}
		//Insertion and Deletion commands
		if(type==2){		
			switch(cmd){
				case 0:
					insert_student();
					break;
				case 1:
					remove_student();
					break;
				case 2:
					insert_subject();
					break;
				case 3:
					remove_subject();
					break;
				case 4:
					insert_StudentSubject();
					break;
				case 5:
					remove_StudentSubject();
					break;
			}
		}
		type_asker(type);
	}
	return 0;
}
void insert_student(){
	ofstream students;
	string key, name, cpf;
	students.open("students.txt", ios::app);

	cin.ignore();
	cout << "Digite o código do aluno:" << endl;
	getline(cin, key, '\n');

	cout << "Digite o nome do aluno:" << endl;
	getline(cin, name, '\n');

	cout << "Digite o CPF do aluno:" << endl;
	cin >> cpf;

	students << key << "|" << name << "|" << cpf << endl;
	system("clear");
	cout << "Aluno " << name << " adicionado com sucesso!" << endl;
	students.close();
}
void insert_subject(){
	ofstream subjects; 
	string name, key, professor, credits; 
	subjects.open("subjects.txt", ios::app);

	cin.ignore();
	cout << "Digite o código da matéria:" << endl;
	getline(cin, key, '\n');

	cout << "Digite o nome da matéria:" << endl;
	getline(cin, name, '\n');

	cout << "Digite o nome do professor:" << endl;
	getline(cin, professor, '\n');

	cout << "Digite o número de créditos:" << endl;
	getline(cin, credits, '\n');

	subjects << key << "|" << name << "|" << professor << "|" << credits << endl;
	system("clear");
	cout << "Matéria " << name << " adicionada com sucesso!" << endl;
	subjects.close();
}
void insert_StudentSubject(){
	ofstream students_subjects; 
	string student_key, subject_key, period;
	students_subjects.open("students_subjects.txt", ios::app);

	cin.ignore();
	cout << "Digite o código do aluno:" << endl;
	getline(cin, student_key, '\n');

	cout << "Digite o código da matéria:" << endl;
	getline(cin, subject_key, '\n');

	cout << "Digite o período em que o aluno participou da matéria (formato 2019.1):" << endl;
	getline(cin, period, '\n');

	students_subjects << student_key << "|" << subject_key << "|" << period << endl;
	system("clear");
	cout << "Matéria" << " adicionada ao aluno com sucesso!" << endl;
	students_subjects.close();
}
void remove_student(){
	string student_key, line;
	vector<string> words;
	ifstream students, students_subjects;
	ofstream new_students, new_students_subjects; 
	students.open("students.txt");
	students_subjects.open("students_subjects.txt");

	new_students.open("new_students.txt");
	new_students_subjects.open("new_students_subjects.txt");


	cin.ignore();
	cout << "Digite o código do aluno que você deseja remover:" << endl;
	getline(cin, student_key, '\n');

	while (getline(students, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[0]==student_key){
			words.clear();
			line.clear();
			continue;
		}
		new_students << line << endl;
		words.clear();
		line.clear();
	}
	remove("students.txt");
	rename("new_students.txt", "students.txt");
	
	while (getline(students_subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[0]==student_key){
			words.clear();
			continue;
		}
		new_students_subjects << line << endl;
		words.clear();
	}
	remove("students_subjects.txt");
	rename("new_students_subjects.txt", "students_subjects.txt");

	students.close();
	new_students.close();
	students_subjects.close();
	new_students_subjects.close();

}
void remove_subject(){
	string subject_key, line;
	vector<string> words;
	ifstream subjects, students_subjects;
	ofstream new_subjects, new_students_subjects; 
	subjects.open("subjects.txt");
	students_subjects.open("students_subjects.txt");

	new_subjects.open("new_subjects.txt");
	new_students_subjects.open("new_students_subjects.txt");


	cin.ignore();
	cout << "Digite o código da matéria que você deseja remover:" << endl;
	getline(cin, subject_key, '\n');

	while (getline(subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[0]==subject_key){
			words.clear();
			line.clear();
			continue;
		}
		new_subjects << line << endl;
		words.clear();
		line.clear();
	}
	remove("subjects.txt");
	rename("new_subjects.txt", "subjects.txt");
	
	while (getline(students_subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[0]==subject_key){
			words.clear();
			continue;
		}
		new_students_subjects << line << endl;
		words.clear();
	}
	remove("students_subjects.txt");
	rename("new_students_subjects.txt", "students_subjects.txt");

	subjects.close();
	new_subjects.close();
	students_subjects.close();
	new_students_subjects.close();

}
void remove_StudentSubject(){
	string student_key, subject_key, line;
	vector<string> words;
	ifstream students_subjects;
	ofstream new_students_subjects;
	students_subjects.open("students_subjects.txt");
	new_students_subjects.open("new_students_subjects.txt");


	cin.ignore();
	cout << "Digite o código do aluno que você deseja remover:" << endl;
	getline(cin, student_key, '\n');
	cout << "Digite o código da matéria que você deseja remover:" << endl;
	getline(cin, subject_key, '\n');
	
	while (getline(students_subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[0]==student_key && words[1]==subject_key){
			words.clear();
			continue;
		}
		new_students_subjects << line << endl;
		words.clear();
	}
	remove("students_subjects.txt");
	rename("new_students_subjects.txt", "students_subjects.txt");

	students_subjects.close();
	new_students_subjects.close();

}
void search_student(){
	ifstream students_subjects, subjects;
	students_subjects.open("students_subjects.txt");
	subjects.open("subjects.txt");
	string student_key, period, line;
	vector<string> words, tmp_ids, subject_ids, subject_names, subject_professors, subject_credits;
	//Asking user for search detais
	cin.ignore();
	cout << "Digite o código do aluno desejado: " << endl;
	getline(cin, student_key, '\n');
	cout << "Digite o período letivo de interesse (formato 2019.1):" << endl;
	getline(cin, period, '\n');
	system("clear");
	//Searching in the txt files
	while(getline(students_subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[0]==student_key && words[2]==period){
			tmp_ids.push_back(words[1]);
		}
	}
	while(getline(subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		for(auto it: tmp_ids){
			if(it == words[0]){
				subject_ids.push_back(words[0]);
				subject_names.push_back(words[1]);
				subject_professors.push_back(words[2]);
				subject_credits.push_back(words[3]);
				break;
			}
		}
	}
	//Showing user the student's subjects in the desired period
	cout << "Matérias do aluno " << student_key << " no período " << period << ":" << endl;
	for(int i=0, qtd_subjects = subject_ids.size(); i<qtd_subjects; i++){
		cout << subject_ids[i] << " - " << subject_names[i] << " - " << subject_professors[i] << " - ";
		cout << subject_credits[i] << " créditos" << endl;
	}
}
void search_subject(){
	ifstream students_subjects, students;
	students_subjects.open("students_subjects.txt");
	students.open("students.txt");
	string subject_key, period, line;
	vector<string> words, tmp_ids, students_ids, students_names, students_cpf;
	//Asking user for search detais
	cin.ignore();
	cout << "Digite o código da matéria desejada: " << endl;
	getline(cin, subject_key, '\n');
	cout << "Digite o período letivo de interesse (formato 2019.1):" << endl;
	getline(cin, period, '\n');
	system("clear");
	//Searching in the txt files
	while(getline(students_subjects, line, '\n') && line!=""){
		words = parse(line, '|');
		if(words[1]==subject_key && words[2]==period){
			tmp_ids.push_back(words[0]);
		}
	}
	while(getline(students, line, '\n') && line!=""){
		words = parse(line, '|');
		for(auto it: tmp_ids){
			if(it == words[0]){
				students_ids.push_back(words[0]);
				students_names.push_back(words[1]);
				students_cpf.push_back(words[2]);
				break;
			}
		}
	}
	//Showing user the student's subjects in the desired period
	cout << "Alunos da matéria " << subject_key << " no período " << period << ":" << endl;
	for(int i=0, qtd_students = students_ids.size(); i<qtd_students; i++){
		cout << students_ids[i] << " - " << students_names[i] << " - " << students_cpf[i] << endl;
	}
	cout << "\n";
}
void type_asker(int &type){
	cout << "Digite o número do tipo de operação que deseja fazer:" << endl;
	cout << "Digite 1 para fazer uma consulta;" << endl;
	cout << "Digite 2 para adicionar/remover alunos ou matérias;" << endl;
	cout << "Para sair do sistema, digite qualquer outro caracter." << endl;
	cin >> type;
}
void cmd_asker(int type, int &cmd){
	cout << "Digite agora o número da operação que deseja realizar:" << endl;
	if(type==1){
		cout << "Digite 0 para buscar as matérias de um aluno;" << endl;
		cout << "Digite 1 para buscar os alunos de uma matéria." << endl;
		cout << "Aperte qualquer outro caracter para retornar ao tipo de operação." << endl;
	}
	else if(type==2){
		cout << "Digite 0 para adicionar um novo aluno;" << endl;
		cout << "Digite 1 para remover um novo aluno;" << endl;
		cout << "Digite 2 para adicionar uma nova matéria;" << endl;
		cout << "Digite 3 para remover uma nova matéria;" << endl;
		cout << "Digite 4 para adicionar uma matéria para um aluno;" << endl;
		cout << "Digite 5 para remover uma matéria de um aluno;" << endl;
		cout <<"Aperte qualquer outro caracter para retornar ao tipo de operação;" << endl;
	}
	else{
		system("clear");
		cout << "Você digitou uma opção inválida. Tente novamente." << endl;
	}
	cin >> cmd;
}
vector<string> parse(string l, char delim){
    vector<string> tokens;
    stringstream ss(l);
    string token;
    while (std::getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}
