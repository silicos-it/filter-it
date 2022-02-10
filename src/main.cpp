/**********************************************************************
main.cpp - filter-it
 
Copyright 2012-213 by Silicos-it, a division of Imacosi BVBA
 
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



#include <options.h>
#include <parseCommandLine.h>
#include <calculator.h>
#include <counter.h>



int main (int argc, char* argv[])
{
	// Parse command line
   	Options* uo = new Options();
  	parseCommandLine(argc, argv, uo);
   	version();
  
   	// Initiate the filter cards
   	Calculator filter;
   	std::cerr << "## INITIATING FILTER PARAMETERS ##" << std::endl << std::endl;
  	filter.ParseFilterFile(uo->GetFilterFilename(), uo);

   	// Filter
   	Counter counts = filter.Calculate(uo);
   	std::cerr << std::endl << counts.Results();
   	std::cerr << "## FINISHED CALCULATIONS ##" << std::endl << std::endl;

   	// Return
   	delete uo;
   	uo = NULL;
   	return 0;
}
