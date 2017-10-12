//
//  CoreIO.h
//  concreteOS
//
//  Created by Jonathan Archer on 10/11/17.
//

#ifndef CoreIO_h
#define CoreIO_h


#endif /* CoreIO_h */

extern char * KeyLine;

class CoreIO {
    
public:
    
    char * GetKeys() {
        
        return KeyLine;
    }
    
};

static CoreIO CoreIO;
