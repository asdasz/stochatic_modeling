#include "pch.h"
#include "../../../mgr/mgr/diff_fun.cpp"
#include <vector>


TEST(fitness_functions, fitness_sphere) {
	 std::vector<double> x = { 0.0, 4.0, 8.0, 12.0, 16.0, 20.0 }; // pow(1)+pow(2)+pow(3)+pow(4)+pow(5)
  EXPECT_EQ(fitness_sphere(x), 55);
	x = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; 
  EXPECT_EQ(fitness_sphere(x), 1375.0); // pow(5) + pow(10) + pow(15) + pow(20) + pow(25)
	x = { 0.0, 5.3 }; 
  EXPECT_TRUE(fitness_sphere(x) > 0.089 && fitness_sphere(x) < 0.091); //pow(0.3)
	x = { 0.0, 5.0 }; 
  EXPECT_EQ(fitness_sphere(x), 0.0); //(pow(0))
}

TEST(fitness_functions, fitness_rastrigin) {
	std::vector<double> x = { 0.0, 4.0, 8.0, 12.0, 16.0, 20.0 }; // pow(4)+pow(8)+pow(12)+pow(16)+pow(20)
	EXPECT_EQ(fitness_rastrigin(x), 880);
	x = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // 5* pow(0)
	EXPECT_EQ(fitness_rastrigin(x), 0);
	x = { 0.0, 5.3 }; // pow(5.3) == 28.09 rest == 13.0902 sum == 41.1802
	EXPECT_TRUE(fitness_rastrigin(x) > 41.18 && fitness_rastrigin(x) < 41.181);
	x = { 0.0, 0.5 }; //0.25 + 20
	EXPECT_EQ(fitness_rastrigin(x), 20.25); 
}

