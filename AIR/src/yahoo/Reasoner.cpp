/**
 * Copyright (c) 2020 University of Luxembourg. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are
 * permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its contributors may be
 * used to endorse or promote products derived from this software without specific prior
 * written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UNIVERSITY OF LUXEMBOURG AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE UNIVERSITY OF LUXEMBOURG OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

/*
 * EventFilter.cpp
 *
 *  Created on:
 *      Author: vinu.venugopal
 */

#include "Reasoner.hpp"

#include <mpi.h>
//#include <__threading_support>
#include <cstring>
#include <iostream>
#include <iterator>
#include <list>
#include <string>
#include <vector>
#include "Python.h"

#include "../communication/Message.hpp"
#include "../serialization/Serialization.hpp"

using namespace std;

Reasoner::Reasoner(int tag, int rank, int worldSize) :
		Vertex(tag, rank, worldSize) {
	D(cout << "EVENTFILTER [" << tag << "] CREATED @ " << rank << endl;)
	THROUGHPUT_LOG(
			datafile.open("Data/tp_log"+ to_string(rank) + ".tsv");
	)

	// cout << "I am from Reasoner constructor...";

}

Reasoner::~Reasoner() {
	D(cout << "EVENTFILTER [" << tag << "] DELETED @ " << rank << endl;)
}

void Reasoner::batchProcess() {
	cout << "EVENTFILTER->BATCHPROCESS [" << tag << "] @ " << rank << endl;
}

void Reasoner::streamProcess(int channel) {

	cout << "Reasoner->STREAMPROCESS [" << tag << "] @ " << rank
			<< " IN-CHANNEL " << channel << endl;

	Message* inMessage, *outMessage;
	list<Message*>* tmpMessages = new list<Message*>();
	Serialization sede;

	WrapperUnit wrapper_unit;
	EventOWL eventOWL;
	EventFT eventFT;
	long int t1, t2;
	int i=0, c = 0, iteration = 0;
	bool isMessageArrived  = false;

	while (ALIVE) {
		cout << "I am from Reasoner ...";
		t1 = MPI_Wtime();
	
		pthread_mutex_lock(&listenerMutexes[channel]);

		while (inMessages[channel].empty())
			pthread_cond_wait(&listenerCondVars[channel],
					&listenerMutexes[channel]);
					
		while (!inMessages[channel].empty()) {
			inMessage = inMessages[channel].front();
			while( 0 < inMessages[channel].size())
			{
				inMessages[channel].pop_front();
			}	
			tmpMessages->push_back(inMessage);
			isMessageArrived = true;
		}

		pthread_mutex_unlock(&listenerMutexes[channel]);

		while (!tmpMessages->empty()) {

			inMessage = tmpMessages->front();
			tmpMessages->pop_front();

			D(cout << "EVENTFILTER->POP MESSAGE: TAG [" << tag << "] @ " << rank
					<< " CHANNEL " << channel << " BUFFER " << inMessage->size
					<< endl;)
			string myText;

			sede.unwrap(inMessage);
			// if (inMessage->wrapper_length > 0) {
			// 	sede.unwrapFirstWU(inMessage, &wrapper_unit);
			// 	sede.printWrapper(&wrapper_unit);
			// }

			int offset = sizeof(int)
					+ (inMessage->wrapper_length * sizeof(WrapperUnit));

			outMessage = new Message(inMessage->size - offset,
					inMessage->wrapper_length); // create new message with max. required capacity

			

			memcpy(outMessage->buffer, inMessage->buffer, offset); // simply copy header from old message for now!
			outMessage->size += offset;

			int event_count = (inMessage->size - offset) / sizeof(EventOWL);

			D(cout << "THROUGHPUT: " << event_count <<" @RANK-"<<rank<<" TIME: "<<(long int)MPI_Wtime()<< endl;)

			THROUGHPUT_LOG(
					datafile <<event_count<< "\t"
					<<rank<< "\t"
					<<(long int)MPI_Wtime()
					<< endl;
					)

			int i = 0, j = 0;
			// cout << "1\n";
			while (i < event_count && isMessageArrived) {
				isMessageArrived = false;
				// cout << "2\n";

				sede.OWLdeserialize(inMessage, &eventOWL,
						offset + (i * sizeof(EventOWL)));

				// D(
					cout << "  " << i << "\tevent_time: " << eventOWL.event_time
						// << "\tevent_type: " << eventOWL.event_type << "\t"
						// << "ad_id: " << eventOWL.ad_id 
						<< endl;
						// )

					Py_Initialize();
					PyRun_SimpleString("import sys");
					PyRun_SimpleString("sys.path.append(\"./\")");
					PyObject *pName, *pModule, *pDict, *pFunc, *pArgs,*pValue;
		
				// Convert the file name to a Python string.
					pModule = PyImport_Import(PyUnicode_FromString("read_onto"));	
					pFunc = PyObject_GetAttrString(pModule, "readOnto");
					pArgs = PyTuple_New(1);
					PyObject *pInteger = Py_BuildValue("i", eventOWL.event_time);
					//PyObject *pRank= Py_BuildValue("i", rank);
					PyTuple_SetItem(pArgs, 0, pInteger);
					//PyTuple_SetItem(pArgs, 1, pRank);

					PyObject* pResult = PyObject_CallObject(pFunc, pArgs);
					Py_Finalize();

				if (strcmp(eventOWL.event_type, "click")==0) { //FILTERING BASED ON EVENT_TYPE
					eventFT.event_time = eventOWL.event_time;
					memcpy(eventFT.ad_id, eventOWL.ad_id, 37);
					sede.YSBserializeFT(&eventFT, outMessage); // store filtered events directly in outgoing message!
					j++;
				}

				i++;
			}
			//cout << "FILTERED_EVENT_COUNT: " << j << endl;

			// Replicate data to all subsequent vertices, do not actually reshard the data here
			int n = 0;
			for (vector<Vertex*>::iterator v = next.begin(); v != next.end();
					++v) {

				int idx = n * worldSize + rank; // always keep workload on same rank

				n++;
				break; // only one successor node allowed!
			}

			delete inMessage;
			c++;
			iteration++;
		}

		tmpMessages->clear();
	}

	delete tmpMessages;
}
