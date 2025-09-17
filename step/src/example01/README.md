# STEP File read and write example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the basic usage of AMCAX STEP Reader and AMCAX STEP Writer. The details are as follows:



	1. Define a printProductName function to output the Product tree structure
	
	2. Define a printSolidName function to output the names of all Solids in the Product tree
	
	3. Set the basic unit used when converting STEP to TopoShape using SetTargetUnit() under AMCAX::STEP::STEPStyledReader; the basic unit is AMCAX::STEP::StepLengthUnit::PresetLengthUnit::METRE
	
	4. Read the file using Read() under AMCAX::STEP::STEPStyledReader
	
	5. Obtain the STEPStyledProduct tree list using GetProducts() under AMCAX::STEP::STEPStyledReader
	
	6. Extract the overall Shape using MakeCompound() under AMCAX::STEP::STEPTool
	
	7. Expand the tree into a one-dimensional array using FlattenInplace() under AMCAX::STEP::STEPTool
	
	8. Convert the TopoShape object to a STEP file using AMCAX::STEP::STEPWriter
	
	9. Set the length unit of the STEP file using SetOutputUnit() under AMCAX::STEP::STEPWriter
	
	10. Write the data part of the STEP file using WriteShapes() under AMCAX::STEP::STEPWriter
	
	11. Compose the ending part of the STEP file and close the output file using Done() under AMCAX::STEP::STEPWriter



<div align = center><img src="https://s2.loli.net/2024/06/04/tmsLOyEUe1GZDnI.png" width="600" height="300">