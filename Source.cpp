//----------------------------- Project #1 ----------------------------------------------------------------------------------------------

//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//
//using namespace std;
//
//mutex mtx;
//condition_variable cv;
//bool production_complete = false;
//
//int doors = 0;
//int windows = 0;
//int stones = 0;
//
//const int MAX_DOORS = 2;
//const int MAX_WINDOWS = 4;
//const int MAX_STONES = 100;
//
//void produce_doors() {
//    while (true) {
//        /*
//         Тут створюється об'єкт unique_lock, який блокує
//         м'ютекс mtx (гарантує, що інші потоки не
//         змінять doors, windows, stones одночасно).
//
//		unique_lock зручніший за lock_guard, бо дозволяє
//		вручну розблокувати (unlock()) м'ютекс пізніше.
//         */
//        unique_lock<mutex> lock(mtx);
//        if (production_complete) break;
//        if (doors < MAX_DOORS) {
//            doors++;
//            cout << "Виготовлено двері. Усього: " << doors << endl;
//        }
//        if (doors >= MAX_DOORS && windows >= MAX_WINDOWS && stones >= MAX_STONES) {
//            production_complete = true;
//            cv.notify_all();
//            break;
//        }
//        lock.unlock();
//        this_thread::sleep_for(chrono::milliseconds(100));
//    }
//}
//
//void produce_windows() {
//    while (true) {
//        unique_lock<mutex> lock(mtx);
//        if (production_complete) break;
//        if (windows < MAX_WINDOWS) {
//            windows++;
//            cout << "Зроблено вікно. Усього: " << windows << endl;
//        }
//        if (doors >= MAX_DOORS && windows >= MAX_WINDOWS && stones >= MAX_STONES) {
//            production_complete = true;
//            cv.notify_all();
//            break;
//        }
//        lock.unlock();
//        this_thread::sleep_for(chrono::milliseconds(100));
//    }
//}
//
//void produce_stones(const string& worker_name) {
//    while (true) {
//        unique_lock<mutex> lock(mtx);
//        if (production_complete) break;
//        if (stones < MAX_STONES) {
//            stones++;
//            cout << worker_name << " зробив камінь. Усього: " << stones << endl;
//        }
//        if (doors >= MAX_DOORS && windows >= MAX_WINDOWS && stones >= MAX_STONES) {
//            production_complete = true;
//            cv.notify_all();
//            break;
//        }
//        lock.unlock();
//        this_thread::sleep_for(chrono::milliseconds(50));
//    }
//}
//
//int main() {
//    system("chcp 65001 > nul");
//    /*srand(time(0));*/
//
//
//    thread t1(produce_doors);
//    thread t2(produce_windows);
//    thread t3(produce_stones, "Робочий 1");
//    thread t4(produce_stones, "Робочий 2");
//
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//
//    cout << "Виробництво завершено: "
//        << doors << " дверей, "
//        << windows << " вікон, "
//        << stones << " каміння." << endl;
//
//}


// ----------------------------- Project #2 ----------------------------------------------------------------------------------------------

//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <condition_variable>
//
//#define RED "\033[31m"
//#define GREEN "\033[32m"
//#define YELLOW "\033[33m"
//#define BLUE "\033[34m"
//#define MAGENTA "\033[35m"
//#define CYAN "\033[36m"
//#define WHITE "\033[37m"
//#define RESET "\033[0m"
//
//using namespace std;
//
//mutex mtx;
//condition_variable cv;
//bool production_completed = false;
//bool packaging_completed;
//
//int currentBunsFactoryOne, currentBunsFactoryTwo = 0;
//
//const int EXPECTED_BUNS_FACTORY_1 = 50;
//const int EXPECTED_BUNS_FACTORY_2 = 24;
//
//const int CONVEYOR_NUMBER = 5;
//
//void produceBunsFactory1(const string& factoryName)
//{
//	while (true)
//	{
//		unique_lock<mutex> lock(mtx);
//		if (production_completed) break;
//
//		if (currentBunsFactoryOne < EXPECTED_BUNS_FACTORY_1)
//		{
//			currentBunsFactoryOne++;
//			cout << GREEN << "Фабрика " << factoryName << " виготовила 1 булочку. Всього булочок фабрики " << factoryName << ": " << currentBunsFactoryOne << RESET << endl;
//		}
//		if (currentBunsFactoryOne >= EXPECTED_BUNS_FACTORY_1 && currentBunsFactoryTwo >= EXPECTED_BUNS_FACTORY_2)
//		{
//			production_completed = true;
//			cv.notify_all();
//			break;
//		}
//		lock.unlock();
//		this_thread::sleep_for(chrono::milliseconds(100));
//	}
//}
//
//void produceBunsFactory2(const string& factoryName)
//{
//	while (true)
//	{
//		unique_lock<mutex> lock(mtx);
//		if (production_completed) break;
//
//		if (currentBunsFactoryTwo < EXPECTED_BUNS_FACTORY_2)
//		{
//			currentBunsFactoryTwo++;
//			cout << RED << "Фабрика " << factoryName << " виготовила 1 булочку. Всього булочок фабрики " << factoryName << ": " << currentBunsFactoryTwo << RESET << endl;
//		}
//		if (currentBunsFactoryOne >= EXPECTED_BUNS_FACTORY_1 && currentBunsFactoryTwo >= EXPECTED_BUNS_FACTORY_2)
//		{
//			production_completed = true;
//			cv.notify_all();
//			break;
//		}
//		lock.unlock();
//		this_thread::sleep_for(chrono::milliseconds(100));
//	}
//}
//
//void conveyor(const int& conveyorNumber, const string& factoryNameOne, const string& factoryNameTwo)
//{
//	int lastPacked1 = 0;
//	int lastPacked2 = 0;
//
//	while (true)
//	{
//		unique_lock<mutex> lock(mtx);
//		if (production_completed && currentBunsFactoryOne - lastPacked1 < conveyorNumber && currentBunsFactoryTwo - lastPacked2 <= conveyorNumber) break;
//
//
//		if (currentBunsFactoryOne - lastPacked1 >= conveyorNumber)
//		{
//			lastPacked1 += conveyorNumber;
//			cout << YELLOW << "Конвеєр " << factoryNameOne << " упакував " << conveyorNumber << " булочок" << RESET << endl;
//		}
//		if (currentBunsFactoryTwo - lastPacked2 >= conveyorNumber)
//		{
//			lastPacked2 += conveyorNumber;
//			cout << YELLOW << "Конвеєр " << factoryNameTwo << " упакував " << conveyorNumber << " булочок" << RESET << endl;
//		}
//		lock.unlock();
//		this_thread::sleep_for(chrono::milliseconds(100));
//	}
//	unique_lock<mutex> lock(mtx);
//	packaging_completed = true;
//	cv.notify_all();
//}
//
//void workDone()
//{
//	unique_lock<mutex> lock(mtx);
//	cv.wait(lock, []()
//	{
//			return production_completed && packaging_completed;
//	});
//	cout << CYAN << "Виробництво завершено: "
//		<< currentBunsFactoryOne << " булочок фабрики ROSHEN, "
//		<< currentBunsFactoryTwo << " булочок фабрики MILKA." << RESET << endl;
//}
//
//
//int main()
//{
//	system("chcp 65001 > nul");
//	thread t1(produceBunsFactory1, "ROSHEN");
//	thread t2(produceBunsFactory2, "MILKA");
//	thread t3(conveyor, CONVEYOR_NUMBER, "ROSHEN", "MILKA");
//	thread t4(workDone);
//
//	t1.join();
//	t2.join();
//	t3.join();
//	t4.join();
//
//
//	return 0;
//}

// ----------------------------- Project #3 ----------------------------------------------------------------------------------------------

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

using namespace std;

mutex mtxPizzasAndSauces;  // для піц і соусів
mutex mtxBaking;           // для випічки
mutex mtxPackaging;        // для пакування



condition_variable cv;
bool pizzas_completed = false;
bool sauces_completed = false;
bool baking_completed = false;
bool packaging_completed = false;

int currentPizzas = 0, currentSauces = 0, bakedPizzas = 0, packagedPizzas = 0;


const int EXPECTED_PIZZAS = 50;
const int EXPECTED_SAUCES = 50;

void producePizzas(const string& pizzaName)
{
	while (true)
	{
		unique_lock<mutex> lockForPizzasAndSauces(mtxPizzasAndSauces);
		if (pizzas_completed) break;
		if (currentPizzas < EXPECTED_PIZZAS)
		{
			currentPizzas++;
			cout << GREEN << "1 піца " << pizzaName << " виготовлена. Всього піц: " << currentPizzas << RESET << endl;
		}
		if (currentPizzas >= EXPECTED_PIZZAS)
		{
			pizzas_completed = true;
			cv.notify_all();
			break;
		}
		lockForPizzasAndSauces.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void produceSauces(const string& pizzaName)
{
	while (true)
	{
		unique_lock<mutex> lockForPizzasAndSauces(mtxPizzasAndSauces);
		if (sauces_completed) break;
		if (currentSauces < EXPECTED_SAUCES)
		{
			currentSauces++;
			cout << RED << "1 соус для " << pizzaName << " виготовлений. Всього соусів: " << currentSauces << RESET << endl;
		}
		if (currentSauces >= EXPECTED_SAUCES)
		{
			sauces_completed = true;
			cv.notify_all();
			break;
		}
		lockForPizzasAndSauces.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}


void bakePizzas(const string& pizzaName)
{
	unique_lock<mutex> lockForPizzasAndSauces(mtxPizzasAndSauces);
	cv.wait(lockForPizzasAndSauces, []()
		{
			return pizzas_completed && sauces_completed;
		});
	while (true)
	{
		unique_lock<mutex> lockForBaking(mtxBaking);
		if (baking_completed) break;
		if (bakedPizzas < EXPECTED_PIZZAS)
		{
			bakedPizzas++;
			cout << YELLOW << "1 піца " << pizzaName << " спечена. Всього спечених піц: " << bakedPizzas << RESET << endl;
		}
		if (bakedPizzas >= EXPECTED_PIZZAS)
		{
			baking_completed = true;
			cv.notify_all();
			break;
		}

		lockForBaking.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void packagePizzas()
{
	try {
		unique_lock<mutex> lockForBaking(mtxBaking);
		cv.wait(lockForBaking, []() {
			return baking_completed;
			});

		while (true)
		{
			unique_lock<mutex> lockForPackaging(mtxPackaging);
			if (packaging_completed) break;

			if (packagedPizzas < EXPECTED_PIZZAS)
			{
				packagedPizzas++;
				cout << BLUE << "1 піца упакована. Всього упакованих піц: " << packagedPizzas << RESET << endl;
			}
			if (packagedPizzas >= EXPECTED_PIZZAS)
			{
				packaging_completed = true;
				cv.notify_all();
				break;
			}
			lockForPackaging.unlock();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Помилка: " << e.what() << std::endl;
	}
}

void workDone()
{
	try {
		unique_lock<mutex> lockForPackaging(mtxPackaging);
		cv.wait(lockForPackaging, []()
			{
				return packaging_completed;
			});
		cout << CYAN << "Виробництво завершено!" << RESET;
	}
	catch (const std::exception& e) {
		std::cerr << "Помилка: " << e.what() << std::endl;
	}
}

int main() {
	system("chcp 65001 > nul");

	thread pizzas(producePizzas, "Pepperoni ");
	thread sauces(produceSauces, "Pepperoni ");
	thread baking(bakePizzas, "Pepperoni ");
	thread packaging(packagePizzas);
	thread pizzasReadyForDelivering(workDone);

	pizzas.join();
	sauces.join();
	baking.join();
	packaging.join();
	pizzasReadyForDelivering.join();
	
	return 0;
}