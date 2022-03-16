package main

import (
	"fmt"
	"reflect"
	"sort"

	"github.com/yourbasic/graph"
)

const (
	White = iota
	Gray
	Black
)

// The package doesn't support vertex labeling. However,
// since vertices are always numbered 0..n-1, it's easy
// to add this type of data on the side. This implementation
// of depth-first search uses separate slices to keep track of
// vertex colors, predecessors and discovery times.
type DFSData struct {
	Time     int
	Color    []int
	Prev     []int
	Discover []int
	Finish   []int
}

func DFS(g graph.Iterator) DFSData {
	n := g.Order() // Order returns the number of vertices.
	d := DFSData{
		Time:     0,
		Color:    make([]int, n),
		Prev:     make([]int, n),
		Discover: make([]int, n),
		Finish:   make([]int, n),
	}
	for v := 0; v < n; v++ {
		d.Color[v] = White
		d.Prev[v] = -1
	}
	for v := 0; v < n; v++ {
		if d.Color[v] == White {
			d.dfsVisit(g, v)
		}
	}
	return d
}

func (d *DFSData) dfsVisit(g graph.Iterator, v int) {
	d.Color[v] = Gray
	d.Time++
	d.Discover[v] = d.Time
	// Visit calls a function for each neighbor w of v,
	// with c equal to the cost of the edge (v, w).
	// The iteration is aborted if the function returns true.
	g.Visit(v, func(w int, c int64) (skip bool) {
		if d.Color[w] == White {
			d.Prev[w] = v
			d.dfsVisit(g, w)
		}
		return
	})
	d.Color[v] = Black
	d.Time++
	d.Finish[v] = d.Time
}

// Show how to use this package by implementing a complete depth-first search.
func Example_dFS() {
	// Build a small directed graph:
	//
	//   0 ---> 1 <--> 2     3
	//
	g := graph.New(4)
	g.Add(0, 1)
	g.AddBoth(1, 2)

	fmt.Println(g)
	fmt.Println(DFS(g))
	// Output:
	// 4 [(0 1) {1 2}]
	// {8 [2 2 2 2] [-1 0 1 -1] [1 2 3 7] [6 5 4 8]}
}

func Example_tSort() {
	// Build a small directed graph:
	//
	//   0 ---> 1 <--> 2     3
	//
	g := graph.New(6)
	g.Add(0, 1)
	g.Add(0, 2)
	g.Add(1, 2)
	g.Add(2, 3)
	g.Add(4, 5)

	fmt.Println(g)
	fmt.Println(graph.TopSort(g))
	// Output:
	// 4 [(0 1) {1 2}]
	// {8 [2 2 2 2] [-1 0 1 -1] [1 2 3 7] [6 5 4 8]}
}

func Example_sPath() {
	// Build a small directed graph:
	//
	//   0 ---> 1 <--> 2     3
	//
	g := graph.New(6)
	g.AddCost(0, 1, 1)
	g.AddCost(0, 2, 1)
	g.AddCost(1, 2, 1)
	g.AddCost(2, 3, 1)
	g.AddCost(4, 5, 1)
	// g.AddCost(3, 4, 1)

	gT := graph.Transpose(g)

	n := g.Order()
	fmt.Println(gT)
	result := make(map[string]map[int]map[string]bool)
	for v := 0; v < n; v++ {
		path, distance := graph.ShortestPaths(gT, v)
		fmt.Println("For Vertex: ", indexToVertex(v))
		fmt.Println(path, distance)
		weightInfo := make(map[int]map[string]bool)
		for i, s := range distance {
			if path[i] > 0 {
				vertexToAdd := indexToVertex(i)
				//check if current weightgroup is already present
				if val, ok := weightInfo[int(s-1)]; ok {
					// if weight is already precent, append new vertex to it
					// {1:{A:true}} becomes {1:{A:true, B:true}}
					val[vertexToAdd] = true
				} else {
					// else add new weight and vertex to weightInfo map
					// {1:{A:true}} becomes {1:{A:true}, 2:{B:true}}
					newVertexEntry := make(map[string]bool)
					newVertexEntry[vertexToAdd] = true
					weightInfo[int(s-1)] = newVertexEntry
				}
			}
		}
		currentVertex := indexToVertex(v)
		result[currentVertex] = weightInfo

	}

	keys := make([]string, 0, len(result))
	for k := range result {
		keys = append(keys, k)
	}
	sort.Strings(keys)

	for _, k := range keys {
		fmt.Println(k, ":", result[k])
	}
	fmt.Println(result)

	testval :=
		map[string]map[int]map[string]bool{
			"A": {},
			"B": {0: {"A": true}},
			"C": {0: {"A": true, "B": true}},
			"D": {0: {"C": true}, 1: {"A": true, "B": true}},
			"E": {},
			"F": {0: {"E": true}},
		}

	fmt.Println(testval)

	if !reflect.DeepEqual(testval, result) {
		fmt.Printf("results do not match: \nwant = \"%+v\"\ngot =  \"%+v\"", testval, result)
	} else {
		fmt.Println("SUCCESS")
	}
}

func indexToVertex(i int) string {
	//return string(rune('A' + i))
	myList := [6]string{"A", "B", "C", "D", "E", "F"}
	return myList[i]
}

// var scenarios = []scenario{
// 	{
// 		title: "minimal example",
// 		components: map[string][]string{
// 			"A": {"B", "C"},
// 			"B": {"C"},
// 			"C": {"D"},
// 			"D": {},
// 			"E": {"F"},
// 			"F": {},
// 		},
// 		wantDownstreamDeps: map[string]map[int]map[string]bool{
// 			"A": {},
// 			"B": {0: {"A": true}},
// 			"C": {0: {"A": true, "B": true}},
// 			"D": {0: {"C": true}, 1: {"A": true, "B": true}},
// 			"E": {},
// 			"F": {0: {"E": true}},
// 		},
// 		wantErr: nil,
// 	},
// }

func main() {
	// Example_dFS()
	Example_sPath()
	// Example_tSort()
}
