#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<fstream>
#include<vector>
#include<windows.h>
#include<string>


using namespace std;


enum Color { Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue = 9, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

enum Direction { Up = 72, Left = 75, Right = 77, Down = 80, Enter = 13, Esc = 27, Space = 32 };


HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


void set_color(Color text, Color background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void set_cursor(int x, int y)
{
	COORD myCoords = { x,y };
	SetConsoleCursorPosition(hStdOut, myCoords);
}


class Menu
{
public:

	void start_buttons(int ch)
	{
		string buttons[] = { "START WORKING", "ABOUT CREATOR", "EXIT" };

		for (int i = 0; i < 3; i++)
		{
			set_cursor(45, 10 + 2 * i);

			if (i == ch)
				set_color(Black, White);
			else
				set_color(White, Black);

			cout << buttons[i];
		}
	}

	int start_menu()
	{
		system("cls");

		int key = 1, change = 0, A = 0;
		int choice;

		start_buttons(change);

		do
		{
			key = _getch();

			switch (key)
			{
			case Up:
				if (change > 0)
				{
					change--;
					start_buttons(change);
				}
				break;

			case Down:
				if (change < 2)
				{
					change++;
					start_buttons(change);
				}
				break;

			case Enter:
				do
				{
					switch (change)
					{
					case 0:
						choice = 0;
						A++;
						break;

					case 1:
						choice = 1;
						A++;
						break;

					case 2:
						choice = 2;
						A++;
						break;
					}
				} while (key != Enter);
			}

		} while (A < 1);


		return choice;
	}


	void about()
	{
		system("cls");

		set_cursor(30, 14);
		cout << "---------------------------------------";
		set_cursor(30, 15);
		cout << "| Created by Sava Novikov, KA-11 IASA |";
		set_cursor(30, 16);
		cout << "---------------------------------------";

		int key = 1;

		while (true)
		{
			key = _getch();
			if (key == Esc)
				return;
		}
	}
}m;


class stockInfo
{
private:

	int number;
	vector<string> name;
	vector<string> adress;

public:

	stockInfo()
	{
		this->number = 0;
	}


	int get_number() { return number; }
	vector<string> get_name() { return name; }
	vector<string> get_adress() { return adress; }

	stockInfo& mod_number(int number)
	{
		this->number = number;
		return *this;
	}
	stockInfo& mod_name(string name)
	{
		this->name.push_back(name);
		return *this;
	}
	stockInfo& mod_name(vector<string> name)
	{
		this->name = name;
		return *this;
	}
	stockInfo& mod_adress(string adress)
	{
		this->adress.push_back(adress);
		return *this;
	}
	stockInfo& mod_adress(vector<string> adress)
	{
		this->adress = adress;
		return *this;
	}


	stockInfo& operator=(stockInfo si)
	{
		this->number = si.get_number();
		this->name = si.get_name();
		this->adress = si.get_adress();

		return *this;
	}

};


class Stocks
{
private:

	stockInfo* info;
	int size;

public:

	Stocks()
	{
		info = new stockInfo[100];
		size = 0;

		from_file();
	}

	~Stocks()
	{
		delete[] info;
		size = 0;
	}


	stockInfo get_info() { return *info; }
	int get_size() { return size; }

	Stocks& mod_info(stockInfo* info)
	{
		this->info = info;
		return *this;
	}
	Stocks& mod_size(int size)
	{
		this->size = size;
		return *this;
	}

	void from_file()
	{
		ifstream F;
		F.open("stocks.txt", ifstream::app);

		while (!F.eof())
		{
			stockInfo inf;
			string input;

			getline(F, input);
			inf.mod_number(stoi(input));

			getline(F, input);
			inf.mod_name(input);

			getline(F, input);
			inf.mod_adress(input);

			info[size] = inf;
			size++;
		}

		F.close();
	}

	void in_file()
	{
		ofstream F;
		F.open("stocks.txt", ofstream::out | ofstream::trunc);

		for (int i = 0; i < size; i++)
		{
			F << info[i].get_number() << endl;
			F << info[i].get_name()[0] << endl;
			if (i != size - 1)
				F << info[i].get_adress()[0] << endl;
			else
				F << info[i].get_adress()[0];
		}

		F.close();
	}


	void row(int ch, int index, int i)
	{
		set_cursor(18, 4 + 2 * (i + 1));
		set_color(White, Black);
		cout << "-------------------------------------------------------";

		set_cursor(18, 5 + 2 * (i + 1));
		cout << "|\t" << info[index].get_number() << "|\t";

		if (i == ch)
			set_color(Black, White);
		else
			set_color(White, Black);
		cout << info[index].get_name()[0];
		set_color(White, Black);

		set_cursor(56, 5 + 2 * (i + 1));
		cout << "|";

		cout << "  " << info[index].get_adress()[0];
		set_cursor(72, 5 + 2 * (i + 1));
		cout << "|";
	}

	void m_buttons(int ch)
	{
		system("cls");

		string buttons[] = { "SEARCH", "ADD STOCK" };

		for (int i = 0; i < 2; i++)
		{
			set_cursor(30, 2 + 2 * i);

			if (i == ch)
				set_color(Black, White);
			else
				set_color(White, Black);

			cout << buttons[i];
		}

		set_color(White, Black);
		set_cursor(18, 8);
		cout << "-------------------------------------------------------";
		set_cursor(18, 9);
		cout << "| num  " << "|\t Stock`s name";
		set_cursor(56, 9);
		cout << "|  Adress";
		set_cursor(72, 9);
		cout << "|";


		int i;
		for (i = 0; i < size; i++)
			row(ch, i, i + 2);

		set_cursor(18, 4 + 2 * (i + 3));
		cout << "-------------------------------------------------------";

	}

	int menu()
	{
		system("cls");

		int key = 1, change = 0, A = 0;

		m_buttons(change);
		do
		{
			key = _getch();

			switch (key)
			{
			case Up:
				if (change > 0)
				{
					change--;
					m_buttons(change);
				}
				break;

			case Down:
				if (change < 1 + size)
				{
					change++;
					m_buttons(change);
				}
				break;

			case Enter: A++; break;

			case Esc: return -1;

			}

		} while (A < 1);

		return change;
	}


	void s_buttons(int ch, vector<int> suitable)
	{
		set_color(White, Black);
		set_cursor(18, 8);
		cout << "-------------------------------------------------------";
		set_cursor(18, 9);
		cout << "| num  " << "|\t Stock`s name";
		set_cursor(56, 9);
		cout << "|  Adress";
		set_cursor(72, 9);
		cout << "|";


		int i;
		for (i = 0; i < suitable.size(); i++)
			row(ch + 2, suitable[i], i + 2);

		set_cursor(18, 4 + 2 * (i + 3));
		cout << "-------------------------------------------------------";
	}

	int search()
	{
		system("cls");

		set_cursor(30, 2);
		cout << "Enter search request:";

		string request;
		set_cursor(30, 3);
		getline(cin, request);

		vector<int> suitable;

		for (int i = 0; i < size; i++)
			if (request == info[i].get_name()[0] || request == info[i].get_adress()[0])
				suitable.push_back(info[i].get_number());


		system("cls");

		set_cursor(30, 2);
		cout << "Enter search request:";

		set_cursor(30, 3);
		cout << request;

		set_cursor(30, 5);
		cout << "Results:";

		int key = 1, change = 0, A = 0;

		s_buttons(change, suitable);
		do
		{
			key = _getch();

			switch (key)
			{
			case Up:
				if (change > 0)
				{
					change--;
					s_buttons(change, suitable);
				}
				break;

			case Down:
				if (change < suitable.size() - 1)
				{
					change++;
					s_buttons(change, suitable);
				}
				break;

			case Enter: A++; break;

			}

		} while (A < 1);

		return suitable[change];
	}


	void add_stock()
	{
		set_cursor(30, 4);
		cout << "                                         ";

		string n_name, n_adress;

		set_cursor(30, 4);
		cout << "Enter data of new stock: Name: ";

		set_cursor(30, 5);
		getline(cin, n_name);
		vector<string> t1 = { n_name };

		set_cursor(30, 6);
		cout << "Adress: ";
		set_cursor(30, 7);
		getline(cin, n_adress);
		vector<string> t2 = { n_adress };


		info[size].mod_number(info[size - 1].get_number() + 1);
		info[size].mod_name(t1);
		info[size].mod_adress(t2);
		size++;
	}


	void delete_stock(int id)
	{
		for (int i = id + 1; i < size; i++)
		{
			info[i].mod_number(info[i].get_number() - 1);
			info[i - 1] = info[i];
		}

		size--;
	}

};



class productInfo
{
private:

	int number;
	vector<string> name;
	int amount;
	vector<string> file_name;

public:

	productInfo()
	{
		this->number = 0;
		this->amount = 0;
	}


	int get_number() { return number; }
	vector<string> get_name() { return name; }
	string get_s_name() { return name[0]; }
	int get_amount() { return amount; }
	string get_s_file_name() { return file_name[0]; }
	vector<string> get_file_name() { return file_name; }

	productInfo& mod_number(int number)
	{
		this->number = number;
		return *this;
	}
	productInfo& mod_name(string name)
	{
		this->name.clear();
		this->name.push_back(name);
		return *this;
	}
	productInfo& mod_name(vector<string> name)
	{
		this->name = name;
		return *this;
	}
	productInfo& mod_amount(int amount)
	{
		this->amount = amount;
		return *this;
	}
	productInfo& mod_file_name(string file_name)
	{
		this->file_name.clear();
		this->file_name.push_back(file_name);
		return *this;
	}


	productInfo& operator=(productInfo& pi)
	{
		this->number = pi.get_number();
		this->name.clear();
		this->name.push_back(pi.get_s_name());
		this->amount = pi.get_amount();
		this->file_name = pi.get_file_name();

		return *this;
	}

};


class Products
{
private:

	vector<productInfo> info;
	int i_size;
	int size;

public:

	Products()
	{
		i_size = 0;
	}

	Products(const Products& inProd)
	{
		this->info = inProd.info;
		this->i_size = inProd.i_size;
		this->size = inProd.size;
	}

	~Products()
	{
		info.clear();
		i_size = 0;
	}


	vector<productInfo> get_info() { return info; }
	int get_i_size() { return i_size; }
	int get_size() { return size; }

	Products& mod_info(const vector<productInfo>& info)
	{
		this->info = info;
		return *this;
	}
	Products& mod_i_size(int i_size)
	{
		this->i_size = i_size;
		return *this;
	}
	Products& mod_size(int size)
	{
		this->size = size;
		return *this;
	}


	productInfo& operator[](int index)
	{
		return info[index];
	}


	Products& operator=(Products inProd)
	{
		this->info.clear();
		this->i_size = 0;
		this->size = 0;

		this->info = inProd.info;
		this->i_size = inProd.i_size;
		this->size = inProd.size;

		return *this;
	}


	void from_file(int i)
	{
		ifstream F;
		F.open("products" + to_string(i) + ".txt", ifstream::app);

		while (!F.eof())
		{
			productInfo inf;

			string input;

			getline(F, input);
			if (input == "")
				break;
			inf.mod_number(stoi(input));

			getline(F, input);
			inf.mod_name(input);

			getline(F, input);
			inf.mod_amount(stoi(input));

			inf.mod_file_name("products" + to_string(i) + ".txt");

			info.push_back(inf);
			i_size++;
		}

		size++;

		F.close();
	}

	void in_file(int i)
	{
		ofstream F;
		F.open("products" + to_string(i) + ".txt", ofstream::out | ofstream::trunc);

		for (int j = 0; j < i_size; j++)
		{
			F << info[j].get_number() << endl;
			F << info[j].get_name()[0] << endl;
			if (j != i_size - 1)
				F << info[j].get_amount() << endl;
			else
				F << info[j].get_amount();
		}

		F.close();
	}


	void row(int ch, int index, int i)
	{
		set_cursor(18, 4 + 2 * (i + 1));
		set_color(White, Black);
		cout << "--------------------------------------------------";

		set_cursor(18, 5 + 2 * (i + 1));
		cout << "|\t" << info[index].get_number() << "|\t";


		cout << info[index].get_name()[0];
		set_cursor(56, 5 + 2 * (i + 1));
		cout << "|  ";


		if (i == ch)
			set_color(Black, White);
		else
			set_color(White, Black);
		cout << info[index].get_amount();
		set_color(White, Black);
		set_cursor(67, 5 + 2 * (i + 1));
		cout << "|";
	}

	void m_buttons(int ch)
	{
		system("cls");

		string buttons[] = { "DELETE STOCK", "SEARCH", "ADD PRODUCT" };

		for (int i = 0; i < 3; i++)
		{
			set_cursor(30, 2 + 2 * i);

			if (i == ch)
				set_color(Black, White);
			else
				set_color(White, Black);

			cout << buttons[i];
		}


		set_color(White, Black);
		set_cursor(18, 10);
		cout << "--------------------------------------------------";
		set_cursor(18, 11);
		cout << "| num  " << "|\t Product`s name";
		set_cursor(56, 11);
		cout << "|  Amount  |";


		int j = 0;
		if (i_size != 0)
			for (j = 0; j < i_size; j++)
				row(ch, j, j + 3);

		set_cursor(18, 4 + 2 * (j + 4));
		cout << "--------------------------------------------------";

	}

	int menu()
	{
		system("cls");

		int key = 1, change = 0, A = 0;

		m_buttons(change);
		do
		{
			key = _getch();

			switch (key)
			{
			case Up:
				if (change > 0)
				{
					change--;
					m_buttons(change);
				}
				break;

			case Down:
				if (change < 2 + i_size)
				{
					change++;
					m_buttons(change);
				}
				break;

			case Enter: A++; break;

			case Esc: return -1;

			}

		} while (A < 1);

		return change;
	}


	void s_buttons(int ch, vector<int> suitable)
	{
		set_color(White, Black);
		set_cursor(18, 8);
		cout << "--------------------------------------------------";
		set_cursor(18, 9);
		cout << "| num  " << "|\t Product`s name";
		set_cursor(56, 9);
		cout << "|  Amount  |";


		int i;
		for (i = 0; i < suitable.size(); i++)
			row(ch + 2, suitable[i], i + 2);

		set_cursor(18, 4 + 2 * (i + 3));
		cout << "--------------------------------------------------";
	}

	int search()
	{
		system("cls");

		set_cursor(30, 2);
		cout << "Enter search request:";

		string request;
		set_cursor(30, 3);
		cin >> request;

		vector<int> suitable;

		for (int i = 0; i < i_size; i++)
			if (request == info[i].get_name()[0])
				suitable.push_back(info[i].get_number());


		system("cls");

		set_cursor(30, 2);
		cout << "Enter search request:";

		set_cursor(30, 3);
		cout << request;

		set_cursor(30, 5);
		cout << "Results:";

		int key = 1, change = 0, A = 0;

		s_buttons(change, suitable);
		do
		{
			key = _getch();

			switch (key)
			{
			case Up:
				if (change > 0)
				{
					change--;
					s_buttons(change, suitable);
				}
				break;

			case Down:
				if (change < suitable.size() - 1)
				{
					change++;
					s_buttons(change, suitable);
				}
				break;

			case Enter: A++; break;

			}

		} while (A < 1);

		return suitable[change];
	}


	void add_product(int num)
	{
		set_cursor(30, 6);
		cout << "                                         ";

		string n_name;
		int n_amount;

		set_cursor(30, 6);
		cout << "Enter data of new product: Name:";

		vector<string> t1;
		do
		{
			t1.clear();
			set_cursor(30, 7);
			getline(cin, n_name);
			t1.push_back(n_name);
		} while (n_name == "");

		set_cursor(30, 8);
		cout << "Amount: ";
		cin >> n_amount;


		productInfo inf;

		if (i_size != 0)
			inf.mod_number(info[i_size - 1].get_number() + 1);
		else
			inf.mod_number(0);

		inf.mod_name(t1);
		inf.mod_amount(n_amount);
		inf.mod_file_name("products" + to_string(num) + ".txt");
		info.push_back(inf);
		i_size++;
	}


	void change_amount(int id)
	{
		set_cursor(58, 5 + 2 * (id + 4));
		cout << "       ";

		int new_amount;
		set_cursor(58, 5 + 2 * (id + 4));
		cin >> new_amount;
		if (new_amount > 0)
		{
			info[id].mod_amount(new_amount);
		}
		else
		{
			for (int i = id; i < i_size - 1; i++)
				info[i] = info[i + 1];

			i_size--;
		}
	}


	void clear_file(int i)
	{
		ofstream F;
		F.open("products" + to_string(i) + ".txt", ofstream::out | ofstream::trunc);

		F.close();
	}

};


int main()
{
	while (true)
	{
		int main_choice = m.start_menu();

		while (main_choice != 0)
		{
			if (main_choice == 1)
				m.about();

			if (main_choice == 2)
				return 0;

			main_choice = m.start_menu();
		}


		Stocks stocks;

		bool main_menu = false;

		while (!main_menu)
		{
			main_choice = stocks.menu();

			switch (main_choice)
			{
			case 1:stocks.add_stock(); break;

			case -1: main_menu = true; break;

			case 0: main_choice = stocks.search() + 2;

			default:
				vector<Products> products;
				for (int i = 0; i < stocks.get_size(); i++)
				{
					Products dummy;
					products.push_back(dummy);
					products[i].from_file(i);
					products[i].mod_size(stocks.get_size());
				}

				int second_main_choice;
				bool second_menu = false;
				string name_last_file;

				vector<Products>::iterator it_erase = products.begin();

				while (!second_menu)
				{
					second_main_choice = products[main_choice - 2].menu();

					switch (second_main_choice)
					{
					case 0:

						it_erase += (main_choice - 2);
						products.erase(it_erase);

						products[0].clear_file(stocks.get_size() - 1);

						for (int i = 0; i < stocks.get_size() - 1; i++)
							products[i].mod_size(stocks.get_size() - 1);

						stocks.delete_stock(main_choice - 2);

						second_menu = true;

						break;

					case 2: products[main_choice - 2].add_product(main_choice - 2); break;

					case -1: second_menu = true; break;

					case 1: second_main_choice = products[main_choice - 2].search() + 3;

					default: products[main_choice - 2].change_amount(second_main_choice - 3); break;

					}

					for (int i = 0; i < stocks.get_size(); i++)
						products[i].in_file(i);

				}

				break;
			}

			stocks.in_file();
		}
	}
}