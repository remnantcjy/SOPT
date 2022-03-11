#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//�� ������ ������ ����ü ����
typedef struct _person {
	char name[30];
	char phone[15];
}person;

//��ǰ ���Ÿ� ���� ����ü�� ����
typedef struct _product {
	char product_name[100];
	char buyer_name[30];
}product;

void print_main();
void view_membership(); //�� ��ȸ
void add_membership();	//ȸ�� ����
void buy_product();		//��ǰ ����
void change_phonenumber();	//��ȭ��ȣ ����
void delete_membership();	//�� Ż��
void find();				//��ȸ - �����˻�

//����ڰ� �Է��ϴ� ������ ���Ͽ� �����ϱ� ���� ���ϸ��� ������ ������(����)
const char *membership = "c:\\Temp\\membership.txt";
const char *product_file = "c:\\Temp\\buy_product.txt";

int main()
{
	char select = 0;	//����ڰ� �����ϴ� ��ȣ�� �����ϱ� ���� select������ ����
	puts("�� ���� ���� �� �Ǹ� ���α׷� \n");
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
		default: printf("\n �߸� �Է��߽��ϴ�. �ٽ� �������ּ���.\n");
		}
	}
	return 0;
}

void print_main()
{
	printf("\nȯ���մϴ� ����*^^*\n");
	printf("���Ͻô� ������ ��ȣ�� �Է����ּ��� \n");

	printf("\n\n1�� : �� ���� ��ȸ\n");
	printf("2�� : ȸ�� ����\n");
	printf("3�� : ��ǰ ����\n");
	printf("4�� : �޴� ��ȭ ��ȣ ����\n");
	printf("5�� : ȸ�� Ż��\n");
	printf("6�� : ���� �̷� �� ������ Ȯ��\n");
	printf("7�� : ������\n\n");
}

//�� ���� ��ȸ �Լ�
void view_membership()
{
	//����ü �迭 ����
	person per[10] = { "","" };	//���� 10������ ����
	int i, cnt = 0;

	FILE *rfp, *wfp;

	rfp = fopen(membership, "r"); //�� ���� ������ �б� ���� ��

	if (rfp == NULL)
	{
		puts("\n **�� ���� ���Ͽ� �� ������ �ϳ��� �����ϴ�.** \n");
		wfp = fopen(membership, "w"); //�� ���� ����
		fclose(wfp);
		return;
	}
	//����� ������ �ϳ��� ������ ������ fread->cnt->feof����.
	//����� ������ �ϳ��� ������ ������ fread->cnt->fraed->cnt->feof����.
	for (i = 0; i < 10; i++)
	{
		fread(&per[i], 1, sizeof(person), rfp);
		if (feof(rfp))
			break;
		cnt++;

	}
	if (cnt == 0)
	{
		printf("\n****����� ������ �ϳ��� �����ϴ�.****\n");
	}

	for (i = 0; i < cnt; i++)
	{
		printf("%s %s\n", per[i].name, per[i].phone);
		//�� ���⼭ %s�ϰ�, per[i]�ϸ� �Ǵ� �� �˾Ҵµ� name�� ���������� �ִµ� per�� ��� �ϳ��ϳ� �����������.
	}

	fclose(rfp);
	printf("\n\n");
}

//ȸ�� ���� �Լ�
//�迭 �� ���� ���� : ȸ�������� 1�� �ؼ�
void add_membership()
{
	//����ü ������ ����
	person per1 = { "","" };

	FILE *wfp;

	memset(&per1, 0, sizeof(person)); //����ü 0���� �ʱ�ȭ

	wfp = fopen(membership, "a"); //������ �߰� ���� ����. ���� ���� ���� ������ ������ ��� ������

	printf("ȸ������ ���͵帮�ڽ��ϴ�.\n\n");
	printf("�̸��� �Է����ּ��� : ");
	gets_s(per1.name);
	printf("��ȭ��ȣ�� �Է����ּ��� : ");
	gets_s(per1.phone);

	fwrite(&per1, 1, sizeof(person), wfp);

	fclose(wfp);
	system("cls");
}

//��ȭ ��ȣ ���� �Լ�
void change_phonenumber()
{
	person per1[10] = { "", "" }; //������ �ִ� 10�� ����ü
	person new_person = { "", "" }; //���� �ٲ� ���ο� ��� ����ü
	int i, ret;
	int cnt = 0;

	FILE *rfp, *wfp;

	memset(&per1, 0, sizeof(person) * 10); //����ü 10�� 0���� �ʱ�ȭ
	memset(&new_person, 0, sizeof(person));

	rfp = fopen(membership, "r"); //������ �б� ���� ����
	if (rfp == NULL) //������ NULL�̸�
	{
		puts("\n�� ���� ������ �����ϴ�. \n"); //���ڿ� ���
		return;
	}

	for (i = 0; i < 10; i++)
	{
		fread(&per1[i], 1, sizeof(person), rfp); //rfp���Ͽ��� �о��

		if (feof(rfp))
			break;
		cnt++; //cnt���� - ex) 7���̸� 7����� cnt ��
	}

	printf("�̸��� �Է����ּ��� : ");
	gets_s(new_person.name);
	printf("��ȭ��ȣ�� �Է����ּ��� : ");
	gets_s(new_person.phone);

	for (i = 0; i < cnt; i++) //������ �� cnt ��ŭ
	{
		ret = strcmp(new_person.name, per1[i].name); //���ο� ����� �̸��� per1�̸��� ���ؼ� ret�� ����
		if (ret == 0)	//��ġ�ϴ°� ������ ���Ͷ�.
		{
			per1[i] = new_person; //new_person�� per1[i]�� ����
			break;
		}
	}

	wfp = fopen(membership, "w"); //������ ���� ���� ��
	for (i = 0; i < cnt; i++) //���� ������ cnt��ŭ for�� �����ϰ�
	{
		fwrite(&per1[i], 1, sizeof(person), wfp); //wfp ���Ͽ� ����
	}
	fclose(wfp);
}

//ȸ�� Ż�� �Լ�
void delete_membership()
{
	person per1[10] = { "","" };
	person delete_person = { "","" };

	//�б� ���� �ʱ�ȭ
	//
	product prod1[10] = { "","" };

	int i = 0, cnt = 0, ret = 0;
	int delete_person_number = -1; // 0��° �Ǽ��� ���� ���Ϸ��� �������.

	FILE *rfp, *wfp;
	FILE *frfp, *fwfp;

	//char file_copy[200] = "";
	//char data[200] = "";

	memset(&per1, 0, sizeof(person) * 10); //����ü 10�� 0���� �ʱ�ȭ
	memset(&delete_person, 0, sizeof(person));

	rfp = fopen(membership, "r");

	if (rfp == NULL)
	{
		puts("\n �� ���� ������ �����ϴ�. \n");
		return;
	}

	printf("**Ż��**\n\n");
	printf("�̸��� �Է����ּ��� : ");
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

	//product_file�� �о�� ���� ����, delete_person_number�� ������ �� ���� �����ϱ�
	for (i = 0; i < 10; i++)
	{
		fread(&prod1[i], 1, sizeof(product), rfp);

		if (feof(rfp))
			break;
		cnt++;
	}
	fclose(frfp);

	fwfp = fopen(product_file, "w");

	//delete_person.name�� ������ continue�ϱ�
	for (i = 0; i < cnt; i++)
	{
		ret = strcmp(delete_person.name, prod1[i].buyer_name);
		if (ret == 0)
			continue;
		fwrite(&prod1[i], 1, sizeof(product), fwfp);
	}
	fclose(fwfp);
}

//��ǰ ���� �Լ�
void buy_product()
{
	FILE *rfp, *wfp;

	product prod = { "", "" };

	wfp = fopen(product_file, "a"); //�� ���� ������ �߰� ���� ����.

	memset(&prod, 0, sizeof(product)); // ����ü �ʱ�ȭ���

	//���� ������ ���ٸ�
	if (wfp == NULL)
	{
		rfp = fopen(product_file, "w"); //�� ������ �����.
		fclose(rfp);
		wfp = fopen(product_file, "a"); //�ٽ� ������ �߰� ���� ����.
	}

	puts("**��ǰ ����**\n");
	puts("�̸��� �Է����ּ��� : ");
	gets_s(prod.buyer_name);

	puts("\n\n1. ��Ų\n2.��ũ��\n3.����ƽ\n\n");
	puts("�����Ͻ� ��ǰ�� �Է����ּ��� : ");
	gets_s(prod.product_name);

	//���Ͽ� ����ü ������ ����
	fwrite(&prod, 1, sizeof(product), wfp);

	fclose(wfp);

	system("cls");
}

//���� �̷� �� ������ Ȯ��(���� �˻�)
void find()
{
	FILE *rfp;

	product prod[100];
	memset(prod, 0, sizeof(product) * 100); // ����ü �迭 ��ü �ʱ�ȭ

	char tmp_prod[30] = "", tmp_name[30] = ""; //��ǰ �˻�, �̸� �˻� �迭 ����
	int i, count = 0;
	int choose;

	rfp = fopen(product_file, "r");

	for (i = 0; ; i++)
	{
		//fwrite(���� ����), fread(���� �б�) 
		fread(&prod[i], 1, sizeof(product), rfp);
		count++;
		if (feof(rfp))
			break;
	}

	puts("\n1�� : �̸� �˻� -> ���� �̷� ����Ʈ\n");
	puts("2�� : ��ǰ �˻� -> ������ ����Ʈ\n");

	printf("��ȣ�� ������ : ");
	choose = _getche();
	printf("\n");

	if (choose == '1')
	{
		printf("�̸� �Է� : ");
		gets_s(tmp_name);	//�̸� �Է�
		printf("");

		for (i = 0; i < count; i++)
		{
			if (strcmp(tmp_name, prod[i].buyer_name) == 0) //�Է��� �̸��̶� product����ü���� ������ �̸��� ��ġ�� ��
			{
				printf("%s\n", prod[i].product_name);	//����ü�� ��ǰ���� ���
			}
		}
	}
	if (choose == '2')
	{
		printf("��ǰ �Է� : ");
		gets_s(tmp_prod);
		printf("");

		for (i = 0; i < count; i++)
		{
			if (strcmp(tmp_prod, prod[i].product_name) == 0) //�Է��� ��ǰ�̶� product����ü���� ��ǰ �̸��� ��ġ�� ��
			{
				printf("%s\n", prod[i].buyer_name);	//����ü�� �����ڰ� ���
			}
		}
	}
	fclose(rfp);
}