#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <winbgim.h>
#include <windows.h>
#include <string.h>
#include <time.h>

#define N 1000

/*KHAI BAO NGUYEN MAU HAM*/

//----------DO HOA --------------------------------------
void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void SetColor(int backgound_color, int text_color);
void ShowScrollbar(BOOL Show);
void gotoxy(int column, int line);
void textrun(char* a,int max,int timesleep,int x, int y);
void textnhapnhay(char* a,int max,int timesleep,int x,int y);
void ptable(int x, int y, int startx, int starty);
void ptable2(int x, int y, int startx, int starty);
void dohoa();
//-------------------------------------------------------
struct atmdata{
	long long account_numbers;	
	int PIN[6];
	char name[30];
	long long account_balance;
	int infor1;
}/*atm*/;
typedef atmdata DS[N];
struct outputdata{
	long long account_numbers;
	int infor1;
	long long infor2;
	long long account_numbers2;
};
typedef outputdata DS1[N];
void init(int* a, int n,int x,int y);
//void out(int* a,int n);
void pass_word(int* password, int n, int* dem, int* k);
void khach_hang(DS atm,DS1 out,int &count_out,int &n,long long mk2);
//int Search(FILE *Data,int n,long long x);
void Read(FILE *Data);
//void Read2(FILE *Sodu);
void giaodich(DS atm,DS1 out,int &count_out,int point,long long st,int &num);
void Display(DS A, int n);
int Search(DS A,int n,long long x);
void InsertElement(DS A,int &n,int t,long long x,int y[],char z[]);
void DeleteElement(DS A,int &n,int t);
void InputfileData(DS A,int &n);
void InputfileSodu(DS A,int &n);
void OutputfileSodu(DS A,int &n);
void inthu(DS A,int n);
/********************************************************/
//Khoi tao danh sach A;
/*HAM CHINH*/
int main(){
	//--------DO HOA---------------------------------------------
	ShowScrollbar(0);
	SetWindowSize(61,21);
	SetScreenBufferSize(60,20);
	backmain :
	dohoa();
	//------------------------------------------------------------
	char a[1000] = "------------MAY ATM TU DONG-------------";
	textrun(a,5,200,20,10);
	char b[1000] = "Vui long cho trong giay lat";
	textnhapnhay(b,2,400,15,10);
	
	
	// --------Nhan Vien IT nhap Password de KHOI DONG may ATM-----------
	FILE *f = fopen("password.txt","r");
	//Tim so ki tu trong password
	int n;
	fscanf(f,"%d",&n);
	
	int dem =0, k =1;
	int i;
	int mk[n];
	long long mk2;
	//Lay password
	for(i=0;i<n;i++){
		fscanf(f,"%d",&mk[i]);
	}
	fscanf(f,"%lld",&mk2);
	do{
		//Nhap password
		pass_word(mk,n,&dem,&k);
		if(k == 0){
			gotoxy(20,16);
			printf("Ban nhap sai %d lan !",dem);
			gotoxy(20,17);
			printf("Con %d lan thu lai.\n",5 - dem);
			k = 1;
		}
		else k = 0;
	} while(dem < 5 && k == 1);
	if(dem < 5 ) {
		backmain2:
		dohoa();
		int q; 
		//In chu ra man hinh
		char bacham[100] = ".... .";
		gotoxy(17,9);
		printf("DANG KHOI DONG ATM");
		textrun(bacham,2,550,36,9);
		ptable2(51,18,4,1);
		ptable(9,3,14,6);		gotoxy(17,7);		printf("Chon 1");
		ptable(9,3,14,9);		gotoxy(17,10);		printf("Chon 2");
		ptable(20,3,25,6);		gotoxy(28,7);		printf("KHOI DONG ATM");
		ptable(20,3,25,9);		gotoxy(28,10);		printf("THOAT");
		gotoxy(0,19);
		scanf("%d",&q);
		switch(q){
			case 1 : {
				system("cls");
				//Nhan Vien IT da khoi dong thanh cong. ATM tro thanh giao dien cho khach hang!
				DS atm;
				DS1 out;
				int n = 0,count_out = 0;
				InputfileData(atm,n);
				InputfileSodu(atm,n);
				for(int i=1;i<=n;i++) atm[i].infor1 = 0;
				khach_hang(atm,out,count_out,n,mk2);
				//IN DANH SACH GIAO DICH
				FILE *output = fopen("danhsachgiaodich.txt","w");
				for(int j=0;j<=count_out;j++){
					fprintf(output,"%lld, %d, %lld, %lld\n",out[j].account_numbers,out[j].infor1,out[j].infor2,out[j].account_numbers2);
				}
				fclose(output);
				//CAP NHAT DU LIEU
				OutputfileSodu(atm,n);
				gotoxy(15,12);		printf("ATM shutting down ......");
				Sleep(5000);
				system("cls");
				Sleep(5000);
				break;
			}
			case 2 :	goto backmain;
			default: 	goto backmain2;
		}
	}
	else {
		dohoa();
		Sleep(2000);
		ptable(20,3,19,9);
		gotoxy(24,10);
		printf("Vo Hieu Hoa!");
		Sleep(3000);
		return 0;
	}

	//Dong file password.txt
	fclose(f);
	//--------------------------------------------------------------------//
	getch();
	return 0;
}
/********************************************************************************/
/*HAM CHUC NANG*/
void init(int* a, int n,int x,int y){
	int i=0;
	gotoxy(x,y); printf("* * * * * *");
	gotoxy(0,13);
	do{
		scanf("%d",&a[i]);
		gotoxy(x+2*i,y); printf("X");
		gotoxy(0,14+i);
		i++;
	}while(i<n);
}
void pass_word(int* password, int n, int* dem,int *k){
	int i;
	int a[n];
	ptable(20,3,19,8);
	ptable(20,3,19,12);
	gotoxy(24,9);
	printf("Nhap Mat Khau");
	init(a,n,25,13);
	for(i=0;i<n;i++)
		if(a[i] != password[i]){
			(*k) = 0;
			printf("Sai Mat Khau!");
			dohoa();
			break;
		}
	(*dem)++;
}
void khach_hang(DS atm,DS1 out,int &count_out,int &n,long long mk2){
	dohoa();
	long long x;
	int z[6];
		ptable(19,3,7,7);
		gotoxy(9,8);
		printf("Nhap So Tai Khoan");
		ptable(24,3,28,7);
		gotoxy(30,8);
		scanf("%lld",&x);
		if(x == mk2) return;
		if(Search(atm,n,x) == -1){
			char char_01[100] = "SO TAI KHOAN KHONG TON TAI!";
			textnhapnhay(char_01,1,1000,17,13);
			char char_02[100] = "Vui long nhap lai...";
			textnhapnhay(char_02,1,1000,20,14);
			khach_hang(atm,out,count_out,n,mk2);
		}
		else{
			int point = Search(atm,n,x);
			gotoxy(8,12);		printf("Xin Chao, khach hang %s",atm[point].name);
			Sleep(3000);
			dohoa();
			int i;
			for(i=0;i<6;i++) z[i] = atm[point].PIN[i];
			int dem = 0;
			int k = 1;
			do{
				pass_word(z,6,&dem,&k);
				if(k == 0){
					gotoxy(20,16);
					printf("Ban nhap sai %d lan !",dem);
					gotoxy(20,17);
					printf("Con %d lan thu lai.\n",5 - dem);
					k = 1;
					Sleep(500);
				}
				else k = 0;
			} while(dem < 5 && k == 1);
			if(dem < 5){
				/* MAN HINH DAU */
				quaylaitudau:
				dohoa();
				gotoxy(14,6);printf("Vui long lua chon loai giao dich");
				ptable(6,3,5,9);	gotoxy(6,10);	printf("Chon 1");
				ptable(12,3,12,9);	gotoxy(14,10);	printf("RUT TIEN");
				ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 2");
				ptable(12,3,12,12);	gotoxy(14,13);	printf("XEM SO DU");
				ptable(6,3,48,9);	gotoxy(49,10);	printf("Chon 3");
				ptable(13,3,34,9);	gotoxy(35,10);	printf("CHUYEN KHOAN");
				ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 4");
				ptable(13,3,34,12);	gotoxy(42,13);	printf("THOAT");
				/* CHON YEU CAU CAN THUC HIEN */
				int counter1;
				quaylai1 :
				gotoxy(0,19);	
				scanf("%d",&counter1);
   				if((counter1 == 1 || counter1 == 3) && atm[point].infor1 == 5){
					gotoxy(7,17);	printf("Quy khach da thuc hien 5 lan giao dich hom nay!");
					goto quaylai1;
				}
				switch(counter1)
   				{
					case 1:{
       					quaylai :
						dohoa();
						int counter2;
						gotoxy(14,5);printf("Xin vui long lua chon so tien");
						ptable(6,3,5,6);	gotoxy(6,7);	printf("Chon 1");
						ptable(12,3,12,6);	gotoxy(14,7);	printf("100,000");
						ptable(6,3,5,9);	gotoxy(6,10);	printf("Chon 2");
						ptable(12,3,12,9);	gotoxy(14,10);	printf("200,000");
						ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 3");
						ptable(12,3,12,12);	gotoxy(14,13);	printf("500,000");
						ptable(6,3,5,15);	gotoxy(6,16);	printf("Chon 4");
						ptable(12,3,12,15);	gotoxy(14,16);	printf("1,000,000");
						ptable(6,3,48,6);	gotoxy(49,7);	printf("Chon 5");
						ptable(13,3,34,6);	gotoxy(38,7);	printf("2,000,000");
						ptable(6,3,48,9);	gotoxy(49,10);	printf("Chon 6");
						ptable(13,3,34,9);	gotoxy(40,10);	printf("SO KHAC");
						ptable(6,3,48,15);	gotoxy(49,16);	printf("Chon 7");
						ptable(13,3,34,15);	gotoxy(42,16);	printf("THOAT");
						gotoxy(0,19);
						scanf("%d",&counter2);
						switch(counter2){
							case 1:
				            {
								int num10=0;
							    giaodich(atm,out,count_out,point,100000,num10);
							    if(num10==1) goto quaylaitudau;
							    else khach_hang(atm,out,count_out,n,mk2);
							    break;
							}
							case 2:
				            {
							    int num11=0;
							    giaodich(atm,out,count_out,point,200000,num11);
							    if(num11==1) goto quaylaitudau;
							    else khach_hang(atm,out,count_out,n,mk2);
							    break;
				            }
							case 3:
				            {
							    int num12=0;
							    giaodich(atm,out,count_out,point,500000,num12);
							    if(num12==1) goto quaylaitudau;
							    else khach_hang(atm,out,count_out,n,mk2);
							    break;
				            }
							case 4:
				            {
							    int num13=0;
							    giaodich(atm,out,count_out,point,1000000,num13);
							    if(num13==1) goto quaylaitudau;
							    else khach_hang(atm,out,count_out,n,mk2);
							    break;
				            }
							case 5:
				            {
							    int num14=0;
							    giaodich(atm,out,count_out,point,2000000,num14);
							    if(num14==1) goto quaylaitudau;
							    else khach_hang(atm,out,count_out,n,mk2);
							    break;
				            }
							case 6:
				            {
					            dohoa();
								ptable(19,3,7,7);	gotoxy(9,8);	printf("So tien can rut");
								ptable(24,3,28,7);	gotoxy(30,8);
								long long tienrut;
								scanf("%lld",&tienrut);
								int num15=0;
							    giaodich(atm,out,count_out,point,tienrut,num15);
							    if(num15==1) goto quaylaitudau;
							    else khach_hang(atm,out,count_out,n,mk2);
							    break;
				            }
							case 7:		goto quaylaitudau;
							default:	goto quaylai;
						}
						break;
					} 
					case 2:{
						back :	
						dohoa();
						gotoxy(6,9);		printf("So du tai khoan cua quy khach la: %lld VND",atm[point].account_balance);
						gotoxy(6,11);		printf("Quy khach co muon thuc hien tiep giao dich khong?");
			        	ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 1");
						ptable(12,3,12,12);	gotoxy(14,13);	printf("CO");
						ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 2");
						ptable(13,3,34,12);	gotoxy(42,13);	printf("KHONG");
						gotoxy(0,19);
						int p;
						scanf("%d",&p);
						switch(p){
							case 1: goto quaylaitudau;
							case 2: khach_hang(atm,out,count_out,n,mk2); break;
							default: goto back;
						}
						break;
					}
					case 3:{
						back3 :
						dohoa();
					    gotoxy(20,4);	printf("CHUYEN TIEN");
					    gotoxy(6,6);	printf("STK CHUYEN DI : %lld",atm[point].account_numbers);
					    gotoxy(12,7);	printf("%s",atm[point].name);
					    gotoxy(6,8);	printf("STK NGUOI NHAN: ");
					    long long tk;
					    scanf("%lld",&tk);
					    int point2 = Search(atm,n,tk);
					    if(tk==atm[point].account_numbers){
					    	gotoxy(16,12);	printf("Trung STK chuyen di!");
					    	Sleep(2000);
							goto back3;	
						}
						if(point2 == -1){
							gotoxy(16,12);	printf("STK khong ton tai!");
							Sleep(2000);
							goto back3;
						}
						gotoxy(12,9);	printf("%s",atm[point2].name);
			        	ptable(6,3,5,10);gotoxy(6,11);printf("Chon 1");
						ptable(13,3,12,10);gotoxy(14,11);printf("Nhap lai STK");
						ptable(6,3,5,13);gotoxy(6,14);printf("Chon 2");
						ptable(13,3,12,13);gotoxy(14,14);printf("Nhap tien");
						ptable(6,3,48,13);gotoxy(49,14);printf("Chon 3");
						ptable(13,3,34,13);gotoxy(42,14);printf("THOAT");
						gotoxy(0,19);
						int q;	scanf("%d",&q);
						switch(q){
							case 1: goto back3;
							case 2: break;
							case 3: goto quaylaitudau;
						}
						system("cls");
						dohoa();
					    gotoxy(20,4);	printf("CHUYEN TIEN");
					    gotoxy(6,6);	printf("STK CHUYEN DI : %lld",atm[point].account_numbers);
					    gotoxy(12,7);	printf("%s",atm[point].name);
					    gotoxy(6,8);	printf("STK NGUOI NHAN: %lld",atm[point2].account_numbers);
					    gotoxy(12,9);	printf("%s",atm[point2].name);
					    gotoxy(6,10);	printf("SO TIEN: ");
					    long long ct;
						scanf("%lld",&ct);
						back31 :
						ptable(6,3,5,13);gotoxy(6,14);printf("Chon 1");
						ptable(13,3,12,13);gotoxy(14,14);printf("Tiep tuc");
						ptable(6,3,48,13);gotoxy(49,14);printf("Chon 2");
						ptable(13,3,34,13);gotoxy(42,14);printf("THOAT");
						gotoxy(0,19);
						scanf("%d",&q);
						switch(q){
							case 1: break;
							case 2: goto quaylaitudau;
							default: goto back31;
						}
					    if(atm[point].account_balance>=ct)
						{
							int hoadon;
							atm[point].account_balance-=ct;
							atm[point2].account_balance+=ct;
							back32 :
							dohoa();
					    	gotoxy(6,5);		printf("Chuyen tien thanh cong!");
					    	gotoxy(6,6);		printf("So du cua quy khach la: %lld VND",atm[point].account_balance);
							gotoxy(19,8);		printf("BAN CO MUON IN HOA DON?");
				        	ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 1");
							ptable(12,3,12,12);	gotoxy(14,13);	printf("CO");
							ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 2");
							ptable(13,3,34,12);	gotoxy(42,13);	printf("KHONG");
							gotoxy(0,19);		scanf("%d",&q);
							switch(q){
								case 1: hoadon = 1000; break;
								case 2: hoadon = 0; break;
								default: goto back32;
							}
							atm[point].account_balance-=hoadon;
							atm[point].infor1+=1;
							out[count_out].account_numbers = atm[point].account_numbers;
							out[count_out].infor1 = 2;
							out[count_out].infor2 = ct+hoadon;
							out[count_out++].account_numbers2 = atm[point2].account_numbers;
							back33 :
							dohoa();
							gotoxy(6,11);		printf("Quy khach co muon thuc hien tiep giao dich khong?");
				        	ptable(6,3,5,12);gotoxy(6,13);printf("Chon 1");
							ptable(12,3,12,12);gotoxy(14,13);printf("CO");
							ptable(6,3,48,12);gotoxy(49,13);printf("Chon 2");
							ptable(13,3,34,12);gotoxy(42,13);printf("KHONG");
							gotoxy(0,19);		scanf("%d",&q);
							switch(q){
								case 1: goto quaylaitudau;
								case 2: khach_hang(atm,out,count_out,n,mk2); break;
								default: goto back33;
							}
						}
						else
						{
							back34 :
							dohoa();
							gotoxy(13,10);		printf("SO DU TAI KHOAN KHONG DU!");
							gotoxy(6,11);		printf("Quy khach co muon thuc hien tiep giao dich khong?");
				        	ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 1");
							ptable(12,3,12,12);	gotoxy(14,13);	printf("CO");
							ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 2");
							ptable(13,3,34,12);	gotoxy(42,13);	printf("KHONG");
							gotoxy(0,19);		scanf("%d",&q);
							switch(q){
								case 1: goto quaylaitudau;
								case 2: khach_hang(atm,out,count_out,n,mk2); break;
								default: goto back34;
							}
						}
						break;
					}
					case 4:{
						dohoa();
						gotoxy(10,11);		printf("CAM ON QUY KHACH DA SU DUNG DICH VU");
			        	Sleep(2000);
						system("cls");
						khach_hang(atm,out,count_out,n,mk2);
						break;
					}
					default:{
						goto quaylaitudau;
					}
				}
			}
			else{
				system("cls");
				khach_hang(atm,out,count_out,n,mk2);			
			}
		}
}
void Read(FILE *Data){
	char tx[10];
	int i;
	long long x;
	int y[6];
	char z[30];
  	fscanf(Data,"%lld",&x);
	for(i=0;i<6;i++){
	fscanf(Data,"%d",&y[i]);
	}
	fgets(tx,10,Data);
	fgets(z,30,Data);
}
void giaodich(DS atm,DS1 out,int &count_out,int point,long long st,int &num){
	    dohoa();
	    int q,hoadon,p;
		if(atm[point].account_balance>=st)
        {
        	gotoxy(19,8);		printf("BAN CO MUON IN HOA DON?");
        	ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 1");
			ptable(12,3,12,12);	gotoxy(14,13);	printf("CO");
			ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 2");
			ptable(13,3,34,12);	gotoxy(42,13);	printf("KHONG");
			gotoxy(0,19);
			scanf("%d",&q);
			if(q==1) hoadon = 1000;
			else hoadon = 0;
			dohoa();
			atm[point].account_balance-=(st+hoadon);
			atm[point].infor1+=1;
			out[count_out].account_numbers = atm[point].account_numbers;
			out[count_out].infor1 = 1;
			out[count_out].infor2 = st+hoadon;
			out[count_out++].account_numbers2 = 0;
			gotoxy(19,7);		printf("GIAO DICH THANH CONG!");
			gotoxy(6,9);		printf("So du con lai cua quy khach la: %lld VND",atm[point].account_balance);
			gotoxy(6,11);		printf("Quy khach co muon thuc hien tiep giao dich khong?");
        	ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 1");
			ptable(12,3,12,12);	gotoxy(14,13);	printf("CO");
			ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 2");
			ptable(13,3,34,12);	gotoxy(42,13);	printf("KHONG");
			back :
			gotoxy(0,19);
			int p;
			scanf("%d",&p);
			switch(p){
				case 1: num=1; break;
				case 2: num=0; break;
				default: goto back;
			}
        }
		else
        {
 			gotoxy(8,8);		printf("SO TIEN CUA QUY KHACH KHONG DU DE THUC HIEN!");
			gotoxy(6,11);		printf("Quy khach co muon thuc hien tiep giao dich khong?");
        	ptable(6,3,5,12);	gotoxy(6,13);	printf("Chon 1");
			ptable(12,3,12,12);	gotoxy(14,13);	printf("CO");
			ptable(6,3,48,12);	gotoxy(49,13);	printf("Chon 2");
			ptable(13,3,34,12);	gotoxy(42,13);	printf("KHONG");
			back2 :
			gotoxy(0,19);
			int p;
			scanf("%d",&p);
			switch(p){
				case 1: num=1; break;
				case 2: num=0; break;
				default: goto back2;
			}
	    }
}
void Display(DS A, int n){
	int i;
	for(i=1;i<=n;i++){
		printf("\n%lld\n%s",A[i].account_numbers,A[i].name);
		for(int j=0;j<=5;j++) printf("%d",A[i].PIN[j]);
	}
}
int Search(DS A,int n,long long x){
	int i = 1;
	while((i<=n) && (x != A[i].account_numbers)) i++;
	if(i<=n) return i;
	else return -1;
}
void InsertElement(DS A,int &n,int t,long long x,int y[],char z[]){
	int i;
	if((n<=N) && (t>=1) && (t<=n+1)){
		for(i=n;i>=t;i--) 
			A[i+1] = A[i];
		strcpy(A[t].name,z);
		A[t].account_numbers = x;
		for(int j=0;j<=5;j++)
				A[t].PIN[j] = y[j];
		n++;
	}
}
void DeleteElement(DS A,int &n,int t){
	int i;
	if((t>=1) && (t<=n)){
		for(i=t+1;i<=n;i++){
			A[i-1] = A[i];
		}
		n--;
	}
}
void InputfileData(DS A,int &n){
	int k=0,q=1;
	long long x;
	int y[6];
	char z[30];
	FILE *data = fopen("data.txt","r");
	while(!feof(data)){
		Read(data);
		k++;
	}
	rewind(data);
	do{
		char tx[10];
		int i;
  		fscanf(data,"%lld",&x);
		for(i=0;i<6;i++){
		fscanf(data,"%d",&y[i]);
		}
		fgets(tx,10,data);
		fgets(z,30,data);
		InsertElement(A,n,q,x,y,z);
		q++;
		k--;
	}while(k>0);
	rewind(data);
	fclose(data);
}
void OutputfileSodu(DS A,int &n){
	FILE *sodu = fopen("sodu.txt","w");
	for(int i=1;i<=n;i++){
		fprintf(sodu,"%lld\n%lld\n",A[i].account_numbers,A[i].account_balance);
	}
	fclose(sodu);
}
void InputfileSodu(DS A,int &n){
	long long x;
	long long y;
	FILE *sodu = fopen("sodu.txt","r");
	for(int i=1;i<=n;i++){
		fscanf(sodu,"%lld",&x);
		fscanf(sodu,"%lld",&y);
		A[i].account_balance = y;	
	}
	rewind(sodu);
	fclose(sodu);
}
void inthu(DS A,int n){
	printf("\n----------------------------------------------");
	Display(A,n);
	printf("\n----------------------------------------------");
}
/****************************************************/
void SetWindowSize(SHORT width, SHORT height){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void SetScreenBufferSize(SHORT width, SHORT height){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}
void ShowScrollbar(BOOL Show){
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}
void SetColor(int backgound_color, int text_color){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
void gotoxy(int column, int line){
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void textrun(char* a,int max,int timesleep, int x, int y){
	char  b[1000];
	char  c[40];
	strcpy(b, a);
	strcat(a, b);
	int i,j=0;
	for (i = 0; i < strlen(a); i++)
	{
		j++;
		strncpy(c, a + i, 20);
		c[20] = 0;
		Sleep(timesleep);
		gotoxy(x,y);
		puts(c);
		if (i == strlen(b)) i = 0;
		if (j > max){
			dohoa();
			break;
		}
	}
}
void textnhapnhay(char* a,int max,int timesleep,int x,int y){
	int i;
	char b ;
	for(i =0; i< max ; i++){
		gotoxy(x, y);
		puts(a);
		Sleep(timesleep);
		dohoa();
		Sleep(timesleep);
	}
}
void ptable(int x, int y, int startx, int starty){
	int i,j;
	for(j = 0; j<y;j++){
		gotoxy(startx,starty+j);
		if(j == 0){
			for(i=0;i<x;i++){
				if(i == 0) printf("%c",218);
				printf("%c",196);
				if(i == x - 1) printf("%c\n",191);
			}
		}
		else{
			if( j == y -1){
				for( i =0;i<x;i++){
					if( i == 0) printf("%c",192);
					printf("%c",196);
					if(i == x -1) printf("%c\n",217);
				}
			}
			else{
				printf("%c",179);
				gotoxy(x + 1 + startx,j + starty);
				printf("%c\n",179);
			}
		}
	}
}
void ptable2(int x, int y, int startx, int starty){
	int i,j;
	for(j = 0; j<y;j++){
		gotoxy(startx,starty+j);
		if(j == 0){
			for(i=0;i<x;i++){
				if(i == 0) printf("%c",178);
				printf("%c",178);
				if(i == x - 1) printf("%c\n",178);
			}
		}
		else{
			if( j == y -1){
				for( i =0;i<x;i++){
					if( i == 0) printf("%c",178);
					printf("%c",178);
					if(i == x -1) printf("%c\n",178);
				}
			}
			else{
				printf("%c",178);
				gotoxy(x + 1 + startx,j + starty);
				printf("%c\n",178);
			}
		}
	}
}
void dohoa(){
	system("cls");
	SetColor(15,0);
    ptable(55,20,2,0);
	ptable2(51,18,4,1);
	gotoxy(17,2);
	printf("NGAN HANG BACH KHOA DA NANG");
	gotoxy(8,3);
	printf("---------------------------------------------");
}
/****************************************************************/
