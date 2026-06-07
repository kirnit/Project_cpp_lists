#include <string>
#include <iostream>
using namespace std;

class STUDENT {
	string name;
	int age;
	float grade; 

public:
	string GetName() const {return name;} 
	int GetAge() const {return age;} 
	float GetGrade() const {return grade;} 
	void SetName(string nik) {name = nik;}
	void SetAge(int ag) {age = ag;} 
	void SetGrade(float gr) {grade = gr;}
	void Set(string nik, int ag, float gr) {
        name = nik;
        age = ag;
        grade = gr;
    };
    STUDENT* next;

    STUDENT(string n, int a, float g){ //конструктор для студента
        name = n;
        age = a; 
        grade = g;
        next = NULL; 
    }

    STUDENT() { //конструктор для первого
        name = "";
        age = 0; 
        grade = 0;
        next = NULL; 
    }


	void Show() {
        cout << "Имя: " << name << "; Возраст: " << age << "; Средний балл: " << grade << endl;
    };
};

void printSTUD(STUDENT* f){ //выводим на экран список всех студентов
    f->Show();
    if (f->next != NULL) printSTUD(f->next);
}

void add_STUD(STUDENT* f, string n, int a, float g){
    if (f->next != NULL) add_STUD(f->next, n, a, g);
    else f->next = new STUDENT(n,a,g);
}


void delall_STUD(STUDENT* f){
    if (f->next != NULL) delall_STUD(f->next);
    delete(f);
}

                //first         3        1             NULL
void delel_STUD(STUDENT* f, int nDel, int N, STUDENT* mom){
    if (N < nDel && f->next != NULL) delel_STUD(f->next, nDel, N+1, f);
    if (nDel == N) mom->next = f->next;
    if (N > nDel) return;
}

int menu(){
    cout << "0. EXIT\n" << 
            "1. Add student to the end\n" <<
            "2. Add student on exact place\n" <<
            "3. Print students\n" <<
            "4. Delete all students\n" <<
            "5. Delete exact student\n";
    int a;
    cin >> a;
    return a;
}

int main() {
    STUDENT *first = new STUDENT();
    bool alive = false;
    string n; int a; float g;
    while (true){
        switch(menu()){
            case 0: return 0;
                break;

            case 1:{ 
                cin >> n >> a >> g;
                if (!alive){
                    first = new STUDENT(n,a,g);
                    alive = true;
                } else add_STUD(first, n, a, g);
                break;}

            case 2: {
                int num;
                cout << "Enter the number of your student (from 1):\n";
                cin >> num;
                cout << "Enter the information about your student:\n";
                cin >> n >> a >> g;
                STUDENT *newstud = new STUDENT(n,a,g);
                STUDENT *curr = first;

                if (!alive){
                    first = new STUDENT(n,a,g);
                    alive = true;}
                
                else if (num==1){
                    newstud->next = first;
                    first = newstud;
                }
                else {
                    for (int i=0; i<(num-2); i++){
                        if (curr->next != NULL) curr = curr->next;}                    
                    newstud->next = curr->next;
                    curr->next = newstud;}
                break;}
                    
            case 3: {
                if (alive) printSTUD(first);
                else cout << "List is empty\n";
                break;}

            case 4: {
                if (alive) delall_STUD(first);
                alive = false;
                cout << "List has been cleared\n";
                break;}

            case 5: {
                cout << "Enter the number of the student to be deleted:\n";
                cin >> a; //кого удалить?
                if (a>1) delel_STUD(first, a, 1, NULL);
                else {
                    STUDENT* T = first; 
                    if (first->next != NULL) first = first->next;
                    else alive = false;
                } break;}

            default: cout << "ERROR\n";
        }
    }
}

