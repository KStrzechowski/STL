#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>

using namespace std;


// Korzystaj¹c z biblioteki STL nale¿y rozwi¹zaæ znajduj¹ce siê w funkcji main 5 zadañ (ka¿de po 1 pkt). Etapy 2-5 mo¿na rozwi¹zaæ w dowolnej kolejnoœci, 
// natomiast etap 1 nale¿y rozwi¹zaæ najpierw. Nale¿y korzystaæ z algorytmów i funktorów z biblioteki STL oraz wyra¿eñ lambda. 
// Zakazane jest korzystanie z pêtli!!! Wszystkie operacje modyfikuj¹ce zbiór wejœciowy powinny byæ wykonywane na jego kopii (Etapy 2-5)!!!

// Funkcja wypisuje na konsoli wszystkie elementy wektora za pomoc¹ for_each
void PrintVector(vector<int> input)
{
	//TODO
	for_each(input.begin(), input.end(), [](int element) {cout << element << " "; });
	cout << endl;
};

// Funkcja zwraca najwiêkszy element zbioru oraz zmodyfikowany zbiór w nastêpuj¹cy sposób:
//   - elementy znajduj¹ce siê przed elementem maksymalnym zostaj¹ pomno¿one przez wylosowan¹ liczbê k
//     (taka sama wartoœæ dla wszystkich elementów z przedzia³u [-10;10))
//   - pozosta³e elementy nie s¹ modyfikowane
//   - w przypadku gdy istnieje kilka elementów o wartoœci maksymalnej modyfikowane s¹ jedynie
//     elementy przed pierwszym wyst¹pieniem elementu maksymalnego
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

// Funkcja zwraca wartoœæ mediany dla podanego zbioru oraz sumê elementów wiêkszych modu³owo od mediany (|x| > |median|)
// Uwaga: mo¿na wykorzystaæ sortowanie
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
	//1. (1 pkt) Zaimplementowaæ funkcje PrintVector, która wypisuje elementy wektora
	// oraz uzupe³niæ nastêpuj¹ce wektory losowymi liczbami z przedzia³u:
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
	//2. (1 pkt) Po³¹czyæ wektory v1 i v2 w wektor v5 (czyli v5 zawiera najpierw elementy v1, a potem V2),
	// a nastêpnie zaimplementowaæ funkcjê GetTask2Output
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
	//3. (1 pkt) Zaimplementowaæ funkcjê GetTask3Output
	double median;
	int sum;

	tie(median, sum) = GetTask3Output(v3);
	cout << "Wektor v3 | Wartosc mediany : " << median << " Wartosc sumy: " << sum << endl;

	tie(median, sum) = GetTask3Output(v4);
	cout << "Wektor v4 | Wartosc mediany : " << median << " Wartosc sumy: " << sum << endl;

	cout << "Etap 4." << endl;
	//4. (1 pkt) Wyznaczyæ losow¹ liczbê k4 z przedzia³u [2;6), wyznaczyæ liczbê elementów podzielnych przez k4 w wektorze v4, a nastêpnie usun¹æ te elementy z wektora
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
	//5. (1 pkt) Posortowaæ rosn¹co wektor v4 wzglêdem wartoœci modu³u elementów,
	//    a nastêpnie usun¹æ duplikaty dla tej samej wartoœci modu³u (np. je¿eli w wektorze s¹ wartoœci -1, 1, 1 to po usuniêciu
	//    duplikatów zostanie jeden z tych elemenetów), na koniec znaleŸæ ostatni element, który jest podzielny przez 3
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

