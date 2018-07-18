//!
//! Created by armad on 5/21/2018.
//!

#include "MapObjects.h"

MapObjects::MapObjects() {

}
MapObjects::~MapObjects() {

}

bool MapObjects::isEmpty() const {
    return true;
}
bool MapObjects::isPath() const {
    return false;
}
bool MapObjects::isTower() const {
    return false;
}