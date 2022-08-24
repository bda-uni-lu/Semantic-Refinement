
from owlready2 import *
#import random
import sys

def readOnto(iteration):
	#print ("My parameter args are " + str(iteration))

	onto1 = get_ontology("ontoFiles/"+str(iteration)+".owl")
	
	onto1.load()
	sync_reasoner(onto1)

	fname = "ontoFiles/sync_onto_"+str(iteration)+".owl"
	default_world.save(fname)
	print("Saved: ")








