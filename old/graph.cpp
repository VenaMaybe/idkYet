#include "graph.h"
#include "graph_interaction_manager.h"

Graph::Graph(GraphInteractionManager* graphInteractionManager = nullptr) 
	: graphInteractionManager(graphInteractionManager) {}

void Graph::render() const {
	for (const auto& v : verts) {
		v->render();
	}
	for (const auto& e : edges) {
		e.render();
	}
	// Shitty but just forces the ones on top to be redrawn above
	for (auto &edge : edges) {
		if (edge.getOutlined()) {
        	edge.render();  // A separate function that only draws orange text
    }
}
}

void Graph::update() {
	for (auto& v : verts) {
		v->update();
	}
	for (auto& e : edges) {
		e.update();
	}
}

void Graph::checkShortestPathFrom(const Vertex* start) {
	std::cout << "checkShortestPathFrom() WAS RUN!!!" << std::endl;

	// Clear the mapped data
	totalDistanceTo.clear();
	previous.clear();

	// Initialize the dictionary of distances
	for (const auto& vertex : verts) {
		totalDistanceTo.emplace(vertex.get(), std::numeric_limits<float>::infinity());
	}

	// We set our start node with distance 0
	totalDistanceTo.at(start) = 0.0f;

	////// Moved previous to private variables
	//std::unordered_map<const Vertex*, const Vertex*> previous;

	for (const auto& vertex : verts) {
		// Initially, no vertex has a predecessor so all values are set to nullptr
		previous[vertex.get()] = nullptr;
			// We have to use the operator[] since it inserts a default value if the key doesn't exist
	}

	// This is a priority queue to get the vertex with the current smallest distance
	// < Elements stored, Container used for storage, Comparison function for ordering>
	std::priority_queue<
        std::pair<float, const Vertex*>,
        std::vector<std::pair<float, const Vertex*>>,
        std::greater<>
    > pq;
    pq.push({0.0f, start});

	// Main Dijkstra's Loop
	while (!pq.empty()) {
		// Get the vertex with the smallest distance
		float currentDist = pq.top().first;
		const Vertex* currentVertex = pq.top().second;
		pq.pop();

		// If this distance doesn't match the one in totalDistanceTo, it's outdated so we skip it
		if (currentDist > totalDistanceTo.at(currentVertex)) {
			continue;
		}

		// Check all neighbors of currentVertex
		for (const auto& [neighbor, weight] : adjacencyList.at(currentVertex)) {

			// Calculate the alternate route distance
			float altDistance = totalDistanceTo.at(currentVertex) + weight;

			

			// If we find a shorter path to neighbor
			if (altDistance < totalDistanceTo.at(neighbor)) {
				// Store the path
				totalDistanceTo.at(neighbor) = altDistance; 
				
				// Record the path
				previous[neighbor] = currentVertex;

				// Push the updated distance to the priority queue
				pq.push({altDistance, neighbor});
			}
		}
	}

	for (auto item : previous) {
		std::cout << "In previous (" << item.first << ", " << item.second << ")" << std::endl;
	}

}

std::vector<const Vertex*> Graph::reconstructPath(const Vertex* start, const Vertex* end) {
	std::vector<const Vertex*> path;

    // If we don't have a path (distance is infinity), just return empty
    // (You could check this if you have direct access to totalDistanceTo[end])
    // For now, let's assume there's a path.

    // Begin at 'end' and follow previous links until start
		// This is classic for(initialization, condition, iteration)
    for (const Vertex* current = end; current != nullptr; current = previous.at(current)) {
        path.push_back(current);
        if (current == start) {
            break;
        }
    }

    // Check if we actually reached the start
    // If the last vertex in path is not start, it means no path was found
    if (path.back() != start) {
        // No path found
        return {}; // empty vector
    }

    // Reverse the path to get from start to end
    std::reverse(path.begin(), path.end());

	for (auto vertex : path) {
		std::cout << "In Path: " << vertex << std::endl;
	}

    return path;
}

// using raw pointer to Vertex as the key
Vertex* Graph::addVertex(Vector2 location) {
	return addVertex(location.x, location.y);
}

Vertex* Graph::addVertex(float x, float y) {
	verts.push_back(std::make_unique<Vertex>(x, y));

	Vertex* vertex = verts.back().get();
	
	// Set a callback for when this vertex is clicked
	vertex->setOnClickCallback(
		[&](Vertex* clickedVertex) {
			// Pass the event up to the interaction manager
			if(graphInteractionManager) {
				graphInteractionManager->onVertexClicked(clickedVertex);
			}
		}
	);

	adjacencyList.emplace( // creates a list emplace for each added vertex
		verts.back().get(), // pointer from last vertex added to verts
							// back() returns unique_ptr<Vertex>& reference
							// get()  returns raw pointer managed by unique_ptr
		std::vector<std::pair<const Vertex*, float>>() // initialize with an empty adjacency list
	);

	return verts.back().get();
}

void Graph::addEdge(const Vertex* from, const Vertex* to, float weight) {
	// emplace_back takes the constructor arguments for the element type as its parameters
	edges.emplace_back(from, to, weight); // <- basically Edge()
	// We want to link both together so it's an undirected graph
	adjacencyList.at(from).emplace_back(to, weight);
	adjacencyList.at(to).emplace_back(from, weight);
}

Edge* Graph::getEdgeBetween(const Vertex* start, const Vertex* end) {
	for (Edge& edge : edges) {
		if (edge.getFrom() == start && edge.getTo() == end || edge.getTo() == start && edge.getFrom() == end) {
			return &edge;
		}
	}
	// If it's not found, return nothing, throw an error ig
	return nullptr;
}


const std::deque<std::unique_ptr<Vertex>>& Graph::getVerts() {
	return verts;
}

std::vector<Edge>& Graph::getEdges() {
	return edges;
}

// =========== util

void Graph::printInfo() const {
	std::cout << "# Edges: " << edges.size() << std::endl;
	std::cout << "# Verts: " << verts.size() << std::endl;
}

void Graph::printAdjList() const {
	for (const auto& vertexEntry : adjacencyList) {
		std::cout << "Vert: " << vertexEntry.first << std::endl; // throw a name in eventually
		for (const auto& neighborWeight : vertexEntry.second) {
			std::cout << "\t└─Neighbors: " << neighborWeight.first 
					  << " with weight: " << neighborWeight.second << std::endl;
		}
	}
}