#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>

#define LAN sizeof (struct list)
#define LEN sizeof (struct list2)
#define LIN sizeof (struct queue)

typedef struct queue
{
	int data;
	queue *next;
};

typedef struct date
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

typedef struct data
{
	int type;
	double money;
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

typedef struct list2
{
	data data1;
	list2 *next;
};

typedef struct list
{
	char name[10];
	char number[20];
	int password;
	char ID[20];
	char mobile[20];
	int credit_rating;
	date start_date;
	list2 *next1;
	list *next2;
	int n;
};

list *h;
void deposit(list *h);
void withdrawal(list *h);
void business_handling(list *h);
void balance(list2 *h);
void printmessage(list *h);
int main();
double reserve = 0;
double total = 0;
double money = 0;
int windows[5] = { 0 };
int qn, sn;

int limit()
{
	if (reserve - total < 0)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

list2 *createlist2(list2 *h,data data1)
{
	if (h == NULL)
	{
		h = (list2 *)malloc(LEN);
		h->data1.type = data1.type;
		h->data1.money = data1.money;
		h->data1.year = data1.year;
		h->data1.month = data1.month;
		h->data1.day = data1.day;
		h->data1.hour = data1.hour;
		h->data1.minute = data1.minute;
		h->data1.second = data1.second;
		h->next = NULL;
	}
	return h;
}

void findlist2(list2 *h,data data1,int type)
{
	if (h != NULL&& 
		h->data1.year == data1.year&&h->data1.month == data1.month&&h->data1.day == data1.day&&
		h->data1.hour == data1.hour, h->data1.minute == data1.minute, h->data1.second == data1.second)
	{
		
		findlist2(h, data1, type);
	}
	else if (h == NULL)
	{
		h = createlist2(h, data1);
	}
	else
	{
		findlist2(h->next, data1, type);
	}
}

void printlist2(list2 *h)
{
	double money;
	if (h != NULL)
	{
		if (h->data1.type == 0)
		{
			money = -h->data1.money;
			printf("%lf    %d.%d.%d  %d:%d:%d\n", money, h->data1.year, h->data1.month, h->data1.day, h->data1.hour, h->data1.minute, h->data1.second);
		}
		else
		{
			printf("%lf    %d.%d.%d  %d:%d:%d\n", h->data1.money, h->data1.year, h->data1.month, h->data1.day, h->data1.hour, h->data1.minute, h->data1.second);
		}
		printlist2(h->next);
	}
}

void deletelist2(list2 *h)
{
	if (h->next != NULL)
	{
		free(h->next);
	}
}

list *createlist(list *h, char name[10], char number[20], char mobile[20], int password, char ID[20], int credit_rating, date start_date)
{
	list *q;
	q = (list *)malloc(LAN);
	strcpy(q->name, name);
	strcpy(q->number, number);
	strcpy(q->mobile, mobile);
	q->password = password;
	strcpy(q->ID, ID);
	q->credit_rating = credit_rating;
	q->start_date = start_date;
	q->next1 = NULL;
	q->n = 0;
	q->next2 = h->next2;
	h->next2 = q;
	return h;
}

int nlist(list *h,int n)
{
	if (h != NULL)
	{
		n++;
		n = nlist(h->next2, n);
	}
	return n;
}

void findlist(list *h1, char number[20],data data1, int flag, int password)
{
	if (flag == 1 && h1->next2 != NULL && strcmp(h1->next2->number, number) == 0)
	{
		date x = h1->next2->start_date;
		printf("������%s\n", h1->next2->name);
		printf("���֤�ţ�%s\n", h1->next2->ID);
		printf("���п��ţ�%s\n", h1->next2->number);
		printf("���룺%d\n", h1->next2->password);
		printf("�������ڣ�%d.%d.%d %d:%d:%d\n", x.year, x.month, x.day, x.hour, x.minute, x.second);
	}
	else if (flag == 4 && h1 != NULL && strcmp(h1->number, number) == 0)
	{
		if (h1->password == password)
		{
			printmessage(h1);
		}
		else
		{
			printf("�����������\n");
			business_handling(h);
		}
	}
	else if (flag == 3 && h1 != NULL && strcmp(h1->number, number) == 0)
	{
		money = 0;
		balance(h1->next1);
		printf("�������Ϊ��%lf\n", money);
		if (data1.money > money)
		{
			printf("ȡ��ʧ�ܣ�\n");
			system("pause");
			exit(0);
		}
	}
	else if (flag == 2 && h1 != NULL && strcmp(h1->number, number) == 0)
	{
		if (data1.type == 0 && h1->password == password)
		{
			list2 *h2 = NULL;
			h2 = (list2 *)malloc(LEN);
			h2->data1 = data1;
			h2->next = h1->next1;
			h1->next1 = h2;
			h1->n++;
		}
		if (data1.type == 1)
		{
			list2 *h2 = NULL;
			h2 = (list2 *)malloc(LEN);
			h2->data1 = data1;
			h2->next = h1->next1;
			h1->next1 = h2;
			h1->n++;
		}
		if (data1.type == 0 && h1->password != password)
		{
			printf("�����������\n");
			business_handling(h);
		}
	}
	else if (flag == 0 && h1->next2 != NULL && strcmp(h1->next2->number, number) == 0)
	{
		if (h1->next2->password == password)
		{
			free(h1->next2);
			h1->next2 = NULL;
		}
		else
		{
			printf("�����������\n");
		}
	}
	else
	{
		findlist(h1->next2, number, data1, flag, password);
	}
}

void deletelist(list *h)
{
	if (h->next2 != NULL)
	{
		free(h->next2);
	}
}

int business_window(queue *q)
{
	int i;
	queue *temp;
	int flag = 0;
	for (i = 0; i < 5; i++)
	{
		if (windows[i] == 0)
		{
			temp = q->next;
			q->next = temp->next;
			windows[i] = temp->data;
			printf("�뵽%d�Ŵ��ڰ���ҵ��\n", i);
			flag = 1;
			break;
		}
	}
	FILE *fp1;
	fp1 = fopen("queue.txt", "r+");
	int n = 2;
	for (i = 0; i < 5; i++)
	{
		fseek(fp1, n, SEEK_SET);
		n = n + 2;
		fprintf(fp1, "%d ", windows[i]);
	}
	fclose(fp1);
	return flag;
}

queue *line_up(queue *q)
{
	int y, z;
	queue *p, *r;
	FILE *fp1;
	fp1 = fopen("queue.txt", "r+");
	fscanf(fp1, "%d", &sn);
	int i;
	for (i = 0; i < 5; i++)
	{
		fscanf(fp1, "%d", &windows[i]);
	}
	printf("������1�����������ŶӺ�\n");
	scanf("%d", &y);
	if (y == 1)
	{
		sn++;
	}
	for (p = q; p != NULL; p = p->next)
	{
		if (p->next == NULL)
		{
			r = (queue *)malloc(LIN);
			r->data = sn;
			r->next = p->next;
			p->next = r;
			break;
		}
	}
	fseek(fp1, 0, SEEK_SET);
	fprintf(fp1, "%d", sn);
	printf("�����ŶӺ�Ϊ��%d��\n", sn);
	z = business_window(q);
	fclose(fp1);
	if (z == 1)
	{
		business_handling(h);
	}
	else
	{
		return q;
	}
}

//�û�����������
/*�û�ͨ�����������ֶ���������Ϣ���뵽����֮�У��ɳ����Զ������û������öȺͿ���ʱ���������ݣ�
ͨ��findlist�����ҵ��½����û���Ϣ��������û����û����Լ�鲢ȷ����Ϣ��
�����Ϣ��ȷ���������û�"������ɣ�",�����Ϣ����ȷ��ͨ��findlist����ɾ�����û���Ϣ���������û���������account_opening*/
list *account_opening()
{
	char name[10];
	char number[20];
	char ID[20];
	char mobile[20];
	int credit_rating;
	int password;
	date start_date;
	printf("����������������\n");
	scanf("%s", name);
	printf("�������������֤�ţ�\n");
	scanf("%s", ID);
	printf("�������������п��ţ�\n");
	scanf("%s", number);
	printf("�����������ֻ��ţ�\n");
	scanf("%s", mobile);
	printf("��������λ�������룺\n");
	scanf("%d", &password);
	//�û����������Ϣ
	credit_rating = 10;
	time_t now;
	struct tm *tm_now;
	time(&now);
	tm_now = localtime(&now);
	start_date.year = tm_now->tm_year + 1900;
	start_date.month = tm_now->tm_mon + 1;
	start_date.day = tm_now->tm_mday;
	start_date.hour = tm_now->tm_hour;
	start_date.minute = tm_now->tm_min;
	start_date.second = tm_now->tm_sec;
	//ϵͳ�����û����öȺͿ���ʱ��
	h = createlist(h, name, number, mobile, password, ID, credit_rating, start_date);
	//���ڽӱ��ﴴ���û����˽ڵ�
	data data1;
	data1.type = 0; data1.money = 0; 
	data1.year = 0; data1.month = 0; data1.day = 0; 
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	printf("��˶�������Ϣ��\n");
	findlist(h, number, data1, 1, password);
	//�����û��ĸ�����Ϣ�����û�ȷ��������Ϣ
	printf("���û�г����밴1\n");
	printf("����д����밴2\n");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		printf("������ɣ�\n");
		return h;
	}
	else
	{
		findlist(h, number, data1, 2, password);//�ҵ��������ĸ�����Ϣ��ɾ��
		h = account_opening();//�����û���������
	}
}

void balance(list2 *h)
{
	if (h != NULL)
	{
		if (h->data1.type == 1)
		{
			money = money + h->data1.money;
		}
		if (h->data1.type == 0)
		{
			money = money - h->data1.money;
		}
		balance(h->next);
	}
}

void print(list *h)
{
	char number[20];
	int password;
	printf("�������˺ţ�");
	scanf("%s", number);
	printf("��������λ�������룺");
	scanf("%d", &password);
	data data1;
	data1.type = 0; data1.money = 0;
	data1.year = 0; data1.month = 0; data1.day = 0;
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	findlist(h, number, data1, 4, password);
}

void printmessage(list *h)
{
	printf("������%s\n���п��ţ�%s\n���֤�ţ�%s\n", h->name, h->number, h->ID);
	printf("��֧�嵥��\n");
	printlist2(h->next1);
}

//�û�������
/*�û�ͨ�����������ֶ��������Ϣ(���п��˺š�����)�ʹ�������뵽ϵͳ�У�
ϵͳ������������˻��źʹ��������û����ȷ��������������ع��ܺ������棬
ϵͳ���ɴ����Ϣ(����ࡢ�����ʱ��)��ͨ��findlist���������½����뵽�û���ȡ��������,���ع��ܺ���*/
void deposit(list *h)
{
	double money;
	char number[20];
	int x = 0;
	printf("��ѡ����Ǵ��ҵ��\n");
	printf("���������п��ţ�");
	scanf("%s", number);
	printf("���������");
	scanf("%lf", &money);
	//�û���������Ϣ
	printf("��ȷ�ϴ���\n");
	printf("�˺ţ�%s\n��%lf\n", number, money);
	//ϵͳ���������Ϣ
	printf("�����������ȷ����\n");
	printf("1.ȷ��    2.ȡ��\n");
	scanf("%d", &x);
	if (x == 1)
	{
		data data1;
		data1.type = 1;
		data1.money = money;
		time_t now;
		struct tm *tm_now;
		time(&now);
		tm_now = localtime(&now);
		data1.year = tm_now->tm_year + 1900;
		data1.month = tm_now->tm_mon + 1;
		data1.day = tm_now->tm_mday;
		data1.hour = tm_now->tm_hour;
		data1.minute = tm_now->tm_min;
		data1.second = tm_now->tm_sec;
		findlist(h, number, data1, 2, 0);
		printf("���ɹ���\n");
		//ϵͳ���ɲ���������Ϣ
		business_handling(h);
	}
	else
	{
		business_handling(h);
		//����������ع��ܺ�������
	}
}

//�û�ȡ���
/*�û�ͨ��������������ȡ����Ϣ(���п��š�����)��ͨ��findlist������ѯ�˻���
����֤���룬�����������򷵻ع��ܺ������棬
�û�����ȡ���ͨ��findlist������֤ȡ�����Ƿ�С���������������ʾȡ��ʧ�ܲ��رճ���
��֤ȡ��������ȡ�����ݣ�����û�ͬ��ȡ��������ȡ����Ϣ�½��ڵ㲢���뵽�û��Ĵ�ȡ����Ϣ�����У�
���򷵻ع��ܺ�������*/
void withdrawal(list *h)
{
	double money;
	char number[20];
	int password;
	printf("��ѡ�����ȡ��ҵ��\n");
	printf("���������п��ţ�");
	scanf("%s", number);
	printf("���������룺");
	scanf("%d", &password);
	//�û�����ȡ����Ϣ
	data data1;
	data1.type = 0; data1.money = 0;
	data1.year = 0; data1.month = 0; data1.day = 0;
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	findlist(h, number, data1, 3, password);
	//��ѯ�˻�����֤����
	printf("������ȡ���\n");
	scanf("%lf", &money);//�û�����ȡ����
	printf("��ȷ��ȡ��\n");
	printf("�˺ţ�%s\n��%lf\n", number, money);
	data1.money = money;
	findlist(h, number, data1, 3, password);
	//��֤ȡ����
	printf("�����������ȷ��ȡ�\n");
	printf("1.ȷ��    2.ȡ��\n");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		data1.type = 0;
		data1.money = money;
		time_t now;
		struct tm *tm_now;
		time(&now);
		tm_now = localtime(&now);
		data1.year = tm_now->tm_year + 1900;
		data1.month = tm_now->tm_mon + 1;
		data1.day = tm_now->tm_mday;
		data1.hour = tm_now->tm_hour;
		data1.minute = tm_now->tm_min;
		data1.second = tm_now->tm_sec;
		findlist(h, number, data1, 2, password);
		printf("ȡ��ɹ���\n");
		business_handling(h);
		//ȡ����Ϣ�����û���ȡ����Ϣ�������ع��ܺ�������
	}
	else
	{
		business_handling(h);
		//�û����ع��ܺ�������
	}
}

//�û�ע���˻����ܺ���
/*�û�ͨ���������������˻���Ϣ(���п��š�����)��ͨ��findlist������֤����Ͳ�ѯ�˻���
��������򷵻ع��ܺ������棬�û�ȷ����Ϣ��ͨ��findlist����ɾ���˻���Ϣ�����ع��ܺ������棬����ֱ�ӷ��ع��ܺ�������*/
void logout_account(list *h)
{
	char number[20];
	int password;
	printf("���������п��ţ�");
	scanf("%s", number);
	printf("��������λ�������룺");
	scanf("%d", &password);
	//�û������˻���Ϣ
	data data1;
	data1.type = 0; data1.money = 0;
	data1.year = 0; data1.month = 0; data1.day = 0;
	data1.hour = 0; data1.minute = 0; data1.second = 0;
	findlist(h, number, data1, 3, password);
	//��֤���룬��ѯ���
	printf("�����������ȷ��ע���˻�%s��\n", number);
	printf("1.ȷ��    2.ȡ��\n");
	int x = 0;
	scanf("%d", &x);
	if (x == 1)
	{
		findlist(h, number, data1, 0, password);
		printf("ע���ɹ���");
		business_handling(h);
		//ɾ���û���Ϣ�����ع��ܺ�������
	}
	if (x == 2)
	{
		business_handling(h);
		//���ع��ܺ�������
	}
}

void business_handling(list *h)
{
	printf("�����������ŶӺ�\n");
	scanf("%d", &qn);
	system("CLS");
	printf("1.����\n");
	printf("2.���\n");
	printf("3.ȡ��\n");
	printf("4.ע���˻�\n");
	printf("5.��ӡ�嵥\n");
	printf("6.������һ��\n");
	printf("��ѡ��ҵ����ţ�");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		h = account_opening();
	}
	else if (x == 2)
	{
		deposit(h);
	}
	else if (x == 3)
	{
		withdrawal(h);
	}
	else if (x == 4)
	{
		logout_account(h);
	}
	else if(x == 5)
	{
		print(h);
	}
	else
	{
		main();
	}
}

//�ļ���ȡ������
/*��data.txt�ļ����Ѿ����ո�ʽ�źõ�����ͨ��fscanf��ȡ������
�ȶ�ȡ�����ڴ�����reserve��֮���ȡ�û�����n��ͨ��forѭ���ֱ��ȡ�û��ĸ�����Ϣ�ʹ�ȡ����Ϣ��
�߶�ȡ��ȡ����Ϣ�߼���ȫ���û���֧�ܶ�����ڼ����жϴ������Ƿ������û�ȡ�*/
int read()
{
	FILE *fp;
	int n, m, i, j;
	list *q = NULL;
	fp = fopen("data.txt", "r");
	fscanf(fp, "%lf", &reserve);//��ȡ���д�����
	fscanf(fp, "%d", &n);//��ȡ�û�����
	h = (list *)malloc(LAN);
	h->next2 = NULL;
	for (i = 0; i < n; i++)
	{
		q = (list *)malloc(LAN);
		fscanf(fp, "%s %d %s %s %d %s %d %d %d %d %d %d %d", q->number, &q->password, q->mobile, q->name, &q->credit_rating, q->ID
			, &q->start_date.year, &q->start_date.month, &q->start_date.day, &q->start_date.hour, &q->start_date.minute, &q->start_date.second, &q->n);
		//��ȡ�û�������Ϣ
		q->next1 = NULL;
		m = q->n;
		list2 *q2 = NULL;
		for (j = 0; j < m; j++)
		{
			q2 = (list2 *)malloc(LEN);
			fscanf(fp, "%d %lf %d %d %d %d %d %d", &q2->data1.type, &q2->data1.money
				, &q2->data1.year, &q2->data1.month, &q2->data1.day
				, &q2->data1.hour, &q2->data1.minute, &q2->data1.second);
			//��ȡ�û���ȡ����Ϣ
			if (q2->data1.type == 1)
			{
				total = total + q2->data1.money;
			}
			if (q2->data1.type == 0)
			{
				total = total - q2->data1.money;
			}//����ȫ���û�����֧�ܶ�
			q2->next = q->next1;
			q->next1 = q2;
		}
		q->next2 = h->next2;
		h->next2 = q;
	}
	return n;//�����û�����
}

//�ļ�д�뺯����
/*���ڽӱ��е����ݰ��ո�ʽ��fprintfд���ļ�data.txt�У�
�ȱ���ÿ���û��Ĵ�ȡ����Ϣ����͸�ֵ��total�У���������reserve��total����Ը��´�����
֮��ͨ��forѭ�����û�������Ϣ�����Ӧ�Ĵ�ȡ����Ϣд���ļ�data.txt֮�С�*/
void write(list *h,int n)
{
	FILE *fp;
	int m, i, j;
	list *q = h;
	fp = fopen("data.txt", "w");
	total = 0;
	for (i = 0; i < n; i++)
	{
		m = q->n;
		list2 *q1 = q->next1;
		for (j = 0; j < m; j++)
		{
			if (q1->data1.type == 1)
			{
				total = total + q1->data1.money;
			}
			if (q1->data1.type == 0)
			{
				total = total - q1->data1.money;
			}
			q1 = q1->next;
		}
		q = q->next2;
	}//�����û��Ĵ�ȡ����Ϣ����͸�ֵ��total
	reserve = reserve + total;//���㴢����reserve
	fprintf(fp, "%lf ", reserve);
	fprintf(fp, "%d ", n);
	q = h;
	for (i = 0; i < n; i++)
	{
		fprintf(fp, "%s %d %s %s %d %s %d %d %d %d %d %d %d ", q->number, q->password, q->mobile, q->name, q->credit_rating, q->ID
			, q->start_date.year, q->start_date.month, q->start_date.day, q->start_date.hour, q->start_date.minute, q->start_date.second, q->n);
		//���û�������Ϣд��
		m = q->n;
		list2 *q2 = q->next1;
		for (j = 0; j < m; j++)
		{
			fprintf(fp, "%d %lf %d %d %d %d %d %d ", q2->data1.type, q2->data1.money
				, q2->data1.year, q2->data1.month, q2->data1.day
				, q2->data1.hour, q2->data1.minute, q2->data1.second);
			//���û���ȡ����Ϣд��
			q2 = q2->next;
		}
		q = q->next2;
	}
	fclose(fp);
	printf("��ȷ��ҵ��������\n");
	printf("1.ȷ��    2.ȡ��\n");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		FILE *fp1;
		int n = 0;
		fp1 = fopen("queue.txt", "r+");
		fseek(fp1, n, SEEK_SET);
		fprintf(fp1, "%d ", sn);
		for (i = 0; i < 5; i++)
		{;
			if (windows[i] == qn)
			{
				windows[i] = 0;
				n = n + 2;
				fseek(fp1, n, SEEK_SET);
				fprintf(fp1, "%d ", windows[i]);
			}
			else
			{
				n = n + 2;
				fseek(fp1, n, SEEK_SET);
				fprintf(fp1, "%d ", windows[i]);
			}
		}
		fclose(fp1);
	}
	else
	{
		system("CLS");
		main();
	}
}

int main()
{
	int n;
	queue *q = NULL;
	q = (queue *)malloc(LIN);
	q->next = NULL;
	n = read();
	int y = 0;
	y = limit();
	if (y == 1)
	{
		printf("��ʱ�޷�����ҵ��\n");
		system("pause");
		return 0;
	}
	reserve = reserve - total;
	printf("����ҵ��ϵͳ\n");
	printf("1.�Ŷ�ȡ��\n");
	printf("2.����ҵ��\n");
	printf("3.�˳�ϵͳ\n");
	printf("��ѡ����ţ�");
	int x;
	scanf("%d", &x);
	if (x == 1)
	{
		q = line_up(q);
		system("pause");
		return 0;
	}
	if (x == 2)
	{
		business_handling(h);
	}
	if (x == 3)
	{
		n = 0;
		n = nlist(h, n) - 1;
		write(h->next2, n);
		system("pause");
		return 0;
	}
	n = 0;
	n = nlist(h, n) - 1;
	write(h->next2, n);
	system("pause");
	return 0;
}