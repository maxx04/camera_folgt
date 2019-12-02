#include "neck.h"

neck::neck()
{
	sh = new Servos(800, 2200, 1350);
	sv = new Servos(1200, 2200, 1700);
}


neck::~neck()
{
}

void neck::move_to(float a, float b)
{
	sh->move_to_angle(a,1000);
	sh->wait_on_position(3000);
	//OPTI Bewegung zusammen realisieren
	sv->move_to_angle(b,1000);
	sv->wait_on_position(3000); 
}

//void neck::move_to()
//{
//	sv->move_to_position();
//	sh->move_to_position();
//}

void neck::test()
{
	sv->test();
	sh->test();
}

//void neck::read_udp_data(float a, float b)
//{
//	sv->position = a;
//}