#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//고객 정보를 저장할 구조체 선언
typedef struct _person {
	char name[30];
	char phone[15];
}person;

//제품 구매를 위한 구조체를 선언
typedef struct _product {
	char product_name[100];
	char buyer_name[30];
}product;

void print_main();
void view_membership(); //고객 조회
void add_membership();	//회원 가입
void buy_product();		//제품 구매
void change_phonenumber();	//전화번호 변경
void delete_membership();	//고객 탈퇴
void find();				//조회 - 교차검색

//사용자가 입력하는 정보를 파일에 저장하기 위해 파일명을 변수에 고정함(전역)
const char *membership = "c:\\Temp\\membership.txt";
const char *product_file = "c:\\Temp\\buy_product.txt";

int main()
{
	char select = 0;	//사용자가 선택하는 번호를 저장하기 위해 select변수를 선언
	puts("고객 정보 관리 및 판매 프로그램 \n");
	puts("---------------------------------------\n");

	while (select != 7)
	{
		print_main();
		select = _getche();
		getchar();
		system("cls");

		switch (select)
		{
		case '1': view_membership();
			break;
		case '2': add_membership();
			break;
		case '3':
			view_membership();
			buy_product();
			break;
		case '4':
			view_membership();
			change_phonenumber();
			break;
		case '5':
			view_membership();
			delete_membership();
			break;
		case '6':
			find();
			break;
		case '7': return 0;
			break;
		default: printf("\n 잘못 입력했습니다. 다시 선택해주세요.\n");
		}
	}
	return 0;
}

void print_main()
{
	printf("\n환영합니다 고객님*^^*\n");
	printf("원하시는 업무의 번호를 입력해주세요 \n");

	printf("\n\n1번 : 고객 정보 조회\n");
	printf("2번 : 회원 가입\n");
	printf("3번 : 제품 구매\n");
	printf("4번 : 휴대 전화 번호 수정\n");
	printf("5번 : 회원 탈퇴\n");
	printf("6번 : 구매 이력 및 구매자 확인\n");
	printf("7번 : 끝내기\n\n");
}

//고객 정보 조회 함수
void view_membership()
{
	//구조체 배열 선언
	person per[10] = { "","" };	//고객을 10명으로 가정
	int i, cnt = 0;

	FILE *rfp, *wfp;

	rfp = fopen(membership, "r"); //고객 정보 파일을 읽기 모드로 염

	if (rfp == NULL)
	{
		puts("\n **고객 정보 파일에 고객 정보가 하나도 없습니다.** \n");
		wfp = fopen(membership, "w"); //빈 파일 생성
		fclose(wfp);
		return;
	}
	//저장된 내용이 하나도 없을때 순서는 fread->cnt->feof종료.
	//저장된 내용이 하나가 있을때 순서는 fread->cnt->fraed->cnt->feof종료.
	for (i = 0; i < 10; i++)
	{
		fread(&per[i], 1, sizeof(person), rfp);
		if (feof(rfp))
			break;
		cnt++;

	}
	if (cnt == 0)
	{
		printf("\n****저장된 정보가 하나도 없습니다.****\n");
	}

	for (i = 0; i < cnt; i++)
	{
		printf("%s %s\n", per[i].name, per[i].phone);
		//난 여기서 %s하고, per[i]하면 되는 줄 알았는데 name은 데이터형이 있는데 per은 없어서 하나하나 지정해줘야함.
	}

	fclose(rfp);
	printf("\n\n");
}

//회원 가입 함수
//배열 안 쓰는 이유 : 회원가입을 1명만 해서
void add_membership()
{
	//구조체 변수를 선언
	person per1 = { "","" };

	FILE *wfp;

	memset(&per1, 0, sizeof(person)); //구조체 0으로 초기화

	wfp = fopen(membership, "a"); //파일을 추가 모드로 열기. 쓰기 모드로 열면 기존의 정보가 모두 지워짐

	printf("회원가입 도와드리겠습니다.\n\n");
	printf("이름을 입력해주세요 : ");
	gets_s(per1.name);
	printf("전화번호를 입력해주세요 : ");
	gets_s(per1.phone);

	fwrite(&per1, 1, sizeof(person), wfp);

	fclose(wfp);
	system("cls");
}

//전화 번호 변경 함수
void change_phonenumber()
{
	person per1[10] = { "", "" }; //기존에 있던 10명 구조체
	person new_person = { "", "" }; //전번 바꿀 새로운 사람 구조체
	int i, ret;
	int cnt = 0;

	FILE *rfp, *wfp;

	memset(&per1, 0, sizeof(person) * 10); //구조체 10개 0으로 초기화
	memset(&new_person, 0, sizeof(person));

	rfp = fopen(membership, "r"); //파일을 읽기 모드로 열기
	if (rfp == NULL) //파일이 NULL이면
	{
		puts("\n고객 정보 파일이 없습니다. \n"); //문자열 출력
		return;
	}

	for (i = 0; i < 10; i++)
	{
		fread(&per1[i], 1, sizeof(person), rfp); //rfp파일에서 읽어옴

		if (feof(rfp))
			break;
		cnt++; //cnt증가 - ex) 7명이면 7명까지 cnt 셈
	}

	printf("이름을 입력해주세요 : ");
	gets_s(new_person.name);
	printf("전화번호를 입력해주세요 : ");
	gets_s(new_person.phone);

	for (i = 0; i < cnt; i++) //위에서 센 cnt 만큼
	{
		ret = strcmp(new_person.name, per1[i].name); //새로운 사람의 이름을 per1이름과 비교해서 ret에 넣음
		if (ret == 0)	//일치하는게 있으면 나와라.
		{
			per1[i] = new_person; //new_person을 per1[i]에 넣음
			break;
		}
	}

	wfp = fopen(membership, "w"); //파일을 쓰기 모드로 염
	for (i = 0; i < cnt; i++) //위의 세어진 cnt만큼 for문 실행하고
	{
		fwrite(&per1[i], 1, sizeof(person), wfp); //wfp 파일에 저장
	}
	fclose(wfp);
}

//회원 탈퇴 함수
void delete_membership()
{
	person per1[10] = { "","" };
	person delete_person = { "","" };

	//읽기 전에 초기화
	//
	product prod1[10] = { "","" };

	int i = 0, cnt = 0, ret = 0;
	int delete_person_number = -1; // 0번째 실수로 삭제 안하려고 만들었다.

	FILE *rfp, *wfp;
	FILE *frfp, *fwfp;

	//char file_copy[200] = "";
	//char data[200] = "";

	memset(&per1, 0, sizeof(person) * 10); //구조체 10개 0으로 초기화
	memset(&delete_person, 0, sizeof(person));

	rfp = fopen(membership, "r");

	if (rfp == NULL)
	{
		puts("\n 고객 정보 파일이 없습니다. \n");
		return;
	}

	printf("**탈퇴**\n\n");
	printf("이름을 입력해주세요 : ");
	gets_s(delete_person.name);

	for (i = 0; i < 10; i++)
	{
		fread(&per1[i], 1, sizeof(person), rfp);

		if (feof(rfp))
			break;
		cnt++;
	}

	fclose(rfp);

	for (i = 0; i < cnt; i++)
	{
		ret = strcmp(delete_person.name, per1[i].name);
		if (ret == 0)
		{
			delete_person_number = i;
			break;
		}
	}

	wfp = fopen(membership, "w");

	for (i = 0; i < cnt; i++)
	{
		if (delete_person_number == i)
			continue;
		fwrite(&per1[i], 1, sizeof(person), wfp);
	}
	fclose(wfp);

	memset(&prod1, 0, sizeof(product) * 10);

	frfp = fopen(product_file, "r");

	//product_file을 읽어와 전부 복사, delete_person_number랑 같으면 걔 빼고 복사하기
	for (i = 0; i < 10; i++)
	{
		fread(&prod1[i], 1, sizeof(product), rfp);

		if (feof(rfp))
			break;
		cnt++;
	}
	fclose(frfp);

	fwfp = fopen(product_file, "w");

	//delete_person.name랑 같으면 continue하기
	for (i = 0; i < cnt; i++)
	{
		ret = strcmp(delete_person.name, prod1[i].buyer_name);
		if (ret == 0)
			continue;
		fwrite(&prod1[i], 1, sizeof(product), fwfp);
	}
	fclose(fwfp);
}

//제품 구매 함수
void buy_product()
{
	FILE *rfp, *wfp;

	product prod = { "", "" };

	wfp = fopen(product_file, "a"); //고객 정보 파일을 추가 모드로 연다.

	memset(&prod, 0, sizeof(product)); // 구조체 초기화방법

	//만약 파일이 없다면
	if (wfp == NULL)
	{
		rfp = fopen(product_file, "w"); //빈 파일을 만든다.
		fclose(rfp);
		wfp = fopen(product_file, "a"); //다시 파일을 추가 모드로 연다.
	}

	puts("**제품 구매**\n");
	puts("이름을 입력해주세요 : ");
	gets_s(prod.buyer_name);

	puts("\n\n1. 스킨\n2.선크림\n3.립스틱\n\n");
	puts("구매하실 제품을 입력해주세요 : ");
	gets_s(prod.product_name);

	//파일에 구조체 단위로 쓰기
	fwrite(&prod, 1, sizeof(product), wfp);

	fclose(wfp);

	system("cls");
}

//구매 이력 및 구매자 확인(교차 검색)
void find()
{
	FILE *rfp;

	product prod[100];
	memset(prod, 0, sizeof(product) * 100); // 구조체 배열 전체 초기화

	char tmp_prod[30] = "", tmp_name[30] = ""; //제품 검색, 이름 검색 배열 선언
	int i, count = 0;
	int choose;

	rfp = fopen(product_file, "r");

	for (i = 0; ; i++)
	{
		//fwrite(파일 쓰기), fread(파일 읽기) 
		fread(&prod[i], 1, sizeof(product), rfp);
		count++;
		if (feof(rfp))
			break;
	}

	puts("\n1번 : 이름 검색 -> 구매 이력 리스트\n");
	puts("2번 : 제품 검색 -> 구매자 리스트\n");

	printf("번호를 고르세요 : ");
	choose = _getche();
	printf("\n");

	if (choose == '1')
	{
		printf("이름 입력 : ");
		gets_s(tmp_name);	//이름 입력
		printf("");

		for (i = 0; i < count; i++)
		{
			if (strcmp(tmp_name, prod[i].buyer_name) == 0) //입력한 이름이랑 product구조체에서 구매자 이름이 일치할 때
			{
				printf("%s\n", prod[i].product_name);	//구조체의 제품명이 출력
			}
		}
	}
	if (choose == '2')
	{
		printf("제품 입력 : ");
		gets_s(tmp_prod);
		printf("");

		for (i = 0; i < count; i++)
		{
			if (strcmp(tmp_prod, prod[i].product_name) == 0) //입력한 제품이랑 product구조체에서 제품 이름이 일치할 때
			{
				printf("%s\n", prod[i].buyer_name);	//구조체의 구매자가 출력
			}
		}
	}
	fclose(rfp);
}