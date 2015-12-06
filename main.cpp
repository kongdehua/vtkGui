//#include <iostream>
#include <vtkConeSource.h>

//static int *x = new int(100);
int main(int argc, char **argv)
{
/*
  int *xx = new int[100];
	//std::cout << " hello " << std::endl;

	delete []xx;
	//delete x;
*/
	
	vtkConeSource *cone = vtkConeSource::New();
	cone->PrintSelf(std::cout, vtkIndent());


	return 0;
};

