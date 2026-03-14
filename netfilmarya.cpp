#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Film{
    char judul[100];
    float price;
    int year;
    float rating;
};

Film arr[100];
int n=0;

void loadFile(){
    FILE *file=fopen("netfilm_db.txt","r");

    if(file==NULL) return;

    while(fscanf(file," %[^;];%f;%d;%f\n",
        arr[n].judul,
        &arr[n].price,
        &arr[n].year,
        &arr[n].rating)!=EOF){

        n++;
    }

    fclose(file);
}

void saveFile(){
    FILE *file=fopen("netfilm_db.txt","w");

    for(int i=0;i<n;i++){
        fprintf(file,"%s;%.0f;%d;%.1f\n",
        arr[i].judul,
        arr[i].price,
        arr[i].year,
        arr[i].rating);
    }

    fclose(file);
}

void tambahFilm(){

    cin.ignore();

    cout<<"Judul Film : ";
    cin.getline(arr[n].judul,100);

    cout<<"Harga : ";
    cin>>arr[n].price;

    cout<<"Tahun : ";
    cin>>arr[n].year;

    cout<<"Rating : ";
    cin>>arr[n].rating;

    n++;

    saveFile();

    cout<<"Film berhasil ditambahkan\n";
}

void tampilFilm(){

    cout<<"\n===== DAFTAR FILM =====\n";

    for(int i=0;i<n;i++){

        cout<<i+1<<". "
        <<arr[i].judul<<" | "
        <<arr[i].price<<" | "
        <<arr[i].year<<" | "
        <<arr[i].rating<<endl;

    }
}

void bubbleSort(){

    for(int i=0;i<n-1;i++){

        for(int j=0;j<n-i-1;j++){

            if(strcmp(arr[j].judul,arr[j+1].judul)>0){

                Film temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;

            }

        }

    }

    cout<<"Data diurutkan berdasarkan Judul (Bubble Sort)\n";
}

int partition(int low,int high){

    float pivot=arr[high].rating;
    int i=low-1;

    for(int j=low;j<high;j++){

        if(arr[j].rating>pivot){

            i++;

            Film temp=arr[i];
            arr[i]=arr[j];
            arr[j]=temp;

        }

    }

    Film temp=arr[i+1];
    arr[i+1]=arr[high];
    arr[high]=temp;

    return i+1;
}

void quickSort(int low,int high){

    if(low<high){

        int pi=partition(low,high);

        quickSort(low,pi-1);
        quickSort(pi+1,high);

    }
}

int linearSearch(char key[]){

    for(int i=0;i<n;i++){

        if(strcmp(arr[i].judul,key)==0){
            return i;
        }

    }

    return -1;
}

int binarySearch(char key[]){

    int left=0;
    int right=n-1;

    while(left<=right){

        int mid=(left+right)/2;

        int cmp=strcmp(arr[mid].judul,key);

        if(cmp==0) return mid;

        else if(cmp<0) left=mid+1;

        else right=mid-1;

    }

    return -1;
}

void cariFilmAuto(){

    char key[100];

    cin.ignore();

    cout<<"Masukkan Judul Film : ";
    cin.getline(key,100);

    int index;

    if(n<30){

        cout<<"Menggunakan Linear Search\n";
        index=linearSearch(key);

    }else{

        bubbleSort();
        cout<<"Menggunakan Binary Search\n";
        index=binarySearch(key);

    }

    if(index!=-1){

        cout<<"Film ditemukan\n";
        cout<<arr[index].judul<<" | "
        <<arr[index].price<<" | "
        <<arr[index].year<<" | "
        <<arr[index].rating<<endl;

    }else{

        cout<<"Film tidak ditemukan\n";

    }
}

void testLinear(){

    char key[100];

    cin.ignore();

    cout<<"Judul Film : ";
    cin.getline(key,100);

    int index=linearSearch(key);

    if(index!=-1)
        cout<<"Film ditemukan (Linear Search)\n";
    else
        cout<<"Film tidak ditemukan\n";

}

void testBinary(){

    bubbleSort();

    char key[100];

    cin.ignore();

    cout<<"Judul Film : ";
    cin.getline(key,100);

    int index=binarySearch(key);

    if(index!=-1)
        cout<<"Film ditemukan (Binary Search)\n";
    else
        cout<<"Film tidak ditemukan\n";

}

int main(){

    loadFile();

    int pilih;

    do{

        cout<<"\n===== NETFILM MENU =====\n";
        cout<<"1. Tambah Film\n";
        cout<<"2. Tampilkan Film\n";
        cout<<"3. Sort Judul (Bubble Sort)\n";
        cout<<"4. Sort Rating (Quick Sort)\n";
        cout<<"5. Cari Film (Auto Search)\n";
        cout<<"6. Test Linear Search\n";
        cout<<"7. Test Binary Search\n";
        cout<<"0. Keluar\n";

        cout<<"Pilih Menu : ";
        cin>>pilih;

        switch(pilih){

            case 1:
                tambahFilm();
                break;

            case 2:
                tampilFilm();
                break;

            case 3:
                bubbleSort();
                tampilFilm();
                break;

            case 4:
                quickSort(0,n-1);
                tampilFilm();
                break;

            case 5:
                cariFilmAuto();
                break;

            case 6:
                testLinear();
                break;

            case 7:
                testBinary();
                break;

        }

    }while(pilih!=0);

}
