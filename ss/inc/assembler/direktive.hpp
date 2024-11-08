#ifndef _DIREKTIVE_HPP
#define _DIREKTIVE_HPP
#include "../strukture.hpp"
#include "kod.hpp"
#include <vector>

Kod direktiva_SKIP(Linija L);
void direktiva_WORD(Linija L, std::vector<Kod>& kodovi);
Kod direktiva_ASCII(Linija L);


#endif