# STEP File read and write example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This example shows the basic usage of AMCAX STEP Reader and AMCAX STEP Writer. The details are as follows:



	1. Define a printProductName function to output a Product tree

	2. Define a printSubName function that outputs the names of all sub-shapes in the Product tree

	3. Use AMCAX::STEP::StepDataList create containers used to store data

	4. Use AMCAX::STEP::StepReader to create shapes for converting STEP files into TopoShape objects
	
	5. Use SetUnit() under AMCAX::STEP::StepReader to set the base unit used when converting STEP to TopoShape. The basic unit for AMCAX::STEP::StepLengthUnit::PresetLengthUnit::was
	
	6. Read the STEP entity using Read() under AMCAX::STEP::StepReader
	
	7. Obtain a list of Pointers to the StepData tree using GetShapes() under AMCAX::STEP::StepReader
	
	8. Use AMCAX::STEP::StepDataTool::create a StepData Flatten a copy of the tree and its spread into an array
	
	9. Convert the TopoShape object to a STEP file using AMCAX::STEP::StepWriter
	
	10. Use SetUnit() under AMCAX::STEP::StepWriter to set the length unit of the STEP file
	
	11. Write the header of the STEP file to the stream using Init() under AMCAX::STEP::StepWriter
	
	12. Write the data portion of the STEP file using WriteShape() under AMCAX::STEP::StepWriter
	
	13. Use Done() under AMCAX::STEP::StepWriter to write the end of the STEP file and close the output file



<div align = center><img src="https://s2.loli.net/2024/06/04/tmsLOyEUe1GZDnI.png" width="600" height="300">