//
//  input.hpp
//  concreteOS
//
//  Created by Jonathan Archer on 2/18/18.
//

#ifndef input_hpp
#define input_hpp

extern struct TypedCharacter KEY;

class io {
public:
  void addKey(struct TypedCharacter KEY);
  static int AddKeySetting;
};

static io Input; // Sets up our input class

#endif
