# Semantic-Refinement



## References

[1] OWLREADY2: https://pythonhosted.org/Owlready2/

[2] owlcpp: a C++ library for working with OWL ontologies: http://owl-cpp.sourceforge.net/

## TODO

### 6-Jan-2021: 
1. Use OWLREADY2 (understand the existing methods) and explore DSA_04092015.owl.

### 27-Jan-2021:
2. List out all instances.
3. For each instance, show which classes it belongs to.
4. what is reasoning? How we can do reasoning?
5. There should be a lib function which u can use for performing reasoning.

### 3-Feb-2021
1. Change the iteration to print: <instance_name> [list of classes]
2. Find the lib function to do the reasoning.
3. How how the classlist changes once you perform reasoning.

### 10-Feb-2021
1. Save the entiled axioms (after reasoning using Hermit) to a file
2. Use that file to generate the defintion of entities again.

### 24-Feb-2021
1. Find out how the instances of a class changes before and after performing a reasoning step. Come up with a suitable example where you can clear show that count of instance in a class had grown after the reasoning step
2. Create an Ontology (TBox) based on the example mentioned in the paper: https://www.w3.org/community/owled/files/2016/11/OWLED-ORE-2016_paper_10.pdf
3. Work of possible ABox instances for the TBox
4. Find out in which Dl the created ontology benlogs to
5. Perform resoning and Find number of instances that fall under the catagory of SmokeDetectionEvent, TemperatureEvent, etc
