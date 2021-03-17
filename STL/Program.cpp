#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>

using namespace std;


// Korzystaj�c z biblioteki STL nale�y rozwi�za� znajduj�ce si� w funkcji main 5 zada� (ka�de po 1 pkt). Etapy 2-5 mo�na rozwi�za� w dowolnej kolejno�ci, 
// natomiast etap 1 nale�y rozwi�za� najpierw. Nale�y korzysta� z algorytm�w i funktor�w z biblioteki STL oraz wyra�e� lambda. 
// Zakazane jest korzystanie z p�tli!!! Wszystkie operacje modyfikuj�ce zbi�r wej�ciowy powinny by� wykonywane na jego kopii (Etapy 2-5)!!!

// Funkcja wypisuje na konsoli wszystkie elementy wektora za pomoc� for_each
void PrintVector(vector<int> input)
{
	//TODO
	for_each(input.begin(), input.end(), [](int element) {cout << element << " "; });
	cout << endl;
};

// Funkcja zwraca najwi�kszy element zbioru oraz zmodyfikowany zbi�r w nast�puj�cy spos�b:
//   - elementy znajduj�ce si� przed elementem maksymalnym zostaj� pomno�one przez wylosowan� liczb� k
//     (taka sama warto�� dla wszystkich element�w z przedzia�u [-10;10))
//   - pozosta�e elementy nie s� modyfikowane
//   - w przypadku gdy istnieje kilka element�w o warto�ci maksymalnej modyfikowane s� jedynie
//     elementy przed pierwszym wyst�pieniem elementu maksymalnego
std::tuple<int, std::vector<int>> GetTask2Output(std::vector<int> input)
{
	std::vector<int> output_vector(input);
	int max_value = 0;

	//TODO
	int k = rand() % 20 - 10;
	bool condition = true;
	for_each(output_vector.begin(), output_vector.end(), [&max_value](int element)
		{
			if (max_value < element) { max_value = element; }
		});

	for_each(output_vector.begin(), output_vector.end(), [max_value, k, &condition](int &element)
		{
			if (max_value == element) { condition = false; }
			if (condition == true) { element *= k; }
		});

	return { max_value, output_vector };
};

// Funkcja zwraca warto�� mediany dla podanego zbioru oraz sum� element�w wi�kszych modu�owo od mediany (|x| > |median|)
// Uwaga: mo�na wykorzysta� sortowanie
std::tuple<double, int> GetTask3Output(std::vector<int> input)
{
	double median = 0.0;
	int sum = 0;

	//TODO
	std::vector<int> output_vector(input);
	int size = output_vector.size();
	sort(output_vector.begin(), output_vector.end());

	if (size % 2 == 0) { median = ((double)output_vector[size / 2] + (double)output_vector[(size / 2) - 1]) / 2.0; }
	else { median = output_vector[(size / 2)]; }

	for_each(output_vector.begin(), output_vector.end(), [&sum, median](int element) 
		{
			if (abs(element) > median) { sum += element; }
		});

	return { median, sum };
}

int main()
{
	srand(0xFULL);
	
	cout << "Etap 1." << endl;
	//1. (1 pkt) Zaimplementowa� funkcje PrintVector, kt�ra wypisuje elementy wektora
	// oraz uzupe�ni� nast�puj�ce wektory losowymi liczbami z przedzia�u:
	// *v1 - [-10;10);
	// *v2 - [0;10);
	// *v3 - [-5;10);
	// *v4 - [-10;10);

	vector<int> v1(10);
	vector<int> v2(12);
	vector<int> v3(15);
	vector<int> v4(24);

	//TODO
	generate(v1.begin(), v1.end(), []() {return rand() % 20 - 10; });
	generate(v2.begin(), v2.end(), []() {return rand() % 10; });
	generate(v3.begin(), v3.end(), []() {return rand() % 15 - 5; });
	generate(v4.begin(), v4.end(), []() {return rand() % 20 - 10; });

	PrintVector(v1);
	PrintVector(v2);
	PrintVector(v3);
	PrintVector(v4);

	cout << "Etap 2." << endl;
	//2. (1 pkt) Po��czy� wektory v1 i v2 w wektor v5 (czyli v5 zawiera najpierw elementy v1, a potem V2),
	// a nast�pnie zaimplementowa� funkcj� GetTask2Output
	vector<int> v5;
	int max_value;
	vector<int> output_task2;

	//TODO
	copy(v1.begin(), v1.end(), back_inserter(v5));
	copy(v2.begin(), v2.end(), back_inserter(v5));

	tie(max_value, output_task2) = GetTask2Output(v5);

	cout << "Wartosc maksymalna: " << max_value << endl;
	PrintVector(output_task2);

	cout << "Etap 3." << endl;
	//3. (1 pkt) Zaimplementowa� funkcj� GetTask3Output
	double median;
	int sum;

	tie(median, sum) = GetTask3Output(v3);
	cout << "Wektor v3 | Wartosc mediany : " << median << " Wartosc sumy: " << sum << endl;

	tie(median, sum) = GetTask3Output(v4);
	cout << "Wektor v4 | Wartosc mediany : " << median << " Wartosc sumy: " << sum << endl;

	cout << "Etap 4." << endl;
	//4. (1 pkt) Wyznaczy� losow� liczb� k4 z przedzia�u [2;6), wyznaczy� liczb� element�w podzielnych przez k4 w wektorze v4, a nast�pnie usun�� te elementy z wektora
	int k4 = 0;
	int count_k4 = 0;
	vector<int> output_task4(v4);

	//TODO
	k4 = rand() % 4 + 2;
	for_each(output_task4.begin(), output_task4.end(), [k4, &count_k4](int element)
		{
			if (element % k4 == 0) { count_k4++; }
		});

	remove_if(output_task4.begin(), output_task4.end(), [k4](int element) {return (element % k4 == 0); });
	output_task4.erase(output_task4.end() - count_k4, output_task4.end());

	cout << "k4=" << k4 << " Liczba elementow podzielnych przez k4 w wektorze v4: " << count_k4 << endl;
	PrintVector(output_task4);

	cout << "Etap 5." << endl;
	//5. (1 pkt) Posortowa� rosn�co wektor v4 wzgl�dem warto�ci modu�u element�w,
	//    a nast�pnie usun�� duplikaty dla tej samej warto�ci modu�u (np. je�eli w wektorze s� warto�ci -1, 1, 1 to po usuni�ciu
	//    duplikat�w zostanie jeden z tych elemenet�w), na koniec znale�� ostatni element, kt�ry jest podzielny przez 3
	int last_element = -100;
	vector<int> output_task5(v4);

	//TODO
	int count_k5 = 0;
	sort(output_task5.begin(), output_task5.end(), [](int el1, int el2) {return abs(el1) < abs(el2); });

	int previous = output_task5[0];
	remove_if(output_task5.begin() + 1, output_task5.end(), [&previous, &count_k5](int element)
		{	
			if (abs(previous) == abs(element)) 
			{
				count_k5++;
				return true;
			}
			else
			{
				previous = element;
				return false;
			}
		});
	output_task5.erase(output_task5.end() - count_k5, output_task5.end());

	for_each(output_task5.begin(), output_task5.end(), [&last_element](int element)
		{
			if (element % 3 == 0) { last_element = element; }
		});

	cout << "Ostatni element wektora podzielny przez 3: " << last_element << endl;
	PrintVector(output_task5);

	return 0;
}

