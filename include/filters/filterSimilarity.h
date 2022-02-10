/**********************************************************************
filterSimilarity.h - filter-it
 
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



#ifndef __FILTERSIMILARITY_H__
#define __FILTERSIMILARITY_H__

#include <filters/filter.h>
#include <fingerprint.h>



class FilterSimilarity: public Filter 
{
   protected:
      
      std::string             _smiles;
      std::string             _name;
      std::vector<unsigned int> _reffp;
      std::vector<unsigned int> _molfp;
      double                  _min;
      double                  _max;
      bool                    _minLimit;
      bool                    _maxLimit;
      double                  _result;
      Fingerprint             _fingerprinter;
   
   public:
   
      FilterSimilarity(void);
      virtual ~FilterSimilarity(void);
      FilterSimilarity(const FilterSimilarity&);
      FilterSimilarity& operator=(const FilterSimilarity&);

      virtual bool            Initialise(const std::string&, const bool);
      
      virtual std::string     Name(void) const;
      virtual std::string     Smiles(void) const;
      
      virtual std::string     FailMessage(const OpenBabel::OBMol*) const;
      virtual double          Result(void) const;

      virtual void            Calculate(OpenBabel::OBMol*);
};



#endif
