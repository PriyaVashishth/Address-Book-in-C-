#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip.h>
#include<stdio.h>
#include"substr.cpp"

#define X_TXTBOX 38
#define ENTER 13
#define Y_TXTBOX1 10
#define X_MAINMENU 28
#define Y_MAINMENU 7
#define DOWN_ARROW 80
#define UP_ARROW 72
#define X_SEARCHMENU 30
#define BCKSPC 8

static int id=1;
int main_menu();
void enable(int, int);
void disable(int, int);
ofstream fout, fout2;
ifstream fin, fin2;
fstream finout;
int max_len_name=0;
int len_name;
int max_len_add=0;
int len_add;
char *addmenu[]= {"ID            :", "First Name    :", "Last Name     :", "DOB(dd/mon/yy):", "Address 1     :", "Address 2     :", "Mobile        :"};
char *menu[]={" Add New Contacts "," Display Contacts "," Search Contacts  ", " Delete Contacts  ", " Edit Contacts    ", " Sort Contacts    ","       Exit       "};

//definition of the class containing all the details
class details
{
	int contact_id;
	char fname[10];
	char lname[10];
	char name[20];
	class dob
	{
		char date[2];
		char mon[12];
		char yr[4];
		public:
		void getdob()
		{
			cin.getline(date, 2);
			cin.getline(mon, '/');
			cin.getline(yr,'\n');
		}
		void show();
		void edit_show()
		{
			cprintf(date);
			cprintf(mon);
			cprintf(yr);
		}
	}date;
	char add1[15];
	char add2[15];
	char add[30];
	char number[13];

	public:
	static void addcontact();
	static void display_contacts();
	static int get_last_id();
	static int get_max_len_name();
	static int get_max_len_add();
	static void search_contact();
	static void search_by_name();
	static void search_by_num();
	static void del_contact();
	static void del_single();
	static void del_all();
	static void edit_contact();
	static void edit_fields();
	static void strsort();
	void get();
	void show();
	void show_dob();
}d1;

//main function
int main()
{
	clrscr();
	main_menu();
	getch();
	return 0;
}

void details::dob::show()
{
	cout<<date<<mon<<"/"<<yr<<"\t";
}
//definition of main_menu to display the MAIN MENU
int main_menu()
{
	if(fin)
	{
		fin.close();
	}
	clrscr();
	textmode(2);
	gotoxy(31,5);
	textcolor(11);
	cprintf("Phone Book");
	for(int i=0;i<7;i++)
	{
		gotoxy(X_MAINMENU,Y_MAINMENU+i);
		if(i==0)
		{
			textcolor(0);
			textbackground(15);
		}
		else if(i>0 && i<6)
		{
			textcolor(15);
			textbackground(0);
		}
		else if(i==6)
		{
			textcolor(4);
		}
		cprintf(menu[i]);
	}
	gotoxy(X_MAINMENU,Y_MAINMENU);
	textmode(2);
	textbackground(0);
	textcolor(15);
	int ch;
	//enabling and disabling options of the MAIN_MENU according to the keystrokes
	while(1)
	{
		textcolor(15);
		ch=getch();
		if(ch==0)
		{
			ch=getch();
			if(ch==DOWN_ARROW && wherey()<13)
			{
				disable(X_MAINMENU,wherey());
				enable(X_MAINMENU,wherey()+1);
			}
			if(ch==UP_ARROW && wherey()>7)
			{
				disable(X_MAINMENU,wherey());
				enable(X_MAINMENU,wherey()-1);
			}
		}
		else if(ch==ENTER && wherey()==7)
		{
			clrscr();
			textmode(2);
			textcolor(15);
			textbackground(0);
			details::addcontact();
			main_menu();
		}
		else if(ch==ENTER && wherey()==8)
		{
			clrscr();
			textmode(2);
			textcolor(15);
			textbackground(0);
			details::display_contacts();
			main_menu();
		}
		else if(ch==ENTER && wherey()==9)
		{
			clrscr();
			textmode(2);
			textbackground(0);
			clrscr();
			details::search_contact();
			main_menu();
		}
		else if(ch==ENTER && wherey()==10)
		{
			clrscr();
			textmode(2);
			textbackground(0);
			clrscr();
			details::del_contact();
			main_menu();
		}
		else if(ch==ENTER && wherey()==11)
		{
			clrscr();
			textmode(2);
			textbackground(0);
			clrscr();
			details::edit_contact();
			main_menu();
		}
		else if(ch==ENTER && wherey()==12)
		{
			clrscr();
			textmode(2);
			textbackground(0);
			clrscr();
			details::strsort();
			main_menu();
		}

		else if(ch==ENTER && wherey()==13)
			exit(0);
	}
}

//definition of enable function for enabling MAIN_MENU options
void enable(int x, int y)
{
	gotoxy(x,y);
	textbackground(15);
	textcolor(0);
	cprintf(menu[wherey()-7]);
}

//definition of disable function for disabling MAIN_MENU options
void disable(int x,int y)
{
	gotoxy(x,y);
	textbackground(0);
	textcolor(15);
	if(wherey()==13)
	{
		textcolor(4);
	}
	cprintf(menu[wherey()-7]);
}

//definition of the funtion to display the "add new contact" menu
void details::addcontact()
{
	textmode(2);
	d1.contact_id=get_last_id()+1;
	char id_str[25];
	clrscr();
	gotoxy(28, 5);
	textcolor(2);
	cprintf("ADD NEW CONTACT");
	//to print the menu items and textboxes
	for(int i=0; i<7; i++)
	{
		textcolor(15);
		textbackground(0);
		gotoxy(18, 8+(2*i));
		cprintf(addmenu[i]);
		gotoxy(X_TXTBOX, 8+(2*i));
		textcolor(0);
		textbackground(7);
		itoa(d1.contact_id, id_str, 10);
		cprintf("                    ");
		if(wherey()==8)
			cprintf(id_str);
	}
	gotoxy(35, 23);
	textcolor(4);
	cprintf("Save");
	gotoxy(X_TXTBOX,10);
	d1.get();
}

//getting the contact_id of the last record
int details::get_last_id()
{
	details d2;
	fout.open("Contact.dat", ios::app);
	fout.close();
	fin.open("Contact.dat", ios::in);
	if(fin==NULL)
	{
		cout<<"Could not open the required file.\nPress any key to exit";
		getch();
		exit(0);
	}
	fin.seekg(0, ios::end);
	int length;
	length = fin.tellg();
	int recsize = sizeof(details);
	if (length != 0)
	{
		fin.seekg(-recsize, ios::end);
		fin.read((char*)&d2, sizeof(d2));
		fin.close();
		return (d2.contact_id);
	}
	else
	{
		return (0);
	}
}

//to input the details according to the y position of the cursor
void details::get()
{
	gotoxy(X_TXTBOX, 10);
	int ch2;
	while(1)
	{
		if(wherey()==Y_TXTBOX1)
		{
			cin.getline(d1.fname, 10);
			strcat(d1.fname," ");
			gotoxy(X_TXTBOX, 12);
		}
		if(wherey()==12)
		{
			lname[0]='\0';
			cin.getline(d1.lname, 10);
			strcpy(d1.name, d1.fname);
			strcpy(d1.name,strcat(d1.name, d1.lname));
			len_name = strlen(d1.name);
			if(len_name > max_len_name)
			{
				max_len_name = len_name;
			}
			gotoxy(X_TXTBOX, 14);
		}
		if(wherey()==14)
		{
			date.getdob();
			gotoxy(X_TXTBOX,16);
		}
		if(wherey()==16)
		{
			cin.getline(add1, 15);
			gotoxy(X_TXTBOX,18);
		}
		if(wherey()==18)
		{
			add2[0] = '\0';
			cin.getline(add2,15);
			strcpy(add, add1);
			if(add2 != NULL)
			{
				strcat(add, ", ");
			}
			strcpy(add, strcat(add, add2));
			len_add = strlen(add);
			if(len_add > max_len_add)
			{
				max_len_add = len_add;
			}
			gotoxy(X_TXTBOX, 20);
		}
		if(wherey()==20)
		{
			cin.getline(d1.number,13);
			gotoxy(X_TXTBOX,23);
		}
		if(wherey()==23)
		{
			getch();
			if((ch2=getch())==ENTER)
			{
				fout.open("Contact.dat", ios::app);
				if(!fout)
				{
					cout<<"Could not load the required file.\nPress any key to exit.";
					getch();
					exit(0);
				}
				fout.write((char*)&d1, sizeof(d1));
				fout.close();
				textmode(2);
				textbackground(0);
				textcolor(15);
				main_menu();
			}
		}
	}
}

//function to show the details on the screen
void details::show()
{
	textmode(2);
	textbackground(0);
	textcolor(15);
	cout<<contact_id<<"\t"<<name<<setw(get_max_len_name()-strlen(name))<<"\t ";
	date.show();
	cout<<add<<setw(get_max_len_add()-strlen(add))<<"\t ";
	cout<<setw(14)<<number;
}

//to display all contacts
void details::display_contacts()
{
	fin.open("Contact.dat",ios::in);
	if (!fin)
	{
		cout<<"Could not read the required file.\nPress any key to exit.";
		getch();
		exit(0);
	}
	fin.seekg(0, ios::beg);
	int count=0;
	for(int i=1; ;) 							//eof() returns 1 if eof is reached, otherwise 0
	{
		fin.read((char*)&d1, sizeof(d1));
		if(fin.eof()) break;
		if(count == 0)
		{
			clrscr();
			cout<<"  ID\t  Name\t\t DOB\t"<<setw(get_max_len_add())<<"Address"<<"\t\tPhone Number";
			cout<<"\n--------------------------------------------------------------------------------\n";
		}
		count ++;
		if (count == 20*i)
		{
			cout<<"Press Enter to see the next records ";
			i++;
			getch();
			clrscr();
			cout<<"  ID\t  Name\t\t DOB\t"<<setw(get_max_len_add())<<"Address"<<"\t\tPhone Number";
			cout<<"--------------------------------------------------------------------------------\n";
		}
		d1.show();
		cout<<"\n";
	}
	getch();
	fin.close();
}

//function to get the length of the longest name for alignment
int details::get_max_len_name()
{
	details d2;
	ifstream fin("Contact.dat");
	if(!fin)
	{
		cout<<"Could not load required file while getting the longest name.";
		cout<<endl<<"Press any key to exit.";
		getch();
		exit(0);
	}
	while(!fin.eof())
	{
		fin.read((char*)&d2, sizeof(d2));
		if(max_len_name < strlen(d2.name))
		{
			max_len_name = strlen(d2.name);
		}
	}
	fin.close();
	return max_len_name;
}

//function to get the length of the longest address
int details::get_max_len_add()
{
	details d2;
	ifstream fin("Contact.dat");
	if(!fin)
	{
		cout<<"Could not load required file while getting the longest name.";
		cout<<endl<<"Press any key to exit.";
		getch();
		exit(0);
	}
	while(!fin.eof())
	{
		fin.read((char*)&d2, sizeof(d2));
		if(max_len_add < strlen(d2.add))
		{
			max_len_add = strlen(d2.add);
		}
	}
	fin.close();
	return max_len_add;
}

//definition of the function to search contacts - display of menu
void details::search_contact()
{
	textmode(2);
	clrscr();
	char *search_menu[] = {"1. By Name    ", "2. By Number  "};
	gotoxy(30,5);
	textcolor(11);
	cprintf("Search Contact");
	for(int i=0; i<2; i++)
	{
		gotoxy(30, 7+i);
		if(wherey()==7)
		{
			textbackground(15);
			textcolor(0);
		}
		else if(wherey()==8)
		{
			textbackground(0);
			textcolor(15);
		}
		cprintf(search_menu[i]);
	}
	gotoxy(X_SEARCHMENU, 7);
	char ch3;
	//enabling and disabling Search Menu options
	while(1)
	{
		ch3=getch();
		if (ch3==0)
		{
			ch3 = getch();
			if (ch3 == DOWN_ARROW  &&  wherey()==7)
			{
				gotoxy(X_SEARCHMENU, 7);
				textbackground(0);
				textcolor(15);
				cprintf(search_menu[0]);
				gotoxy(X_SEARCHMENU, 8);
				textbackground(15);
				textcolor(0);
				cprintf(search_menu[1]);
				gotoxy(X_SEARCHMENU, 8);
			}
			else if (ch3 == UP_ARROW && wherey()==8)
			{
				gotoxy(X_SEARCHMENU, 8);
				textbackground(0);
				textcolor(15);
				cprintf(search_menu[1]);
				gotoxy(X_SEARCHMENU, 7);
				textbackground(15);
				textcolor(0);
				cprintf(search_menu[0]);
				gotoxy(X_SEARCHMENU, 7);
			}
		}
		else if(ch3==ENTER && wherey()==7)
		{
			details::search_by_name();
		}
		else if(ch3==ENTER && wherey()==8)
		{
			details::search_by_num();
		}
	}
}

//function to search by name
void details::search_by_name()
{
	clrscr();
	textbackground(0);
	textcolor(15);
	details d2;
	char search[20], ch;
	for(int i=0; i<20; i++)
	{
		search[i]=NULL;
	}
	clrscr();
	cout<<"\nEnter the characters of the name to search :";
	int k=0;
	while(1)
	{
	 //	fin.seekg(0, ios::beg);                      // won't work once we reach the end of file. 'seekg' etc need the file pointer to be within the records and not beyond the end of file
		fin.open("Contact.dat", ios::in);
		if(fin == NULL)
		{
			cout<<"Couldn't load the file required for completing the search.\nPress any key to exit.";
			getch();
			exit(0);
		}
		ch=getch();
		if(ch==ENTER)
			break;
		clrscr();
		search[k++]=ch;
		cout<<endl<<search<<endl;
		cout<<"  ID"<<setw(get_max_len_name())<<"Name\t"<<"DOB\t"<<setw(get_max_len_add())<<"\tAddress"<<"\t\tPhone Number";
		cout<<"--------------------------------------------------------------------------------\n";

		for(int i=0; (!fin.eof()); i++)
		{
			fin.read((char*)&d2, sizeof(d2));
			if(fin.eof())
				break;
			for(int j=0; j<strlen(d2.name); j++)
			{
				if(strcmpi(substr(d2.name, j, strlen(search)), search)==0)
				{
					d2.show();
					cout<<endl;
					break;
				}
			}
		}
		fin.close();
	}
	cout<<endl<<"Search complete.";
	main_menu();
	getch();
}

//function to search by number
void details::search_by_num()
{
	clrscr();
	textbackground(0);
	textcolor(15);
	details d2;
	char search[20], ch;
	for(int i=0; i<20; i++)
	{
		search[i]=NULL;
	}
	clrscr();
	cout<<"\nEnter the digits of the phone number to search :";
	int k=0;
	while(1)
	{
	 //	fin.seekg(0, ios::beg);                      // won't work once we reach the end of file. 'seekg' etc need the file pointer to be within the records and not beyond the end of file
		fin.open("Contact.dat", ios::in);
		if(fin == NULL)
		{
			cout<<"Couldn't load the file required for completing the search.\nPress any key to exit.";
			getch();
			exit(0);
		}
		ch=getch();
		if(ch==ENTER)
			break;
		clrscr();
		search[k++]=ch;
		cout<<endl<<search<<endl;
		cout<<"  ID"<<setw(get_max_len_name())<<"Name\t"<<"DOB\t"<<setw(get_max_len_add())<<"\tAddress"<<"\t\tPhone Number";
		cout<<"\n--------------------------------------------------------------------------------\n";

		for(int i=0; (!fin.eof()); i++)
		{
			fin.read((char*)&d2, sizeof(d2));
			if(fin.eof())
				break;
			for(int j=0; j<strlen(d2.number); j++)
			{
				if(strcmpi(substr(d2.number, j, strlen(search)), search)==0)
				{
					d2.show();
					cout<<endl;
					break;
				}
			}
		}
		fin.close();
	}
	cout<<endl<<"Search complete.";
	main_menu();
	getch();
}

//function to delete contact
void details::del_contact()
{
	if(fin)
	{
		fin.close();
	}
	if(fout2)
	{
		fout2.close();
	}
	textmode(2);
	clrscr();
	char *del_menu[] = {"1. Delete Single Contact ", "2. Delete All Contacts   "};
	gotoxy(30,5);
	textcolor(11);
	cprintf("Delete Contact");
	for(int i=0; i<2; i++)
	{
		gotoxy(30, 7+i);
		if(wherey()==7)
		{
			textbackground(15);
			textcolor(0);
		}
		else if(wherey()==8)
		{
			textbackground(0);
			textcolor(15);
		}
		cprintf(del_menu[i]);
	}
	gotoxy(X_SEARCHMENU, 7);
	char ch3;
	//enabling and disabling Search Menu options
	while(1)
	{
		ch3=getch();
		if (ch3==0)
		{
			ch3 = getch();
			if (ch3 == DOWN_ARROW  &&  wherey()==7)
			{
				gotoxy(X_SEARCHMENU, 7);
				textbackground(0);
				textcolor(15);
				cprintf(del_menu[0]);
				gotoxy(X_SEARCHMENU, 8);
				textbackground(15);
				textcolor(0);
				cprintf(del_menu[1]);
				gotoxy(X_SEARCHMENU, 8);
			}
			else if (ch3 == UP_ARROW && wherey()==8)
			{
				gotoxy(X_SEARCHMENU, 8);
				textbackground(0);
				textcolor(15);
				cprintf(del_menu[1]);
				gotoxy(X_SEARCHMENU, 7);
				textbackground(15);
				textcolor(0);
				cprintf(del_menu[0]);
				gotoxy(X_SEARCHMENU, 7);
			}
		}
		else if(ch3==ENTER && wherey()==7)
		{
			clrscr();
			textbackground(0);
			textcolor(15);
			details::del_single();
			main_menu();
		}
		else if(ch3==ENTER && wherey()==8)
		{
			clrscr();
			textbackground(0);
			textcolor(15);
			details::del_all();
		}
	}
}

//function to delete a single record
void details::del_single()
{

	details d2;
	cout<<"Existing Contacts are :"<<endl;
	details::display_contacts();
	clrscr();
	textmode(2);
	textbackground(0);
	textcolor(15);
	fin2.open("Contact.dat", ios::in);
	if(!fin2)
	{
		cout<<"Couldn't open the file required for reading the existing contacts.\nPress any key to exit.";
		getch();
		exit(0);
	}
	fout2.open("Dummy.dat", ios::out);
	if(!fout2)
	{
		cout<<"Couldn't open the file required for copying the new contacts.\nPress any key to exit.";
		getch();
		exit(0);
	}
	int del_id;
	cout<<"Enter the id of the contact to delete : ";
	cin>>del_id;
	while(!fin2.eof())
	{
		fin2.read((char*)&d2, sizeof(d2));
		if(fin2.eof())
			break;
		if(del_id != d2.contact_id)
		{
			fout2.write((char*)&d2, sizeof(d2));
		}
	}
	fin2.close();
	fout2.close();
	remove("Contact.dat");
	rename("Dummy.dat", "Contact.dat");
	cout<<"Contact Deleted Successfully!!";
	if(fin)
	{
		fin.close();
	}
	getch();
}

//function to delete all the contacts
void details::del_all()
{
	remove("Contact.dat");
	fout.open("Contact.dat", ios::app);
	fout.close();
	main_menu();
}

//to display the edit contact menu
void details::edit_contact()
{
	int edit_id;
	details d2;
	cout<<"Enter the id of the contact to edit : ";
	cin>>edit_id;
	finout.open("Contact.dat", ios::in | ios::out);
	if(!finout)
	{
		cout<<"Couldn't access the required file for editing the record.\nPress any key to exit.";
		getch();
		exit(0);
	}
	while(!finout.eof())
	{
		finout.read((char*)&d2, sizeof(d2));
		if(finout.eof())
			break;
		if(d2.contact_id == edit_id)
		{
			d2.show();
			break;
		}
	}
	cout<<"\nEdit Contact? (Y/N)";
	char ch_ans;
	ch_ans=getche();
	if(ch_ans == 'N' || ch_ans == 'n' )
	{
		cout<<"\nContact not updated.\nPress Enter to exit.";
		getch();
		main_menu();
	}
	else if(ch_ans == 'Y' || ch_ans == 'y' )
	{
		int recsize=sizeof(details);
		finout.seekg(-recsize, ios::cur);
		textmode(2);
		char id_str[25];
		clrscr();
		gotoxy(28, 5);
		textcolor(2);
		cprintf("EDIT CONTACT");
		//to print the menu items and textboxes
		for(int i=0; i<7; i++)
		{
			textcolor(15);
			textbackground(0);
			gotoxy(18, 8+(2*i));
			cprintf(addmenu[i]);
			gotoxy(X_TXTBOX, 8+(2*i));
			textcolor(0);
			textbackground(7);
			itoa(d2.contact_id, id_str, 10);
			cprintf("                    ");
			if(wherey()==8)
				cprintf(id_str);
		}
		gotoxy(35, 23);
		textcolor(4);
		cprintf("Done");
		gotoxy(X_TXTBOX,10);
		textcolor(0);
		if(wherey()==Y_TXTBOX1)
		{
			cprintf(d2.fname);
			gotoxy(X_TXTBOX, 12);
		}
		if(wherey()==12)
		{
			cprintf(d2.lname);
			gotoxy(X_TXTBOX, 14);
		}
		if(wherey()==14)
		{
			d2.show_dob();
			gotoxy(X_TXTBOX,16);
		}
		if(wherey()==16)
		{
			cprintf(d2.add1);
			gotoxy(X_TXTBOX,18);
		}
		if(wherey()==18)
		{
			cprintf(d2.add2);
			gotoxy(X_TXTBOX,20);
		}
		if(wherey()==20)
		{
			cprintf(d2.number);
			gotoxy(35,23);
		}
		getch();
		gotoxy(X_TXTBOX, 10);
		int ch4;
		while(1)
		{
			ch4=getch();
			if(ch4==ENTER && wherey()<=18)
				gotoxy(X_TXTBOX, wherey()+2);
			else if(ch4==ENTER && wherey()==20)
				gotoxy(X_TXTBOX, 23);
			if(ch4==BCKSPC)
			{
				gotoxy(X_TXTBOX, wherey());
				textbackground(7);
				textcolor(0);
				cprintf("                    ");
				gotoxy(X_TXTBOX, wherey());
				if(wherey()==10)
				{
					char temp[10];
					char flush=ch4;
					cin.get(flush);
					cin.getline(temp,10);
					if(strlen(temp)>0)	strcpy(d2.fname, temp);
					strcat(d2.fname, " ");
					gotoxy(X_TXTBOX, 12);
				}
				if(wherey()==12)
				{
					char ch;
					cin.get(ch);
					char temp[10];
					cin.getline(temp,10);
					if(strlen(temp)>0)	strcpy(d2.lname, temp);
					strcpy(d2.name, d2.fname);
					strcpy(d2.name,(strcat(d2.name, d2.lname)));
					gotoxy(X_TXTBOX, 14);
				}
				if(wherey()==14)
				{
					dob date;
					date.getdob();
					gotoxy(X_TXTBOX, 16);
				}
				if(wherey()==16)
				{
					char temp[15];
					char ch;
					cin.get(ch);
					cin.getline(temp,15);
					if(strlen(temp)>0)	strcpy(d2.add1, temp);
					gotoxy(X_TXTBOX, 18);
				}
				if(wherey()==18)
				{
					char temp[15];
					char ch;
					cin.get(ch);
					cin.getline(temp,15);
					if(strlen(temp)>0)
					{
						strcpy(d2.add2, temp);
					}
					strcat(d2.add1, ", ");
					strcpy(d2.add, d2.add1);
					strcpy(d2.add, strcat(d2.add, d2.add2));
					gotoxy(X_TXTBOX, 20);
				}
				if(wherey()==20)
				{
					char ch;
					cin.get(ch);
					char temp[13];
					cin.getline(temp, 13);
					if(strlen(temp)>0)	strcpy(d2.number, temp);
					gotoxy(35, 23);
				}
			}
			else if(ch4==ENTER && wherey()==23)
			{
				finout.write((char*)&d2, sizeof(d2));
				break;
			}
		}
	}
	finout.close();
	textbackground(0);
	textcolor(15);
	main_menu();
}

//function to show the DOB only
void details::show_dob()
{
	date.edit_show();
}

char record[100][150];
//function to sort all the contacts
void details::strsort()
{
	textcolor(15);
	textbackground(0);
	details d2;
	fin.open("Contact.dat", ios::in);
	if(fin == NULL)
	{
		cout<<"Couldn't open the required file for sorting.\nPress any key to exit.";
		getch();
		exit(0);
	}
	char id_str[10];
	cout<<"\tName\tID\tAddress\t\tNumber                          \n";
	cout<<"--------------------------------------------------------\n";
	for(int i=0; !fin.eof(); i++)
	{
		fin.read((char*)&d2, sizeof(d2));
		if(fin.eof()) break;
		strcpy(record[i], d2.name);
		strcat(record[i], "\t");
		itoa(d2.contact_id, id_str, 10);
		strcat(record[i], id_str);
		strcat(record[i], "\t");
		strcat(record[i], d2.add);
		strcat(record[i], "\t");
		strcat(record[i], d2.number);
	}
	int n=i-1;
	for(i=i-1; i>=0; i--)
	{
		for(int j=i; j>=0; j--)
		{
			if(strcmpi(record[i], record[j])<0)
			{
				char temp[150];
				strcpy(temp,record[i]);
				strcpy(record[i], record[j]);
				strcpy(record[j], temp);
			}
		}
	}
	textmode(2);
	textcolor(15);
	textbackground(0);
	for(i=0; i<=n; i++)
	{
		cout<<record[i];
		cout<<endl;
	}
	getch();
	fin.close();
	main_menu();
}