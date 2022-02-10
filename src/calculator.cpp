/**********************************************************************
calculator.cpp - filter-it
 
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



#include <calculator.h>



Calculator::Calculator(void)
{
	// Clear all
   	_elementFilters.clear();
   	_titleFilters.clear();
   	_integerFilters.clear();
   	_realFilters.clear();
   	_fragmentFilters.clear();
   	_similarityFilters.clear();
   	_similarityStackFilters.clear();
   	_distanceFilters.clear();
   	_sdfTagFilters.clear();
   	_sdfTagValueFilters.clear();

   	// Element filters
   	_elementFilters.push_back(new FilterElementsExcluded());
   	_elementFilters.push_back(new FilterElementsOnly());
   
   	// Title filters
   	_titleFilters.push_back(new FilterTitle());
   
   	// Integer property filters
   	_integerFilters.push_back(new FilterAbsorption());
   	_integerFilters.push_back(new FilterAromaticRings());
   	_integerFilters.push_back(new FilterAtoms());
   	_integerFilters.push_back(new FilterAtomsInCore());
   	_integerFilters.push_back(new FilterAtomsInLargestAromaticRing());
   	_integerFilters.push_back(new FilterAtomsInLargestBridge());
   	_integerFilters.push_back(new FilterAtomsInLargestNonaromaticRing());
   	_integerFilters.push_back(new FilterAtomsInLargestRing());
   	_integerFilters.push_back(new FilterAtomsInLargestRingsystem());
   	_integerFilters.push_back(new FilterAtomsInLargestSidechain());
   	_integerFilters.push_back(new FilterAtomsInSmallestAromaticRing());
   	_integerFilters.push_back(new FilterAtomsInSmallestBridge());
   	_integerFilters.push_back(new FilterAtomsInSmallestNonaromaticRing());
   	_integerFilters.push_back(new FilterAtomsInSmallestRing());
   	_integerFilters.push_back(new FilterAtomsInSmallestRingsystem());
   	_integerFilters.push_back(new FilterAtomsInSmallestSidechain());
   	_integerFilters.push_back(new FilterBonds());
   	_integerFilters.push_back(new FilterBridges());
   	_integerFilters.push_back(new FilterCarbons());
   	_integerFilters.push_back(new FilterChiralCenters());
   	_integerFilters.push_back(new FilterCores());
   	_integerFilters.push_back(new FilterFormalCharges());
   	_integerFilters.push_back(new FilterHalides());
   	_integerFilters.push_back(new FilterHbondAcceptors());
   	_integerFilters.push_back(new FilterHbondDonors());
   	_integerFilters.push_back(new FilterHeteroAtoms());
   	_integerFilters.push_back(new FilterLipinskiAcceptors());
   	_integerFilters.push_back(new FilterLipinskiDonors());
   	_integerFilters.push_back(new FilterLipinskiViolations());
   	_integerFilters.push_back(new FilterNonaromaticRings());
   	_integerFilters.push_back(new FilterRigidBonds());
   	_integerFilters.push_back(new FilterRings());
   	_integerFilters.push_back(new FilterRingsInLargestRingsystem());
   	_integerFilters.push_back(new FilterRingsInSmallestRingsystem());
   	_integerFilters.push_back(new FilterRingsystems());
   	_integerFilters.push_back(new FilterRotatableBonds());
   	_integerFilters.push_back(new FilterSidechains());
   	_integerFilters.push_back(new FilterTotalFormalCharge());
   
   	// Real property filters
   	_realFilters.push_back(new FilterAdmetScore());
   	_realFilters.push_back(new FilterAndrewsEnergy());
   	_realFilters.push_back(new FilterAromaticRingFraction());
   	_realFilters.push_back(new FilterAromaticOverTotalRingFraction());
   	_realFilters.push_back(new FilterFlexibility());
   	_realFilters.push_back(new FilterBridgeFraction());
   	_realFilters.push_back(new FilterCoreFraction());
   	_realFilters.push_back(new FilterHeteroCarbonRatio());
   	_realFilters.push_back(new FilterHalideFraction());
   	_realFilters.push_back(new FilterLigandEfficiency());
   	_realFilters.push_back(new FilterLogp());
   	_realFilters.push_back(new FilterLogs());
   	_realFilters.push_back(new FilterMolwt());
   	_realFilters.push_back(new FilterNonaromaticOverTotalRingFraction());
   	_realFilters.push_back(new FilterNonaromaticRingFraction());
   	_realFilters.push_back(new FilterRingsystemFraction());
   	_realFilters.push_back(new FilterRingFraction());
   	_realFilters.push_back(new FilterSidechainFraction());
   	_realFilters.push_back(new FilterTpsa());
   
   	// Fragment filters
   	// -> are added at initialisation stage
   
   	// Similarity and similarity stack filters
   	// -> are added at initialisation stage

   	// Distance filters
   	_distanceFilters.push_back(new FilterDistance());

   	// Sdf-tag filters
   	// -> are added at initialisation stage
}



Calculator::~Calculator(void)
{
   	// Element filters
   	for (unsigned int i = 0; i < _elementFilters.size(); ++i) delete _elementFilters[i];

   	// Title filters
   	for (unsigned int i = 0; i < _titleFilters.size(); ++i) delete _titleFilters[i];
   
   	// Integer property filters
   	for (unsigned int i = 0; i < _integerFilters.size(); ++i) delete _integerFilters[i];
   
   	// Real property filters
   	for (unsigned int i = 0; i < _realFilters.size(); ++i) delete _realFilters[i];
   
   	// Fragment filters
   	for (unsigned int i = 0; i < _fragmentFilters.size(); ++i) delete _fragmentFilters[i];

   	// Similarity filters
   	for (unsigned int i = 0; i < _similarityFilters.size(); ++i) delete _similarityFilters[i];
   
   	// Similarity stack filters
   	for (unsigned int i = 0; i < _similarityStackFilters.size(); ++i) delete _similarityStackFilters[i];
   
   	// SdfTag filters
   	for (unsigned int i = 0; i < _sdfTagFilters.size(); ++i) delete _sdfTagFilters[i];
   
   	// SdfTagValue filters
   	for (unsigned int i = 0; i < _sdfTagValueFilters.size(); ++i) delete _sdfTagValueFilters[i];

   	// Distance filters
   	for (unsigned int i = 0; i < _distanceFilters.size(); ++i) delete _distanceFilters[i];
}



Calculator::Calculator(const Calculator& f)
{
}



Calculator&
Calculator::operator=(const Calculator& f)
{
   	return *this;
}



void
Calculator::ParseFilterFile(const std::string& filename, Options* o)
{
	std::cerr << "PARSING FILTER FILE \"" << filename << "\":" << std::endl;

   	// Variables
   	unsigned int linecount(0);
   	std::string parameter;
   	std::string line;
   	const std::string whiteSpace("\n\t \r");
   	unsigned int b;
   	unsigned int e;
   
   	// Open file
   	std::ifstream pfs(filename.c_str());
   	if (!pfs)
   	{
      	std::cerr << "ERROR: Could not open filter file ";
      	std::cerr << filename;
      	std::cerr << std::endl;
      	exit(1);
   	}
   
   	// Check correctness of keywords
   	while (pfs.good())
   	{
      	(void) getline(pfs, line);
      	++linecount;
      
      	// Reset
      	line.erase(0, line.find_first_not_of(whiteSpace, 0));
      	parameter.clear();
      
      	// Get the parameter out of the string
      	parameter = line.substr(0, line.find_first_of(whiteSpace, 0));
      	for_each(parameter.begin(), parameter.end(), toupper);
      
      	// Handle according value of parameter
      	if ((parameter.empty()) || (parameter.substr(0,1) == "#") || (parameter.substr(0,2) == "//"))
      	{
         	goto endOfLoop1;
      	}
      
      	// INCLUDE
      	if (parameter == "INCLUDE")
      	{
         	b = line.find_first_not_of(whiteSpace, 7);
         	e = line.find_first_of(whiteSpace, b);
         	std::string fn(line.substr(b, e - b));
         	(void) this->ParseFilterFile(fn, o);
         	goto endOfLoop1;
      	}
      
      	// ELEMENT FILTERS
      	for (unsigned int i = 0; i < _elementFilters.size(); ++i)
      	{
         	_ef = dynamic_cast<FilterElements*>(_elementFilters[i]);
         	if (parameter == _ef->Keyword())
         	{
            	if (_ef->IsInitialised())
            	{
               		std::cerr << "  -> WARNING: line " << linecount << " of file \"";
               		std::cerr << filename << "\": duplicate " << parameter;
               		std::cerr << " keyword encountered: skipping this one.";
               		std::cerr << std::endl;
            	}
            	else _ef->Initialise(line, o->HasTabulateSet());
            	goto endOfLoop1;
         	}
      	}

      	// TITLE FILTERS
      	for (unsigned int i = 0; i < _titleFilters.size(); ++i)
      	{
         	_tf = _titleFilters[i];
         	if (parameter == _tf->Keyword())
         	{
            	_tf->Initialise(line, o->HasTabulateSet());
            	goto endOfLoop1;
         	}
      	}
      
      	// INTEGER PROPERTY FILTERS
      	for (unsigned int i = 0; i < _integerFilters.size(); ++i)
      	{
         	_if = dynamic_cast<FilterIntegerProperty*>(_integerFilters[i]);
         	if (parameter == _if->Keyword())
         	{
            	if (_if->IsInitialised())
            	{
               		std::cerr << "  -> WARNING: line " << linecount << " of file \"";
               		std::cerr << filename << "\": duplicate " << parameter;
               		std::cerr << " keyword encountered: skipping this one.";
               		std::cerr << std::endl;
            	}
            	else _if->Initialise(line, o->HasTabulateSet());
            	goto endOfLoop1;
         	}
      	}

      	// REAL PROPERTY FILTERS
      	for (unsigned int i = 0; i < _realFilters.size(); ++i)
      	{
         	_rf = dynamic_cast<FilterRealProperty*>(_realFilters[i]);
         	if (parameter == _rf->Keyword())
         	{
            	if (_rf->IsInitialised())
            	{
               		std::cerr << "  -> WARNING: line " << linecount << " of file \"";
               		std::cerr << filename << "\": duplicate " << parameter;
               		std::cerr << " keyword encountered: skipping this one.";
               		std::cerr << std::endl;
            	}
            	else _rf->Initialise(line, o->HasTabulateSet());
            	goto endOfLoop1;
         	}
      	}
      
      	// FRAGMENT FILTERS
      	if (parameter == "FRAGMENT")
      	{
         	_fragmentFilters.push_back(new FilterFragment());
         	_ff = _fragmentFilters[_fragmentFilters.size() - 1];
         	_ff->Initialise(line, o->HasTabulateSet());
         	goto endOfLoop1;
      	}

      	// SIMILARITY FILTERS
      	if (parameter == "SIMILARITY")
      	{
         	_similarityFilters.push_back(new FilterSimilarity());
        	_sf = _similarityFilters[_similarityFilters.size() - 1];
         	_sf->Initialise(line, o->HasTabulateSet());
         	goto endOfLoop1;
      	}

      	// SIMILARITY STACK FILTERS
      	if (parameter == "SIMILARITY_STACK")
      	{
         	FilterSimilarityStack* f = new FilterSimilarityStack();
         	if (f->Initialise(line, o->HasTabulateSet()))
         	{
            	_similarityStackFilters.push_back(f);
         	}
         	else
         	{
            	delete f;
         	}
         	goto endOfLoop1;
      	}

		// SDF-TAG FILTERS
      	if (parameter == "SDFTAG")
      	{
			OpenBabel::OBConversion* conv;
    	    conv->SetInFormat(conv->FormatFromExt(o->GetInputFilename().c_str()));
         	if (!std::strncmp(conv->GetInFormat()->GetID(), "sdf", 3))
         	{
            	_sdfTagFilters.push_back(new FilterSdfTag());
            	_shtf = _sdfTagFilters[_sdfTagFilters.size() - 1];
            	_shtf->Initialise(line, o->HasTabulateSet());
         	}
         	else
         	{
            	std::cerr << "  -> WARNING: line " << linecount << " of file \"";
            	std::cerr << filename << "\": " << parameter;
            	std::cerr << " keyword encountered, but input file is not an sd-file:";
            	std::cerr << " skipping this line.";
            	std::cerr << std::endl;
         	}
         	goto endOfLoop1;
      	}

      	// SDF-TAG VALUE FILTERS
      	if (parameter == "SDFTAG_VALUE")
      	{
			OpenBabel::OBConversion* conv;
  	    	conv->SetInFormat(conv->FormatFromExt(o->GetInputFilename().c_str()));
       		if (!std::strncmp(conv->GetInFormat()->GetID(), "sdf", 3))
         	{
            	_sdfTagValueFilters.push_back(new FilterSdfTagValue());
            	_stvf = _sdfTagValueFilters[_sdfTagValueFilters.size() - 1];
            	_stvf->Initialise(line, o->HasTabulateSet());
         	}
         	else
         	{
            	std::cerr << "  -> WARNING: line " << linecount << " of file \"";
            	std::cerr << filename << "\": " << parameter;
            	std::cerr << " keyword encountered, but input file is not an sd-file:";
            	std::cerr << " skipping this line.";
            	std::cerr << std::endl;
         	}
         	goto endOfLoop1;
      	}

      	// DISTANCE FILTERS
      	if ((parameter == "DISTANCE") || (parameter == "PATTERN"))
      	{
         	_distanceFilters[0]->Initialise(line, o->HasTabulateSet());
         	goto endOfLoop1;
      	}

      	// MISMATCH
      	{
         	std::cerr << "ERROR: Unrecognized keyword when parsing filter file: ";
         	std::cerr << parameter << std::endl;
         	exit(1);
      	}
      	// END OF LOOP
      	endOfLoop1:
         	continue;
	}
   
   	// Update the distance filter
   	if (_distanceFilters[0]->IsInitialised())
   	{
      	_distanceFilters[0]->PostProcess();
   	}
   
   	// Check multiple occurences of fragment filters
   	std::set<std::string> names;
   	names.clear();
   	for (unsigned int i = 0; i < _fragmentFilters.size(); ++i)
   	{
      	if (names.count(_fragmentFilters[i]->Name()))
      	{
         	std::cerr << "ERROR: Multiple occurences of filter ";
         	std::cerr << _fragmentFilters[i]->Keyword();
         	std::cerr << " with name \"";
         	std::cerr << _fragmentFilters[i]->Name();
         	std::cerr << "\"" << std::endl;
         	exit(1);
      	}
      	else
      	{
         	names.insert(_fragmentFilters[i]->Name());
      	}
   	}
   
   	// Check multiple occurences of similarity filters
   	names.clear();
   	for (unsigned int i = 0; i < _similarityFilters.size(); ++i)
   	{
      	if (names.count(_similarityFilters[i]->Name()))
      	{
         	std::cerr << "ERROR: Multiple occurences of filter ";
         	std::cerr << _similarityFilters[i]->Keyword();
         	std::cerr << " with name \"";
         	std::cerr << _similarityFilters[i]->Name();
         	std::cerr << "\"" << std::endl;
         	exit(1);
      	}
      	else
      	{
         	names.insert(_similarityFilters[i]->Name());
      	}
   	}
   
   	// Check multiple occurences of similarity stack filters
   	names.clear();
   	for (unsigned int i = 0; i < _similarityStackFilters.size(); ++i)
   	{
      	if (names.count(_similarityStackFilters[i]->Name()))
      	{
         	std::cerr << "ERROR: Multiple occurences of filter ";
         	std::cerr << _similarityStackFilters[i]->Keyword();
         	std::cerr << " with name \"";
         	std::cerr << _similarityStackFilters[i]->Name();
         	std::cerr << "\"" << std::endl;
         	exit(1);
      	}
      	else
      	{
         	names.insert(_similarityStackFilters[i]->Name());
      	}
   	}
}



Counter
Calculator::Calculate(Options* o)
{
	Counter counter;

    // INPUT FILE
	std::ifstream* ifs = new std::ifstream();
	ifs->open(o->GetInputFilename().c_str());	
	OpenBabel::OBConversion* iconv = new OpenBabel::OBConversion();
	iconv->SetInStream(ifs);
	if (o->GetInputFormat().empty())
	{
		if (!iconv->FormatFromExt(o->GetInputFilename().c_str()))
		{
			version();
	       	usage();
	       	std::cerr << "ERROR: Could not deduce the file format from the '--input=<file>' option." << std::endl;
	       	std::cerr << "       Use the '--inputFormat=<format>' option instead." << std::endl;
			std::cerr << std::endl;
	       	exit(1);
		}
		else
		{
			iconv->SetInFormat(iconv->FormatFromExt(o->GetInputFilename().c_str()));
		}
	}
	else
	{
		if (!iconv->SetInFormat(o->GetInputFormat().c_str()))
		{
			version();
	       	usage();
	       	std::cerr << "ERROR: Could not deduce the format from the '--inputFormat=<format>' option." << std::endl;
			std::cerr << std::endl;
	       	exit(1);
		}
	}
	o->SetInputFormat(iconv->GetInFormat()->GetID());
    if (!iconv->GetInStream()->good())
    {
       version();
       usage();
       std::cerr << "ERROR:" << std::endl << std::endl;
       std::cerr << " cannot open the file as specified by the '--input=<file>' option.\n" << std::endl;
       exit(1);
    }
    iconv->AddOption("d", OpenBabel::OBConversion::GENOPTIONS);	// Delete hydrogens


   	// PASS FILE
	std::ofstream* pfs = new std::ofstream();
	OpenBabel::OBConversion* pconv = new OpenBabel::OBConversion();
    if (o->HasPassSet() && !o->HasTabulateSet())
	{
		if (!(o->GetPassFilename().empty()))
		{
			pfs->open(o->GetPassFilename().c_str());
			pconv->SetOutStream(pfs);
			
			if (o->GetPassFormat().empty())
			{
				// Deduce format from the filename extension
				if (!pconv->FormatFromExt(o->GetPassFilename().c_str()))
				{
					version();
			       	usage();
			       	std::cerr << "ERROR: Could not deduce file format from the '--pass=<file>' option." << std::endl;
			       	std::cerr << "       Use the '--passFormat=<format>' option instead." << std::endl;
					std::cerr << std::endl;
			       	exit(1);
				}
				else
				{
					pconv->SetOutFormat(pconv->FormatFromExt(o->GetPassFilename().c_str()));
				}
			}
			else
			{
				// Deduce format from --passFormat option
				if (!pconv->SetOutFormat(o->GetPassFormat().c_str()))
				{
					version();
			       	usage();
			       	std::cerr << "ERROR: Could not deduce the format from the '--passFormat=<format>' option." << std::endl;
					std::cerr << std::endl;
			       	exit(1);
				}
			}
		}

		// Check quality of pass file
		o->SetPassFormat(pconv->GetOutFormat()->GetID());
	    if (!pconv->GetOutStream()->good())
	    {
	   		version();
	   		usage();
	   		std::cerr << "ERROR: Cannot open the file as specified by the '--pass=<file>' option.\n" << std::endl;
	       	exit(1);
		}
	}


   	// FAIL FILE
	std::ofstream* ffs = new std::ofstream();
	OpenBabel::OBConversion* fconv = new OpenBabel::OBConversion();
    if (o->HasFailSet() && !o->HasTabulateSet())
	{
		if (!(o->GetFailFilename().empty()))
		{
			ffs->open(o->GetFailFilename().c_str());
			fconv->SetOutStream(ffs);
			
			if (o->GetFailFormat().empty())
			{
				// Deduce format from the filename extension
				if (!fconv->FormatFromExt(o->GetFailFilename().c_str()))
				{
					version();
			       	usage();
			       	std::cerr << "ERROR: Could not deduce the format from the '--fail=<file>' option." << std::endl;
			       	std::cerr << "       Use the '--failFormat=<format>' option instead." << std::endl;
					std::cerr << std::endl;
			       	exit(1);
				}
				else
				{
					fconv->SetOutFormat(fconv->FormatFromExt(o->GetFailFilename().c_str()));
				}
			}
			else
			{
				// Deduce format from --failFormat option
				if (!fconv->SetOutFormat(o->GetFailFormat().c_str()))
				{
					version();
			       	usage();
			       	std::cerr << "ERROR: Could not deduce the format from the '--failFormat=<format>' option." << std::endl;
					std::cerr << std::endl;
			       	exit(1);
				}
			}
		}

		// Check quality of fail file
		o->SetFailFormat(fconv->GetOutFormat()->GetID());
	    if (!fconv->GetOutStream()->good())
	    {
	   		version();
	   		usage();
	   		std::cerr << "ERROR: Cannot open the file as specified by the '--fail=<file>' option.\n" << std::endl;
	       	exit(1);
		}
	}


   	// TABULATE FILE
	std::ostream* tfs = &std::cout;
	std::ofstream tfout;
	if (o->HasTabulateSet() && !o->GetTabulateFilename().empty())
	{
		tfout.open(o->GetTabulateFilename().c_str());
		tfs = &tfout;
	}
   	

	// PPRINT OPTIONS
	std::cerr << o->Print();
   	std::cerr << "## STARTING CALCULATIONS ##" << std::endl << std::endl;

   	// Molecule and mol2can converter
   	OpenBabel::OBMol* mol = new OpenBabel::OBMol();
   	std::string title;
   	OpenBabel::OBConversion mol2can;
   	mol2can.SetOutFormat("can");  // Canonical smiles
   	mol2can.AddOption("n", OpenBabel::OBConversion::OUTOPTIONS); // No title after smiles
   
   	// Print title line if in --tab mode
   	if (o->HasTabulateSet())
   	{
      	// Print title line
      	*tfs << "NAME\t";

      	for (unsigned int i = 0; i < _elementFilters.size(); ++i)
      	{
         	_ef = dynamic_cast<FilterElements*>(_elementFilters[i]);
         	if (_ef->IsInitialised()) *tfs << _ef->Keyword() << "\t";
      	}
      
      	for (unsigned int i = 0; i < _titleFilters.size(); ++i)
      	{
         	_tf = _titleFilters[i];
         	if (_tf->IsInitialised()) *tfs << _tf->Keyword() << "\t";
      	}
      
      	for (unsigned int i = 0; i < _integerFilters.size(); ++i)
      	{
         	_if = dynamic_cast<FilterIntegerProperty*>(_integerFilters[i]);
         	if (_if->IsInitialised()) *tfs << _if->Keyword() << "\t";
      	}

      	for (unsigned int i = 0; i < _realFilters.size(); ++i)
      	{
         	_rf = dynamic_cast<FilterRealProperty*>(_realFilters[i]);
         	if (_rf->IsInitialised()) *tfs << _rf->Keyword() << "\t";
      	}

      	for (unsigned int i = 0; i < _fragmentFilters.size(); ++i)
      	{
         	_ff = _fragmentFilters[i];
         	if (_ff->IsInitialised()) *tfs << _ff->Name() << "\t";
      	}

      	for (unsigned int i = 0; i < _similarityFilters.size(); ++i)
      	{
         	_sf = _similarityFilters[i];
         	if (_sf->IsInitialised()) *tfs << _sf->Name() << "\t";
      	}
      
      	for (unsigned int i = 0; i < _similarityStackFilters.size(); ++i)
      	{
         	_ssf = _similarityStackFilters[i];
         	if (_ssf->IsInitialised()) *tfs << _ssf->Name() << "\t";
      	}
      
      	for (unsigned int i = 0; i < _sdfTagFilters.size(); ++i)
      	{
         	_shtf = _sdfTagFilters[i];
         	if (_shtf->IsInitialised()) *tfs << "<" << _shtf->TagName() << ">\t";
      	}

      	for (unsigned int i = 0; i < _sdfTagValueFilters.size(); ++i)
      	{
         	_stvf = _sdfTagValueFilters[i];
         	if (_stvf->IsInitialised()) *tfs << "<" << _stvf->TagName() << ">\t";
      	}

      	for (unsigned int i = 0; i < _distanceFilters.size(); ++i)
      	{
         	_df = _distanceFilters[i];
         	if (_df->IsInitialised()) *tfs << _df->Keyword() << "\t";
      	}

      	*tfs << std::endl;
   	}
      
   	// Process molecules 
   	std::ostringstream os;
   	std::string smiles;
   	std::string line;
   	double min;
   	double max;
   	bool minLimit;
   	bool maxLimit;
   	unsigned int molCount(0);
   	while (iconv->Read(mol))
   	{
      	// Increase counter
      	++molCount;
      
      	// Find rings and set chirality
     	mol->FindRingAtomsAndBonds();
         
      	// Strip salts
		if (!o->Salts())
		{
			std::string oldTitle(mol->GetTitle());
			std::vector<OpenBabel::OBMol> mols = mol->Separate();
			if (mols.size() > 1)
			{
 				unsigned int maxindex = 0;
				unsigned int maxsize = mols[maxindex].NumAtoms();
				for (unsigned int i(1); i < mols.size(); ++i)
				{
					if (maxsize < mols[i].NumAtoms())
					{
						maxsize = mols[i].NumAtoms();
						maxindex = i;
					}
				}
				*mol = mols[maxindex];
				mol->SetTitle(oldTitle);
 			}
   		}

      	// Molecule name
      	if (o->Rename())
      	{
         	os.str("");
         	os << molCount;
         	mol->SetTitle(os.str().c_str());
      	}
      	else
      	{
         	title = mol->GetTitle();
         	if (title.empty()) mol->SetTitle(mol2can.WriteString(mol, true).c_str());
      	}
      	if (o->HasTabulateSet()) *tfs << mol->GetTitle() << "\t";

      	// Element filters
      	for (unsigned int i = 0; i < _elementFilters.size(); ++i)
      	{
         	_ef = dynamic_cast<FilterElements*>(_elementFilters[i]);
         	if (_ef->IsInitialised())
         	{
            	_ef->Calculate(mol);
            
            	if (o->HasTabulateSet())
					*tfs << _ef->Result() << "\t";
            	else if (_ef->HasFailed())
            	{
               		if (o->Log()) std::cout << _ef->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}

      	// Title filters
      	for (unsigned int i = 0; i < _titleFilters.size(); ++i)
      	{
         	_tf = _titleFilters[i];
         	if (_tf->IsInitialised())
         	{
            	_tf->Calculate(mol);
            
            	if (o->HasTabulateSet()) *tfs << _tf->Result() << "\t";
            	else if (_tf->HasFailed())
            	{
               		if (o->Log()) std::cout << _tf->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}

      	// Integer property filters
      	for (unsigned int i = 0; i < _integerFilters.size(); ++i)
      	{
         	_if = dynamic_cast<FilterIntegerProperty*>(_integerFilters[i]);
         	if (_if->IsInitialised())
         	{
            	_if->Calculate(mol);
            
            	if (o->HasTabulateSet()) *tfs << _if->Result() << "\t";
            	else if (_if->HasFailed())
            	{
               		if (o->Log()) std::cout << _if->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}

      	// Real property filters
      	for (unsigned int i = 0; i < _realFilters.size(); ++i)
      	{
         	_rf = dynamic_cast<FilterRealProperty*>(_realFilters[i]);
         	if (_rf->IsInitialised())
         	{
            	_rf->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		(*tfs).precision(3);
               		*tfs << std::fixed << _rf->Result() << "\t";
            	}
            	else if (_rf->HasFailed())
            	{
               		if (o->Log()) std::cout << _rf->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}
      
      	// Fragment filters
      	for (unsigned int i = 0; i < _fragmentFilters.size(); ++i)
     	{
         	_ff = _fragmentFilters[i];
         	if (_ff->IsInitialised())
         	{
            	_ff->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		*tfs << _ff->Result() << "\t";
            	}
            	else if (_ff->HasFailed())
           		{
               		if (o->Log()) std::cout << _ff->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}
         
      	// Similarity filters
      	for (unsigned int i = 0; i < _similarityFilters.size(); ++i)
      	{
         	_sf = _similarityFilters[i];
         	if (_sf->IsInitialised())
         	{
           		_sf->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		(*tfs).precision(3);
               		*tfs << std::fixed << _sf->Result() << "\t";
            	}
            	else if (_sf->HasFailed())
            	{
               		if (o->Log()) std::cout << _sf->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}
   
      	// Similarity stack filters
      	for (unsigned int i = 0; i < _similarityStackFilters.size(); ++i)
      	{
         	_ssf = _similarityStackFilters[i];
         	if (_ssf->IsInitialised())
         	{
            	_ssf->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		(*tfs).precision(3);
               		*tfs << std::fixed << _ssf->Result() << "\t";
            	}
            	else if (_ssf->HasFailed())
            	{
               		if (o->Log()) std::cout << _ssf->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}
      	if (!_similarityStackFilters.empty())
      	{
         	// Get info from last item on similarity stack
         	_ssf = _similarityStackFilters[_similarityStackFilters.size() - 1];
         	minLimit = _ssf->GetMinLimit();
         	maxLimit = _ssf->GetMaxLimit();
         	min = _ssf->GetMin();
         	max = _ssf->GetMax();

         	// Add molecule to stack
         	_similarityStackFilters.push_back(new FilterSimilarityStack());
         	_ssf = _similarityStackFilters[_similarityStackFilters.size() - 1];
         	smiles = mol2can.WriteString(mol, true);
         	os.str("");
			std::string cleanTitle = mol->GetTitle(); // Title with spaces replaced by '_'
			std::replace(cleanTitle.begin(), cleanTitle.end(), ' ', '_');
         	os << _ssf->Keyword() << " " << cleanTitle << " " << smiles + " ";
         	if (!minLimit) os << "* "; else os << min << " ";
         	if (!maxLimit) os << "* "; else os << max << " ";
         	os << std::endl;
         	line = os.str();
         	_ssf->Initialise(line, o->HasTabulateSet());
         	std::cerr << mol->GetTitle() << " >> added to " << _ssf->Keyword() << std::endl;
         	for (unsigned int i = 0; i < _similarityStackFilters.size() - 1; ++i)
         	{
            	_ssf = _similarityStackFilters[i];
            	std::cerr << "\t-> Similarity to " << _ssf->Name() << ": ";
           		std::cerr.precision(3);
            	std::cerr << std::fixed << _ssf->Result() << std::endl;
         	}
      	}
      
      	// SdfTag filters
      	for (unsigned int i = 0; i < _sdfTagFilters.size(); ++i)
      	{
         	_shtf = _sdfTagFilters[i];
         	if (_shtf->IsInitialised())
         	{
            	_shtf->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		*tfs << _shtf->Result() << "\t";
            	}
            	else if (_shtf->HasFailed())
            	{
               		if (o->Log()) std::cout << _shtf->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}
         
      	// SdfTagValue filters
      	for (unsigned int i = 0; i < _sdfTagValueFilters.size(); ++i)
      	{
         	_stvf = _sdfTagValueFilters[i];
         	if (_stvf->IsInitialised())
         	{
            	_stvf->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		*tfs << _stvf->ResultAsString() << "\t";
            	}
            	else if (_stvf->HasFailed())
            	{
               		if (o->Log()) std::cout << _stvf->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}
       
      	// Distance filters
      	for (unsigned int i = 0; i < _distanceFilters.size(); ++i)
      	{
         	_df = _distanceFilters[i];
         	if (_df->IsInitialised())
         	{
            	_df->Calculate(mol);
            
            	if (o->HasTabulateSet())
            	{
               		*tfs << _df->Result() << "\t";
            	}
            	else if (_df->HasFailed())
            	{
               		if (o->Log()) std::cout << _df->FailMessage(mol) << std::endl;
               		if (!o->GetFailFilename().empty()) fconv->Write(mol);
               		goto endOfLoop2;
            	}
         	}
      	}

      	counter.MolHasPassed();
      	if (o->HasTabulateSet())
      	{
         	*tfs << std::endl;
         	mol->Clear();
         	continue;
      	}
      	else 
      	{
         	if (o->Log())
        	{
            	std::cout << mol->GetTitle() << " >> passed" << std::endl;
         	}
			if (!o->GetPassFilename().empty()) pconv->Write(mol);
         	mol->Clear();
         	continue;
     	}
         
      	// End of loop 2
      	endOfLoop2:
         	counter.MolHasFailed();
         	mol->Clear();
         	continue;
   	}
	
	if (!_similarityStackFilters.empty())
	{
		std::cerr << std::endl;
		std::cerr << "SIMILARITY STACK CONTENTS:" << std::endl << std::endl;
	}
  	for (unsigned int i = 0; i < _similarityStackFilters.size(); ++i)
  	{
		_ssf = _similarityStackFilters[i];
		std::cerr << _ssf->Smiles() << " " << _ssf->Name() << std::endl;
	}
	return counter;
}
