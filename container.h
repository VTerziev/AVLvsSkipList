#ifndef CONTAINER_GUARD
#define CONTAINER_GUARD

struct Container {
  virtual bool contains(int x) = 0;
  virtual void insert(int x) = 0;
  virtual void remove(int x) = 0;

  virtual ~Container() {};
};

#endif