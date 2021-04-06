#ifndef stringer_h
#define stringer_h

#include "Arduino.h"

class StringTokenizer
{
public:
    StringTokenizer(String str, String del);
    
    boolean hasNext();
    
    String nextToken();

private:
    
    String _str;
    
    String _del;
    
    int ptr;
};

#endif