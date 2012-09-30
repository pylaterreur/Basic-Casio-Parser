
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Usage: " << *argv << "prog [subprog ...]" << std::endl;
      return (-1);
    }
  std::cout << "Done" << std::endl;
}
