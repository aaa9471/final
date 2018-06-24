#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

class Object{
public:
    Object(){}
    ~Object(){}

    virtual void Draw() = 0; // pure function for drawing object

protected:

};

#endif
