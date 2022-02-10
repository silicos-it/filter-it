/**********************************************************************
filterSimilarityStack.h - filter-it
 
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



#ifndef __FILTERSIMILARITYSTACK_H__
#define __FILTERSIMILARITYSTACK_H__

#include <filters/filterSimilarity.h>



class FilterSimilarityStack: public FilterSimilarity 
{
   protected:
      
   public:
   
      FilterSimilarityStack(void);
      virtual ~FilterSimilarityStack(void);
      FilterSimilarityStack(const FilterSimilarityStack&);
      FilterSimilarityStack& operator=(const FilterSimilarityStack&);

      virtual bool            Initialise(const std::string&, const bool);

      virtual double          GetMin(void) const;
      virtual double          GetMax(void) const;
      virtual bool            GetMinLimit(void) const;
      virtual bool            GetMaxLimit(void) const;
      
      virtual void            Calculate(OpenBabel::OBMol*);
};



#endif
