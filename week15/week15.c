// friend_list_struct.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100


typedef struct {
	char n[30];
	int k;
	int e;
	int m;
	int t,  //����
		r;  //���
	float a; //���
} Student;

Student students[MAX_SIZE];
int std_count = 0;



int FI(int* count) {
	FILE* file;
	if (fopen_s(&file, "name.dat", "rb") != 0) { // "rb": �б� ���� ����
		printf("������ �� �� �����ϴ�.\n");
		return 0;
	}

	// ���Ͽ��� �����͸� �о�ɴϴ�
	*count = fread(students, sizeof(Student), MAX_SIZE, file);
	fclose(file);

	printf("%d���� �����͸� �ε��߽��ϴ�.\n", *count);
	return 1;
}

void STP(Student* students, int* count) {

	Student* new_student = &students[*count];
	printf("\n�л� �̸�: ");
	scanf_s("%29s", new_student->n, sizeof(new_student->n)); // ���� ũ�� ����

	printf("���� ����: ");
	scanf_s("%d", &new_student->k);

	printf("���� ����: ");
	scanf_s("%d", &new_student->e);

	printf("���� ����: ");
	scanf_s("%d", &new_student->m);

	new_student->t = new_student->k + new_student->e + new_student->m;
	new_student->a = new_student->t / 3.0f; // ����� �ε��Ҽ��� ����
	new_student->r = 0;  // ����� ���߿� ���

	(*count)++;
	printf("\n�л� ������ �߰��Ǿ����ϴ�.\n\n");
}

void SFI(Student* students, int count) {
	FILE* file = fopen("name.dat", "wb");
	if (!file) {
		printf("\n���� ���忡 �����߽��ϴ�.\n\n");
		return;
	}

	fwrite(students, sizeof(Student), count, file);
	fclose(file);

	printf("\n%d���� �л� �����͸� �����߽��ϴ�.\n\n", count);
}

void DST(Student* students, int count) {
	if (count == 0) {
		printf("\n��ϵ� �л��� �����ϴ�.\n\n");
		return;
	}

	for (int i = 0; i < count; i++) {
		students[i].r = 1;
		for (int j = 0; j < count; j++) {
			if (students[i].t < students[j].t) {
				students[i].r++;
			}
		}
	}

	printf("\n%-20s %-10s %-10s %-10s %-10s %-10s %-10s\n", "�̸�", "����", "����", "����", "����", "���", "���");
	printf("=================================================================================\n");
	for (int i = 0; i < count; i++) {
		printf("%-20s %-10d %-10d %-10d %-10d %-10.2f %-10d\n",
			students[i].n,
			students[i].k,
			students[i].e,
			students[i].m,
			students[i].t,
			students[i].a,
			students[i].r);
	}
	printf("=================================================================================\n\n");
}

int main(void) {

	int menu_num;

	// ���� ����: ����ڰ� 3�� ������ break ������ �����Ŵ
	while (1) {
		// �޴��� ȭ�鿡 �����
		printf("\t[ Menu ]\t\n");
		printf("1. .dat ���Ͽ��� ������ �б�\n");
		printf("2. �߰� �л� ���� �Է�\n");
		printf("3. .dat ���� ����\n");
		printf("4. ���� Ȯ�� (��� ��� ��)\n");
		printf("5. ����\n");
		printf("===========================\n");
		printf("����(1~5):");
		scanf_s("%d", &menu_num);

		// while������ ������ �ڴ�....
		if (menu_num == 5) break;

		switch (menu_num) {
		case 1:
			FI(&std_count);
			break;
		case 2:
			STP(students,&std_count);
			break;
		case 3:
			SFI(students, std_count);
			break;
		case 4:
			DST(students, std_count);
			break;
		default:
			// ��ȣ�� ��ȿ���� ���� ��쿡 ���� �޽����� �����
			printf("1~5 ��ȣ�� ������ �� �ֽ��ϴ�!!\n\n");
		}
	}

	return 0;
}	