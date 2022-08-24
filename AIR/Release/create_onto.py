from owlready2 import *
import random
import sys

def saveOnto(iteration):  

	#print ("My parameter args are " + str(iteration))

	onto = get_ontology("FireEvent.owl")
	onto.load()

	n = 500
	m = 500
	with onto:
	    class Smoke(Thing): pass
	    class SmokePpty(Thing): pass
	    class Event(Thing): pass
	    class Observation(Thing): pass
	    class Elevator(Thing): pass
	    class ServerRoom(Thing): pass
	    class Office(Thing): pass
	    class Temperature(Thing): pass
	    class TemperatureEvent(Thing): pass
	    class ValueAbove20(Temperature): pass
	    class ValueAbove40(ValueAbove20): pass
	    class FireEvent(Thing): pass

	for i in range(n):
	    instance = "b00001f001r001z"
	    smoke = Smoke(instance)

	    SmokePpty_instance = "b00001f001r001y"
	    smoke_property = SmokePpty(name = SmokePpty_instance, hasObservedProperty = [smoke])

	    smoke_event_instance = "b00001f001r001x" + str(i)
	    S_instance = Event(name = smoke_event_instance, hasContext = [smoke_property])

	for i in range(m):

	    random_number = random.randint(40, 100)
	    E_Temp_instance = str(random_number) + "F"
	    Elevator_Temp_instance = ValueAbove40(name = E_Temp_instance)

	    Elevator_instance = "b00001f001er001er"
	    Elevator_loc = Elevator(name = Elevator_instance)

	    E_abnormal_instance = "b00001f001er00" + str(i)
	    obs_instance = Observation(name = E_abnormal_instance, hasObservationResult = [Elevator_Temp_instance], hasLocation = [Elevator_loc])

	    random_number1 = random.randint(20, 39)
	    S_Temp_instance = str(random_number1) + "F"
	    Server_Temp_instance = ValueAbove20(name = S_Temp_instance)

	    Server_instance = "b00001f001sr001sr"
	    Server_loc = ServerRoom(name = Server_instance)

	    S_abnormal_instance = "b00001f001sr00" + str(i)
	    obs_instance = Observation(name = S_abnormal_instance, hasObservationResult = [Server_Temp_instance], hasLocation = [Server_loc])

	    F_Temp_instance = str(random_number) + "F"
	    Office_Temp_instance = ValueAbove40(name = F_Temp_instance)
	    
	    Office_instance = "b00001f001of001of"
	    Office_loc =  Office(name =  Office_instance)

	    F_abnormal_instance = "b00001f001of00" + str(i)
	    obs_instance = Observation(name = F_abnormal_instance, hasObservationResult = [Office_Temp_instance], hasLocation = [Office_loc])
	    
	    random_number2 = random.randint(0, 100)
	    Temp_instance = str(random_number2) + "F"
	    Elevator_Temp_instance = ValueAbove40(name = E_Temp_instance)

	    Temperature_instance = "temperature_event"
	    obs_instance = Observation(name = Temperature_instance, hasObservedProperty = [Elevator_Temp_instance, Server_Temp_instance])
	    
	    Abnormal_Temp_instance = "abnormal_temp_event"
	    abnormal_instance = TemperatureEvent(name = Temperature_instance, hasObservedProperty = [Elevator_Temp_instance, Server_Temp_instance])
	    
	    F_instance = "fire_event"+ str(i)
	    fire_instance = Observation(name = F_instance, hasEvent = [S_instance, abnormal_instance])
	    
	    Server_fire_instance = "b00001f001sr001f"+ str(i)
	    sf_instance = FireEvent(name = Server_fire_instance, hasObservationResult = [Server_Temp_instance], hasLocation = [Server_loc])
	    
	    Elevator_fire_instance = "b00001f001er001f"+ str(i)
	    ef_instance = FireEvent(name = Elevator_fire_instance, hasObservationResult = [Elevator_Temp_instance], hasLocation = [Elevator_loc])
	    
	    Office_fire_instance = "b00001f001of001f"+ str(i)
	    of_instance = FireEvent(name = Office_fire_instance, hasObservationResult = [Office_Temp_instance], hasLocation = [Office_loc])
	    
	onto.save("ontology20.owl")
	#sync_reasoner()
	#default_world.save("sync_onto.owl")

	fname = "ontoFiles/"+str(iteration)+".owl"
	onto.save(fname)
	
#saveOnto(1)	
	
	
	




