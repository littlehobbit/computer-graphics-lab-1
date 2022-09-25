#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Object;

class Component {
 public:
  Component(Object* owner) : owner(owner) {}
  virtual ~Component() = default;

  virtual void process() {}

 protected:
  Object* owner = nullptr;
};

#endif  // __COMPONENT_H__