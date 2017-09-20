#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"
using namespace std;

	//list<double> shapeList;
	
	

	vertex vertex_1 = {0,0};
	vertex vertex_2 = {0,3};
	vertex vertex_3 = {4,0};
	Triangle tri(vertex_1,vertex_2,vertex_3,"t1"); //perimter 12 area 6 compactness 0.5
		
	Circle cir(0,0,5, "c1"); //perimter 10pi area 25pi compactness 2.5

	Rectangle rect(0,0,8,9, "r1"); //perimter 34 area 72 compactness 2.1

TEST (Sort, sortByIncreasingPerimeter) {

	std::list<Shape *>mylist;
	mylist.push_back(&cir);
	mylist.push_back(&tri);
	mylist.push_back(&rect);

	Sort sort;
	sort.sortByIncreasingPerimeter(&mylist);

	list<Shape *>::iterator it = mylist.begin();
	
	// for(it =mylist.begin();it != mylist.end();++it){
	// 	cout << (*it)->getShapeName() <<endl;
	// }
	// cout << (*it)->getShapeName();
	// ++it;
	// cout << (*it)->getShapeName();
	// ++it;
	// cout << (*it)->getShapeName();
	// cout  <<endl;

	ASSERT_EQ(tri.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(cir.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(rect.name,(*it)->getShapeName());
	
}

TEST (Sort, sortByDecreasingPerimeter) {
	std::list<Shape *>mylist;
	mylist.push_back(&cir);
	mylist.push_back(&tri);
	mylist.push_back(&rect);

	Sort sort;
	sort.sortByDecreasingPerimeter(&mylist);

	list<Shape *>::iterator it = mylist.begin();

	ASSERT_EQ(rect.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(cir.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(tri.name,(*it)->getShapeName());
}

TEST (Sort, sortByIncreasingArea) {
	std::list<Shape *>mylist;
	mylist.push_back(&cir);
	mylist.push_back(&tri);
	mylist.push_back(&rect);

	Sort sort;
	sort.sortByIncreasingArea(&mylist);

	list<Shape *>::iterator it = mylist.begin();

	ASSERT_EQ(tri.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(rect.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(cir.name,(*it)->getShapeName());
}

TEST (Sort, sortByDecreasingArea) {
	std::list<Shape *>mylist;
	mylist.push_back(&cir);
	mylist.push_back(&tri);
	mylist.push_back(&rect);

	Sort sort;
	sort.sortByDecreasingArea(&mylist);

	list<Shape *>::iterator it = mylist.begin();

	ASSERT_EQ(cir.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(rect.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(tri.name,(*it)->getShapeName());
}

TEST (Sort, sortByIncreasingCompactness) {
	std::list<Shape *>mylist;
	mylist.push_back(&cir);
	mylist.push_back(&tri);
	mylist.push_back(&rect);

	Sort sort;
	sort.sortByIncreasingCompactness(&mylist);

	list<Shape *>::iterator it = mylist.begin();

	ASSERT_EQ(tri.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(rect.name,(*it)->getShapeName());
	++it;
	ASSERT_EQ(cir.name,(*it)->getShapeName());
}

#endif
