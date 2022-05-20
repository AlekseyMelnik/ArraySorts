#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<time.h>

int* WriteHandMass(int* mass, int& _countArray); //���������� ������ ������
void ShowMass(int* mass, int countArray); //���� ������
int* RandMass(int* mass, int& _countArray); //���������� ������ ����������� ��������
int* ReadFileMass(int* mass, int& _countArray); //���������� ������ � �����
int countelem(FILE* fd); //���������� ������� �������� ������
void WriteToFile(int* mass, const char* namefile, int _countArray); //����� ������ � ����

//���������� �������, ���������� �������, ���������� ����������


int sortChoice(int array[], int n);
void countSort(int* masiv, int N); //���������� ����������
int merge(int arr[], // �����, �� ���������
	int beg, // ������� ����� ��������
	int mid, // ���������
	int end);
int sortMerge(int arr[], // �����, �� ���������,
	int beg, // ������� ����� �������� ������ arr ��� ����������
	int end);


int main(void) {

	int* mass = NULL;
	int countArray;
	int choice; //����� ��� ������ 
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	do { //����� ���������� ������ �� ���� ����������
		do { //���� ������� ���������� ������
			printf("-------------------------------------\n�� �� ������ ��������� �����?\n");
			printf("1 - ��������� � ���������\n2 - �� ��������� ������� �������\n3 - ������� � ����� \n4 - ����� � ��������\n");
			if (!scanf("%d", &choice)) {
				printf("����������� ��������! ����� � ��������...");
				return -1;
			};
		} while (choice < 1 || choice > 4);


		switch (choice)
		{
		case 1: { //���������� ������ ������

			mass = WriteHandMass(mass, countArray);
			WriteToFile(mass, "in.txt", countArray);
			ShowMass(mass, countArray);
			break;
		}
		case 2: { //���������� ������ ����������� �������
			mass = RandMass(mass, countArray);
			WriteToFile(mass, "in.txt", countArray);
			ShowMass(mass, countArray);
			break;
		}
		case 3: { //�������� ������ � �����
			mass = ReadFileMass(mass, countArray);
			ShowMass(mass, countArray);
			break;
		}
		case 4: { //����� � ��������
			printf("�� ������ ������!\n");
			return 0;
			break;
		}
		default:
			break;
		}


		do { //���� ������� ����������
			printf("������� ����� ����������:\n1 - �������\n2 -  C��������� �������\n3 - ���������� ����������\n4 - �����\n");
			if (!scanf("%d", &choice)) {
				printf("����������� ��������! ����� � ��������...");
				return -1;
			};
			switch (choice)
			{
			case 1: {
				int time1 = clock();
				//insertionSort(mass, countArray);
				sortMerge(mass, 0, countArray-1);
				int time2 = clock();
				printf("��� ���������� �������: %f\n", (float)(time2 - time1) / 1000);
				ShowMass(mass, countArray);
				WriteToFile(mass, "MergeSort.txt", countArray);
				break;
			}
			case 2: {
				int time1 = clock();
				sortChoice(mass, countArray);
				int time2 = clock();
				printf("���  ���������� �������: %f\n", (float)(time2 - time1) / 1000);
				ShowMass(mass, countArray);
				WriteToFile(mass, "ChoiceSortOut.txt", countArray);
				break;
			}
			case 3: {
				int time1 = clock();
				countSort(mass, countArray);
				int time2 = clock();
				printf("��� ���������� ����������: %f\n", (float)(time2 - time1) / 1000);
				ShowMass(mass, countArray);
				WriteToFile(mass, "methodOfCalculation.txt", countArray);
				break;
			}

			default:
				break;
			}
		} while (choice < 1 || choice>4);


	} while (choice != 4);

	return 0;
}
/*
������� WriteHandMass
������� ���������� ������ � ���������
����:
mass - �����
_countArray - �-�� �������� ������
����:
mass - �����
���������:
�� �������� ����� ���������� ���� ������
*/
int* WriteHandMass(int* mass, int& _countArray)
{
	int countArray;
	do {
		printf("������ ������� �������� ������ :\n");
		if (!scanf("%d", &countArray)) {
			printf("����������� ��������! ����� � ��������...");
			exit(-1);
		}
	} while (countArray < 1);
	mass = (int*)malloc(sizeof(int) * countArray);
	if (!mass) {
		printf("�� ��������� ���*���");
		return nullptr;
	}
	for (int i = 0; i < countArray; i++)
	{
		if (!scanf("%d", &mass[i])) {
			printf("����������� ��������! ����� � ��������...");
			exit(-1);
		}
	}

	_countArray = countArray;
	return mass;
}

/*
������� ShowMass
������� ������ ������
����:
mass - �����
countArray - �-�� �������� ������
����:
mass - �����
���������:
�� ������ ����� �� �����
*/
void ShowMass(int* mass, int countArray)
{

	int choice;

	do {
		printf("1 - ������� ����� �� ����� \n");
		printf("2 - �� ��������  ����� �� ����� \n");
		if (!scanf("%d", &choice)) {
			printf("����������� ��������! ����� � ��������...");
			exit(-1);
		}
	} while (choice < 1 || choice>2);
	if (choice == 1) {
		for (int i = 0; i < countArray; i++)
		{
			printf("%d ", mass[i]);
		}
		printf("\n");
	}
	else {
		return;
	}
}
/*
������� RandMass
������� ���������� ������ ����������� �������
����:
mass - �����
countArray - �-�� �������� ������
����:
mass - �����
���������:
�� ��������� ����� �� ��������� �-��� �������
*/
int* RandMass(int* mass, int& _countArray)
{
	int countArray;
	int max_number;
	int min_number;
	printf("������ ������ ������� �������\n");
	if (!scanf("%d", &max_number)) {
		printf("����������� ��������! ����� � ��������...");
		exit(-1);
	}
	printf("������ ����� ������� �������\n");
	if (!scanf("%d", &min_number)) {
		printf("����������� ��������! ����� � ��������...");
		exit(-1);
	}
	if (max_number < min_number) {
		printf("������ ������� �� ���� ���� ������ �� ����� �������! ����� � ��������...");
		exit(-1);
	}
	srand(time(NULL));
	do {
		printf("������ ������� �������� ������ :\n");
		if (!scanf("%d", &countArray)) {
			printf("����������� ��������! ����� � ��������...");
			exit(-1);
		}
	} while (countArray < 1);
	mass = (int*)malloc(sizeof(int) * countArray);
	if (!mass) {
		printf("�� ������� ���*��...\n");
		return nullptr;
		exit(-1);
	}
	for (int i = 0; i < countArray; i++)
	{
		//mass[i] = (rand() % max_number) + min_number;
		mass[i] = (rand() % (max_number + min_number * (-1) + 1) + min_number);
	}
	_countArray = countArray;
	return mass;

}

/*
������� ReadFileMass
������� ���������� ����� � �����
����:
mass - �����
countArray - �-�� �������� ������
����:
mass - �����
���������:
�� ������� ����� � �����
*/
int* ReadFileMass(int* mass, int& _countArray)
{
	FILE* in = NULL;
	int countArray;
	if ((in = fopen("in.txt", "r")) == NULL) {
		printf("He ������� ������� ���� in.txt! \n");
		exit(-1);
	}
	countArray = countelem(in) - 1;
	mass = (int*)malloc(sizeof(int) * countArray);
	if (!mass) {
		printf("�� ������� ���*��...\n");
		return nullptr;
	}
	for (int i = 0; i < countArray; i++)
	{
		if (!fscanf(in, "%d ", &mass[i])) {
			printf("����������� ��������! ����� � ��������...");
			exit(-1);
		}
	}

	if (fclose(in) == EOF) {
		printf("������� ��� ������� �����!\n");
	}
	_countArray = countArray;
	return mass;
}
/*
������� ShowMass
������� ���������� �-� ��������� ����
����:
fd - ����
����:
elem - �-�� ��������
���������:
�� ���������� ������� �������� � ����
*/
int countelem(FILE* fd) {
	int elem = 0;

	while (!feof(fd)) {
		fscanf(fd, "%*d");
		elem++;
	}
	rewind(fd);

	return elem;
}


/*
������� WriteToFile
������� ������ ������ � ����
����:
mass - �����
countArray - �-�� �������� ������
namefile - ����� �����
���������:
�� �������� ��� ������������� ����� � ����
*/
void WriteToFile(int* mass, const char* namefile, int _countArray)
{
	FILE* out = NULL;
	if ((out = fopen(namefile, "w")) == NULL) {
		printf("He ������� ������� ���� out.txt! \n");
		exit(-1);
	}

	for (int i = 0; i < _countArray; i++)
	{
		fprintf(out, "%d ", mass[i]);
	}
	if (fclose(out) == EOF) {
		printf("������� ��� ������� �����!!\n");
	}
}


/*
������� countSort
������� ���������� ������ �����������
����:
mass - �����
N - �-�� ��������
����:
countSort - ������������ �����
���������:
�� ����������� ����� ��������: ����������
*/
void countSort(int* mass, int N) {
	int* new_mass_plus, * new_mass_minus, //��� �������
		size_plus = 1, size_minus = 1;
	for (int i = 0; i < N; i++) {
		if (mass[i] >= 0 && size_plus < mass[i]) {//����� �� ������ �����
			size_plus = mass[i];
		}
		else if (mass[i] < 0 && size_minus > mass[i]) {//�� ��'���
			size_minus = mass[i];
		}
	}
	size_plus++;
	size_minus = int(fabs(size_minus)) + 1;//������������ ����� ������� ��� �������� �����

	if (!(new_mass_plus = (int*)calloc(size_plus, sizeof(int)))) {
		printf("��� ������ ������ �� ������� ���'��!\n");
		_getch();
		exit(0);
	}
	if (!(new_mass_minus = (int*)calloc(size_minus, sizeof(int)))) {
		printf("��� ������ ������ �� ������� ���'��!\n");
		_getch();
		exit(0);
	}
	//������ � �������
	for (int i = 0; i < N; i++) {
		if (mass[i] >= 0) {
			new_mass_plus[mass[i]]++;
		}
		else {
			new_mass_minus[int(fabs(mass[i]))]++;
		}
	}
	//� ���������� ������ ���� ������������
	int b = 0;
	for (int j = size_minus; j > 0; j--) {
		for (int i = 0; i < new_mass_minus[j]; i++) {
			mass[b] = -j;
			b++;
		}
	}
	for (int j = 0; j < size_plus; j++) {
		for (int i = 0; i < new_mass_plus[j]; i++) {
			mass[b] = j;
			b++;
		}
	}
	free(new_mass_minus);
	free(new_mass_plus);
}


int merge(int arr[], // �����, �� ���������
	int beg, // ������� ����� ��������
	int mid, // ���������
	int end) { // ����� ������� ��������
	int i = beg, // ������� ����� ��������
		j = mid + 1, // ������� ������� ��������
		index = beg,
		k,
		* temp, // ������ ���������� ������
		size; // ����� ���������� ������
		// ��������� ���������� ������
	size = end + 1;
	temp = (int*)malloc(sizeof(int) * size);
	if (!temp) return 1; // ���������� ��� ������� ���'��!
	// ���������� ��������� ����� � ����������� �������
	while ((i <= mid) && (j <= end)) {
		if (arr[i] < arr[j]) {
			temp[index] = arr[i];
			i++;
		}
		else {
			temp[index] = arr[j];
			j++;
		}
		index++;
	}
	if (i > mid) { // ���������� ����������� �������� ������� ��������,
	// ���� ��� ��������
		while (j <= end) {
			temp[index] = arr[j];
			j++;
			index++;
		}
	}
	else { // ���������� ����������� �������� ����� ��������,
	// ���� ��� ��������
		while (i <= mid) {
			temp[index] = arr[i];
			i++;
			index++;
		}
	}
	// ������� ��������� ����� � ���������� ����� arr
	
		for (k = beg; k < index; k++)
			arr[k] = temp[k];
	return 0; // ��������� ���������� � ������� � �������� ����!
}
int sortMerge(int arr[], // �����, �� ���������,
	int beg, // ������� ����� �������� ������ arr ��� ����������
	int end) { // ����� ������� �������� ������ arr)
	int mid; // ������ ���������
	if (beg < end) {
		mid = (beg + end) / 2; // ��������� ���������
		sortMerge(arr, beg, mid); // ������� ���� �� ������ ��������
		sortMerge(arr, mid + 1, end); // ��'������ ���������� ��������
		if (!merge(arr, beg, mid, end))
			return 0; // ���� ��� � �������, ��������� 0
		else
			return 1; // ���� ������� ���'��, ��������� 1
	}
}

int sortChoice(int array[], // ������� �����
	int n) { // ������� �������� ������
	int iter, jter, kter; // "������"-��������� ��� �������� ������
	int temp; // �����, � ��� ��������� ���������� �������� �������� ������ 
	
		/* �������� ����������� ������ ������ */
		if (n < 1)
			return 1;
	/* ��������� ��������� ��������� */
	for (iter = 0; iter < n - 1; iter++) { // ������� ����
		kter = iter; // ������������ kter � ������� iter
		temp = array[iter]; // � �������� �������� ��������
		for (jter = iter + 1; jter < n; jter++) { // �������� ����
			if (array[jter] < temp) { //����������, �� �������� �������� 
				
					kter = jter; // �������� ������ ���������� ��������
				temp = array[kter]; // �������� ���� ��������
			}
		}
		/* �������� �������� ���������� �������� ������ � �������� */
		array[kter] = array[iter];
		array[iter] = temp;
	}
	return 0; // ��������� ���������� �������
}