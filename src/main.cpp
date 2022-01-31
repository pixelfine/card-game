#include <iostream>
#include <stdexcept>
#include <memory>

#include "./BaseGame/Input.hpp"
#include "./Games/MainGame.hpp"
#include "./Games/Americain.hpp"
#include "./Games/Tarot.hpp"
#include "./Games/Belote.hpp"
using namespace std;

int main(){
	std::cout << "Hello world!" << std::endl;

	GameComponent component = GameComponent();
	int n = Input::numericIn("1 : Bataille\n2 : Americain\n3 : Tarot\n4 : Belote\n");
	switch(n){
		case 1 : MainGame(component).start(); break;
		case 2 : Americain(component).start(); break;
		case 3 : Tarot(component).start(); break;
		case 4 : Belote(component).start(); break;
	}
}