#ifndef GRAPH_INTERACTION_MANAGER_H
#define GRAPH_INTERACTION_MANAGER_H

/* This should control the UI for selecting start and end points for shortest graph */

#include "vertex.h"
#include "graph.h"

class GraphInteractionManager {
public:
	GraphInteractionManager(Graph* graph);

	void onVertexClicked(Vertex* vertex);
	
	void setSelectingStart(bool selecting) {
		selectingStart = selecting;
	}

private:
	Graph* graph; // The managed graph
	const Vertex* startVertex = nullptr; // For pathing
	const Vertex* endVertex = nullptr; // 
	
	bool selectingStart = true;
};




#endif // GRAPH_INTERACTION_MANAGER_H