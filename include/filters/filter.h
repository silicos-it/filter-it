/**********************************************************************
filter.h - filter-it
 
Copyright 2012-2013 by Silicos-it, a division of Imacosi BVBA
 
This file is part of Filter-it.

	Filter-it is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published 
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Filter-it is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with Filter-it.  If not, see <http://www.gnu.org/licenses/>.

Filter-it is linked against OpenBabel version 2.

	OpenBabel is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation version 2 of the License.

***********************************************************************/



#ifndef __FILTER_H__
#define __FILTER_H__




#include <set>
#include <map>
#include <math.h>
#include <string>
#include <sstream>
#include <ctype.h>
#include <stdlib.h>
#include <string>

#include <fingerprint.h>

#include <openbabel/mol.h>
#include <openbabel/atom.h>
#include <openbabel/bond.h>
#include <openbabel/obconversion.h>
#include <openbabel/obiter.h>
#include <openbabel/parsmart.h>
#include "openbabel/stereo/tetrahedral.h"



class Filter 
{
   protected:
   
      bool              _initialised;
      std::string       _whiteSpace;
      bool              _passed;
      std::string       _keyword;
      
   public:
   
      Filter(void);
      virtual ~Filter(void);
      Filter(const Filter&);
      Filter& operator=(const Filter&);

      virtual bool         Initialise(const std::string&, const bool) = 0;
      virtual bool         IsInitialised(void) const;
      
      virtual std::string  Keyword(void) const;
      
      virtual std::string  FailMessage(const OpenBabel::OBMol*) const = 0;

      virtual void         Calculate(OpenBabel::OBMol*) = 0;
      virtual bool         HasPassed(void) const;
      virtual bool         HasFailed(void) const;
};



#endif
