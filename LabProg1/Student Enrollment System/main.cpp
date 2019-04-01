#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

struct student{
	string codigo;
	string nome;
	string cpf;
};

struct subject{
	string codigo;
	string nome;
	string professor;
	string creditos;
};

struct student_subject{
	string codigo_aluno;
	string codigo_subject;
	string periodo;
};

//Insert new student
void insert_student(vector<student> &student_vector);
//Remove a student by id
void remove_student(vector<student> &student_vector, vector<student_subject> &student_subject_vector);
//Insert new subject
void insert_subject(vector<subject> &subject_vector);
//Remove a subject by id
void remove_subject(vector<subject> &subject_vector, vector<student_subject> &student_subject_vector);
//Insert new student-subject relation
void insert_StudentSubject(vector<student_subject> &student_subject_vector);
//Remove a student-subject relation by student and subject id
void remove_StudentSubject(vector<student_subject> &student_subject_vector);
//Search all subjects of a student by Student Id and period
void search_student(vector<subject> &subject_vector, vector<student_subject> &student_subject_vector);
//Search all students of a subject by Subject Id and period 
void search_subject(vector<student> &student_vector, vector<student_subject> &student_subject_vector);
//Asks for the operation type {turn system off(0), searching(1), insertion and deletion(2)} 
void type_asker(int &type);
//Asks for the operation
void cmd_asker(int type, int &cmd);
//Saves new version
void save_version(const vector<student> &student_vector, const vector<subject> &subject_vector, const vector<student_subject> &student_subject_vector);
//Loads previous version
void load_version(vector<student> &student_vector, vector<subject> &subject_vector, vector<student_subject> &student_subject_vector);
//Returns attributes from txt lines
vector<string> parse(string l, char delim);

int main(){
	int cmd, type;
	vector<student> student_vector;
	vector<subject> subject_vector;
	vector<student_subject> student_subject_vector;
	//Welcome message
	system("clear");
	cout << "Bem-vindo ao gerenciador da faculdade. ";
	type_asker(type);
	//State machine loop
	while(type){	
		if(type == 1 || type == 2  || type ==3) cmd_asker(type, cmd);
		else{
			type = 0;
			continue;
		}
		//Searching student and subject commands
		if(type==1){
			switch(cmd){
				case 0:
					break;
				case 1:
					search_student(subject_vector, student_subject_vector);
					break;
				case 2:
					search_subject(student_vector, student_subject_vector);
					break;
			}
		}
		//Insertion and Deletion commands
		else if(type==2){		
			switch(cmd){
				case 0:
					break;
				case 1:
					insert_student(student_vector);
					break;
				case 2:
					remove_student(student_vector, student_subject_vector);
					break;
				case 3:
					insert_subject(subject_vector);
					break;
				case 4:
					remove_subject(subject_vector, student_subject_vector);
					break;
				case 5:
					insert_StudentSubject(student_subject_vector);
					break;
				case 6:
					remove_StudentSubject(student_subject_vector);
					break;
			}
		}
		else if(type==3){
			switch(cmd){
				case 0:
					break;
				case 1:
					save_version(student_vector, subject_vector, student_subject_vector);
					break;
				case 2:
					load_version(student_vector, subject_vector, student_subject_vector);
					break;
			}
		}
		type_asker(type);
	}
	return 0;
}

void insert_student(vector<student> &student_vector){
	string key, name, cpf;

	cin.ignore();
	cout << "Digite o código do aluno:" << endl;
	getline(cin, key, '\n');

	cout << "Digite o nome do aluno:" << endl;
	getline(cin, name, '\n');

	cout << "Digite o CPF do aluno:" << endl;
	cin >> cpf;

	student_vector.push_back(student());
	student_vector[student_vector.size()-1].codigo = key;
	student_vector[student_vector.size()-1].nome   = name;
	student_vector[student_vector.size()-1].cpf    = cpf;
	
	system("clear");
	cout << "Aluno " << name << " adicionado com sucesso!" << endl;
}
void insert_subject(vector<subject> &subject_vector){
	string name, key, professor, credits; 

	cin.ignore();
	cout << "Digite o código da matéria:" << endl;
	getline(cin, key, '\n');

	cout << "Digite o nome da matéria:" << endl;
	getline(cin, name, '\n');

	cout << "Digite o nome do professor:" << endl;
	getline(cin, professor, '\n');

	cout << "Digite o número de créditos:" << endl;
	getline(cin, credits, '\n');
	subject_vector.push_back(subject());
	subject_vector[subject_vector.size()-1].codigo     = key;
	subject_vector[subject_vector.size()-1].nome       = name;
	subject_vector[subject_vector.size()-1].professor  = professor;
	subject_vector[subject_vector.size()-1].creditos    = credits;
	system("clear");
	cout << "Matéria " << name << " adicionada com sucesso!" << endl;
}
void insert_StudentSubject(vector<student_subject> &student_subject_vector){
	string student_key, subject_key, period;

	cin.ignore();
	cout << "Digite o código do aluno:" << endl;
	getline(cin, student_key, '\n');

	cout << "Digite o código da matéria:" << endl;
	getline(cin, subject_key, '\n');

	cout << "Digite o período em que o aluno participou da matéria (formato 2019.1):" << endl;
	getline(cin, period, '\n');

	student_subject_vector.push_back(student_subject());
	student_subject_vector[student_subject_vector.size()-1].codigo_aluno = student_key;
	student_subject_vector[student_subject_vector.size()-1].codigo_subject   = subject_key;
	student_subject_vector[student_subject_vector.size()-1].periodo    = period;
	system("clear");
	cout << "Matéria" << " adicionada ao aluno com sucesso!" << endl;
}
void remove_student(vector<student> &student_vector, vector<student_subject> &student_subject_vector){
	string student_key, line;
	vector<string> words;

	cin.ignore();
	cout << "Digite o código do aluno que você deseja remover:" << endl;
	getline(cin, student_key, '\n');

	for(int i=0; i<student_vector.size(); i++){
		if(student_vector[i].codigo==student_key) student_vector.erase(student_vector.begin()+i);
	}
	for(int i=0; i<student_subject_vector.size(); i++){
		if(student_subject_vector[i].codigo_aluno==student_key) student_subject_vector.erase(student_subject_vector.begin() + i);
	}
	system("clear");
	cout << "Aluno apagado com sucesso!" << endl;
}
void remove_subject(vector<subject> &subject_vector, vector<student_subject> &student_subject_vector){
	string subject_key, line;
	vector<string> words;

	cin.ignore();
	cout << "Digite o código da matéria que você deseja remover:" << endl;
	getline(cin, subject_key, '\n');

	for(int i=0; i<subject_vector.size(); i++){
		if(subject_vector[i].codigo==subject_key) subject_vector.erase(subject_vector.begin()+i);
	}
	for(int i=0; i<student_subject_vector.size(); i++){
		if(student_subject_vector[i].codigo_subject==subject_key) student_subject_vector.erase(student_subject_vector.begin() + i);
	}
	system("clear");
	cout << "Matéria apagada com sucesso!" << endl;

}
void remove_StudentSubject(vector<student_subject> &student_subject_vector){
	string student_key, subject_key, line;
	vector<string> words;

	cin.ignore();
	cout << "Digite o código do aluno que você deseja remover:" << endl;
	getline(cin, student_key, '\n');
	cout << "Digite o código da matéria que você deseja remover:" << endl;
	getline(cin, subject_key, '\n');
	
	for(int i=0; i<student_subject_vector.size(); i++){
		if(student_subject_vector[i].codigo_subject==subject_key && student_subject_vector[i].codigo_aluno==student_key){
			student_subject_vector.erase(student_subject_vector.begin() + i);
		}
	}
}
void search_student(vector<subject> &subject_vector, vector<student_subject> &student_subject_vector){
	string student_key, period, line;
	vector<string> words, tmp_ids, subject_ids, subject_names, subject_professors, subject_credits;
	//Asking user for search detais
	cin.ignore();
	cout << "Digite o código do aluno desejado: " << endl;
	getline(cin, student_key, '\n');
	cout << "Digite o período letivo de interesse (formato 2019.1):" << endl;
	getline(cin, period, '\n');
	system("clear");

	for(int i=0; i<student_subject_vector.size(); i++){
		if(student_subject_vector[i].codigo_aluno==student_key && student_subject_vector[i].periodo==period){
			 tmp_ids.push_back(student_subject_vector[i].codigo_subject);
		}
	}
	for(int i=0; i<subject_vector.size(); i++){
		for(auto it: tmp_ids){
			if(it == subject_vector[i].codigo){
				subject_ids.push_back(subject_vector[i].codigo);
				subject_names.push_back(subject_vector[i].nome);
				subject_professors.push_back(subject_vector[i].professor);
				subject_credits.push_back(subject_vector[i].creditos);
				break;
			}
		}
	}
	//Showing user the student's subjects in the desired period
	if(subject_ids.empty()){
		cout << "O aluno " << student_key << " não possui matérias no período " << period << "!" << endl;
	}
	else{
		cout << "Matérias do aluno " << student_key << " no período " << period << ":" << endl;
		for(int i=0, qtd_subjects = subject_ids.size(); i<qtd_subjects; i++){
			cout << subject_ids[i] << " - " << subject_names[i] << " - " << subject_professors[i] << " - ";
			cout << subject_credits[i] << " créditos" << endl;
		}
	}
	
}
void search_subject(vector<student> &student_vector, vector<student_subject> &student_subject_vector){
	string subject_key, period, line;
	vector<string> words, tmp_ids, students_ids, students_names, students_cpf;
	//Asking user for search detais
	cin.ignore();
	cout << "Digite o código da matéria desejada: " << endl;
	getline(cin, subject_key, '\n');
	cout << "Digite o período letivo de interesse (formato 2019.1):" << endl;
	getline(cin, period, '\n');
	system("clear");


	for(int i=0; i<student_subject_vector.size(); i++){
		if(student_subject_vector[i].codigo_subject==subject_key && student_subject_vector[i].periodo==period){
			 tmp_ids.push_back(student_subject_vector[i].codigo_aluno);
		}
	}
	for(int i=0; i<student_vector.size(); i++){
		for(auto it: tmp_ids){
			if(it == student_vector[i].codigo){
				students_ids.push_back(student_vector[i].codigo);
				students_names.push_back(student_vector[i].nome);
				students_cpf.push_back(student_vector[i].cpf);
				break;
			}
		}
	}
	//Showing user the student's subjects in the desired period
	if(students_ids.empty()){
		cout << "A matéria " << subject_key << " não possui alunos registrados no período " << period << "!" << endl;
	}
	else{
		cout << "Alunos da matéria " << subject_key << " no período " << period << ":" << endl;
		for(int i=0, qtd_students = students_ids.size(); i<qtd_students; i++){
			cout << students_ids[i] << " - " << students_names[i] << " - " << students_cpf[i] << endl;
		}
		cout << "\n";
	}
}
void save_version(const vector<student> &student_vector, const vector<subject> &subject_vector, const vector<student_subject> &student_subject_vector){
	ofstream students, students_subjects, subjects; 
	remove("students.txt");
	remove("subjects.txt");
	remove("students_subjects.txt");
	students.open("students.txt");
	students_subjects.open("students_subjects.txt");
	subjects.open("subjects.txt");
	for(auto it: student_vector){
		students << it.codigo << "|" << it.nome << "|" << it.cpf << endl;
	}
	for(auto it: subject_vector){
		subjects << it.codigo << "|" << it.nome << "|" << it.professor << "|" << it.creditos << endl;
	}
	for(auto it: student_subject_vector){
		students_subjects << it.codigo_aluno << "|" << it.codigo_subject << "|" << it.periodo << endl;
	}
	system("clear");
	cout << "Nova versão salva com sucesso!" << endl;
}
void load_version(vector<student> &student_vector, vector<subject> &subject_vector, vector<student_subject> &student_subject_vector){
	ifstream students_subjects_file, students_file, subjects_file;
	string line;
	int i=0;
	vector<string> words;
	students_subjects_file.open("students_subjects.txt");
	students_file.open("students.txt");
	subjects_file.open("subjects.txt");
	student_vector.clear();
	subject_vector.clear();
	student_subject_vector.clear();
	while(getline(students_file, line, '\n') && line!=""){
		words = parse(line, '|');
		student_vector.push_back(student());
		student_vector[i].codigo = words[0];
		student_vector[i].nome   = words[1];
		student_vector[i].cpf    = words[2];
		i++;
	}
	i=0;
	while(getline(subjects_file, line, '\n') && line!=""){
		words = parse(line, '|');
		subject_vector.push_back(subject());
		subject_vector[i].codigo    = words[0];
		subject_vector[i].nome      = words[1];
		subject_vector[i].professor = words[2];
		subject_vector[i].creditos  = words[3];
		i++;
	}
	i=0;
	while(getline(students_subjects_file, line, '\n') && line!=""){
		words = parse(line, '|');
		student_subject_vector.push_back(student_subject());
		student_subject_vector[i].codigo_aluno   = words[0];
		student_subject_vector[i].codigo_subject = words[1];
		student_subject_vector[i].periodo        = words[2];
		i++;
	}

}
void type_asker(int &type){
	cout << "Digite o número do tipo de operação que deseja fazer:" << endl;
	cout << "-Digite 1 para fazer uma consulta;" << endl;
	cout << "-Digite 2 para adicionar/remover alunos ou matérias;" << endl;
	cout << "-Digite 3 para salvar ou carregar a versão anterior;" << endl;
	cout << "-Para sair do sistema, digite qualquer outro caracter." << endl;
	cin >> type;	
	system("clear");

}
void cmd_asker(int type, int &cmd){
	cout << "Digite agora o número da operação que deseja realizar:" << endl;
	if(type==1){
		cout << "-Digite 1 para buscar as matérias de um aluno;" << endl;
		cout << "-Digite 2 para buscar os alunos de uma matéria;" << endl;
		cout << "-Para voltar ao menu de tipo de operação, digite 0." << endl;
		cin >> cmd;
		system("clear");
		if(cin.fail() || (cmd!=0 && cmd!=1 && cmd!=2)){
			cout << "Opção inválida, tente novamente." << endl; 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cmd_asker(type, cmd);
		}
	}
	else if(type==2){
		cout << "-Digite 1 para adicionar um novo aluno;" << endl;
		cout << "-Digite 2 para remover um novo aluno;" << endl;
		cout << "-Digite 3 para adicionar uma nova matéria;" << endl;
		cout << "-Digite 4 para remover uma matéria;" << endl;
		cout << "-Digite 5 para adicionar uma matéria para um aluno;" << endl;
		cout << "-Digite 6 para remover uma matéria de um aluno;" << endl;
		cout << "-Para voltar ao menu de tipo de operação, digite 0." << endl;
		cin >> cmd;
		system("clear");
		if(cin.fail() || (cmd!=0 && cmd!=1 && cmd!=2 && cmd!=3 && cmd!=4 && cmd!=5 && cmd!=6)){
			cout << "Opção inválida, tente novamente." << endl; 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cmd_asker(type, cmd);
		}
	}
	else if(type==3){
		cout << "-Digite 1 para apagar a versão anterior e salvar a atual;" << endl;
		cout << "-Digite 2 para carregar a versão anterior;" << endl;
		cout << "-Para voltar ao menu de tipo de operação, digite 0." << endl;
		cin >> cmd;
		system("clear");
		if(cin.fail() || (cmd!=0 && cmd!=1 && cmd!=2)){
			cout << "Opção inválida, tente novamente." << endl; 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cmd_asker(type, cmd);
		}
	}
	else{
		system("clear");
		cout << "Ocorreu um erro. Entre em contato com o administrador do sistema." << endl;
	}
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
