#include "keypoints.h"



keypoints::keypoints()
{
	step_vector_queue = new queue<Point2f>[MAX_COUNT];
	hist = histogram(10);
}


keypoints::~keypoints()
{
	//delete points_queue;
}

void keypoints::clear(void)
{
	prev_points.clear();
	current_points.clear();

}

void keypoints::swap(void)
{
	std::swap(current_points, prev_points);
}


///

int keypoints::load_step_vectors(void)
{
	Point2f step,sum = Point2f(0, 0);
	int number = 0;


	for (size_t i = 0; i < prev_points.size(); i++) 
	{
		if (status[i] == 1)
		{
			//speichere in zeit nur gute punkte
			//points_queue[i].push(current_points[i] - prev_points[i] - sum );
			step = (current_points[i] - prev_points[i]);
			sum += step;
			number++;
			step_vector_queue[i].push(step); // step vektor beladen
		}

	}

	if (number != 0) summ_vector.push(sum/(float)number); // TODO Assert 0, summandvektor beladen

	return number;
}

float keypoints::distance(Point2f a, Point2f b)
{
	return sqrt( pow((a.x - b.x),2) + pow((a.y - b.y),2));
}

float keypoints::length(Point2f a)
{
	return sqrt(pow((a.x), 2) + pow((a.y), 2));
}

double keypoints::get_queue_time(void)
{
	const double timeSec = (frame_timestamp.back() - frame_timestamp.front()) / getTickFrequency();
	// clean
	while (!frame_timestamp.empty()) frame_timestamp.pop();

	return timeSec;
}

vector<Point2f>* keypoints::get_next_points_addr(void)
{
	return &current_points;
}


Point2f keypoints::get_next_summ_vector()
{
	Point2f sum;

	sum = summ_vector.front();
	summ_vector.pop();

	return sum;
}

Point2f keypoints::get_next_step_vector(int i)
{
	Point2f p1 = step_vector_queue[i].front(); //HACK entnahme aus queue vector
	step_vector_queue[i].pop();
	return p1;
}

Point2f keypoints::get_mainmove_backgraund_vector()
{
	return Point2f();
}

int keypoints::calculate_move_vectors()
{
	Point2f p;
	const double M_PI = 3.14159265359;


	for (int i = 0; i < prev_points.size(); i++)
	{
		p = current_points[i] - prev_points[i]; //OPTI mehrmals woanders durchgefuehrt

		double d = fmodf((atan2(p.x, p.y) * (180.0 / M_PI)) + 360, 360);
		if (p.x != 0.0) 
			hist.collect(point_satz{ i , (float)d}); // TODO assert

	}

	hist.sort(); 
	

	//TODO finde hauptdirection: das ist background direction
	// dabei gut zu markieren die punkten die gehoeren mein backraund bewegung
	double d = hist.get_main_middle_value();
	hist.clear();

	//TODO nach histogram vectorlaenge finden hauptvector laenge
	// dabei gut zu markieren die punkten die gehoeren mein backraund bewegung

	float l;

	for (int i = 0; i < prev_points.size(); i++)
	{
		p = current_points[i] - prev_points[i]; //OPTI mehrmals woanders durchgefuehrt
		l = length(p);
		hist.collect(point_satz{ i , (float)l }); //
	}

	hist.sort();
	double v = hist.get_main_middle_value();
	hist.clear();

	//TODO weitere hauptvectors finden drehen um achse roll

	//TODO bei fortbewegegung ueber raeder drehgeschwindigkeit und zeit zwischen frames
	// kann man finden axiale abstand zwischen frames (gibt es alternativen f�r quadrakopter?
	// abstand zwischen zwei frames zu finden?)
	// dadurch kann man finden abstand zu keypoints

	//TODO rausnehmen den hauptvector aus punktenbewegung dabei wird man sehen eigene bewegung von punkten





 	return 0;
}
