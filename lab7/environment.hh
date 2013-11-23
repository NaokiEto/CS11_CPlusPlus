#ifndef ENVIRONMENT_HH
#define ENVIRONMENT_HH

#include <map>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;


/**
 * A simple environment for storing symbols and their numeric values.  Internal
 * representation uses an STL map, which associates string keys with double
 * values.
 *
 * Symbols can be accessed with the getSymbolValue function.  Note that if an
 * unrecognized symbol name is specified, a runtime_error is thrown!
 *
 * Symbols can be set with the setSymbolValue function.  If a symbol name isn't
 * yet specified in the environment, the symbol is created.  If the name already
 * appears in the environment, its value is simply replaced.
 **/
class Environment {
  /** Collection of name/value pairs. **/
  map<string, double> m_symbols;

public:
  Environment() { }

  double getSymbolValue(const string &name) const {
    map<string, double>::const_iterator citer = m_symbols.find(name);
    
    if (citer == m_symbols.end()) {
      ostringstream oss;
      oss << "Symbol undefined:  '" << name << "'";
      throw runtime_error(oss.str());
    }

    return (*citer).second;
  }
  
  void setSymbolValue(const string &name, double value) {
    m_symbols[name] = value;
  }
};


#endif // ENVIRONMENT_HH

