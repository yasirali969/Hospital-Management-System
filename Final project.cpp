#include<iostream>
#include<fstream>
#include <string>
using namespace std;
					// Doctor Data//
struct Doctor{
    string name;
    string specialist;
    string doctorID;
    string Day;
    int NoofApp;
};

                 // Patient Data //
struct Patient{
    string name;
    string age;
    string disease;
    string PatientID;
};

struct Disease{
    string dis;  // Treatment available for diseases
};

int size = 3;

void Menu(){
	cout << "======================================================\n";
	cout<<"1.Search Doctor\n";
	cout<<"2.Display Doctors\n";
	cout<<"3.Treatment availble disease\n";
	cout<<"4.Patient Data\n";
	cout<<"5.Search Patient\n";
	cout<<"6.Patient Appointment\n";
	cout<<"7.Display Doctors\n";
	cout<<"8.Add New Doctors\n";
	cout<<"9.No of Appointments for Doctors\n";
	cout<<"10.Doctor Feedback\n";
	cout<<"11.Exit\n";
	cout << "======================================================\n";
}

// ======================== FILE HANDLING FOR PATIENTS ========================
void Display (Patient P1[]){
	ofstream input("Patients.txt",ios::app);   // File for writing

    if (!input) {
        cout << "Error opening file!";
        return;
    }

 	input << "Name\tAge\tDisease\tPatientID" << endl << endl;
 	  for(int i = 0; i < size; i++){
       input<<P1[i].name<<"\t"<<P1[i].age<<"\t"<<P1[i].disease<<"\t"<<P1[i].PatientID<<endl;
    }
    input.close();
    cout<<"Patient Data stored successfully\n";
}

// ======================== SEARCH PATIENT ========================
void SearchPatient(Patient P1[]){
	string Pname;
	bool Search=false;
	cin.ignore();
	cout<<"Enter the Patient name to search :\n";
	getline(cin,Pname);

    for(int i = 0; i < size; i++){
       if(Pname==P1[i].name){
    	   cout << P1[i].name << "\t" << P1[i].age << "\t" << P1[i].disease << "\t" << P1[i].PatientID<< endl;
		   cout<<"-------------------------------------------------------\n";
		   Search=true;
		   break;
	   }
	}
	if(!Search){
        cout<<"Sorry! Patient is not Admitted here \n";
    }
}

// ======================== SEARCH DOCTOR ========================
void SearchDoctor(Doctor Dr[]){
	string Name;
	bool Search=false;
	cin.ignore();
   	cout<<"Enter the Doctor name to search :\n";
	getline(cin,Name);

    for(int i = 0; i < 4; i++){
      	 if(Name==Dr[i].name){
      	   cout << Dr[i].name << "\t" << Dr[i].specialist << "\t" << Dr[i].doctorID << "\t" << Dr[i].Day << "\t" << Dr[i].NoofApp<< endl;
		   cout<<"-------------------------------------------------------\n";
		   Search=true;
		   break;
		 }
	}
	if(!Search){
        cout<<"Sorry! Doctor is not Available \n";
    }
}

// ======================== DISPLAY DOCTORS ========================
void DisplayDoctors(Doctor Dr[], int n){
    cout << "Name\tSpecialist\tDoctorID\tDay\tNoOfApp\n";
    for(int i = 0; i < n; i++){
        cout << Dr[i].name << "\t" << Dr[i].specialist << "\t" << Dr[i].doctorID << "\t" << Dr[i].Day << "\t" << Dr[i].NoofApp << endl;
    }
}

// ======================== ADD NEW DOCTOR ========================
void NewDoctors(Doctor NewDoc[], Doctor Dr[]){
    for(int i = 0; i < 4; i++){
        NewDoc[i] = Dr[i];
    }
    for(int i=4;i<6;i++){
        cin.ignore();
        cout<<"Add Doctor "<<i+1<<endl;
        cout << "Name: ";
        getline(cin,NewDoc[i].name);
        cout << "Specialist: ";
        getline(cin,NewDoc[i].specialist);
        cout << "DoctorID: ";
        getline(cin,NewDoc[i].doctorID);
        cout<<"Day for checkup: ";
        getline(cin,NewDoc[i].Day);
        cout<<"No of Appointments: ";
        cin>>NewDoc[i].NoofApp;
    }

    // File handling for doctors
    ofstream fout("Doctors.txt",ios::app);
    if(fout){
        for(int i=0;i<6;i++){
            fout<<NewDoc[i].name<<"\t"<<NewDoc[i].specialist<<"\t"<<NewDoc[i].doctorID<<"\t"<<NewDoc[i].Day<<"\t"<<NewDoc[i].NoofApp<<endl;
        }
        fout.close();
        cout<<"Doctor Data saved successfully\n";
    }
}

// ======================== Count NO OF APPOINTMENTS ========================
void NoAppointment(Doctor Dr[], Patient P1[], Disease d1[]){
    int count[4] = {0};
    for(int i = 0; i < size; i++){
        for(int j=0;j<4;j++){
            if(P1[i].disease == d1[j].dis)
                count[j]++;
        }
    }

    cout << "\n===== Appointment Count =====\n";
    for(int i=0;i<4;i++)
        cout << "No of Patients for " << Dr[i].name << ": " << count[i] << endl;
    cout << "======================================================\n";
}

// ======================== APPOINTMENT ========================
void Appointment(Doctor Dr[], Patient P1[], int size){
    for(int i = 0; i < size; i++){
        bool appointed = false;

        for(int j = 0; j < 4; j++){

            // Disease → Specialist mapping
            if(
               (P1[i].disease == "Thrombosis" && Dr[j].specialist == "Cardiologist") ||
               (P1[i].disease == "BrainHemorrhage" && Dr[j].specialist == "Neurologist") ||
               (P1[i].disease == "Ringworm" && Dr[j].specialist == "Dermatologist") ||
               (P1[i].disease == "Fever" && Dr[j].specialist == "Radiologist") // if no GP
              )
            {
                if(Dr[j].NoofApp > 0){
                    Dr[j].NoofApp--;

                    cout << "Patient " << P1[i].name 
                         << " appointed to " << Dr[j].name 
                         << " on " << Dr[j].Day << endl;

                    ofstream fout("Appointments.txt", ios::app); // append mode
                    fout << P1[i].name << "\t" 
                         << Dr[j].name << "\t" 
                         << Dr[j].Day << endl;
                    fout.close();

                    appointed = true;
                    break;
                }
            }
        }

        if(!appointed){
            cout << "No available doctor for " 
                 << P1[i].name 
                 << " with disease " 
                 << P1[i].disease << endl;
        }
    }
}

// ======================== DOCTOR RATING ========================
void RatingDoctors(Doctor Dr[], int n){
    string name;
    int rating;
    cin.ignore();
    cout<<"Enter the Doctor name: ";
    getline(cin,name);
    cout<<"Enter the rating (1-5): ";
    cin>>rating;

    // Save rating to file
    ofstream fout("DoctorRatings.txt", ios::app);
    fout<<name<<"\t"<<rating<<endl;
    fout.close();

    cout<<"Rating saved for "<<name<<endl;
}

// ======================== MAIN ========================
int main(){
	
					// Doctors (Declaration+Initialization)
    Doctor Dr[4]= {
        {"Dr. Ali Khan", "Cardiologist", "DOC001", "Monday", 5},
        {"Dr. Sara Ahmed", "Neurologist", "DOC002", "Tuesday", 5},
        {"Dr. Hamza Malik", "Dermatologist", "DOC003", "Wedday", 5},
        {"Dr. Zainab Shah", "Radiologist", "DOC004", "Thrsday", 5}
    };

			       //  Diseases (Declaration+Initialization)
    Disease d1[4] = {{"Thrombosis"},{"BrainHemorrhage"},{"Ringworm"},{"Fever"}};
                   
                  // Patient Declaration
    Patient P1[size];
                 
				  // New Doctors array Declaration
    Doctor NewDoc[6];
                 
                 // Login System 
    string Username, Password;
    const string adminUser = "Mavericks";
    const string adminPass = "804";

    cout << "\n===== ADMIN LOGIN =====\n";
    cout << "Enter Username: ";
    cin >> Username;
    cout << "Enter Password: ";
    cin >> Password;

    if(Username != adminUser || Password != adminPass){
        cout << "\nInvalid Username or Password!\n";
        return 0;
    }
    cout << "\nLogin Successful!\n";
    
    
                // Switch Choices 

    int choice;
    
    while(true){
       
	   	Menu(); // Display Menu
       
	    cout<<"Enter the choice :";
        cin>>choice;

        switch(choice){
        	
        	case 1 : 
			SearchDoctor(Dr); 
			break;
			
        	case 2:
			DisplayDoctors(Dr, 4);
			break;
			
        	case 3:
        	cout <<"Diseases whose treatment is available:\n";
        		for(int i = 0; i < 4; i++) 
				cout << d1[i].dis << endl;
        	break;
        	
			case 4:
        		cin.ignore();
        		for(int i = 0; i < size; i++){
        			cout<<"\nPatient "<<i+1<<endl;
	        		cout<<"Enter Name: ";
	        		getline(cin,P1[i].name);
	        		cout<<"Enter Age: ";
	        		getline(cin,P1[i].age);
	        		cout<<"Enter Disease: ";
	        		getline(cin,P1[i].disease);
	        		cout<<"Enter PatientID: ";
	        		getline(cin,P1[i].PatientID);
	        }
	        Display(P1); // File handling for patients
        	break;
        	
        	case 5:
			SearchPatient(P1); 
			break;
        	
			case 6: 
			Appointment(Dr, P1,size); 
			break;
			
        	case 7:
			DisplayDoctors(Dr, 4); 
			break;
			
        	case 8:
			NewDoctors(NewDoc, Dr); 
			DisplayDoctors(NewDoc, 6); 
			break;
			
        	case 9:
			NoAppointment(Dr, P1, d1);
			break;
			
        	case 10:
			 RatingDoctors(Dr, 4);
			break;
			
        	case 11: 
			return 0;
			
        	default:
			cout << "Invalid Choice!\n";
		    break;
        }
    }
}
