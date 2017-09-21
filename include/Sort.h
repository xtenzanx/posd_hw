#include <list>
#include "Shapes.h"
using namespace std;

class Sort {

  public :static void sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
    list<Shape *>::iterator left = shapeList->begin();
    list<Shape *>::iterator right = shapeList->end();
    right--;

    list<Shape *>::iterator temp;

    while (left != right)
    {
        for (list<Shape *>::iterator i = left; i != right; ++i)
        {
            list<Shape *>::iterator next = i;
            next++;
            if ((*i)->perimeter() > (*next)->perimeter())
            {
                swap(*i, *next);
                temp = i;
            }
        }
        right = temp;
        for (list<Shape *>::iterator i = right; i != left; i--)
        {
            list<Shape *>::iterator last = i;
            last--;
            if ((*i)->perimeter() < (*last)->perimeter())
            {
                swap(*i, *last);
                temp = i;
            }
        }
        left = temp;
    }
  };

  public :static void sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    list<Shape *>::iterator left = shapeList->begin();
    list<Shape *>::iterator right = shapeList->end();
    right--;

    list<Shape *>::iterator temp;

    while (left != right)
    {
        for (list<Shape *>::iterator i = left; i != right; ++i)
        {
            list<Shape *>::iterator next = i;
            next++;
            if ((*i)->perimeter() < (*next)->perimeter())
            {
                swap(*i, *next);
                temp = i;
            }
        }
        right = temp;
        for (list<Shape *>::iterator i = right; i != left; i--)
        {
            list<Shape *>::iterator last = i;
            last--;
            if ((*i)->perimeter() > (*last)->perimeter())
            {
                swap(*i, *last);
                temp = i;
            }
        }
        left = temp;
    }
  };

  public :static void sortByIncreasingArea(std::list<Shape *> * shapeList){
    list<Shape *>::iterator left = shapeList->begin();
    list<Shape *>::iterator right = shapeList->end();
    right--;

    list<Shape *>::iterator temp;

    while (left != right)
    {
        for (list<Shape *>::iterator i = left; i != right; ++i)
        {
            list<Shape *>::iterator next = i;
            next++;
            if ((*i)->area() > (*next)->area())
            {
                swap(*i, *next);
                temp = i;
            }
        }
        right = temp;
        for (list<Shape *>::iterator i = right; i != left; i--)
        {
            list<Shape *>::iterator last = i;
            last--;
            if ((*i)->area() < (*last)->area())
            {
                swap(*i, *last);
                temp = i;
            }
        }
        left = temp;
    }
  };

  public :static void sortByDecreasingArea(std::list<Shape *> * shapeList){
    list<Shape *>::iterator left = shapeList->begin();
    list<Shape *>::iterator right = shapeList->end();
    right--;

    list<Shape *>::iterator temp;

    while (left != right)
    {
        for (list<Shape *>::iterator i = left; i != right; ++i)
        {
            list<Shape *>::iterator next = i;
            next++;
            if ((*i)->area() < (*next)->area())
            {
                swap(*i, *next);
                temp = i;
            }
        }
        right = temp;
        for (list<Shape *>::iterator i = right; i != left; i--)
        {
            list<Shape *>::iterator last = i;
            last--;
            if ((*i)->area() > (*last)->area())
            {
                swap(*i, *last);
                temp = i;
            }
        }
        left = temp;
    }
  };
  
  public :static void sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    list<Shape *>::iterator left = shapeList->begin();
    list<Shape *>::iterator right = shapeList->end();
    right--;

    list<Shape *>::iterator temp;

    while (left != right)
    {
        for (list<Shape *>::iterator i = left; i != right; ++i)
        {
            list<Shape *>::iterator next = i;
            next++;
            if ((*i)->area() / (*i)->perimeter() / (*i)->perimeter() > (*next)->area() / (*next)->perimeter() / (*next)->perimeter())
            {
                swap(*i, *next);
                temp = i;
            }
        }
        right = temp;
        for (list<Shape *>::iterator i = right; i != left; i--)
        {
            list<Shape *>::iterator last = i;
            last--;
            if ((*i)->area() / (*i)->perimeter() / (*i)->perimeter() < (*last)->area() / (*last)->perimeter() / (*last)->perimeter())
            {
                swap(*i, *last);
                temp = i;
            }
        }
        left = temp;
    }
  };



public:
  static string sortPerimeterOut(std::list<Shape *> *shapeList)
  {
      std::stringstream ss;
      for (list<Shape *>::iterator i = shapeList->begin(); i != shapeList->end(); i++)
      {
          ss << " name:" << (*i)->getShapeName() << ", perimeter= " << (*i)->perimeter();
      }

      return ss.str();
  }

public:
  static string sortAreaOut(std::list<Shape *> *shapeList)
  {
      std::stringstream ss;
      for (list<Shape *>::iterator i = shapeList->begin(); i != shapeList->end(); i++)
      {
          ss << " name:" << (*i)->getShapeName() << ", area= " << (*i)->area();
      }

      return ss.str();
  }

public:
  static string sortCompactnessOut(std::list<Shape *> *shapeList)
  {
      std::stringstream ss;
      for (list<Shape *>::iterator i = shapeList->begin(); i != shapeList->end(); i++)
      {
          ss << " name:" << (*i)->getShapeName() << ", area= " << (*i)->area()/(*i)->perimeter() / (*i)->perimeter();
      }

      return ss.str();
  }
  
};
