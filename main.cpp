#include <iostream>
#include "Ship.h"
#include "Cruiser.h"
#include "Freighter.h"
#include "Controller.h"
int main(int argc, char *argv[]) {
	Model &a = Model::get_Instance();

	a.addView(new View()); //View with default parameters

	auto *q = new Controller(a.getViewVector()[0].get());

	//adds the data(i.e initial information about the ports) in the file given as a parameter to the program

    if (argv[1]== nullptr)
        cerr<<"file name not valid";
    else
	    Controller::init(argv[1]);

    //runs the loop that interacts with user
	q->run();

	return 0;
}
