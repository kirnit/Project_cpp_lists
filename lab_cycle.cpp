#include <string>
#include <iostream>
using namespace std;

class STUDENT {
public:
	string name;
    int age;
    float grade;
    STUDENT *next, *mom; //ссылки на родителей и детей
    STUDENT(string n, int age, float grade){
        this->name = n;
        this->age = age;
        this->grade = grade;
        this->next = this;
        this->mom = this;
    }
    STUDENT* func(){
        return this;
    }

    STUDENT() {};

	void Show() {
        cout << "Имя: " << name << "; Возраст: " << age << "; Средний балл: " << grade << endl;
    };
};


void printSTUD(STUDENT* f, STUDENT* first){ 
    f->Show();
    if (f->next != first) printSTUD(f->next, first);
}

void add_STUD(STUDENT* f, STUDENT* first, string name, int age, float grade){
    if (f->next != first) add_STUD(f->next, first, name, age, grade);
    else {
        f->next = new STUDENT(name, age, grade);
        f->next->mom = f;
        f->next->next = first;
        first->mom = f->next;
    }
}

void delall_STUD(STUDENT* f, STUDENT* first){
    if (f->next != first) delall_STUD(f->next, first);
    delete(f);
}

                //first         3        1
void delel_STUD(STUDENT* f, int nDel, int N, STUDENT* mom, STUDENT* first){
    if (N < nDel && f->next != first) delel_STUD(f->next, nDel, N+1, f, first);
    if (nDel == N) {
        f->next->mom = f->mom;
        f->mom->next = f->next;
        delete(f);

    }
}

int menu(){
    cout << "0. EXIT\n" << 
            "1. Add student to the end\n" <<
            "2. Add student on exact place\n" <<
            "3. Print students\n" <<
            "4. Delete all students\n" <<
            "5. Delete exact student\n" <<
            "6. Print quantity of the students\n" <<
            "7. Add student on existing place\n";
    int a;
    cin >> a;
    return a;
}

int main() {
    STUDENT *first = new STUDENT();
    first->next = first;
    first->mom = first;
    bool alive = false;
    string n; int a, count=0; float g;
    while (true){
        switch(menu()){

            case 0: return 0;
                break;

            case 1:{ 
                cout << "Enter the name of your student: ";
                cin >> n;
                cout << "Enter the age of your student: ";
                cin >> a;
                cout << "Enter the grade of your student: ";
                cin >> g;
                if (!alive){
                    first = new STUDENT(n,a,g);
                    alive = true;} 
                    else {
                    add_STUD(first, first, n, a, g);}
                count++;
                break;}

            case 2: {
                int num;
                cout << "Enter the number of your student (from 1):\n";
                cin >> num;
                cout << "Enter information about your student:\n";
                cin >> n >> a >> g;
                STUDENT *newstud = new STUDENT(n,a,g);
                STUDENT *curr = first;

                if (!alive){
                    first = new STUDENT(n,a,g);
                    alive = true;}
                
                else if (num==1){
                    newstud->mom = first->mom;
                    newstud->next = first;
                    first->mom = newstud;
                    newstud->mom->next = newstud;
                    first = newstud;}
                else {
                    for (int i=0; i<(num-2); i++){
                        if (curr->next != first) curr = curr->next;}   
                    newstud->next = curr->next;
                    newstud->mom = curr;
                    curr->next->mom = newstud;
                    curr->next = newstud;}
                
                count++;
                break;}
                    
            case 3: {
                if (alive) printSTUD(first, first);
                else cout << "List is empty\n";
                break;}

            case 4: {
                if (alive) delall_STUD(first, first);
                alive = false;
                cout << "List has been cleared\n";
                count = 0;
                break;}

            case 5: {
                cout << "Enter the number of the student to be deleted:\n";
                cin >> a; 

                if (!alive) cout << "List is already empty";
                else if (first->next == first) {
                    delete(first);
                    alive = false;}
                else if (a>1) delel_STUD(first, a, 1, first, first);
                else {
                    STUDENT* T = first;
                    first->next->mom = first->mom;
                    first->mom->next = first->next;
                    first = first->next;
                    delete(T);
                } count--;
                break;}

            case 6: {
                cout << "Now you have " << count << " student(s) in your list\n";
                break;} 

            case 7: {
                int num;
                cout << "Enter the number of the student to be replaced:\n";
                cin >> num;
                cout << "Enter the name of your student: ";
                cin >> n;
                cout << "Enter the age of your student: ";
                cin >> a;
                cout << "Enter the grade of your student: ";
                cin >> g;
                STUDENT *t = new STUDENT(n,a,g);
                STUDENT *f = first;
                if (!alive) {cout << "The list is empty, firstly add students"; break;}
                if (count < num) {cout << "Incorrect number, try again"; break;}
                if (first->next == first){
                    delete(first);
                    first = t;}
                else {
                    for (int i=1; i<num; i++){
                        if (f->next != first) f = f->next;}   
                    t->next = f->next;
                    t->mom = f->mom;
                    f->next->mom = t;
                    f->mom->next = t;
                    if (f == first) first = t;}
                break;}

            default: cout << "ERROR\n";
        }
    }
}

