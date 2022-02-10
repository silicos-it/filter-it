/**********************************************************************
calculator.h - filter-it
 
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



#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__



// Library includes
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <string>

// Open Babel includes
#include <openbabel/mol.h>

// filter-it includes
#include <options.h>
#include <counter.h>
#include <parseCommandLine.h>

// Sdf-tag filters
#include <filters/filterSdfTag.h>
#include <filters/filterSdfTagValue.h>

// Element filters
#include <filters/filterElements.h>
#include <filters/filterElementsOnly.h>
#include <filters/filterElementsExcluded.h>

// Title filters
#include <filters/filterTitle.h>

// Integer property filters
#include <filters/filterIntegerProperty.h>
#include <filters/filterAbsorption.h>
#include <filters/filterAromaticRings.h>
#include <filters/filterAtoms.h>
#include <filters/filterAtomsInCore.h>
#include <filters/filterAtomsInLargestAromaticRing.h>
#include <filters/filterAtomsInLargestBridge.h>
#include <filters/filterAtomsInLargestNonaromaticRing.h>
#include <filters/filterAtomsInLargestRing.h>
#include <filters/filterAtomsInLargestRingsystem.h>
#include <filters/filterAtomsInLargestSidechain.h>
#include <filters/filterAtomsInSmallestAromaticRing.h>
#include <filters/filterAtomsInSmallestBridge.h>
#include <filters/filterAtomsInSmallestNonaromaticRing.h>
#include <filters/filterAtomsInSmallestRing.h>
#include <filters/filterAtomsInSmallestRingsystem.h>
#include <filters/filterAtomsInSmallestSidechain.h>
#include <filters/filterBonds.h>
#include <filters/filterBridges.h>
#include <filters/filterCarbons.h>
#include <filters/filterChiralCenters.h>
#include <filters/filterCores.h>
#include <filters/filterFormalCharges.h>
#include <filters/filterHalides.h>
#include <filters/filterHbondAcceptors.h>
#include <filters/filterHbondDonors.h>
#include <filters/filterHeteroAtoms.h>
#include <filters/filterLipinskiAcceptors.h>
#include <filters/filterLipinskiDonors.h>
#include <filters/filterLipinskiViolations.h>
#include <filters/filterNonaromaticRings.h>
#include <filters/filterRigidBonds.h>
#include <filters/filterRings.h>
#include <filters/filterRingsInLargestRingsystem.h>
#include <filters/filterRingsInSmallestRingsystem.h>
#include <filters/filterRingsystems.h>
#include <filters/filterRotatableBonds.h>
#include <filters/filterSidechains.h>
#include <filters/filterTotalFormalCharge.h>

// Real property filters
#include <filters/filterRealProperty.h>
#include <filters/filterAdmetScore.h>
#include <filters/filterAndrewsEnergy.h>
#include <filters/filterAromaticRingFraction.h>
#include <filters/filterAromaticOverTotalRingFraction.h>
#include <filters/filterBridgeFraction.h>
#include <filters/filterCoreFraction.h>
#include <filters/filterFlexibility.h>
#include <filters/filterHeteroCarbonRatio.h>
#include <filters/filterHalideFraction.h>
#include <filters/filterLigandEfficiency.h>
#include <filters/filterLogp.h>
#include <filters/filterLogs.h>
#include <filters/filterMolwt.h>
#include <filters/filterNonaromaticOverTotalRingFraction.h>
#include <filters/filterNonaromaticRingFraction.h>
#include <filters/filterRingFraction.h>
#include <filters/filterRingsystemFraction.h>
#include <filters/filterSidechainFraction.h>
#include <filters/filterTpsa.h>

// Distance filters
#include <filters/filterDistance.h>

// Fragment filters
#include <filters/filterFragment.h>

// Similarity filters
#include <filters/filterSimilarity.h>
#include <filters/filterSimilarityStack.h>



class Calculator
{
   protected:
      // Filter sets
      std::vector<FilterSdfTag*>             _sdfTagFilters;
      std::vector<FilterSdfTagValue*>        _sdfTagValueFilters;
      std::vector<FilterElements*>           _elementFilters;
      std::vector<FilterTitle*>              _titleFilters;
      std::vector<FilterIntegerProperty*>    _integerFilters;
      std::vector<FilterRealProperty*>       _realFilters;
      std::vector<FilterDistance*>           _distanceFilters;
      std::vector<FilterFragment*>           _fragmentFilters;
      std::vector<FilterSimilarity*>         _similarityFilters;
      std::vector<FilterSimilarityStack*>    _similarityStackFilters;
      
      // Filter pointers
      FilterSdfTag*                          _shtf;
      FilterSdfTagValue*                     _stvf;
      FilterElements*                        _ef;
      FilterTitle*                           _tf;
      FilterIntegerProperty*                 _if;
      FilterRealProperty*                    _rf;
      FilterDistance*                        _df;
      FilterFragment*                        _ff;
      FilterSimilarity*                      _sf;
      FilterSimilarityStack*                 _ssf;
   
   public:
      
      Calculator(void);
      virtual ~Calculator(void);
      Calculator(const Calculator&);
      Calculator& operator=(const Calculator&);
  
      virtual void      ParseFilterFile(const std::string&, Options*);
      virtual Counter   Calculate(Options*);
};




#endif
