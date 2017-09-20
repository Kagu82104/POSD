#include <list>
#include "Shapes.h"
using namespace std;
class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList)
  {
     
    list<Shape *>::iterator it1 = shapeList->begin() ;
    list<Shape *>::iterator it2 = shapeList->begin() ;
    Shape *temp;
    for ( int i=0; i<shapeList->size()-1; i++)
    {

      for (int j = 0; j < shapeList->size()-1-i; j++)
      {
        advance(it1,j);
        advance(it2,j+1);

          if ((*it1)->perimeter() > (*it2)->perimeter())
          {
            temp = *it1;
            *it1 = *it2;
            *it2 = temp;
          }
          it1=shapeList->begin();
          it2=shapeList->begin();
        
      }
      
    }
     

  };

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    list<Shape *>::iterator it1 = shapeList->begin() ;
    list<Shape *>::iterator it2 = shapeList->begin() ;
    Shape *temp;
    for ( int i=0; i<shapeList->size()-1; i++)
    {

      for (int j = 0; j < shapeList->size()-1-i; j++)
      {
        advance(it1,j);
        advance(it2,j+1);

          if ((*it1)->perimeter() < (*it2)->perimeter())
          {
            temp = *it1;
            *it1 = *it2;
            *it2 = temp;
          }
          it1=shapeList->begin();
          it2=shapeList->begin();
        
      }
      
    }
  };

  public :static void sortByIncreasingArea(std::list<Shape *> * shapeList){
    list<Shape *>::iterator it1 = shapeList->begin() ;
    list<Shape *>::iterator it2 = shapeList->begin() ;
    Shape *temp;
    for ( int i=0; i<shapeList->size()-1; i++)
    {

      for (int j = 0; j < shapeList->size()-1-i; j++)
      {
        advance(it1,j);
        advance(it2,j+1);

          if ((*it1)->area() > (*it2)->area())
          {
            temp = *it1;
            *it1 = *it2;
            *it2 = temp;
          }
          it1=shapeList->begin();
          it2=shapeList->begin();
        
      }
      
    }
  };

  public :static void sortByDecreasingArea(std::list<Shape *> * shapeList)
  {
     list<Shape *>::iterator it1 = shapeList->begin() ;
    list<Shape *>::iterator it2 = shapeList->begin() ;
    Shape *temp;
    for ( int i=0; i<shapeList->size()-1; i++)
    {

      for (int j = 0; j < shapeList->size()-1-i; j++)
      {
        advance(it1,j);
        advance(it2,j+1);

          if ((*it1)->area() < (*it2)->area())
          {
            temp = *it1;
            *it1 = *it2;
            *it2 = temp;
          }
          it1=shapeList->begin();
          it2=shapeList->begin();
        
      }
      
    }
  };
  
  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    list<Shape *>::iterator it1 = shapeList->begin() ;
    list<Shape *>::iterator it2 = shapeList->begin() ;
    Shape *temp;
    for ( int i=0; i<shapeList->size()-1; i++)
    {

      for (int j = 0; j < shapeList->size()-1-i; j++)
      {
        advance(it1,j);
        advance(it2,j+1);

          if (((*it1)->area()/(*it1)->perimeter()) > ((*it2)->area()/(*it2)->perimeter()))
          {
            temp = *it1;
            *it1 = *it2;
            *it2 = temp;
          }
          it1=shapeList->begin();
          it2=shapeList->begin();
        
      }
      
    }
};
};