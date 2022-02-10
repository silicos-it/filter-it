/**********************************************************************
parseCommandLine.cpp - filter-it
 
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



#include <parseCommandLine.h>
#include <cstdlib>
#include <unistd.h>



void
parseCommandLine(int argc, char* argv[], Options* o)
{
	static struct option longopts[] =
	{
        { "input",			required_argument,	NULL, 	11 },
		{ "pass",			optional_argument,	NULL,	12 },
		{ "fail",			optional_argument,	NULL,	13 },
		{ "filter",			required_argument,	NULL,	14 },
        { "tab",			optional_argument,	NULL,	15 },
        { "salts",			no_argument,		NULL,	16 },
        { "noLog",			no_argument,		NULL,	17 },
        { "rename",			no_argument,		NULL,	18 },
		{ "inputFormat",	required_argument,  NULL,	19 },
		{ "passFormat",		required_argument,  NULL,	20 },
		{ "failFormat", 	required_argument,  NULL,	21 },
		{ "help",			no_argument,		NULL,	22 },
		{ "version",		no_argument,		NULL,	23 },
		{ NULL,				0,					NULL,	0 }
	};
          
	// Set default values
	o->Salts(false);
	o->NoLog(false);
	o->Rename(false);
	
   	// Process command-line
	bool sethelp = false;
	bool setversion = false;
	int choice;
    std::string ff;
	opterr = 0;
	int longindex = 0;
	int opterr = 1;
	while ((choice = getopt_long(argc, argv, "vh", longopts, &longindex )) != -1)
	{
		switch(choice)
		{
			// --input
			case 11:
			if (optarg != NULL)
				(void) o->SetInputFilename(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--input=[file]': [file] specification is required.\n" << std::endl;
	            exit(1);
			}
           	break;
            

			// --pass
         	case 12:
			if (optarg != NULL)
				(void) o->SetPassFilename(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--pass=[file]': [file] specification is required.\n" << std::endl;
	            exit(1);
			}
           	break;

			
			// --fail
         	case 13:
			if (optarg != NULL)
				(void) o->SetFailFilename(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--fail=[file]': [file] specification is required.\n" << std::endl;
	            exit(1);
			}
        	break;
            

			// --filter
         	case 14:
			if (optarg != NULL)
				(void) o->SetFilterFilename(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--filter=[file]': [file] specification is required.\n" << std::endl;
	            exit(1);
			}
           	break;
            

			// --tab
        	case 15:
			if (optarg == NULL) (void) o->SetTabulateFilename("");
			else (void) o->SetTabulateFilename(optarg);
  			break;


			// --salts
         	case 16:
           	o->Salts(true);
           	break;
             
			
			// --noLog
         	case 17:
           	o->NoLog(true);
           	break;
            

			// --rename
         	case 18:
            o->Rename(true);
            break;


			// --inputFormat
			case 19:
			if (optarg != NULL)
				(void) o->SetInputFormat(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--inputFormat=[format]': [format] specification is required.\n" << std::endl;
	            exit(1);
			}
			break;


			// --passFormat
			case 20:
			if (optarg != NULL)
				(void) o->SetPassFormat(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--passFormat=[format]': [format] specification is required.\n" << std::endl;
	            exit(1);
			}
			break;


			// --failFormat
			case 21:
			if (optarg != NULL)
				(void) o->SetFailFormat(optarg);
			else
			{
	            version();
	            usage();
	            std::cerr << "ERROR:" << std::endl << std::endl;
				std::cerr << "  '--failFormat=[format]': [format] specification is required.\n" << std::endl;
	            exit(1);
			}
			break;
			
			
			// -h or --help
			case 22:
			case 'h':
			sethelp = true;
			break;


			// -v or --version
			case 23:
			case 'v':
			setversion = true;
			break;


			default:
            version();
            usage();
            std::cerr << "ERROR:" << std::endl << std::endl;
			std::cerr << "  Unknown command line option " << argv[optind - 1] << std::endl;
            exit(1);
			break;
		}
	}


	argc -= optind;
	argv += optind;
	
	if (sethelp)
	{
		version();
		usage();
		exit(0);
	}
	
	if (setversion)
	{
		version();
		exit(0);
	}
	
	if (!o->HasInputSet())
	{
    	version();
    	usage();
    	std::cerr << "ERROR:" << std::endl << std::endl;
		std::cerr << "  Required '--input=[file]' option has not been given.\n" << std::endl;
    	exit(1);
	}
	
	if (!o->HasFilterSet())
	{
    	version();
    	usage();
    	std::cerr << "ERROR:" << std::endl << std::endl;
		std::cerr << "  Required '--filter=[file]' option has not been given.\n" << std::endl;
    	exit(1);
	}
}



void
usage(void) 
{
	std::cerr << std::endl;
	std::cerr << "TASK: " << std::endl;
	std::cerr << std::endl;
	std::cerr << "  Filter-it is a tool to filter molecules from molecules." << std::endl;
	std::cerr << std::endl;
	std::cerr << "USAGE " << std::endl;
	std::cerr << std::endl;
	std::cerr << "  filter-it [options]" << std::endl;
	std::cerr << std::endl;
	std::cerr << "REQUIRED OPTIONS:" << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --input=[file]" << std::endl;
	std::cerr << "    Specifies the file containing the input molecules. The format of the" << std::endl;
	std::cerr << "    file is specified by the file extension or, with higher priority, by the" << std::endl;
	std::cerr << "    optional --inputFormat=[format] option. Gzipped files are also processed." << std::endl;
	std::cerr << "    The [file] specification is required." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --filter=[file]" << std::endl;
	std::cerr << "    Specifies the file that defines the filter criteria. The [file] specification" << std::endl;
	std::cerr << "    is required." << std::endl;
	std::cerr << std::endl;
	std::cerr << "OPTIONAL OPTIONS:" << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --inputFormat=[format]" << std::endl;
	std::cerr << "    Specifies the format of the input file. The [format] specification is required" << std::endl;
	std::cerr << "    when using this option." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --pass=[file]" << std::endl;
	std::cerr << "    Specifies the file to which the molecules are written that pass the" << std::endl;
	std::cerr << "    filtering. The format of the file is specified by the file extension or," << std::endl;
	std::cerr << "    with higher priority, by the --passFormat=[format] option. If the" << std::endl;
	std::cerr << "    extension is .gz, a compressed file will be written. The [file] specification" << std::endl;
	std::cerr << "    is required when using this option." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --passFormat=[format]" << std::endl;
	std::cerr << "    Specifies the format of the pass file. The <format> specification is required" << std::endl;
	std::cerr << "    when using this option." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --fail=[file]" << std::endl;
	std::cerr << "    Specifies the file to which the molecules are written that do not pass the" << std::endl;
	std::cerr << "    filter criteria. The format of the file is specified by the file extension" << std::endl;
	std::cerr << "    or, with higher priority, by the --failFormat=[format] option. If the" << std::endl;
	std::cerr << "    extension is .gz, a compressed file will be written. The [file] argument" << std::endl;
	std::cerr << "    is required when using this option." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --failFormat=[format]" << std::endl;
	std::cerr << "    Specifies the format of the fail file. The [format] specification is required" << std::endl;
	std::cerr << "    when using this option." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --tab or --tab=[file]" << std::endl;
	std::cerr << "    This flag directs the program to calculate all properties listed in" << std::endl;
	std::cerr << "    the filter definition file without applying any filtering step." << std::endl;
	std::cerr << "    The calculated parameters are written to [file]. The [file] argument is" << std::endl;
	std::cerr << "    optional; if not provided then all output is written to standard output." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --salts" << std::endl;
	std::cerr << "    This flag directs the program not to strip away all salt fragments from the" << std::endl;
	std::cerr << "    molecules before the filtering takes place. By specifying this option," << std::endl;
	std::cerr << "    this stripping is not performed and ensures that all salt counterions" << std::endl;
	std::cerr << "    are also taken into account during the filtering process." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --rename" << std::endl;
	std::cerr << "    This flag directs the program to rename the title of each molecules" << std::endl;
	std::cerr << "    into a increasing digit reflecting the sequence of the molecule in" << std::endl;
	std::cerr << "    the input file. Existing titles are overwritten." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --noLog" << std::endl;
	std::cerr << "    This flag specifies whether verbose logging should be switched off. When not" << std::endl;
	std::cerr << "    specified, then for each molecule a message is written to standard output" << std::endl;
	std::cerr << "    whether the molecule passes or fails the filter criteria. Is only of use when" << std::endl;
	std::cerr << "    the program is used in filtering mode (not in tabulate mode)." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --help | -h" << std::endl;
	std::cerr << "    Displays this help on standard error." << std::endl;
	std::cerr << std::endl;
	std::cerr << "  --version | -v" << std::endl;
	std::cerr << "    Displays the program version on standard error." << std::endl;
	std::cerr << std::endl;
}



void
version(void)
{
	std::cerr << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cerr << "Filter-it v";
	std::cerr << FILTERIT_VERSION << "." << FILTERIT_RELEASE << "." << FILTERIT_SUBRELEASE;
	std::cerr << " | ";
	std::cerr << __DATE__;
	std::cerr << " ";
	std::cerr << __TIME__;
	std::cerr << std::endl;
	std::cerr << std::endl;
	std::cerr << "  -> GCC:        " << __VERSION__ << std::endl;
	std::cerr << "  -> Open Babel: " << BABEL_VERSION << std::endl;
	std::cerr << std::endl;
	std::cerr << "Copyright 2012 by Silicos-it, a division of Imacosi BVBA" << std::endl;
	std::cerr << std::endl;
	std::cerr << "Filter-it is free software: you can redistribute it and/or modify" << std::endl;
	std::cerr << "it under the terms of the GNU Lesser General Public License as published" << std::endl;
	std::cerr << "by the Free Software Foundation, either version 3 of the License, or" << std::endl;
	std::cerr << "(at your option) any later version." << std::endl;
	std::cerr << std::endl;
	std::cerr << "Filter-it is distributed in the hope that it will be useful," << std::endl;
	std::cerr << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << std::endl;
	std::cerr << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << std::endl;
	std::cerr << "GNU Lesser General Public License for more details." << std::endl;
	std::cerr << std::endl;
	std::cerr << "You should have received a copy of the GNU Lesser General Public License" << std::endl;
	std::cerr << "along with Filter-it.  If not, see http://www.gnu.org/licenses/." << std::endl;
	std::cerr << std::endl;
	std::cerr << "Filter-it is linked against OpenBabel version 2." << std::endl;
	std::cerr << "OpenBabel is free software; you can redistribute it and/or modify" << std::endl;
	std::cerr << "it under the terms of the GNU General Public License as published by" << std::endl;
	std::cerr << "the Free Software Foundation version 2 of the License." << std::endl;
	std::cerr << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
	std::cerr << std::endl;
}
