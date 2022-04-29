#pragma once

#include <stack>

#include "variable_table.h"

//����� �����������. ���� ���� ��� � ���
//���������������: ������ ���������� ��������.

class translator{

 public:
	translator();
	//������������ �� ���������. ���� ���������� ������.

	bool lex_analysis(string sorce_code_file, string tokens_file, string errors_file);
	//���� ������������ �������
	//sorce_code_file - ��� ����� � �������� �����
	//tokens_file - ��� ����� �������(����� �������������)
	//errors_file - ��� ����� ��� ������
	//���������� true, ���� ���� ������� ����������

	bool parse(string tokens_file, string errors_file); 
	//���� ��������������� �������
	//tokens_file - ��� ����� �������
	//errors_file - ��� ����� ��� ������

	void out_tree(string f_name);
	//����� ������ ��� ��������� ���� � ���� (�������� �������)
	//f_name - ��� �����

	//���������, ����������� �����
	class token{
	 public:
		int table_n; //����� �������
		int chain_n; //����� �������, ���� ������� ���������� - -1
		int numb; //����� � ������� / � �������

		token();
		token(int t_n, int ch_n, int n); //����������� �� ���� "����� ��"

		friend ostream& operator << (ostream& os, token& out_t); //����� ������
		friend istream& operator >> (istream& is, token& inp_t); //���� ������

	};

 private:
	 //��������� �������
	 const_table<char> admis_chars; //������� ���������� ��������, ������������ ��� ��� (�� ����������� ����), ����� ������� - 0
	 const_table<char> numbs; //������� ����, ����� ������� - 1
	 const_table<char> opers_chars; //������� �������� ��������, ����� ������� - 7
	 const_table<string> opers; //������� ��������, ����� ������� - 2
	 const_table<string> key_words; //������� �������� ����, ����� ������� - 3
	 const_table<char> separaters; //������� ������������, ����� ������� - 4

	 //���������� �������
	 variable_table identifier; //������� ���������������, ����� ������� - 5
	 variable_table consts; //������� ��������, ����� ������� - 6

	 
	 string get_token_text(token get_t); // ���������� ����� ������ ���������� � ������

	 bool lex_string_process(string inp_str); //����������� ��������� ������. ���������� true, ���� ������ ���, ����� - false

	 int check_symbol(char sym); //�������� �������� �� ������ � ����������:
	 // -1 - �� ��������
	 // ���� ��������, �� ������ ����� �������

	ifstream lex_sorce_s; //����������� ������. ����� ��� ������ � ������ ��������� ����.
	ofstream token_s; //����������� ������. ����� ��� ������ � ������ �������.
	ofstream errors_s; //����������� ������. ����� ��� ������ � ������ ������.

	//===============================================================================================================
	//===================================== ��� ��������������� ������� =============================================

	//������� ������� �������
	struct synt_table_el{
		vector<string> terminal; //������������ ������
		int jump; //�������
		bool accept; //��������� ��� ���
		bool put_in_stack; //����� � ���� ��� ���
		bool should_return; //������������ ��� ���
		bool error; //����� ������� ������ ��� ���

	};

	vector<synt_table_el> parsing_table; //������� �������
	stack<int> parsing_stack; //����, ������������ ��� �������


	// ===================================== �������� ��������� ������ =====================================

	//�������� ������, ��� �������� ���������� ������ ���� (���� ������� ��� ������� ����� ���� ������, ������� ����� ���)
	 struct tree_el{

			tree_el(){	//����������� �� ���������
			 left = 0;
			 right = 0;
			}

			 int type; //��� �������
			 //0 - ���� ��������(��� ������������)
			 //1 - ����������
			 //2 - ����� � �������


			 string id; //�������� �������������, � ���� ������

			 tree_el *left, *right; //������ � ����� ���������
		};

		void grow_tree(vector<token> code); //�������� ������ �� ������� ������� � ������������� ��� � ��������� ������
		void grow_little_tree(vector<token> code, tree_el *&beg); //�������� ���������� ������(�����������)

		tree_el *tree_begin; //������ ������
		tree_el *tree_cur; //��������� �� ������� �������� ������

		void out_tree_rec(ofstream& out_f, tree_el *beg); //����� �����������, ��� ������ ���


};