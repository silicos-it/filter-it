#!/usr/bin/env python


import argparse



################################################################################
#
# Arguments parsing
#
################################################################################

def ParseArguments():
	parser = argparse.ArgumentParser(description="Filter-it")

	# Required arguments
	flags = parser.add_argument_group("required arguments")

	flags.add_argument("--input",
	type=str,
	required=True,
	help="""
	Specifies the name of the file containing the input molecules. The input file 
	contains one or more molecules specified as a set of connection tables according 
	specific molecular formats. The format of these connection tables can be SDF or SMILES.
	The format is specified by the input filename extension ('.sd', '.sdf', '.smi', or 
	'.smiles'). Compressed files are also allowed ('.gz').
	""")

	flags.add_argument("--filter",
	type=str,
	required=True,
	help="""
	This option specifies a the name of the filter file that describes the filter criteria 
	to apply to the input molecules. A detailed overview of the specific format of this 
	file and a list of all parameters is provided in the manual.
	""")

	# Optional arguments
	flags = parser.add_argument_group("optional arguments")

	flags.add_argument("--pass",
	type=str,
	required=False,
	help="""
	Specifies the name of the file to which the molecules are written that have 
	successfully passed all the filter criteria. The format of the file is 
	specified by the file extension ('.sd', '.sdf', '.smi', or 
	'.smiles'). If the file extension ends with '.gz', a compressed
	file will be written. In case a tabulate run mode has been requested 
	(with the --tab option), then this argument is ignored by the program.
	""")

	flags.add_argument("--fail",
	type=str,
	required=False,
	help="""
	Specifies the file to which molecules are written that fail for at least one 
	of the filter criteria. The format of the file is specified by the file extension 
	('.sd', '.sdf', '.smi', or '.smiles'). If the file extension ends with '.gz', 
	a compressed file will be written. In case a tabulate run mode has been 
	requested (with the --tab option), then this argument is ignored by the program.
	""")

	flags.add_argument("--tab",
	action='store_const',
	required=False,
	const=True,
	default=False,
	help="""
	This flag directs the program to calculate all properties listed in the 
	filter definition file without applying any filtering step. The calculated 
	parameters are written to standard output. In case the--tab option has been 
	specified, the molecules are not written to the --pass and --fail files. 
	Property tables as requested with --tab are calculated for the majority of 
	properties, with the exception of a few. The properties that cannot be 
	generated during a tabulate run are indicated in the manual.
	""")

	flags.add_argument("--salts",
	action='store_const',
	required=False,
	const=True,
	default=False,
	help="""
	Before any property calculation and filtering step takes place in filter-it, 
	each molecule is cleaned by removing all small fragments that are present 
	in the molecular connection table. Such small fragments are often salt 
	fragments. Implementation-wise, salts are first removed, and then the 
	actual filtering is taking place on the remaining part of the molecular 
	entity. This prevents molecules to be filtered out due to unwanted salt 
	fragments that should have been removed in first instance. The default 
	salt-stripping step can be suppressed by specifying the --salts option, 
	in which case no salt stripping occurs. In this case, all calculations 
	and filtering steps are performed on the entire molecule together with 
	all salt moieties that might be present in the molecular connection table.
	""")

	flags.add_argument("--rename",
	action='store_const',
	required=False,
	const=True,
	default=False,
	help="""
	Molecular titles are sometimes absent or misleading. In such cases, 
	it might be useful to rename the title of each molecule into a number 
	reflecting the sequence of the molecule in the input file. This feature 
	is optional and is initiated with the --rename option. If this option 
	is not provided, renaming will not occur.
	""")

	flags.add_argument("--noLog",
	action='store_const',
	required=False,
	const=True,
	default=False,
	help="""
	When the program is run in the normal filtering mode (not in the tabulate mode), 
	output messages are written to standard output to indicate whether or 
	not the molecule fails or passes the filter criteria. For large input 
	files, this could lead to large logging files. Therefore, this command 
	line option is provided to turn off this default behaviour.
	""")

	flags.add_argument("--version", "-v",
	action='store_const',
	required=False,
	const=True,
	default=False,
	help="""
	Displays the program version.
	""")

	# Parse
	args = parser.parse_args()
	return(args)
