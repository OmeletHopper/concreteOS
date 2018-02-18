//
//  input.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 2/18/18.
//

#ifndef input_hpp
#define input_hpp

extern struct typedCharacter KEY;

class io
{
public:

    void addKey(struct typedCharacter KEY);
    static int addKeySetting;
};

static io Input;  // Sets up our input class

#endif /* input_hpp */
