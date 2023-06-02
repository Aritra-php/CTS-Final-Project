//********Header files************//

#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

//********End of header files********//

//**********Class declaration**********//

class student
{
    int rollno;
    char name[50];
    int phy_marks, chem_marks, math_marks, eng_marks, cs_marks;
    double per;
    char grade;
    
    void calculate(); //function to calculate marks
public:
    void getdata(); //functon to calculate grade
    void showdata() const; //funtion to accept data from user
    void showtabular() const; //function to show table 
    int retrollno() const;
};

void student::calculate() //inherit function from class(inheritence)
{
    per=(phy_marks+chem_marks+math_marks+eng_marks+cs_marks)/5.0;
    if(per>=75)
    {
        grade='A';
    }
    else if(per>=60)
    {
        grade='B';
    }
    else if(per>=50)
    {
        grade='C';
    }
    else
    {
       grade='D'; 
    }
}
void student::getdata()
{
    cout<<"\n Please enter the roll number of student::";
    cin>>rollno;
    cout<<"\n Please enter the name of the student::";
    cin>>name;
    cout<<"\n Please enter the marks obtained in physics::";
    cin>>phy_marks;
    cout<<"\n Please enter the marks obtained in chemistry::";
    cin>>chem_marks;
    cout<<"\n Please enter the marks obtained in maths::";
    cin>>math_marks;
    cout<<"\n Please enter the marks obtained in english::";
    cin>>eng_marks;
    cout<<"\n Please enter the marks obtained in computer science::";
    cin>>cs_marks;
    calculate();//
}
void student::showdata() const
{
    cout<<"\nThe roll number of student is::"<<rollno;
    cout<<"\nThe name of the student is::"<<name;
    cout<<"\nThe marks obtained in physics::"<<phy_marks;
    cout<<"\nThe marks obtained in chemistry::"<<chem_marks;
    cout<<"\nThe marks obtained in maths::"<<math_marks;
    cout<<"\nThe marks obtained in english::"<<eng_marks;
    cout<<"\nThe marks obtained in computer science::"<<cs_marks;
    cout<<"\nThe percentage obtained by the student is::"<<per;
    cout<<"\nThe grade obtained by the student is::"<<grade;
}
void student::showtabular() const
{
    cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<" "<<phy_marks<<setw(10)<<" "<<chem_marks<<setw(10)<<" "<<
    math_marks<<setw(10)<<" "<<eng_marks<<setw(10)<<" "<<cs_marks<<setw(10)<<" "<<per<<setw(10)<<" "<<
    grade<<setw(10)<<endl;
}
int student::retrollno() const
{
    return rollno;
}
//**************End class declaration*****************//

//*************Function declaration****************//

void write_student(); //write record in binary file
void display_all(); //red all record from binay file
void display_sp(int); 
void modify_student(int); //modify student record
void delete_student(int); //delete record
void class_result(); //display all records in tabular format
void result(); //display result MENU
void intro(); //display introduction
void entry_menu(); //display entry MENU

//************End of function declaration*************//

//******************Main function******************//
int main()
{
    char ch;
    cout.setf(ios::fixed|ios::showpoint);
    cout<<setprecision(2);
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\t MAIN MENU";
        cout<<"\n\n\t 1.RESULT MENU";
        cout<<"\n\n\t 2.ENTRY/EXIT MENU";
        cout<<"\n\n\t 3.EXIT";
        cout<<"\n\n\tPLEASE SELECT YOUR CHOICE(1-3)";
        cin>>ch;
        switch(ch)
        {
            case '1': result();
                break;
            case '2': entry_menu();
                break;
            case '3': 
                break;
            default: cout<<"\a";
        }
    }while(ch!='3');
    return 0;
}
//**********End of main function**************//

//**********Function to write in file*****************//

void write_student()
{
    student st;
    ofstream outfile;
    outfile.open("student.dat",ios::binary|ios::app);
    st.getdata();
    outfile.write(reinterpret_cast<char *> (&st), sizeof(student));
    outfile.close();
        cout<<"\n\nStudent record has been created";
    cin.ignore();
    cin.get();
}

//************End of function*********//

//***********Function to read all records from file*************//

void display_all()
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
        cout<<"File could not open!! Press any key....";
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\nDISPLAY ALL RECORDS\n\n\n";
    while(infile.read(reinterpret_cast<char *> (&st),sizeof(student)))
    {
        st.showdata();
        cout<<"\n\n=======================\n\n";
    }
    infile.close();
    cin.ignore();
    cin.get();
}

//**************End of function*****************//

//*******Function to read specific record from fie*************//

void display_sp(int n)
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
        cout<<"File could not open!! press any key....";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag=false;
    while(infile.read(reinterpret_cast<char *> (&st),sizeof(student)))
    {
        if(st.retrollno()==n)
        {
            st.showdata();
            flag=true;
        }
    }
    infile.close();
    if(flag=false)
    {
        cout<<"\n\nRecord does not exist";
    }
    cin.ignore();
    cin.get();
}

//***********End of function****************//

//************Function to modify record***********//

void modify_student(int n)
{
    bool found=false;
    student st;
    fstream File;
    File.open("student.dat",ios::binary|ios::in|ios::out);
    if(!File)
    {
        cout<<"\n\nFile could not open!! press any key...";
        cin.ignore();
        cin.get();
        return;
    }
    while(!File.eof() && found==false)
    {
        File.read(reinterpret_cast<char *> (&st),sizeof(student));
        if(st.retrollno()==n)
        {
            st.showdata();
            cout<<"\n\nPlease enter the new data of the students\n\n"<<endl;
            st.getdata();
                int pos=(-1)*static_cast<int>(sizeof(st));
                File.seekp(pos,ios::cur);
                File.write(reinterpret_cast<char *> (&st),sizeof(student));
                cout<<"\n\nRecord Updated";
                found=true;
        }
    }
    File.close();
    if(found==false)
    {
        cout<<"\n\nRecord not found";
    }
    cin.ignore();
    cin.get();
}
//**********End of function****************//

//************Function to delete record*************//

void delete_student(int n)
{
    student st;
    ifstream infile;
    infile.open("student.dat",ios::binary);
    if(!infile)
    {
        cout<<"File could not open!!! press any key...."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat",ios::out);
    infile.seekg(0,ios::beg);
    while(infile.read(reinterpret_cast<char *> (&st),sizeof(student)))
    {
        if(st.retrollno()!=n)
        {
            outFile.write(reinterpret_cast<char *> (&st),sizeof(student));
        }
    }
    outFile.close();
    infile.close();
    remove("student.dat");
    rename("student.dat","temp.dat");
    cout<<"\n\n Record deleted\n\n";
    cin.ignore();
    cin.get();
}

//***********End of function*******************//

//***********Function to display grade report*************//

void class_result()
{
    student st;
    ifstream inFile;
    inFile.open("student.dat",ios::binary);
    if(!inFile)
    {
        cout<<"File could not open!!! press any key..."<<endl;
        cin.ignore();
        cin.get();
        return;
    }
    cout<<"\n\n\tSTUDENT REPORT CARD\n\n";
    cout<<"=============================================\n";
    cout<<"Roll NO         Name       P   C   M   E   CS    Per   GRADE"<<endl;
    cout<<"=============================================\n";
    while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
    {
        st.showtabular();
    }
    cin.ignore();
    cin.get();
    inFile.close();
}

//*****************End of function*****************//

//******************Function to display result menu************//

void result()
{
	char ch;
	int rollno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rollno;
				display_sp(rollno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//***************End of function**************************//

//*************Introduction function*************//

void intro()
{
    cout<<"\n\n\n\t\t STUDENT"<<endl;
    cout<<"\n\n\n\t\t REPORT CARD MANAGEMENT SYSTEM"<<endl;
    cin.get();
}

//***********End of function***************//

//************Entry/Edit menu function***********//

void entry_menu()
{
    char ch;
    int num;
    system("cls");
    cout<<"\n\n\t ENTRY MENU";
    cout<<"\n\n\t 1.CREATE STUDENT RECORD";
    cout<<"\n\n\t 2.DISPLAY STUDENT RECORD";
    cout<<"\n\n\t 3.SEARCH STUDENT RECORD";
    cout<<"\n\n\t 4.EDIT STUDENT RECORD";
    cout<<"\n\n\t 5.DELETE STUDENT RECORD";
    cout<<"\n\n\t 6.BACK TO MAIN MENU";
    cout<<"\n\n\t Please choose an option(1-6)";
    cin>>ch;
    system("cls");
    switch(ch)
    {
        case '1': write_student(); break;
        case '2': display_all(); break;
        case '3': cout<<"\n\n\tPlease enter the roll number::"; cin>>num;
                    display_sp(num); break;
        case '4': cout<<"\n\n\tPlease enter the roll number::"; cin>>num;
                    modify_student(num); break;
        case '5': cout<<"\n\n\tPlease enter the roll number::"; cin>>num;
                    delete_student(num); break;
        case '6': break;
        default:  cout<<"\a"; entry_menu();
    }
    
}

//************End of the function*****************//