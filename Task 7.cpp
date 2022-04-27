#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <random>




bool is_in_circle(float x, float y, float radius);
void calculations(int N, int seed_0, float& result);

int main(int argc, char** argv)
{

	char set_parallel;
	int radius = 0.5;
	int count_of_iter = 0;

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);

	std::cout << "Use paralell version? Insert y/n, if you insert n, program will use only one thread" << std::endl;
	std::cin >> set_parallel;

	std::cout << "Insert count of interations: " << std::endl;
	std::cin >> count_of_iter;

	if (set_parallel == 'y') {

		float result_1 = 0;
		float result_2 = 0;

		std::thread t1(calculations, count_of_iter, rd(), std::ref(result_1));
		std::thread t2(calculations, count_of_iter, rd()+1, std::ref(result_2));

		t1.join();
		t2.join();

		std::cout << result_1 << std::endl;
		std::cout << result_2 << std::endl;

		std::cout << "pi is equal: " << (result_1 + result_2) / 2;
		
	}
	if (set_parallel == 'n') {
		float result_3 = 0;
		calculations(count_of_iter, rd()+3, std::ref(result_3));
		std::cout << "pi is equal: " << result_3 << std::endl;
	}

	if (set_parallel != 'n' and set_parallel != 'y') {
		std::cout << "wrong input" << std::endl;
	}



	
}


bool is_in_circle(float x, float y, float radius) {   //centre of circle is (radius, radius)
	return ((x - radius) * (x - radius) + (y - radius) * (y - radius) < radius * radius);
}

void calculations(int N, int seed_0, float &result){

	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(seed_0);
	std::uniform_real_distribution<> dis(0.0, 1.0);

	float radius = 0.5;
	int counter_in = 0;

	for (int i = 0; i < N; i++) {
		if (is_in_circle(dis(gen), dis(gen), radius)) { counter_in++; };
	}

	result = 4 * counter_in / (N * 1.0);
}