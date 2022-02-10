/**********************************************************************
filterIntegerProperty.h - filter-it
 
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



#ifndef __FILTERINTEGERPROPERTY_H__
#define __FILTERINTEGERPROPERTY_H__

#include <filters/filter.h>



class FilterIntegerProperty: public Filter 
{
   protected:
      
      int                     _min;
      int                     _max;
      bool                    _minLimit;
      bool                    _maxLimit;
      int                     _result;
         
   public:
   
      FilterIntegerProperty(void);
      virtual ~FilterIntegerProperty(void);
      FilterIntegerProperty(const FilterIntegerProperty&);
      FilterIntegerProperty& operator=(const FilterIntegerProperty&);

      virtual bool            Initialise(const std::string&, const bool);
      
      virtual std::string     FailMessage(const OpenBabel::OBMol*) const;
      virtual int             Result(void) const;

      virtual void            Calculate(OpenBabel::OBMol*) = 0;
};



#endif
