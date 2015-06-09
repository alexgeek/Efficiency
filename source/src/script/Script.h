#ifndef SCRIPT_H
#define SCRIPT_H

#include <iostream>
#include <lua.hpp>
#include <string>

class Script
{
    public:
      Script();
      Script(std::string name, std::string contents_);
      /* accessors & mutators */
      std::string Name() const { return name_; }
      std::string Contents() const { return contents_; }
    protected:
    private:
      std::string name_;
      std::string contents_;

};

#endif
