package main

import "fmt"

type Node struct {
	value int
	next  *Node
}

type LinkedList struct {
	head *Node
	len  int
}

func (l *LinkedList) Insert(val int) {
	n := Node{}
	n.value = val
	if l.len == 0 {
		l.head = &n
		l.len++
		return
	}
	ptr := l.head
	for i := 0; i < l.len; i++ {
		if ptr.next == nil {
			ptr.next = &n
			l.len++
			return
		}
		ptr = ptr.next
	}
}

func (l *LinkedList) Print() {
	if l.len == 0 {
		fmt.Println("No nodes in list")
	}
	ptr := l.head
	for i := 0; i < l.len; i++ {
		fmt.Println("Node: ", ptr)
		ptr = ptr.next
	}
}

func main() {
	l := LinkedList{}

	fmt.Println("\n************* Insert *************")
	l.Insert(89)
	l.Insert(232)
	l.Insert(1)
	l.Insert(95)
	fmt.Println("************* Print *************")
	l.Print()
}
