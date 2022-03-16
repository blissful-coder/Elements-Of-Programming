package main

import (
	"fmt"
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

	gT := graph.Transpose(g)
	//"D": {0: {"C": true}, 1: {"A": true, "B": true}}
	n := g.Order() // Order returns the number of vertices.
	result := make(map[string]map[int]map[string]bool)
	for v := 0; v < n; v++ {
		path, distance := graph.ShortestPaths(gT, v)
		// fmt.Printf("For Vertex: %q\n", toChar(v))
		// fmt.Println(path, distance)
		weightInfo := make(map[int]map[string]bool)
		for i, s := range distance {
			// fmt.Println(i, s)
			if path[i] > 0 {
				if val, ok := weightInfo[int(s-1)]; ok {
					// fmt.Println("Alread Present ", val)
					// addhere := val[int(s)]
					vertexToAdd := fmt.Sprintf("%q", toChar(i))
					val[vertexToAdd] = true
				} else {
					temp2 := make(map[string]bool)
					vertexToAdd := fmt.Sprintf("%q", toChar(i))
					// fmt.Printf("%q", toChar(i))
					temp2[vertexToAdd] = true
					weightInfo[int(s-1)] = temp2
				}
			}
		}
		currentVertex := fmt.Sprintf("%q", toChar(v))
		result[currentVertex] = weightInfo
		// m is a map[string]interface.
		// loop over keys and values in the map.
		// A: {1:{B:true,C:true}, 2: {D:true}}
	}
	// fmt.Println("\n\nResult:")
	// for k, v := range result {
	// 	fmt.Println(k, " : ", v)
	// }

	keys := make([]string, 0, len(result))
	for k := range result {
		keys = append(keys, k)
	}
	sort.Strings(keys)

	for _, k := range keys {
		fmt.Println(k, ":", result[k])
	}
}

func toChar(i int) rune {
	return rune('A' + i)
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
