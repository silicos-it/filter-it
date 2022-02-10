/**********************************************************************
filterLipinskiViolations.h - filter-it
 
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



#ifndef __FILTERLIPINSKIVIOLATIONS_H__
#define __FILTERLIPINSKIVIOLATIONS_H__

#include <filters/filterIntegerProperty.h>
#include <filters/filterLipinskiAcceptors.h>
#include <filters/filterLipinskiDonors.h>
#include <filters/filterLogp.h>




class FilterLipinskiViolations: public FilterIntegerProperty 
{
   protected:
   
      FilterLipinskiAcceptors       _lpa;
      FilterLipinskiDonors          _lpd;
      FilterLogp                    _logp;
      
      
   public:
   
      FilterLipinskiViolations(void);
      virtual ~FilterLipinskiViolations(void);
      FilterLipinskiViolations(const FilterLipinskiViolations&);
      FilterLipinskiViolations& operator=(const FilterLipinskiViolations&);

      virtual void            Calculate(OpenBabel::OBMol*);
};



#endif
