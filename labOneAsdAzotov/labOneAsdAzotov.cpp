#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#include<windows.h>
#include<time.h>

int* WriteHandMass(int* mass, int& _countArray); //Заповнення масиву вручну
void ShowMass(int* mass, int countArray); //Вивід масиву
int* RandMass(int* mass, int& _countArray); //Заповнення масиву випадковими масивами
int* ReadFileMass(int* mass, int& _countArray); //Зчитування масиву з файлу
int countelem(FILE* fd); //Розрахунок кількості елементів масиву
void WriteToFile(int* mass, const char* namefile, int _countArray); //Запис масиву у файл

//Сортування вибором, сортування злиттям, сортування підрахунком


int sortChoice(int array[], int n);
void countSort(int* masiv, int N); //Сортування підрахунком
int merge(int arr[], // масив, що сортується
	int beg, // початок лівого підмасиву
	int mid, // серединка
	int end);
int sortMerge(int arr[], // масив, що сортується,
	int beg, // початок лівого підмасиву масиву arr для сортування
	int end);


int main(void) {

	int* mass = NULL;
	int countArray;
	int choice; //Змінна для вибору 
	system("cls");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	do { //Спосіб заповнення масиву та його сортування
		do { //Вибір способу заповнення масиву
			printf("-------------------------------------\nЯк ви хочете заповнити масив?\n");
			printf("1 - заповнити з клавіатури\n2 - за допомогою функції рандому\n3 - зчитати з файлу \n4 - вихід з програми\n");
			if (!scanf("%d", &choice)) {
				printf("Некорректне значення! Вихід з програми...");
				return -1;
			};
		} while (choice < 1 || choice > 4);


		switch (choice)
		{
		case 1: { //Заповнення масиву вручну

			mass = WriteHandMass(mass, countArray);
			WriteToFile(mass, "in.txt", countArray);
			ShowMass(mass, countArray);
			break;
		}
		case 2: { //Заповнення масиву випадковими числами
			mass = RandMass(mass, countArray);
			WriteToFile(mass, "in.txt", countArray);
			ShowMass(mass, countArray);
			break;
		}
		case 3: { //Зчитання масиву з файлу
			mass = ReadFileMass(mass, countArray);
			ShowMass(mass, countArray);
			break;
		}
		case 4: { //Вихід з програми
			printf("Ви успішно вийшли!\n");
			return 0;
			break;
		}
		default:
			break;
		}


		do { //Вибір способу сортування
			printf("Виберіть спосіб сортування:\n1 - Злиттям\n2 -  Cортування вибором\n3 - Сортування підрахунком\n4 - Вийти\n");
			if (!scanf("%d", &choice)) {
				printf("Некорректне значення! Вихід з програми...");
				return -1;
			};
			switch (choice)
			{
			case 1: {
				int time1 = clock();
				//insertionSort(mass, countArray);
				sortMerge(mass, 0, countArray-1);
				int time2 = clock();
				printf("Час сортування злиттям: %f\n", (float)(time2 - time1) / 1000);
				ShowMass(mass, countArray);
				WriteToFile(mass, "MergeSort.txt", countArray);
				break;
			}
			case 2: {
				int time1 = clock();
				sortChoice(mass, countArray);
				int time2 = clock();
				printf("Час  сортування вибором: %f\n", (float)(time2 - time1) / 1000);
				ShowMass(mass, countArray);
				WriteToFile(mass, "ChoiceSortOut.txt", countArray);
				break;
			}
			case 3: {
				int time1 = clock();
				countSort(mass, countArray);
				int time2 = clock();
				printf("Час сортування підрахунком: %f\n", (float)(time2 - time1) / 1000);
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
Функція WriteHandMass
функція заповнення масиву з клавіатури
Вхід:
mass - масив
_countArray - к-ть елементів масиву
Вивід:
mass - масив
Результат:
ми створили масив заповнивши його вручну
*/
int* WriteHandMass(int* mass, int& _countArray)
{
	int countArray;
	do {
		printf("Введіть кількість елементів масиву :\n");
		if (!scanf("%d", &countArray)) {
			printf("Некорректне значення! Вихід з програми...");
			exit(-1);
		}
	} while (countArray < 1);
	mass = (int*)malloc(sizeof(int) * countArray);
	if (!mass) {
		printf("Не виділилась пам*ять");
		return nullptr;
	}
	for (int i = 0; i < countArray; i++)
	{
		if (!scanf("%d", &mass[i])) {
			printf("Некорректне значення! Вихід з програми...");
			exit(-1);
		}
	}

	_countArray = countArray;
	return mass;
}

/*
Функція ShowMass
функція виводу масиву
Вхід:
mass - масив
countArray - к-ть елементів масиву
Вивід:
mass - масив
Результат:
ми вивели масив на екран
*/
void ShowMass(int* mass, int countArray)
{

	int choice;

	do {
		printf("1 - Вивести масив на екран \n");
		printf("2 - Не виводити  масив на екран \n");
		if (!scanf("%d", &choice)) {
			printf("Некорректне значення! Вихід з програми...");
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
Функція RandMass
функція заповнення масиву випадковими числами
Вхід:
mass - масив
countArray - к-ть елементів масиву
Вивід:
mass - масив
Результат:
ми заповнили масив за допомогою ф-ції рандому
*/
int* RandMass(int* mass, int& _countArray)
{
	int countArray;
	int max_number;
	int min_number;
	printf("Введіть верхню границю рандому\n");
	if (!scanf("%d", &max_number)) {
		printf("Некорректне значення! Вихід з програми...");
		exit(-1);
	}
	printf("Введіть нижню границю рандому\n");
	if (!scanf("%d", &min_number)) {
		printf("Некорректне значення! Вихід з програми...");
		exit(-1);
	}
	if (max_number < min_number) {
		printf("Верхня границя не може бути меншою за нижню границю! Вихід з програми...");
		exit(-1);
	}
	srand(time(NULL));
	do {
		printf("Введіть кількість елементів масиву :\n");
		if (!scanf("%d", &countArray)) {
			printf("Некорректне значення! Вихід з програми...");
			exit(-1);
		}
	} while (countArray < 1);
	mass = (int*)malloc(sizeof(int) * countArray);
	if (!mass) {
		printf("не вистачає пам*яті...\n");
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
Функція ReadFileMass
функція зчитування масву з файлу
Вхід:
mass - масив
countArray - к-ть елементів масиву
Вивід:
mass - масив
Результат:
ми зчитали масив з файлу
*/
int* ReadFileMass(int* mass, int& _countArray)
{
	FILE* in = NULL;
	int countArray;
	if ((in = fopen("in.txt", "r")) == NULL) {
		printf("He вдалося відкрити файл in.txt! \n");
		exit(-1);
	}
	countArray = countelem(in) - 1;
	mass = (int*)malloc(sizeof(int) * countArray);
	if (!mass) {
		printf("не вистачає пам*яті...\n");
		return nullptr;
	}
	for (int i = 0; i < countArray; i++)
	{
		if (!fscanf(in, "%d ", &mass[i])) {
			printf("Некорректне значення! Вихід з програми...");
			exit(-1);
		}
	}

	if (fclose(in) == EOF) {
		printf("Помилка при закритті файлу!\n");
	}
	_countArray = countArray;
	return mass;
}
/*
Функція ShowMass
функція обчислення к-ті елементіву файлі
Вхід:
fd - файл
Вивід:
elem - к-ть елементів
Результат:
ми порахували кількість елементів у файлі
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
Функція WriteToFile
функція запису масиву у файл
Вхід:
mass - масив
countArray - к-ть елементів масиву
namefile - назва файлу
Результат:
ми записали наш новостворений масив у файл
*/
void WriteToFile(int* mass, const char* namefile, int _countArray)
{
	FILE* out = NULL;
	if ((out = fopen(namefile, "w")) == NULL) {
		printf("He вдалося відкрити файл out.txt! \n");
		exit(-1);
	}

	for (int i = 0; i < _countArray; i++)
	{
		fprintf(out, "%d ", mass[i]);
	}
	if (fclose(out) == EOF) {
		printf("Помилка при закритті вайлу!!\n");
	}
}


/*
Функція countSort
функція сортування масиву підстановкою
Вхід:
mass - масив
N - к-ть елементів
Вивід:
countSort - відсортований масив
Результат:
ми відсортували масив способом: підстановка
*/
void countSort(int* mass, int N) {
	int* new_mass_plus, * new_mass_minus, //нові массиви
		size_plus = 1, size_minus = 1;
	for (int i = 0; i < N; i++) {
		if (mass[i] >= 0 && size_plus < mass[i]) {//аналіз на додатні числа
			size_plus = mass[i];
		}
		else if (mass[i] < 0 && size_minus > mass[i]) {//та від'емні
			size_minus = mass[i];
		}
	}
	size_plus++;
	size_minus = int(fabs(size_minus)) + 1;//перевертаемо розмір массива для мінусових чисел

	if (!(new_mass_plus = (int*)calloc(size_plus, sizeof(int)))) {
		printf("Для такого масиву не вистачає пам'яті!\n");
		_getch();
		exit(0);
	}
	if (!(new_mass_minus = (int*)calloc(size_minus, sizeof(int)))) {
		printf("Для такого масиву не вистачає пам'яті!\n");
		_getch();
		exit(0);
	}
	//рахуємо в массиви
	for (int i = 0; i < N; i++) {
		if (mass[i] >= 0) {
			new_mass_plus[mass[i]]++;
		}
		else {
			new_mass_minus[int(fabs(mass[i]))]++;
		}
	}
	//з отриманних робимо один відсортований
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


int merge(int arr[], // масив, що сортується
	int beg, // початок лівого підмасиву
	int mid, // серединка
	int end) { // кінець правого підмасиву
	int i = beg, // початок лівого підмасиву
		j = mid + 1, // початок правого підмасиву
		index = beg,
		k,
		* temp, // адреса допоміжного масиву
		size; // розмір допоміжного масиву
		// створення допоміжного масиву
	size = end + 1;
	temp = (int*)malloc(sizeof(int) * size);
	if (!temp) return 1; // повернення при нестачі пам'яті!
	// заповнюємо допоміжний масив в правильному порядку
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
	if (i > mid) { // переписуємо нескопійовані елементи правого підмасиву,
	// якщо такі лишилися
		while (j <= end) {
			temp[index] = arr[j];
			j++;
			index++;
		}
	}
	else { // переписуємо нескопійовані елементи лівого підмасиву,
	// якщо такі лишилися
		while (i <= mid) {
			temp[index] = arr[i];
			i++;
			index++;
		}
	}
	// копіюємо допоміжний масив в початковий масив arr
	
		for (k = beg; k < index; k++)
			arr[k] = temp[k];
	return 0; // нормальне повернення з функціі – підмасиви злиті!
}
int sortMerge(int arr[], // масив, що сортується,
	int beg, // початок лівого підмасиву масиву arr для сортування
	int end) { // кінець правого підмасиву масива arr)
	int mid; // індекс серединки
	if (beg < end) {
		mid = (beg + end) / 2; // визначаємо серединку
		sortMerge(arr, beg, mid); // сортуємо лівий та правий підмасиви
		sortMerge(arr, mid + 1, end); // об'єднуємо відсортовані підмасиви
		if (!merge(arr, beg, mid, end))
			return 0; // якщо все в порядку, повертаємо 0
		else
			return 1; // якщо нестача пам'яті, повертаємо 1
	}
}

int sortChoice(int array[], // вхідний масив
	int n) { // кількість елементів масиву
	int iter, jter, kter; // "бігунки"-ітератори для перебору масиву
	int temp; // змінна, в якій тимчасово зберігається значення елементу масива 
	
		/* Перевірка корректності розміру масиву */
		if (n < 1)
			return 1;
	/* Реалізація основного алгоритму */
	for (iter = 0; iter < n - 1; iter++) { // зовнішній цикл
		kter = iter; // ініціалізовуємо kter в позицію iter
		temp = array[iter]; // і зберігаємо значення елементу
		for (jter = iter + 1; jter < n; jter++) { // внутрішній цикл
			if (array[jter] < temp) { //перевіряємо, чи значення елементу 
				
					kter = jter; // зберігаємо індекс найменшого елементу
				temp = array[kter]; // зберігаємо його значення
			}
		}
		/* обмінюємо значення найменшого елементу масиву з поточним */
		array[kter] = array[iter];
		array[iter] = temp;
	}
	return 0; // нормальне завершення функції
}