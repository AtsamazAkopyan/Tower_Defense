//!
//! Created by armad on 5/21/2018.
//!

#ifndef PA2PROJECT_MAPOBJECTS_H
#define PA2PROJECT_MAPOBJECTS_H

//!All map objects will inherit from this class.
//!Polymorphism
class MapObjects {
public:
    MapObjects();

    virtual ~MapObjects();

    virtual bool isEmpty() const;
    virtual bool isPath () const;
    virtual bool isTower () const;
};


#endif //!PA2PROJECT_MAPOBJECTS_H
