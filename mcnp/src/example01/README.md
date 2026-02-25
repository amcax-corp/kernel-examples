# MCNP Parser Example

[![en-us](https://img.shields.io/badge/en-us-yellow.svg)](./README.md) [![中文-简体](https://img.shields.io/badge/%E4%B8%AD%E6%96%87-%E7%AE%80%E4%BD%93-red.svg)](./README.zh_cn.md)

### This tutorial provides the basic usage of the MCNP parser: parsing MCNP input cards, automatically constructing topological entities, and finally exporting the results in the form of Labels (with material attributes attached to the Labels). The specific implementation steps are as follows:

	1. Use AMCAX::MCNP::MCNPReader to construct a parser.
	
	2. Use the Read() method under AMCAX::MCNP::MCNPReader for parsing and construction.
	
	3. Use the GetShape() method under AMCAX::Label to obtain the shape corresponding to the Label.
	
	4. Use the Add() method under AMCAX::TopoBuilder to add the traversed shapes to a Compound.
	
	5. Use the FindAttribute() method under AMCAX::Label to obtain attribute.
	
	6. Use the GetValue() method under AMCAX::Attribute to obtain the attribute value.
	
	7. Use the Write() method under AMCAX::OCCTIO::OCCTTool to write the Compound into a BREP file.

