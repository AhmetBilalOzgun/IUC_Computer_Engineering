#include <iostream>
#include <string>

struct Appointment {
    std::string patientName;
    double time;          
    int duration;         
    Appointment* next;
};

double time_agg(double t,int d){
    int start_hours = (int)t;                 
    int start_minutes = (int)((t - start_hours) * 100); 

    int total_minutes = start_minutes + d;

    int added_hours = total_minutes / 60;   
    int final_minutes = total_minutes % 60; 

    int final_hours = start_hours + added_hours;

    double final_time = final_hours + (final_minutes / 100.0);

    return final_time;
    
}

bool checkConflict(Appointment* head, double newTime, int newDuration) {
    double newEndTime = time_agg(newTime, newDuration);
    
    if (newTime < 9.00 || newEndTime > 17.00) {
        return true;
    }

    for (Appointment* current = head; current != nullptr; current = current->next) {
        double currentEndTime = time_agg(current->time, current->duration);

        if (newTime < currentEndTime && current->time < newEndTime) {
            return true;
        }
    }
    return false; 
}

void printAll(Appointment* head){

    int count=1;
    if (head==nullptr){
        std::cout<<"Liste bos. Hiç randevu yok."<<std::endl;
        return;
    }
    for(Appointment* i=head; i!=nullptr; i=i->next){
        std::cout<<count<<". Randevu: "<<i->patientName<<" | Saat: "<<i->time<<" | Sure: "<<i->duration<<" dk"<<std::endl;
        count++;
    }
}

void printFromTime(Appointment* head, double time){
    int count=1;
    bool found=false;
    for(Appointment* i=head; i!=nullptr; i=i->next){
        if(i->time>=time){
            std::cout<<count<<". Randevu: "<<i->patientName<<" | Saat: "<<i->time<<" | Sure: "<<i->duration<<" dk"<<std::endl;
            found=true;
            count++;
        }
    }
    if (!found){
        std::cout << time << " saatinden sonra randevu bulunamadi." << std::endl;
    }
}

void insertAppointment(Appointment*& head, std::string name, double time, int duration) {

    Appointment* newAppointment = new Appointment{name, time, duration, nullptr};
    
    if (head == nullptr || time < head->time) {
        newAppointment->next = head;
        head = newAppointment;
        return;
    }

    Appointment* current = head;
    Appointment* previous = nullptr;

    while (current != nullptr && current->time < time) {
        previous = current;
        current = current->next;
    }

    if (previous != nullptr) {
        previous->next = newAppointment;
        newAppointment->next = current;
    }
}

void deleteAppointment(Appointment*& head, double time){
    Appointment* temp = head;
    Appointment* prev = nullptr;

    if (temp != nullptr && temp->time == time) {
        head = temp->next; 
        delete temp;       
        return;
    }

    
    while (temp != nullptr && temp->time != time) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cout << "Saat " << time << " olan bir randevu bulunamadi" << std::endl;
        return;
    }

    prev->next = temp->next;

    delete temp;

}


int totalBusyMinutes(Appointment* head){
    int total = 0; 
    
    for(Appointment* i = head; i != nullptr; i = i->next){
         total += i->duration; 
    }

    return total;
}


double suggestNextAvailable(Appointment* head, double startTime) {
    
    const double END_OF_DAY = 17.00;
    
    if (startTime < 9.00) {
        startTime = 9.00;
    }

    double potentialAvailableTime = startTime; 

    Appointment* current = head;

    while (current != nullptr) {
        double currentAppointmentEndTime = time_agg(current->time, current->duration);

        if (current->time >= potentialAvailableTime) {
            
 
            if (potentialAvailableTime < END_OF_DAY) {
                return potentialAvailableTime; 
            } else {
                return -1.0; // 
            }
        }
        
        if (currentAppointmentEndTime > potentialAvailableTime) {
            potentialAvailableTime = currentAppointmentEndTime;
        }

        current = current->next;
    }

    if (potentialAvailableTime < END_OF_DAY) {
        return potentialAvailableTime; 
    }

    return -1.0; 
}




int main(){
    bool menu=true;
    Appointment* head = nullptr;
    while (menu==true){
    int userInput;
    std::cout<< "========== RANDEVU PLANLAMA =========="<<std::endl;
    std::cout<< "1. Tum randevulari listele"<<std::endl;
    std::cout<< "2. Belirli bir saatten sonraki randevulari goster"<<std::endl;
    std::cout<< "3. Yeni randevu ekle"<<std::endl;
    std::cout<< "4. Randevu sil"<<std::endl;
    std::cout<< "5. Toplam dolu sureyi hesapla"<<std::endl;
    std::cout<< "6. Ilk uygun zamani oner"<<std::endl;
    std::cout<< "0. Cikis"<<std::endl;
    std::cout<< "Seciminiz:";
    std::cin>>userInput;

    if (userInput==1){
        printAll(head);
    }
    else if(userInput==2){
        double time;
        std::cout<<"Sonrasindaki randevulari gormek istediginiz saat: "<<std::endl;
        std::cin >> time;
        printFromTime(head, time);

    }
    else if(userInput==3){
        std::string name;
        int duration;
        double time;
        std::cout<<"Adiniz (Sadece ilk isminizi girin): "<<std::endl;
        std::cin>>name;
        std::cout<<"Randevu almak istediğiniz saat: "<<std::endl;
        std::cin>>time;
        std::cout<<"Randevu suresi: "<<std::endl;
        std::cin>> duration;
        bool conflict=checkConflict(head,time,duration);
        if(conflict==false){
            insertAppointment(head,name,time,duration);
        }
        else{
            std::cout<<"Almaya calistiginiz randevu ya mesai saatleri disinda ya da baska bir randevu ile cakisiyor."<<std::endl;
        }
    }
    else if(userInput==4){
        double time;
        std::cout<<"Silmek istediginiz randevunun saatini girin: "<<std::endl;
        std::cin>>time;
        deleteAppointment(head, time);
    }
    else if(userInput==5){
        std::cout<<totalBusyMinutes(head)<<" Dakika dolu."<<std::endl;
    }
    else if(userInput==6){
        double startTime;
        std::cout<<"Saati giriniz: "<<std::endl;
        std::cin>> startTime;
        std::cout<<"Bir soonraki boş saat: "<<suggestNextAvailable(head, startTime)<<std::endl;
        
    }
    else if(userInput==0){
        Appointment* current = head;
        while (current != nullptr) {
            Appointment* next = current->next;
            delete current;
            current = next;
        }
        menu=false;
    }
    else{
        std::cout << "Gecersiz secim. Lutfen tekrar deneyin." << std::endl;
    }
    
    }
}