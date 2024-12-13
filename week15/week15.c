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
	int t,  //총점
		r;  //등수
	float a; //평균
} Student;

Student students[MAX_SIZE];
int std_count = 0;



int FI(int* count) {
	FILE* file;
	if (fopen_s(&file, "name.dat", "rb") != 0) { // "rb": 읽기 모드로 열기
		printf("파일을 열 수 없습니다.\n");
		return 0;
	}

	// 파일에서 데이터를 읽어옵니다
	*count = fread(students, sizeof(Student), MAX_SIZE, file);
	fclose(file);

	printf("%d명의 데이터를 로드했습니다.\n", *count);
	return 1;
}

void STP(Student* students, int* count) {

	Student* new_student = &students[*count];
	printf("\n학생 이름: ");
	scanf_s("%29s", new_student->n, sizeof(new_student->n)); // 버퍼 크기 지정

	printf("국어 점수: ");
	scanf_s("%d", &new_student->k);

	printf("영어 점수: ");
	scanf_s("%d", &new_student->e);

	printf("수학 점수: ");
	scanf_s("%d", &new_student->m);

	new_student->t = new_student->k + new_student->e + new_student->m;
	new_student->a = new_student->t / 3.0f; // 평균은 부동소수점 연산
	new_student->r = 0;  // 등수는 나중에 계산

	(*count)++;
	printf("\n학생 정보가 추가되었습니다.\n\n");
}

void SFI(Student* students, int count) {
	FILE* file = fopen("name.dat", "wb");
	if (!file) {
		printf("\n파일 저장에 실패했습니다.\n\n");
		return;
	}

	fwrite(students, sizeof(Student), count, file);
	fclose(file);

	printf("\n%d명의 학생 데이터를 저장했습니다.\n\n", count);
}

void DST(Student* students, int count) {
	if (count == 0) {
		printf("\n등록된 학생이 없습니다.\n\n");
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

	printf("\n%-20s %-10s %-10s %-10s %-10s %-10s %-10s\n", "이름", "국어", "영어", "수학", "총점", "평균", "등수");
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

	// 무한 루프: 사용자가 3을 누르면 break 문으로 종료시킴
	while (1) {
		// 메뉴를 화면에 출력함
		printf("\t[ Menu ]\t\n");
		printf("1. .dat 파일에서 데이터 읽기\n");
		printf("2. 추가 학생 정보 입력\n");
		printf("3. .dat 파일 저장\n");
		printf("4. 성적 확인 (평균 계산 등)\n");
		printf("5. 종료\n");
		printf("===========================\n");
		printf("선택(1~5):");
		scanf_s("%d", &menu_num);

		// while문에서 나가야 겠다....
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
			// 번호가 유효하지 않은 경우에 오류 메시지를 출력함
			printf("1~5 번호만 선택할 수 있습니다!!\n\n");
		}
	}

	return 0;
}	